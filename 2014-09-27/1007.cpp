#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
struct line {
    double x1, y1, z1, x2, y2, z2;
} a[100];
struct light {
    double x, y, z, a, b, c;
    int type;
} b[100];
double ans[8];
int main() {
    int T; scanf("%d", &T);
    for (int _ = 1; _ <= T; _++) {
        int n, m; scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++)
            scanf("%lf%lf%lf%lf%lf%lf", &a[i].x1, &a[i].y1, &a[i].z1, &a[i].x2, &a[i].y2, &a[i].z2);
        for (int i = 0; i < m; i++) {
            char ch;
            scanf("%lf%lf%lf%lf%lf%lf %c", &b[i].x, &b[i].y, &b[i].z, &b[i].a, &b[i].b, &b[i].c, &ch);
            if (ch == 'R') b[i].type = 1;
            else if (ch == 'G') b[i].type = 2;
            else b[i].type = 4;
        }
        for (int i = 0; i < 8; i++) ans[i] = 0;
        for (int i = 0; i < n; i++) {
            std::vector<double> tmp;
            tmp.push_back(0), tmp.push_back(1);
            for (int j = 0; j < m; j++) {
                double x1 = a[i].x1 - b[j].x, y1 = a[i].y1 - b[j].y, z1 = a[i].z1 - b[j].z;
                double x2 = a[i].x2 - a[i].x1, y2 = a[i].y2 - a[i].y1, z2 = a[i].z2 - a[i].z1;
                double a1 = b[j].a, b1 = b[j].b, c1 = b[j].c;
                double A = x2*x2/(a1*a1)+y2*y2/(b1*b1)+z2*z2/(c1*c1);
                double B = 2*(x1*x2/(a1*a1)+y1*y2/(b1*b1)+z1*z2/(c1*c1));
                double C = x1*x1/(a1*a1)+y1*y1/(b1*b1)+z1*z1/(c1*c1) - 1;
                double delta = B*B-4*A*C;
                if (delta > 0) {
                    double X1 = (sqrt(delta)-B)/(2*A), X2 = (-sqrt(delta)-B)/(2*A);
                    if (X1 > 0 && X1 < 1) tmp.push_back(X1);
                    if (X2 > 0 && X2 < 1) tmp.push_back(X2);
                }
            }
            std::sort(tmp.begin(), tmp.end());
            for (int j = 0; j+1 < tmp.size(); j++)
                if (tmp[j+1]-tmp[j] > 1e-8) {
                    double t = (tmp[j]+tmp[j+1])/2;
                    double x = a[i].x1+t*(a[i].x2-a[i].x1), y = a[i].y1+t*(a[i].y2-a[i].y1), z = a[i].z1+t*(a[i].z2-a[i].z1);
                    int type = 0;
                    for (int k = 0; k < m; k++)
                        if ((x-b[k].x)*(x-b[k].x)/(b[k].a*b[k].a)+(y-b[k].y)*(y-b[k].y)/(b[k].b*b[k].b)+(z-b[k].z)*(z-b[k].z)/(b[k].c*b[k].c) < 1 - 1e-10)
                            type |= b[k].type;
                    ans[type] += (tmp[j+1]-tmp[j]) * sqrt((a[i].x2-a[i].x1)*(a[i].x2-a[i].x1)+(a[i].y2-a[i].y1)*(a[i].y2-a[i].y1)+(a[i].z2-a[i].z1)*(a[i].z2-a[i].z1));
                }
        }
        printf("%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n", ans[0], ans[1], ans[2], ans[4], ans[3], ans[5], ans[6], ans[7]);
    }
    return 0;
}
