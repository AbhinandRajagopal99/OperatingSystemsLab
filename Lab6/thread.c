#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


/*
//------------------------SUM OF N NUMBERS----------------------

int sum=0;

void *runnersum (void * param){
	int ul = atoi(param);
	for (int i=1; i<=ul; i++)
		sum+=i;

	pthread_exit(0);
}

int main(int argc, char **argv){

	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_create(&tid, &attr, runnersum, argv[1]);
	pthread_join(tid, NULL);

	printf("Sum of first %s natural Numbers is %d\n", argv[1], sum);

	return 0;
}

*/

/*
//----------------MATRIX MULTIPLICATION-----------------------

int m=3, k=2, n=3;

int A[3][2];
int B[2][3];
int C[3][3];

struct DT{
	int i;
	int j;
};

void *runnermat (void * param){
	int sum=0;
	struct DT *data = param;

	for(int p=0; p<k; p++)
		sum=sum+ A[data->i][p] * B[p][data->j];
	//printf("Threading - \n");

	C[data->i][data->j] = sum;
	pthread_exit(0);

}

int main(){

	printf("A:\n");
	for(int p=0; p<m; p++){
		for(int r=0; r<k; r++)
			scanf("%d",&A[p][r]);
	}

	printf("B:\n");
	for(int r=0; r<k; r++){
		for(int q=0; q<n; q++)
			scanf("%d",&B[r][q]);
	}

	pthread_t tid[9];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	int k=0;
	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			struct DT *data = (struct DT *) malloc(sizeof(struct DT));

			data->i = i;
			data->j = j;

			pthread_create(&tid[k],&attr, runnermat, data);
			k++;
		}
	}
	for(int i=0; i<k; i++)
		pthread_join(tid[i],NULL);

	printf("C:\n");
	for(int p=0; p<m; p++){
		for(int q=0; q<n; q++)
			printf("%d ",C[p][q]);
		printf("\n");
	}

	return 0;
}

*/

/*

//-------------------QUESTION 1: PRIME NUMBERS--------------

void *runnerprime (int param){

	int val=param;
	int flag=0;
	for(int i=2; i<val; i++){
		if(val%i==0){
			flag=1;
			break;
		}
	}
	if(flag==0)
		printf("%d ", val);

	pthread_exit(0);
}

int main(int argc, char *argv[]){

	pthread_t tid[100];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	int p= atoi(argv[1]);

	for(int i=2; i<=p; i++){
		int param = i;
		pthread_create(&tid[i], &attr, runnerprime, param);
	}
	for(int i=2; i<=p; i++)
		pthread_join(tid[i],NULL);
	printf("\n");

	return 0;
}

*/

/*

//--------------------QUESTION 2: MEAN MEDIAN MODE---------------------
int size;

void *runnermean (void **param){
	int sum=0;
	for(int i=0; i<size; i++)
		sum+= atoi(param[i+1]);
	float mean = sum/size;
	printf("Mean: %f\n", mean);

	pthread_exit(0);
}

void *runnermedian (void **param){
	int array[size];
	for(int i=0; i<size; i++)
		array[i]= atoi(param[i+1]);

	int check;
	for(int i=0; i<size-1;i++){
		check=0;
		for(int j=0;j<size-i-1; j++){
			if(array[j]>array[j+1]){
				int temp=array[j];
				array[j]=array[j+1];
				array[j+1]=temp;
				check=1;
			}
		}
		if(check==0)
			break;
	}
	float median;
	if(size%2 == 0)
		median = (float)(array[size/2 -1] + array[size/2])/2;
	else 
		median = array[size/2];

	printf("Median: %f\n", median);

	pthread_exit(0);

}

void *runnermode (void **param){

	int array[size];
	int b[size][2];

	for(int i=0; i<size; i++)
		array[i]= atoi(param[i+1]);

	int check;
	for(int i=0; i<size-1;i++){
		check=0;
		for(int j=0;j<size-i-1; j++){
			if(array[j]>array[j+1]){
				int temp=array[j];
				array[j]=array[j+1];
				array[j+1]=temp;
				check=1;
			}
		}
		if(check==0)
			break;
	}

	int flag[size];
	for(int i=0; i<size; i++)
		flag[i]=0;
	int k=0;
	for(int i=0; i<size; i++){
		
		if(flag[i]==1)
			continue;
		int count=1;
		for(int j=i+1; j<size; j++){
			if(array[i]==array[j]){
				count++;
				flag[j]=1;
			}
		}
		b[k][0] = array[i];
		b[k][1] = count;
		k++;
	}

	int max=b[0][1];

	for (int i=0; i<k; i++){
		if(b[i][1]>max)
			max=b[i][1];
	}
	printf("Mode: ");
	for(int i=0; i<k; i++){
		if(b[i][1]==max)
			printf("%d ", b[i][0]);
	}
	printf("\n");


	pthread_exit(0);
}

int main(int argc, char ** argv){

	pthread_t tid[3];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	size= argc-1;

	pthread_create(&tid[0], &attr, runnermean, argv);
	pthread_create(&tid[1], &attr, runnermedian, argv);
	pthread_create(&tid[2], &attr, runnermode, argv);

	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	pthread_join(tid[2],NULL);

	return 0;
}


*/


