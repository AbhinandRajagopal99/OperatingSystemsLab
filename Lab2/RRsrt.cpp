//Scheduling Algos

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sstream>
#include<ctime>
#include<algorithm>

using namespace std;

struct Sch2{

	int pid;
	int AT;
	int BT;
	int CT;
	int TAT;
	int WT;
	int check;
	int RT;
} f1[10], f2[10];

struct Queue{
	int ReadyWait[50];
	int front;
	int rear;
}Q;

int n=4;
int CPUtime=0;

class algos{
private:
	int p, a, b, c, t, w;
public:
	void RRalg();
	void srtalg();
	int RRSearch(int ps);
};



string GetStdoutFromCommand(string cmd) {

string data;
FILE * stream;
const int max_buffer = 256;
char buffer[max_buffer];
cmd.append(" 2>&1");

stream = popen(cmd.c_str(), "r");
if (stream) {
while (!feof(stream))
if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
pclose(stream);
}
return data;
}

int TexttoValue(string var){
	stringstream stlen(var);
	int val;
	stlen >> val;
	return val;
}

int algos::RRSearch(int ps){
	for(int i=0; i<n; i++){
		if(f2[i].pid == ps)
			return i;
	}

}


bool Arrivaltime(Sch2 a1, Sch2 a2){
	return a1.AT<a2.AT;
}

bool Pidtime(Sch2 a1, Sch2 a2){
	return a1.pid<a2.pid;
}

void CheckProcArr(){
	for(int i=0; i<n; i++){
		if(f2[i].AT<=CPUtime && f2[i].RT !=0 && f2[i].check==0){ 
			Q.rear++;
			Q.ReadyWait[Q.rear] = f2[i].pid;
			f2[i].check=1;
			
		}
	}
}

