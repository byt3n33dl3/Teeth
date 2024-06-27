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

var INSECURE = new function() {
  this.angel = function(opts) {
    //Algorithm used at http://angel.net/~nic/passwd.current.html 
    return Crypto.util.bytesToBase64(Crypto.SHA1(opts['password'] + ":" + opts['domain'], {asBytes: true})).substring(0,8) + "1a";
  };
    



  this.md5hash = function(opts) {
    //Original algorithm:  (domain used as salt)
    //#!/bin/bash
    //salt=`echo -n $1 | base64 | md5sum | cut -c 1-8`
    //salthash=`openssl passwd -1 -salt $salt`
    //echo ${salthash:12}
    // Openssl implementation from:
    //http://www.freebsd.org/cgi/cvsweb.cgi/~checkout~/src/lib/libcrypt/crypt.c?rev=1.2
    var salt = Crypto.MD5(btoa(opts['domain'] + opts['seq']) + '\n').substring(0,8);
    var tmp = Crypto.MD5(opts['password'] + salt + opts['password'], {asBytes:true});
    var str = opts['password'] + "$1$" + salt;
    str = Crypto.charenc.Binary.stringToBytes(str);

    var cnt;
    for (cnt = opts['password'].length;cnt > 16; cnt = cnt - 16) {
      str = str.concat(tmp);
    }
    str = str.concat(tmp.slice(0,cnt));


    for(cnt = opts['password'].length;cnt > 0; cnt = cnt >> 1) {
      if ((cnt & 1) != 0) {
        str = str.concat([0]);
      }
      else {
        str = str.concat(Crypto.charenc.Binary.stringToBytes(opts['password'].substring(0,1)));
      }
    }
    var foo = Crypto.charenc.Binary.bytesToString(str);
    var last = Crypto.MD5(str, {asBytes:true});

    for (cnt=0;cnt<1000;cnt++) {
      var next = [];
      if ((cnt&1) != 0) {
        next = next.concat(Crypto.charenc.Binary.stringToBytes(opts['password']));
      }
      else {
        next = next.concat(last);
      }
      if (cnt % 3 != 0) {
        next = next.concat(Crypto.charenc.Binary.stringToBytes(salt));
      }
      if (cnt % 7 != 0) {
        next = next.concat(Crypto.charenc.Binary.stringToBytes(opts['password']));
      }
      if ((cnt&1) != 0) {
        next = next.concat(last);
      }
      else {
        next = next.concat(Crypto.charenc.Binary.stringToBytes(opts['password']));
      }
      last = Crypto.MD5(next, {asBytes:true});
    }
    // For some reason they reorder the bytes when converting to base64
    var reorder = [
        last[0], last[6], last[12],
        last[1], last[7], last[13],
        last[2], last[8], last[14],
        last[3], last[9], last[15],
        last[4], last[10], last[5],
        0,0,last[11] ];

    // They use a different base64
    var tmp2 = Crypto.util.bytesToBase64(reorder);
    var tmp3 = DOH.trans_chars(Crypto.util.bytesToBase64(reorder),"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/","./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    var tmp4 = "";
    for (cnt=0;cnt<tmp3.length;cnt = cnt + 4) {
      tmp4 += tmp3.substring(cnt+3,cnt+4);
      tmp4 += tmp3.substring(cnt+2,cnt+3);
      tmp4 += tmp3.substring(cnt+1,cnt+2);
      tmp4 += tmp3.substring(cnt,cnt+1);
    }
    return tmp4.substring(0,tmp4.length-2);
//    return salt;
  };
};
