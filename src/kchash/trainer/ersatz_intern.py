#!/usr/bin/env python3

#############################################################################
# Used to evaluate the effectiveness of a multi-word tokenizer
# --Utilizes several shortcuts to estimate false positive and false negative
#   rates, so the results should be treated sceptically. Ideally you would
#   have a person manually tokenize the test set, but that takes time
#   and is boring. Hence the name of this tool, Ersatz Intern.
#
#  The MIT License (MIT)
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included in all
#  copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#  SOFTWARE.
#
#
#  Contact Info: cweir@vt.edu
#############################################################################


##--Including this to print error message if python < 3.0 is used
from __future__ import print_function
import sys
###--Check for python3 and error out if not--##
if sys.version_info[0] < 3:
    print("This program requires Python 3.x", file=sys.stderr)
    sys.exit(1)
    
import argparse
import os  ##--Used for file path information

#Custom modules
from markov_trainer.common_file_io import detect_file_encoding
from markov_trainer.trainer_file_io import TrainerFileIO

##--Global varialbe to specify what seperators to use for tokens
##--When adding them manually, will use the first item in the list
token_seperator = [' ']


####################################################
# Parses the command line
####################################################
def parse_command_line(runtime_options):
    parser = argparse.ArgumentParser(description='Ersatz Intern: Used to evaluate the effectiveness of multiword tokenizers')
    
    ##Input File options
    group = parser.add_argument_group('Input Files')
    group.add_argument('--wordlist', '-w', help='The generated multiword wordlist, split up by spaces. For example "correct staple"',
        metavar='FILENAME',required=True)
    group.add_argument('--testlist', '-t', help='The golden list to test against, split up by camelcase. For example "correctStaple"',
        metavar='FILENAME',required=True)
    group.add_argument('--encoding','-e', help='File encoding used to read the input training set. If not specified autodetect is used', metavar='ENCODING', required=False)
    
    ##Output file options    
    group = parser.add_argument_group('Output Options')
    # None yet
    
    try:
        args=parser.parse_args()
        
        ##Input File options
        runtime_options['wordlist'] = args.wordlist
        runtime_options['testlist'] = args.testlist
        runtime_options['encoding'] = args.encoding
        
        ##Output file options
        #None
        
        ##Markov grammar options
        #None
        
    except Exception as msg:
        print(msg, file=sys.stderr)
        return False
    except SystemExit:
        return False

    return True 

    
###################################################################################
# Prints the start-up banner when this tool is run
###################################################################################
def print_banner(program_details):
    print('',file=sys.stderr)
    print (program_details['program'], file=sys.stderr)
    print ("Version " + program_details['version'], file=sys.stderr)
    print ("Written by " + program_details['author'], file=sys.stderr)
    print ("Sourcecode available at " + program_details['source'], file=sys.stderr)
    print('',file=sys.stderr)  


####################################################################################
# ASCII art for displaying an error state before quitting
####################################################################################
def print_error():
    print('',file=sys.stderr)
    print('An error occured, shutting down',file=sys.stderr)
    print('',file=sys.stderr)
    print(r' \__/      \__/      \__/      \__/      \__/      \__/          \__/',file=sys.stderr)
    print(r' (oo)      (o-)      (@@)      (xx)      (--)      (  )          (OO)',file=sys.stderr)
    print(r'//||\\    //||\\    //||\\    //||\\    //||\\    //||\\        //||\\',file=sys.stderr)
    print(r'  bug      bug       bug/w     dead      bug       blind      bug after',file=sys.stderr)
    print(r'         winking   hangover    bug     sleeping    bug     whatever you did',file=sys.stderr)
    print('',file=sys.stderr)

    
###################################################################################
# ASCII art for more generic failure
###################################################################################
def ascii_fail():
    print("                                          __ ",file=sys.stderr)
    print("                                      _  |  |",file=sys.stderr)
    print("                  Yye                |_| |--|",file=sys.stderr)
    print("               .---.  e           AA | | |  |",file=sys.stderr)
    print("              /.--./\  e        A",file=sys.stderr)
    print("             // || \/\  e      ",file=sys.stderr)
    print("            //|/|| |\/\   aa a    |\o/ o/--",file=sys.stderr)
    print("           ///|\|| | \/\ .       ~o \.'\.o'",file=sys.stderr)
    print("          //|\|/|| | |\/\ .      /.` \o'",file=sys.stderr)
    print("         //\|/|\|| | | \/\ ( (  . \o'",file=sys.stderr)
    print("___ __ _//|/|\|/|| | | |\/`--' '",file=sys.stderr)
    print("__/__/__//|\|/|\|| | | | `--'",file=sys.stderr)
    print("|\|/|\|/|\|/|\|/|| | | | |",file=sys.stderr)
    print("",file=sys.stderr)
    
    
####################################################################################
# Splits passwords up based on CamelCase and returns tokens lowercased and seperated by a space
# --For example: catDogHorse would be returned as "cat dog horse" 
# --Added logic to deal with capitalize words, aka theHORSE to be 'the horse
####################################################################################
def detect_camelcase(input_pw):
    
    ##--quick sanity bail out if the string is empty
    if not input_pw:
        return 
    
    ##--tells if there is a run going on
    ##--start as true so we don't split on the first character
    current_run = True
    
    ##--Initialize the results. 
    final_pw = []
    
    ##--Walk through the string and add spaces if character is uppercase
    for c in input_pw:
        if c.isupper():
            ##--If it is an uppercase run, don't split, continue the run
            if current_run:
                final_pw.append(c.lower())
            ##--Else start an uppercase run, split the word
            else:
                current_run = True
                final_pw.append(token_seperator[0] + c.lower())
        else:
            ##--If this is a token seperator, start a run so we don't have two spaces if we split on next character
            if c in token_seperator:
                current_run = True
            
            else:
                ##--No longer a run
                current_run = False
            
            ##--Save the lowercase character
            final_pw.append(c.lower())
    
    return ''.join(final_pw)
    
