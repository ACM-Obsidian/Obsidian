#include <cstdio>
#include <vector>
#define P 1000000007
int m, le[100000], pow[100001], u[100000], q[100000], minlev;
char s[100001], sym[100000];
std::vector<int> g[100000];
void connect(const std::vector<std::pair<int, int> > &l, const std::vector<std::pair<int, int> > &r) {
	int i = 0, j = 0;
	while (i < l.size() && j < r.size()) {
		if (sym[l[i].first] == sym[r[j].first])
			g[l[i].first].push_back(r[j].first), g[r[j].first].push_back(l[i].first);
		if (i+1 == l.size()) j++;
		else if (j+1 == l.size()) i++;
		else if (l[i+1].second == r[j+1].second) i++, j++;
		else if (le[l[i].first] > le[r[j].first]) j++;
		else i++;
	}
}
void concat(int lev, const std::vector<std::pair<int, int> > &l, const std::vector<std::pair<int, int> > &r, std::vector<std::pair<int, int> > &res) {
	res = l;
	for (int i = 0; i < r.size(); i++)
		res.push_back(std::make_pair(r[i].first, (r[i].second+pow[lev])%P));
}
int process(int k, int lev, std::vector<std::pair<int, int> > &u, std::vector<std::pair<int, int> > &l, std::vector<std::pair<int, int> > &d, std::vector<std::pair<int, int> > &r) {
	if (s[k] == '+') {
		std::vector<std::pair<int, int> > ulu, ull, uld, ulr, uru, url, urd, urr, dlu, dll, dld, dlr, dru, drl, drd, drr;
		int t = process(process(process(process(k+1, lev-1, ulu, ull, uld, ulr), lev-1, uru, url, urd, urr), lev-1, dlu, dll, dld, dlr), lev-1, dru, drl, drd, drr);
		connect(ulr, url), connect(dlr, drl), connect(uld, dlu), connect(urd, dru);
		concat(lev, ulu, uru, u), concat(lev, ull, dll, l), concat(lev, dld, drd, d), concat(lev, urr, drr, r);
		return t;
	} else {
		sym[m] = s[k], le[m] = lev;
		if (lev < minlev) minlev = lev;
		u.push_back(std::make_pair(m, 0)), l = d = r = u;
		m++;
		return k+1;
	}
}
int main() {
	freopen("quadtree.in", "r", stdin);
	gets(s);
	pow[0] = 1;
	for (int i = 1; i <= 100000; i++) pow[i] = pow[i-1]*2%P;
	std::vector<std::pair<int, int> > U, L, D, R;
	minlev = 100000;
	process(0, 100000, U, L, D, R);
	int max = 0; char maxsym;
	for (int i = 0; i < m; i++)
		if (!u[i]) {
			int l = 0, r = 0, s = 0; q[0] = i, u[i] = 1;
			while (l <= r) {
				int t = q[l]; l++;
				s += 1<<2*(le[t]-minlev);
				for (int j = 0; j < g[t].size(); j++)
					if (!u[g[t][j]]) q[++r] = g[t][j], u[g[t][j]] = 1;
			}
			if (s > max || s == max && sym[i] < maxsym) max = s, maxsym = sym[i];
		}
	printf("%d\n%c\n", max, maxsym);
	return 0;
}
