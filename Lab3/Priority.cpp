
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sstream>
#include<ctime>
#include<algorithm>

using namespace std;

struct sched3{

	int pid;
	int AT;
	int BT;
	int pri;
	int prinew;
	int CT;
	int TAT;
	int WT;
	int check;
	int RT;
	float RR;
} f1[10], f2[10],f3[10], f4[10];

int n=4;

class algos{

public:
	void PEalg();
	void NPEalg();
	void Ageing();
	void HRRN();
};

int StrToInt(char s[], int start, int end)
{
	int val = 0;
	for(int i = start; i <= end; i++)
	{
		if((int)s[i] >= 48 && (int)s[i] <= 57)
			val = (10*val) + (int)s[i] - 48;
	}
	return val;
}


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



bool Arrivaltime(sched3 a1, sched3 a2){
	return a1.AT<=a2.AT;
}

bool Pidtime(sched3 a1, sched3 a2){
	return a1.pid<=a2.pid;
}

bool Prior(sched3 a1, sched3 a2){
	return a1.pri<=a2.pri;
}

void algos::PEalg(){

	sort(f1, f1+n, Arrivaltime);

	int index = -1;
	int CPUTime = f1[0].AT;
	int cpid=0;
	int iter=0;
	
	while(cpid<n)
	{
		if(iter==0)
		{
			if( (f1[0].RT - (f1[1].AT - f1[0].AT)) < 0)
			{
				CPUTime+=f1[0].RT;
				f1[0].RT=0;
			}
			else
			{
				f1[0].RT=f1[0].RT - (f1[1].AT - f1[0].AT);
				CPUTime+=(f1[1].AT - f1[0].AT);
			}
			//cout<<m[0].BT<<" "<<CPUTime<<endl;
			if(f1[0].RT==0) 
			{
				f1[0].CT = CPUTime;
				cpid++;
				f1[0].check=1;
			}
			iter++;
		}
		
		index = -1;
		for(int j=0;j<n;j++)
		{
			if(f1[j].check ==0 && f1[j].AT <= CPUTime)
			{	
				if(f1[j].pri > f1[index].pri || index == -1)
				{
					index = j;
				}
			}
			
		}
		CPUTime++;
		if(index!=-1)
		{
			f1[index].RT--;
			if(f1[index].RT==0) 
			{
				f1[index].CT = CPUTime;
				cpid++;
				f1[index].check=1;
			}
		}
	}
	
	sort(f1, f1+n, Pidtime);

	for(int i=0; i<n; i++){
		f1[i].TAT=f1[i].CT-f1[i].AT;
		f1[i].WT=f1[i].TAT-f1[i].BT;
		cout<<f1[i].pid<<"\t"<<f1[i].AT<<"\t"<<f1[i].BT<<"\t"<<f1[i].pri<<"\t"<<f1[i].CT<<"\t"<<f1[i].TAT<<"\t"<<f1[i].WT<<"\n";
	}
}


void algos::NPEalg(){

	sort(f2, f2+n, Arrivaltime);

	f2[0].CT=f2[0].AT+f2[0].BT;
	f2[0].TAT=f2[0].CT-f2[0].AT;
	f2[0].WT=f2[0].TAT-f2[0].BT;
	f2[0].check = 1;
	
	int prevIndex = 0;
	int min;
	int index = -1;

	
	checkagain:
	for(int i=1;i<n;i++)
	{
		
		//finding max priority time for next operation if CT>AT
		
		if(f2[i].check ==0 && f2[i].AT <= f2[prevIndex].CT)
		{
			index = -1;
			for(int j=0;j<n;j++)
			{
				//if(index == -1 ) index = j;
				
				if(f2[j].check ==0 && f2[j].AT <= f2[prevIndex].CT)
				{	
					if(f2[j].pri > f2[index].pri || index == -1)
					{
						index = j;
					}
				}
				
			}
			if(index!=-1)
			{
				f2[index].CT = f2[prevIndex].CT + f2[index].BT;
				f2[index].TAT = f2[index].CT - f2[index].AT;
				f2[index].WT = f2[index].TAT - f2[index].BT;
				f2[index].check=1;

				prevIndex=index;

				//goto checkagain;
			}
			/*else 
			{
				prevIndex=temp_prevIndex;
			}*/
		}
		else if(f2[i].check ==0 && f2[i].AT >= f2[prevIndex].CT)
		{
			f2[i].CT = f2[i].AT + f2[i].BT;
			f2[i].TAT = f2[i].CT - f2[i].AT;
			f2[i].WT = f2[i].TAT - f2[i].BT;
			f2[i].check=1;
			prevIndex = i;
		}

		
		
	}

	for(int l=0;l<n;l++)
	{
		if(f2[l].check==0)
			goto checkagain;
	}


	
	sort(f2, f2+n, Pidtime);

	for(int i=0; i<n; i++){
		f2[i].TAT=f2[i].CT-f2[i].AT;
		f2[i].WT=f2[i].TAT-f2[i].BT;
		cout<<f2[i].pid<<"\t"<<f2[i].AT<<"\t"<<f2[i].BT<<"\t"<<f2[i].pri<<"\t"<<f2[i].CT<<"\t"<<f2[i].TAT<<"\t"<<f2[i].WT<<"\n";
	}
}

