#!/usr/bin/env python3
'''
parse .aln file - output from cap3 program. Output is fasta file and
profile file
'''
import argparse
import re


def parse_args():
    '''Argument parsin'''
    description = """
    parsing cap3 assembly aln output
    """

    parser = argparse.ArgumentParser(
        description=description,
        formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument('-a',
                        '--aln_file',
                        default=None,
                        required=True,
                        help="Aln file input",
                        type=str,
                        action='store')
    parser.add_argument('-f',
                        '--fasta',
                        default=None,
                        required=True,
                        help="fasta output file name",
                        type=str,
                        action='store')
    parser.add_argument('-p',
                        '--profile',
                        default=None,
                        required=True,
                        help="output file for coverage profile",
                        type=str,
                        action="store")
    return parser.parse_args()


def get_header(f):
    aln_header = "    .    :    .    :    .    :    .    :    .    :    .    :"
    contig_lead = "******************"
    aln_start = -1
    while True:
        line = f.readline()
        if not line:
            return None, None
        if line[0:18] == contig_lead:
            line2 = f.readline()
        else:
            continue
        if aln_header in line2:
            aln_start = line2.index(aln_header)
            break
    contig_name = line.split()[1] + line.split()[2]
    return contig_name, aln_start


def segment_start(f):
    pos = f.tell()
    line = f.readline()
    # detect next contig or end of file
    if "********" in line or line == "" or "Number of segment pairs = " in line:
        segment = False
    else:
        segment = True
    f.seek(pos)
    return segment


def get_segment(f, seq_start):
    if not segment_start(f):
        return None, None
    aln = []
    while True:
        line = f.readline()
        if ".    :    .    :" in line:
            continue
        if "__________" in line:
            consensus = f.readline().rstrip('\n')[seq_start:]
            f.readline()  # empty line
            break
        else:
            aln.append(line.rstrip('\n')[seq_start:])
    return aln, consensus


def aln2coverage(aln):
    coverage = [0] * len(aln[0])
    for a in aln:
        for i, c in enumerate(a):
            if c not in " -":
                coverage[i] += 1
    return coverage


def read_contig(f, seq_start):
    contig = ""
    coverage = []
    while True:
        aln, consensus = get_segment(f, seq_start)
        if aln:
            contig += consensus
            coverage += aln2coverage(aln)
        else:
            break
    return contig, coverage

def remove_gaps(consensus, coverage):
    if "-" not in consensus:
        return consensus, coverage
    new_coverage = [cov for cons, cov in zip(consensus, coverage)
                    if cons != "-"]
    new_consensus = consensus.replace("-", "")
    return new_consensus, new_coverage

def main():
    args = parse_args()
    with open(args.aln_file, 'r') as f1, open(args.fasta, 'w') as ffasta, open(args.profile, 'w') as fprofile:
        while True:
            contig_name, seq_start = get_header(f1)
            if contig_name:
                consensus, coverage = remove_gaps(*read_contig(f1, seq_start))
                ffasta.write(">{}\n".format(contig_name))
                ffasta.write("{}\n".format(consensus))
                fprofile.write(">{}\n".format(contig_name))
                fprofile.write("{}\n".format(" ".join([str(i) for i in coverage])))
            else:
                break


if __name__ == "__main__":

    main()
