#!/bin/sh

SCRIPT_FILE_PATTERN='\.prep/fuzzer/common.c?$'
SCRIPT_FILES=`git diff --cached --name-only | grep -E $SCRIPT_FILE_PATTERN`
SCRIPT_FILES="$SCRIPT_FILES"`git diff --cached --name-only | grep -F '(benchmark-unify|relbench)'`
if [ "x$SCRIPT_FILES" != "x" ] ; then
# 1. missing exec bit on a script file.
   SCRIPT_LISTING=`echo "$SCRIPT_FILES" | xargs ls -l`
   echo "$SCRIPT_LISTING" | cut -b 4 | grep -v -q x && \
      echo 'COMMIT REJECTED:' && echo "$SCRIPT_LISTING" | grep ^-..- && exit 1
fi

#--------------------------------------------------------------
# Tests 2/3/4/5. Make sure source does not have execute bit set
#--------------------------------------------------------------
TXT_FILE_PATTERN='\.(ac|cl|c|h|txt|S|s|in|chr|conf|txt|md|asm|cin|py|dep|gost|legacy|macros|stub|m4|cu|bash_completion|zsh_completion|lst)(\..+)?$'
TXT_FILES=`git diff --cached --name-only | grep -E $TXT_FILE_PATTERN`
TXT_FILES="$TXT_FILES"`git diff --cached --name-only | grep -E ^doc/`
if [ "x$TXT_FILES" != "x" ] ; then
# 2. exec attrib
   TXT_LISTING=`echo "$TXT_FILES" | xargs ls -l`
   echo "$TXT_LISTING" | cut -b 4 | grep -q x && \
      echo 'COMMIT REJECTED:' && echo "$TXT_LISTING" | grep ^-..x && exit 1
# 3. Trailing spaces
   TXT_LISTING=`echo "$TXT_FILES" | xargs grep -l '[ ]$'`
   if [ "x$TXT_LISTING" != "x" ] ; then
      echo 'COMMIT REJECTED:' && echo "$TXT_LISTING" && exit 1
   fi
# 4. DOS eol's
   TXT_LISTING=`echo "$TXT_FILES" | xargs grep -lU $'\x0D'`
   if [ "x$TXT_LISTING" != "x" ] ; then
      echo 'COMMIT REJECTED:' && echo "$TXT_LISTING" && exit 1
   fi
# 5. missing final EOL
   # this is by far the most costly test.  We should fine a more effiecent implementation.  It is not bad on
   # a couple file commit, but if it is dozens or 100's of files, it is slow
   if [ -e /usr/bin/perl ] ; then
      echo $TXT_FILES | \
         xargs perl -e '$r=0; foreach $n (@ARGV)
                        {
                          if (open(F,"<",$n)) { seek(F,-1,2); read(F,$c,1);
                          if($c ne "\n") { $r=1; print "Missing final EOL in file $n\n"; }
                          close(F); exit($r); }
                        }'
        if [ "x$?" != "x0" ] ; then echo 'COMMIT REJECTED:' && exit 1 ; fi
   else
      # slow but should be portable.
      MISSING_EOF=""
      for f in $TXT_FILES; do if [ -e "$f" ]; then if [ -n "$(tail -c 1 <"$f")" ]; then echo "missing final EOL in file $f" && MISSING_EOF="Yup" ; fi ; fi ; done
      if [ "x$MISSING_EOF" != "x" ] ; then
         echo 'COMMIT REJECTED:' && exit 1
      fi
   fi
fi

exit 0=0
