#include <stdio.h>
#include <x86intrin.h>

#define NUM_ELEMS ((1 << 16) + 10)

int main()
{
    int vals[NUM_ELEMS];
    __m128i temp_vec;
    __m128i _127 = _mm_set1_epi32(127);


    for (unsigned int i = 0; i < NUM_ELEMS; i++) vals[i] = rand() % 256;
    unsigned int n = NUM_ELEMS >> 2;
    __m128i *temp_pointer = vals;
    for(unsigned int i=0;i<n;i++)
    {
        temp_vec = _mm_loadu_si128(vals+4*i);
        printf("i:%d, vec: %d, vals: %d\n",i,temp_vec[0],*(vals+4*i));
        // printf("i:%d, vec: %d\n",i,*(vals+4*i));
    }

}