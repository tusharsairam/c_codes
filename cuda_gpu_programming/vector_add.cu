#include <cuda_runtime_api.h>
#include <driver_types.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define N 10000000
#define MAX_ERR 1e-6

__global__ void vector_add(float *out, float *a, float *b, int n)
{
	for (int i=0; i<n; ++i) 
		out[i] = a[i] + b[i];
}

int main()
{
	float *a, *b, *out;
	float *d_a, *d_b, *d_out;

	a    = (float*)malloc(sizeof(float) * N);
	cudaMalloc((void**)&d_a, sizeof(float) * N);
	cudaMemcpy(d_a, a, sizeof(float) * N, cudaMemcpyHostToDevice);
	b    = (float*)malloc(sizeof(float) * N);
	cudaMalloc((void**)&d_b, sizeof(float) * N);
	cudaMemcpy(d_b, b, sizeof(float) * N, cudaMemcpyHostToDevice);

	out  = (float*)malloc(sizeof(float) * N);
	cudaMalloc((void**)&d_out, sizeof(float) * N);

	vector_add<<<1,1>>>(d_out, d_a, d_b, N);

	cudaMemcpy(out, d_out, sizeof(float) * N, cudaMemcpyDeviceToHost);

	cudaDeviceSynchronize();

	for (int i=0; i<N; ++i) {
		assert(fabs(out[i] - a[i] - b[i]) < MAX_ERR);
	}

	printf("out[0] = %f\n", out[0]);
	printf("PASSED\n");

	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_out);

	free(a);
	free(b);
	free(out);
}

