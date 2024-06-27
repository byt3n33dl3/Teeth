# Correct Staple Research Tools

This directory contains a collection of tools to perform research into creating better multiword tokenization tools

## General Disclaimer

The tools here are not optimized for password cracking sessions. Furthermore they have not been rigourously tested and may employ shortucts so care should be taken when evaluating their results. 

## Tool List

### ersatz_intern.py

Requirements:\
Python3\
chardet https://github.com/chardet/chardet

Description:\
This is a very basic tool to evaluate the effectiveness of a multiword tokenization tool. It requires a formatted "test list" to compare against, and will return the percentage of correct parsings matched, along with the parsed tokens not created.

Usage:\
python3 ersatz_intern.py --wordlist FILENAME --testlist FILENAME 

Args:\
--wordlist: The generated tokenized wordlist. Individual parsed tokenizations should be seperated by spaces, with multiple versions of tokens seperated by newlines. Consider the original word catdograbbit. The tokenized version should be passed as "cat dog rabbit".

--testlist: The golden list to test against. The "correct" answers should be seperated by spaces or camelcasing. For example "catDogRabbit" or "cat dog rabbit"






