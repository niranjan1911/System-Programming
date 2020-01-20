#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <queue>
using namespace std;
struct symbol
{
  int no;
  string name;
  int addr;
};
 
struct literal
{
  int no;
  string name;
  int addr;
};
struct code
{
   string name;
   int opcode;
   string type;
};

int isnumber(char *s)
{
        
	for(int i = 0;s[i]!='\0';i++)
	{
	  if(!isdigit(s[i]))
	  {
	    return 0;
	  }
	}
	return 1;
}

int searchMN(char *s, struct code cd[])
{
	for(int i=0;i<25;i++)
	{
		if(cd[i].type == s)
			return i;
	}
	return -1;
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

int issame(char *s, char s1)
{
    
      if(s[0] != s1)
      {
         return 0;
      }
    
    return 1; 
}
int main()
{
        struct symbol sym[25];
        struct literal lt[25];
        struct code cd[25];
        fstream symbol,literal,code,mnemo,fout;
	symbol.open("symbol.txt", ios::in);
	literal.open("Literal.txt", ios::in);
	code.open("final.txt", ios::in);
	mnemo.open("mnemonic.txt", ios::in);
	fout.open("machine.txt", ios::out);
	
	//mnemonic
	int c = 0;
	while(!mnemo.eof())
	{
	  mnemo >> cd[c].name >> cd[c].opcode >> cd[c].type;
	  c++;
	}
	mnemo.close();
	
	/*for(int i= 0;i<c-1;i++)
   	{
   	  cout<<cd[i].name<<"\t"<<cd[i].opcode<<"\t"<<cd[i].type<<"\n";
   	}*/
   	
   	
	//Symbol table
	int rc = 0;
   	while(!symbol.eof())
   	{
		symbol >> sym[rc].no >> sym[rc].name >> sym[rc].addr;
		rc++;
   	}
   	symbol.close();
   	
   	/*for(int i= 0;i<rc-1;i++)
   	{
   	  cout<<cd[i].no<<"\t"<<cd[i].name<<"\t"<<cd[i].addr<<"\n";
   	}*/
   	
	//litreal table
	int rc1 = 0;
	while(!literal.eof())
   	{
		literal >> lt[rc1].no >> lt[rc1].name >> lt[rc1].addr;
		rc1++;
   	}
   	literal.close();
   	
   	
   	for(int i= 0;i<rc1-1;i++)
   	{
   	  cout<<lt[i].no<<"\t"<<lt[i].name<<"\t"<<lt[i].addr<<"\n";
   	}
   	
   	string tp, str;
   	int count = 0;
   	
   	fout<<"LC\t"<<"MNEMO\t"<<"REGI\t"<<"MO\n\n";
   	int SLflag = 0,SYMflag = 0, LITflag = 0;
   	while(getline(code, tp))
   	{
   		int n = tp.length(); 
 		char s[n + 1];
 		strcpy(s, tp.c_str());	
   		char *token = strtok(s," ,()");
	      
	        if(substring(tp,"AD"))
	        {
	          fout<<"------------AD--------------\n";
	          continue;
	        }
	        if(substring(tp,"(DL,1)") || substring(tp,"(DL,2)"))
	        {
	          fout<<"------------DL--------------\n";
	          continue;
	        }
	       
	        while(token)
	        {
	          ++count;
	          cout<<"["<<token<<"]\t";
	          
	          if(isnumber(token) && count == 1)
	          {
	            //cout<<"Constant found";
	            fout<<token<<"\t";
	          }
	          
	          //literal
	          if(LITflag == 1)
	          {
	                for(int i= 0;i<rc1-1;i++)
		   	{
		   	  int check = atoi(token);
		   	  if(lt[i].no == check)
		   	  {
		   	     fout<<lt[i].addr;
		   	     cout<<"Addreess of literal";
		   	     LITflag = 0;
		   	  }
		   	}
	          }
	          
	          //symbol
	          if(SYMflag == 1)
	          {
	                for(int i= 0;i<rc-1;i++)
		   	{
		   	  int check = atoi(token);
		   	  if(sym[i].no == check)
		   	  {
		   	     fout<<sym[i].addr;
		   	     cout<<"Addreess of symbol";
		   	     SYMflag = 0;
		   	  }
		   	}
	          }
	          
	          if(!isnumber(token))
	          { 
			  if(issame(token,'S') || issame(token,'L'))
			  {
			    cout<<"SYM:LIT found";
			    SLflag = 1;
			  }
			  if(issame(token,'S'))
			     SYMflag = 1;
			  if(issame(token,'L'))
			     LITflag = 1;
		   }
	          /*if(isflag == 1 && isnumber(token))
	          {
	            fout << token << "'t";
	            isflag = 0;
	          }*/
	          if(isnumber(token) && count != 1 && SLflag == 0)
	          {
	             
	             fout<<token<<"\t";
	             cout<<"number found";
	          }
	          //for a statements which takes only one argument i.e print 
	          if(count == 4 && !isnumber(token))
	          {
	             fout<<"-\t";
	          }
	          
	          
	          token = strtok(0, " ,()");	
	        }
	        //for stop
	        if(count == 3)
	        {
	          fout<<"-\t-";
	        }
	        SLflag = 0;
	       fout<<"\n"; 
	       cout<<"\n";
   	 count = 0;
   	}
   	
   	
  return 0;
}