void algos::RRalg(){

	Q.front=-1;
	Q.rear=-1;

	sort(f2, f2+n, Arrivaltime);

	int tq;
	cout<<"Enter Time Quanta: ";
	cin>>tq;

	
	int flag;
	int it=0;
	int k=0;

	while(1){
		flag=1;
		for(int j=0; j<n; j++)
			if(f2[j].RT !=0){
				flag=0;
				break;
			}
		if(flag==1)
			break;

		if(it==0){
			Q.rear++;
			Q.front++;
			Q.ReadyWait[Q.rear]= f2[k].pid;
			f2[k].check = 1;

			CPUtime += f2[k].AT;

			if(f2[k].RT > tq){
				f2[k].RT = f2[k].RT -tq;
				CPUtime += tq;

				CheckProcArr();

				f2[k].check=0;
				Q.front++;
				Q.rear++;

				Q.ReadyWait[Q.rear] = f2[k].pid;
				f2[k].check = 1;

			}
			else{
				CPUtime += f2[k].RT;
				f2[k].RT = 0;
				f2[k].CT = CPUtime;

				CheckProcArr();

				f2[k].check = 0;
				Q.front++;

			}
			it++;

			cout<<"CPU: "<<CPUtime<<": ";
			for(int j=Q.front; j<=Q.rear; j++)
				cout<< Q.ReadyWait[j];
			cout<<endl;

		}
		else{

			k = RRSearch(Q.ReadyWait[Q.front]);
			
			if(f2[k].RT >tq){
				f2[k].RT -= tq;
				CPUtime += tq;

				CheckProcArr();

				f2[k].check =0;
				Q.front++;
				Q.rear++;

				Q.ReadyWait[Q.rear] = f2[k].pid;
				f2[k].check = 1;

			}

			else{
				CPUtime += f2[k].RT;
				f2[k].RT =0;
				f2[k].CT = CPUtime;

				CheckProcArr();

				f2[k].check=0;
				Q.front++;
			}

			cout<<"CPU: "<<CPUtime<<": ";
			for(int j=Q.front; j<=Q.rear; j++)
				cout<< Q.ReadyWait[j];
			cout<<endl;
		}

		if(Q.front > Q.rear){
			Q.rear =-1;
			Q.front =0;

			k=-1;
			for(int i=0; i<n; i++){
				if(f2[i].AT > CPUtime && f2[i].RT!=0 && f2[i].check==0){
					if(k==-1)
						k=i;
					else if(f2[i].AT < f2[k].AT)
						k=i;
				}
			}

			CPUtime = f2[k].AT;

			CheckProcArr();

		}

	}
	/*
	int cpid=0;
	

	CPUtime += f2[0].AT;
	Q.front++;
	Q.rear++;

	if(f2[0].BT <=tq){
		f2[0].CT=f2[0].AT+f2[0].BT;
		f2[0].RT = 0;
		CPUtime = f2[0].CT;
	}
	else{
		Q.ReadyWait[Q.rear]=f2[0].pid;
		f2[0].check=1;

		//f2[0].CT=f2[0].AT+tq;
		f2[0].RT = f2[0].BT - tq;
		// Q.rear++;
		// Q.ReadyWait[Q.rear] = f2[0].pid;

		CPUtime += tq;

		for(int i=0; i<n; i++){
			if(f2[i].AT<=CPUtime && f2[i].RT !=0 && f2[i].check==0){ 
				Q.rear++;
				Q.ReadyWait[Q.rear] = f2[i].pid;
				f2[i].check=1;
				
			}
			cout<<"helloolo: "<<f2[i].pid<<"\t"<<f2[i].AT<<"\t"<<f2[i].BT<<"\t"<<f2[i].CT<<"\t"<<f2[i].TAT<<"\t"<<f2[i].RT<<"\t"<<f2[i].check<<"\n";
		}
		cout<<"CPU: "<<CPUtime<<"    k: "<<k<<":-> ";
		for(int j=Q.front; j<=Q.rear; j++)
				cout<< Q.ReadyWait[j];
			cout<<endl;

		Q.rear++;
		Q.ReadyWait[Q.rear] = f2[0].pid;
		f2[0].check=1;

		Q.front++;


	}

	while(Q.front != -1){
		
		if(Q.front > Q.rear){
			if(cpid==n){
				Q.front=-1;
				Q.rear =-1;
			}
			else{
				int index;
				int mint=10000000;
				for(int i=0; i<n; i++){
					if(f2[i].RT !=0 && mint>=f2[i].AT){
						mint=f2[i].AT;
						index=i;
					}
				}

				CPUtime = f2[index].AT;
				Q.rear++;
				Q.ReadyWait[Q.rear] = f2[index].pid;
				f2[index].check=1;


			}

		}

		else{
			

			for(int i=0; i<n; i++){
				if(f2[i].AT<=CPUtime && f2[i].RT !=0 && f2[i].check==0){ 
					Q.rear++;
					Q.ReadyWait[Q.rear] = f2[i].pid;
					f2[i].check=1;
					
				}
				cout<<"helloolo: "<<f2[i].pid<<"\t"<<f2[i].AT<<"\t"<<f2[i].BT<<"\t"<<f2[i].CT<<"\t"<<f2[i].TAT<<"\t"<<f2[i].RT<<"\t"<<f2[i].check<<"\n";
			}

			k=RRSearch(Q.ReadyWait[Q.front]);
			f2[k].check=1;

			cout<<"CPU: "<<CPUtime<<"    k: "<<k<<":-> ";
			

			if(f2[k].RT >tq){
				f2[k].RT = f2[k].RT - tq;
				CPUtime += tq;
				Q.rear++;
				Q.ReadyWait[Q.rear] = f2[k].pid;
				//Q.front++;
				
			}

			else{
				CPUtime += f2[k].RT;
				cout<<"\nREM: "<<f2[k].pid<<" - "<<f2[k].RT<<endl;
				cpid++;
				f2[k].RT=0;
				f2[k].CT = CPUtime;

				f2[k].check=0;
			}
			Q.front++;
			

			for(int j=Q.front; j<=Q.rear; j++)
				cout<< Q.ReadyWait[j]<<" ";
			cout<<endl;

		}
	}
	*/
	sort(f2, f2+n, Pidtime);

	for(int i=0; i<n; i++){
		f2[i].TAT= f2[i].CT-f2[i].AT;
		f2[i].WT= f2[i].TAT-f2[i].BT;
		cout<<f2[i].pid<<"\t"<<f2[i].AT<<"\t"<<f2[i].BT<<"\t"<<f2[i].CT<<"\t"<<f2[i].TAT<<"\t"<<f2[i].WT<<"\n";
	}
}

