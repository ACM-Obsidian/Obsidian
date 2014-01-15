#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <set>
#include <sstream>
using namespace std;

const int N = 100010;

char temp[N], s1[N], s2[N], s3[N];

string rec;
set<string> forb;

int main ()
{
	int kase; for (scanf("%d", &kase), gets(temp); kase; --kase)
	{
		gets(temp);
		rec = string(temp);
		istringstream is(rec);
		forb.clear();
		while (1)
		{
			gets(temp);
			if (strcmp(temp, "what does the fox say?"))
			{
				sscanf(temp, "%s %s %s", s1, s2, s3);
				forb.insert(string(s3));	
			}
			else break;
		}
		bool first = true;
		string word;
		while (is >> word)
		{
			if (forb.find(word) == forb.end())
			{
				if (first) first = false;
				else printf(" ");
				printf("%s", word.c_str());
			}
		}
		printf("\n");
	}
	return 0;
}
