//Scheduling Algos

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sstream>
#include<ctime>
#include<algorithm>

using namespace std;

struct fcfs{

	int pid;
	int AT;
	int BT;
	int CT;
	int TAT;
	int WT;
	int check;
} f1[10], f2[10];

int n=4;

class algos{
private:
	int p, a, b, c, t, w;
public:
	void fcfsalg();
	void sjfalg();
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



bool Arrivaltime(fcfs a1, fcfs a2){
	return a1.AT<a2.AT;
}

bool Pidtime(fcfs a1, fcfs a2){
	return a1.pid<a2.pid;
}

void algos::fcfsalg(){

	sort(f1, f1+n, Arrivaltime);

	f1[0].CT = f1[0].AT+f1[0].BT;
	f1[0].TAT=f1[0].CT-f1[0].AT;
	f1[0].WT=f1[0].TAT-f1[0].BT;
	
	for(int i=1; i<n; i++){
		if(f1[i-1].CT >= f1[i].AT)
			f1[i].CT=f1[i-1].CT+f1[i].BT;
		else
			f1[i].CT=f1[i].BT+f1[i].AT;

		f1[i].TAT=f1[i].CT-f1[i].AT;
		f1[i].WT=f1[i].TAT-f1[i].BT;
	}
	
	sort(f1, f1+n, Pidtime);

	for(int i=0; i<n; i++){
		cout<<f1[i].pid<<"\t"<<f1[i].AT<<"\t"<<f1[i].BT<<"\t"<<f1[i].CT<<"\t"<<f1[i].TAT<<"\t"<<f1[i].WT<<"\n";
	}
}

void algos::sjfalg(){

	int k=0;

	sort(f2, f2+n, Arrivaltime);

	f2[0].CT=f2[0].AT+f2[0].BT;
	f2[0].TAT=f2[0].CT-f2[0].AT;
	f2[0].WT=f2[0].TAT-f2[0].BT;
	f2[0].check=1;
	
	
	//int min;
	//int temp_k;
	int pos=-1;

	checkagain:
 	for(int a=1;a<n;a++){
 		
 		if(f2[a].check==0 && f2[a].AT<f2[k].CT){

 			//temp_k=k;
 			pos=-1;
		  	for(int i=0;i<n;i++){
				if(f2[i].check==0 && f2[i].AT<f2[k].CT){
					if(f2[i].BT < f2[pos].BT || pos==-1){
						//min=f2[i].BT;
						pos=i;
					}
						
					
				}
				
		  	}
			if(pos!= -1){
				f2[pos].CT=f2[k].CT+f2[pos].BT;
				//cout<<"ifff2     f2[pos].CT: "<<f2[pos].CT<<" f2[pos].BT: "<<f2[pos].BT<<endl;
				f2[pos].TAT=f2[pos].CT-f2[pos].AT;
				f2[pos].WT=f2[pos].TAT-f2[pos].BT;
				f2[pos].check=1;
				
				//temp_k=pos;
				k=pos;
			}
			
		}
		else if(f2[a].check==0 && f2[a].AT>=f2[k].CT){
				f2[a].CT=f2[a].AT+f2[a].BT;
				k=a;
				//cout<<"ifff1     f2[pos].CT: "<<f2[a].CT<<" f2[pos].BT: "<<f2[a].BT<<endl;
				f2[a].TAT=f2[a].CT-f2[a].AT;
				f2[a].WT=f2[a].TAT-f2[a].BT;
				f2[a].check=1;

			}
	}

	for(int l=0; l<n; l++){
		if(f2[l].check==0)
			goto checkagain;
	}

	sort(f2, f2+n, Pidtime);

	for(int i=0; i<n; i++){
		cout<<f2[i].pid<<"\t"<<f2[i].AT<<"\t"<<f2[i].BT<<"\t"<<f2[i].CT<<"\t"<<f2[i].TAT<<"\t"<<f2[i].WT<<"\n";
	}

}

int main(){

	
	// cout<<"Enter number of processes: ";
	// cin>>n;

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
		//cout<< command_stat<<endl;
		//int testat= system(""); 	//``````````````
		string wordcount = GetStdoutFromCommand("wc -m text"+geek[i]+".txt");
		//cout<<wordcount;
		f1[i].BT= TexttoValue(wordcount);
		
		//cin>>f1[i].AT;

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
		
		
		//cout<<crtime<<endl;

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

		f1[i].AT = (int)creation_time;
	}
	int minat=100000000;
	for(int i=0; i<n; i++){
		if(minat>=f1[i].AT)
			minat=f1[i].AT;
	}

	cout<<minat<<endl;

	for(int i=0; i<n; i++){
		//cout<<"pid: "<<i+1<<"\t";
		

		f1[i].AT=f1[i].AT-minat;
		

		//cout<<"AT: "<<f1[i].AT<<"\t";
		//cout<<f1[i].BT<<"\n";
		f1[i].pid=i+1;
		f2[i].pid=f1[i].pid;
		f2[i].AT=f1[i].AT;
		f2[i].BT=f1[i].BT;
		f2[i].check=0;
	}
	algos obj;
	cout<<"FCFS Algorithm: \n";
	obj.fcfsalg();
	cout<<"SJF Algorithm:\n";
	obj.sjfalg();
	return 0;
}