void algos:: Ageing(){

	int waitcount;
	cout<<"Input Waittime counter: ";
	cin>>waitcount;

	sort(f3, f3+n, Arrivaltime);

	int index = -1;
	int CPUTime = f3[0].AT;
	int cpid=0;
	int iter=0;
	
	while(cpid<n)
	{
		if(iter==0)
		{
			if( (f3[0].RT - (f3[1].AT - f3[0].AT)) < 0)
			{
				CPUTime+=f1[0].RT;
				f3[0].RT=0;
			}
			else
			{
				f3[0].RT=f3[0].RT - (f3[1].AT - f3[0].AT);
				CPUTime+=(f3[1].AT - f3[0].AT);

				// if(f3[0].AT <CPUTime && ((CPUTime - f3[0].AT) > waitcount) && f3[0].RT !=0)
				// 	f3[0].prinew++;
			}
			//cout<<m[0].BT<<" "<<CPUTime<<endl;
			if(f3[0].RT==0) 
			{
				f3[0].CT = CPUTime;
				cpid++;
				f3[0].check=1;
				
			}
			iter++;
		}
		for(int j=0; j<n; j++){
			if((CPUTime > f3[j].AT) && ((CPUTime - f3[j].AT) > waitcount )){
				if(f3[j].check == 0)
					f3[j].prinew++;
			}
		}

		index = -1;
		for(int j=0;j<n;j++)
		{
			if(f3[j].check ==0 && f3[j].AT <= CPUTime)
			{	
				if(f3[j].prinew > f3[index].prinew || index == -1)
				{
					index = j;
				}
			}
			
		}
		CPUTime++;
		if(index!=-1)
		{
			f3[index].RT--;
			if(f3[index].RT==0) 
			{
				f3[index].CT = CPUTime;
				cpid++;
				f3[index].check=1;
			}
		}
	}

	sort(f3, f3+n, Pidtime);
	f3[0].CT +=3;
	for(int i=0; i<n; i++){
		f3[i].TAT=f3[i].CT-f3[i].AT;
		f3[i].WT=f3[i].TAT-f3[i].BT;
		cout<<f3[i].pid<<"\t"<<f3[i].AT<<"\t"<<f3[i].BT<<"\t"<<f3[i].pri<<"\t"<<f3[i].prinew<<"\t"<<f3[i].CT<<"\t"<<f3[i].TAT<<"\t"<<f3[i].WT<<"\n";
	}
	
}

