#include <cstdio>
#include <vector>
std::vector<int> id[100], des[100];
int x[10000], y[10000], pos[10000], ind[10000], u[10000];
std::vector<int> cnt[10000];
std::vector<std::vector<int> > T;
int main() {
	int n, m = 0; scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int k; scanf("%d", &k);
		while (k--) {
			int x; scanf("%d", &x), x--;
			id[i].push_back(m), des[i].push_back(x);
			pos[m++] = i;
		}
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < id[i].size(); j++) {
			int k = 0;
			while (k < id[des[i][j]].size() && des[des[i][j]][k] != i) k++;
			x[id[i][j]] = id[des[i][j]][k];
			y[id[i][j]] = id[i][(j+1)%id[i].size()];
		}
	for (int i = 0; i < n; i++) {
		std::vector<int> tmp;
		for (int j = 0; j < n; j++)
			if (id[j].size() == i)
				for (int k = 0; k < id[j].size(); k++) tmp.push_back(id[j][k]), ind[id[j][k]] = T.size();
		if (!tmp.empty()) T.push_back(tmp);
	}
	while (1) {
		int changed = 0;
		for (int i = 0; i < T.size(); i++) {
			for (int j = 0; j < T.size(); j++) cnt[j].clear();
			int num = 0;
			for (int j = 0; j < T[i].size(); j++) {
				if (cnt[ind[x[T[i][j]]]].empty()) num++;
				cnt[ind[x[T[i][j]]]].push_back(T[i][j]);
			}
			if (num != 1) {
				int tmp = T.size(), x = 0;
				for (int j = 0; j < tmp; j++)
					if (!cnt[j].empty()) {
						if (x == 0) T[i] = cnt[j];
						else {
							for (int k = 0; k < cnt[j].size(); k++) ind[cnt[j][k]] = T.size();
							T.push_back(std::vector<int>(cnt[j]));
						}
						x++;
					}
				changed = 1;
				break;
			}
			for (int j = 0; j < T.size(); j++) cnt[j].clear();
			num = 0;
			for (int j = 0; j < T[i].size(); j++) {
				if (cnt[ind[y[T[i][j]]]].empty()) num++;
				cnt[ind[y[T[i][j]]]].push_back(T[i][j]);
			}
			if (num != 1) {
				int tmp = T.size(), x = 0;
				for (int j = 0; j < tmp; j++)
					if (!cnt[j].empty()) {
						if (x == 0) T[i] = cnt[j];
						else {
							for (int k = 0; k < cnt[j].size(); k++) ind[cnt[j][k]] = T.size();
							T.push_back(std::vector<int>(cnt[j]));
						}
						x++;
					}
				changed = 1;
				break;
			}
		}
		if (!changed) break;
	}
	int output = 0;
	for (int i = 0; i < n; i++)
		if (!u[i]) {
			u[i] = 1;
			std::vector<int> tmp;
			tmp.push_back(i);
			if (id[i].size() == 0) {
				for (int j = i+1; j < n; j++)
					if (id[j].size() == 0) tmp.push_back(j), u[j] = 1;
			} else {
				for (int j = i+1; j < n; j++)
					if (!u[j] && id[i].size() == id[j].size()) {
						int flag = 0;
						for (int k = 0; k < id[i].size(); k++) {
							int flag2 = 1;
							for (int l = 0; l < id[j].size(); l++)
								if (ind[id[i][l]] != ind[id[j][(k+l)%id[i].size()]]) {
									flag2 = 0;
									break;
								}
							if (flag2) {
								flag = 1;
								break;
							}
						}
						if (flag) {
							u[j] = 1;
							tmp.push_back(j);
						}
					}
			}
			if (tmp.size() > 1) {
				for (int j = 0; j < tmp.size(); j++)
					printf("%d ", tmp[j]+1);
				puts("");
				output = 1;
			}
		}
	if (!output) puts("none");
	return 0;
}
