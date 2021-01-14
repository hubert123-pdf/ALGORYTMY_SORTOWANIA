#include <iostream>
#include <algorithm> 
#include <iomanip> 
#include <limits>
using namespace std;

class Proces
{
 	public:
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

bool porownaj(Proces p1, Proces p2) 
{ 
    return p1.arrival_time < p2.arrival_time;
}

bool compareID(Proces p1, Proces p2) 
{  
    return p1.pid < p2.pid;
}
ostream&operator<<(ostream & s,Proces & p)
{
    s<<p.arrival_time<<' '<<p.burst_time<<' ';
    return s;
}
void SJF(Proces* p,int i,int il,int n)
{
        for(int j=0;i+j<n;j++)
        {
            if(p[i+j].arrival_time<p[i-1].completion_time)
            {
                il++;
            }
        }
        for(int j = i; j < i+il+1; j++) 
            {
                if(p[j+1].burst_time<p[j].burst_time)
                {
                    swap(p[j],p[j+1]);
                }
            }
}
int main()
{
    int n;
    cout<<"Podaj ilosc procesow: ";
	cin>>n;
    Proces* p=new Proces[n];
    p[n+1].burst_time=numeric_limits<int>::max();
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    float cpu_utilisation;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;
    float throughput;
    int il=0;

    for(int i = 0; i < n; i++) 
	{

        cout<<"Podaj czas przybycia "<<i+1<<": ";
        cin>>p[i].arrival_time;
        cout<<"Podaj czas trwania "<<i+1<<": ";
        cin>>p[i].burst_time;
        p[i].pid = i+1;
        cout<<endl;
    }

sort(p,p+n,porownaj);

    for(int i = 0; i < n; i++) 
	{
        SJF(p,i,il,n);
        p[i].start_time = (i == 0)?p[i].arrival_time:max(p[i-1].completion_time,p[i].arrival_time);
        p[i].completion_time = p[i].start_time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        p[i].response_time = p[i].start_time - p[i].arrival_time;

        total_turnaround_time += p[i].turnaround_time;
        total_waiting_time += p[i].waiting_time;
        total_response_time += p[i].response_time;
        total_idle_time += (i == 0)?(p[i].arrival_time):(p[i].start_time - p[i-1].completion_time);
        il=0;
    }

    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;
    avg_response_time = (float) total_response_time / n;
    cpu_utilisation = ((p[n-1].completion_time - total_idle_time) / (float) p[n-1].completion_time)*100;
    throughput = float(n) / (p[n-1].completion_time - p[0].arrival_time);


    cout<<endl;
    cout<<"Numer Procesu\t"<<"Czas przyjscia procesu\t"<<"Czas trwania procesu\t"<<"Czas oczekiwania procesu\t"<<endl;

    for(int i = 0; i < n; i++) 
	{
        cout<<"      "<<p[i].pid<<"\t\t\t"<<p[i].arrival_time<<"\t\t\t"<<p[i].burst_time<<"\t\t\t\t"<<p[i].waiting_time<<endl;
    }
    
    cout<<"Sredni czas czekania = "<<avg_waiting_time<<endl;
    delete [] p;
}