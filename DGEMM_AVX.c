// Double precision GEneral Matrix Multiply with AVX optimization
#include <x86intrin.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N (int)8e3 // 2e3 já fica bastante tempo


double A[N * N], B[N * N], C[N * N];

void dgemm(size_t n, double* A, double* B, double* C){
	for (size_t i = 0; i < n; i += 4)
		for (size_t j = 0; j < n; j++){
			__m256d c0 = _mm256_load_pd(C + i + j * n); /* c0 = C[i][j] */
			for (size_t k = 0; k < n; k++)
				c0 = _mm256_add_pd(c0, /* c0 += A[i][k]*B[k][j] */
					_mm256_mul_pd(_mm256_load_pd(A + i + k * n),
						_mm256_broadcast_sd(B + k + j * n)));
			_mm256_store_pd(C + i + j * n, c0); /* C[i][j] = c0 */
		}
}


void make_rand_matrix(size_t n, double* A, double* B, double* C){
	srand(clock());
	for (size_t i = 0; i < n * n; i++){
		A[i] = rand();
		B[i] = rand();
		C[i] = rand();
	}
}

int main(int argc, char* argv[]){

	size_t n = atoi(argv[1]);

	make_rand_matrix(n, A, B, C);

	time_t start = clock();
	dgemm(n, A, B, C);
	time_t stop = clock();

	printf("Total time = %ldms\n", (stop - start) * 1000 / CLOCKS_PER_SEC);
	fflush(stdout);
	// for(int i = 0; i < 100; i++) printf("%lf ", C[i]);

	return 0;
}