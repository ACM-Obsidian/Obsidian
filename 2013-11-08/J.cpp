#include <cstdio>
#include <vector>
#include <algorithm>
struct state {
	std::vector<long long> v;
	int hash() {
		int sum = 0;
		for (int i = 0; i < v.size(); i++) sum = sum*1234567+v[i];
		return (unsigned int)sum % 120007;
	}
};
struct hash_t {
	state *x;
	long long a, b;
	int op;
	state *pre;
};
struct ans_t {
	int a, b, c;
	char op;
};
std::vector<hash_t> h[120007];
state pool[1000000], *q[1000000], *sans;
int top, t, ans;
long long tmp[7];
void solve() {
	top = 0;
	state *init = &pool[top++];
	init->v.clear();
	for (int i = 0; i < 6; i++) {
		int x; scanf("%d", &x);
		tmp[i] = x;
	}
	scanf("%d", &t);
	ans = ~0U>>2;
	std::sort(tmp, tmp+6);
	for (int i = 0; i < 6; i++) init->v.push_back(tmp[i]);
	int l = 0, r = 1; q[0] = init;
	hash_t htmp; htmp.x = init, htmp.pre = NULL;
	h[init->hash()].push_back(htmp);
	while (l < r) {
		state *now = q[l];
		int cnt = now->v.size();
		for (int i = 0; i < cnt; i++)
			if (llabs(now->v[i]-t) < abs(ans-t)) {
				ans = now->v[i];
				sans = now;
			}
		//for (int i = 0; i < cnt; i++) printf("%d ", now->v[i]); puts("");
		for (int i = 0; i < cnt; i++)
			for (int j = 0; j < cnt; j++)
				if (i != j)
					for (int k = 0; k < 4; k++) {
						for (int l = 0; l < cnt; l++) tmp[l] = now->v[l];
						if (k == 1 && tmp[i] <= tmp[j]) continue;
						if (k == 3 && tmp[i]%tmp[j]) continue;
						hash_t htmp; htmp.a = tmp[i], htmp.b = tmp[j], htmp.op = k, htmp.pre = now;
						switch (k) {
							case 0: tmp[i] = tmp[i]+tmp[j]; break;
							case 1: tmp[i] = tmp[i]-tmp[j]; break;
							case 2: tmp[i] = tmp[i]*tmp[j]; break;
							case 3: tmp[i] = tmp[i]/tmp[j]; break;
						}
						tmp[j] = -1;
						std::sort(tmp, tmp+cnt);
						state *succ = &pool[top++];
						succ->v.clear();
						for (int l = 1; l < cnt; l++)
							succ->v.push_back(tmp[l]);
						htmp.x = succ;
						int hash = succ->hash(), flag = 1;
						for (int l = 0; l < h[hash].size(); l++)
							if (h[hash][l].x->v == succ->v) {
								flag = 0;
								break;
							}
						if (!flag) continue;
						h[hash].push_back(htmp);
						q[r++] = succ;
					}
		l++;
	}
	printf("Target: %d\n", t);
	std::vector<ans_t> vans;
	for (state *cur = sans; cur != init; ) {
		int hash = cur->hash();
		ans_t atmp;
		for (int l = 0; l < h[hash].size(); l++)
			if (h[hash][l].x->v == cur->v) {
				atmp.a = h[hash][l].a, atmp.b = h[hash][l].b;
				switch (h[hash][l].op) {
					case 0: atmp.c = atmp.a+atmp.b; atmp.op = '+'; break;
					case 1: atmp.c = atmp.a-atmp.b; atmp.op = '-'; break;
					case 2: atmp.c = atmp.a*atmp.b; atmp.op = '*'; break;
					case 3: atmp.c = atmp.a/atmp.b; atmp.op = '/'; break;
				}
				cur = h[hash][l].pre;
				break;
			}
		vans.push_back(atmp);
	}
	if (vans.size())
		for (int i = vans.size()-1; i >= 0; i--) printf("%d %c %d = %d\n", vans[i].a, vans[i].op, vans[i].b, vans[i].c);
	printf("Best approx: %d\n\n", ans);
	for (int i = 0; i < 120007; i++) h[i].clear();
}
int main() {
	int T;
	for (scanf("%d", &T); T--; solve());
	return 0;
}
