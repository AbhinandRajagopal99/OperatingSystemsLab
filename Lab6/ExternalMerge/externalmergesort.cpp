#include <bits/stdc++.h> 
using namespace std; 
  

struct data{
	int beg;
	int end;

};

int arr[1000];

int run_size;

struct MinHeapNode 
{ 
	// The element to be stored 
	int element; 
  
	// index of the array from which the element is taken 
	int i; 
}; 
  
void swap(MinHeapNode* x, MinHeapNode* y); 
  
class MinHeap 
{ 
	MinHeapNode* harr; // pointer to array of elements in heap 
	int heap_size;     // size of min heap 
  
public: 
	// Constructor: creates a min heap of given size 
	MinHeap(MinHeapNode a[], int size); 
  
	// to heapify a subtree with root at given index 
	void MinHeapify(int); 
  
	// to get index of left child of node at index i 
	int left(int i) { return (2 * i + 1); } 
  
	// to get index of right child of node at index i 
	int right(int i) { return (2 * i + 2); } 
  
	// to get the root 
	MinHeapNode getMin() {  return harr[0]; } 
  
	// to replace root with new node x and heapify() 
	// new root 
	void replaceMin(MinHeapNode x) 
	{ 
		harr[0] = x; 
		MinHeapify(0); 
	} 
}; 
  
MinHeap::MinHeap(MinHeapNode a[], int size) 
{ 
	heap_size = size; 
	harr = a; // store address of array 
	int i = (heap_size - 1) / 2; 
	while (i >= 0) 
	{ 
		MinHeapify(i); 
		i--; 
	} 
} 
  
void MinHeap::MinHeapify(int i) 
{ 
	int l = left(i); 
	int r = right(i); 
	int smallest = i; 
	if (l < heap_size && harr[l].element < harr[i].element) 
		smallest = l; 
	if (r < heap_size && harr[r].element < harr[smallest].element) 
		smallest = r; 
	if (smallest != i) 
	{ 
		swap(&harr[i], &harr[smallest]); 
		MinHeapify(smallest); 
	} 
} 
  
void swap(MinHeapNode* x, MinHeapNode* y) 
{ 
	MinHeapNode temp = *x; 
	*x = *y; 
	*y = temp; 
} 


void merge(int beg,int end){

	int i=beg,k;  
	int mid=(beg+end)/2;
	int j=mid+1;  
	int b[end-beg+1];
	
	for(k=0;k<(end-beg+1);k++){
		if(i<=mid && j<=end){
			if(arr[i]<arr[j]){ 
				b[k] = arr[i];
				i++;
			}
			else{
				b[k] = arr[j];
				j++;
			}
		}
		
		else 
			break;
				
	}
	if(i>mid || j>end){
		if(i>mid){
			for(int ma=j;ma<=end;ma++){
				b[k] = arr[ma];
				k++;
			}
		}
		else if(j>end){
			for(int ma=i;ma<=mid;ma++){
				b[k] = arr[ma];
				k++;
			}
		}
	}
	
	int z=0;
	for(int ma=beg;ma<=end;ma++){
		arr[ma] = b[z];
		z++;
	}
}

void * mergeSort(void *param)
{ 
	struct data *DM = (struct data *)param;
	int l= DM->beg;
	int r= DM->end;
	
	// for(int i=0; i<run_size; i++)
	// 	arr[i]=DM->arr[i];

	if (l < r) 
	{ 
		
		int mid = l + (r - l) / 2; 

		struct data MLeft,MRight;
		MLeft.beg = l;
		MLeft.end = mid;
		
		// for(int i=0; i<run_size; i++){
		// 	MLeft.arr[i]=arr[i];
		// 	MRight.arr[i] =arr[i];
		// }

		MRight.beg = mid+1;
		MRight.end = r;

		pthread_t tid[2];
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		pthread_create(&tid[0],&attr,mergeSort,&MLeft);
		pthread_create(&tid[1],&attr,mergeSort,&MRight);
		pthread_join(tid[0],NULL);
		pthread_join(tid[1],NULL);

		merge(l, r);

	}
	pthread_exit(0); 
} 
  
