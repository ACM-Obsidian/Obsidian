#include <cstdio>
#include <cstring>
#include <vector>
struct tree {
	char op;
	tree *l, *r;
} *root, *root2;
char s[1003], stack[1000];
tree *tstack[1000];
int top, ttop, l, prec[256], res[2][2048], len[2], val[2048], u[2048], v[2048];
int eval(tree *t, int i) {
	if (t->op >= 'a' && t->op <= 'k') return i>>t->op-'a'&1;
	else {
		int x = eval(t->r, i), y;
		if (t->op != '~') y = eval(t->l, i);
		switch(t->op) {
			case '~': return !x; break;
			case '&': return x&&y; break;
			default: return x||y;
		}
	}
}
void dfs(tree *t) {
	if (t->l != NULL) {
		if (t->op == '&' && t->l->op == '|') putchar('(');
		dfs(t->l);
		if (t->op == '&' && t->l->op == '|') putchar(')');
	}
	putchar(t->op);
	if (t->r != NULL) {
		if (t->op == '&' && t->r->op == '|') putchar('(');
		dfs(t->r);
		if (t->op == '&' && t->r->op == '|') putchar(')');
	}
}
int solve(tree *&t, int mask, int sample) {
	if (mask == 0) return 0;
	if (mask == (mask&-mask)) {
		tree *u = new tree;
		u = new tree;
		u->op = 'a'+__builtin_ctz(mask);
		u->l = u->r = NULL;
		if (!val[mask|sample]) {
			t = new tree;
			t->op = '~';
			t->l = NULL, t->r = u;
		} else t = u;
		return 1;
	}
	std::vector<int> valv[2], tmp;
	for (int i = mask; ; (--i) &= mask) {
		valv[val[i|sample]].push_back(i);
		if (i == 0) break;
	}
	for (int i = mask; i; (--i) &= mask) {
		if (i == mask) continue;
		int cntu = 0, cntv = 0;
		for (int j = 0; j < valv[0].size(); j++) {
			if (!u[valv[0][j] & i]) u[valv[0][j] & i] = 1, cntu++;
			if (!v[valv[0][j] & mask-i]) v[valv[0][j] & mask-i] = 1, cntv++;
		}
		for (int j = 0; j < valv[0].size(); j++)
			u[valv[0][j] & i] = 0, v[valv[0][j] & mask-i] = 0;
		if (cntu*cntv == valv[0].size()) {
			t = new tree;
			t->op = '|';
			return solve(t->l, i, sample|valv[0][0]&mask-i) && solve(t->r, mask-i, sample|valv[0][0]&i);
		}
		cntu = cntv = 0;
		for (int j = 0; j < valv[1].size(); j++) {
			if (!u[valv[1][j] & i]) u[valv[1][j] & i] = 1, cntu++;
			if (!v[valv[1][j] & mask-i]) v[valv[1][j] & mask-i] = 1, cntv++;
		}
		for (int j = 0; j < valv[1].size(); j++)
			u[valv[1][j] & i] = 0, v[valv[1][j] & mask-i] = 0;
		if (cntu*cntv == valv[1].size()) {
			t = new tree;
			t->op = '&';
			return solve(t->l, i, sample|valv[1][0]&mask-i) && solve(t->r, mask-i, sample|valv[1][0]&i);
		}
	}
	return 0;
}
int main() {
	freopen("formula.in", "r", stdin);
	freopen("formula.out", "w", stdout);
	s[0] = '(';
	gets(s+1);
	l = strlen(s);
	s[l++] = ')';
	prec['('] = -1, prec['&'] = 1, prec['|'] = 0, prec['~'] = 2;
	for (int i = 0; i < l; i++)
		if (s[i] == '(')
			stack[top++] = '(';
		else if (s[i] == ')') {
			for (; stack[top-1] != '('; top--) {
				tree *t = new tree;
				t->op = stack[top-1], t->l = tstack[ttop-2], t->r = tstack[ttop-1];
				ttop--;
				tstack[ttop-1] = t;
			}
			top--;
		} else if (s[i] == '(' || s[i] == '&' || s[i] == '|' || s[i] == '~') {
			if (s[i] == '~') tstack[ttop++] = NULL;
			else
				for (; prec[stack[top-1]] >= prec[s[i]]; top--) {
					tree *t = new tree;
					t->op = stack[top-1], t->l = tstack[ttop-2], t->r = tstack[ttop-1];
					ttop--;
					tstack[ttop-1] = t;
				}
			stack[top++] = s[i];
		} else if (s[i] >= 'a' && s[i] <= 'k') {
			tree *t = new tree;
			t->op = s[i];
			t->l = t->r = NULL;
			tstack[ttop++] = t;
		}
	root = tstack[0];
	for (int i = 0; i < 1<<11; i++) val[i] = eval(root, i);
	int mask = 0;
	for (; mask < 1<<11; mask++) {
		int flag = 1;
		for (int i = 0; i < 1<<11; i++)
			if (val[i] != val[i&mask]) flag = 0;
		if (flag) break;
	}
	if (solve(root2, mask, 0)) {
		puts("Yes");
		dfs(root2); puts("");
	} else puts("No");
	return 0;
}
