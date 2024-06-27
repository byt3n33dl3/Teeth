#############################################################################
# Contains OMEN specific file IO functions to read from the training file
#############################################################################

import sys
import os
import errno
import codecs

#####################################################################################
# Making this a class so it can return one password at a time from the training file
#####################################################################################
class TrainerFileIO:
    #####################################################
    # Open the file for reading
    # Passes file exceptions back up if they occuring
    # Aka: if the file doesn't exist
    #####################################################
    def __init__(self, filename, encoding = 'utf-8'):
        
        ##--Using surrogateescape to handle errors so we can detect encoding issues without raising an exception
        ##  during the reading of the original password
        self.encoding = encoding
        self.filename = filename
        self.file = codecs.open(self.filename, 'r', encoding= self.encoding, errors= 'surrogateescape')
        self.num_encoding_errors = 0
        
        
    ######################################################
    # Returns one password from the training set
    #
    # If there are no more passwords returns None
    #######################################################    
    def read_password(self):
        
        ##--Quick sanity check to make sure the file is still open
        if self.file.closed:
            return None
        
        ##--Read an input password from the training set        
        try:
            ##--Loop until we find a valid password
            while True:
                password = self.file.readline()
            
                ##--Check to see if the file is done--##
                if password == "":
                    ##--Close file and return None
                    self.file.close()
                    return None
                    
                ##--Check the encoding of the file
                ##  Re-encode it and detect surrogates, this way we can identify encoding errors
                ##  I know, could simplify by throwing an exception during the original parsing and
                ##  not use surrogate escapes, but this has helped with troubleshooting in the past
                try:
                    password.encode(self.encoding)
                except UnicodeEncodeError as e:
                    if e.reason == 'surrogates not allowed':
                        self.num_encoding_errors += 1
                    else:
                        print("Hmm, there was a weird problem reading in a line from the training file",file=sys.stderr)
                        print("",file=sys.stderr)
                    continue
                
                ##--Return the password minus the trailing newline
                ##--Can't use lstrip
                return password.rstrip('\n\r')
        
        ##--File errors *shouldn't* happen but if they do raise them to make sure they don't silently halt the training
        ##  Aka we want the training to stop and the user to know something went wrong        
        except IOError as error:
            print (error,file=sys.stderr)
            print ("Error reading file " + self.filename ,file=sys.stderr)
            raise
           