#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 160;

int arr[N], n;

bool nar_ok (int nar)
{
	double nar_inf, nar_sup, wid_inf, wid_sup;

	nar_inf = wid_inf = 500;
	nar_sup = wid_sup = 0;

	for (int i = 0; i < n; i++)
	{
		if (arr[i] <= nar)
		{
			nar_inf = min(nar_inf, (double) arr[i]);
			nar_sup = max(nar_sup, (double) arr[i]);
		}
		else
		{
			wid_inf = min(wid_inf, (double) arr[i]);
			wid_sup = max(wid_sup, (double) arr[i]);
		}
	}

	double inf = min(nar_inf, wid_inf * 0.5), sup = max(nar_sup, wid_sup * 0.5);

	// printf("nar = %d, inf = %f, sup = %f, %f %f\n", nar, inf, sup, sup / 1.05, inf / 0.95);

	if (sup / 1.05 - inf / 0.95 > 1e-12) return false;
	else return true;
}

inline int decode (int s)
{
	switch (s)
	{
		case 1:
			return 0;
		case 17:
			return 1;
		case 9:
			return 2;
		case 24:
			return 3;
		case 5:
			return 4;
		case 20:
			return 5;
		case 12:
			return 6;
		case 3:
			return 7;
		case 18:
			return 8;
		case 16:
			return 9;
		case 4:
			return 10;
		case 6:
			return -2; // start / stop
		default:
			return -1; // invalid
	}
}

int dec[N];

int readNum (int& p, int n, int nar)
{
	// printf("readNum %d %d %d\n", p, n, nar);
	int s = 0, i;
	for (i = 0; i < 5 && p < n; i++, p++)
	{
		if (arr[p] <= nar) s = (s << 1);
		else s = (s << 1) | 1;
	}
	if (i < 5) return -1; // invalid;
	if (p < n && arr[p] > nar) return -1;
	if (p < n) ++p;
	// printf("s = %d\n", s);
	return decode(s);
}

int main ()
{
	int kase = 0; while (scanf("%d", &n), n)
	{
		for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
		bool ok = false; int nar;
		for (int i = 1; !ok && i <= 200; i++)
		{
			if (nar_ok(i))
			{
				nar = i;
				ok = true;
			}
		}
		int p = 0, dmr = 0;
		printf("Case %d: ", ++kase);
		if (!ok || (readNum(p, n, nar) != -2 && (reverse(arr, arr + n), p = 0, readNum(p, n, nar) != -2))) printf("bad code\n");
		else
		{
			bool badcode = false;
			while (1)
			{
				dec[dmr] = readNum(p, n, nar);
				if (dec[dmr] == -2)
				{
					if (p != n) badcode = true;
					break;
				}
				else if (dec[dmr] == -1)
				{
					badcode = true;
					break;
				}
				else ++dmr;
			}
			if (badcode) printf("bad code\n");
			else
			{
				int s = 0, tn = dmr - 3;
				for (int i = 0; i < dmr - 2; i++)
					s += ((tn - i) % 10 + 1) * dec[i];
				if (dec[dmr - 2] != s % 11)
				{
					printf("bad C\n");
				}
				else
				{
					s = 0, tn = dmr - 2;
					for (int i = 0; i < dmr - 1; i++)
						s += ((tn - i) % 9 + 1) * dec[i];
					if (dec[dmr - 1] != s % 11)
					{
						printf("bad K\n");
					}
					else
					{
						for (int i = 0; i < dmr - 2; i++)
						{
							if (dec[i] == 10) printf("-");
							else printf("%c", dec[i] + '0');
						}
						printf("\n");
					}
				}
			}
		}
	}
	return 0;
}
