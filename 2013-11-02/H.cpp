#include <cstdio>
#include <cstring>
char a[101];
int main() {
	freopen("palin.in","r",stdin);
	freopen("palin.out","w",stdout);
	gets(a);
	int l = strlen(a);
	for (int i = 0; i < l; i++) {
		int flag = 1;
		for (int j = i, k = (i+l-1)%l, t = 0; t < l>>1; j = (j+1)%l, k = (k+l-1)%l, t++)
			if (a[j] != a[k]) {
				flag = 0;
				break;
			}
		if (flag) {
			puts("yes");
			return 0;
		}
	}
	puts("no");
	return 0;
}
