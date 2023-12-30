// Double precision GEneral Matrix Multiply

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N (size_t)8e3 // 2e3 já fica bastante tempo


double A[N][N], B[N][N], C[N][N];

void print_matrix(size_t n, double* A){
  for (size_t i = 0; i < n; i++){
    for (size_t j = 0; j < n; j++){
      printf("%8.2lf ", A[(i * N) + j]);
    }
    printf("\n");
  }
  printf("\n");
}

void dgemm(size_t n, double* A, double* B, double* C){
  for (size_t i = 0; i < n; i++){
    for (size_t j = 0; j < n; j++){
      for (size_t k = 0; k < n; k++)
        C[(i * N) + j] += A[(i * N) + k] * B[(k * N) + j];
    }
  }
}

void make_rand_matrix(size_t n, double* A){
  srand(clock());
  for (size_t i = 0; i < n * n; i++){
    A[i] = rand();
  }
}


int main(int argc, char* argv[]){

  size_t n = atoi(argv[1]);

  make_rand_matrix(n, A);
  make_rand_matrix(n, B);

  time_t start = clock();
  dgemm(n, A, B, C);
  time_t stop = clock();

  printf("Total time = %lldms\n", (stop - start) * 1000 / CLOCKS_PER_SEC);
  fflush(stdout);

  // printf("A =\n");
  // print_matrix(n, A);
  // printf("B =\n");
  // print_matrix(n, B);
  // printf("C =\n");
  // print_matrix(n, C);

  return 0;
}