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
string is[11]={"read","movem","mover","stop","print","mult","add","sub","div","comp","bc"};
string ad[5]={"start","end","origin","ltorg","equ"};
string ds[2]={"dc","ds"};


int check(string str)
{
    int flag3=0;
     int bit2=0;
   for(int i=0;i<str[i]!='\0';i++)
       {
                 
		 if(!isalpha(str[i]) && bit2==0) 
		 {
		   
		 
		   flag3=1;
		  
		   continue;
		 }
		 bit2=1;
		  if((str[i]>=33 && str[i]<=47) || (str[i]>=58 && str[i]<=64))
		 {
		   flag3=1;
		 }
        }
        if(flag3==1)
	    {
	      return 0;
	     }
	     return 1;
}
//trim
std::string trim(string astring)
{
    std::remove(astring.begin(), astring.end(), ' ');
   
    return astring;
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
  std::string str,abc=" ",word,prv;

  struct symbol s1[20];
  struct pool p[20];
  struct literal l[20];
  struct tii t[20];  
  char ch;
  int bit=0,error=0,lc=0,bit1=1,s=0,count=0,symbolcount=0,vbit=0,moverbit=0,printbit=0,stopbit=0,flag1=0;
  int pcount=0;

  if(!fin)
  {
          cout<<"Failed to open file";
  }
  else
  {    
	   //putting the pointer at the begining of the file
	   fin.clear();
	   fin.seekg(0,ios::beg);
	   bit=0,bit1=0,error=0;
	   int readbit=0,rbit=0;
	   //by line
	   while(std::getline(fin,str))
	   {
	     
	     
	     cout<<"line:"<<str<<"\n";
	     
	     str.append(abc);
	     //cout<<"line:"<<str<<"]\n";
	    
	     for(int i=0;str[i]!='\0';i++)
	     {
	             
		     if(str[i]==' ' || str[i]=='\t' || str[i]=='\n' /*|| str[i]==','*/)
		     {
		        ++count;
			word=trim(word);
			cout<<"["<<word<<"]\n";
		
			if(iskeyword(word))
			{
			  if(str.compare("start") && bit==0)
			  {
			    bit=1;
			    word="";
			    continue;
			  }
			  //stop
			  
			 /* if(str.compare("origin") && bit1==0)
			  {
			    bit1=1;
			    word="";
			    continue;
			  }*/
			  if(str.compare("read") && readbit==0)
			  {
			    readbit=1;
			    //cout<<"read found";
			    word="";
			    continue;
			  }
			  if(str.compare("print") && printbit==0)
			  {
			    printbit=1;
			    //cout<<"read found";
			    word="";
			    continue;
			  }
			   if(str.compare("mover") && moverbit==0)
			  {
			    moverbit=1;
			    //cout<<"read found";
			    word="";
			    continue;
			  }
			  
			  if(str.compare("areg") || str.compare("breg") || str.compare("breg") || str.compare("breg"))
			  {
				rbit=1;
			  }
			   
			}
			else
			{ 
			  //checking for start
			  if(isconstant(word) && bit==1)
			  {
			    lc=atoi(word.c_str());
			    fout<<"    (ad,"<<lc<<")"<<"\n";
			    bit=2;//end of start
			    word="";
			    continue;
			  }
			  
			  if(bit==1 && !isconstant(word))
			  {
			    cout<<"**Error** at start";
			    word="";
			    break;
			  }
			  if(bit==0)
			  {
			    cout<<"**Error** program must start with start";
			    word="";
			    break;
			  }
			  //checking for origin
			  /*if(isconstant(word) && bit1==1)
			  {
			    lc=atoi(word.c_str());
			    fout<<"(ad,"<<lc<<")"<<"\n";
			    bit1=2;//end of origin/
			    word="";
			    continue;
			  }
			  
			  if(bit1==1 && !isconstant(word))
			  {
			    cout<<bit1;
			    cout<<"**Error** at origin";
			    word="";
			    break;
			  }*/
			  //literal
			  /*else if(isliteral(word) && rbit==1)
			  {
			     cout<<"literal found";
			  }*/
			  //variabble
			  if(isliteral(word))
			  {
			    lc++;
			    p[pcount].literal=word;
			    pcount++;
			  }
			  
			  //checking read variable
			   if(printbit==1)
			  {
				   //cout<<"checking for read";
				   cout<<word;
				   int c=check(word);
				   if(c==1)
				   {
				     lc++;
				     fout<<lc<<" (is,09)(s,"<<++s<<")\n";
				     word="";
				      printbit=0;
				     continue;
				     //cout<<"writing complete" ;
				   }
				   else
				   {
				     cout<<"**Error** at print variable:"<<word;
				     word="";
				      printbit=0;
				     break;
				   }
				  
			  } 
			  if(readbit==1)
			  {
				   //cout<<"checking for read";
				   cout<<word;
				   int c=check(word);
				   if(c==1)
				   {
				     lc++;
				     fout<<lc<<" (is,04)(s,"<<++s<<")\n";
				     word="";
				     readbit=0;
				     continue;
				     //cout<<"writing complete" ;
				   }
				   else
				   {
				     cout<<"**Error** at read variable:"<<word;
				     word="";
				     readbit=0;
				     break;
				   }
				   
			  }
			
			  if(!isconstant(word) && !isliteral(word) && count==1)
			  {
			    lc++;
			    for(int i=0;i<20;i++)
			    {
			      if(s1[i].name==word)
			      {
			        s1[i].address=lc;
			      }
			    }
			    cout<<"variable found";
			    s1[symbolcount].id=symbolcount;
			    s1[symbolcount].name=word;
			    s1[symbolcount].address=lc;
			    s1[symbolcount].length=1;
			    fout<<s1[0].address<<"\n";
			    symbolcount++;
			    
			   
			    
			    vbit=1;
			  }
			  if(!isconstant(word) && !isliteral(word) && count==4)
			  {
			    for(int i=0;i<20;i++)
			    {
			      if(s1[i].name==word)
			      {
			        //do something
			      }
			    }
			    s1[symbolcount].id=symbolcount;
			    s1[symbolcount].name=word;
			    s1[symbolcount].length=1;
			    symbolcount++;
			    
			  }
			  
			}
			
		
		      
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
  //displaying pool table
  cout<<"\n:POOL TABLE:\n";
   for(int i=0;i<pcount;i++)
   {
     cout<<p[i].literal<<"\n";
   }
   //displaying symbol table
   cout<<"\n:SYMBOL TABLE:\n";
   for(int i=0;i<symbolcount;i++)
   {
     cout<<s1[i].id<<"\t"<<s1[i].name<<"\t"<<s1[i].address<<"\n";
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
