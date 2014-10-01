#include <cstdio>
#include <cmath>
#include <cstring>
const double pi = 3.14159265358979324;
double a[3][3], b[3][3];
void mul(double a[3][3], double b[3][3]) {
    double c[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            c[i][j] = 0;
            for (int k = 0; k < 3; k++)
                c[i][j] += b[i][k]*a[k][j];
        }
    memcpy(a, c, sizeof c);
}
void solve() {
    int n; scanf("%d", &n);
    memset(a, 0, sizeof a);
    a[0][0] = a[1][1] = a[2][2] = 1;
    double th = 0;
    while (n--) {
        double x, y, p; scanf("%lf%lf%lf", &x, &y, &p);
        th += p;
        b[0][0] = cos(p), b[0][1] = -sin(p), b[0][2] = x*(1-cos(p))+y*sin(p);
        b[1][0] = sin(p), b[1][1] = cos(p), b[1][2] = y*(1-cos(p))-x*sin(p);
        b[2][0] = b[2][1] = 0, b[2][2] = 1;
        mul(a, b);
    }
    th -= int(th / (2*pi)) * (2*pi);
    a[0][0] -= 1, a[1][1] -= 1;
    double x = (a[1][2]*a[0][1]-a[0][2]*a[1][1])/(a[0][0]*a[1][1]-a[0][1]*a[1][0]);
    double y = (a[1][0]*a[0][2]-a[1][2]*a[0][0])/(a[0][0]*a[1][1]-a[0][1]*a[1][0]);
    printf("%.8lf %.8lf %.8lf\n", x, y, th);
}
int main() {
    int T;
    for (scanf("%d", &T); T--; solve());
    return 0;
}
