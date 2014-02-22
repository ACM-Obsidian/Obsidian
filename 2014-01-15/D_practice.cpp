#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <string>
#include <sstream>
using std::string;
using std::map;
using std::vector;
using std::istringstream;
map<string, int> stopsym, linesym;
vector<int> line[100000], stop[300000], dlines[100001];
int stopd[300000], lined[100000], f[300000], q[300000];
char tmp[1100000], tmp2[100], sname[100], tname[100];
void solve() {
	stopsym.clear();
	linesym.clear();
	gets(tmp);
	gets(tmp);
	istringstream sin(tmp);
	sin >> tmp2;
	int n = 0;
	while (sin >> tmp2) {
		if (tmp2[strlen(tmp2)-1] == ',')
			tmp2[strlen(tmp2)-1] = 0;
		stopsym.insert(std::make_pair(string(tmp2), n++));
	}
	gets(tmp);
	sin.clear();
	sin.str(tmp);
	sin >> tmp2;
	int m = 0;
	while (sin >> tmp2) {
		if (tmp2[strlen(tmp2)-1] == ',')
			tmp2[strlen(tmp2)-1] = 0;
		linesym.insert(std::make_pair(string(tmp2), m++));
	}
	for (int i = 0; i < n; i++) stop[i].clear();
	for (int i = 0; i < m; i++) line[i].clear(), dlines[i].clear();
	for (int i = 0; i < m; i++) {
		gets(tmp);
		sin.clear();
		sin.str(tmp);
		sin >> tmp2;
		int id = linesym.find(string(tmp2))->second;
		sin >> tmp2;
		while (sin >> tmp2) {
			if (tmp2[strlen(tmp2)-1] == ',')
				tmp2[strlen(tmp2)-1] = 0;
			int stid = stopsym.find(string(tmp2))->second;
			line[id].push_back(stid);
			stop[stid].push_back(id);
		}
	}
	gets(tmp);
	sin.clear();
	sin.str(tmp);
	sin >> tmp2 >> tmp2 >> tmp2 >> sname;
	int sid = stopsym.find(string(sname))->second;
	gets(tmp);
	sin.clear();
	sin.str(tmp);
	sin >> tmp2 >> tmp2 >> tmp2 >> tname;
	int tid = stopsym.find(string(tname))->second;

	memset(stopd, -1, sizeof stopd);
	memset(lined, -1, sizeof lined);
	stopd[sid] = 0;
	int l = 0, r = 0; q[0] = sid;
	for (; l <= r; l++)
		for (int i = 0; i < stop[q[l]].size(); i++)
			if (lined[stop[q[l]][i]] == -1) {
				int j = stop[q[l]][i];
				lined[j] = stopd[q[l]];
				dlines[lined[j]].push_back(j);
				for (int k = 0; k < line[j].size(); k++)
					if (stopd[line[j][k]] == -1) {
						stopd[line[j][k]] = stopd[q[l]]+1;
						q[++r] = line[j][k];
					}
			}

	memset(f, 0xC0, sizeof f);
	f[sid] = 0;
	for (int i = 0; dlines[i].size() > 0; i++)
		for (int j = 0; j < dlines[i].size(); j++) {
			int k = dlines[i][j], cur = 0xC0000000;
			for (int l = 0; l < line[k].size(); l++) {
				cur++;
				if (stopd[line[k][l]] == i) {
					if (f[line[k][l]] > cur)
						cur = f[line[k][l]];
				} else {
					if (cur > f[line[k][l]])
						f[line[k][l]] = cur;
				}
			}
			cur = 0xC0000000;
			for (int l = (int)line[k].size()-1; l >= 0; l--) {
				cur++;
				if (stopd[line[k][l]] == i) {
					if (f[line[k][l]] > cur)
						cur = f[line[k][l]];
				} else {
					if (cur > f[line[k][l]])
						f[line[k][l]] = cur;
				}
			}
		}

	printf("optimal travel from %s to %s: %d line%s, %d minute%s\n", sname, tname, stopd[tid], stopd[tid] == 1 ? "" : "s", f[tid], f[tid] == 1 ? "" : "s");
}
int main() {
	int T;
	for (scanf("%d", &T), gets(tmp); T--; solve());
}
