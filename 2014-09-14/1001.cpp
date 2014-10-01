#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 10010;
char str[N];

bool mai (int i) {
    if (strncmp(str + i, "Apple", 5) == 0 ||
    strncmp(str + i, "iPhone", 6) == 0 ||
    strncmp(str + i, "iPod", 4) == 0 ||
    strncmp(str + i, "iPad", 4) == 0)
        return true;
    else return false;
}

bool dafa (int i) {
    if (strncmp(str + i, "Sony", 4) == 0)
        return true;
    else return false;
}

int main () {
    while (gets(str) != NULL) {
        int l = strlen(str);
        for (int i = 0; i < l; i++) {
            if (mai(i)) printf("MAI MAI MAI!\n");
            else if (dafa(i)) printf("SONY DAFA IS GOOD!\n");
        }
    }
    return 0;
}
