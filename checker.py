#!/usr/bin/env python3
import subprocess
import os
import re
from time import time, sleep

def system_r(cmd):
	p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
	return p.stdout.read()

def system_t(cmd, t):
	print(f"(No body should die): {cmd} for {t}s")
	p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
	start = int(time())
	while int(time()) - start < t:
		if p.poll() is not None:
			print("Test failed")
			return
		sleep(1)
	print("Test passed")
	os.system("kill " + str(p.pid))

def save_test(txt, n):
	with open("tests_checker/test_"+str(n), "w") as f:
		f.write(txt)

s_check = 5

PATH = "philo"
BIN = f"{PATH}/{PATH}"

if __name__ == '__main__':
	if not os.path.exists(BIN) or input("Recompile? (y/n)").lower() == 'y':
		os.system(f"make re -C {PATH}/")
	if not os.path.exists(BIN):
		print(f"Error: {BIN} binary not found")
	
	if not os.path.exists("tests_checker/"):
		os.mkdir("tests_checker")
	#Test 1
	print("Test 1: The philosopher should not eat and should die!")
	res = system_r(f"{BIN} 1 800 200 200").decode()
	if res.find("eating") == -1 and res.find("died") != -1:
		print("Test passed")
	else:
		print("Test failed")
	save_test(res, 1)
	
	#Test 2 No body should die
	print("Test 2: ", end='')
	res = system_t(f"{BIN} 5 800 200 200 > tests_checker/test_2", s_check)

	#Test 3 
	print("Test 3: no one should die and the simulation should stop when all the philosopher has eaten at least 7 times each.")
	res = system_r(f"{BIN} 5 800 200 200 7").decode()
	for i in range(1, 6):
		x = [m.start() for m in re.finditer(str(i)+" is eating", res)]
		if len(x) != 7:
			print("Test failed")
			break
	else:
		print("Test passed")
	save_test(res, 3)

	#Test 4 No body should die
	print("Test 4: ", end='')
	res = system_t(f"{BIN} 4 410 200 200  > tests_checker/test_4", s_check)

	#Test 5
	print("Test 5: A philosopher should die")
	res = system_r(f"{BIN} 4 310 200 100").decode()
	if len([m.start() for m in re.finditer("died", res)]) == 1:
		print("Test passed")
	else:
		print("Test failed")
	save_test(res, 5)
	
	#test1 = system_r("philo/philo 1 800 200 200")
	#test2 = system_r("philo/philo 4 310 200 100")
