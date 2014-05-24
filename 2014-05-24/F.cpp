#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 1000010;

struct Node {
	Node *ch[2]; int l, r; long long dk, db, k, b;
	void Update(void) {
		k = ch[0]->k + ch[1]->k + (r - l + 1) * dk;
		b = ch[0]->b + ch[1]->b + (r - l + 1) * db;
	}
	void Set(long long k0, long long b0) {
		dk += k0, db += b0;
		k += k0 * (r - l + 1);
		b += b0 * (r - l + 1);
	}
	void Push(void) {
		if (dk || db) {
			ch[0]->Set(dk, db);
			ch[1]->Set(dk, db);
			dk = db = 0;
		}
	}
}*root, POOL[MAXN << 2], *data = POOL;

Node *Build(int l, int r) {
	Node *ret = data++;
	ret->l = l, ret->r = r;
	if (l == r) return ret;
	int mid = (l + r) >> 1;
	ret->ch[0] = Build(l, mid);
	ret->ch[1] = Build(mid + 1, r);
	return ret;
}

void Add(Node *now, int l, int r, long long k0, long long b0) {
	if (l > r) return;
	if (l <= now->l && now->r <= r) {
		now->Set(k0, b0);
		return;
	}
	now->Push();
	int mid = (now->l + now->r) >> 1;
	Add(now->ch[0], l, min(r, mid), k0, b0);
	Add(now->ch[1], max(mid + 1, l), r, k0, b0);
	now->Update();
}

long long Cal(Node *now, int l, int r, long long y) {
	if (l > r) return 0;
	if (l <= now->l && now->r <= r) {
		return now->k * y + now->b;
	}
	now->Push();
	int mid = (now->l + now->r) >> 1;
	return Cal(now->ch[0], l, min(r, mid), y) + Cal(now->ch[1], max(mid + 1, l), r, y);
}

struct Rect {
	int l, r, y, d, id;
	Rect(int l, int r, int y, int d, int id = 0):l(l), r(r), y(y), d(d), id(id){}
	bool operator <(const Rect& oth) const {
		return y < oth.y;
	}
};

vector<Rect> tmp;

int n, q; long long Ans[MAXN];

int main(void) {
//	freopen("in", "r", stdin);
	scanf("%d%d", &n, &q); int l, w, L = 1; scanf("%d%d", &l, &w);
	for (int i = 1; i <= n; i++) {
		int x1, y1, x2, y2; scanf("%d%d%d%d", &x1, &y1, &x2, &y2); L = max(L, x2);
		tmp.push_back(Rect(x1 + 1, x2, y1, -1));
		tmp.push_back(Rect(x1 + 1, x2, y2, 1));
	}
	for (int i = 1; i <= q; i++) {
		int x1, y1, x2, y2; scanf("%d%d", &x1, &y1); x2 = x1 + l, y2 = y1 + w; L = max(L, x2);
		tmp.push_back(Rect(x1 + 1, x2, y1, -1, i));
		tmp.push_back(Rect(x1 + 1, x2, y2, 1, i));
	}
	sort(tmp.begin(), tmp.end());
	root = Build(1, L);
	for (int i = 0; i < (int)tmp.size(); i++) {
		if (!tmp[i].id) {
			// printf("l: %d, r: %d, k: %d, b: %d\n", tmp[i].l, tmp[i].r, -tmp[i].d, tmp[i].d * tmp[i].y);
			Add(root, tmp[i].l, tmp[i].r, -tmp[i].d, tmp[i].d * tmp[i].y);
		} else {
			long long A = Cal(root, tmp[i].l, tmp[i].r, tmp[i].y);
			Ans[tmp[i].id] += tmp[i].d * A;
		}
	}
	for (int i = 1; i <= q; i++) printf("%lld\n", Ans[i]);
	return 0;
}

