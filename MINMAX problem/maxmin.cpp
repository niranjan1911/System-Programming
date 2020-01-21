#include<iostream>

using namespace std;

void in(int *a,int n)
{
	cout<<"Enter the array elements:\n";
	for(int i=0;i<n;i++)
	{
	  cin>>a[i];
	}
}

void out(int *a,int n)
{
	cout<<"Your array:\n";
	for(int i=0;i<n;i++)
	{
	  cout<<a[i]<<"\t";
	}
	cout<<"\n";
}

int* minmax(int *a,int low,int high)
{	

	  int *temp;
	  temp = new int[2];  
	  
	  if(high == 0)//if only one element is present
	  {
	    temp[0] = a[0];
	    temp[1] = a[0];
	    return temp;
	  }
	  else if(high == 1)//if two elements are present
	  {
	    if(a[0] < a[1])
	    {
	      temp[0] = a[0];
	      temp[1] = a[1];
	      return temp;
	    }
	    else
	    {
	      temp[0] = a[1];
	      temp[1] = a[0];
	      return temp;
	    }
	  }
	  else
	  {
	     int mid = (low + high) / 2;
	     int *Ltemp,*Rtemp,min,max;
	     Ltemp = new int[2];
	     Rtemp = new int[2];
	     
	     Ltemp = minmax(a,low,mid);
	     Rtemp = minmax(a,mid+1,high);
	     
	     //final min
	     if(Ltemp[0] < Rtemp[0])
	     {
	       min = Ltemp[0];
	     }
	     else
	     {
	       min = Rtemp[0];
	     }
	     
	     //final max
	     if(Ltemp[1] < Rtemp[1])
	     {
	       max = Rtemp[1];
	     }
	     else
	     {
	       max = Ltemp[1];
	     }
	    
	     temp[0] = min;
	     temp[1] = max;
	     
	     return temp;
	  }
}
int main()
{
	int n,*a,*output,ch;
	
	while(1) 
	{
	        cout<<"\n1.MINMAX\n2.EXIT\n";
	        cin>>ch;
	        switch(ch)
	        {
			case 1:
				cout<<"Enter the Number of elemnts in array:\n";
				cin>>n;
				//Dynamic memory allocation
				a = new int;
				output = new int[2];

				in(a,n);
				out(a,n);
	
				output = minmax(a,0,n-1);
				cout<<"MIN:"<<output[0]<<"\nMAX:"<<output[1];
				break;
		        case 2:
				return 0;
			default:
				cout<<"You have entered the wrong choice...\n";
		}
	}
	
	return 0;
}
