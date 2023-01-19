#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libbmp/libbmp.h"

#define REPEAT 60
#define BUF_SIZE 8192

#define ARRAY_SIZE 5000000

double* gen_array(int n) {
  double* array = (double*)malloc(n * sizeof(double));
  for (int i = 0; i < n; i++) array[i] = drand48();
  return array;
}


void v_add_optimized_adjacent(double* x, double* y, double* z) {
  // TODO: Modify this function
  // Do NOT use the `for` directive here!
  #pragma omp parallel
  {
    int n = omp_get_num_threads();
    int chunk_num = ARRAY_SIZE/n;
    int id = omp_get_thread_num();
    int i;
    for(i=id*chunk_num; i<(id+1)*chunk_num ; i++)
      z[i] = x[i] + y[i];
    if((i=chunk_num*n+id) < ARRAY_SIZE)
      z[i] = x[i] + y[i];
  }
}

void v_add_pallel(double* x, double* y, double* z) {
  // TODO: Modify this function
  // Do NOT use the `for` directive here!
  #pragma omp parallel for
    for(int i=0; i<ARRAY_SIZE; i+=1)
    {
        z[i] = x[i] + y[i];
       // t[i] = omp_get_thread_num();
    }
}



int main() {
	// Generate input vectors and destination vector
	double *x = gen_array(ARRAY_SIZE);
	double *y = gen_array(ARRAY_SIZE);
	double *z = (double*) malloc(ARRAY_SIZE*sizeof(double));
    int *t = (int*) malloc(ARRAY_SIZE*sizeof(int));

	// Test framework that sweeps the number of threads and times each run
	double start_time, run_time;
	int num_threads = omp_get_max_threads();	

    int i=8;
    int *array = (int*) malloc(i*(sizeof(int)));
    for(int k=0;k<i;k++)
    array[k]=0;

		omp_set_num_threads(i);		
	  	start_time = omp_get_wtime();
        for(int n=0;n<REPEAT;n++)
		v_add_optimized_adjacent(x,y,z);
		run_time = omp_get_wtime() - start_time;
	    printf("Optimized adjacent: %d thread(s) took %f seconds\n",i,run_time);
    

		omp_set_num_threads(i);		
	  	start_time = omp_get_wtime();
        for(int n=0;n<REPEAT;n++)
		v_add_pallel(x,y,z);
		run_time = omp_get_wtime() - start_time;
	    printf("pallel: %d thread(s) took %f seconds\n",i,run_time);

        // for(int n =0; n<ARRAY_SIZE;n++)
        // {
        //     for(int k =0; k<i; k++)
        //     {
        //         if(t[n]==k)
        //         array[k]+=1;
        //     }
        // }
        // for(int k =0;k<i;k++)
        //     printf("k:%d, num:%d\n",k,array[k]);

        // FILE *f =fopen("pallel.txt","w");
        // for(int n=0;n<ARRAY_SIZE;n++)
        //     fprintf(f,"%d %d\n",n, t[n]);
        // fclose(f);
  return 0;
}


