#include <cstdio>
#include <cmath>
#include <algorithm>
double a, b, c, d, e, f;
int main() {
    while (scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &e, &f) != EOF) {
        long double A = -(a+b+c), B = a*b+b*c+a*c-(d*d+e*e+f*f)/4, C = -a*b*c-(d*e*f-a*d*d-b*e*e-c*f*f)/4;
        long double l = -1e5, r = 1e5;
        while (r-l > 1e-12) {
            long double mid = (l+r)/2;
            long double v = ((mid+A)*mid+B)*mid+C;
            if (v < 0) l = mid;
            else r = mid;
        }
        long double x1 = (l+r)/2, x2, x3;
        long double D = A + x1, E = B + x1 * D;
        if (fabs(D*D-4*E) < 1e-8) x2 = x3 = -D/2;
        else if (D*D-4*E < 0) x2 = x3 = -1e30;
        else x2 = (sqrt(D*D-4*E)-D)/2, x3 = (-sqrt(D*D-4*E)-D)/2;
        long double x = std::max(x1, std::max(x2, x3));
        printf("%.8lf\n", (double)sqrt(1 / x));
    }
    return 0;
}
