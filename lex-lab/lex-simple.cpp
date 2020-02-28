#include <iostream>
#include <fstream>
#include<bits/stdc++.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <cstring>
#include<algorithm>


using namespace std;

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
	string str,s,total;
	int n,flag=0;
	
	file.open("code.txt",ios::in);
	  //Reading each character from file
	  file.get(ch);
	  while(!file.eof())
	  {
	  		++cnt;
            total +=ch;
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
	 				//cout<<s;
			  			
	 				 cout<<s<<" is Identifire"<<endl;
			  		
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
			  	cout<<"++"<<" is Terminal"<<endl;
			  	
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
	 			
			  	
	 			cout<<"--"<<" is Terminal"<<endl;

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
	  		
	  		//cout<<str<<endl;
	  		//cout<<ch<<endl;

	  		char *temp = new char();
	  		strcpy(temp,str.c_str());
	  		//cout<<"after temp"<<temp<<endl;
	  		int c = oper(temp);

	  		//if keyword then push into terminal table
	  		int chky = iskeyword(kw,str);
	  		if(chky)
	  		{
	  			//cout<<"keword found"<<endl;
	  		
	  			cout<<str<<" is Terminal"<<endl;
			  		
	  		}
	  		else if(c==1)
	  		{
	  			//if string contain number
	  			
	  			if(!str.empty())
	  			{
		  			if(c==1)
		  			{
		  				 cout<<str<<" is Literal"<<endl;
					  		
		  			}
	  			}
	  		}
	  		else
	  		{
	  			if(!str.empty() && flag!=1)
	  			{
			  		     
	  				     cout<<str<<" is Identifire"<<endl;
	  			}
	  		}
	  		 //making string empty after each operator
	  		 str  = "";
	  		//Pushing each operator in terminal table
	  		if(ch!=32)//if no space
	  		{
	  			cout<<ch<<" is Terminal"<<endl;
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
	fstream literal,identifire,terminal,ust;	  
}	
int main()
{
  struct node kw[40];
  init(kw);
  performOP(kw);
  return 0;
}