import sys, subprocess
from random import randint

# usage:
# 1. Modify the code below to generate the tests you want to use
# 2. Compile the 2 solutions to compare (e.g. A.cpp B.cpp into A B)
# 3. run: python3 generador.py A B
# Note that 'generador.py', 'A' and 'B' must be in the SAME FOLDER.
# Note that A and B must READ FROM STANDARD INPUT, not from file,
#	careful with the usual freopen("input.in", "r", stdin) in them

ntests = 100 # change as wanted
sol1 = sys.argv[1]
sol2 = sys.argv[2]
for curtest in range(ntests):
	test_case = ""
	# STARTS test creation (change according to problem)
	# example of trivial "a+b" problem
	a = randint(1,100)
	b = randint(1,100)
	test_case += f"{a} {b}\n"
	# ENDS test creation

	# Here the test is executed and outputs are compared
	print("running... ", end='')
	ans1 = subprocess.check_output(f"./{sol1}",
		input=test_case.encode('utf-8')).decode('utf-8')
	ans2 = subprocess.check_output(f"./{sol2}",
		input=test_case.encode('utf-8')).decode('utf-8')
	if ans1 == ans2:
		print("OK")
	else:
		print("FAILED!")
		print(test_case)
		print(f"ans from {sol1}:\n{ans1}")
		print(f"ans from {sol2}:\n{ans2}")
		break