void algos::srtalg(){

	int pos=-1;


	sort(f1, f1+n, Arrivaltime);
	int CPUtime = f1[0].AT;
	int cpid=0;
	int itrn=0;

	
	while(cpid<n){

		if(itrn==0){
			if((f1[0].RT + f1[0].AT - f1[1].AT) < 0){
				CPUtime += f1[0].RT;
				f1[0].RT = 0;
			}
			else{
				f1[0].RT= f1[0].RT + (f1[0].AT - f1[1].AT);
				CPUtime += f1[1].AT - f1[0].AT;
			}

			if(f1[0].RT == 0){
				f1[0].CT = CPUtime;
				f1[0].check = 1;
				cpid++;	
			}
			itrn++;
		}

		pos=-1;
		for(int i=0; i<n; i++){
			if(f1[i].check==0 && f1[i].AT <= CPUtime){
				if(f1[i].RT < f1[pos].RT || pos==-1)
					pos=i;
			}
		}

		CPUtime++;
		if(pos != -1){
			f1[pos].RT--;
			if(f1[pos].RT==0){
				f1[pos].CT = CPUtime;
				f1[pos].check = 1;
				cpid++;
			}

		}
		
	}
	
	sort(f1, f1+n, Pidtime);

	for(int i=0; i<n; i++){
		f1[i].TAT=f1[i].CT-f1[i].AT;
		f1[i].WT=f1[i].TAT-f1[i].BT;
		cout<<f1[i].pid<<"\t"<<f1[i].AT<<"\t"<<f1[i].BT<<"\t"<<f1[i].CT<<"\t"<<f1[i].TAT<<"\t"<<f1[i].WT<<"\n";
	}

}

int main(){


	string geek[10];
	for(int i=0; i<n; i++){

		int num=i+1; 
		// declaring output string stream 
		ostringstream str1; 
		// Sending a number as a stream into output 
		str1 << num; 
		geek[i] = str1.str(); 

	}
	cout<<"AT and BT:\n";
	for(int i=0; i<n; i++){

		string command_stat = GetStdoutFromCommand("stat text"+geek[i]+".txt");
		string wordcount = GetStdoutFromCommand("wc -m text"+geek[i]+".txt");
		
		f1[i].BT= TexttoValue(wordcount);
		

		char crtime[19];

		for(int j=0;j<495;j++)
		{
			char check[6];
			check[0] = command_stat[j];
			check[1] = command_stat[j + 1];
			check[2] = command_stat[j + 2];
			check[3] = command_stat[j + 3];
			check[4] = command_stat[j + 4];
			check[5] = command_stat[j + 5];

			check[6] = '\0';

			if(strcmp(check, "Modify") == 0)
			{
				for(int k=j+19; k<j+37; k++)
				{
					crtime[k-j-19] = command_stat[k];
				}
				crtime[18] = '\0';
				break;
			}
		}
		
		

		string crtime1, crtime2, crtime3, crtime4;

		for(int j=0; j<=1; j++){
			crtime1[j]=crtime[j];
			crtime2[j]=crtime[j+3];
			crtime3[j]=crtime[j+6];
		}

		for(int j=0; j<=3; j++)
			crtime4[j]=crtime[j+9];

		int crtime_hr = TexttoValue(crtime1);
		int crtime_min = TexttoValue(crtime2);
		int crtime_sec = TexttoValue(crtime3);
		int crtime_sec_decimal = TexttoValue(crtime4);


		double creation_time = 3600 * crtime_hr + 60 * crtime_min + crtime_sec + (0.0001 * crtime_sec_decimal);

		//---------------USER INPUT OR FILE INPUT-----------------------

		f1[i].AT = (int)creation_time;
		//cin>> f1[i].AT;
		//cin>> f1[i].BT;
		
	}

	int minat=10000000;
	for(int i=0; i<n; i++){
		if(minat>=f1[i].AT)
			minat=f1[i].AT;
	}
	cout<<minat<<endl;

	for(int i=0; i<n; i++){
		

		f1[i].AT=f1[i].AT-minat;
		

		f1[i].pid=i+1;
		f2[i].pid=f1[i].pid;
		f2[i].AT=f1[i].AT;
		f2[i].BT=f1[i].BT;
		f1[i].RT=f1[i].BT;
		f2[i].RT=f1[i].RT;
		f2[i].check=0;
		f1[i].check=0;
	}
	algos obj;
	cout<<"RR Algorithm: \n";
	obj.RRalg();
	cout<<"SRT Algorithm:\n";
	obj.srtalg();
	return 0;
}
