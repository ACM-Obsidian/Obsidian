#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 5010;
char ori[N], proc[N];

int main ()
{
	freopen("brackets.in", "r", stdin);
	freopen("brackets.out", "w", stdout);
	gets(ori);
	int len = strlen(ori);
	int lm = -1, rm = -1;
	for (int i = 0; lm == -1 && i < len; i++)
		if (ori[i] == '[') lm = i;
	for (int i = len - 1; rm == -1 && i >= 0; i--)
		if (ori[i] == ']') rm = i;
	int tlen = 0;
	for (int i = 0; i < len; i++)
	{
		if (ori[i] == '(' || ori[i] == ')' ||
			(ori[i] == '[' && i == lm) ||
			(ori[i] == ']' && i == rm))
			proc[tlen++] = ori[i];
	}
	proc[tlen] = 0;
	int st = 0, tmin = 0;
	for (int i = 0; i < tlen; i++)
	{
		if (proc[i] == '(') ++st;
		else if (proc[i] == ')') --st;
		tmin = min(tmin, st);
	}
	if (lm == -1 && rm == -1) // no sq bracket
	{
		if (st || tmin < 0) printf("Impossible\n");
		else printf("%s\n", proc);
	}
	else if (rm != -1 && (lm == -1 || (lm > rm && st >= 0))) // only right sq bracket
	{
		if (st < 0) printf("Impossible\n");
		else
		{
			int Min = 5000, tst = 0;
			for (int i = 0; i < tlen; i++)
			{
				if (proc[i] == '(') ++tst;
				else if (proc[i] == ')') --tst;
				else if (proc[i] == ']') tst -= st;
				Min = min(Min, tst);
			}
			if (Min < 0) printf("Impossible\n");
			else
			{
				for (int i = 0; i < tlen; i++)
				{
					if (proc[i] == '(' || proc[i] == ')') putchar(proc[i]);
					else if (proc[i] == ']') for (int j = 0; j < st; j++) putchar(')');
				}
				printf("\n");
			}
		}
	}
	else if (lm != -1 && (rm == -1 || (lm > rm && st < 0))) // only left sq bracket
	{
		if (st > 0) printf("Impossible\n");
		else
		{
			int Min = 5000, tst = 0;
			for (int i = 0; i < tlen; i++)
			{
				if (proc[i] == '(') ++tst;
				else if (proc[i] == ')') --tst;
				else if (proc[i] == '[') tst -= st;
				Min = min(Min, tst);
			}
			if (Min < 0) printf("Impossible\n");
			else
			{
				for (int i = 0; i < tlen; i++)
				{
					if (proc[i] == '(' || proc[i] == ')') putchar(proc[i]);
					else if (proc[i] == '[') for (int j = 0; j < -st; j++) putchar('(');
				}
				printf("\n");
			}
		}
	}
	else // both brackets
	{
		int Min = 5000, nmin, tst = 0;
		for (int i = 0; i < tlen; i++)
		{
			if (proc[i] == '(') ++tst;
			else if (proc[i] == ')') --tst;
			Min = min(Min, tst);
			if (proc[i] == ']') nmin = Min;
		}
		int ll = 0;
		ll = max(max(-nmin, -st), 0);
		int rr = ll + st;
		Min = 5000, tst = 0;
		for (int i = 0; i < tlen; i++)
		{
			if (proc[i] == '(') ++tst;
			else if (proc[i] == ')') --tst;
			else if (proc[i] == '[') tst += ll;
			else if (proc[i] == ']') tst -= rr;
			Min = min(Min, tst);
		}
		if (Min < 0) printf("Impossible\n");
		else
		{
			for (int i = 0; i < tlen; i++)
			{
				if (proc[i] == '(' || proc[i] == ')') putchar(proc[i]);
				else if (proc[i] == '[')
				{
					for (int i = 0; i < ll; i++) putchar('(');
				}
				else if (proc[i] == ']')
				{
					for (int i = 0; i < rr; i++) putchar(')');
				}
			}
			printf("\n");
		}
	}
	return 0;
}
