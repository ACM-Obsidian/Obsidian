//Orz Sevenkplus
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cctype>
#include<complex>
#include<algorithm>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<bitset>
#define un using namespace
un std;
#define pb push_back
#define pf pop_front

#define mp make_pair

#define c0 first
#define c1 second
#define sqr(x)((x)*(x))
#define clr(x)memset(x,0,sizeof(x))
#define clr1(x)memset(x,-1,sizeof(x))
#define clr80(x)memset(x,0x80,sizeof(x))
#define clr7F(x)memset(x,0x7F,sizeof(x))

#define ll long long
#ifdef __unix__
#define LLD "%lld"
#else
#define LLD "%I64d"
#endif
#define pii pair<int,int>
#define pip pair<int,pii>
#define vi vector<int>
#define vpi vector<pii>
#define pq priority_queue

template<typename T>inline bool chkmin(T&a,T b){return a>b?a=b,1:0;}
template<typename T>inline bool chkmax(T&a,T b){return a<b?a=b,1:0;}
#define modadd(a,b,c)(((a)+(b))%(c))
#define modmul(a,b,c)((int)(((ll)(a)*(b))%(c)))

#define P 1000000007

char str[1000010];
void go(){
	if(str[0]!='M'){
		puts("No");
		return;
	}
	int l=strlen(str),a=l-1;
	if(a==1&&str[1]=='I'){
		puts("Yes");
		return;
	}
	for(int i=1;i<l;i++){
		if(str[i]=='M'){
			puts("No");
			return;
		}if(str[i]=='U')a+=2;
	}
	if(a%6==2||a%6==4){
		puts("Yes");
		return;
	}
	puts("No");
	return;
}
int main(){
	int n;
	scanf("%d",&n);
	while(n--){
		scanf("%s",str);
		go();
	}
	return 0;
}
