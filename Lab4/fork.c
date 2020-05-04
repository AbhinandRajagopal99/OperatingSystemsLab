#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>




void MergeSort(int beg, int end);
void Merge(int beg, int end);
void quicksort(int beg, int end);
int partition(int beg, int end);

char *terminal();


int a[15];
int b[15];

char cmd[100][100];
int size=0;

char *terminal(){
	int pidt = vfork();
	char *x[10];

	if(pidt>0){
		wait(NULL);
		return x[0];
	}

	else{
		char c[100];
		int i, len, count=0, j;

		fgets(c, 100, stdin);
		strcpy(cmd[size], c);

		size++;
		x[0] = &c[0];

		for(len=0; c[len]; len++);
		for(i=0, j=0; i<len-1; i++, j++){
			if(c[i]==' '){
				x[count][j]='\0';
				count++;
				x[count]=&c[i+1];
				j=-1;
			}
		}

		x[count][j]='\0';
		count++;
		x[count] = NULL;
		count++;



		execvp(x[0], x);
		if(strcmp(x[0],"exit"))
			printf("Command %s not found\n", x[0]);

		exit(0);
	}
}

void quicksort(int beg, int end){
	if(beg<end){
		int j=partition(beg, end);
		pid_t pidq=vfork();
		if(pidq==0){
			//printf("parent\n");
			quicksort(beg,j-1);
			exit(0);
		}
		else if(pidq>0){
			//printf("child\n");
			quicksort(j+1,end);
		}
		
	}
}
int partition(int beg, int end){
	int i=beg+1;
	int j=end;
	int pivot=a[beg];
	int temp;
	
	while(i<j)
	{
		//count++;
		while(a[i]<=pivot && i<=end)
			i++;
		while(a[j]>pivot && j>beg)
			j--;
		if(i<j){
			temp=a[i];
			a[i]=a[j];
			a[j]=temp;
		}
	}
	if(pivot>a[j])
	{
		temp=a[beg];
		a[beg]=a[j];
		a[j]=temp;
	}

	// for(int i=beg; i<=end; i++){
	// 	printf("%d ", a[i]);
	// }
	return j;
}

void MergeSort(int beg, int end){
	int mid;
	if(beg<end)
	{
		mid=(beg+end)/2;
		pid_t pidm = vfork();
		if(pidm==0){
			MergeSort(beg,mid);
			exit(0);
		}
		if(pidm>0){
			MergeSort(mid+1,end);
		}
		Merge(beg,end);	
	}

}

void Merge(int beg, int end){
	int mid=(beg+end)/2;
	int i=beg;
	int j=mid+1;
	int k;
	for(k=beg; k<=end; k++){
	
		if((i<=mid) && (j<=end)){
			
			if(a[i]<a[j]){
				b[k]=a[i];
				i++;
			}
			else{
				b[k]=a[j];
				j++;
			}
			
		}
		else
			break;
	
	}
		int t;
		if(i>mid)
			for(t=j; t<=end; t++){
				b[k]=a[t];
				k++;
			}
		else
			for(t=i; t<=mid; t++){
				b[k]=a[t];
				k++;
			}
	
	for(int q=beg; q<=end; q++)
	{
		a[q]=b[q];
		//printf("%d ", a[q]);
	}
	//printf("\n");
}



