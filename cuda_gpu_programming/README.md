`gpu_basicmath.cu`

Sources:
* https://www.youtube.com/watch?v=JKHmXbCH7vE - Daniel Hirsch made an excellent video on writing CUDA C code. The differences in my version are:
    * I calculate `N_BLOCKS` based on the total data size and no. of threads instead of setting `N_THREADS = N`. Any GPU would only have a limited amount of threads to offer
    * While this might not be necessary, I initialized all elements of `vec_res` to 0.0 using `cudaMemset()`
* https://developer.nvidia.com/blog/even-easier-introduction-cuda/ 

Each thread handles one cell of the vector system. For example, thread 0 would handle `vec_res[0] = A[0] + B[0]`. If the no. of threads is lesser than the data size, then the left-out cells would not be processed, leading to those elements of `vec_res` being left as 0.0. Recycling the same threads would defeat the purpose of parallelism anyways (say if I allocate 5 threads, then the only way I can think the program would work is that the first 5 elements are processed in parallel, then the next 5 elements, and so on. This is a serial process of parallel processes, so not truly parallel)


