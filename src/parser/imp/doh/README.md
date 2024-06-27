# DOmain Hash password generator (DOH)

The Domain Hash Password Generator (DOH) uses hashes to generate unique passwords for each domain from a single master password.

## Features

* Passwords are cryptographically secure.
* Passwords are never stored anywhere. Not even on your own computer.
* Passwords are guaranteed to be accepted by the website.\*
* Passwords are reproducible from a single master password.
* Multiple hashing strategies are available.

\* Given a correct domain specification (see below).

## Visuals

After installation, the patented "DOH it!" button appears in password fields.

![Username](https://raw.githubusercontent.com/amozoss/doh/master/images/username.png)

Pressing "DOH it!" instantly generates your secure password. 

![Password](https://raw.githubusercontent.com/amozoss/doh/master/images/password_generated.png)

## Description

DOH generates passwords based on a domain, master password, and salt.  Each site has different passwords, and DOH can generate passwords that are guaranteed to have the right number of special characters, uppercase letters, numbers, etc.  The algorithm does not save any state, so any computer you use can generate your passwords with information from your head -- without any syncing.  This also means there is no database to be hacked or service provider you need to trust.

DOH is entirely opensource, so you can audit the code yourself to make sure your passwords are safe.

The following have been implemented:

* Pure javascript HTML webpage generator
* Chromium plugin
* Firefox plugin (unfinished; see branches)



##Installation

You need some flavor of ruby installed (it converts the yaml file to json).

    git clone https://github.com/onionjake/doh.git
    cd doh
    ./setup

### Chromium Plugin

    <launch chrome/chromium>
    Type in 'chrome://extensions' in the address bar
    Check 'Developer mode'
    Load unpacked extension
    Browse to 'doh/chromium' and click Open
    
### HTML (any browser)

    <launch browser>
    Type 'file://<cloned location>/doh/html/index.html' into the address bar
    <or>
    Goto 'https://onionjake.github.io/doh/'
    
    
## Terminology

Master Password:  Your secret password.  This should be long, secure, and follow all good password conventions.

Salt:  This is something unique to you.  It does not need to be secret or hard to guess, just memorable.  Something like your email address or your favorite online username is good.

Domain: This is part of the URL of the website.  It does not include www or anything else ahead of the domain.

Examples: 

https://www.github.com/onionjake/doh - github.com
          
https://login.yahoo.com - yahoo.com

## Use

### Chromium Plugin

    TODO    

### HTML (any browser)

    Read terminology section above
    Enter Master Password
    Enter Salt
    Enter Domain
    Enter Seqeunce String (optional)
    Click 'Generate Password'
    Copy and paste generated password into website.
    
## The algorithm

Here is the algorithm in a nutshell:

1. User enters salt (username, name, or something memorable but unique), master password, and domain, and an optional sequence number.
2. Compute PBKDF2(sha512, sha256(salt + master password), sequence + domain + salt, 2000, <varies on domain spec>) and output in base64.\*  Remove padding characters ('=').
3. Based on a domain specification (shipped with program or provided by user), translate standard base64 to a new base64 with characters from the required character set for given domain.
4. Search result for password that meets all requirements set in the domain spec.
5. If password cannot be found, rotate a bit and search again.
6. If password cannot be found after 5 rotations, rehash and search again.

\* Where '+' is concatenation.  See http://en.wikipedia.org/wiki/PBKDF2 on PBKDF2 function definition.

The expected number of characters needed to fulfill typical password requirements is 10 characters. Determining each domain's expected number of minimum characters to meet requirements can be done using the coupon collectors problem.

## Domain Specifications

TODO

## License

Copyright (c) 2016 Jake Willoughby

This file is part of DOH.

DOH is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

DOH is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with DOH.  See gpl3.txt. If not, see <http://www.gnu.org/licenses/>.