//----------------------QUESTION 2b  BOX PLOT-------------------------			//GRAPHICAL SUPPORT REQUIRED

int size;
int maxs, mins;
float median, quat1, quat3;
int array[20];
int out[10];
int outsize=0;

void *runnermedian (void *param){
	
	int check;
	for(int i=0; i<size-1;i++){
		check=0;
		for(int j=0;j<size-i-1; j++){
			if(array[j]>array[j+1]){
				int temp=array[j];
				array[j]=array[j+1];
				array[j+1]=temp;
				check=1;
			}
		}
		if(check==0)
			break;
	}

	for(int i=0; i<size; i++)
		printf("%d ", array[i]);
	printf("\n");

	// mins = array[0];
	// maxs = array[size-1];

	if(size%2 == 0)
		median = (float)(array[size/2 -1] + array[size/2])/2;
	else 
		median = array[size/2];

	// printf("Median: %f\n", median);

	pthread_exit(0);

}

void *runnerQ1 (void *param){
	int k=0;
	int b[10];
	for (int i=0; i<size; i++){
		if(array[i]<median){
			b[k]= array[i];
			k++;
		}
	}

	int check;
	for(int i=0; i<k-1;i++){
		check=0;
		for(int j=0;j<k-i-1; j++){
			if(b[j]>b[j+1]){
				int temp=b[j];
				b[j]=b[j+1];
				b[j+1]=temp;
				check=1;
			}
		}
		if(check==0)
			break;
	}

	if(k%2 == 0)
		quat1 = (float)(b[k/2 -1] + b[k/2])/2;
	else 
		quat1 = b[k/2];

	// printf("Quartile 1: %f\n", quat1);

	pthread_exit(0);

	
}

void *runnerQ3 (void *param){
	int k=0;
	int b[10];
	for (int i=0; i<size; i++){
		if(array[i]>median){
			b[k]= array[i];
			k++;
		}
	}

	int check;
	for(int i=0; i<k-1;i++){
		check=0;
		for(int j=0;j<k-i-1; j++){
			if(b[j]>b[j+1]){
				int temp=b[j];
				b[j]=b[j+1];
				b[j+1]=temp;
				check=1;
			}
		}
		if(check==0)
			break;
	}

	if(k%2 == 0)
		quat3 = (float)(b[k/2 -1] + b[k/2])/2;
	else 
		quat3 = b[k/2];

	// printf("Quartile 3: %f\n", quat3);

	pthread_exit(0);

}

