#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 50

// Usually best to go with a multiple of 2
#define N_THREADS 32 

// No. of blocks = ceil(N / N_THREADS)
// so we have atleast as many threads as no. of elements
#define N_BLOCKS (int)ceil((double)N / N_THREADS)

// Performs some simple math operations in parallel
__global__ void gpu_basicmath(float *vec_a, float *vec_b, float *vec_res)
{
        int t_id = threadIdx.x + (blockDim.x * blockIdx.x);
        //printf("Block=%d\tThread=%d\tTID=%d\n", blockIdx.x, threadIdx.x, t_id);

        // Each thread handles one cell of the vector
        vec_res[t_id] = vec_a[t_id] + vec_b[t_id];
}

// Initialize N elements of vec to random numbers
__host__ void init_vec(float *vec)
{
        srand(time(NULL));
        for (int i=0; i<N; ++i)
                vec[i] = rand() % 100;
}

// Print all contents of vec (upto element N)
__host__ void print_vec(float *vec)
{
        for (int i=0; i<N; ++i)
                printf("Vec[%d]=%f\n", i, vec[i]);
}

int main()
{
        float
                *vec_a,
                *vec_b,
                *vec_res;

        cudaMallocManaged(&vec_a, N*sizeof(float));
        cudaMallocManaged(&vec_b, N*sizeof(float));
        cudaMallocManaged(&vec_res, N*sizeof(float));
        cudaMemset(vec_res, 0.0, N*sizeof(float));
        
        init_vec(vec_a);
        init_vec(vec_b);
        
        printf("Vector A:\n");
        print_vec(vec_a);
        printf("Vector B:\n");
        print_vec(vec_b);

        printf("No. of Threads: %d\n", N_THREADS);
        printf("No. of Blocks:  %d\n", N_BLOCKS);
        gpu_basicmath<<<N_BLOCKS, N_THREADS>>>(vec_a, vec_b, vec_res);
        
        cudaDeviceSynchronize();
        
        printf("Result:\n");
        print_vec(vec_res);

        cudaFree(vec_a);
        cudaFree(vec_b);
        cudaFree(vec_res);
        return 0;
}
