#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int base = 10000;
const int len = 500;
const char* sym = "%04d";

struct BigInteger
{
	int m, arr[len];
	void simplify (void)
	{
		for (int i = 0; i <= m; i++)
		{
			if (arr[i] >= base)
			{
				if (i == m) ++m, arr[m] = 0;
				arr[i + 1] += arr[i] / base;
				arr[i] %= base;
			}
		}
	}
	BigInteger (void) : m(0)
	{
		arr[0] = 0;
	}
	BigInteger (int p) : m(0)
	{
		arr[0] = p;
		if (p >= base) simplify();
	}
	BigInteger& operator+= (const BigInteger& a)
	{
		if (m < a.m)
		{
			for (int i = m + 1; i <= a.m; i++) arr[i] = 0;
			m = a.m;
		}
		for (int i = 0; i <= a.m; i++)
			arr[i] += a.arr[i];
		simplify();
		return *this;
	}
	BigInteger& operator*= (const int& a)
	{
		for (int i = 0; i <= m; i++)
			arr[i] *= a;
		simplify();
		return *this;
	}
	void out (void)
	{
		printf("%d", arr[m]);
		for (int i = m - 1; i >= 0; i--) printf(sym, arr[i]);
	}
};
BigInteger operator+ (const BigInteger& a, const BigInteger& b)
{
	BigInteger res(a); res += b; return res;
}
BigInteger operator* (const BigInteger& a, const int& b)
{
	BigInteger res(a); res *= b; return res;
}
BigInteger operator* (const int& b, const BigInteger& a)
{
	return a * b;
}

BigInteger pow[2503];
int n, a[4000];

int main ()
{
	pow[0] = 1;
	for (int i = 1; i <= 2502; i++) pow[i] = pow[i-1] * 2;
	scanf("%d", &n);
	for (int i = 0; i < 2*n; i++) scanf("%d", &a[i]);
	BigInteger res = 0;
	for (int i = 0; i < n; i++)
		if (i < n-1)
			if (a[2*i] < a[2*i+1])
				res += pow[n-i], std::swap(a[2*i+2], a[2*i+3]);
			else
				res += pow[n-i+1];
		else
			if (a[2*i] < a[2*i+1])
				res += 2;
			else
				res += 3;
	res.out(); puts("");
	return 0;
}
