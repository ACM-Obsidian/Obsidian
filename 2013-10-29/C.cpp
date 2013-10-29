#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

int dyna[2010];
bool show[210];

int main ()
{
	freopen("crosses.in", "r", stdin);
	freopen("crosses.out", "w", stdout);
    dyna[0] = 0;
    for (int i = 1; i <= 2000; i++)
    {
        int ans = 0;
        memset(show, false, sizeof show);
        for (int j = 1; j <= i; j++)
        {
            int l = (j - 3 < 0) ? 0 : (j - 3);
            int r = (i - j - 2 < 0) ? 0 : (i - j - 2);
            int mask = dyna[l] ^ dyna[r];
            show[mask] = true;
            while (show[ans]) ++ans;
        }
        dyna[i] = ans;
    }
    int a; scanf("%d", &a);
    if (dyna[a]) printf("1\n");
    else printf("2\n");
    return 0;
}
