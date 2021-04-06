Parallel-Matrix-Multiplication-OpenMP

Implementation of parallel matrix multiplication with OpenMP.

The code of naive-mmm.c was provided by Professor Charlie Peck from Earlham College.

If you run the parallelized version of the program, then it will initiate three matrices (two matrices that will be multiplied and one that will store the result).
After that, it will iterate through the entries of the matrices to perform the matrix multiplication. The work is split up into the rows and columns, so that one thread can compute the value of one entry in the resulting matrix.
