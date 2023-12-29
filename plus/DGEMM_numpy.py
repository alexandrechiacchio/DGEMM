import sys, time
import numpy as np

size = int(sys.argv[1])
# size = 4

a = np.array([[i*size + j + 1 for j in range(size)] for i in range(size)], dtype='float64')
b = np.array([list(reversed(i)) for i in reversed(a)], dtype='float64')
c = np.zeros((size, size), dtype='float64')


def main():

  start,stop = 0, 0
  start = time.time()
  c = a@b
  stop = time.time()

  print("Total time = %fms" % ((stop - start)*1000))
  # print(a)
  # print(b)
  # print(c)

main()