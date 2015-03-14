#include <cstdio>
#include <complex>
#include <cstdlib>
#include <ctime>
const long double pi = 3.14159265358979324;
typedef std::complex<long double> complex;
double a[5];
long double p[4];
bool near(complex a, complex b, long double zero) {
	return std::abs(a-b) < zero || std::abs(a-b) < std::abs(a)*zero;
}
int main() {
	freopen("definite.in", "r", stdin);
	freopen("definite.out", "w", stdout);
	srand(time(0));
	for (int i = 0; i < 5; i++)
		scanf("%lf", &a[i]);
	for (int i = 0; i < 4; i++)
		p[i] = a[i] / a[4];
	complex r1 = complex((long double)rand()/RAND_MAX*2-1, (long double)rand()/RAND_MAX*2-1);
	while (1) {
		complex r_ = ((((3.0L*r1+2.0L*p[3])*r1+p[2])*r1)*r1-p[0])/(((4.0L*r1+3.0L*p[3])*r1+2.0L*p[2])*r1+p[1]);
		if (near(r_, r1, 1e-14))
			break;
		r1 = r_;
	}
	r1 = complex(r1.real(), std::abs(r1.imag()));
	long double u2 = -p[3]/2 - r1.real(), v2 = sqrt(p[0]/(r1.real()*r1.real()+r1.imag()*r1.imag()) - u2*u2);
	complex r2 = complex(u2, v2);
	while (1) {
		complex r_ = ((((3.0L*r2+2.0L*p[3])*r2+p[2])*r2)*r2-p[0])/(((4.0L*r2+3.0L*p[3])*r2+2.0L*p[2])*r2+p[1]);
		if (near(r_, r2, 1e-14))
			break;
		r2 = r_;
	}
	double ans = (complex(0, 2.0*pi) * (1.0L/(((4.0L*r1+3.0L*p[3])*r1+2.0L*p[2])*r1+p[1]) + 1.0L/(((4.0L*r2+3.0L*p[3])*r2+2.0L*p[2])*r2+p[1]))).real();
	ans /= a[4];
	printf("%.12lf\n", ans);
	return 0;
}
