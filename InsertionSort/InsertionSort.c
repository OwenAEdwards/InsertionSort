#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct timeval start,stop;

static int numSwaps=0,numComparisons=0;

void swap(int *a,int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
    numSwaps++;
}

int *randDataStructPopulator(int numOfElements,int *dataStruct) {
   srand(time(NULL));
   for (int i=0;i<=numOfElements;i++) {
      dataStruct[i]=rand()%100; // only numbers from 0 to 99
   }
   return dataStruct;
}
// we begin with dataStruct and its corresponding numOfElements as our input size (N)
void insertionSort(int numOfElements,int *dataStruct) {
    // we want to loop through every element except the first (because we won't have anything to compare the 0th element with) in
    // dataStruct so we go from 1 to the numOfElements
    for (int i=1;i<numOfElements;i++) {
        // since we have i++ (incrementing by 1), i being our current "unsorted" index, we will set i equal to j, where j will be
        // the index of all previous "sorted" elements that we want to check against our current element
        int j=i;
        // while the element of a "sorted" index we're comparing j is greater than 0 (within dataStruct) AND the previous element
        // j-1 of dataStruct is greater than j, we continue to compare backwards after each swap
        while (j>0&&dataStruct[j-1]>dataStruct[j]) {
            // we swap every "sorted" element at dataStruct[j-1] with our "unsorted" dataStruct[j] while dataStruct[j-1] is still
            // larger
            swap(&dataStruct[j-1],&dataStruct[j]);
            // we decrement through index j while our "unsorted" A[j] still remains "unsorted"
            j--;
            numComparisons++;
        }
    }
}

int main() {

    int numOfElements;
    int *dataStruct;

    printf("Number of elements in data structure (N): ");
    scanf("%d",&numOfElements);

    dataStruct=(int*)malloc(numOfElements*sizeof(int)); // allocating space in the data structure

    dataStruct=randDataStructPopulator(numOfElements,dataStruct);

    gettimeofday(&start,NULL);
    insertionSort(numOfElements,dataStruct);
    gettimeofday(&stop,NULL);

    printf("The selection sort lasted: %fms\n",(((double)stop.tv_sec-start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec)/1000);

    printf("\n");
    
    printf("The total of comparisons was: %d\n",numComparisons);
    printf("The best case number of comparisons is O(N): %d\n",numOfElements);
    printf("The worst case number of comparisons is %d*(%d-1), approximately O(N^2), which is %lu\n",numOfElements,numOfElements,(long)numOfElements*(numOfElements-1));

    printf("\n");

    printf("The total of swaps was: %d\n",numSwaps);
    printf("The best case number of swaps is O(1)\n");
    printf("The worst case number of swaps is %d*(%d-1), approximately O(N^2), which is %lu\n",numOfElements,numOfElements,(long)numOfElements*(numOfElements-1));

    return 0;
}