#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>


int main() 
{ 
    // ftok to generate unique key 
    key_t key = ftok("shmfile",65); 
  
    // shmget returns an identifier in shmid 		//int shmget(key_t,size_tsize,intshmflg);
    int shmid = shmget(key,1024,0666|IPC_CREAT); 
  
    // shmat to attach to shared memory 	
    //void *shmat(int shmid ,void *shmaddr ,int shmflg);
    //shmid is shared memory id. shmaddr specifies specific address to use but we should set it to zero and OS will automatically choose the address.
    char *str = (char*) shmat(shmid,(void*)0,0); 
  
    printf("Write Data : "); 
    scanf("%s",str); 
  
    printf("Data written in memory: %s\n",str); 
      
    //detach from shared memory  	int shmdt(void *shmaddr);
    shmdt(str); 
  
    return 0; 
} 