FILE* openFile(char* fileName, char* mode) 
{ 
	FILE* fp = fopen(fileName, mode); 
	if (fp == NULL) 
	{ 
		perror("Error while opening the file.\n"); 
		exit(EXIT_FAILURE); 
	} 
	return fp; 
} 
  
void mergeFiles(char *output_file, int n, int k) 
{ 
	FILE* in[k]; 
	for (int i = 0; i < k; i++) 
	{ 
		char fileName[2]; 
  
		// convert i to string 
		snprintf(fileName, sizeof(fileName), "%d", i); 
  
		// Open output files in read mode. 
		in[i] = openFile(fileName, "r"); 
	} 
  
	FILE *out = openFile(output_file, "w"); 

	MinHeapNode* harr = new MinHeapNode[k]; 
	int i; 
	for (i = 0; i < k; i++) 
	{ 
		// break if no output file is empty and 
		// index i will be no. of input files 
		if (fscanf(in[i], "%d ", &harr[i].element) != 1) 
			break; 
  
		harr[i].i = i; // Index of scratch output file 
	} 
	MinHeap hp(harr, i); // Create the heap 
  
	int count = 0; 
  
	// Now one by one get the minimum element from min 
	// heap and replace it with next element. 
	// run till all filled input files reach EOF 
	while (count != i) 
	{ 
		// Get the minimum element and store it in output file 
		MinHeapNode root = hp.getMin(); 
		fprintf(out, "%d ", root.element); 
  
		// Find the next element that will replace current 
		// root of heap. The next element belongs to same 
		// input file as the current min element. 
		if (fscanf(in[root.i], "%d ", &root.element) != 1 ) 
		{ 
			root.element = INT_MAX; 
			count++; 
		} 
  
		// Replace root with next element of input file 
		hp.replaceMin(root); 
	} 
  
	// close input and output files 
	for (int i = 0; i < k; i++) 
		fclose(in[i]); 
  
	fclose(out); 
} 
  
void createInitialRuns(char *input_file, int num_ways) 
{ 
	FILE *in = openFile(input_file, "r"); 

	FILE* out[num_ways]; 
	char fileName[2]; 
	for (int i = 0; i < num_ways; i++) 
	{ 
		// convert i to string 
		snprintf(fileName, sizeof(fileName), "%d", i); 
  
		// Open output files in write mode. 
		out[i] = openFile(fileName, "w"); 
	} 
  
	//int* arr = (int*)malloc(run_size * sizeof(int)); 
  
	bool more_input = true; 
	int next_output_file = 0; 
  
	int i;
	while (more_input) 
	{ 
		for (i = 0; i < run_size; i++) 
		{ 
			if (fscanf(in, "%d ", &arr[i]) != 1) 
			{ 
				more_input = false; 
				break; 
			} 
		} 
   
		pthread_t tid;
		pthread_attr_t attr;
		pthread_attr_init (&attr);

		struct data StM;
		StM.beg = 0;
		StM.end = i-1;
		
		pthread_create(&tid,&attr,mergeSort,&StM);
		pthread_join(tid,NULL);

		 
		// write the records to the appropriate scratch output file 
		// can't assume that the loop runs to run_size 
		// since the last run's length may be less than run_size 
		for (int j = 0; j < i; j++) 
			fprintf(out[next_output_file], "%d ", arr[j]); 
  
		next_output_file++; 
	} 
  
	for (int i = 0; i < num_ways; i++) 
		fclose(out[i]); 
  
	fclose(in); 
} 
  
 
void externalSort(char* input_file,  char *output_file, 
				  int num_ways, int run_size) 
{ 
	createInitialRuns(input_file, num_ways); 
  	mergeFiles(output_file, run_size, num_ways); 
} 
 
int main() 
{ 
	// No. of Partitions of input file. 
	int num_ways = 10; 
  
	// The size of each partition 
	run_size = 5; 
  
	char input_file[] = "input.txt"; 
	char output_file[] = "output.txt"; 
  
	FILE* in = openFile(input_file, "w"); 
  
	srand(time(NULL)); 

	for (int i = 0; i < num_ways * run_size; i++) 
		fprintf(in, "%d ", rand()%100); 
  
	fclose(in); 
  
	externalSort(input_file, output_file, num_ways, 
				run_size); 
  
	return 0; 
} 

