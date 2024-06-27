#!/usr/bin/env python3

#########################################################################
# Contains common IO functions that I use when parsing password and
# dictionary files. Goal is to have one library shared across multiple
# projects since a lot of those projects have to do common things like
# read in a set of previously cracked passwords
#
#########################################################################

import os
import sys
import errno
import codecs

##############################################################################
# Create a directory if one does not already exist
##############################################################################
def make_sure_path_exists(path):
    try:
        os.makedirs(path)
    except OSError as exception:
        if exception.errno != errno.EEXIST:
            raise
            

#################################################################################################
# Used for autodetecting file encoding of the training password set
#
# Returns True if an encoding can be determined
# Returns False if a file error occurs
#
# Requires the python package chardet to be installed
# pip3 install chardet
# You can also get it from https://github.com/chardet/chardet
# I'm keeping the declarations for the chardet package local to this file so people can run this
# tool without installing it if they don't want to use this feature
##################################################################################################
def detect_file_encoding(training_file, file_encoding, max_passwords = 10000, default = 'utf-8'):
    print()
    print("Attempting to autodetect file encoding of the file: " + str(training_file), file=sys.stderr)
    print("-----------------------------------------------------------------")

    ##--Try to import chardet. 
    ##--If that package is not installed print out a warning and use the default
    try:
        from chardet.universaldetector import UniversalDetector
        detector = UniversalDetector()
    except ImportError as error:
        print("FAILED: chardet not installed", file=sys.stderr)
        print("IT IS HIGHLY RECOMMENDED THAT YOU INSTALL THE chardet PACKAGE", file=sys.stderr)
        print("or manually specify the file encoding of the training set via the command line", file=sys.stderr)
        print("You can download chardet from https://pypi.python.org/pypi/chardet", file=sys.stderr)
        print("Defaulting as " + default, file=sys.stderr)
        file_encoding.append(default)
        return True
        
    ##--Read through up to the number specified in 'max_passwords' to identify the character encoding    
    try:
        cur_count = 0
        with open(training_file, 'rb') as file:
            for line in file.readlines():
                detector.feed(line)
                if detector.done: 
                    break
                cur_count = cur_count + 1
                if cur_count >= max_passwords:
                    break
            detector.close()
    except IOError as error:
        print ("Error opening file " + training_file)
        print ("Error is " + str(error))
        return False
        
    try:
        file_encoding.append(detector.result['encoding'])
        print("File Encoding Detected: " + str(detector.result['encoding']), file=sys.stderr)
        print("Confidence for file encoding: " + str(detector.result['confidence']), file=sys.stderr)
        print("If you think another file encoding might have been used please manually specify the file encoding and run the training program again", file=sys.stderr)
        print()
    except KeyError as error:
        print("Error encountered with file encoding autodetection", file=sys.stderr)
        print("Error : " + str(error))
        return False

    return True            