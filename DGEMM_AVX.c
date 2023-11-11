// Double precision GEneral Matrix Multiply with AVX optimization
#include <x86intrin.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N (int)8e3 // 2e3 já fica bastante tempo


double A[N][N], B[N][N], C[N][N];

void print_matrix(size_t n, double* A){
	for (size_t i = 0; i < n; i++){
		for (size_t j = 0; j < n; j++){
			printf("%lf ", A[(i * N) + j]);
		}
		printf("\n");
	}
	printf("\n");
}

void dgemm(size_t n, double* A, double* B, double* C){ //A * B^T = C^T
	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < n; j += 4){
			print_matrix(n, C);
			__m256d c0 = _mm256_load_pd(C + (i * N) + j); /* c0 = C[i][j] */
			for (size_t k = 0; k < n; k++)
				c0 = _mm256_add_pd(c0, _mm256_mul_pd(_mm256_broadcast_sd(A + (i * N) + k), _mm256_load_pd(B + (N * k) + j)));
			_mm256_store_pd(C + (i * N) + j, c0); /* C[i][j] = c0 */
		}
}

void make_rand_matrix(size_t n, double* A, double* B, double* C){
	srand(clock());
	for (size_t i = 0; i < n * n; i++){
		A[i] = rand();
		B[i] = rand();
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

	// printf("A =\n");
	// print_matrix(n, A);
	// printf("B =\n");
	// print_matrix(n, B);
	// printf("C =\n");
	// print_matrix(n, C);

	return 0;
}