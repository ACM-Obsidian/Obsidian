#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

int trans (char p[])
{
	int res;
	switch (p[1])
	{
		case 'm':
			res = 0; break;
		case 's':
			res = 9; break;
		case 'p':
			res = 18; break;
		default:
			res = 27;
	}
	return res + p[0] - '0' - 1;
}
int cnt[34], tot;
bool ron (int st)
{
	if (tot == 2)
	{
		for (int i = 0; i < 34; i++) if (cnt[i] == 2) return true;
		return false;
	}
	else
	{
		for (int i = 0; i <= 24; i++) // 24: 7p
		{
			// 8m, 9m, 8s, 9s
			if (st > i) continue;
			if (i == 7 || i == 8 || i == 16 || i == 17) continue;
			if (cnt[i] && cnt[i + 1] && cnt[i + 2])
			{
				--cnt[i], --cnt[i + 1], --cnt[i + 2];
				tot -= 3;
				bool res = ron(i);
				++cnt[i], ++cnt[i + 1], ++cnt[i + 2];
				tot += 3;
				if (res) return true;
			}
		}
		for (int i = 0; i < 34; i++)
		{
			if (st > i + 25) continue;
			if (cnt[i] >= 3)
			{
				cnt[i] -= 3; tot -= 3;
				bool res = ron(i + 25);
				cnt[i] += 3; tot += 3;
				if (res) return true;
			}
		}
		return false;
	}
}
bool nana (void)
{
	for (int i = 0; i < 34; i++)
	{
		if (cnt[i] != 2 && cnt[i] != 0) return false;
	}
	return true;
}
bool koku (void)
{
	int y9[13] = {0, 8, 9, 17, 18, 26, 27, 28, 29, 30, 31, 32, 33};
	int t = -1;
	for (int i = 0; i < 13; i++)
	{
		if (cnt[y9[i]] < 1 || cnt[y9[i]] > 2) return false;
		if (cnt[y9[i]] == 2)
		{
			if (t != -1) return false;
			t = i;
		}
	}
	return t != -1;
}
int main ()
{
	int kase; for (scanf("%d", &kase); kase; --kase)
	{
		memset(cnt, 0, sizeof cnt);
		for (int i = 0; i < 13; i++)
		{
			char str[5];
			scanf("%s", str);
			cnt[trans(str)]++;
		}
		tot = 14;
		int ans[20], amr = 0;
		for (int i = 0; i < 34; i++)
		{
			if (cnt[i] == 4) continue;
			++cnt[i];
			if (ron(0) || nana() || koku()) ans[amr++] = i;
			--cnt[i];
		}
		if (amr == 0) printf("Nooten\n");
		else
		{
			printf("%d", amr);
			for (int i = 0; i < amr; i++)
			{
				if (ans[i] < 9) printf(" %dm", ans[i] + 1);
				else if (ans[i] < 18) printf(" %ds", ans[i] - 9 + 1);
				else if (ans[i] < 27) printf(" %dp", ans[i] - 18 + 1);
				else printf(" %dc", ans[i] - 27 + 1);
			}
			printf("\n");
		}
	}
	return 0;
}