#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

// -1: not searched; 0: draw; 1: win
int status[18000000];

inline int sgn (int x)
{
	if (x < 0) return -1;
	else if (x > 0) return 1;
	return 0;
}

typedef pair<int, int> pii;
#define X first
#define Y second

inline pii decode (int x)
{
	return pii(x >> 3, x & 7);
}
inline int encode (pii x)
{
	return (x.X << 3) | x.Y;
}
inline bool bMovable (int x, int y, int obs1, int obs2, int obs3)
{
	if (x == y) return false;
	pii xx = decode(x), yy = decode(y);
	if (abs(xx.X - yy.X) != abs(xx.Y - yy.Y)) return false;
	int r1 = sgn(yy.X - xx.X), r2 = sgn(yy.Y - xx.Y);
	while (xx.X >= 0 && xx.X <= 7 && xx.Y >= 0 && xx.Y <= 7)
	{
		if (encode(xx) == y) return true;
		else if (encode(xx) == obs1 || encode(xx) == obs2 || encode(xx) == obs3)
		{
			return false;
		}
		xx.X += r1, xx.Y += r2;
	}
	return false;
}

struct pack
{
	int ws1, ws2, wk, bk, hand;
	pack (void) {}
	pack (int _ws1, int _ws2, int _wk, int _bk, int _hand) :
		ws1(_ws1), ws2(_ws2), wk(_wk), bk(_bk), hand(_hand) {}
	pack (int x)
	{
		ws1 = x & 63; x >>= 6;
		ws2 = x & 63; x >>= 6;
		wk 	= x & 63; x >>= 6;
		bk  = x & 63; x >>= 6;
		hand = x & 1;
	}
	int encode ()
	{
		int res = hand;
		res <<= 1; res |= bk;
		res <<= 6; res |= wk;
		res <<= 6; res |= ws2;
		res <<= 6; res |= ws1;
		return res;
	}
	bool valid ()
	{
		if (hand == 0) // black finished: the king mustn't be taken
		{
			pii Bk = decode(bk);
			// white king takes black king
			pii Wk = decode(wk);
			if (abs(Wk.X - Bk.X) <= 1 && abs(Wk.Y - Bk.Y) <= 1) return false;
			// bishops
			if (bMovable(ws1, bk, ws2, wk, -1) || bMovable(ws2, bk, ws1, wk, -1)) return false;
			// no problem
			return true;
		}
		else // white finished: the king mustn't be taken, and bishops which are not protected mustn't be taken
		{
			pii Wk = decode(wk), Bk = decode(bk);
			// white king
			if (abs(Wk.X - Bk.X) <= 1 && abs(Wk.Y - Bk.Y) <= 1) return false;
			// bishop 1
			pii Ws1 = decode(ws1);
			if (!bMovable(ws2, ws1, wk, bk, -1) && (abs(Wk.X - Ws1.X) > 1 || abs(Wk.Y - Ws1.Y) > 1)) // not protected
			{
				if (abs(Bk.X - Ws1.X) <= 1 && abs(Bk.Y - Ws1.Y) <= 1) return false;
			}
			// bishop 2
			pii Ws2 = decode(ws2);
			if (!bMovable(ws1, ws2, wk, bk, -1) && (abs(Wk.X - Ws2.X) > 1 || abs(Wk.Y - Ws2.Y) > 1)) // not protected
			{
				if (abs(Bk.X - Ws2.X) <= 1 && abs(Bk.Y - Ws2.Y) <= 1) return false;
			}
			// no problem
			return true;
		}
	}
	bool bCheckmate (void)
	{
		if (bMovable(ws1, bk, ws2, wk, -1) || bMovable(ws2, bk, ws1, wk, -1)) return true;
		else return false;
	}
	bool occu (int x)
	{
		return x == wk || x == ws1 || x == ws2 || x == bk;
	}
	void debug (void)
	{
		pii Ws1(decode(ws1)), Ws2(decode(ws2)), Wk(decode(wk)), Bk(decode(bk));
		printf("STATUS: WS1 (%d, %d), WS2 (%d, %d), WK (%d, %d), BK (%d, %d), HAND %d\n", Ws1.X, Ws1.Y, Ws2.X, Ws2.Y, Wk.X, Wk.Y, Bk.X, Bk.Y, hand);
	}
};
inline int readPl (void)
{
	char t[5]; scanf("%s", t);
	return encode(pii(t[0] - 'a', t[1] - '0'));
}

