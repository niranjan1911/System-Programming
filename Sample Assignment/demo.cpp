#include<iostream>
#include<string.h>
#include <fstream>
#include<string>

using namespace std;
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
int main()
{
  std::ifstream fin("demo.txt");
  std::string str,temp;
  char ch,word[20];
  int flag=0,flag1=0,flag2=0,bit=0,bit1=0,bit2=0,yes=0,stopbit=0;

  
  if(!fin)
  {
   cout<<"Failed to open file";
  }
  else
  {    
   //putting the pointer at the begining of the file
   fin.clear();
   fin.seekg(0,ios::beg);
   
   
   while(std::getline(fin,str))
   {
     cout<<"\n"<<str;
      //Start
      
     if(str.compare("start")==0 && flag==0)
     {
       
       flag=1;
       continue;
     }
     if(flag==0)
     {
      cout<<"\nERROR::Start not found";
      continue;
     }
     //intermidiate
     if(substring(str,"read")==1)
     {
    
       //for space and read spelling
       if(str[0]!='r' || str[1]!='e' || str[2]!='a' || str[3]!='d' || str[4]!=' ')
       {
         flag2=1;
       }
       //for two arguments
      
	       for(int i=5;i<str[i]!='\0';i++)
	       {
		         
		  if(!isalpha(str[i]) && bit1==0) 
			 {
			   
			   
			   flag2=1;
			  
			   continue;
			 }
			 bit1=1;
			 
		       if(str[i]==',')
		       {
			 bit=bit+1;
			 bit2=1;
			 continue;
		       }
		       yes=1;
		       if(!isalpha(str[i]) && bit2==1) 
			 {
			   
			   
			   flag2=1;
			  
			   continue;
			 }
			 bit2=0;
			 
		     if((str[i]>=33 && str[i]<=47) || (str[i]>=58 && str[i]<=64))
			 {
			   flag2=1;
			 }
		}
		if(flag2==1 || bit==0 || bit>1)
		    {
		      cout<<"\nERROR::near ""read"" ";
		      
		     }
	       continue;
       }
       
       //for mover statement
       flag2=0;
       bit=0;
       bit1=0;
       bit2=0;
       
       if(substring(str,"mover")==1)
     {
    
       //for space and spelling of mover statement
       if(str[0]!='m' || str[1]!='o' || str[2]!='v' || str[3]!='e' || str[4]!='r' || str[5]!=' ')
       {
         flag2=1;
       }
       //for two arguments
      
	       for(int i=6;i<str[i]!='\0';i++)
	       {
		         
		  if(!isalpha(str[i]) && bit1==0) 
			 {
			   
			   
			   flag2=1;
			  
			   continue;
			 }
			 bit1=1;
			 
		       if(str[i]==',')
		       {
			 bit=bit+1;
			 bit2=1;
			 continue;
		       }
		       yes=1;
		       if(!isalpha(str[i]) && bit2==1) 
			 {
			   
			   
			   flag2=1;
			  
			   continue;
			 }
			 bit2=0;
			 
		     if((str[i]>=33 && str[i]<=47) || (str[i]>=58 && str[i]<=64))
			 {
			   flag2=1;
			 }
		}
		if(flag2==1 || bit==0 || bit>1)
		    {
		      cout<<"\nERROR::near ""mover"" ";
		      
		     }
	       continue;
       }
    

     //single parameter
      int flag4=0;
     int bit3=0;
     if(substring(str,"print")==1)
     {
       if(str[0]!='p' || str[1]!='r' || str[2]!='i' || str[3]!='n' || str[4]!='t' || str[5]!=' ')
       {
         flag4=1;
       }
       for(int i=6;i<str[i]!='\0';i++)
       {
                 
		 if(!isalpha(str[i]) && bit3==0) 
		 {
		   
		   bit3=1;
		   flag4=1;
		  
		   continue;
		 }
		 bit3=1;
		 if((str[i]>=33 && str[i]<=47) || (str[i]>=58 && str[i]<=64))
		 {
		   flag4=1;
		 }
        }
        if(flag4==1)
	    {
	      cout<<"\nERROR::near ""print"" ";
	      
	     }
       continue;
     }
     //for resq
     int flag3=0;
     int bit2=0;
     
     if(substring(str,"resq")==1)
     {
       if(str[0]!='r' || str[1]!='e' || str[2]!='s' || str[3]!='q' || str[4]!=' ')
       {
         flag3=1;
       }
       for(int i=5;i<str[i]!='\0';i++)
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
	      cout<<"\nERROR::near ""resq"" ";
	      
	     }
       continue;
     }
      //stop
     if(str.compare("stop")==0 && stopbit==0)
     {
       
       stopbit=1;
       continue;
       
     }
      if(stopbit==0)
     {
      cout<<"\nERROR::stop not found";
      
      
     }
     //End
     if(str.compare("end")==0 && flag1==0)
     {
       
       flag1=1;
       
       continue;
     }
   
    
   cout<<"\nERROR::Character after end are not allowed";
   }

   if(flag1==0)
     {
      cout<<"\nERROR::End not found";
      
     }
  } 
  fin.close();
  
   return 0;
}

