#include <iostream>
#include <fstream>
#include<bits/stdc++.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <cstring>
#include<algorithm>


using namespace std;
int terCNT=0,litCNT=0,symCNT=0,tabCNT=0;
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
struct UST 
{
   string name;
   int pos;
   string type;
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
int indexTER(struct TN ter[],string s)
{	
	for (int i = 0; i < terCNT; ++i)
	{
		if(ter[i].name==s)
		{
			return ter[i].id;
		}
	}
}
int indexSYM(struct SYM sym[],string s)
{
	
	for (int i = 0; i < symCNT; ++i)
	{
		if(sym[i].name==s)
		{
			return sym[i].id;
		}
	}
}
int indexLT(struct LT lit[],string s)
{
	
	for (int i = 0; i < litCNT; ++i)
	{
		if(lit[i].name==s)
		{
			return lit[i].id;
		}
	}
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
	struct UST tab[1000];
	
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
			  				//Symbol/Identifirte table
		  				 	sym[symCNT].id = symCNT;
		  					sym[symCNT++].name = s;
		  				 }
		  				 //UST table
			  			tab[tabCNT].name = s;
				  		tab[tabCNT].pos = indexSYM(sym,s);
				  		tab[tabCNT++].type = "ID";
			  		
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
			  		//Terminal table
	  				ter[terCNT].id = terCNT;
	  				ter[terCNT++].name = "++";
	  			}
	  			//UST table
	  			tab[tabCNT].name = "++";
			  	tab[tabCNT].pos = indexTER(ter,"++");
			  	tab[tabCNT++].type = "TERM";
			  	
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
			  		//Terminal table
	  				ter[terCNT].id = terCNT;
	  				ter[terCNT++].name = "--";
	  			}
	  			//UST table
	  			tab[tabCNT].name = "--";
			  	tab[tabCNT].pos = indexTER(ter,"--");
			  	tab[tabCNT++].type = "TERM";

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
			  		//Terminal table
	  				ter[terCNT].id = terCNT;
	  				ter[terCNT++].name = str;
	  			}
	  			//UST table
	  			tab[tabCNT].name = str;
			  	tab[tabCNT].pos = indexTER(ter,str);
			  	tab[tabCNT++].type = "TERM";
			  		
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
		  				 	
					  		//Literal table
	  				
		  				 	lit[litCNT].id = litCNT;
		  					lit[litCNT++].name = str;
		  				 }
		  				 //UST table
			  			tab[tabCNT].name = str;
					  	tab[tabCNT].pos = indexLT(lit,str);
					  	tab[tabCNT++].type = "LIT";
					  		
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
		  				 	
	  						//Identtifire table
		  				 	sym[symCNT].id = symCNT;
		  					sym[symCNT++].name = str;
		  				 }
		  			     //UST table
		  			     tab[tabCNT].name = str;
			  		     tab[tabCNT].pos = indexSYM(sym,str);
			  		     tab[tabCNT++].type = "ID";
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
	  				//terminal tbale
	  				ter[terCNT].id = terCNT;
	  				ter[terCNT++].name = ch;
	  			}
	  			//UST table
	  			tab[tabCNT].name = ch;
	  			tab[tabCNT].pos = indexTER(ter,s);
	  			tab[tabCNT++].type = "TERM";
	  			
	  		}

	  		
	  	}
	  	else
	  	{
	  		//if no opearator then stroing char into string
	  		str += ch;
	  	}
	  	
	  	file.get(ch);
	  }
	  //file.seekp(1);
	  //cout<<"==="<<file.get(1)<<"";
	file.close();
	fstream literal,identifire,terminal,ust;
	//opening files
	literal.open("literal.txt",ios::out);
	identifire.open("identifire.txt",ios::out);
	terminal.open("terminal.txt",ios::out);
	ust.open("ust.txt",ios::out);
	
	//displaying terminal table
	cout<<endl;
	cout<<"ID\tName"<<endl;
	for (int i = 0; i < terCNT; ++i)
	{
		cout<<ter[i].id<<"\t"<<ter[i].name<<endl;
		terminal<<ter[i].id<<"\t"<<ter[i].name<<endl;
	}
	//displaying literal table
	cout<<endl;
	cout<<"ID\tName"<<endl;
	for (int i = 0; i < litCNT; ++i)
	{
		cout<<lit[i].id<<"\t"<<lit[i].name<<endl;
		literal<<lit[i].id<<"\t"<<lit[i].name<<endl;
	}
	//displaying symbol table
	cout<<endl;
	cout<<"ID\tName"<<endl;
	for (int i = 0; i < symCNT; ++i)
	{
		cout<<sym[i].id<<"\t"<<sym[i].name<<endl;
		identifire<<sym[i].id<<"\t"<<sym[i].name<<endl;
	}
	//displaying UST table
	cout<<endl;
	cout<<"Name\t\tPosition\t\tClass"<<endl;
	for (int i = 0; i < tabCNT; ++i)
	{
		cout<<tab[i].name<<"\t\t"<<tab[i].pos<<"\t\t"<<tab[i].type<<endl;
		ust<<tab[i].name<<"\t\t"<<tab[i].pos<<"\t\t"<<tab[i].type<<endl;
	}

		  
}	
 
int main()
{
  struct node kw[40];
  init(kw);
  performOP(kw);
  return 0;
}