void *runnerIQR(void *param){
	float iqr = quat3 - quat1;
	float leftbound = quat1 - 1.5*iqr;
	float rightbound = quat3 + 1.5*iqr;

	//printf("Left: %f, Right: %f\n",leftbound, rightbound);

	for(int i=0; i<size; i++){
		if(array[i]<leftbound || array[i]>rightbound){
			out[outsize]=array[i];
			outsize++;
		}
	}

	for(int i=0; i<size; i++){
		if(array[i]>=leftbound){
			mins=array[i];
			break;
		}
	}
	for(int i=size-1; i>0; i--){
		if(array[i]<=rightbound){
			maxs=array[i];
			break;
		}
	}

	pthread_exit(0);
}


int main(int argc, char ** argv){

	pthread_t tid[5];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	size= argc-1;

	for(int i=0; i<size; i++)
		array[i]= atoi(argv[i+1]);
	

	pthread_create(&tid[0], &attr, runnermedian, NULL);
	pthread_join(tid[0],NULL);

	pthread_create(&tid[1], &attr, runnerQ1, NULL);
	pthread_create(&tid[2], &attr, runnerQ3, NULL);
	
	pthread_join(tid[1],NULL);
	pthread_join(tid[2],NULL);

	pthread_create(&tid[3], &attr, runnerIQR, NULL);
	pthread_join(tid[3], NULL);

	printf("Min: %d, Quartile 1: %f, Median: %f, Quartile 3: %f, Max: %d\n", mins, quat1, median, quat3, maxs);
	printf("Outliers: ");
	for(int i=0; i<outsize; i++)
		printf("%d ", out[i]);
	printf("\n");

	for(int i=0; i<quat1; i++)
		printf(" ");
	
	for(int i=quat1; i<=quat3; i++)
		printf("-");

	for(int i=quat3+1; i<=100; i++)
		printf(" ");

	printf("\n");

	int l=0;
	// if(l<outsize)
	// 	while(out[l]<mins){
	// 		printf(".");
	// 		l++;
	// 	}

	int startleft =0;
	int startright=maxs;

	if(out[0]<mins && outsize>0){
		for(int i=0; i<out[0]; i++)
			printf(" ");
		while(out[l]<mins){
			printf(".");
			l++;
		}
		startleft = out[l-1];
	}

	for(int i=startleft+1; i<mins; i++)
			printf(" ");

	for(int i=mins; i<quat1; i++)
			printf("-");
	printf("|");

	for(int i=quat1+1; i<median; i++)
		printf(" ");

	printf("|");
	for(int i=median+1; i<quat3; i++)
		printf(" ");

	printf("|");

	for(int i=quat3+1; i<=maxs; i++)
			printf("-");


	if(out[l]>maxs && outsize>0){
		for(int i=maxs+1; i<out[l]; i++)
			printf(" ");
		while(out[l]>maxs){
			printf(".");
			l++;
		}
	}

	printf("\n");


	for(int i=0; i<quat1; i++)
		printf(" ");
	
	for(int i=quat1; i<=quat3; i++)
		printf("-");

	for(int i=quat3+1; i<=100; i++)
		printf(" ");

	printf("\n");

	for(int i=0; i<quat1; i++)
		printf(" ");
	printf("%2.0lf", quat1);

	for(int i=quat1+3; i<median; i++)
		printf(" ");
	printf("%2.0lf", median);

	for(int i=median+3; i<quat3; i++)
		printf(" ");
	printf("%2.0lf", quat3);

	printf("\n");


	return 0;
}



