#include <iostream>
#include <fstream>
 #include <stdlib.h>
 #include <sstream>
#include <string>
#include <cstring>
#include <queue>
using namespace std;
int lc = -1;

struct code
{
	string mnemo;
	int opcode;
	string type;
}cd;

struct LITAB
{
	int srno;
	string lname;
	int addr;
}lt;

struct LTR
{
	int srno;
	string lname;
}lit;

struct SYMTAB
{
	int srno, addr;
	string symName;
}sym;

struct TII
{
	int addr;
	string name;
}tii;

void init(struct code cd[])
{
	fstream file2;
	file2.open("mnemonic.txt", ios::in);
	
	int rc = 0;
   	while(!file2.eof())
   	{
		file2 >> cd[rc].mnemo >> cd[rc].opcode >> cd[rc].type;
		rc++;
   	}
   	file2.close();
   
}

int searchMN(char *s, struct code cd[])
{
	for(int i=0;i<25;i++)
	{
		if(cd[i].mnemo == s)
			return i;
	}
	return -1;
}

bool searchSYM(char *s, struct SYMTAB sym[])
{
	for(int i=0;i<20;i++)
	{
		if(sym[i].symName == s)
			return true;
		else
			return false;
	}
}

bool searchTII(char *s, struct TII tii[])
{
	for(int i=0; i<20 ;i++)
	{
		if(tii[i].name == s)
			return true;
		else
			return false;
	}
}

char oper(char *s)
{
	char *p;
	strtol(s, &p, 10);
	
	if(*p)
	{
		if(s[0] == 61)
			return 'L';
		else
			return 'S';
	}
	return 'C';
}

int check(char *s)
{
        int i=0;
	for(i=0;s[i]!='\0';i++){}
         i--;
        if(s[0]==39 && s[i]==39)
        {
          return 1;
        }
        return 0;
}

int isplus(char *s)
{
        int i=0;
	for(i=0;s[i]!='\0';i++)
	{
	   if(s[i] == '+')
	   {
	    return 1; 
	   }
	   if(s[i] == '-')
	   {
	    return 2; 
	   }
	}
	return 0;
}
int find(string s,struct SYMTAB sym[])
{
	for(int i=0;i<20;i++)
	{
		if(sym[i].symName == s)
			return sym[i].addr;
		else
			return -1;
	}
}
  
int searchSYMIND(string s, struct SYMTAB sym[])
{
        cout<<s;
	for(int i=0;i<20;i++)
	{
		if(sym[i].symName == s)
			return i;
		else
			return -1;
	}
}      

