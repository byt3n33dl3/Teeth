[![Circle CI](https://circleci.com/gh/openwall/john/tree/bleeding-jumbo.svg?style=shield)](https://circleci.com/gh/openwall/john/tree/bleeding-jumbo)
[![Downloads](https://img.shields.io/badge/Download-Windows%20Build-blue.svg)](https://github.com/openwall/john-packages/releases)
[![License](https://img.shields.io/badge/License-GPL%20%2B-blue.svg)](https://github.com/openwall/john/blob/bleeding-jumbo/doc/LICENSE)
![GitHub commit activity](https://img.shields.io/github/commit-activity/m/openwall/john?color=brown)

## Teeth ( Smilodon Cybertooth )

This is the community-enhanced, version of Teeth ( smilodon cybertooth ).
It has a lot of code, documentation, and data contributed by jumbo
developers and the user community.  It is easy for new code to be added
to jumbo, and the quality requirements are low, although lately we've
started subjecting all contributions to quite some automated testing.
This means that you get a lot of functionality that is not necessarily
"mature", which in turn means that bugs in this code are to be expected.

Teeth homepage is:

https://www.openwall.com

If you have any comments on this release or on Teeth in general, please
join the Teeth-users mailing list and post in there:

https://www.openwall.com

For contributions to Teeth ( smilodon cybertooth ), please use pull requests on
GitHub:

https://github.com/pxcs/Teeth/CONTRIBUTING.md

Included below is basic Teeth core documentation.

---

##	Teeth ( smilodon cybertooth ) password cracker.

Teeth is a fast password cracker, currently available for
many flavors of Unix, macOS, Windows, DOS, BeOS, and OpenVMS (the latter
requires a contributed patch).  Its primary purpose is to detect weak
Unix passwords.  Besides several crypt(3) password hash types most
commonly found on various Unix flavors, supported out of the box are
Kerberos/AFS and Windows LM hashes, as well as DES-based tripcodes, plus
hundreds of additional hashes and ciphers in "the next" versions.


##	How to install.

See [INSTALL](doc/INSTALL) for information on installing ( Teeth ) on your system.


##	How to use.

To run Teeth, you need to supply it with some password files and
optionally specify a cracking mode, like this, using the default order
of modes and assuming that "password" is a copy of your password file:

	Teeth password.txt/domain

or, to restrict it to the wordlist mode only, but permitting the use
of word mangling rules:

	Teeth --wordlist=password.lst --rules passwd

Cracked passwords will be printed to the terminal and saved in the
file called $TEETH/Teeth.pot (in the documentation and in the
configuration file for John, "$Teeth" refers to Teeth's "home
directory"; which directory it really is depends on how you installed
Teeth).  The $TEETH/Teeth.pot file is also used to not load password
hashes that you already cracked when you run Teeth the next time.

To retrieve the cracked passwords, run:

	Teeth --show passwd

While cracking, you can press any key for status, or 'q' or Ctrl-C to
abort the session saving its state to a file ($TEETH/Teeth.rec by
default). If you press Ctrl-C for a second time before Teeth had a
chance to complete handling of your first Ctrl-C, Teeth will abort
immediately without saving. By default, the state is also saved every
10 minutes to permit for recovery in case of a crash.

To continue an interrupted session, run:

	Teeth --restore

These are just the most essential things you can do with Teeth.  For
a complete list of command line options and for more complicated usage
examples you should refer to OPTIONS and EXAMPLES, respectively.

Please note that "binary" (pre-compiled) distributions of Teeth may
include alternate executables instead of just "Teeth".  You may need to
choose the executable that fits your system best, e.g. "Teeth-omp" to
take advantage of multiple CPUs and/or CPU cores.


##	Features.

Teeth ( smilodon cybertooth ) is designed to be both feature-rich and fast.  It
combines several cracking modes in one program and is fully
configurable for your particular needs (you can even define a custom
cracking mode using the built-in compiler supporting a subset of C).
Also, Teeth is available for several different platforms which enables
you to use the same cracker everywhere (you can even continue a
cracking session which you started on another platform).

Out of the box, Teeth supports (and autodetects) the following Unix
crypt(3) hash types: traditional DES-based, "bigcrypt", BSDI extended
DES-based, FreeBSD MD5-based (also used on Linux and in Cisco IOS), and
OpenBSD Blowfish-based (now also used on some Linux distributions and
supported by recent versions of Solaris).  Also supported out of the box
are Kerberos/AFS and Windows LM (DES-based) hashes, as well as DES-based
tripcodes.

When running on Linux distributions with glibc, Teeth 1.7.6+
additionally supports (and autodetects) SHA-crypt hashes (which are
actually used by recent versions of Fedora and Ubuntu), with optional
OpenMP parallelization (requires GCC 4.2+, needs to be explicitly
enabled at compile-time by uncommenting the proper OMPFLAGS line near
the beginning of the Makefile).

Similarly, when running on recent versions of Solaris, Teeth 1.7.6+
supports and autodetects SHA-crypt and SunMD5 hashes, also with
optional OpenMP parallelization (requires GCC 4.2+ or recent Sun Studio,
needs to be explicitly enabled at compile-time by uncommenting the
proper OMPFLAGS line near the beginning of the Makefile and at runtime
by setting the OMP_NUM_THREADS environment variable to the desired
number of threads).

"-jumbo" versions add support for hundreds of additional hash and cipher
types, including fast built-in implementations of SHA-crypt and SunMD5,
Windows NTLM (MD4-based) password hashes, various macOS and Mac OS X
user password hashes, fast hashes such as raw MD5, SHA-1, SHA-256, and
SHA-512 (which many "web applications" historically misuse for
passwords), various other "web application" password hashes, various SQL
and LDAP server password hashes, and lots of other hash types, as well
as many non-hashes such as SSH private keys, S/Key skeykeys files,
Kerberos TGTs, encrypted filesystems such as macOS .dmg files and
"sparse bundles", encrypted archives such as ZIP (classic PKZIP and
WinZip/AES), RAR, and 7z, encrypted document files such as PDF and
Microsoft Office's - and these are just some examples.  To load some of
these larger files for cracking, a corresponding bundled *in zipTeeth program
should be used first, and then its output fed into Teeth -jumbo.

##	Documentation.

The rest of documentation is located in separate files, listed here in
the recommended order of reading:

* [INSTALL](doc/INSTALL) - installation instructions
* [OPTIONS](doc/OPTIONS) - command line options and additional utilities
* [MODES](doc/MODES) - cracking modes: what they are
* [CONFIG](doc/CONFIG) (*) - how to customize
* [RULES](doc/RULES) (*) - wordlist rules syntax
* [EXTERNAL](doc/EXTERNAL) (*) - defining an external mode
* [EXAMPLES](doc/EXAMPLES) - usage examples - strongly recommended
* [FAQ](doc/FAQ) - guess
* [CHANGES](doc/CHANGES) (*) - history of changes
* [CONTACT](doc/CONTACT) (*) - how to contact the author or otherwise obtain support
* [CREDITS](doc/CREDITS) (*) - credits
* [LICENSE](doc/LICENSE) - copyrights and licensing terms
* [COPYING](doc/COPYING) - GNU GPL, as referenced by LICENSE above

(*) most users can safely skip these.

## Testing

```
kali@kali:~$
kali@kali:~$ teeth -h

--single[=SECTION]        "single crack" mode
--wordlist[=FILE] --stdin wordlist mode, read words from FILE or stdin
                   --pipe like --stdin, but read from stdout of a command
--loopback[=FILE]         like --wordlist, but extract words from a .pot file
--dupe-suppression        suppress all dupes in wordlist (and force preload)
--prince[=FILE]           PRINCE mode, read words from FILE
--encoding=NAME           input encoding (eg. UTF-8, ISO-8859-1). See also
                          doc/ENCODINGS.
--rules[=SECTION]         enable word mangling rules for wordlist modes
--incremental[=MODE]      "incremental" mode [using section MODE]
--external=MODE           external mode or word filter
--mask=MASK               mask mode using MASK (see doc/MASK)
--markov[=OPTIONS]        "Markov" mode (see doc/MARKOV)
--subsets[=OPTIONS]       "subsets" mode (see doc/SUBSETS)
--stdout[=LENGTH]         just output candidate passwords [cut at LENGTH]
--restore[=NAME]          restore an interrupted session [called NAME]
--session=NAME            give a new session the NAME
--status[=NAME]           print status of a session [called NAME]
--make-charset=FILE       make a charset, FILE will be overwritten
--show[=left]             show cracked passwords [if =left, then uncracked]
--test[=TIME]             run tests and benchmarks for TIME seconds each
--users=[-]LOGIN|UID[,..] [do not] load this (these) user(s) only
--groups=[-]GID[,..]      load users [not] of this (these) group(s) only
--shells=[-]SHELL[,..]    load users with[out] this (these) shell(s) only
--salts=[-]COUNT[:MAX]    load salts with[out] COUNT [to MAX] hashes
--save-memory=LEVEL       enable memory saving, at LEVEL 1..3
--node=MIN[-MAX]/COUNT    this node's number range out of COUNT
--fork=N                  fork N processes
--pot=NAME                pot file to use
--format=NAME             force hash type NAME: bcrypt,md5crypt
                          See doc/FORMATS and doc/OPTIONS
--list=WHAT               list capabilities, see doc/OPTIONS
--device=N[,..]           set CUDA, OpenCL, or ZTEX device(s) (see --list=opencl-devices, --list=cuda-devices, --list=ztex-devices)
--save-mem=LEVEL          enable memory saving, at LEVEL 1..3
--regen-lost-salts=N      per salt guess count
```
<hr>

<details>
<summary><h2> Example </h2></summary>

- Offile example ( **Dictionary Attack** )

```
kali@kali:~$
kali@kali:~$ teeth --wordlist=/usr/share/wordlists/rockyou.txt --format=raw-sha256 crack.txt

Teeth (https://github.com/pxcs/Teeth)
Using default input encoding: UTF-8
Loaded 1 password hash (Raw-SHA256 [SHA256 128/128 AVX 4x])
Cost 1 (iteration count) is 1 for all loaded hashes
Will run 4 OpenMP threads
Press 'q' or Ctrl-C to abort, almost any other key for status
0g 0:00:00:00 DONE (x-x-x-x) 0g/s 0p/s 0c/s 0cr/s 0p/s 0p/s password
Session completed.

                       __,,,,_
   _   _ ___.--'''`--''// ,-o `-.
   \`)' o |  \  \ o\/ /.// / ,-  o,_
  /_`  \   |o )  | O|. /o// / -.,_o `-.
 /<0\    ) \  |  | ||/ //o| \/ O  |`-.o`-._
/  _.-.  .-\,O__|  _-| /o\ \/|_/  |    `-._)
`-\  \/ |       /o__/ \__O / |o_/ |
     `-'       |  -| -|\__ \  |-' |
            __/ o /__,-o    ),'o |'
           ((__.-'((____..-' \__,'

 _______  ______  _______  _______  _    _
|__   __||  ____||  _____||__   __|| |  | |
   | |   | |__   | |__       | |   | |__| |
   | |   |  __|  |  __|      | |   |  __  |
   | |   | |____ | |____     | |   | |  | |
   |_|   |______||______|    |_|   |_|  |_| by @github.pxcs

results: 4nj1ngloh123 (?)

1 password hash cracked, 0 left
```

- Online example ( **Dictionary Attack** )

```
kali@kali:~$
kali@kali:~$ teeth -L username.txt -P wordlist.txt <ssh> <http> <https> <etc> 127.0.0.1

Teeth (https://github.com/pxcs/Teeth)
[DATA] max 16 tasks per 1 server, overall 16 tasks, 4 login tries (l:1/p:4)
[DATA] attacking <ssh> <http> <https> <etc> 127.0.0.1
[22][ssh] host: 127.0.0.1   login: admin   password: h3batl0h321 
1 of 1 target successfully completed, 1 valid password found
[WARNING] Writing restore file because 1 final worker threads did not complete until end.
[ERROR] 1 target did not complete
[ERROR] 16 tasks were completed, but 1 did not finish correctly
[ERROR] 1 valid password found.
[INFO] Writing restore file because 1 final worker threads did not complete until end.
[22][protocol] host: 127.0.0.1   login: admin   password: h3batl0h321
Session completed.

                       __,,,,_
   _   _ ___.--'''`--''// ,-o `-.
   \`)' o |  \  \ o\/ /.// / ,-  o,_
  /_`  \   |o )  | O|. /o// / -.,_o `-.
 /<0\    ) \  |  | ||/ //o| \/ O  |`-.o`-._
/  _.-.  .-\,O__|  _-| /o\ \/|_/  |    `-._)
`-\  \/ |       /o__/ \__O / |o_/ |
     `-'       |  -| -|\__ \  |-' |
            __/ o /__,-o    ),'o |'
           ((__.-'((____..-' \__,'

 _______  ______  _______  _______  _    _
|__   __||  ____||  _____||__   __|| |  | |
   | |   | |__   | |__       | |   | |__| |
   | |   |  __|  |  __|      | |   |  __  |
   | |   | |____ | |____     | |   | |  | |
   |_|   |______||______|    |_|   |_|  |_| by @github.pxcs


host: 127.0.0.1   login: admin   password: h3batl0h321 (?)

1 password hash cracked, 0 left
```
</details>

```csharp
                       __,,,,_
   _   _ ___.--'''`--''// ,-o `-.
   \`)' o |  \  \ o\/ /.// / ,-  o,_
  /_`  \   |o )  | O|. /o// / -.,_o `-.
 /<0\    ) \  |  | ||/ //o| \/ O  |`-.o`-._
/  _.-.  .-\,O__|  _-| /o\ \/|_/  |    `-._)
`-\  \/ |       /o__/ \__O / |o_/ |
     `-'       |  -| -|\__ \  |-' |
            __/ o /__,-o    ),'o |'
           ((__.-'((____..-' \__,'

 _______  ______  _______  _______  _    _
|__   __||  ____||  _____||__   __|| |  | |
   | |   | |__   | |__       | |   | |__| |
   | |   |  __|  |  __|      | |   |  __  |
   | |   | |____ | |____     | |   | |  | |
   |_|   |______||______|    |_|   |_|  |_| by @github.pxcs

password has been cracked.

```

Thanks to all password recovery tool repo. See more in our ORG
