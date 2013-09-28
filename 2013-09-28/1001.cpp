#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 1010;
char arr[N]; int len;
char A[N], B[N], X[N], Y[N]; int n;

void div2 (void)
{
    for (int i = 0; i < len; i++)
    {
        arr[i + 1] += (arr[i] & 1) * 10;
        arr[i] >>= 1;
    }
    arr[len] = 0;
}
void sub1 (char a[])
{
    for (int i = 0; i < n; i++)
    {
        a[i] = 1 - a[i];
        if (!a[i]) break;
    }
}
void read (char a[])
{
    scanf("%s", arr);
    len = strlen(arr);
    for (int i = 0; i < len; i++) arr[i] -= '0';
    for (int i = 0; i <= n; i++)
    {
        a[i] = (arr[len - 1] & 1);
        div2();
    } 
}

int main ()
{
    int kase, _ = 1; for (scanf("%d", &kase); _ <= kase; ++_)
    {
        scanf("%d", &n);
        read(A), read(X), read(B), read(Y);
        sub1(A), sub1(B), sub1(X), sub1(Y);
        /* for (int i = n - 1; i >= 0; i--) printf("%d", A[i]); printf("\n");
        for (int i = n - 1; i >= 0; i--) printf("%d", B[i]); printf("\n");
        for (int i = n - 1; i >= 0; i--) printf("%d", X[i]); printf("\n");
        for (int i = n - 1; i >= 0; i--) printf("%d", Y[i]); printf("\n"); */
        bool ans = false;
        for (int offset = 0; offset < n; offset++)
        {
            bool ok = true;
            for (int i = 0; ok && i < n; i++)
            {
                if ((A[i] == X[(i + offset) % n]) != (B[i] == Y[(i + offset) % n])) ok = false;
            }
            if (ok)
            {
                ans = true;
                break;
            }
        }
        printf("Case %d: %s\n", _, ans ? "Yes" : "No");
    }
    return 0;
}
