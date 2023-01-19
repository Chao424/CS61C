#include "transpose.h"

/* The naive transpose function as a reference. */
void transpose_naive(int n, int blocksize, int *dst, int *src) {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            dst[y + x * n] = src[x + y * n];
        }
    }
}

/* Implement cache blocking below. You should NOT assume that n is a
 * multiple of the block size. */
void transpose_blocking(int n, int blocksize, int *dst, int *src) {
//     int number = n / blocksize;
//     int i,j,x,y;
//     for (i = 0; i < number; i++){
//         for (j=0; j< number; j++){
//             for(x = i*blocksize; x< (i+1)*blocksize; x++){
//                 for(y=j*blocksize;y< (j+1)*blocksize;y++){
//                     dst[y+x*n] = src[x+y*n];
//                 }
//             }
//         }
//     }
// }
    // YOUR CODE HERE
    for (int i = 0; i < n; i += blocksize)
        for (int j = 0; j < n; j+= blocksize)
            for (int x = 0; x < blocksize; x++)
                for (int y = 0; y < blocksize; y++) {
                    dst[(i + x)*n + j + y] = src[(j + y)*n + i + x];
                }
}

