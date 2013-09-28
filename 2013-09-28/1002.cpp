#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

const int N = 1000010;
int ch[N][2];
int mr;
set<int> mark[N];

inline int tran (int a, char bres[])
{
    for (int i = 0; i < 8; i++)
    {
        bres[7 - i] = (a & 1);
        a >>= 1;
    }
    bres[8] = 0;
}
char ip1[40], ip2[40];
inline void cat (int a, int b, int c, int d, char ip[])
{
    tran(a, ip);
    tran(b, ip + 8);
    tran(c, ip + 16);
    tran(d, ip + 24);
}

inline int newnode (void)
{
    ch[mr][0] = ch[mr][1] = -1;
    return mr++;
}
int ins (char ip[], int len, int id)
{
    int now = 0;
    for (int i = 0; i < len; i++)
    {
        if (ch[now][ip[i]] == -1) ch[now][ip[i]] = newnode();
        now = ch[now][ip[i]];
    }
    mark[now].insert(id);
    // printf("ADD %d %d\n", now, id);
    return now;
}
vector<int> mem[1100];
void del (int id)
{
    for (int i = 0; i < mem[id].size(); i++)
    {
        mark[mem[id][i]].erase(id);
        // printf("DEL %d %d\n", mem[id][i], id);
    }
    mem[id].clear();
}
bool sch[1100];
bool query (char ip[], bool ins)
{
    if (ins) memset(sch, 0, sizeof sch);
    int now = 0;
    for (int i = 0; i < 32; i++)
    {
        if (ch[now][ip[i]] == -1) return false;
        now = ch[now][ip[i]];
        // printf("%d: CHECK %d\n", ins, now);
        for (set<int>::iterator ite = mark[now].begin(); ite != mark[now].end(); ++ite)
        {
            if (!ins && sch[*ite]) return true;
            if (ins) sch[*ite] = true;
        }
    }
    return false;
}

int main ()
{
    mr = 0;
    newnode();
    char cmd[5];
    while (scanf("%s", cmd) == 1)
    {
        if (cmd[0] == 'E')
        {
            int id, n; scanf("%d %d", &id, &n);
            del(id);
            for (int i = 0; i < n; i++)
            {
                int a, b, c, d, len;
                scanf("%d.%d.%d.%d/%d", &a, &b, &c, &d, &len);
                cat(a, b, c, d, ip1);
                
                // for (int i = 0; i < 32; i++) printf("%d", ip1[i]); printf("\n");
                
                int tt = ins(ip1, len, id);
                mem[id].push_back(tt);
            }
        }
        else if (cmd[0] == 'D')
        {
            int id; scanf("%d", &id);
            del(id);
        }
        else // F
        {
            int a, b, c, d;
            scanf("%d.%d.%d.%d", &a, &b, &c, &d);
            cat(a, b, c, d, ip1);
            scanf("%d.%d.%d.%d", &a, &b, &c, &d);
            cat(a, b, c, d, ip2);
            
            // for (int i = 0; i < 32; i++) printf("%d", ip1[i]); printf("\n");
            // for (int i = 0; i < 32; i++) printf("%d", ip2[i]); printf("\n");
            bool same = true;
            for (int i = 0; same && i < 32; i++)
                if (ip1[i] != ip2[i]) same = false;
            // if (same) printf("F\n");
            // else
            // {
                query(ip1, true);
                printf("%s\n", query(ip2, false) ? "F" : "D");
            // }
        }
    }   
    return 0;
}
