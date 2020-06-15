// parallel-mmm.c - parallel implementation of matrix matrix multiplication. 
// gbruns18 - 03/01/2020

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include <omp.h>

long rdtsc(void);

int main (int argc, char *argv[]) {
  int itemsPerDimension = 100;
  int repeats = 1;
  int counter, i, j, k, sum;
  unsigned long totalBytes; 
  struct timeval startTime, stopTime;
  double wallTimeForAll, wallTimeForOne, MatrixKBPerSecond; 
  char platform[32] = "unknown";
  long startCount = rdtsc();
  sleep(1);
  long endCount = rdtsc();
  long cycles = endCount - startCount;
  float coreSpeed = cycles / 1000000000.0;
  int thread_count = 1;
  int opt = 0;
  int debug = 0;

  while((opt = getopt(argc, argv, "d:i:r:p:t:")) != -1) {
    switch(opt) {
      case 'd':
 	debug = 1;
	break;
      case 'i':
	itemsPerDimension = atoi(optarg);
	break;
      case 'r':
	repeats = atoi(optarg);
	break;
      case 'p':
	strcpy(platform, optarg);
	break;
      case 't':
	thread_count = atoi(optarg);
	break;
    }
  }

  if(debug) {
	fprintf(stderr, "# itemsPerDimension: %d, repeats: %d, platform: %s, coreSpeed: %.3f, thread_count: %d\n", itemsPerDimension, repeats, platform, coreSpeed, thread_count);
	return 1;
  }
  
  if(itemsPerDimension < 1 || repeats < 1 || thread_count < 0) {
	fprintf(stderr, "Correct usage: ./parallel-mmm -i 'int > 0' -r 'int > 0' -p 'String' -t 'int > 0'\n");
	return 1;
  }

  fprintf(stderr, "# itemsPerDimension: %d, repeats: %d, platform: %s, coreSpeed: %.3f, thread_count: %d\n", itemsPerDimension, repeats, platform, coreSpeed, thread_count);
    
  totalBytes = itemsPerDimension * itemsPerDimension * sizeof(int); 
  
  int (*mOne)[itemsPerDimension] = malloc(sizeof(int[itemsPerDimension][itemsPerDimension]));
  int (*mTwo)[itemsPerDimension] = malloc(sizeof(int[itemsPerDimension][itemsPerDimension]));
  int (*mResult)[itemsPerDimension] = malloc(sizeof(int[itemsPerDimension][itemsPerDimension]));

  if ((mOne == NULL) || (mTwo == NULL) || (mResult == NULL)) {
    perror("initial malloc() of mOne, mTwo, and/or mResult failed");
    exit(-1); }

  // initialize the three matrices 
  for (i = 0; i < itemsPerDimension; i++) {
    for(j = 0; j < itemsPerDimension; j++) {
      mOne[i][j] = 333333;         
      mTwo[i][j] = 777777; 
      mResult[i][j] = 0; } }

	if (gettimeofday(&startTime, NULL) != 0) { 
		perror("gettimeofday() startTime failed");
		exit(-1); }

  // do the math repeats number of times. do not 
  for (counter = 0; counter < repeats; counter++) {
    sum = 0;
# pragma omp parallel for num_threads(thread_count) schedule(static, 1) \
	private(i, j, k, sum) shared(mOne, mTwo, mResult)
    for (i = 0; i < itemsPerDimension; i++) {
      for (j = 0; j < itemsPerDimension; j++) {
        for (k = 0; k < itemsPerDimension; k++) {
          sum = sum + mOne[i][k] * mTwo[k][j]; } 

        mResult[i][j] = sum;
        sum = 0; } } 
  }
  
	if (gettimeofday(&stopTime, NULL) != 0) { 
		perror("gettimeofday() stopTime failed");
		exit(-1); }
  
	wallTimeForAll = (double)(stopTime.tv_sec - startTime.tv_sec) + 
  					       (double)((stopTime.tv_usec - startTime.tv_usec) * 
  					       (double)0.000001); 

  // factor out repeats, generate rate in MatrixItemsPerSecond
  wallTimeForOne = wallTimeForAll / (double)repeats; 
  MatrixKBPerSecond = ((double)totalBytes / (double)1024.0) / wallTimeForOne; 

  // display a portion of mResult, for testing and debugging, enabled via gcc -DDISPLAY ...
  #ifdef DISPLAY 
    for (i = 0; i < 2; i++) {
      for(j = 0; j < 2; j++) {
        fprintf(stderr, "mResult[%d][%d] = %d\n", i, j, mResult[i][j]); } } }
  #endif
        
  fprintf(stderr, "# platform, totalBytes, wallTimeForAll, wallTimeForOne, MatrixKBPerSecond\n"); 
  fprintf(stderr, "%s, %lu, %.3lf, %.3lf, %.3lf\n", platform, totalBytes, wallTimeForAll, wallTimeForOne, MatrixKBPerSecond); 

  free(mOne); free(mTwo); free(mResult); 
  exit(0);
}

long rdtsc(void)
{
    long ret0[2];
    __asm__ __volatile__("rdtsc" : "=a"(ret0[0]), "=d"(ret0[1]));
    return ((long)ret0[1] << 32) | ret0[0];
}
