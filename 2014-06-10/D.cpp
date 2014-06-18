#include <cstdio>
#include <algorithm>
#include <cmath>
const float pi = 3.14159265358979324;
int main() {
	int T;
	for (scanf("%d", &T); T--; ) {
		float r[3];
		for (int i = 0; i < 3; i++) scanf("%f", &r[i]);
		std::sort(r, r+3);
		float ll = r[1]+r[2], rr = 250;
		while (ll+1e-4 < rr) {
			float mid = (ll+rr)/2, th = 0;
			float tr0 = mid-r[0], tr1 = mid-r[1], tr2 = mid-r[2];
			float rs0 = r[0]+r[1], rs1 = r[1]+r[2], rs2 = r[2]+r[0];
			th = acos((tr0*tr0+tr1*tr1-rs0*rs0)/(2*tr0*tr1))
				+ acos((tr1*tr1+tr2*tr2-rs1*rs1)/(2*tr1*tr2))
				+ acos((tr2*tr2+tr0*tr0-rs2*rs2)/(2*tr2*tr0));
			if (th > 2*pi) ll = mid;
			else rr = mid;
		}
		float ans = (ll+rr)/2;
		float tr = (r[1]*r[2]*(r[1]+r[2]))/(r[1]*r[1]+r[2]*r[2]+r[1]*r[2]);
		if (r[0] < tr) ans = r[1]+r[2];
		printf("%.10lf\n", ans);
	}
	return 0;
}
