# usage: (note that test_generator.py refers to this file)
# 1. Modify the code below to generate the tests you want to use
# 2. Compile the 2 solutions to compare (e.g. A.cpp B.cpp into A B)
# 3. run: python3 test_generator.py A B
# Note that 'test_generator.py', 'A' and 'B' must be in the SAME FOLDER
# Note that A and B must READ FROM STANDARD INPUT, not from file,
#	be careful with the usual freopen("input.in", "r", stdin) in them
import sys, subprocess
from datetime import datetime
from random import randint, seed

def buildTestCase(): # example of trivial "a+b" problem
	a = randint(1,100)
	b = randint(1,100)
	return f"{a} {b}\n"

seed(datetime.now().timestamp())
ntests = 100 # change as wanted
sol1 = sys.argv[1]
sol2 = sys.argv[2]
# Sometimes it's a good idea to use extra arguments that could then be
# passed to 'buildTestCase' and help you "shape" your tests
for curtest in range(ntests):
	test_case = buildTestCase()
	# Here the test is executed and outputs are compared
	print("running... ", end='')
	ans1 = subprocess.check_output(f"./{sol1}",
		input=test_case.encode('utf-8')).decode('utf-8')
	ans2 = subprocess.check_output(f"./{sol2}",
		input=test_case.encode('utf-8')).decode('utf-8')
	if ans1 == ans2:
		assert ans1 != "", 'ERROR?? ans1 = ans2 = empty string ("")'
		print("OK")
	else:
		print("FAILED!")
		print(test_case)
		print(f"ans from {sol1}:\n{ans1}")
		print(f"ans from {sol2}:\n{ans2}")
		break
