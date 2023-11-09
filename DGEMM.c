// Double precision GEneral Matrix Multiply

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N (int)8e3 // 2e3 já fica bastante tempo


double A[N * N], B[N * N], C[N * N];

void dgemm(size_t n, double* A, double* B, double* C){
	for (size_t i = 0; i < n; ++i){
		for (size_t j = 0; j < n; ++j){
			double cij = C[i + j * n]; // cij = C[i][j]
			for (size_t k = 0; k < n; k++)
				cij += A[i + k * n] * B[k + j * n]; // cij += A[i][j]*B[k][j]
			C[i + j * n] = cij; // C[i][j] = cij
		}
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