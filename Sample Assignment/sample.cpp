#include<iostream>
#include<string.h>
#include <fstream>

using namespace std;
int main()
{
  fstream fin;
  char ch,word[20];
  int space=0,line=0,keyword=0,digit=0,symbol=0,w=0;

  fin.open("sample.txt",ios::in | ios::out);
  if(!fin)
  {
   cout<<"Failed to open file";
  }
  else
  {  
    while(!fin.eof())
   {
	  fin.get(ch);
	     if(isdigit(ch))
	     {
	       digit++;
	     }
	     else if(isalpha(ch))
	     {
	       keyword++;
	     }
	     else if(ch==' ')
	     {
	       space++;
	     }
	     else if(ch=='\n')
	     {
	       line++;
	     }
	     else if((ch>=33 && ch<=47) || (ch>=58 && ch<=64))
	     {
	      symbol++;
	     }
  
   }
   fin.clear();
   fin.seekg(0,ios::beg);
   while(fin>>word)
   {
     w++;
   }
  }
  fin.close();
   cout<<"\nCharacters:"<<keyword;
   cout<<"\nSpaces:"<<space;
   cout<<"\ndigit:"<<digit;
   cout<<"\nWords:"<<w;
   cout<<"\nSpecial Symbol:"<<symbol;
   cout<<"\nLines:"<<line;
   return 0;
}
/*
read b,A
resq a
mover argc,b
print a
stop