int dfs (int st)
{
	if (status[st] != -1) return status[st];
	status[st] = 0;
	pack now(st);
	printf("DFS: ");
	now.debug();
	if (now.hand == 0) // white
	{
		// bishop 1
		for (int i = 0; i < 64; i++) if (!now.occu(i) && bMovable(now.ws1, i, now.ws2, now.wk, now.bk))
		{
			pack tg(now);
			tg.ws1 = i;
			tg.hand ^= 1;
			if (tg.valid())
			{
				if (dfs(tg.encode()))
				{
					now.debug(); printf("RES 1\n");
					return status[st] = 1;
				}
			}
		}
		// bishop 2
		for (int i = 0; i < 64; i++) if (!now.occu(i) && bMovable(now.ws2, i, now.ws1, now.wk, now.bk))
		{
			pack tg(now);
			tg.ws2 = i;
			tg.hand ^= 1;
			if (tg.valid())
			{
				if (dfs(tg.encode()))
				{
					now.debug(); printf("RES 1\n");
					return status[st] = 1;
				}
			}
		}
		// wk
		pii Wk = decode(now.wk);
		for (int x = -1; x < 1; ++x)
			for (int y = -1; y < 1; ++y)
			{
				if (x == 0 && y == 0) continue;
				if (Wk.X + x < 0 || Wk.X + x > 7 || Wk.Y + y < 0 || Wk.Y + y > 7) continue;
				int i = encode(pii(Wk.X + x, Wk.Y + y));
				if (!now.occu(i))
				{
					pack tg(now);
					tg.wk = i;
					tg.hand ^= 1;
					if (tg.valid())
					{
						if (dfs(tg.encode()))
						{
							now.debug(); printf("RES 1\n");
							return status[st] = 1;
						}
					}
				}
			}
		now.debug(); printf("RES 0\n");
		return status[st] = 0;
	}
	else // black
	{
		bool nowhere = true;
		pii Bk = decode(now.bk);
		for (int x = -1; x < 1; ++x)
			for (int y = -1; y < 1; ++y)
			{
				if (x == 0 && y == 0) continue;
				if (Bk.X + x < 0 || Bk.X + x > 7 || Bk.Y + y < 0 || Bk.Y + y > 7) continue;
				int i = encode(pii(Bk.X + x, Bk.Y + y));
				if (!now.occu(i))
				{
					pack tg(now);
					tg.bk = i;
					tg.hand ^= 1;
					if (tg.valid())
					{
						nowhere = false;
						if (dfs(tg.encode()) == 0)
						{
							now.debug(); printf("RES 0\n");
							return status[st] = 0;
						}
					}
				}
			}
		if (nowhere) // stalemate?
		{
			if (now.bCheckmate())
			{
				now.debug(); printf("RES 0\n");
				return status[st] = 0;
			}
			else
			{
				now.debug(); printf("RES 1\n");
				return status[st] = 1;
			}
		}
		else
		{
			now.debug(); printf("RES 0\n");
			return status[st] = 0;
		}
	}
}

int main ()
{
	pack init;
	init.wk = readPl(), init.ws1 = readPl(), init.ws2 = readPl();
	init.bk = readPl();
	char str[10]; scanf("%s", str);
	if (strcmp(str, "white") == 0) init.hand = 0;
	else init.hand = 1;
	memset(status, -1, sizeof status);
	if (dfs(init.encode())) printf("white wins\n");
	else printf("draw");
	return 0;
}
