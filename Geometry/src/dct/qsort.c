#include "defs.h"
#include "qsort.h"


void print_points(point** array,int n)
{
  int i=0;

  for(i=0; i<n;i++)
  printf("%.2f %.2f\n",array[i]->x,array[i]->y);
}


// Quicksort to sort individual segments
void quicksort(point** arr, int low, int high,int numBusyThreads, int MAX_THREADS) 
{
	 int i = low;
	 int j = high;
	 int y = 0;
	 point midpoint;
         point* temp;
	 /* compare value */
	 int z = (low + high)/2;
         
         midpoint = *arr[z];

	 omp_set_nested(1);
	
	 /* partition */
	 do {

 	  while((arr[i]->x < midpoint.x) || (arr[i]->x == midpoint.x && arr[i]->y < midpoint.y))
            i++;

         while((arr[j]->x > midpoint.x) || (arr[j]->x == midpoint.x && arr[j]->y > midpoint.y)) 
            j--;

	  if(i <= j) {
	   /* swap two elements */

	   temp=arr[i];
	   arr[i]=arr[j];
	   arr[j] = temp;
	   i++; 
	   j--;
	  }

	 } while(i <= j);
	
	// printf("Num busy threads %d\n",numBusyThreads);
	  #pragma omp flush(numBusyThreads)

	 if(numBusyThreads >= MAX_THREADS)	 
         {
	 	/* recursive */
	 	if(low < j) 
	 	 quicksort(arr, low, j,numBusyThreads,MAX_THREADS);

	 	if(i < high) 
	 	 quicksort(arr, i, high,numBusyThreads,MAX_THREADS);
         }
	 else
  	 {
		//printf("running paralle");
		#pragma omp atomic
		numBusyThreads += 2;
		//omp_set_num_threads(2);			
		#pragma omp parallel shared(arr,low,high,i,j)
		{
			printf("threads=%d\n",omp_get_num_threads());
			#pragma omp sections nowait
			{
			    #pragma omp section
			    {
	 			if(low < j) 
			 	quicksort(arr, low, j,numBusyThreads,MAX_THREADS);

				#pragma omp atomic
				numBusyThreads--;
			    }

			    #pragma omp section
			    {
	 			if(i < high) 
			 	quicksort(arr, i, high,numBusyThreads,MAX_THREADS);

				#pragma omp atomic
				numBusyThreads--;
			    }

			}
		}
		
	 }

}

/*
void alloc_memory(int n)
{

  int i;

    p_array = (point *)calloc(n, sizeof(point));
  if (p_array == NULL)
    printf("Not enough memory\n");

}
int read_points(int np)
{
  int i;
  FILE* fp;
  int code=0;
  int n;
   
  fp = fopen("input.txt","r");
  code=fscanf(fp,"%d",&n);
  printf("%d\n",n);
  alloc_memory(n);
  for (i = 0; i < n; i++)
  code=fscanf(fp,"%f %f", &p_array[i].x, &p_array[i].y);

  fclose(fp);
  return n;
}*/

/*
int main(int argc, char *argv[])
{
  //cardinal n;
  int n;
  int i;
  int low=0;
  int high =0 ;
  int max_threads;
 n = read_points(n);

   printf("Number of sites are %d\n",n);

 
  high = n-1;
  max_threads = omp_get_num_procs();
 printf("Number of threads are %d\n",max_threads);
  printf("Before sorting\n");
  print_points(p_array,n);
  quicksort(p_array, low, high, 0, max_threads) ;
  printf("After sorting\n");
  print_points(p_array,n);
}*/
 

