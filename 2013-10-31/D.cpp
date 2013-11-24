#include <cstdio>
#include <cmath>
const double pi = 3.14159265358979324;
double s1, s2, s3, w1, h1, w2, h2, x20, y20, x21, y21, x22, y22, w3, h3, x30, y30, x31, y31, x32, y32;
int flag;
bool inside(double x, double y, double x1, double y1, double x2, double y2, double x3, double y3, double w, double h) {
	double x_ = ((x-x1)*x2+(y-y1)*y2)/w, y_ = ((x-x1)*x3+(y-y1)*y3)/h;
	return x_ > -1e-8 && x_ < w+1e-8 && y_ > -1e-8 && y_ < h+1e-8;
}
int main() {
	freopen("maps.in","r",stdin);
	freopen("maps.out","w",stdout);
	double x, y;
	scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf", &s1, &w1, &h1, &s2, &s3, &x30, &y30, &x31, &y31, &x, &y, &x32, &y32);
	x31 -= x30, y31 -= y30, x32 -= x30, y32 -= y30;
	double d = (x31-w1)*(y32-h1)-x32*y31, x0 = w1*(x32*y30+x30*(h1-y32))/d, y0 = h1*(x30*y31+y30*(w1-x31))/d;
	double th0 = atan2(y0, x0), r0 = sqrt(x0*x0+y0*y0);
	w2 = w1*s2/s1, h2 = h1*s2/s1;
	for (double th2 = 0; th2 < 2*pi; th2 += 0.001) {
		x20 = x0-r0*s2/s1*cos(th0+th2), y20 = y0-r0*s2/s1*sin(th0+th2);
		x21 = w2*cos(th2), y21 = w2*sin(th2);
		x22 = -h2*sin(th2), y22 = h2*cos(th2);
		if (
				inside(x20, y20, 0, 0, w1, 0, 0, h1, w1, h1) &&
				inside(x20+x21, y20+y21, 0, 0, w1, 0, 0, h1, w1, h1) &&
				inside(x20+x21+x22, y20+y21+y22, 0, 0, w1, 0, 0, h1, w1, h1) &&
				inside(x20+x22, y20+y22, 0, 0, w1, 0, 0, h1, w1, h1) &&
				inside(x30, y30, x20, y20, x21, y21, x22, y22, w2, h2) &&
				inside(x30+x31, y30+y31, x20, y20, x21, y21, x22, y22, w2, h2) &&
				inside(x30+x31+x32, y30+y31+y32, x20, y20, x21, y21, x22, y22, w2, h2) &&
				inside(x30+x32, y30+y32, x20, y20, x21, y21, x22, y22, w2, h2)
		   ) {
			flag = 1;
			break;
		}
	}
	if (!flag) puts("impossible");
	else printf("%.8lf %.8lf\n%.8lf %.8lf\n%.8lf %.8lf\n%.8lf %.8lf\n", x20, y20, x20+x21, y20+y21, x20+x21+x22, y20+y21+y22, x20+x22, y20+y22);
	return 0;
}
