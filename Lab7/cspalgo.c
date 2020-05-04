#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>


//---------------------PETERSON'S ALGORITHM 2 SETUP PRODUCER CONSUMER----------------------

/*

#define N 2

bool flag[2];
int turn;
int x=5;

void * runner1(void * param){
	
	do{
		flag[0]= true;
		turn = 1;

		while(flag[1]==true && turn == 1);
		
		x++;
		printf("Thread 1: %d\n", x);
		fflush(stdout);
		sleep(2);

		flag[0]=false;

		//printf("Thread 1: RS\n");
	} while(true);

	pthread_exit(0);
}

void * runner2(void * param){
	
	do{
		flag[1]= true;
		turn = 0;

		while(flag[0]==true && turn == 0);
		
		x--;
		printf("Thread 2: %d\n", x);
		fflush(stdout);
		sleep(2);

		flag[1]=false;

		//printf("Thread 2: RS\n");
	} while(true);

	pthread_exit(0);

}

int main(){

	pthread_t tid[N];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_create(&tid[0], &attr, runner1, NULL);
	pthread_create(&tid[1], &attr, runner2, NULL);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	return 0;
}

*/


//---------------------PETERSON'S ALGORITHM N SETUP----------------------

/*

#define N 4

struct data{
	int i;
};

bool Key;
int x=5;
bool lock = false;
bool waiting[N];

bool test_set(bool * target){
	bool rv = *target;
	*target = true;

	return rv;
}

void * runneri(void * param){
	
	struct data *d = (struct data *)param;
	int j;

	do{
		waiting[d->i] = true;
		Key = true;

		while(waiting[d->i]==true && Key == true)
		
			Key = test_set(&lock);
		
		if(d->i % 2 == 0)
			x++;
		else
			x--;

		printf("Thread %d: CS %d\n", d->i, x);
		fflush(stdout);
		sleep(1);

		waiting[d->i]=false;

		j = (d->i + 1) %N;

		while(j!=d->i && waiting[j]==false)
			j = (j+1) %N;

		if(j==d->i)
			lock=false;
		else
			waiting[j]=false;

	} while(true);

	pthread_exit(0);
}

int main(){

	pthread_t tid[N];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	struct data d[N];
	for(int i=0; i<N; i++){
		
		d[i].i = i;
		pthread_create(&tid[i], &attr, runneri, &d[i]);
	}

	for(int i=0; i<N; i++)
		pthread_join(tid[i], NULL);
	

	return 0;
}


*/

//---------------------DEKKER'S ALGORITHM 2 SETUP PRODUCER CONSUMER----------------------

/*

#define N 2

bool flag[2];
int turn;
int x=5;

void * runner1(void * param){
	
	do{
		flag[0]= true;
		
		if(turn == 1){
			flag[0] = false;
			while(turn==1);
			flag[0] = true;
		}

		x++;
		printf("Thread 1: %d\n", x);
		fflush(stdout);
		sleep(2);

		turn =1;
		flag[0]= false;

	} while(true);

	pthread_exit(0);
}

void * runner2(void * param){
	
	do{
		flag[1]= true;
		
		if(turn == 0){
			flag[1] = false;
			while(turn==0);
			flag[1] = true;
		}

		x--;
		printf("Thread 2: %d\n", x);
		fflush(stdout);
		sleep(2);

		turn =0;
		flag[1]= false;
		

	} while(true);

	pthread_exit(0);
}


int main(){

	pthread_t tid[N];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_create(&tid[0], &attr, runner1, NULL);
	pthread_create(&tid[1], &attr, runner2, NULL);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	return 0;
}

*/

//---------------------DEKKER'S ALGORITHM N SETUP----------------------

/*

#define N 4

bool flag[N];
int turn;
int x=5;

struct data{
	int i;
};

void * runneri(void * param){
	
	struct data *v = (struct data *)param;
	
	do{
		flag[v->i]= true;
		
		if(turn != v->i){
			flag[v->i] = false;
			while(turn != v->i);
			flag[v->i] = true;
		}
			
		printf("Thread %d ", v->i);
		if((v->i) %2 ==0)
			x++;
		else
			x--;
		
		printf("--> %d\n", x);
		
		sleep(1);

		
		fflush(stdout);

		turn = ((v->i) +1) %N;
		flag[v->i]= false;

	} while(true);

	pthread_exit(0);
}

int main(){


	pthread_t tid[N];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	struct data d[N];
	for(int i=0; i<N; i++){
		d[i].i = i;
		pthread_create(&tid[i], &attr, runneri, &d[i]);
	}

	for(int i=0; i<N; i++)
		pthread_join(tid[i], NULL);
	

	return 0;
}


*/