/*

//----------------------QUESTION 3: MERGE and QUICK SORT----------------																									//WORKS IF SIZE IS MULTIPLE OF NO. OF THREADS

struct data{
	int beg;
	int end;
	
};

int size;
int ArrM[100],ArrQ[100];

void *QuickSort(void *Q);
int partition(int beg,int end);
void *MergeSort(void *M);
void Merge(int beg,int end);


int main(int argc, char *argv[]){

	pthread_t tid[2];
	pthread_attr_t attr;
	pthread_attr_init (&attr);
	struct data StM,StQ;
	size = argc -1;
	StM.beg = 0;
	StM.end = size-1;
	StQ.beg = 0;
	StQ.end = size-1;
	for(int i=1;i<=size;i++){
		ArrM[i-1] = atoi(argv[i]);
		ArrQ[i-1] = atoi(argv[i]);

	}
	pthread_create(&tid[0],&attr,MergeSort,&StM);
	pthread_create(&tid[1],&attr,QuickSort,&StQ);
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);

	printf("QuickSort\n");
	for(int i=0;i<size;i++)
		printf("%d ",ArrQ[i] );

	printf("\nMergeSort\n");
	for(int i=0;i<size;i++)
		printf("%d ",ArrM[i] );
	printf("\n");


	return 0;
}

// QUICK SORT
void *QuickSort(void *Q){

	struct data *DQ = Q;
	int begi = DQ->beg;
	int endi = DQ->end;
	if(begi<endi){

		int j;
		j=partition(begi,endi);
		struct data QLeft,QRight;
		QLeft.beg = begi;
		QLeft.end = j-1;

		QRight.beg = j+1;
		QRight.end = endi;

		pthread_t tid[2];
		pthread_attr_t attr;
		pthread_attr_init (&attr);

		pthread_create(&tid[0],&attr,QuickSort,&QLeft);
		pthread_create(&tid[1],&attr,QuickSort,&QRight);

		pthread_join(tid[0],NULL);
		pthread_join(tid[1],NULL);
		
	}
	pthread_exit(0);

}

int partition(int beg,int end){
	int pivot=ArrQ[beg];
	int i=beg;
	int j=end;
	while(i<j){	
		
		while(ArrQ[i]<=pivot && i<end)
			i++;
			
		while(ArrQ[j]>pivot && j>beg)
			j--;
			
		if(i<j){
			int temp=ArrQ[i];
			ArrQ[i]=ArrQ[j];
			ArrQ[j]=temp;
		}
	}
	

	int temp=ArrQ[beg];
	ArrQ[beg]=ArrQ[j];
	ArrQ[j]=temp;


return j;
}


// MERGE SORT
void *MergeSort(void *M){
	struct data *DM = M;
	int begi = DM->beg;
	int endi = DM->end;
	if(begi<endi){
		int mid=(begi+endi)/2;

		struct data MLeft,MRight;
		MLeft.beg = begi;
		MLeft.end = mid;

		MRight.beg = mid+1;
		MRight.end = endi;

		pthread_t tid[2];
		pthread_attr_t attr;
		pthread_attr_init (&attr);

		pthread_create(&tid[0],&attr,MergeSort,&MLeft);
		pthread_create(&tid[1],&attr,MergeSort,&MRight);
		pthread_join(tid[0],NULL);
		pthread_join(tid[1],NULL);
		
		Merge(begi,endi);
	}
	pthread_exit(0);
}

void Merge(int beg,int end){

	int i=beg,k;  
	int mid=(beg+end)/2;
	int j=mid+1;  
	int b[end-beg+1];
	
	for(k=0;k<(end-beg+1);k++){
		if(i<=mid && j<=end){
			if(ArrM[i]<ArrM[j]){ 
				b[k] = ArrM[i];
				i++;
			}
			else{
				b[k] = ArrM[j];
				j++;
			}
		}
		
		else 
			break;
				
	}
	if(i>mid || j>end){
		if(i>mid){
			for(int ma=j;ma<=end;ma++){
				b[k] = ArrM[ma];
				k++;
			}
		}
		else if(j>end){
			for(int ma=i;ma<=mid;ma++){
				b[k] = ArrM[ma];
				k++;
			}
		}
	}
	
	int z=0;
	for(int ma=beg;ma<=end;ma++){
		ArrM[ma] = b[z];
		z++;
	}
}

*/