void performOP(struct code cd[])
{
	struct LITAB lt[10];
	struct LTR lit[10];
	struct SYMTAB sym[20];
	struct TII tii[10];
	int i = 0, flag = 0, constant = 1, locMN, fl = 0, poolno = 0, poolflag = 0, litflag = 0, count = 0, tiiCNT = 0, symCNT = 0, cflag=0, eflag = 0,oflag = 0, equind = 0, endflag = 0, forpooltab = 1;
	char pool;
	queue <string> q1;
	fstream file, output, literal, fin, symbol, incomplete;
	string line[10];
	int poolTAB[10],poolTABCNT=0;
	
	
	file.open("demo.txt", ios::in);	
   	output.open("output.txt",ios::out);
   	literal.open("Literal.txt",ios::out);
   	 	  	
   	
   	string tp, str;
   	while(getline(file, tp))
   	{
   		int n = tp.length(); 
 		char s[n + 1];
 		strcpy(s, tp.c_str());	
   		char *token = strtok(s," "); 
   	        cout<<tp<<"\n";
   	        
   		while(token) 
	    	{
	    		++count;
	    		line[count] = token;
	    		if(endflag == 1)
	    		{
	    		  cout<<"\n**ERROR** ANY STATEMNT AFTER END IS NOT ALLOWED....\n";
	    		  output<<"\n**ERROR** ANY STATEMNT AFTER END IS NOT ALLOWED....\n";
	    		  break;
	    		}
	    		locMN = searchMN(token, cd); 
	    		if(fl)
	    		{
	    			lc = atoi(token);
	    			fl = 0;
	    		}
	    		if(locMN == 11 || locMN == 13)
	    		{
	    			fl = 1;
	    			if(locMN == 13)
	    			{
	    			  oflag = 1;
	    			}
	    		}
			if(locMN != -1)
			{
				if(token == cd[locMN].mnemo)
				{
					if(cd[locMN].type == "AD")
					{
						if(cd[locMN].mnemo == "LTORG" || cd[locMN].mnemo == "END")
						{
							while(!q1.empty())
							{
								lt[poolno].srno = poolno;
								lt[poolno].lname = q1.front();
								q1.pop();
								lt[poolno].addr = lc++;
								literal << lt[poolno].srno << "\t" <<lt[poolno].lname <<"\t"<<lt[poolno].addr << endl; 
								
								forpooltab--;
								if(forpooltab == 0)
								{
								  poolTAB[poolTABCNT] = poolno;
								  poolTABCNT++;
								}
								poolno++;
								
							}
							forpooltab = 1;
						}
						if(cd[locMN].mnemo == "END")
						{
						  endflag = 1;
						}
						if(cd[locMN].mnemo == "EQU")
						{
						  eflag = 1;
						}
						output <<"("<<cd[locMN].type<<","<<cd[locMN].opcode<<")";
						flag = 1;
					}
					else
					{
						if(flag)
						{	
							if(cd[locMN].type == "R" )
							{
								output<<"  ("<<cd[locMN].opcode<<")";
							}	
							else if(cd[locMN].type == "DL")
							{						
								output<<lc++<<" ("<<cd[locMN].type<<","<<cd[locMN].opcode<<")";
								if(token==cd[locMN].mnemo)
								{
								  cflag=1;
								}
							}
							else
							{
							        output<<lc++<<" ("<<cd[locMN].type<<","<<cd[locMN].opcode<<")";
							}
						}
					}
				}
			}
			else
			{
				if(flag)
				{
					char s = oper(token);
					int ret = check(token);
					if(s == 'C')
					{
					   if(cflag == 1)
					    {
						    lc += atoi(token);
						    //lc--;
						    cflag = 0;
					    }
					}
					if(s == 'C' || ret==1)
					{
					   
					
					  output <<"    ("<<"C"<<","<<token<<")"; 
					}
					else if(s == 'L')
					{
						lit[litflag].lname = token;
						lit[litflag].srno = litflag;
						
						output <<"    ("<<s<<","<<lit[litflag].srno<<")"; 
						litflag++;
						q1.push(token);
					}
					else if(s == 'S')
					{
						if(count == 3 || count == 4 || count == 2)
						{
							bool tflag = false;
							tflag = searchSYM(token, sym);
							if(!tflag)
							{
							      if(!isplus(token))
							      {
								tii[tiiCNT].name = token;
								tii[tiiCNT].addr = lc;
								tiiCNT++;
							      }
								output << "    "<<token<<" ";
							}
							else
							{
							        output << "    "<<token<<" ";
							}
						}
						else
						{
							bool sflag = false;
							sflag = searchSYM(token, sym);
							if(!sflag)
							{
							        equind =symCNT;
								sym[symCNT].srno = symCNT;
								sym[symCNT].addr = lc;
								sym[symCNT].symName = token;
								symCNT++;
								 
								//output <<lc<< "    "<<token<<" ";
							}
							else
							{
								cout<<"\n**ERROR** DUPLICATE DECLARTION OF VARIABLE:"<<token<<endl;
							      output<<"\n**ERROR** DUPLICATE DECLARTION OFVARIABLE:"<<token<<endl;
								break;
							}
						}
						/*if(count == 1)
						{
						   int DUPLIflag = searchSYM(token, sym);
						   if(DUPLIflag == 1)
						   {
						      cout<<"\n**ERROR** DUPLICATE DECLARTION OF VARIABLE : "<<token;
						      output<<"\n**ERROR** DUPLICATE DECLARTION OF VARIABLE : "<<token;
						   }
						   DUPLIflag = 0;
						}*/
						
					}
					if(isplus(token) && eflag == 1)
					{
					          int plusorminus = isplus(token);
						  int flagplus = 0;
						  char *s;
						  string a,b;
						  s = token;
						  for(int i=0;s[i]!='\0';i++)
						  {
							    if(s[i] == '+')
							    {
							      flagplus = 1; 
							      continue;
							    }
							    if(flagplus == 0)
							    {
							      a += s[i];
							    }
							    else
							    {
							      b += s[i];
							    }
							   
						  }
						 // cout<<a<<"\n"<<b<<"\n";
						  
						  int address = find(a, sym);
						 // int constant = stoi(b);
						  int constant;
						  std::istringstream(b) >> constant;
						  
						  //cout<<address + constant<<"\n";
						  
						  string equstr = line[1];
						  
						  //cout<<equstr;
						  
						  if(plusorminus == 1)
						  {
							  sym[equind].addr = address + constant;
						  }
						  if(plusorminus == 2)
						  {
							  sym[equind].addr = address - constant;
						  }
						  
						  eflag = 0;
					  
					}
					if(isplus(token) && oflag == 1)
					{
					          int plusorminus = isplus(token);
						  int flagplus = 0;
						  char *s;
						  string a,b;
						  s = token;
						  for(int i=0;s[i]!='\0';i++)
						  {
							    if(s[i] == '+')
							    {
							      flagplus = 1; 
							      continue;
							    }
							    if(flagplus == 0)
							    {
							      a += s[i];
							    }
							    else
							    {
							      b += s[i];
							    }
							   
						  }
						 // cout<<a<<"\n"<<b<<"\n";
						  
						  int address = find(a, sym);
						 // int constant = stoi(b);
						  int constant;
						  std::istringstream(b) >> constant;
						  
						  if(plusorminus == 1)
						  {
							  lc = address + constant;
						  }
						  if(plusorminus == 2)
						  {
							  lc = address - constant;
						  }
						  
						  
						  oflag = 0;
					  
					}
					else if(eflag == 1)
					{
					  char s = oper(token);
					  if(s == 'C')
					  {
					      string equstr = line[1];
					      int constant = atoi(token);
					      sym[equind].addr = constant;
					  } 
					}
					
					s = '\0';
				}
				else
				{
					cout<<"\n**ERROR** PROGRAN MUST START WITH START";
					output<<"\n**ERROR** PROGRAN MUST START WITH START";
					break;
				}	
			}
			
			token = strtok(0, " ,"); 
	    	}
	    	count = 0;
	    	output<<endl;
	    	
	 
	}
	output.close();
	
	output.open("output.txt",ios::out | ios::in);
	fin.open("final.txt",ios::out );
	bool data;
	
	while(getline(output, str))
	{
		int n = str.length(), fla = 0; 
 		char s[n];
 		strcpy(s, str.c_str());	
   		char *token = strtok(s," ");
   		
   		while(token)
   		{
   			for(int i=0;i<symCNT;i++)
			{	
				if(token == sym[i].symName)
				{
					fin << " ("<<'S'<<","<<sym[i].srno<<")  ";
					fla = 1;
				}
			}
			if(!fla)
				fin << " " << token;
			token = strtok(0, " ");	
   		}
   		fin << endl;	 	
	}
	fin.close();
	output.close();
	//remove("output.txt");
	file.close();
	literal.close();
	
	
	symbol.open("symbol.txt",ios::out);
	incomplete.open("incomplete.txt",ios::out); 
	//Symbol table
	cout<<"\n\nSymbol table:\n";
	cout<<"ID\tName\tAddress\n";
	for(int i=0;i<symCNT;i++)
	{
	  cout<<sym[i].srno<<"\t"<<sym[i].symName<<"\t"<<sym[i].addr<<"\n";
	  symbol<<sym[i].srno<<"\t"<<sym[i].symName<<"\t"<<sym[i].addr<<"\n";
	}
	//literal table table
	cout<<"\nLiteral table:\n";
	cout<<"ID\tName\tAddress\n";
	for(int i=0;i<poolno;i++)
	{
	  cout<<lt[i].srno<<"\t"<<lt[i].lname<<"\t"<<lt[i].addr<<"\n";
	}
	
	cout<<"\nTII table:\n";
	cout<<"ID\tName\n";
	for(int i=0;i<tiiCNT;i++)
	{
	  cout<<tii[i].addr<<"\t"<<tii[i].name<<"\n";
	  incomplete<<tii[i].addr<<"\t"<<tii[i].name<<"\n";
	}
	
	cout<<"\nPOOL TABLE:\n";
	cout<<"ID\n";
	for(int i=0;i<poolTABCNT;i++)
	{
	  cout<<"#"<<poolTAB[i]<<"\n";
	}
	
	//ERROR checking for varible declaration
	int ERRORflag = 0,aaa;;
	
	for(int i=0;i<tiiCNT;i++)
	{
	  for(int j=0;j<symCNT;j++)
	  {
	     aaa++;
	     if(tii[i].name == sym[j].symName)
	     {
	        
	        ERRORflag = 1;
	       
	     }
	  }
	  
	  if(ERRORflag == 0)
	  {
	    cout<<"**ERROR** VARIABLE DECLRATION NOT FOUND : "<<tii[i].name<<"\n";
	   // output<<"**ERROR** VARIABLE DECLRATION NOT FOUND : "<<tii[i].name<<"\n";
	    //break;
	  }
	  ERRORflag = 0;
	}
	//cout<<aaa;
	symbol.close();
	incomplete.close();
	
}

int main()
{
	struct code cd[25];
	init(cd);
   	performOP(cd);
}
