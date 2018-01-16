#include "stdafx.h"
#include "Blowfish.h"
#include <string>
using namespace std;

int findPassword(string);
bool caseInsensitiveStringCompare(const string&, const string&);

string users[] = { "root", "admin" };
string passwords[] = { "acc3s$", "isrom0m" };

int authenticate(string user, string pass)
{
	int position = findPassword(user);
	if(position == -1)
		return 0;

	if(pass == passwords[position])
		return 1;
	else
		return 0;
}

int findPassword(string user)
{
	int size = sizeof(users) / sizeof(string);

	for ( int i = 0; i < size; i++ )
	{
		if (caseInsensitiveStringCompare(users[i], user))
			return i;
	}

	return -1;
}

bool caseInsensitiveStringCompare(const string& str1, const string& str2) {
	if (str1.size() != str2.size()) {
		return false;
	}
	for (string::const_iterator c1 = str1.begin(), c2 = str2.begin(); c1 != str1.end(); ++c1, ++c2) {
		if (tolower(*c1) != tolower(*c2)) {
			return false;
		}
	}
	return true;
}