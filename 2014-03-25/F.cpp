#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <map>
using namespace std;

typedef pair<int, int> pii;
#define X first
#define Y second

int m, n;

struct status
{
	pii pl[8];
	bool operator < (const status& s) const
	{
		for (int i = 0; i < m; i++) if (pl[i] != s.pl[i]) return pl[i] < s.pl[i];
		return false;
	}
	bool operator == (const status& s) const
	{
		for (int i = 0; i < m; i++) if (pl[i] != s.pl[i]) return false;
		return true;
	}
	void show (void) const
	{
		printf("STATUS:");
		for (int i = 0; i < m; i++) printf(" (%d, %d)", pl[i].X, pl[i].Y);
	}
};

char board[4][4];
bool access[4][4][4];

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

inline bool in (int x, int y)
{
	return x >= 0 && x < n && y >= 0 && y < n;
}

bool valid;
status move (const status& s, int dir)
{
	char tb[4][4];
	char fill[4][4];
	memset(tb, -1, sizeof tb);
	memset(fill, 0, sizeof fill);
	for (int i = 0; i < m; i++)
	{
		int tx = s.pl[i].X, ty = s.pl[i].Y;
		if (board[tx][ty] == i)
		{
			fill[tx][ty] = 1;
		}
		else
		{
			tb[tx][ty] = i;
		}
	}
	status res;

	if (dir == 0)
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) if (tb[i][j] >= 0)
			{
				int tj = j, ttj = tj - 1; // Modify here
				while (in(i, ttj) && tb[i][ttj] == -1 && access[i][tj][dir])
				{
					if (board[i][ttj] == -1 || fill[i][ttj])
					{
						tb[i][ttj] = tb[i][tj];
						tb[i][tj] = -1;
						tj = ttj;
						ttj = tj - 1; // Modify here
					}
					else // a hole!
					{
						if (board[i][ttj] == tb[i][tj])
						{
							tb[i][tj] = -1;
							fill[i][ttj] = 1;
							break;
						}
						else
						{
							valid = false;
							return res;
						}
					}
				}
			}
	}
	else if (dir == 1)
	{
		for (int i = 0; i < n; i++)
			for (int j = n - 1; j >= 0; j--) if (tb[i][j] >= 0)
			{
				int tj = j, ttj = tj + 1; // Modify here
				while (in(i, ttj) && tb[i][ttj] == -1 && access[i][tj][dir])
				{
					if (board[i][ttj] == -1 || fill[i][ttj])
					{
						tb[i][ttj] = tb[i][tj];
						tb[i][tj] = -1;
						tj = ttj;
						ttj = tj + 1; // Modify here
					}
					else // a hole!
					{
						if (board[i][ttj] == tb[i][tj])
						{
							tb[i][tj] = -1;
							fill[i][ttj] = 1;
							break;
						}
						else
						{
							valid = false;
							return res;
						}
					}
				}
			}
	}
	else if (dir == 2)
	{
		for (int j = 0; j < n; j++)
			for (int i = 0; i < n; i++) if (tb[i][j] >= 0)
			{
				int ti = i, tti = ti - 1; // Modify here
				while (in(tti, j) && tb[tti][j] == -1 && access[ti][j][dir])
				{
					if (board[tti][j] == -1 || fill[tti][j])
					{
						tb[tti][j] = tb[ti][j];
						tb[ti][j] = -1;
						ti = tti;
						tti = ti - 1; // Modify here
					}
					else // a hole!
					{
						if (board[tti][j] == tb[ti][j])
						{
							tb[ti][j] = -1;
							fill[tti][j] = 1;
							break;
						}
						else
						{
							valid = false;
							return res;
						}
					}
				}
			}
	}
	else // if (dir == 3)
	{
		for (int j = 0; j < n; j++)
			for (int i = n - 1; i >= 0; i--) if (tb[i][j] >= 0)
			{
				int ti = i, tti = ti + 1; // Modify here
				while (in(tti, j) && tb[tti][j] == -1 && access[ti][j][dir])
				{
					if (board[tti][j] == -1 || fill[tti][j])
					{
						tb[tti][j] = tb[ti][j];
						tb[ti][j] = -1;
						ti = tti;
						tti = ti + 1; // Modify here
					}
					else // a hole!
					{
						if (board[tti][j] == tb[ti][j])
						{
							tb[ti][j] = -1;
							fill[tti][j] = 1;
							break;
						}
						else
						{
							valid = false;
							return res;
						}
					}
				}
			}
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (tb[i][j] != -1)
				res.pl[(int)tb[i][j]] = pii(i, j);
			if (board[i][j] != -1 && fill[i][j])
				res.pl[(int)board[i][j]] = pii(i, j);
		}
	valid = true;
	return res;
}

const int N = 200010;
map<status, int> hash;
status que[N];

int main ()
{
	int w, kase = 0; while (scanf("%d %d %d", &n, &m, &w), n)
	{
		memset(board, -1, sizeof board);
		memset(access, 1, sizeof access);
		status init, tar;

		for (int i = 0; i < m; i++)
		{
			int x, y; scanf("%d %d", &x, &y);
			init.pl[i] = pii(x, y);
		}
		for (int i = 0; i < m; i++)
		{
			int x, y; scanf("%d %d", &x, &y);
			board[x][y] = i, tar.pl[i] = pii(x, y);
		}
		for (int i = 0; i < w; i++)
		{
			int x1, y1, x2, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			for (int j = 0; j < 4; j++)
			{
				if (x1 + dx[j] == x2 && y1 + dy[j] == y2) access[x1][y1][j] = false;//, printf("BLOCKED %d %d %d\n", x1, y1, j);
			}
			for (int j = 0; j < 4; j++)
			{
				if (x2 + dx[j] == x1 && y2 + dy[j] == y1) access[x2][y2][j] = false;//, printf("BLOCKED %d %d %d\n", x2, y2, j);
			}
		}
		int l = 0, r = 0;
		que[r++] = init;
		hash.clear();
		hash[init] = 0;
		while (r > l)
		{
			status c = que[l++];
			// printf("THIS STATUS: ");
			// c.show();
			// printf(" MOVES = %d\n", hash[c]);
			for (int i = 0; i < 4; i++)
			{
				status t = move(c, i);
				if (valid)
				{
					// printf("MOVE %d: ", i);
					// t.show(); printf("\n");
					if (hash.find(t) == hash.end())
					{
						que[r++] = t;
						hash[t] = hash[c] + 1;
					}
				}
			}
		}
		++kase;
		printf("Case %d: ", kase);
		if (hash.find(tar) == hash.end()) printf("impossible\n");
		else printf("%d moves\n", hash[tar]);
		puts("");
	}
	return 0;
}
