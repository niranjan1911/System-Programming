#include<iostream>
#include<string.h>
#include <fstream>
#include<string>
#include <bits/stdc++.h> 

using namespace std;
typedef struct symbol
{
  int id;
  string name;
  int address;
  int length;
}s;
struct literal
{
  int id;
  string lit;
  int address;
};
struct pool
{
  string literal;
};
struct tii
{
  int address;
  string name;
};

struct code
{
	string mnemo;
	int opcode;
	string type;
}cd;

void init(struct code cd[])
{
	fstream fout;
	fout.open("mnemonic.txt", ios::in);
	
	int rc = 0;
   	while(!fout.eof())
   	{
		fout >> cd[rc].mnemo >> cd[rc].opcode >> cd[rc].type;
		rc++;
   	}
   	fout.close();
}



//check if special sybmol or not
int isspecial(char c)
{
        int ch=c;
      
	if((ch>=33 && ch<=47) || (ch>=58 && ch<=64))
	{
	   return 1;
        }
        return 0;
}
//substring
int substring(string str,string sub)
{
  size_t found = str.find(sub);
  if (found != string::npos) 
  {
        return 1;
  }
  else
  {
   return 0;
  } 
}
//is keyword function
int iskeyword(string str)
{
  for(int i=0;i<5;i++)
  {
    if(str.compare(ad[i])==0)
    {
      return 1;
    }
  }
  for(int i=0;i<11;i++)
  {
    if(str.compare(is[i])==0)
    {
      return 1;
    }
  }
  for(int i=0;i<2;i++)
  {
    if(str.compare(ds[i])==0)
    {
      return 1;
    }
  }
  return 0;
}
//is number
int isconstant(string str)
{
   for(int i=0;str[i]!='\0';i++)
   {
	    if(!isdigit(str[i]))
	    {
	      return 0;
	    }
   }
  return 1; 
}

//is literal
int isliteral(string str)
{
  int i;
  for(i=0;str[i]!='\0';i++){}
  i--;
  if(str[0]==61 && str[1]==39 && str[i]==39)
  {
    return 1;
   }
}


int main()
{
  std::fstream fin("demo.txt");
  std::fstream fout("im.txt",std::fstream::out);
  std::fstream mn("mnemonic.txt",std::fstream::out);
  std::string str,abc=" ",word,prv;

  struct code s[20];
  init(s);
  char ch;
 
   
  if(!fin)
  {
          cout<<"Failed to open file";
  }
  else
  {    
	   //putting the pointer at the begining of the file
	   fin.clear();
	   fin.seekg(0,ios::beg);
	  
	   //by line
	   while(std::getline(fin,str))
	   {
	     
	     
	     cout<<"line:"<<str<<"\n";
	     int n=str.length();
	     char s[n+1];
	     strcpy(s,str.c_str());
	     char *token=strtok(s,"")
	       
	     //cout<<"line:"<<str<<"]\n";
	    
	     for(int i=0;str[i]!='\0';i++)
	     {
	             
		     if(str[i]==' ' || str[i]=='\t' || str[i]=='\n' || str[i]==',')
		     {
		        ++count;
			word=trim(word);
			cout<<"["<<word<<"]\n";
		
			word="";
			
		     }
		     else
		     {
		     	word += str[i];
		     }
	     }
	     count=0;
	     word="";
	   }
	   
	   
   }

	   
   return 0;
}	



/*
	read a
   loop mover areg,='1'
        sub areg,='1'
        bc gt,loop
        stop
      a ds 1
        end
        */
