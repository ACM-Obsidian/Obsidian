#include <cstdio>
#include <cstring>
#include <cmath>
const char arr[7][11] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
const int numday[7] = {8, 8, 8, 8, 8, 4, 4};
char a[11];
double L, s;
int main() {
	for (; scanf("%s%lf%lf", a, &L, &s) != EOF; ) {
		int day = 0;
		for (int i = 0; i < 7; i++)
			if (strcmp(a, arr[i]) == 0) day = i;
		double cycle = s * 48;
		int num = int(L / cycle) * 7;
		L -= num / 7 * cycle;
		for (; L > 1e-5; L -= numday[day] * s, day = (day+1)%7) ;
		day = (day+6)%7;
		puts(arr[day]);
	}
	return 0;
}
