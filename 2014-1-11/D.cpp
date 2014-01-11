#include <cstdio>
#include <cstring>
struct node {
	int e;
	node *s[26];
} *root1, *root2, stack[1000000];
char s[10000][41];
int top, cnt[26];
long long ans;
void dfs2(node *p) {
	for (int i = 0; i < 26; i++)
		if (p->s[i] != NULL) {
			cnt[i]++;
			dfs2(p->s[i]);
		}
}
void dfs1(node *p) {
	for (int i = 0; i < 26; i++)
		if (p->s[i] != NULL) {
			if (root2->s[i] != NULL && p != root1 && !p->s[i]->e) ans++;
			dfs1(p->s[i]);
		} else if (p != root1)
			ans += cnt[i];
}
int main() {
	int n; scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%s", s[i]);
	root1 = &stack[top++];
	for (int i = 0; i < n; i++) {
		node *p = root1;
		for (int j = 0, l = strlen(s[i]); j < l; j++) {
			if (p->s[s[i][j]-97] == NULL)
				p->s[s[i][j]-97] = &stack[top++];
			p = p->s[s[i][j]-97];
		}
		if (!p->e) {
			ans++;
			p->e = 1;
		}
	}
	root2 = &stack[top++];
	for (int i = 0; i < n; i++) {
		node *p = root2;
		for (int j = strlen(s[i])-1; j >= 0; j--) {
			if (p->s[s[i][j]-97] == NULL)
				p->s[s[i][j]-97] = &stack[top++];
			p = p->s[s[i][j]-97];
		}
	}
	dfs2(root2);
	dfs1(root1);
	printf("%lld\n", ans);
	return 0;
}