/*

//----------------------QUESTION 4: MONTE CARLO ESTIMATION OF PI----------------(Threading in each quadrant)

#define Interval 1000


double pi1, pi2, pi3, pi4;
void *runnermonte(int param){

	double x, y, dist, pi;
	int cipoints=0, sqpoints=0;

	srand(time(NULL));

	for(int i=0; i<Interval * Interval; i++){
		x= (double)(rand() % (Interval+1))/Interval;
		y= (double)(rand() % (Interval+1))/Interval;

		dist = x*x + y*y;

		if(dist <=1)
			cipoints++;

		sqpoints++;

		pi= (double) cipoints/sqpoints;

	}
	switch (param){
		case 0:
			pi1=pi;
			break;
		case 1:
			pi2=pi;
			break;
		case 2:
			pi3=pi;
			break;
		case 3:
			pi4=pi;
			break;
	}

	pthread_exit(0);

}

int main(){

	double pi;
	pthread_t tid[4];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	for(int i=0; i<4; i++)
		pthread_create(&tid[i], &attr, runnermonte, i);
	
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	pthread_join(tid[2],NULL);
	pthread_join(tid[3],NULL);

	printf("Iterations: %d\nQuatrant 1: %lf\nQuatrant 2: %lf\nQuatrant 3: %lf\nQuatrant 4: %lf", Interval, pi1, pi2, pi3, pi4);

	pi = pi1+pi2+pi3+pi4;
	printf("\nPi: %lf\n", pi);


	return 0;
}

*/

/*
//----------------------QUESTION 4: MONTE CARLO ESTIMATION OF PI----------------(Threading in each points)

int Interval=100;
int cipoints=0, sqpoints=0;

void *runnermonte(int param){

	double x, y, dist;
	//srand(time(NULL));

	x= (double)(rand() % (Interval+1))/Interval;
	y= (double)(rand() % (Interval+1))/Interval;

	dist = x*x + y*y;

	if(dist <=1)
		cipoints++;

	sqpoints++;

	pthread_exit(0);

}

int main(){

	double pi;
	pthread_t tid[Interval*Interval];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	for(int i=0; i<Interval*Interval; i++)
		pthread_create(&tid[i], &attr, runnermonte, i);
	
	for(int i=0; i<Interval*Interval; i++)
		pthread_join(tid[i], NULL);

	pi = (double) cipoints/sqpoints * 4;
	printf("\nPi: %lf\n", pi);


	return 0;
}

*/

/*
//----------------------QUESTION 5: MATRIX INVERSE-------------------
# define N 4

int adj[N][N];
float inv[N][N];
int A[N][N];

struct DT{
	int i;
	int j;
};

void cofactor(int mat[N][N], int temp[N][N], int p, int q, int n){

	int i=0, j=0;

	for(int row= 0; row<n; row++){
		for(int col=0; col<n; col++){
			if(row!=p && col!=q){
				temp[i][j++] = mat[row][col];
				if(j==n-1){
					j=0;
					i++;
				}
			}
		}
	}

}

int determinant(int mat[N][N], int n){
	
	int D=0;

	if(n==1)
		return mat[0][0];

	int temp[N][N];
	int sign=1;


	for(int f=0; f<n; f++){
		cofactor(mat, temp, 0, f, n);
		D += sign * mat[0][f] * determinant(temp, n-1);

		sign=-sign;
	}
	return D;
}

void* runnercofacval(void *param){

	int temp[N][N];
	int sign=1;

	struct DT *data = param;
	cofactor(A, temp, data->i, data->j, N);
	sign = ((data->i + data->j)%2==0) ? 1: -1;
	adj[data->j][data->i] = sign * (determinant(temp, N-1));

	pthread_exit(0);
}

int main(){
	
	printf("Enter the %d x %d matrix:\n",N,N);
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			scanf("%d",&A[i][j]);
		}
	}


	pthread_t tid[N*N];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	if(N==1){
		adj[0][0]=1;

	}
	else{

		int k=0;
		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++){
				struct DT *data = (struct DT *) malloc(sizeof(struct DT));

				data->i = i;
				data->j = j;

				pthread_create(&tid[k],&attr, runnercofacval, data);
				k++;
			}
		}
		for(int i=0; i<k; i++)
			pthread_join(tid[i],NULL);

	}
	printf("Adjoint:\n");
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++)
			printf("%d ",adj[i][j]);
		printf("\n");
	}

	int det = determinant(A, N);
	if(det==0){
		printf("Inverse doesn't exist\n");
		return 0;
	}

	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			inv[i][j]= adj[i][j]/((float)det);

	printf("Inverse:\n");
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++)
			printf("%f ",inv[i][j]);
		printf("\n");
	}

	return 0;
}

*/

