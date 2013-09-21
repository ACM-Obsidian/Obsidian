#include <cstring> 
#include <cstdio> 
#include <algorithm> 
#include <cctype> 

using namespace std;

const int MAXN = 200010; 
const int MAXM = 10010; 

inline int ScanInt(void) { 
    int r = 0, c; 
    while (!isdigit(c = getchar())); 
    r = c - '0'; 
    while ( isdigit(c = getchar())) r = r * 10 + c - '0'; 
    return r; 
} 

int n, m, k, a[MAXN], b[MAXN], p[MAXN], MAXH = 0;

void Input(void) { 
    for (int i = 1; i <= n; i++) MAXH = std::max(MAXH, a[i] = ScanInt()); 
    for (int j = 1; j <= m; j++) MAXH = std::max(MAXH, b[j] = ScanInt()); 
} 

class BIT {public: 
    int a[MAXM], n; 
    inline void Add(int u, int t) { 
        for (;u <= n; u += (u&-u)) a[u] += t; 
    } 
    inline int Cal(int u) { 
        int ret = 0; 
        for (;u;u-=(u&-u)) ret += a[u]; 
        return ret; 
    } 
    inline void clear(void) { memset(a, 0, sizeof a); } 
}; 

BIT T; 
pair<int, int> rank[MAXN]; 

inline void Prepare(void) { 
    T.clear(); T.n = MAXH; 
    for (int i = 1; i <= m; i++) { 
        rank[i] = make_pair(T.Cal(b[i] - 1) + 1, T.Cal(b[i]));
        T.Add(b[i], 1); 
    }
}

int last; 
inline pair<int, int> Ask(int a[], int L, int t) { 
    while (last < L) 
        T.Add(a[last++], -1); 
    return make_pair(T.Cal(t - 1) + 1, T.Cal(t));
} 

int Ans[MAXN], f[MAXN];

inline void Work(void) { 
    T.clear(); T.Add(b[1], 1); 
    int j = 0; last = 1; 
    for (int i = 2; i <= m; i++) { 
        while (j && Ask(b, i - j, b[i]) != rank[j + 1])  
            j = p[j]; 
        if (j == 0) Ask(b, i - j, b[i]);
        if (Ask(b, i - j, b[i]) == rank[j + 1]) j++; 
        p[i] = j; 
        T.Add(b[i], 1); 
    }
    T.clear(); 
    j = 0; last = 1; 
    for (int i = 1; i <= n; i++) { 
        while (j && Ask(a, i - j, a[i]) != rank[j + 1])
            j = p[j]; 
        if (j == 0) Ask(a, i - j, a[i]);
        if (Ask(a, i - j, a[i]) == rank[j + 1]) j++; 
        if (j == m) { 
            Ans[i] = true;
            j = p[j]; 
        } 
        T.Add(a[i], 1); 
    }
    f[0] = 0;
    for (int i = 1; i <= n; i++) {
//        printf("%d ", Ans[i]);
        f[i] = f[i - 1];
        if (Ans[i] > 0) f[i] = max(f[i], f[i - m] + 1);
    }
//    puts("");
    printf("%d\n", f[n]);
} 

inline void clear(void) {
    MAXH = last = 0;
    memset(a, 0, sizeof a);
    memset(b, 0, sizeof b);
    memset(p, 0, sizeof p);
    memset(rank, 0, sizeof rank);
    memset(Ans, 0, sizeof Ans);
    memset(f, 0, sizeof f);
}

void solve(void) { 
    while (scanf("%d%d%d", &n, &m, &k) == 3) {
        clear();
        Input(); 
        Prepare(); 
        Work(); 
    }
} 
int main(int argc, char** argv) { 
//    freopen("in", "r", stdin); 
    solve(); 
    return 0; 
}

