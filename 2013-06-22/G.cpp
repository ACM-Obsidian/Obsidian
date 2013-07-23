#include <cstdio>
#include <cstring>
const char* monthstr[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
char month1[15], month2[15];
int day1, day2, year1, year2;
void solve() {
	scanf("%s %d, %d%s %d, %d", month1, &day1, &year1, month2, &day2, &year2);
	int i = 0;
	for (; i < 12; i++)
		if (strcmp(month1, monthstr[i]) == 0) break;
	if (i < 2) year1--;
	for (i = 0; i < 12; i++)
		if (strcmp(month2, monthstr[i]) == 0) break;
	if (i == 0 || i == 1 && day2 < 29) year2--;
	printf("%d\n", year2 / 4 - year2 / 100 + year2 / 400 - year1 / 4 + year1 / 100 - year1 / 400);
}
int main() {
	int T; scanf("%d", &T);
	for (int i = 1; i <= T; i++)
		printf("Case %d: ", i), solve();
	return 0;
}