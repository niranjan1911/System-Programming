#include<stdio.h>
#include<math.h>
#include<stdlib.h>


int chess[20],count=0,n;

void output()
{
	  printf("\nSolution:%d\n",++count);
	   
	  for(int i=1;i<=n;i++)
	  {
	    for(int j=1;j<=n;j++)
	    {
	      if(chess[i]==j)
	      {
		printf("\tQ");
	      }
	      else
	      {
		printf("\t-");
	      }
	    }
	    printf("\n");
	  }
}

int place(int k,int j)
{
	  for(int i=1;i<=k-1;i++)
	  {
	    if(chess[i]==j || (abs(i-k)==abs(chess[i]-j)))
	       return 0;
	  }
	  return 1;
}

void nqueen(int k,int n)
{
	  for(int i=1;i<=n;i++)
	  {
	    if(place(k,i))
	    {
	      chess[k]=i;
	      if(k==n)
	      {
		printf("\nThe output is:");
		output(n);
	      }
	      else
	      {
		nqueen(k+1,n);
	      }
	    }
	  }
}

int main()
{
  int ch;
  while(1)
  {
	  printf("\nEnter the choice::\n1.No. of queens\n2.Exit\n");
	  scanf("%d",&ch);
	  switch(ch)
	  {
	    case 1:
	            count=0;
		    printf("\nEnter the number of queens:");
		    scanf("%d",&n);
		    nqueen(1,n);
		    break;
	    case 2:
	            return 0;
	    default: 
	            printf("\nYou have entered wrong choice");
	  }
  }
  return 0;
}
