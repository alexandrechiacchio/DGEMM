// Double precision GEneral Matrix Multiply with AVX optimization and Loop unrolling
#include <x86intrin.h>
#include <immintrin.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE (int)8e3
#define UNROLL (4) //tamanho do UNROLL
#define BLOCKSIZE 32

double A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];

void print_matrix(size_t n, double* A){
  for (size_t i = 0; i < n; i++){
    for (size_t j = 0; j < n; j++){
      printf("%8.2lf ", A[(i * SIZE) + j]);
    }
    printf("\n");
  }
  printf("\n");
}

void do_block(int n, int si, int sj, int sk, double* A, double* B, double* C){
  for (int i = si; i < si + BLOCKSIZE; i++)
    for (int j = sj; j < sj + BLOCKSIZE; j += 4 * UNROLL) {
      __m256d c[UNROLL];
      for (int r = 0; r < UNROLL; r++)
        c[r] = _mm256_load_pd(C + (i * SIZE) + j + r * 4); //[ UNROLL];

      for (int k = sk; k < sk + BLOCKSIZE; k++)
      {
        __m256d bb = _mm256_broadcast_sd(A + (i * SIZE) + k);
        for (int r = 0; r < UNROLL; r++)
          c[r] = _mm256_add_pd(c[r], _mm256_mul_pd(bb, _mm256_load_pd(B + (SIZE * k) + j + 4 * r)));
      }
      for (int r = 0; r < UNROLL; r++)
        _mm256_store_pd(C + (i * SIZE) + j + r * 4, c[r]);
    }
}

void dgemm(int n, double* A, double* B, double* C){
  for (int si = 0; si < n; si += BLOCKSIZE)
    for (int sj = 0; sj < n; sj += BLOCKSIZE)
      for (int sk = 0; sk < n; sk += BLOCKSIZE)
        do_block(n, si, sj, sk, A, B, C);
}

int main(int argc, char* argv[]){

  size_t n = atoi(argv[1]);


  for (size_t i = 0; i < n * n; i++) A[i / n][i % n] = i + 1;
  for (size_t i = 0; i < n * n; i++) B[i / n][i % n] = n * n - i;


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
