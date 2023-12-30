import subprocess
import sys
import re
import numpy as np

matrix_test_sizes = [256, 1000, 2000, 4000, 8000]
optimization_levels = ["-O3"]

means = dict(list(map(lambda x: (x, []), optimization_levels)))
# with open("output.txt", 'w+') as sys.stdout:
for i in optimization_levels:
	print("making", i)
	subprocess.run(["gcc", "-mavx", "./DGEMM_ILP.c", i, "-w"])
	for j in matrix_test_sizes:
		runtimes = []
		print("running", j)
		for k in range(10):
			output = subprocess.run(["./a", str(j)], capture_output=True, encoding="utf-8")
			# print(output.stdout, end='')
			runtimes.append(int(re.findall(r'\d+', output.stdout)[0]))
			sys.stdout.flush()
		print(i, j, runtimes)
		runtimes = np.array(runtimes)
		means[i].append(np.mean(runtimes))
		print(np.mean(runtimes), np.std(runtimes))
print(means)