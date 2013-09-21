#include <cstdio>
#include <cstring>
int a[100][100], n, c[100];
int dfs(int k) {
    for (int i = 0; i < n; i++)
        if (i != k && a[k][i])
            if (c[i] == -1) {
                c[i] = !c[k];
                if (!dfs(i)) return 0;
            } else if (c[i] == c[k])
                return 0;
    return 1;
}
void solve() {
    memset(a, 0, sizeof a);
    for (int i = 0; i < n; i++) {
        int x;
        for (; scanf("%d", &x), x; a[i][x-1] = 1);
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) if (i != j)
            a[i][j] = !a[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j && a[i][j]) a[j][i] = 1;
    memset(c, -1, sizeof c);
    int flag = 1;
    for (int i = 0; i < n; i++)
        if (c[i] == -1 && (c[i] = 0, !dfs(i))) {
            flag = 0;
            break;
        }
    puts(flag ? "YES" : "NO");
}
int main() {
    for (; scanf("%d", &n) != EOF; ) solve();
    return 0;
}

