#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;

char str[20];
typedef char* pchar;

LL readnum (pchar& p) {
	LL res = 0;
	while (*p >= '0' && *p <= '9') {
		res = res * 10 + *p - '0';
		++p;
	}
	return res;
}
LL calc1 (void) {
	LL ans = 0, c = 1;
	char *p = str;
	while (*p) {
		LL a = readnum(p);
		c *= a;
		if (*p == '+' || *p == 0) ans += c, c = 1;
		++p;
	}
	return ans;
}
LL calc2 (void) {
	char *p = str;
	LL ans = readnum(p);
	while (*p) {
		char t = *p; ++p;
		LL a = readnum(p);
		if (t == '+') ans += a;
		else ans *= a;
	}
	return ans;
}

int main () {
	LL ans; scanf("%s %lld", str, &ans);
	LL a1 = calc1(), a2 = calc2();
	if (ans == a1) {
		printf("%s\n", ans == a2 ? "U" : "M");
	}
	else {
		printf("%s\n", ans == a2 ? "L" : "I");
	}
	return 0;
}