int main(){

	pid_t pid;
	

	
	//------------------------Q0---------------------------Test Run Fork
	//Q0:

	//Comment Here------------
	/*
	if(fork() || fork())
		fork();
	printf("OS 2019");
	*/
	
	//Comment Here -----------
	/*
	if(fork() && fork())
		fork();
	if(fork() || fork()){
		fork();
	}
	printf("os\n");
	*/

	//Comment Here------------
	/*
	printf("OS");
	fork();
	fork();
	fork();

	*/

	//Comment Here-----------
	/*
	printf("OS\n");
	fork();
	fork();
	fork();

	*/

	
	
	//------------------------Q1---------------------------Test Run EXEC
	//Q1:

	//Comment Here-------------
	/*
	char *args[] = {"ls", NULL};
	execvp(args[0], args);

	printf("Ends--\n");
	*/

	//Comment Here-----------------
	/*
	execl("/bin/ls", "ls", NULL);

	printf("Ends--\n");
	
	*/

	//Comment Here-----------------
	/*
	char *args[] = {"ls","-h", NULL};
	execvp(args[0], args);		

	printf("Ends--\n");
	*/

	//Comment Here-----------------
	/*
	execlp("man","fork", NULL);		

	printf("Ends--\n");
	*/

	//Comment Here-------------
	/*
	char *Binary = "/bin/bash";
	char *const args[] = {Binary, "-c", "echo \"Visit $HOSTNAME:$PORT from your browser\"", NULL};
	char *const env[] = {"HOSTNAME=www.arr.com", "PORT=8080", NULL};
	execve(Binary, args, env);

	*/

	/*
	//------------------------Q2---------------------------Even and Odd
	//Q2:

	int n;
	printf("Question 2: \nEnter number of terms: ");
	scanf("%d", &n);

	pid= fork();
	printf("\n");
	if(pid<0)
		printf("Failed to Fork\n");
	else if(pid==0){
		printf("Odd Series Generation:\n");
		int j=1;
		for(int i=0; i<n; i++){
			printf("%d ", j);
			j=j+2;
		}

	}
	else if(pid>0){
		printf("Even Series Generation:\n");
		int j=0;
		for(int i=0; i<n; i++){
			printf("%d ", j);
			j=j+2;
		}
	}

	printf("\n");
	
	*/

	/*

	//----------------------------Q3--------------Fibonacci and Prime
	//Q3:

	int n;
	printf("Question 3: \nEnter number of terms: ");
	scanf("%d", &n);

	pid= fork();
	printf("\n");

	if(pid<0)
		printf("Failed to Fork\n");
	else if(pid==0){
		printf("Prime Numbers Generation:\n");
		int count, c, i=3;

		if(n>=1){
			printf("2 ");
		}
		for(count=2; count<=n; i++){
			for(c=2; c<i; c++){
				if(i%c==0)
					break;
			}

			if(c==i){
				printf("%d ", i);
				count++;
			}
		}


	}
	else if(pid>0){
		printf("Fibonacci Numbers Generation:\n");
		int f=0; int s=1;
		int next;

		for(int i=0; i<n; i++){
			if(i<=1)
				next =i;
			else{
				next = f+s;
				f=s;
				s=next;
			}
			printf("%d ", next);
		}

	}

	printf("\n");

	*/

	
	
	//----------------------------Q4--------------Ascending and Descending
	//Q4:

	int n;
	printf("Question 4: \nEnter number of terms: ");
	scanf("%d", &n);
	int a[n];
	printf("Enter the Series: ");
	for(int i=0; i<n; i++)
		scanf("%d", &a[i]);

	pid= fork();
	printf("\n");

	if(pid<0)
		printf("Failed to Fork\n");
	else if(pid==0){
		printf("Descending Order:\n");
		
		int check;
		for(int i=0; i<n-1;i++)
		{
			check=0;
			for(int j=0;j<n-i-1; j++)
			{
				if(a[j]<a[j+1])
				{
					int temp=a[j];
					a[j]=a[j+1];
					a[j+1]=temp;
					check=1;
				}
			}
			if(check==0)
				break;
		}

		for(int i=0; i<n; i++)
			printf("%d ", a[i]);
		

	}
	else if(pid>0){
		printf("Ascending Order:\n");
		
		int check;
		for(int i=0; i<n-1;i++)
		{
			check=0;
			for(int j=0;j<n-i-1; j++)
			{
				if(a[j]>a[j+1])
				{
					int temp=a[j];
					a[j]=a[j+1];
					a[j+1]=temp;
					check=1;
				}
			}
			if(check==0)
				break;
		}

		for(int i=0; i<n; i++)
			printf("%d ", a[i]);

	}

	printf("\n");

	


	/*
	//----------------------Q5---------------Half Ascending Half Descending
	//Q5:

	int n;
	printf("Question 5: \nEnter number of terms: ");
	scanf("%d", &n);
	int a[n];
	printf("Enter the Series: ");
	for(int i=0; i<n; i++)
		scanf("%d", &a[i]);

	pid= vfork();
	printf("\n");

	if(pid<0)
		printf("Failed to Fork\n");
	
	else if(pid==0){
		printf("Leading Ascending Order:\n");
		
		int max,imax;
		for(int i=1; i<n;i++)
		{
			max=a[0];
			imax=0;
			for(int j=1; j<=n-i; j++)
			{
				if(a[j]>max)
				{
					max=a[j];
					imax=j;
				}
			}
			int temp=a[imax];
			a[imax]=a[n-i];
			a[n-i]=temp;
		}
		
		exit(0);

	}
	else if(pid>0){

		printf("Trailing Descending Order:\n");
		
		for(int i=0, j=n-1; i<n; i++, j--){
			b[j] = a[i];
		}
		for(int i=n/2, j=0; i<n; i++, j++)
			a[i]=b[j];
		printf("\n");
		for(int i=0; i<n; i++)
			printf("%d ", a[i]);
		

	}

	printf("\n");

	*/

	/*
	//-------------------------------Q6--------------------Orphan Zombie
	//Q6: 


	//Comment Here----------
	//Orphan Process:

	printf("Orphan process\n");
	pid_t pid2 = fork();
	
	if(pid2>0)
		printf("In ParentO Process ");
	else if(pid2==0){
		printf("%d ", getppid());
		sleep(8);
		printf("In ChildO Process");
		printf("%d ", getppid());
	}
	printf("\n");
	


	//Comment Here------
	//Zombie Process:

	printf("Zombie Process\n");
	pid_t pid2= fork();
	
	if(pid2>0){
		sleep(10);
		printf("In ParentZ Process");
	}

	else if(pid2==0){
		printf("In ChildZ Process");
		exit(0);
	}
	printf("\n");
	

	*/

	/*
	//-------------------------------Q7--------------------Merge Quick Sort 
	//Q7: 

	int n;
	printf("Question 7: \nEnter number of terms: ");
	scanf("%d", &n);
	printf("Enter the Series: ");
	for(int i=0; i<n; i++)
		scanf("%d", &a[i]);

	int op;
	printf("\n");
	printf("Enter Option: 1. Merge or 2. quick: ");
	scanf("%d", &op);

	switch(op){
		case 1:{
			printf("Merge Sort:\n");
			MergeSort(0,n-1);
			for(int i=0; i<n; i++)
				printf("%d ", a[i]);
			printf("\n");
			break;
		}
		case 2:{
			printf("Quick sort:\n");
			quicksort(0, n-1);
			for(int i=0; i<n; i++)
				printf("%d ", a[i]);
			printf("\n");
			break;
		}
	}
		
		

	printf("\n");

	*/
		

	/*
	//-------------------------------Q8--------------------History Command Prompt
	//Q8: 
	
	printf("Question 8: Command Prompt:\n");

	while(1){
		char A[10];
		printf("arr@arr-Lenovo-ideapad-110-15ISK:~$ ");
		int i, len=0, x=0, c=0;
		strcpy(A, terminal());
		if(strcmp(A,"exit")==0)
			break;
		for(len=0; A[len]; len++);

		if(A[0]=='!'){
			for(i=len-1; i>=1; i--){
				if(A[i]>='0' && A[i]<='9'){
					x+= pow(10, c)*((int)A[i] - 48);
					c++;
					continue;
				}
				else
					break;
			}
			if(i<=0){
				for(i=size-1, c=0; i>=0 && c<x; i--, c++)
					printf("%s", cmd[i]);
			}
		}

	}
		

	printf("\n");

	
	
	*/
	/*
	//-------------------------------Q9--------------------Histogram
	//Q9: 

	
	char string[100];
	
	printf("Question 9:\nEnter the String: ");
	scanf("%s", string);

	int count[36];
	int x;

	pid= vfork();
	printf("\n");


	if(pid<0)
		printf("Failed to Fork\n");
	else if(pid==0){
		printf("Frequency:\n");
		int i=0;
		for(int i=0; i<36; i++)
			count[i]=0;
		while(string[i]!='\0'){
			if(string[i] >= 'a' && string[i]<='z'){
				x=string[i] -'a';
				count[x]++;
			}
			if(string[i] >= 'A' && string[i]<= 'Z'){
				x=string[i] -'A';
				count[x]++;
			}
			if(string[i] >= '0' && string[i]<='9'){
				x=string[i] -'0' +26;
				count[x]++;
			}
			i++;
		}

		exit(0);

	}
	else if(pid>0){
		printf("Histogram:\n");
		sleep(2);
		for(int i=0; i<26; i++)
			printf("%c/%c-> %d\n", i+'a',i+'A', count[i]);
		for(int i=26; i<36; i++)
			printf("%c -> %d\n", i-26+'0', count[i]);

	}

	printf("\n");

	*/
	

	/*
	//------------------------Q10---------------------------Magic Square
	//Q10:


	
	int dim, magcon;

	printf("Question 10:\nEnter the Dimension: ");
	scanf("%d", &dim);
	int magic[dim][dim];
	magcon = dim * (dim*dim +1)/2;
	for(int i=0; i<dim; i++){
		for(int j=0; j<dim; j++)
			magic[i][j]=0;
	}
	printf("Magic Constant: %d\n", magcon);

	pid = vfork();

	if(pid<0)
		printf("Failed to Fork");
	else if(pid==0){
		printf("dim:%d\n", dim);
		int i=0;
		int j=dim/2;
		if(dim%2!=0){
			

			for(int num=1; num<=dim*dim; ){
				if(i==-1 && j==dim){
					j=dim-1;
					i=1;
				}
				else{
					if(j==dim)
						j=0;
					if(i<0)
						i=dim-1;
				}
				if(magic[i][j]){
					j--;
					i+=2;
				}
				else{
					magic[i][j] = num++;
					j++; i--;
				}
				
			}
		}
		for(int i=0; i<dim; i++){
			for(int j=0; j<dim; j++)
				printf("%d ", magic[i][j]);
			printf("\n");
		}
		exit(0);
		
	}
	else if(pid>0){
		printf("Check:\n");
		sleep(2);
		int sum[2*dim +2];
		printf("\nRow wise: ");
		for(int i=0; i<dim; i++){
			sum[i]=0;
			for(int j=0; j<dim; j++){
				sum[i]+=magic[i][j];
			}
			printf("%d : ", sum[i]);

		}
		printf("\nColumn wise: ");
		for(int j=0; j<dim; j++){
			sum[dim+j]=0;
			for(int i=0; i<dim; i++){
				sum[j+dim]+=magic[i][j];
			}
			printf("%d : ", sum[j+dim]);

		}
		printf("\ndiag 1 wise: ");
		sum[2*dim]=0;
		for(int i=0; i<dim; i++){
			sum[2*dim]+=magic[i][i];			
		}
		printf("%d : ", sum[2*dim]);

		printf("\ndiag 2 wise: ");
		sum[2*dim+1]=0;
		for(int i=0, j=dim-1; i<dim; i++, j--){
			sum[2*dim+1]+=magic[i][j];			
		}
		printf("%d : \n", sum[2*dim+1]);

		int count=0;
		for(int i=0; i<2*dim + 2; i++){
			if(sum[i]==magcon)
				count++;
		}

		if((count- 2)/2==dim)
			printf("checked\n");
		else
			printf("error\n");

	}	

	printf("\n");

	*/

	return 0;

}