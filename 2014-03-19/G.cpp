#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 110;
typedef pair<int, int> pii;
#define CMD first
#define PARA second
pii cmdlist[N];

#define INC first
#define PAID second
pii paylist[N];

// IN: 0, OUT 1, PAY 2

int main ()
{
	int n; while (scanf("%d", &n), n)
	{
		int mc = 0;
		for (int i = 0; i < n; i++)
		{
			char s[10]; int p; scanf("%s %d", s, &p);
			if (strcmp(s, "IN") == 0) cmdlist[mc++] = pii(0, p);
			else if (strcmp(s, "OUT") == 0) cmdlist[mc++] = pii(1, p);
			else if (strcmp(s, "PAY") == 0) cmdlist[mc++] = pii(2, p);
		}
		int inc = 0, mp = 0, mininc = 0, pay = 0;
		bool last_pay = false, first_pay = true;
		for (int i = 0; i < mc; i++)
		{
			if ((cmdlist[i].CMD == 0 || cmdlist[i].CMD == 1) && last_pay)
			{
				last_pay = false;
				if (!first_pay)
				{
					// printf("INS INC = %d, PAY = %d\n", inc, pay);
					paylist[mp++] = pii(inc, pay);
				}
				pay = 0;
			}
			if (cmdlist[i].CMD == 0) inc += cmdlist[i].PARA, first_pay = false;
			else if (cmdlist[i].CMD == 1) inc -= cmdlist[i].PARA, mininc = min(mininc, inc), first_pay = false;
			else if (cmdlist[i].CMD == 2) pay += cmdlist[i].PARA, last_pay = true;
			// printf("AFTER CMD %d: LAST_PAY = %d, FIRST_PAY = %d, INC = %d, MP = %d, MININC = %d, PAY = %d\n", i, last_pay, first_pay, inc, mp, mininc, pay);
		}
		if (mp == 0) printf("SIZE >= %d\n", 1 - mininc);
		else
		{
			bool first = true;
			int iend = 19931005;
			for (int i = 0; i < mp; i++) iend = min(iend, paylist[i].PAID - paylist[i].INC);
			for (int i = 1 - mininc; i <= iend; i++)
			{
				bool ok = true;
				for (int j = 0; ok && j < mp; j++) if (paylist[j].PAID % (i + paylist[j].INC) != 0) ok = false;
				if (ok)
				{
					if (!first) printf(" ");
					printf("%d", i);
					first = false;
				}
			}
			if (first) printf("IMPOSSIBLE");
			printf("\n");
		}
	}
	return 0;
}