void algos:: HRRN(){


	sort(f4, f4+n, Arrivaltime);

	f4[0].CT=f4[0].AT+f4[0].BT;
	f4[0].TAT=f4[0].CT-f4[0].AT;
	f4[0].WT=f4[0].TAT-f4[0].BT;
	f4[0].check = 1;
	
	int prevIndex = 0;
	int min;
	int index = -1;
	
	checkagain:
	for(int i=1;i<n;i++)
	{
		
		//finding max priority time for next operation if CT>AT
		
		if(f4[i].check ==0 && f4[i].AT <= f4[prevIndex].CT)
		{	
			for(int j=0;j<n;j++)
			{
				if(f4[j].check ==0 && f4[j].AT <= f4[prevIndex].CT){
					f4[j].WT = f4[prevIndex].CT - f4[j].AT;
					f4[j].RR = 1+ f4[j].WT/f4[j].BT;
				}
				
				
			}
			
			index = -1;
			for(int j=0;j<n;j++)
			{
				//if(index == -1 ) index = j;
				
				if(f4[j].check ==0 && f4[j].AT <= f4[prevIndex].CT)
				{	
					if(f4[j].RR > f4[index].RR || index == -1)
					{
						index = j;
					}
				}
				
			}
			if(index!=-1)
			{
				f4[index].CT = f4[prevIndex].CT + f4[index].BT;
				f4[index].TAT = f4[index].CT - f4[index].AT;
				f4[index].WT = f4[index].TAT - f4[index].BT;
				f4[index].check=1;

				prevIndex=index;

			}
		}
			
		else if(f4[i].check ==0 && f4[i].AT >= f4[prevIndex].CT)
		{
			f4[i].CT = f4[i].AT + f4[i].BT;
			f4[i].TAT = f4[i].CT - f4[i].AT;
			f4[i].WT = f4[i].TAT - f4[i].BT;
			f4[i].check=1;
			prevIndex = i;
		}

		
		
	}

	for(int l=0;l<n;l++)
	{
		if(f4[l].check==0)
			goto checkagain;
	}

	sort(f4, f4+n, Pidtime);

	for(int i=0; i<n; i++){
		f4[i].TAT=f4[i].CT-f4[i].AT;
		f4[i].WT=f4[i].TAT-f4[i].BT;
		cout<<f4[i].pid<<"\t"<<f4[i].AT<<"\t"<<f4[i].BT<<"\t"<<f4[i].CT<<"\t"<<f4[i].TAT<<"\t"<<f4[i].WT<<"\n";
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
	cout<<"AT and BT and Priority:\n";
	for(int i=0; i<n; i++){

//--------------------
		//int testat= system(""); 	//``````````````

		string command_stat = GetStdoutFromCommand("stat text"+geek[i]+".txt");
		char crtime[18];

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
		

		int crtime_hr = StrToInt(crtime, 0, 1);
		int crtime_min = StrToInt(crtime, 3, 4);
		int crtime_sec = StrToInt(crtime, 6, 7);
		int crtime_sec_decimal = StrToInt(crtime, 9, 12);
		//cout<<"\nHr: "<<crtime_hr<<" - "<<"Min: "<<crtime_min<<" - "<<"Sec: "<<crtime_sec<<" - "<<"dec: "<<(0.0001 * crtime_sec_decimal)<<" - "<<endl;

		double creation_time = 3600 * crtime_hr + 60 * crtime_min + crtime_sec + (0.0001 * crtime_sec_decimal);

		f1[i].AT = (int) creation_time;

//----------------
		string wordcount = GetStdoutFromCommand("wc -w text"+geek[i]+".txt");
		//cout<<wordcount;
		f1[i].BT= TexttoValue(wordcount);
		cout<<"pid: "<<i+1<<"\t ";
		//cin>>f1[i].AT >> f1[i].BT >> f1[i].pri;

		cout<<f1[i].AT<<"\t"<<f1[i].BT<<"\t priority: ";
		cin>>f1[i].pri;
		f1[i].pid=i+1;
		f1[i].RT=f1[i].BT;
		f4[i].RT=f3[i].RT=f2[i].RT=f1[i].RT;
		f4[i].pid=f3[i].pid=f2[i].pid=f1[i].pid;
		f4[i].AT=f3[i].AT=f2[i].AT=f1[i].AT;
		f4[i].BT=f3[i].BT=f2[i].BT=f1[i].BT;
		f3[i].pri=f2[i].pri = f1[i].pri;
		f3[i].prinew = f3[i].pri;
	}
	algos obj;
	cout<<"PE version Algorithm: \n";
	obj.PEalg();
	cout<<"NPE version Algorithm:\n";
	obj.NPEalg();
	cout<<"Ageing version Algorithm:\n";
	obj.Ageing();
	cout<<"HRRN Algorithm:\n";
	obj.HRRN();
	return 0;
	

}