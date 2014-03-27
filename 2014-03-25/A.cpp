#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

inline int encode (const char* sang)
{
	int r1, r2;
	char tt[5];
	strcpy(tt, sang);
	int l = strlen(tt);
	char rh = tt[l - 1];
	tt[l - 1] = 0;

	if (strcmp(tt, "O") == 0) r1 = 0;
	else if (strcmp(tt, "A") == 0) r1 = 2;
	else if (strcmp(tt, "B") == 0) r1 = 4;
	else if (strcmp(tt, "AB") == 0) r1 = 6;

	if (rh == '+') r2 = 1;
	else r2 = 0;

	return r1 | r2;
}

bool pos[8][8][8];

const char *sangui[8] = {"O-", "O+", "A-", "A+", "B-", "B+", "AB-", "AB+"};

int main ()
{
	memset(pos, 0, sizeof pos);
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			int ta[2], tb[2], tr[2], am = 0, bm = 0, rm = 0;

			if ((i & 1) || (j & 1)) tr[rm++] = 0, tr[rm++] = 1;
			else tr[rm++] = 0;

			if ((i >> 1) == 0) ta[am++] = 0;
			else if ((i >> 1) == 1) ta[am++] = 0, ta[am++] = 2;
			else if ((i >> 1) == 2) ta[am++] = 0, ta[am++] = 4;
			else ta[am++] = 2, ta[am++] = 4;

			if ((j >> 1) == 0) tb[bm++] = 0;
			else if ((j >> 1) == 1) tb[bm++] = 0, tb[bm++] = 2;
			else if ((j >> 1) == 2) tb[bm++] = 0, tb[bm++] = 4;
			else tb[bm++] = 2, tb[bm++] = 4;

			for (int a = 0; a < am; a++)
				for (int b = 0; b < bm; b++)
					for (int r = 0; r < rm; r++)
						pos[i][j][ta[a] | tb[b] | tr[r]] = true;
		}

	int kase = 0;
	while (1)
	{
		char in[3][10];
		scanf("%s %s %s", in[0], in[1], in[2]);
		if (in[0][0] == 'E') break;
		++kase;
		printf("Case %d:", kase);
		for (int i = 0; i < 3; i++)
		{
			if (in[i][0] != '?') printf(" %s", in[i]);
			else
			{
				const char *ans[8]; int am = 0;
				for (int j = 0; j < 8; j++)
				{
					strcpy(in[i], sangui[j]);
					if (pos[encode(in[0])][encode(in[1])][encode(in[2])])
					{
						ans[am++] = sangui[j];
					}
				}
				if (am == 0) printf(" IMPOSSIBLE");
				else if (am == 1) printf(" %s", ans[0]);
				else
				{
					for (int j = 0; j < am; j++)
					{
						if (j == 0) printf(" {%s", ans[j]);
						else printf(", %s", ans[j]);
					}
					printf("}");
				}
			}
		}
		printf("\n");
	}
	return 0;
}