/*
//----------------------QUESTION 6: BINARY SEARCH-------------------		

int part=0;
int size;
int a[100];
int value;
int ind;
int found = 0;

void *runnerbinary(void * param){
	int threadpart = part++;

	int mid;
	int beg = threadpart * size/4;
	int end = (threadpart +1) * size/4 -1;

	//printf("%d %d ->\n", beg, end);

	while(beg<=end){
		mid=(end+beg)/2;

		if(a[mid]==value){
			found=1;
			ind = mid;
			break;
		}
		else if(a[mid]>value)
			end= mid-1;
		else
			beg= mid+1;
	}

	pthread_exit(0);
}

int main(int argc, char *argv[])
{	
	size= argc-1;

	printf("Enter value to be searched: ");
	scanf("%d", &value);

	for(int i=0; i<argc-1; i++)
		a[i] = atoi(argv[i+1]);

	for(int i=1; i<size; i++){
		for(int j=i; j>0; j--){	
			if(a[j]<a[j-1]){
				
				int tmp=a[j];
				a[j]=a[j-1];
				a[j-1]=tmp;
			}
			else
				break;
		}
	}

	printf("Sorted Array: ");
	for(int i=0; i<size; i++)
		printf("%d ", a[i]);
	printf("\n");

	pthread_t tid[4];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	for(int i=0; i<4; i++)
		pthread_create(&tid[i], &attr, runnerbinary, NULL);
	
	for (int i=0; i<4; i++)
		pthread_join(tid[i], NULL);

	if(found)
		printf("%d Found at %d\n", value, ind);
	else
		printf("%d Not Found\n", value);
	
	
	return 0;
}

*/

/*

//----------------------QUESTION 7: EXTENDED BINARY SEARCH-------------------

int part=0;
int size;
int a[100];
int value;
int ind[100];
int k=0;
int found = 0;

void *runnerbinary(void * param){
	int threadpart = part++;

	int mid;
	int beg = threadpart * size/4;
	int end = (threadpart +1) * size/4 -1;

	printf("%d %d ->\n", beg, end);

	while(beg<=end){
		mid=(end + beg)/2;

		if(a[mid]==value){
			found=1;
			ind[k] = mid;
			k++;
			break;
		}
		else if(a[mid]>value)
			end= mid-1;
		else
			beg= mid+1;
	}

	if(mid<=end && found==1){
		for(int i=mid+1; i<=end; i++){
			if(value==a[i]){
				ind[k]=i;
				k++;
			}
		}
		for(int i=beg; i<mid; i++){
			if(value==a[i]){
				ind[k]=i;
				k++;
			}
		}
	}

	pthread_exit(0);
}

int main(int argc, char *argv[])
{	
	size= argc-1;

	printf("Enter value to be searched: ");
	scanf("%d", &value);

	for(int i=0; i<argc-1; i++)
		a[i] = atoi(argv[i+1]);

	for(int i=1; i<size; i++){
		for(int j=i; j>0; j--){	
			if(a[j]<a[j-1]){
				
				int tmp=a[j];
				a[j]=a[j-1];
				a[j-1]=tmp;
			}
			else
				break;
		}
	}

	printf("Sorted Array: ");
	for(int i=0; i<size; i++)
		printf("%d ", a[i]);
	printf("\n");

	pthread_t tid[4];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	for(int i=0; i<4; i++)
		pthread_create(&tid[i], &attr, runnerbinary, NULL);
	
	for (int i=0; i<4; i++)
		pthread_join(tid[i], NULL);

	if(found){
		printf("%d Found at ", value);
		for(int i=0; i<k; i++)
			printf("%d ",ind[i]);
		printf("\n");
	}
	else
		printf("%d Not Found\n", value);
	
	
	return 0;
}


*/
