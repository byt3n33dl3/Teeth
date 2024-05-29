// Copyright (c) 2012 Jake Willoughby
// 
// This file is part of DOH.
// 
// DOH is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
// 
// DOH is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with DOH.  See gpl3.txt. If not, see <http://www.gnu.org/licenses/>.

// Requires 2.5.3-crypto-sha1-hmac-pbkdf2.js to be included first.
// Requires js-yaml-0.3.7.min.js to be included first.

var DOH = new function() {
var lower   = "abcdefghijklmnopqrstuvwxyz";
var upper   = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
var num     = "0123456789";
var special = " !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

var char_set = function(use,exclude) {
  var use_vals = use.split(',').sort();
  var even_split = Math.floor(64/use_vals.length);
  var left = 64;
  var pos  = 0;
  var final_set = "";
  var size = 0;
  
  for (var i=0; i<use_vals.length; i++) {
    switch (use_vals[i]) {
      case "c":
        size = even_split;
        if (size > upper.length) {
          size = upper.length;
        }
        final_set += upper.substring(0,size);
        left -= size;
        break;
      case "l":
        size = even_split;
        if (size > lower.length) {
          size = lower.length;
        }
        final_set += lower.substring(0,size);
        left -= size;
        break;
      case "n":
        size = even_split;
        if (size > num.length) {
          size = num.length;
        }
        final_set += num.substring(0,size);
        left -= size;
        break;
      case "x":
        size = left;
        if (size > special.length) {
          size = special.length;
        }
        final_set += special.substring(0,size);
        left -= size;
        break;
      default:
        alert("Bad use string " + use);
    }
  }

  var exclude_re = new RegExp ("[" + RegExp.escape(exclude) + "]", 'g');
  final_set = final_set.replace(exclude_re,'');
  while (final_set.length < 64) {
    final_set += final_set;
  }
  return final_set;
}

this.trans_chars = function(str,from,to) {
  var translate_re = new RegExp ("[" + from + "]", 'g');
  return (str.replace(translate_re, function(match) {
    return to.substr(from.indexOf(match),1); })
  );
}

// Thanks to: http://simonwillison.net/2006/jan/20/escape/
RegExp.escape = function(text) {
    return text.replace(/[-[\]{}()*+?.,\\^$|#\s]/g, "\\$&");
}

var get_domain_reqs = function(domain) {
  var rsp = {};
  var ds = DOH_UI.domainSpecs;
  if (!(domain in ds)) {
    domain = "defaults";
  }
  var d = ds[domain];
  rsp.use     = d.use;
  rsp.exclude = d.exclude;
  rsp.length  = d.max_length;
  return rsp;
}

this.gen_password = function(opts) { //hashedMaster,salt,seq,domain) {
    var hashedMaster = opts['hashedMaster'];
    var salt = opts['salt'];
    var seq = opts['seq'];
    var domain = opts['domain'];
    var hashFunction = opts['hashFunction'];
    if (hashFunction == "sha1") {
      hashFunction = Crypto.SHA1;
    }
    else if (hashFunction == "sha256") {
      hashFunction = Crypto.SHA256;
    }
    else {
      hashFunction = Crypto.SHA256;
    }
    var reqs = get_domain_reqs(domain);

    // Convert character length into byte lengths
    var len = Math.ceil(reqs.length*6/8); 
    var foo =  Crypto.PBKDF2(hashedMaster,seq + domain + salt,len, {iterations: 2000, 
            asBytes: true,
            hasher: hashFunction});
    foo =  Crypto.util.bytesToBase64(foo);
    var set = char_set(reqs.use, reqs.exclude);
    var result = DOH.trans_chars(foo,upper+lower+num+"+/", set);
    return result;
}
};
