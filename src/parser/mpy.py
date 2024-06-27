
# Read list of domain names from file and write to list of output file depends on the length of the domain

# with open('generic.txt') as old:
# 	for line in old:
# 		line.strip()
# 		mlength = len(line)-1
# 		with open('generic-'+str(mlength)+'.txt', 'a') as new:
# 			new.write(line)

# Remove duplicate line from file
lines_seen = set() # holds lines already seen
outfilename = "unit_tests/valid_host.txt"
infilename = "unit_tests/all_log.log"
outfile = open(outfilename, "w")
for line in open(infilename, "r"):
    if line not in lines_seen: # not a duplicate
        outfile.write(line)
        lines_seen.add(line)
outfile.close()