####################################################################################
# Splits passwords up based on digits and returns tokens lowercased and seperated by a space
# --For example: cat11dog would be returned as "cat 11 dog" 
####################################################################################
def detect_digits(input_pw):
    
    ##--quick sanity bail out if the string is empty
    if not input_pw:
        return 
    
    ##--tells if there is a current run going on. Start as true so we don't split if the
    ##--first character is a digit
    current_run = True
    
    ##--Initialize the results. Don't split on the first character...    
    final_pw = []
       
    ##--Walk through the rest of the string and add spaces if character is uppercase
    for c in input_pw:
        if c.isdigit():
            ##--If it is a ongoing run, don't split, continue the run
            if current_run:
                final_pw.append(c.lower())
            ##--Else start an run, split the word
            else:
                current_run = True
                final_pw.append(token_seperator[0] + c.lower())
        else:
            ##--If this is a token seperator, start a run so we don't have two spaces if we split on next character
            if c in token_seperator:
                current_run = True
            
            else:
                ##--No longer a run
                current_run = False
            
            ##--Save the lowercase character
            final_pw.append(c.lower())
    
    return ''.join(final_pw)
    
    
##################################################################
# Main function
##################################################################
def main():
    
    management_vars = {
        ##--Information about this program--##
        'program_details':{
            'program':'Ersatz Intern wordlist tokenizer evaluator',
            'version': '0.1',
            'author':'Matt Weir',
            'contact':'cweir@vt.edu',
            'source':'Upon Request'
        },
        ##--Runtime specific values, can be overridden via command line options
        'runtime_options':{
            ##input file options
            'wordlist':None,
            'traininlist':None,
            'encoding':None,
            
            ##Output options
            # None yet
        }
    }  
    
    ##--Print out banner
    print_banner(management_vars['program_details'])
    
    ##--Parse the command line ---##
    command_line_results = management_vars['runtime_options']
    if parse_command_line(command_line_results) != True:
        return
    
    ##--Set the file encoding for the training set
    ##--If NOT specified on the command line by the user run an autodetect
    if command_line_results['encoding'] == None:
        possible_file_encodings = []
        
        ##--Assume the wordlist and testlist have the same encoding
        if not detect_file_encoding(command_line_results['wordlist'], possible_file_encodings):
            ascii_fail()
            print("Exiting...")
            return
            
        command_line_results['encoding'] = possible_file_encodings[0]
        
    ######################################    
    ##--Read in and parse the test list
    ######################################
    try:
        test_list = TrainerFileIO(command_line_results['testlist'], command_line_results['encoding'])
    except Exception as msg:
        print (error,file=sys.stderr)
        print ("Error reading file " + command_line_results['testlist'] ,file=sys.stderr)
        ascii_fail()
        print("Exiting...")
        return
        
    gold_pw = test_list.read_password()
    total_gold_count = 0
    test_dataset = {}
    while gold_pw != None:
        camelcase_pw = detect_camelcase(gold_pw)
        digit_pw = detect_digits(camelcase_pw)
        
        ##--I plan to add other pre-processors at a later time
        final_pw = digit_pw
        
        ######################################
        ##--Save the results to a dictionary
        ######################################
        
        ##--if the string has been seen before
        if final_pw in test_dataset:
            test_dataset[final_pw]['count'] += 1
            ##--Update the raw password count
            if gold_pw in test_dataset[final_pw]['raw_pw']:
                test_dataset[final_pw]['raw_pw'][gold_pw] += 1
            else:
                test_dataset[final_pw]['raw_pw'][gold_pw] = 1
            
        else:
            test_dataset[final_pw] = {
                'count' : 1,
                'raw_pw' : {gold_pw:1},
                'found' : False
            }
        
        total_gold_count +=1
        gold_pw = test_list.read_password()
        
    
    ###############################################    
    ##--Read in and parse the generated wordlist
    ################################################
    ######################################    
    ##--Read in and parse the test list
    ######################################
    try:
        word_list = TrainerFileIO(command_line_results['wordlist'], command_line_results['encoding'])
    except Exception as msg:
        print (error,file=sys.stderr)
        print ("Error reading file " + command_line_results['wordlist'] ,file=sys.stderr)
        ascii_fail()
        print("Exiting...")
        return
        
    input_pw = word_list.read_password()
    total_input_count = 0
    found_password_count = 0
    
    ##--Check the results for each generated password in the wordlist
    while input_pw != None:
         
        if input_pw in test_dataset:
            ##--Gotta check if the password has been found or not. Only increment found for unfound passwords
            if not test_dataset[input_pw]['found']:
                found_password_count += test_dataset[input_pw]['count']
                test_dataset[input_pw]['found'] = True
                
        total_input_count +=1
        input_pw = word_list.read_password()
    
    print()
    print("------------------------------------------------------------")
    print("--     Not Found                                          --")
    print("------------------------------------------------------------")
    
    for key, value in test_dataset.items():
        if not value['found']:
            print(key + " : <RAW> " + str(value['raw_pw']))
    
    print()
    print("------------------------------------------------------------")
    print("--     Results                                            --")
    print("------------------------------------------------------------")
    print("Total passwords in test set: " + str(total_gold_count))    
    print("Found Passwords:             " + str(found_password_count))
    print("Not Found Passwords:         " + str(total_gold_count - found_password_count))
    print("Percentage Found:            " + str(found_password_count/ total_gold_count))
    
        
#######################################################################
# Standard python stub to call main
#######################################################################  
if __name__ == "__main__":
    main()
