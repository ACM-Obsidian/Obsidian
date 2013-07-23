#include <cstdio>
#include <cstring>
#include <cmath>
#include <complex>
#define maxn 262144
typedef std::complex<double> complex;
const double pi = 3.14159265358979324;
complex wx[maxn], tw[maxn], *e;
int n, a[maxn];
long long b[maxn];
void pre() {
    e = new complex[2*maxn-1], e += maxn-1;
    for (int i = 0; i < maxn; i++) e[i] = complex(cos(2*pi*i/maxn), sin(2*pi*i/maxn));
    for (int i = 1; i < maxn; i++) e[-i] = e[maxn-i];
}
void dft(complex *a, complex *tw, int l, int n, int d) {
    if (n == 1) return;
    int m = n>>1;
    for (int i = 0; i < m; i++) tw[l+i] = a[l+2*i], tw[l+m+i] = a[l+2*i+1];
    dft(tw, a, l, m, d*2), dft(tw, a, l+m, m, d*2);
    for (int i = 0; i < m; i++) a[l+i] = tw[l+i]+e[d*i]*tw[l+i+m];
    for (int i = m; i < n; i++) a[l+i] = tw[l+i-m]+e[d*i]*tw[l+i];
}
void solve() {
    scanf("%d", &n);
    memset(a, 0, sizeof a);
    int max = 0;
    for (int i = 0, x; i < n; i++) {
        scanf("%d", &x), a[x]++;
        if (x > max) max = x;
    }
    int m = n;
    for (int i = 0; i <= 18; i++)
        if (1<<i >= 2*max+1) {
            m = 1<<i;
            break;
        }
    for (int i = 0; i < m; i++)
        wx[i] = complex(a[i], 0);
    dft(wx, tw, 0, m, maxn/m);
    for (int i = 0; i < m; i++) wx[i] = wx[i]*wx[i];
    dft(wx, tw, 0, m, -maxn/m);
    for (int i = 0; i < m; i++) b[i] = (long long) (wx[i].real()/m+0.5);
    long long ans = 0, sum = 0;
    for (int i = 1, j = 0; i <= max; i++) {
        for (int k = 0; k < a[i]; k++, j++) ans += 1LL*j*(j-1)/2;
        long long tmp = b[i];
        if (!(i%2)) tmp -= a[i/2];
        sum += tmp/2;
        ans -= sum*a[i];
    }
    printf("%.7lf\n", ans*6.0/(1LL*n*(n-1)*(n-2)));
}
int main() {
    pre();
    int T;
    for (scanf("%d", &T); T--; solve());
    return 0;
}