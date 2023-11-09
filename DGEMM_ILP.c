// Double precision GEneral Matrix Multiply with AVX optimization and Loop unrolling
#include <x86intrin.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N (int)8e3 // 2e3 já fica bastante tempo
#define UNROLL (4)

double A[N * N], B[N * N], C[N * N];

void dgemm(int n, double* A, double* B, double* C){
	for (int i = 0; i < n; i += UNROLL * 8)
		for (int j = 0; j < n; ++j){
			__m512d c[UNROLL];
			for (int r = 0; r < UNROLL; r++)
				c[r] = _mm512_load_pd(C + i + r * 8 + j * n); //[ UNROLL];

			for (int k = 0; k < n; k++){
				__m512d bb = _mm512_load_pd(_mm_load_sd(B + j * n + k));
				for (int r = 0; r < UNROLL; r++)
					c[r] = _mm512_fmadd_pd(_mm512_load_pd(A + n * k + r * 8 + i), bb, c[r]);
			}

			for (int r = 0; r < UNROLL; r++)
				_mm512_store_pd(C + i + r * 8 + j * n, c[r]);
		}
}


void make_rand_matrix(size_t n, double* A, double* B){
	srand(clock());
	for (size_t i = 0; i < n * n; i++){
		A[i] = rand();
		B[i] = rand();
	}
}

int main(int argc, char* argv[]){

	size_t n = atoi(argv[1]);

	make_rand_matrix(n, A, B);

	time_t start = clock();
	dgemm(n, A, B, C);
	time_t stop = clock();

	printf("Total time = %ldms\n", stop - start);
	fflush(stdout);
	// for(int i = 0; i < 100; i++) printf("%lf ", C[i]);

	return 0;
}
  git config --global user.email "you@example.com"
  git config --global user.name "Your Name"