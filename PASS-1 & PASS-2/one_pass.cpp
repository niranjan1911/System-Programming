#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <cstring>
using namespace std;
int lc = -1;

struct code
{
	string mnemo;
	int opcode;
	string type;
}cd;

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

char oper(const char *s)
{
	char *p;
	long converted = strtol(s, &p, 10);
	
	if(*p)
	{
		if(s[0] == 61)
			return 'L';
		else
			return 'S';
	}
		return 'C';
}

void performOP(struct code cd[])
{
	int i = 0, flag = 0, constant = 1, locMN, fl = 0;
	fstream file, output;
	
	file.open("demo.txt", ios::in);	
   	output.open("output.txt",ios::out | ios::in);
   	
   	string tp;
   	while(getline(file, tp))
   	{
   		int n = tp.length(); 
 		char s[n + 1];
 		strcpy(s, tp.c_str());	
   		char *token = strtok(s," "); 
   	
   		while(token) 
	    	{
	    		locMN = searchMN(token, cd); 
	    		if(fl)
	    		{
	    			lc = atoi(token);
	    			fl = 0;
	    		}
	    		if(locMN == 11)
	    			fl = 1;
			if(locMN != -1)
			{
				if(token == cd[locMN].mnemo)
				{
					if(cd[locMN].type == "AD")
					{
						output <<"   ("<<cd[locMN].type<<","<<cd[locMN].opcode<<")";
						flag = 1;
					}
					else
					{
						if(flag)
						{	
							if(cd[locMN].type == "R" || cd[locMN].type == "DL")
							{
							output<<"  ("<<cd[locMN].type<<","<<cd[locMN].opcode<<")";
							}	
							else{						
							output<<lc<<"("<<cd[locMN].type<<","<<cd[locMN].opcode<<")";
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
					output <<"  ("<<s<<","<<atoi(token)<<")";
				}
				else
				{
					output<<"\nProgram must start with AD START";
					//break;
				}	
			}
			token = strtok(0, " ,"); 
	    	}
	    	output<<endl;
	    	lc++;
	}
	file.close();
	output.close();
}

int main()
{
	struct code cd[25];
	init(cd);
   	performOP(cd);
}
