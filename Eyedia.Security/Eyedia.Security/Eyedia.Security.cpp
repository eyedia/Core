#include "stdafx.h"
#include "Global.h"
#include "Blowfish.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <comdef.h>
#include <atlbase.h>

using namespace std;

int authenticate(string, string);


//extern "C" __declspec(dllexport) LPCTSTR lazeisha(LPCTSTR input)

extern "C" __declspec(dllexport) int Authenticate(const char* user, const char* password)
{
	return authenticate(user, password);
}

extern "C" __declspec(dllexport) BSTR Encrypt(char* plaintext)
{
	string plainstr(plaintext);
	string decstr = EncryptCpp(plainstr);
	BSTR s = ::SysAllocString(CComBSTR(decstr.c_str()));
	return s;
}
TCHAR dllName[MAX_PATH + 1];

std::string getExectablePath() {
  std::vector<char> executablePath(MAX_PATH);

  // Try to get the executable path with a buffer of MAX_PATH characters.
  DWORD result = ::GetModuleFileNameA(
    nullptr, &executablePath[0], static_cast<DWORD>(executablePath.size())
  );

  // As long the function returns the buffer size, it is indicating that the buffer
  // was too small. Keep enlarging the buffer by a factor of 2 until it fits.
  while(result == executablePath.size()) {
    executablePath.resize(executablePath.size() * 2);
    result = ::GetModuleFileNameA(
      nullptr, &executablePath[0], static_cast<DWORD>(executablePath.size())
    );
  }

  // If the function returned 0, something went wrong
  if(result == 0) {
    throw std::runtime_error("GetModuleFileName() failed");
  }

  // We've got the path, construct a standard string from it
  return std::string(executablePath.begin(), executablePath.begin() + result);
}

extern "C" __declspec(dllexport) int IsEqual(char* plaintext, char* enctext)
{
	//GetModuleFileName(NULL, dllName, MAX_PATH);
	/*ofstream out("c:\\temp\\dll.txt", ios::trunc);
	out << getExectablePath();
	out.close();*/
	int plaintextlength = strlen(plaintext);
	int enctextlength = strlen(enctext);

	string plainstr(plaintext, plaintextlength);
	string encstr(enctext, enctextlength);
	string plainstr2 = DecryptCpp(encstr);
	string plainstr2trimmed(plainstr2.c_str());	//easy trim
	return plainstr == plainstr2trimmed ? 1 : 0;
}

/*
extern "C" __declspec(dllexport) int IsEqual(char* plaintext, int plaintextlength, char* enctext, int enctextlength)
{
	//GetModuleFileName(NULL, dllName, MAX_PATH);
	/*ofstream out("c:\\temp\\dll.txt", ios::trunc);
	out << getExectablePath();
	out.close();	
	int len  = strlen(plaintext);
	if(plaintextlength < len)
		plaintextlength = len;

	len  = strlen(enctext);
	if(enctextlength < len)
		enctextlength = len;

	string plainstr(plaintext, plaintextlength);
	string encstr(enctext, enctextlength);
	string plainstr2 = DecryptCpp(encstr);	
	string plainstr2trimmed(plainstr2.c_str());	//easy trim
	return plainstr == plainstr2trimmed ? 1 : 0;
}
*/

/*
We do not want expose this method to outsiders
extern "C" __declspec(dllexport) int Decrypt(char* enctext, int length)
{
	string encstr(enctext, length + 1);
	string plainstr = Decrypt(encstr);
	strcpy(enctext, plainstr.c_str());
	return plainstr.length();
}
*/

