#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>


int main() 
{
	// ftok to generate unique key 
	key_t key = ftok("shmfile",65); 

	// shmget returns an identifier in shmid 
	int shmid = shmget(key,1024,0666|IPC_CREAT); 

	// shmat to attach to shared memory 
	char str[20];
	strcpy(str,(char*) shmat(shmid,(void*)0,0)); 

	char strr[20];

	int j=strlen(str)-1;
	//printf("%d", j+1);
	printf("Data read from memory: %s\n",str);
	printf("Reverse of Data: ");
	strr[j+1]='\0';
	for(int i=0; i<strlen(str); i++){
		strr[j]=str[i];
		j--;
	}

	printf("%s\n",strr);

	if(strcmp(strr,str)==0)
		printf("it is a palindrome\n");
	else
		printf("it is not a palindrome\n");
	//detach from shared memory  
	shmdt(str); 
	
	// destroy the shared memory 
	//when you detach from shared memory,it is not destroyed. So, to destroy shmctl() is used. 
	//shmctl(int shmid,IPC_RMID,NULL); 
	shmctl(shmid,IPC_RMID,NULL); 
	
	return 0; 
}