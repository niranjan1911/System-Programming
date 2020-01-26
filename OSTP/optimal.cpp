#include<iostream>

using namespace std;

struct tape
{
  int id;
  int cap;
  int content[];
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

int main()
{
	int *a,n,size,min;
	cout<<"\nHow much programs:\n";
	cin>>n;
	
	cout<<"\nEnter the number of tape:\n";
	cin>>size;
	
	struct tape t[size];
	
	cout<<"\nEnter the size of each Tape:";
	for(int i=0;i<size;i++)
	{
	  cout<<"\nTape "<<i+1<<":";
	  cin>>t[i].cap;
	}
	
	a = new int[n];
	
	in(a,n);
	
	
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
	
	out(a,n);
	
	int count = 0;
	
	//checking for tapes 
	int tid=0, index = 0;
	int temp = n;
	int capacity;
	int tapesize[size],c = 0;//size of each tapes after elemets are added
	while(tid<size)
	{
		while(index<n)	
		{
		  if(a[index] <= t[tid].cap)
		  {
		    t[tid].cap -= a[index];
		    t[tid].content[count++] = a[index];
		    temp--;
		    index++;
		  } 
		  else
		  {
		    cout<<"\nbreaked.....at...."<<a[index]<<"\n";
		    break;
		  }
		  
		}
		//capacity = t[index].cap;
	        if(temp != 0)
		{
		  tid++;
		  tapesize[c++] = count;
		  count = 0;
		}
	}
	
	//displaying tape contents
	cout<<"\n===Tape contents===\n";
	tid = 0;
	while(tid<size)
	{
	        cout<<"\nTape "<<tid+1<<":";
		for(int i=0;i<tapesize[tid];i++)
		{
		  cout<<t[tid].content[i]<<"\t";
		}
		tid++;
	}
	
	cout<<"\n===Tape capacity remaining===\n";
	for(int i=0;i<size;i++)
	{
	   cout<<"\nTape "<<i+1<<":";
	   cout<<t[0].cap;
	}
	cout<<"\n";
	return 0;
	//multitape
}
