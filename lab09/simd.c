#include <time.h>
#include <stdio.h>
#include <x86intrin.h>
#include "simd.h"

long long int sum(int vals[NUM_ELEMS]) {
	clock_t start = clock();

	long long int sum = 0;
	int a;
	for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
		for(unsigned int i = 0; i < NUM_ELEMS; i++) {
			if(vals[i] >= 128) {
				sum += vals[i];
			}
		}
	}
	clock_t end = clock();
	printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
	return sum;
}

long long int sum_unrolled(int vals[NUM_ELEMS]) {
	clock_t start = clock();
	long long int sum = 0;

	for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
		for(unsigned int i = 0; i < NUM_ELEMS / 4 * 4; i += 4) {
			if(vals[i] >= 128) sum += vals[i];
			if(vals[i + 1] >= 128) sum += vals[i + 1];
			if(vals[i + 2] >= 128) sum += vals[i + 2];
			if(vals[i + 3] >= 128) sum += vals[i + 3];
		}

		//This is what we call the TAIL CASE
		//For when NUM_ELEMS isn't a multiple of 4
		//NONTRIVIAL FACT: NUM_ELEMS / 4 * 4 is the largest multiple of 4 less than NUM_ELEMS
		for(unsigned int i = NUM_ELEMS / 4 * 4; i < NUM_ELEMS; i++) {
			if (vals[i] >= 128) {
				sum += vals[i];
			}
		}
	}
	clock_t end = clock();
	printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
	return sum;
}

long long int sum_simd(int vals[NUM_ELEMS]) {
	clock_t start = clock();
	__m128i _127 = _mm_set1_epi32(127);		// This is a vector with 127s in it... Why might you need this?
	long long int result = 0;				   // This is where you should put your final result!
	/* DO NOT DO NOT DO NOT DO NOT WRITE ANYTHING ABOVE THIS LINE. */
		__m128i temp_vec;
	unsigned int result_inner[4];
	unsigned int n = NUM_ELEMS >> 2;
	// __m128i *temp_pointer = vals;
	// __m128i *result_vec = result_inner;

	for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
		/* YOUR CODE GOES HERE */
		__m128i sum_vec = _mm_setzero_si128();
		for(unsigned int i =0; i<n; i++)
		{
			temp_vec = _mm_loadu_si128(vals+4*i);
			temp_vec = _mm_and_si128(temp_vec, _mm_cmpgt_epi32(temp_vec, _127));
			sum_vec = _mm_add_epi32(sum_vec,temp_vec);
	
		}
		/* You'll need a tail case. */

		_mm_storeu_si128(result_inner, sum_vec);

		result += result_inner[0]+result_inner[1]+result_inner[2]+result_inner[3];
		for(unsigned int i= n * 4; i<NUM_ELEMS;i++)
		{
			// printf("result: %lld\n", result);
			result += vals[i];
		}
	}
	clock_t end = clock();
	printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
	return result;
}

long long int sum_simd_unrolled(int vals[NUM_ELEMS]) {
	clock_t start = clock();
	__m128i _127 = _mm_set1_epi32(127);
	long long int result = 0;

	__m128i temp_vec;
	unsigned int result_inner[4];
	unsigned int n = NUM_ELEMS >> 2;
	for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
		/* COPY AND PASTE YOUR sum_simd() HERE */
		/* MODIFY IT BY UNROLLING IT */
		__m128i sum_vec = _mm_setzero_si128();
		for(unsigned int i =0; i < n / 4; i++)
		{
			temp_vec = _mm_loadu_si128(vals+16*i);
			temp_vec = _mm_and_si128(temp_vec, _mm_cmpgt_epi32(temp_vec, _127));
			sum_vec = _mm_add_epi32(sum_vec,temp_vec);

			temp_vec = _mm_loadu_si128(vals+16*i+4);
			temp_vec = _mm_and_si128(temp_vec, _mm_cmpgt_epi32(temp_vec, _127));
			sum_vec = _mm_add_epi32(sum_vec,temp_vec);

			temp_vec = _mm_loadu_si128(vals+16*i+8);
			temp_vec = _mm_and_si128(temp_vec, _mm_cmpgt_epi32(temp_vec, _127));
			sum_vec = _mm_add_epi32(sum_vec,temp_vec);

			temp_vec = _mm_loadu_si128(vals+16*i+12);
			temp_vec = _mm_and_si128(temp_vec, _mm_cmpgt_epi32(temp_vec, _127));
			sum_vec = _mm_add_epi32(sum_vec,temp_vec);
	
		}
		/* You'll need 1 or maybe 2 tail cases here. */
		for(unsigned int i = n / 4 * 4; i<n; i++){
			temp_vec = _mm_loadu_si128(vals+4*i);
			temp_vec = _mm_and_si128(temp_vec, _mm_cmpgt_epi32(temp_vec, _127));
			sum_vec = _mm_add_epi32(sum_vec,temp_vec);
		}

		_mm_storeu_si128(result_inner, sum_vec);

		result += result_inner[0]+result_inner[1]+result_inner[2]+result_inner[3];
		for(unsigned int i= n * 4; i<NUM_ELEMS;i++)
		{
			// printf("result: %lld\n", result);
			result += vals[i];
		}

	}
	clock_t end = clock();
	printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
	return result;
}