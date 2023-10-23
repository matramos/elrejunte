import os, sys, subprocess

# This script assumes that every pair of input-output files share the same
# name, except for having a possibly different suffix (like .in and .out)

# 1st param: path to directory with input files
indir = sys.argv[1]
# 2nd param: path to directory with output files
outdir = sys.argv[2]
# 3rd param: compiled solution file name (must be in same folder as this script)
sol = sys.argv[3]
#Optional 4th param: suffix of all input files (e.g. .in)
insuffix = ""
if len(sys.argv) > 4:
	insuffix = sys.argv[4]
#Optional 5th param: suffix of all output files (e.g. .out)
outsuffix = ""
if len(sys.argv) > 5:
	outsuffix = sys.argv[5]
#Optional 6th param: filter tests, to run those that contain a given substring
namecontains = ""
if len(sys.argv) > 6:
	namecontains = sys.argv[6]


for filename in os.listdir(indir):
	if not filename.endswith(insuffix):
		continue
	test_in = ""
	with open(indir + filename, 'r') as fin:
		test_in = fin.read()
	outfile = ""
	if len(insuffix) > 0:
		outfile = outdir + filename[:-len(insuffix)] + outsuffix
	else:
		outfile = outdir + filename + outsuffix
	test_out = ""
	with open(outfile, 'r') as fout:
		test_out = fout.read()

	print(f"running {filename}... ", end='')
	ans = subprocess.check_output(f"./{sol}",
		input=test_in.encode('utf-8')).decode('utf-8')
	if ans == test_out:
		assert ans != "", 'ERROR?? ans = expected = empty string ("")'
		print("OK")
	else:
		# You may want to move things around here to cut on first fail or not
		# to only print some inputs and/or some outputs
		print("FAILED!")
		print(f"ans from {sol}:\n{ans}")
		print(f"expected:\n{test_out}")
		if len(test_in) < 10:
			print(test_in)
			break
