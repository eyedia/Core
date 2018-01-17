#include "stdafx.h"
#include "Blowfish.h"
#include <string>
#include <vector>
using namespace std;


string EncryptCpp(string plaintext)
{  
 //string plaintext = "ababababccccccccababababccccccccababababccccccccxxx12ababababccccccccababababccccccccababababccccccccxxx12debjyoti";  
  char* plaintextchar = new char[plaintext.length()];
  strcpy(plaintextchar, plaintext.c_str());
  
  int len = ceil((double)plaintext.length() / 8);
  len = len * 8;
  
  unsigned char * tempBuffer = NULL;
  std::vector<unsigned char> realBuffer(len);
  tempBuffer = &realBuffer[0];
  memset(tempBuffer, 0, plaintext.length() + 1);  

  CBlowFish oBlowFish((unsigned char*)"1234567890123456", 16);
  oBlowFish.Encrypt((unsigned char*)plaintextchar, 
                    tempBuffer, len, CBlowFish::ECB);   
    
  char* enchars = new char[len * 2];
  memset(enchars, 0, (len * 2));

  CharStr2HexStr(tempBuffer, enchars, len);
  string enctext(enchars, (len *2));  
  return enctext;
  /*ofstream out1("out1.txt", ios::trunc);
  out1 << entext;
  out1.close();*/
}


string DecryptCpp(string enctext)
{  
 /*string enctext;
  ifstream in("out1.txt");
  in >> enctext;
  cout << enctext << endl;
  in.close();*/
  
  int len = (enctext.length()/2);
  if(len < 8)
	  len = 8;	//-ive scenario

  char* szDataIn = new char[len];
  char* szDataOut = new char[len];
  memset(szDataIn, 0, len);
  memset(szDataOut, 0, len);

  HexStr2CharStr(enctext.c_str(),(unsigned char*)szDataIn, len);

  CBlowFish oBlowFish((unsigned char*)"1234567890123456", 16);
  oBlowFish.Decrypt((unsigned char*)szDataIn, 
                    (unsigned char*)szDataOut, len, CBlowFish::ECB);

  string plaintext(szDataOut, len);
  delete(szDataIn);
  delete(szDataOut);
  return plaintext;
}

