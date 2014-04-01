#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 110;
typedef long long LL;

long long D;

struct poly
{
	LL arr[N];
	poly (void)
	{
		clear();
	}
	const char* parseTerm (const char *s)
	{
		// printf("parseTerm %s\n", s);

		bool minus = false;
		if (s[0] == '(') ++s;
		if (s[0] == '-') minus = true, ++s;
		else if (s[0] == '+') ++s;
		long long k = 1;
		if (s[0] >= '0' && s[0] <= '9')
		{
			k = 0;
			while (s[0] >= '0' && s[0] <= '9')
			{
				k = k * 10 + s[0] - '0';
				++s;
			}
		}
		if (s[0] == 'n')
		{
			++s;
			if (s[0] == '^')
			{
				++s;
				int tt = 0;
				while (s[0] >= '0' && s[0] <= '9')
				{
					tt = tt * 10 + s[0] - '0';
					++s;
				}
				arr[tt] = (minus ? D - k % D : k) % D;
			}
			else
			{
				arr[1] = (minus ? D - k % D : k) % D;
			}
		}
		else // const
		{
			arr[0] = (minus ? D - k % D : k) % D;
		}
		return s;
	}
	poly (const char* s)
	{
		clear();
		while (s[0] && s[0] != ')')
		{
			s = parseTerm(s);
		}
	}
	poly& operator+= (const poly& p)
	{
		for (int i = 0; i < N; i++)
			(arr[i] += p.arr[i]) %= D;
		return *this; 
	}
	poly& operator*= (const int& k)
	{
		for (int i = 0; i < N; i++)
			(arr[i] *= k) %= D;
		return *this;
	}
	poly operator- (void) const
	{
		poly res;
		for (int i = 0; i < N; i++)
			res.arr[i] = (D - arr[i] % D) % D;
		return res;
	}
	int degree (void) const
	{
		for (int i = N - 1; i >= 0; i--) if (arr[i]) return i;
		return 0;
	}
	void clear (void)
	{
		memset(arr, 0, sizeof arr);
	}
	void show (void) const
	{
		for (int i = N - 1; i >= 0; i--)
		{
			if (arr[i]) printf("+ (%lld)n^%d ", arr[i], i);
		}
		printf("\n");
	}
};
poly operator+ (const poly& a, const poly& b)
{
	poly res(a);
	res += b;
	return res;
}
poly operator- (const poly& a, const poly& b)
{
	poly res(-b);
	res += a;
	return res;
}
poly operator* (const poly& a, const int& k)
{
	poly res(a);
	res *= k;
	return res;
}

long long C[N][N];
poly addone[N];
char polystr[10010];

poly diff (const poly& a)
{
	poly res;
	for (int i = N - 1; i >= 0; i--)
	{
		if (a.arr[i]) res += addone[i] * a.arr[i];
	}
	// printf("f(n + 1) = "), res.show();
	res = res - a;
	return res;
}

int main ()
{
	int kase = 0;
	while (scanf("%s", polystr) && strcmp(polystr, "."))
	{
		char *sl = polystr;
		while (*sl != '/') ++sl;
		*sl = 0; ++sl;
		sscanf(sl, "%lld", &D);
		// printf("D = %d\n", D);

		C[0][0] = 1 % D;
		for (int i = 1; i < N; i++)
		{
			for (int j = 0; j <= i; j++)
				C[i][j] = (C[i - 1][j] + (j - 1 >= 0 ? C[i - 1][j - 1] : 0)) % D;
		}
		for (int i = 0; i < N; i++)
		{
			addone[i].clear();
			for (int j = 0; j <= i; j++) addone[i].arr[j] = C[i][j];
			// if (i < 10) addone[i].show();
		}

		poly proc(polystr);
		// proc.show();

		long long s = 0;
		for (int i = N - 1; i >= 0; i--) (s += proc.arr[i]) %= D;
		bool ok = true;
		if (s != 0) ok = false;

		while (ok && proc.degree() > 0)
		{
			proc = diff(proc);//, proc.show(), getchar();
			s = 0;
			for (int i = N - 1; i >= 0; i--) (s += proc.arr[i]) %= D;
			if (s != 0) ok = false;
		}
		printf("Case %d: ", ++kase);
		if (ok) printf("Always an integer\n");
		else printf("Not always an integer\n");
	}
	return 0;
}
