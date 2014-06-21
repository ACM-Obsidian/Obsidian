#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAXN = 1000100;

inline int fim(int x) {
	if (x == 'A') return 0;
	if (x == 'C') return 1;
	if (x == 'G') return 2;
	if (x == 'T') return 3;
}

struct Node {
	Node *ch[4]; vector<int> End; int deep, r;
}*root, POOL[MAXN], *data = POOL;

int n; char ch[MAXN];
Node *d[MAXN];

vector<pair<int, int> > Ans; long long ret = 0;

int main(void) {
	// freopen("in", "r", stdin);
	scanf("%d", &n); root = data++;
	for (int i = 1; i <= n; i++) {
		scanf("%s", ch); int len = strlen(ch);
		Node *tmp = root;
		for (int j = 0; j < len; j++) {
			int x = fim(ch[j]);
			if (!tmp->ch[x]) tmp->ch[x] = data++;
			tmp = tmp->ch[x];
		}
		tmp->End.push_back(i);
	}
	int head = 1, tail = 1; d[1] = root;
	while (head <= tail) {
		Node *now = d[head++];
		for (int i = 0; i < 4; i++) if (now->ch[i]) d[++tail] = now->ch[i], now->ch[i]->deep = now->deep + 1;
	}
	for (int i = tail; i >= 1; i--) {
		Node *now = d[i];
		for (int j = 0; j < 4; j++) if (now->ch[j] && now->ch[j]->r != 0) now->End.push_back(now->ch[j]->r);
		int t = 0;
		if (now->End.size() & 1) now->r = now->End[0], t = 1;
		for (int j = t; j < now->End.size(); j += 2) {
			ret += now->deep;
			Ans.push_back(make_pair(now->End[j], now->End[j + 1]));
		}
	}
	printf("%lld\n", ret);
	for (int i = 0; i < Ans.size(); i++) printf("%d %d\n", Ans[i].first, Ans[i].second);
	return 0;
}