//---------------------DIJKSTRA'S ALGORITHM N SETUP PRODUCER CONSUMER----------------------
/*

#define N 4


struct data{
	int i;
};

bool interested[2];
bool passed[2];
int k;
int flag = 1;
int x=5;

void * runneri(void * param){

	struct data *v =(struct data *)param;

	bool done;
	do{

		while(flag == 0);
		interested[v->i]=true;
		do{

			

			while(k!= v->i){
				if(interested[k]==false)
					k=v->i;	//kth Thread is not interested in entering cs then i will take the lock
			}
			flag =1;
			passed[v->i] = true;	//going to pass inside CS
			done = true;
			for(int j=0; j<N; j++){
				if(j!= v->i)
					if(passed[j]==true){	//if there is already a Thread which has entered CS
						passed[v->i]=false;	//pass value is false since you cannot enter cs 
						done=false;	//not done yet
					}
			}
		} while(done==false);

		if(v->i %2 ==0)
			x++;
		else
			x--;

		printf("Thread %d: -> %d\n",v->i, x);
		fflush(stdout);
		sleep(1);

		passed[v->i] = false;
		interested[v->i] = false;

		flag = 0;

	} while(true);
	pthread_exit(0);
}


int main(){


	pthread_t tid[N];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	struct data d[N];
	for(int i=0; i<N; i++){
		d[i].i = i;
		pthread_create(&tid[i], &attr, runneri, &d[i]);
	}

	for(int i=0; i<N; i++)
		pthread_join(tid[i], NULL);
	

	return 0;
}

*/
//---------------------SEMAPHORES PRODUCER CONSUMER----------------------

/*


#define N 2

int x=5;
int flag=1;

sem_t mutex;

struct data{
	int i;
};

void * runneri(void * param){
	
	struct data *d = (struct data *)param;
	do{
		while(flag ==0);
		sem_wait(&mutex);

		flag=1;
		
		if(d->i % 2 == 0)
			x++;
		else
			x--;

		printf("Thread %d: CS %d\n", d->i, x);
		fflush(stdout);
		sleep(1);

		sem_post(&mutex);

		flag=0;

	} while(true);

	pthread_exit(0);
}

int main(){

	pthread_t tid[N];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	sem_init(&mutex, 0, 1);
	struct data d[N];
	for(int i=0; i<N; i++){
		
		d[i].i = i;
		pthread_create(&tid[i], &attr, runneri, &d[i]);
	}

	for(int i=0; i<N; i++)
		pthread_join(tid[i], NULL);
	

	return 0;
}

*/


//---------------------SEMAPHORES Barber Shop Problem----------------------


#define n 5			//no. of chairs

struct id{
	int i;
};

sem_t customer; 	//Counts waiting customers
sem_t barber;		//Barber is busy or not(sleeping)
sem_t mutex;		

//time_t end_time;	//Closing Time of Barber Shop
int threadcount = 0;
int customeri = 0;

void cut_hair(){	//barber cutting hair
	sleep(3);
}

void get_haircut(){	//get haircut for some time
	sleep(2);
}

void * barbers(){

	while(true){		//while(time(NULL)<end_time || customeri > 0){
		sem_wait(&customer);	//sleep when there are no waiting customers
		sem_wait(&mutex);	//accessing customers
		customeri -=1;
		printf("Barber: Cut Hair, Waiting Customers: %d\n", customeri);
		
		sem_post(&mutex);	//Release waiting
		sem_post(&barber);	//Barber ready to cut hair
		
		printf("Barber cutting Hair\n\n");
		cut_hair();
		if(customeri == 0){
			printf("Barber Sleeping\n");
			if(threadcount== n+2){
				printf("BarberShop Closed!\n");
				break;
			}
		}
		
	}

	pthread_exit(0);
}

void * customers(void * param){
	threadcount++;
	//while (true){			//while (time(NULL) < end_time){
		sem_wait(&mutex);
		// printf("\n\n customer %d Enters \n", d->i);
		if(customeri <n){
			if(customeri == 0){
				printf("Barber Sleeping\nBarber Wakes Up!\n\n");
			}
			customeri += 1;
			printf("Customer: Number of Waiting Customers %d\n", customeri);
			sem_post(&mutex);
			sem_post(&customer);
			sem_wait(&barber);	//wait for barber to be free;

			printf("Customer getting haircut\n");
			get_haircut();

		}
		else{	//all chairs are occupied so leave
			printf("\nChairs are occupied, Leave\n");
			sem_post(&mutex);
			//sem_post(&mutex);
		}
	//}
	pthread_exit(0);
}



int main(){

	sem_init(&mutex, 0, 1);
	sem_init(&customer, 0, 0);
	sem_init(&barber, 0, 1);

	//end_time = time(NULL) + 30;

	pthread_t tidc[n+2], tidb;
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_create(&tidb, &attr, barbers, NULL);
	for(int i=0; i<n+2; i++){
		pthread_create(&tidc[i], &attr, customers, NULL);
		sleep(1);
	}
	
	
	pthread_join(tidb, NULL);
	for(int i=0; i<n+2; i++)
		pthread_join(tidc[i],NULL);
	

	return 0;
}

