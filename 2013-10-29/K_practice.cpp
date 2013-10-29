#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
char s[256], **ans;
int maxw, maxh, maxpw, maxph, w, h;
void dfs(int l, int r, int p2w, int pw, int p2h, int ph) {
	for (; s[l] == ' '; l++);
	for (; s[r] == ' '; r--);
	if (s[l] == '[') {
		l++, r--;
		for (; s[l] == ' '; l++);
		for (; s[r] == ' '; r--);
	}
	for (; !(pw%2)&&p2w; pw/=2, p2w--);
	for (; !(ph%2)&&p2h; ph/=2, p2h--);
	maxpw = 1LL*maxpw*pw/std::__gcd(maxpw,pw);
	maxph = 1LL*maxph*ph/std::__gcd(maxph,ph);
	if (s[l] >= '0' && s[l] <= '9') {
		int w = (r-l+4)*pw;
		for (int i = 0; i < p2w; i++) w = (w+1)/2;
		int h = 2*ph;
		for (int i = 0; i < p2h; i++) h = (h+1)/2;
		if (w > maxw) maxw = w;
		if (h > maxh) maxh = h;
	} else {
		std::vector<int> loc;
		int num = 0, fl = -1;
		char sp;
		for (int i = l; i <= r; i++)
			if (s[i] == '(') num++;
			else if (s[i] == '[' && num == 1) fl = loc.size(), num++;
			else if (s[i] == '[') num++;
			else if (s[i] == ')' || s[i] == ']') num--;
			else if (num == 1 && (s[i] == '.' || s[i] == ':')) sp = s[i], loc.push_back(i);
		if (sp == '.') {
			int pwt = pw;
			if (fl == -1) pwt *= loc.size()+1;
			else pwt *= loc.size()+2;
			for (int i = 0; i <= loc.size(); i++) {
				int lt, rt;
				if (i == 0) lt = l+1; else lt = loc[i-1]+1;
				if (i == loc.size()) rt = r-1; else rt = loc[i]-1;
				dfs(lt, rt, p2w + (i == fl), pwt, p2h, ph);
			}
		} else {
			int pht = ph;
			if (fl == -1) pht *= loc.size()+1;
			else pht *= loc.size()+2;
			for (int i = 0; i <= loc.size(); i++) {
				int lt, rt;
				if (i == 0) lt = l+1; else lt = loc[i-1]+1;
				if (i == loc.size()) rt = r-1; else rt = loc[i]-1;
				dfs(lt, rt, p2w, pw, p2h + (i == fl), pht);
			}
		}
	}
}
void dfs2(int x, int y, int h, int w, int l, int r) {
	for (int i = y+1; i < y+w; i++) {
		if (ans[x][i] != '+') ans[x][i] = '-';
		if (ans[x+h][i] != '+') ans[x+h][i] = '-';
	}
	for (int i = x+1; i < x+h; i++) {
		if (ans[i][y] != '+') ans[i][y] = '|';
		if (ans[i][y+w] != '+') ans[i][y+w] = '|';
	}
	ans[x][y] = ans[x+h][y] = ans[x][y+w] = ans[x+h][y+w] = '+';
	for (; s[l] == ' '; l++);
	for (; s[r] == ' '; r--);
	if (s[l] == '[') {
		l++, r--;
		for (; s[l] == ' '; l++);
		for (; s[r] == ' '; r--);
	}
	if (s[l] >= '0' && s[l] <= '9') {
		int t = l;
		for (; s[t] >= '0' && s[t] <= '9'; t++)
			ans[x+1][y+2+t-l] = s[t];
	} else {
		std::vector<int> loc;
		int num = 0, fl = -1;
		char sp;
		for (int i = l; i <= r; i++)
			if (s[i] == '(') num++;
			else if (s[i] == '[' && num == 1) fl = loc.size(), num++;
			else if (s[i] == '[') num++;
			else if (s[i] == ')' || s[i] == ']') num--;
			else if (num == 1 && (s[i] == '.' || s[i] == ':')) sp = s[i], loc.push_back(i);
		if (sp == '.') {
			int wt = w, cury = y;
			if (fl == -1) wt /= loc.size()+1;
			else wt /= loc.size()+2;
			for (int i = 0; i <= loc.size(); i++) {
				int lt, rt;
				if (i == 0) lt = l+1; else lt = loc[i-1]+1;
				if (i == loc.size()) rt = r-1; else rt = loc[i]-1;
				dfs2(x, cury, h, wt*(1+(i==fl)), lt, rt);
				cury += wt*(1+(i==fl));
			}
		} else {
			int ht = h, curx = x;
			if (fl == -1) ht /= loc.size()+1;
			else ht /= loc.size()+2;
			for (int i = 0; i <= loc.size(); i++) {
				int lt, rt;
				if (i == 0) lt = l+1; else lt = loc[i-1]+1;
				if (i == loc.size()) rt = r-1; else rt = loc[i]-1;
				dfs2(curx, y, ht*(1+(i==fl)), w, lt, rt);
				curx += ht*(1+(i==fl));
			}
		}
	}
}
int main() {
	freopen("kak-u-pakal.in","r",stdin);
	freopen("kak-u-pakal.out","w",stdout);
	gets(s);
	maxpw = maxph = 1;
	dfs(0, strlen(s)-1, 0, 1, 0, 1);
	w = maxw;
	if (w % maxpw) w = w/maxpw*maxpw+maxpw;
	h = maxh;
	if (h % maxph) h = h/maxph*maxph+maxph;
	ans = new char*[h+1];
	for (int i = 0; i <= h; i++) {
		ans[i] = new char[w+1];
		memset(ans[i], 32, w+1);
	}
	dfs2(0, 0, h, w, 0, strlen(s)-1);
	for (int i = 0; i <= h; i++) {
		for (int j = 0; j <= w; j++)
			putchar(ans[i][j]);
		puts("");
	}
	return 0;
}
