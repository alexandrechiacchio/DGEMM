import sys, time

size = int(sys.argv[1])
# size = 4

a = []
b = []
c = [[0 for _ in range(size)] for _ in range(size)]


def dgemm(a, b, c):
  for i in range(size):
    for j in range(size):
      for k in range(size):
        c[i][j] += a[i][k]*b[k][j]

def main():

  for i in range(size):
    line = []
    for j in range(size):
      line.append(i*size + j + 1)
    a.append(line)

  for i in reversed(a):
    b.append(list(reversed(i)))



  start,stop = 0, 0
  start = time.time()
  dgemm(a, b, c)
  stop = time.time()

  print("Total time = %fms" % ((stop - start)*1000))
  # print(a)
  # print(b)
  # print(c)

main()