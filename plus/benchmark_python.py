import subprocess
import sys
import re
import numpy as np


matrix_test_sizes = [256, 1000, 2000, 4000, 8000]

# subprocess.run(["gfortran", "DGEMM.f90"])

means = []
for j in matrix_test_sizes:
  runtimes = []
  print("running", j)
  for k in range(10):
    output = subprocess.run(["python", "./DGEMM.py", str(j)], capture_output=True, encoding="utf-8", )
    # print(output.stdout, end='')
    runtimes.append(int(re.findall(r'\d+', output.stdout)[0]))
    sys.stdout.flush()
  print(j, runtimes)
  runtimes = np.array(runtimes)
  means.append(np.mean(runtimes))
  print("média =", np.mean(runtimes), "Desvio padrão =", np.std(runtimes))
print(means)