// mmm-nieve.c - nieve implementation of matrix matrix multiplication. 
// charliep - ages ago..., updated Spring, 2016 and again in Spring, 2020.

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>

int main (int argc, char *argv[]) {
  int itemsPerDimension, repeats, counter, i, j, k, sum;
  unsigned long totalBytes; 
  struct timeval startTime, stopTime;
  double wallTimeForAll, wallTimeForOne, MatrixKBPerSecond; 
  char platform[32] = ""; 
  float coreSpeed = 1.0; 

  if (argc == 5) {
    sscanf(argv[1], "%d", &itemsPerDimension);
    sscanf(argv[2], "%d", &repeats); 
    sscanf(argv[3], "%f", &coreSpeed); 
    sscanf(argv[4], "%s", platform); } 

  else if (argc == 4) {
    sscanf(argv[1], "%d", &itemsPerDimension);
    sscanf(argv[2], "%d", &repeats); 
    sscanf(argv[3], "%f", &coreSpeed); 
    strcpy(platform, "unknown"); } 

  else if (argc == 3) {
    sscanf(argv[1], "%d", &itemsPerDimension);
    sscanf(argv[2], "%d", &repeats); 
    coreSpeed = 1.0; 
    strcpy(platform, "unknown"); } 

  else if (argc == 2) {
    sscanf(argv[1], "%d", &itemsPerDimension);
    repeats = 10; 
    coreSpeed = 1.0;  
    strcpy(platform, "unknown"); } 

  else {
    itemsPerDimension = 1000;
    repeats = 10; 
    coreSpeed = 1.0; 
    strcpy(platform, "unknown"); } 

  fprintf(stderr, "# itemsPerDimension: %d, repeats: %d, platform: %s, coreSpeed: %.3f\n", itemsPerDimension, repeats, platform, coreSpeed); 
    
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
