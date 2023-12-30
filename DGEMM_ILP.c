// Double precision GEneral Matrix Multiply with AVX optimization and Loop unrolling
#include <x86intrin.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N (int)8e3 // 2e3 já fica bastante tempo
#define UNROLL (4) //tamanho do UNROLL

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

void dgemm(size_t n, double* A, double* B, double* C){ //A * B^T = C^T
	for (size_t i = 0; i < n; i++)
		for (size_t j = 0; j < n; j += 4 * UNROLL){
			__m256d c[UNROLL];
			for (int r = 0; r < UNROLL; r++)
				c[r] = _mm256_load_pd(C + (i * N) + j + r * 4);

			for (size_t k = 0; k < n; k++){
				__m256d bb = _mm256_broadcast_sd(A + (i * N) + k);
				for (int r = 0; r < UNROLL; r++){
					c[r] = _mm256_add_pd(c[r], _mm256_mul_pd(bb, _mm256_load_pd(B + (N * k) + j + 4 * r)));
				}
			}
			for (int r = 0; r < UNROLL; r++)
				_mm256_store_pd(C + (i * N) + j + r * 4, c[r]);
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
	// size_t n = 6;

	make_rand_matrix(n, A);
	make_rand_matrix(n, B);

	for (int i = 0; i < n * n; i++) A[i / n][i % n] = i + 1;
	for (int i = 0; i < n * n; i++) B[i / n][i % n] = n * n - i;

	time_t start = clock();
	dgemm(n, A, B, C);
	time_t stop = clock();

	printf("Total time = %lldms\n", (stop - start) * 1000 / CLOCKS_PER_SEC);
	fflush(stdout);

	// printf("A =\n");
	// print_matrix(n, A);
	// printf("B =\n");
	// print_matrix(n, B);
	printf("C =\n");
	print_matrix(n, C);

	return 0;
}
