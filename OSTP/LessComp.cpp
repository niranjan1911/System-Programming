#include<iostream>

using namespace std;

struct tape
{
  int cap;
};
void in(int *a,int n)
{
	cout<<"\nEnter the programs:\n";
	for(int i=0;i<n;i++)
	{
	  cin>>a[i];
	}
}

void out(int *a,int n)
{
	cout<<"\nYour programs in sorted manner:\n";
	for(int i=0;i<n;i++)
	{
	  cout<<"-"<<a[i]<<"-\t";
	}
	cout<<"\n";
}
void sort(int *a,int n)
{
   int min;
                for(int i=0;i<n-1;i++)
		{
		  min = i;
		  for(int j=i+1;j<n;j++)
		  {
		    if(a[j]<a[min])
		    {
		      min = j;
		    }   
		  }
		   //swapping
		    int temp = a[min];
		    a[min] = a[i];
		    a[i] = temp;
		}
}
int main()
{
	int *a,n,size;
	cout<<"\nHow much programs:\n";
	cin>>n;
	
	
	a = new int[n];
	
	in(a,n);
	
	cout<<"\nEnter the number of tape:\n";
	cin>>size;
	
	int content[size][n];
	struct tape t[size];
	
	cout<<"\nEnter the size of each Tape:";
		for(int i=0;i<size;i++)
		{
		  cout<<"\nTape "<<i+1<<":";
		  cin>>t[i].cap;
		}
	
	
	
	sort(a,n);
	
	out(a,n);
	
	int count = 0;
	
	//checking for tapes 
	int tid=0, i = 0;
	int temp = n;
	int tapesize[size],c = 0;//size of each tapes after elemets are added
	
		
		 
		  while(i<n)
		  {
		    cout<<"="<<tid<<"="<<endl;
		    if(a[i]<=t[tid].cap)
		    {
			    content[tid][c++] = a[i];
			   
			    t[tid].cap -= a[i];
			    temp--;
			    i++;
		     }
		     if(a[i]>t[tid].cap || i==n-1)
		     {
		       if(a[i]==t[tid].cap)
		       {
		           content[tid][c++] = a[i];
		           t[tid].cap -= a[i];
			   temp--;
			   i++;
		       }
		       
			   tapesize[tid] = c;
			   tid++;
			   c = 0;
		       }
		     }
		    
		
		  
		cout<<"tapesize:";
		for(int i=0;i<size;i++)
		{
		  cout<<"tape "<<i+1<<":";
		  cout<<tapesize[i]<<"\n";
		}
		
	
		
	
	
	//displaying tape contents
	cout<<"\n===Tape contents===\n";
	tid = 0;
		while(tid<size)
		{
			cout<<"\nTape "<<tid+1<<":";
			for(int i=0;i<tapesize[tid];i++)
			{
			  cout<<content[tid][i]<<"\t";
			}
			tid++;
		}
	//MRT caculation
	double sum = 0, fin = 0;
	for(int tid=0;tid<size;tid++)
	{
	  fin = 0;
	  for(int i =0;i<tapesize[tid];i++)
	  {
	     sum = 0;
	     for(int j=0;j<=i;j++)
	     {
	       sum += content[tid][j];
	     }
	     fin += sum;
	  }
	  cout<<"\nMRT for Tape: "<<tid+1<<"\n";
	  cout<<fin/tapesize[tid];
	}
	cout<<"\n";
	return 0;
}
