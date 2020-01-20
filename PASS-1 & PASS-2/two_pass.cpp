#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <queue>
using namespace std;

struct code
{
	string mnemo;
	int opcode;
	string type;
}cd[25];

struct LITAB
{
	int srno;
	string lname;
	int addr;
}lt[25];


struct SYMTAB
{
	int srno, addr;
	string symName;
}sym[25];


void init()
{
  fstream literal,symbol,fout,fin;
  fin.open("final.txt",ios::in);
  literal.open("Literal.txt",ios::in);
  symbol.open("symbol.txt",ios::in);
  fout.open("machine.txt",ios::out);
  
  for(int i=0;i<25;i++)
  {
    fin>> cd[i].mnemo>> cd[i].opcode>> cd[i].type;
  }
   for(int i=0;i<25;i++)
  {
    symbol>> sym[i].srno>> sym[i].symName>> sym[i].addr;
  }
   for(int i=0;i<25;i++)
  {
    literal>> lt[i].srno>> l[i].lname>> lt[i].addr;
  }
  
  //disp[lay
    for(int i=0;i<25;i++)
  {
   cout<< cd[i].mnemo<< cd[i].opcode<< cd[i].type;
  }
   for(int i=0;i<25;i++)
  {
    cout<< sym[i].srno<< sym[i].symName<< sym[i].addr;
  }
   for(int i=0;i<25;i++)
  {
    cout<< lt[i].srno<< lt[i].lname<< lt[i].addr;
  }
}
int main
{
  init();
  return 0;
}

