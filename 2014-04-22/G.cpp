#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const int N = 510;

double arr[N]; 

const double pi = 3.14159265358979;

inline double calc1 (double r, int s, int t)
{
	double sum = 0;
	for (int i = s; i < t; i++) sum += asin(arr[i] * 0.5 / r);
	return sum;
}
inline double calc2 (double r, int s, int t, int m)
{
	double sum = asin(arr[m] * 0.5 / r);
	for (int i = s; i < t; i++) if (i != m) sum -= asin(arr[i] * 0.5 / r);
	return sum;
}
inline double area1 (double r, int s, int t)
{
	double sum = 0, r2 = r * r;
	for (int i = s; i < t; i++)
	{
		double ang = asin(arr[i] * 0.5 / r) * 2;
		sum += r2 * sin(ang);
	}
	return sum * 0.5;
}
inline double area2 (double r, int s, int t, int m)
{
	double sum = 0, r2 = r * r;
	for (int i = s; i < t; i++)
	{
		double ang = asin(arr[i] * 0.5 / r) * 2;
		if (i == m) sum -= r2 * sin(ang);
		else sum += r2 * sin(ang);
	}
	return sum * 0.5;
}
inline double max_area (int s, int t)
{
	if (t - s <= 2) return 0;

	int m = s; double sum = arr[s];
	for (int i = s + 1; i < t; i++)
	{
		if (arr[i] > arr[m]) m = i;
		sum += arr[i];
	}
	double tt = max_area(s, m) + max_area(m + 1, t);
	if (sum - arr[m] < arr[m] + 1e-12)
	{
		return tt;
	}

	double ll = arr[m] * 0.5, rr = 100000, ans;
	while (rr - ll >= 1e-08)
	{
		double mid = (rr + ll) * 0.5;
		if (calc1(mid, s, t) < pi) rr = mid;
		else ll = mid;
	}
	if (calc1(ll, s, t) < pi) {
		ll = arr[m] * 0.5, rr = 100000;
		while (rr - ll >= 1e-08)
		{
			double mid = (rr + ll) * 0.5;
			if (calc2(mid, s, t, m) < 0) rr = mid;
			else ll = mid;
		}
		ans = area2(ll, s, t, m);
	} else {
		ans = area1(ll, s, t);
	}
	return max(tt, ans);
}

// double dp[N];

int main ()
{
	int kase = 0, n; while (scanf("%d", &n), n)
	{
		for (int i = 0; i < n; i++) scanf("%lf", &arr[i]); 
		/* dp[0] = 0;
		for (int i = 1; i < n; i++)
		{
			dp[i] = dp[i - 1];
			for (int j = -1; j < i; j++)
			{
				double t = max_area(j + 1, i + 1);
				if (t > 0)
				{
					if (j == -1) dp[i] = max(dp[i], t);
					else dp[i] = max(dp[i], dp[j] + t);
				}
			}
		} */
		printf("Case %d: %.6lf\n", ++kase, max_area(0, n));
	}
	return 0;
}
