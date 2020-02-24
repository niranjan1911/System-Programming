#include <iostream>
#include <fstream>
#include<bits/stdc++.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <cstring>
#include<algorithm>


using namespace std;
int terCNT=0,litCNT=0,symCNT=0;
struct LT
{
  int id;
  string name;
};
struct SYM
{
  int id;
  string name;
};
struct TN
{ 
   int id;
   string name;
};
struct node
{
	string name;
};
void init(struct node kw[])
{
  fstream key;
  key.open("keyword.txt",ios::in);

   int rc=0;
   while(!key.eof())
   	{
		key >> kw[rc].name;
		rc++;
   	}
   	key.close();
   	for(int i=0;i<37;i++)
   	{
    	   cout<<"-"<<kw[i].name<<"-"<<endl;
   	}
}

int isalreadyTN(struct TN ter[],string s)
{
	
	for (int i = 0; i < terCNT; ++i)
	{
		if(ter[i].name==s)
		{
			return 1;
		}
	}
	return 0;
}
int isalreadyLT(struct LT lit[],string s)
{
	
	for (int i = 0; i < litCNT; ++i)
	{
		if(lit[i].name==s)
		{
			return 1;
		}
	}
	return 0;
}
int isalreadySYM(struct SYM sym[],string s)
{
	
	for (int i = 0; i < symCNT; ++i)
	{
		if(sym[i].name==s)
		{
			return 1;
		}
	}
	return 0;
}
int iskeyword(struct node kw[],string str)
{
	for (int i = 0; i < 37; ++i)
	{
		if(kw[i].name==str)
		{

			return 1;
		}
	}
	return 0;
}
int oper(char *s)
{
	char *p;
	strtol(s, &p, 10);
	
	if(*p)
	{
		return 0;
	}
	return 1;
}

void performOP(struct node kw[])
{
	fstream file;
	char ch; 
	int cnt=0,cntstore=0,plusflag=0,minusflag=0,cntstore1=0;
	string str, s;
	int n,flag=0;
	struct TN ter[100];
	struct LT lit[100];
	struct SYM sym[100];
	
	file.open("code.txt",ios::in);
	  //Reading each character from file
	  file.get(ch);
	  while(!file.eof())
	  {
	  		++cnt;
	  		//if tab or line feed then skip 
		  	if(ch == 10 || ch == 9){
		  		file.get(ch);
		  		continue;
		  	}
		  	//if operator found then check for string which is stored
	  	if((ch>=32 && ch<=47) || (ch>=58 && ch<=64) || (ch>=91 && ch<=96) || (ch>=123 && ch<=126))
	  	{
	  		
	  		//within double qoutes
	 		if(flag==1)
	 		{
	 			s = s  + str;
	 			s += " ";
	 			if(ch=='"')
	 			{
	 				cout<<s;
	 				 int chk = isalreadySYM(sym,s);
		  				 if(!chk)
		  				 {
		  				 	sym[symCNT].id = symCNT;
		  					sym[symCNT++].name = s;
		  				 }
	 				flag=0;
	 				s = "";
	 				str = "";
	 				file.get(ch);
	  				continue;
	 			}	
	 		}

	  		if(ch=='"')
	  		{
	  			flag=1;
	  			file.get(ch);
	  			continue;
	  		}
	  		//++ cheking

	  		if((cnt-cntstore==1) && plusflag==1 && ch=='+')
	 		{
	 			int chk = isalreadyTN(ter,"++");
	  			if(!chk)
	  			{
	  				ter[terCNT].id = terCNT;
	  				ter[terCNT++].name = "++";
	  			}
	 			plusflag = 0;
	 			cntstore = 0;
	 		}
	 		else
	 		{
	 			plusflag = 0;
	 			cntstore = 0;
	 		}
	 		if(ch=='+')
	 		{
	 			cntstore = cnt;
	 			plusflag = 1;
	 		}

	 		//minus
	 		if((cnt-cntstore1==1) && minusflag==1 && ch=='-')
	 		{
	 			int chk = isalreadyTN(ter,"--");
	  			if(!chk)
	  			{
	  				ter[terCNT].id = terCNT;
	  				ter[terCNT++].name = "--";
	  			}
	 			minusflag = 0;
	 			cntstore1 = 0;
	 		}
	 		else
	 		{
	 			minusflag = 0;
	 			cntstore1 = 0;
	 		}
	 		if(ch=='-')
	 		{
	 			cntstore1 = cnt;
	 			minusflag = 1;
	 		}
	  		
	  		
	  		//if '.' founf for header and float value then skip
	  		if(ch == '.')
	  		{
	  			str += ch;
	  			file.get(ch);
	  			continue;	
	  		}
	  		//displaying string and operator
	  		
	  		cout<<str<<endl;
	  		cout<<ch<<endl;

	  		char *temp = new char();
	  		strcpy(temp,str.c_str());
	  		//cout<<"after temp"<<temp<<endl;
	  		int c = oper(temp);

	  		//if keyword then push into terminal table
	  		int chky = iskeyword(kw,str);
	  		if(chky)
	  		{
	  			//cout<<"keword found"<<endl;
	  			int chk = isalreadyTN(ter,str);
	  			if(!chk)
	  			{
	  				ter[terCNT].id = terCNT;
	  				ter[terCNT++].name = str;
	  			}
	  		}
	  		else if(c==1)
	  		{
	  			//if string contain number
	  			
	  			if(!str.empty())
	  			{
		  			if(c==1)
		  			{
		  				 int chk = isalreadyLT(lit,str);
		  				 if(!chk)
		  				 {
		  				 	lit[litCNT].id = litCNT;
		  					lit[litCNT++].name = str;
		  				 }
		  			}
	  			}
	  		}
	  		else
	  		{
	  			if(!str.empty() && flag!=1)
	  			{
	  				     int chk = isalreadySYM(sym,str);
		  				 if(!chk)
		  				 {
		  				 	sym[symCNT].id = symCNT;
		  					sym[symCNT++].name = str;
		  				 }
	  			}
	  		}
	  		
	  		 //making string empty after each operator
	  		 str  = "";
	  		//Pushing each operator in terminal table
	  		if(ch!=32)//if no space
	  		{
	  			string s(1,ch);
	  			int chk = isalreadyTN(ter,s);
	  			if(!chk)
	  			{
	  				ter[terCNT].id = terCNT;
	  				ter[terCNT++].name = ch;
	  			}
	  			
	  		}

	  		
	  	}
	  	else
	  	{
	  		//if no opearator then stroing char into string
	  		str += ch;
	  	}
	  	
	  	file.get(ch);
	  }
	file.close();
	//displaying terminal table
	cout<<endl;
	cout<<"ID\tName"<<endl;
	for (int i = 0; i < terCNT; ++i)
	{
		cout<<ter[i].id<<"\t"<<ter[i].name<<endl;
	}
	//displaying literal table
	cout<<endl;
	cout<<"ID\tName"<<endl;
	for (int i = 0; i < litCNT; ++i)
	{
		cout<<lit[i].id<<"\t"<<lit[i].name<<endl;
	}
	//displaying symbol table
	cout<<endl;
	cout<<"ID\tName"<<endl;
	for (int i = 0; i < symCNT; ++i)
	{
		cout<<sym[i].id<<"\t"<<sym[i].name<<endl;
	}

		  
}	
 
int main()
{
  struct node kw[40];
  init(kw);
  performOP(kw);
  return 0;
}
