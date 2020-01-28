#include<iostream>

using namespace std;

int main()
{
  int a[5] = {1,2,3,4,5};
  int sum = 0,fin = 0;
  for(int i = 0;i<5;i++)
  {
    sum = 0;
    for(int j =0;j<=i;j++)
    {
    	sum = sum +a[j];
    }
    fin += sum;
  }
  cout<<fin;
}
