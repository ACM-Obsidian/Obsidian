#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;
const ll Max = 1000000000000ll;

struct alvec
{
	ll cnt[26];
	alvec (void)
	{
		memset(cnt, 0, sizeof cnt);
	}
	alvec (ll _cnt[])
	{
		for (int i = 0; i < 26; i++)
			cnt[i] = _cnt[i];
	}
	const ll& operator[] (const int& idx) const
	{
		return cnt[idx];
	}
	ll& operator[] (const int& idx)
	{
		return cnt[idx];
	}
	void inc (int k)
	{
		if (cnt[k] != -1) ++cnt[k];
		if (cnt[k] > Max) cnt[k] = -1;
	}
};
alvec operator+ (const alvec& a1, const alvec& a2)
{
	alvec res;
	for (int i = 0; i < 26; i++)
	{
		if (a1[i] == -1 || a2[i] == -1) res[i] = -1;
		else res[i] = a1[i] + a2[i];
		if (res[i] > Max) res[i] = -1;
	}
	return res;
}
alvec operator* (const alvec& a, int k)
{
	alvec res;
	for (int i = 0; i < 26; i++)
	{
		if (a[i] == -1) res[i] = -1;
		else if (a[i] && k > Max / a[i]) res[i] = -1;
		else res[i] = a[i] * k;
		if (res[i] > Max) res[i] = -1;
	}
	return res;
}

int mb_rec[100010];

int matching_brac (char str[], int k)
{
	return mb_rec[k];
}

bool rec[100010];
alvec hehe[100010];

bool mid_break;
alvec analyser (char str[], int l, int r, ll occured_a, ll max_a)
{
	// printf("PROC %d %d %lld %lld\n", l, r, occured_a, max_a);
	if (rec[l] && hehe[l][0] != -1 && occured_a + hehe[l][0] < max_a)
	{
		mid_break = false;
		return hehe[l];
	}
	alvec res;
	for (int i = l; i < r; )
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			res.inc(str[i] - 'a');
			if (res[0] + occured_a >= max_a)
			{
				mid_break = true;
				return res;
			}
			++i;
		}
		else // number
		{
			int rep = 0, j;
			// printf("NUM %d\n", i);
			for (j = i; j < r; j++)
			{
				if (str[j] >= '0' && str[j] <= '9')
				{
					rep = rep * 10 + str[j] - '0';
				}
				else break;
			}
			// printf("J = %d, REP = %d\n", j, rep);
			i = j;
			int mb = matching_brac(str, i);
			// printf("BRAC %d %d\n", i, mb);
			alvec tt = analyser(str, i + 1, mb, occured_a + res[0], max_a);
			if (mid_break) // case 1
			{
				// printf("case 1\n");
				mid_break = true;
				return res + tt;
			}
			else if (tt[0] * rep + occured_a + res[0] < max_a) // case 2
			{
				// printf("case 2\n");
				res = res + tt * rep;
				i = mb + 1;
			}
			else // case 3
			{
				// printf("case 3\n");
				// printf("tt[0] = %lld\n", tt[0]);
				int max_rep = (max_a - occured_a - res[0]) / tt[0];
				if (tt[0] * max_rep + occured_a + res[0] == max_a) --max_rep;
				// printf("MAX_REP = %d\n", max_rep);
				if (max_rep) res = res + tt * max_rep;
				alvec tt2 = analyser(str, i + 1, mb, occured_a + res[0], max_a);
				mid_break = true;
				return res + tt2;
			}
		}
	}
	mid_break = false;
	rec[l] = true;
	hehe[l] = res;
	// printf("returned\n");
	return res;
}

char str[100010];
int sta[100010], top = 0;

int main ()
{
	freopen("az.in", "r", stdin);
	freopen("az.out", "w", stdout);
	int k; scanf("%s %d", str, &k);
	memset(mb_rec, -1, sizeof mb_rec);
	memset(rec, 0, sizeof rec);
	int n = strlen(str);
	for (int i = 0; i < n; i++)
	{
		if (str[i] == '(') sta[top++] = i;
		else if (str[i] == ')') mb_rec[sta[--top]] = i;
	}
	alvec res = analyser(str, 0, n, 0, k);
	for (int i = 0; i < 26; i++) if (res[i])
	{
		printf("%c %I64d\n", i + 'a', res[i]);
	}
	return 0;
}
