#!/bin/bash

export DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
export TEXT_DATA="$DIR/test-data"
export classification_tbl=${DIR}/tool-data/protein_domains/Viridiplantae_v3.0_class
export pdb=${DIR}/tool-data/protein_domains/Viridiplantae_v3.0_pdb

# make sure  dir for testing exists
mkdir -p $DIR/tmp

######## DANTE
## single_seq, for/rev strand of mapping
$DIR/dante.py -q ${TEXT_DATA}/GEPY_test_long_1 -pdb $pdb -cs $classification_tbl \
              --domain_gff $PWD/tmp/single_fasta.gff3
## multifasta
$DIR/dante.py -q ${TEXT_DATA}/vyber-Ty1_01.fasta -pdb $pdb -cs $classification_tbl \
              --domain_gff $PWD/tmp/multifasta.gff3
## multifasta_win
$DIR/dante.py -q ${TEXT_DATA}/vyber-Ty1_01.fasta -pdb $pdb -cs $classification_tbl \
              -wd 3100 -od 1500 --domain_gff $PWD/tmp/multifasta_win.gff3

# test filtering
$DIR/dante_gff_output_filtering.py --dom_gff $PWD/tmp/single_fasta.gff3 \
                                   --domains_filtered $PWD/tmp/single_fasta_filtered.gff3 \

