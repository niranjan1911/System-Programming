#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <cstring>
#include<vector>

using namespace std;

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
  int id;
  string clas;
};
void init(vector <string> kw)
{
  fstream key;
  key.open("keyword.txt",ios::in);
	
	string str;
   	while(getline(key,str))
   	{
		kw.push_back(str);
   	}
   	key.close();
   	for(int i=0;i<kw.size();i++)
   	{
    	   cout<<kw[i]<<endl;
   	}
}
void wordcheking(string token)
{
   cout<<"fun	"<<token;
}



void performOP(vector <string> kw)
{
	fstream file;
	char ch; 
	string str;
	file.open("code.txt",ios::in);
	if(file==NULL)
	{
	  	  cout<<"\nFile does not exist";
	}
	else
	{
	  //file.get(ch);
		  while(getline(file,str))
		  {
		    //cout<<ch<<endl;
		    //file.get(ch);
		      int n = str.length(); 
	 	      char s[n + 1];
	 	      strcpy(s, str.c_str());	
	   	      char *token = strtok(s," "); 
	   		
	   	        while(token)
	   	        {
	   	          cout<<token<<endl;
	   	          wordcheking(token);
	   	          token = strtok(0," "); 
	   	        }
		  }
	}
}
 
int main()
{
  vector <string> kw;
  init(kw);
  performOP(kw);
  return 0;
}
