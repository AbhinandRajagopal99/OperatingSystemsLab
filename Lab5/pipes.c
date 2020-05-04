#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>

#include<ctype.h>

#include<math.h>

#define BS 20

int main(){

	//---------------------------Qusetion 1-------------------------
	//Q1:	Test Drive PIPES

	/*
	//Comment Here:
	char wm[BS] = "IIITDM COE2017";
	char rm[BS];

	int fd[2];

	pipe(fd);

	pid_t pid;
	pid = fork();

	if(pid>0){
		close(fd[0]);
		write(fd[1], wm, strlen(wm)+1);
		close(fd[1]);
	}
	else if(pid==0){
		close(fd[1]);
		read(fd[0], rm, BS);
		close(fd[0]);

		printf("child: %s\n", rm);
	}
	*/
	

	/*
	//Comment Here:

	char buf[BS];

	int fd[2];

	pipe(fd);
	pid_t pid;
	pid = fork();
	int nb;
	char *args[] = {"ls", "-o", "-l", NULL};

	if(pid==0){
		dup2(fd[1],1);
		execvp("ls", args);
	}

	else if(pid>0){
		close(fd[1]);
		while((nb= read(fd[0], buf, BS))>0){
			for (int i = 0; i < BS; ++i)
			{
				buf[i] = toupper(buf[i]);
			}
			printf("%s\n", buf);
		}
	}
	
	*/

		
	/*
	//---------------------Question 2--------------------
	//Q2: String Manipulation

	char wm1[BS], wm2[BS];
	char rm1[BS], rm2[BS];

	char cat[40];

	printf("Enter String1: ");
	scanf("%s", wm1);
	printf("Enter String2: ");
	scanf("%s", wm2);

	int fd[2];
	pipe(fd);
	pid_t pid = fork();

	if(pid<0)
		printf("failed to fork\n");
	
	else if(pid==0){
		close(fd[0]);

		write(fd[1], wm1, strlen(wm1)+1);
		write(fd[1], wm2, strlen(wm2)+1);
		write(fd[1], wm1, strlen(wm1));
		write(fd[1], wm2, strlen(wm2)+1);

		close(fd[1]);
	}

	else if(pid>0){
		close(fd[1]);

		read(fd[0], rm1, strlen(wm1)+1);
		read(fd[0], rm2, strlen(wm2)+1);
		read(fd[0], cat, BS+BS);

		close(fd[0]);
		printf("strcpy: %s %s\n", rm1, rm2);

		printf("strcat: %s\n", cat);

		int rm1size= strlen(rm1);
		int rm2size= strlen(rm2);

		
		int diff=0;
		if(rm1size>=rm2size){
			for(int i=0; i<rm1size; i++){
				if(rm1[i]==rm2[i])
					continue;
				else{
					diff=rm1[i]-rm2[i];
					break;
				}
			}
		}

		else{
			for(int i=0; i<rm2size; i++){
				if(rm1[i]==rm2[i])
					continue;
				else{
					diff=rm1[i]-rm2[i];
					break;
				}
			}
		}
		printf("strcmp: %d\n", diff);

		char rm1u[20], rm2u[20];
		char rm1l[20], rm2l[20];

		for(int i=0; i<=rm1size; i++){
			if(rm1[i]>=97 && rm1[i]<=122)
				rm1u[i]= rm1[i]-32;
			else
				rm1u[i] = rm1[i];
		}
		
		for(int i=0; i<=rm2size; i++){
			if(rm2[i]>=97 && rm2[i]<=122)
				rm2u[i]= rm2[i]-32;
			else
				rm2u[i] = rm2[i];
		}

		printf("toupper: %s %s\n", rm1u, rm2u);

		for(int i=0; i<=rm1size; i++){
			if(rm1[i]>=65 && rm1[i]<=90)
				rm1l[i]= rm1[i]+32;
			else
				rm1l[i] = rm1[i];
		}
		
		for(int i=0; i<=rm2size; i++){
			if(rm2[i]>=65 && rm2[i]<=90)
				rm2l[i]= rm2[i]+32;
			else
				rm2l[i] = rm2[i];
		}

		printf("tolower: %s %s\n", rm1l, rm2l);

	}
	
	*/

	/*
	//---------------------Question 3--------------------
	//Q3: Word Count Command

	char wm[BS];
	char rm[BS];

	
	int fd[2];
	pipe(fd);

	FILE *fp;
	
	pid_t pid = fork();

	if(pid<0)
		printf("failed to fork\n");

	else if(pid==0){
		char ch[1];
		close(fd[0]);
		fp= fopen("textwc.txt", "r");

		while(!feof(fp)){
			ch[0] = fgetc(fp);
			write(fd[1], ch, 1);
		}
		fclose(fp);
		close(fd[1]);
	}

	else if(pid>0){
		int nc=0, nw=0, nl=0, ns=0;
		char rec[1];
		close(fd[1]);
		while(read(fd[0], rec, 1)>0){
			nc++;
			//printf("%c-->%d\n", rec[0], nc );
			if(rec[0]=='.')
				ns++;
			if(rec[0]=='\n')
				nl++;
			if(rec[0]==' ' || rec[0] == '\n')
				nw++;
		}
		//printf("%c %d\n", rec[0], rec[0] );
		nw++;
		nc--;

		close(fd[0]);

		printf("wc -c: %d\twc -l: %d\twc -w: %d\t: Sentence count: %d\n", nc, nl, nw, ns);
	}
	*/


	
	//---------------------Question 4--------------------
	//Q4: String Reversal and Palindrome Check Using PIPES

	char wm[BS];
	char rm[BS];

	printf("Enter String: ");
	scanf("%s", wm);

	int fd[2];

	pipe(fd);

	pid_t pid;
	pid = fork();

	if(pid>0){
		close(fd[0]);
		write(fd[1], wm, strlen(wm)+1);
		close(fd[1]);
	}
	else if(pid==0){

		char rmr[BS];

		close(fd[1]);
		read(fd[0], rm, BS);
		close(fd[0]);

		printf("%s\n", rm);
		int j=strlen(rm)-1;
		rmr[j+1]='\0';
		for(int i=0; i<strlen(rm); i++){
			rmr[j] = rm[i];
			j--;
		}
		printf("%s\n", rmr);

		if(strcmp(rmr,rm)==0)
			printf("It is a Palindrome\n");
		else
			printf("It is not a Palindrome\n");
	}
	
	

	
	/*
	//---------------------Question 5--------------------
	//Q5: WC of LS Output:

	int fd[2];

	pipe(fd);
	pid_t pid;
	pid = fork();
	int nw=0, nc=0, nl=0;

	char rec[1];

	char *args[] = {"ls", NULL};

	if(pid==0){
		dup2(fd[1],1);
		execvp("ls", args);
	}

	else if(pid>0){
		close(fd[1]);
		while(read(fd[0], rec, 1)>0){
			nc++;
			printf("%c", rec[0]);
			if(rec[0]=='\n')
				nl++;
			if(rec[0]==' ' || rec[0] == '\n')
				nw++;
		}
		//printf("%c %d\n", rec[0], rec[0] );
		close(fd[0]);

		printf("wc -c: %d\twc -l: %d\twc -w: %d\n", nc, nl, nw);
	}

	*/


	/*
	//---------------------Question 6--------------------
	//Q6: BiDirectional Pipe

	char wmp[BS];
	char rmp[BS];
	char wmc[BS];
	char rmc[BS];

	int fd1[2], fd2[2];

	pipe(fd1);
	pipe(fd2);

	pid_t pid;
	pid = fork();

	if(pid>0){

		printf("Parent Message for Child ");
		scanf("P: %[^\n]", wmp);
		close(fd1[0]);
		close(fd2[1]);
		write(fd1[1], wmp, strlen(wmp)+1);
		read(fd2[0], rmp, BS);
		close(fd1[1]);
		close(fd2[0]);

		printf("Parent Message from Child: %s\n", rmp);
	}
	else if(pid==0){

		printf("and Child Message for Parent Respectively:\n");
		scanf("C: %[^\n]", wmc);
		close(fd1[1]);
		close(fd2[0]);
		read(fd1[0], rmc, BS);
		write(fd2[1], wmc, strlen(wmc)+1);
		close(fd1[0]);
		close(fd2[1]);

		printf("Child Message from Parent: %s\n", rmc);
	}
	
	

	return 0;
}