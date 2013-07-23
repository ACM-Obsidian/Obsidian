#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;

const double inf = 1e+100;
typedef pair<double, double> pdd;
typedef pair<pdd, pdd> line;
#define X first
#define Y second

// 以下是模板

const double eps = 1e-08, dlt = 1e-05;
inline int fi (double a)
{
    return a > eps ? 1 : (a < -eps ? -1 : 0);
}
inline pdd operator* (const pdd& a, double b)
{
    return pdd(a.X * b, a.Y * b);
}
inline pdd operator* (double a, const pdd& b)
{
    return b * a;
}
inline pdd operator+ (const pdd& a, const pdd& b)
{
    return pdd(a.X + b.X, a.Y + b.Y);
}
inline pdd operator- (const pdd& a, const pdd& b)
{
    return pdd(a.X - b.X, a.Y - b.Y);
}
inline double operator* (const pdd& a, const pdd& b)
{
    return a.X * b.Y - a.Y * b.X;
}
inline double dot (const pdd& a, const pdd& b)
{
    return a.X * b.X + a.Y * b.Y;
}
inline double len (const pdd& a)
{
    return sqrt(a.X * a.X + a.Y * a.Y);
}
inline double len (const line& a)
{
    return len(a.Y - a.X);
}
inline bool on (const pdd& a, const line& b)
{
    // double v = fi((a - b.X) * (b.Y - b.X));
    double x1 = min(b.X.X, b.Y.X), x2 = max(b.X.X, b.Y.X);
    double y1 = min(b.X.Y, b.Y.Y), y2 = max(b.X.Y, b.Y.Y);
    return fi(a.X - x1) >= 0 && fi(a.X - x2) <= 0 && fi(a.Y - y1) >= 0 && fi(a.Y - y2) <= 0;
}
bool parallel;
inline pdd intersect (const line& a, const line& b)
{
    double s1 = (b.X - a.Y) * (b.Y - a.Y);
    double s2 = (b.Y - a.X) * (b.X - a.X);
    double s = s1 + s2;
    if (!fi(s))
    {
        parallel = true;
        return pdd(0, 0);
    }
    parallel = false;
    s1 /= s, s2 /= s;
    return a.X * s1 + a.Y * s2;
}
inline pdd symm (const pdd& a, const line& b)
{
    pdd v = b.Y - b.X, u = a - b.X;
    pdd p = u - v * (dot(u, v) / dot(v, v));
    return a - 2 * p;
}

// 以上是模板

const int N = 310;
pdd city[N]; line barr[N];
double dist[N][N];
int n, m, seq[N];

inline pdd fetch (int a)
{
    // 0 ~ N - 1: cities
    // N ~ N + M - 1: barr 的起点
    // N + M ~ N + 2M - 1: barr 的终点
    if (a < n) return city[a];
    else if (a < n + m) return barr[a - n].X;
    else return barr[a - n - m].Y;
}
inline int barrCheck (int a)
{
    if (a < n) return -1;
    else if (a < n + m) return a - n;
    else return a - n - m;
}
bool valid (const line& a, int p1, int p2)
{
    p1 = barrCheck(p1), p2 = barrCheck(p2);
    for (int i = 0; i < m; i++)
    {
        if (i == p1 || i == p2) continue;
        pdd r = intersect(a, barr[i]);
        // printf("CHECK %d: PARALLEL %d, (%f, %f)\n", i, parallel, r.X, r.Y);
        if (parallel)
        {
            if (on(a.X, barr[i]) || on(a.Y, barr[i]) || on(barr[i].X, a) || on(barr[i].Y, a))
                return false;
        }
        else
        {
            if (on(r, barr[i]) && on(r, a))
                return false;
        }
    }
    return true;
}

// 这下面是计算最小需要几条链，只有长度不大于 mp 才算合法边。
// ……改这儿就行

bool sch[N];
int match[N];
inline bool find (int x, double mp)
{
    for (int i = x + 1; i < n; i++) if (!sch[i] && fi(dist[seq[x]][seq[i]] - mp) <= 0)
    {
        sch[i] = true;
        if (match[i] == -1 || find(match[i], mp))
        {
            match[i] = x;
            return true;
        }
    }
    return false;
}
// 计算需要多少条链
inline int count (double mp)
{
    memset(match, -1, sizeof match);
    int res = 0;
    for (int i = 0; i < n; i++)
    {
        memset(sch, 0, sizeof sch);
        if (find(i, mp)) res++;
    }
    return n-res;
}

int main ()
{
    int kase; for (scanf("%d", &kase); kase; --kase)
    {
        int p; scanf("%d %d %d", &n, &m, &p);
        for (int i = 0; i < n; i++)
        {
            double x, y; scanf("%lf %lf", &x, &y);
            city[i] = pdd(x, y);
        }
        for (int i = 0; i < m; i++)
        {
            double sx, sy, ex, ey; scanf("%lf %lf %lf %lf", &sx, &sy, &ex, &ey);
            barr[i] = line(pdd(sx, sy), pdd(ex, ey));
        }
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &seq[i]);
            --seq[i];
        }
        int mx = n + 2 * m;
        for (int i = 0; i < mx; i++)
        {
            dist[i][i] = 0;
            for (int j = i + 1; j < mx; j++)
            {
                line tar = line(fetch(i), fetch(j));
                if (valid(tar, i, j))
                {
                    dist[i][j] = dist[j][i] = len(tar);
                }
                else
                {
                    dist[i][j] = dist[j][i] = inf;
                }
                // printf("DIST %d %d = %f\n", i, j, dist[i][j]);
            }
        }
        for (int k = 0; k < mx; k++)
            for (int i = 0; i < mx; i++)
                for (int j = 0; j < mx; j++)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        double l = 0, r = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) r = max(r, dist[i][j]);

        // 二分答案
        while (r - l > dlt)
        {
            double mid = (l + r) * 0.5;
            if (count(mid) > p) l = mid;
            else r = mid;
            // printf("L = %f, R = %f, MID = %f\n", l, r, mid);
        }
        printf("%.2f\n", r);
    }
    return 0;
}