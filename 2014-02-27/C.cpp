#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>
#include <cassert>
using namespace std;
 
inline int id (char color)
{
    switch (color)
    {
        case 'W': return 0;
        case 'R': return 1;
        default: return 2;
    }
}
 
int front[6] = {2, 4, 0, 5, 1, 3};
int left[6] = {5, 3, 4, 1, 2, 0};
 
struct status
{
    char st[3][3];
    int getHash(void) {
        int ret = 0;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) ret = ret * 7 + (st[i][j]+ 1);
        return ret;
    }
    bool operator < (const status& a) const
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (st[i][j] != a.st[i][j]) return st[i][j] < a.st[i][j];
        return false;
    }
};
inline bool in (int x, int y)
{
    return x >= 0 && x < 3 && y >= 0 && y < 3;
}
 
int goal[3][3];
const int MAXH = 44000007;
 
map<int, int> step1, step2;

const int quemax = 1 << 21;
const int quemask = quemax - 1;
 
int l = 0, r = 0;
status que[quemax];
 
void add_queue (int crd, status st)
{
    if (crd == 9)
    {
        que[r++] = st;
        step2[st.getHash()] = 0;
        return;
    }
    int x = crd / 3, y = crd % 3;
    if (goal[x][y] == -1)
    {
        st.st[x][y] = -1;
        add_queue(crd + 1, st);
    }
    else
    {
        st.st[x][y] = goal[x][y] * 2;
        add_queue(crd + 1, st);
        st.st[x][y] = goal[x][y] * 2 + 1;
        add_queue(crd + 1, st); 
	}
}
 
int main ()
{
    freopen("C.txt", "r", stdin);
    int x, y; while (scanf("%d %d", &x, &y), x)
    {
		step1.clear();
        status init;
        memset(init.st, 0, sizeof init.st);
        init.st[y - 1][x - 1] = -1;
        step1[init.getHash()] = 0;
        l = r = 0;
        que[r++] = init;
        while (r != l)
        {
            status c = que[(l++) & quemask];
            int st = step1[c.getHash()];
            if (st == 19) continue;
 
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (c.st[i][j] != -1)
                    {
                        if (in(i - 1, j) && c.st[i - 1][j] == -1) // up
                        {
                            status c2 = c;
                            c2.st[i - 1][j] = front[c.st[i][j]];
                            c2.st[i][j] = -1;
                            if (step1.find(c2.getHash()) == step1.end())
                            {
                                step1[c2.getHash()] = st + 1;
                                que[(r++) & quemask] = c2;
                            }
                        }
                        if (in(i + 1, j) && c.st[i + 1][j] == -1) // down
                        {
                            status c2 = c;
                            c2.st[i + 1][j] = front[c.st[i][j]];
                            c2.st[i][j] = -1;
                            if (step1.find(c2.getHash()) == step1.end())
                            {
                                step1[c2.getHash()] = st + 1;
                                que[(r++) & quemask] = c2;
                            }
                        }
                        if (in(i, j - 1) && c.st[i][j - 1] == -1) // left
                        {
                            status c2 = c;
                            c2.st[i][j - 1] = left[c.st[i][j]];
                            c2.st[i][j] = -1;
                            if (step1.find(c2.getHash()) == step1.end())
                            {
                                step1[c2.getHash()] = st + 1;
                                que[(r++) & quemask] = c2;
                            }
                        }
                        if (in(i, j + 1) && c.st[i][j + 1] == -1) // right
                        {
                            status c2 = c;
                            c2.st[i][j + 1] = left[c.st[i][j]];
                            c2.st[i][j] = -1;
                            if (step1.find(c2.getHash()) == step1.end())
                            {
                                step1[c2.getHash()] = st + 1;
                                que[(r++) & quemask] = c2;
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                char st[5];
                scanf("%s", st);
                goal[i][j] = (st[0] == 'E' ? -1 : id(st[0]));
            }
        }
		step2.clear();
        l = r = 0;
        add_queue(0, status());
        int ans = 100;
        while (r != l)
        {
            status c = que[(l++) & quemask];
            int st = step2[c.getHash()];
            if (step1.find(c.getHash()) != step1.end())
            {
                ans = min(step1[c.getHash()] + st, ans);
                continue;
            }
            else if (st == 11 || st >= ans) continue;
 
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (c.st[i][j] != -1)
                    {
                        if (in(i - 1, j) && c.st[i - 1][j] == -1) // up
                        {
                            status c2 = c;
                            c2.st[i - 1][j] = front[c.st[i][j]];
                            c2.st[i][j] = -1;
                            if (step2.find(c2.getHash()) == step2.end())
                            {
                                step2[c2.getHash()] = st + 1;
                                que[(r++) & quemask] = c2;
                            }
                        }
                        if (in(i + 1, j) && c.st[i + 1][j] == -1) // down
                        {
                            status c2 = c;
                            c2.st[i + 1][j] = front[c.st[i][j]];
                            c2.st[i][j] = -1;
                            if (step2.find(c2.getHash()) == step2.end())
                            {
                                step2[c2.getHash()] = st + 1;
                                que[(r++) & quemask] = c2;
                            }
                        }
                        if (in(i, j - 1) && c.st[i][j - 1] == -1) // left
                        {
                            status c2 = c;
                            c2.st[i][j - 1] = left[c.st[i][j]];
                            c2.st[i][j] = -1;
                            if (step2.find(c2.getHash()) == step2.end())
                            {
                                step2[c2.getHash()] = st + 1;
                                que[(r++) & quemask] = c2;
                            }
                        }
                        if (in(i, j + 1) && c.st[i][j + 1] == -1) // right
                        {
                            status c2 = c;
                            c2.st[i][j + 1] = left[c.st[i][j]];
                            c2.st[i][j] = -1;
                            if (step2.find(c2.getHash()) == step2.end())
                            {
                                step2[c2.getHash()] = st + 1;
                                que[(r++) & quemask] = c2;
                            }
                        }
                    }
                }
            }
        }
 
        if (ans > 30) printf("-1\n");
        else printf("%d\n", ans);
    }
    return 0;
}
