#include <cstdio> 
#include <algorithm> 
#include <cstring> 
namespace Solve { 
    typedef long long Int64; 
    const int MAXN = 200020; 
      
    int n; 
    Int64 S[MAXN], E[MAXN], D[MAXN], Sum[MAXN]; 
    inline Int64 Cal(int i, Int64 P) { 
        if (P > E[i]) return Sum[i]; 
        if (P < S[i]) return 0; 
        Int64 cnt = (P - S[i]) / D[i] + 1; 
        return cnt; 
    } 
  
    inline void clear(void) {
        memset(S, 0, sizeof S);
        memset(E, 0, sizeof E);
        memset(D, 0, sizeof D);
        memset(Sum, 0, sizeof Sum);
    }

    void solve(void) { 
        while (scanf("%d", &n) == 1) {
            clear();
            Int64 l = 0, r = 0; 
            for (int i = 1; i <= n; i++) scanf("%I64d%I64d%I64d", S + i, E + i, D + i), r = std::max(r, E[i]); 
            Int64 SoS = 0; 
            for (int i = 1; i <= n; i++) SoS += (Sum[i] = Cal(i, E[i])); 
            if (SoS % 2 == 0) { 
                puts("DC Qiang is unhappy."); 
                continue;
            }
            while (l <= r) { 
                Int64 mid = (l + r) >> 1; 
                Int64 tmp = 0; 
                for (int i = 1; i <= n; i++) tmp += Cal(i, mid); 
                if (tmp & 1) 
                    r = mid - 1; 
                else
                    l = mid + 1; 
            } 
            Int64 S2 = 0, S1 = 0; 
            for (int i = 1; i <= n; i++) S1 += Cal(i, l - 1), S2 += Cal(i, l); 
            printf("%I64d %I64d\n", l, S2 - S1); 
        }
    } 
} 
int main(int argc, char** argv) { 
    //freopen("in", "r", stdin); 
    Solve::solve(); 
    return 0; 
}
