#!/usr/bin/env python3
'''
Helper script to create DANTE database which can be used in second iteration
'''
import sys

fasta_input = sys.argv[1]
db_fasta_output_file = sys.argv[2]
db_classification_file = sys.argv[3]
classification_table = set()
# fasta header will be reformatted to correct REXdb classification
with open(fasta_input, 'r') as f, open(db_fasta_output_file, 'w') as out:
    for line in f:
        if line[0] == ">":
            ## modify header
            name, domain, classification = line.split(" ")
            name_clean=name[1:].replace("-","_")
            new_header = ">NA-{}__{}\n".format(domain, name_clean)
            classification_string = "\t".join(classification.split("|"))
            classification_table.add("{}\t{}".format(name_clean, classification_string))
            out.write(new_header)
        else:
            out.write(line)
with open(db_classification_file, 'w') as f:
    f.writelines(classification_table)
