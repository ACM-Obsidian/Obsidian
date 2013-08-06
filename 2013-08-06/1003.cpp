#include <cstdio>
#include <cstring>
#include <set>
#define maxn 100001
#define inf 1e9
typedef std::multiset<int> SET;
struct deal{
    int min;
};
deal operator +(deal x,deal y){
    deal z;
    z.min=x.min;if(y.min<x.min)z.min=y.min;
    return z;
}
struct SEGT{
    struct tree{
        deal x;int l,r;
    }*t;
    void build(int l,int r,int p){
        t[p].l=l,t[p].r=r;
        if(l<r){
            int mid=l+r>>1;
            build(l,mid,p*2),build(mid+1,r,p*2+1);
        }
    }
    SEGT(int l,int r){
        t=new tree[4*(r-l+1)];
        build(l,r,1);
    }
    void up(int p){
        t[p].x=t[p*2].x+t[p*2+1].x;
    }
    void update(int k,deal x){
        int p=1;
        for(;t[p].l<t[p].r;)
            if(k-t[p].l<=t[p].r-k)p=p*2;else p=p*2+1;
        t[p].x=x;
        for(;p>>=1;)up(p);
    }
    deal query(int l,int r,int p){
        if(t[p].l==l&&t[p].r==r)return t[p].x;
        else if(r-t[p].l<=t[p].r-r)return query(l,r,p*2);
        else if(l-t[p].l>t[p].r-l)return query(l,r,p*2+1);
        else{
            int mid=t[p].l+t[p].r>>1;
            return query(l,mid,p*2)+query(mid+1,r,p*2+1);
        }
    }
    deal query(int l,int r){return query(l,r,1);}
}*segt[maxn],*segt2[maxn];
SET set[maxn],set2[maxn];
std::set<int> black[maxn],white[maxn];
struct node{
    int n;
    node *next;
}*g[maxn];
void addedge(int x,int y){
    node *i=new node;i->n=y;i->next=g[x],g[x]=i;
    i=new node;i->n=x;i->next=g[y];g[y]=i;
}
int u[maxn],p[maxn][18],s[maxn],num[maxn],loc[maxn],size[maxn],color[maxn],weight[maxn],val[maxn],val2[maxn],n,m;
void dfs1(int n){
    u[n]=1;s[n]=1;
    for(node *i=g[n];i!=NULL;i=i->next)
        if(!u[i->n]){
            p[i->n][0]=n;
            for(int j=1;p[i->n][j-1];j++)p[i->n][j]=p[p[i->n][j-1]][j-1];
            dfs1(i->n);
            s[n]+=s[i->n];
        }
    u[n]=0;
}
void dfs2(int n){
    u[n]=1;deal x;
    if(s[n]>1){
        int max=0,maxi;
        for(node *i=g[n];i!=NULL;i=i->next)
            if(!u[i->n]&&s[i->n]>max)max=s[i->n],maxi=i->n;
        num[maxi]=num[n],loc[maxi]=loc[n]+1;
        dfs2(maxi);
        for(node *i=g[n];i!=NULL;i=i->next)
            if(!u[i->n]&&i->n!=maxi){
                num[i->n]=m++,loc[i->n]=1,dfs2(i->n);
                int bln=black[num[i->n]].size()?*black[num[i->n]].begin():size[num[i->n]]+1;
                val[i->n]=(bln>1?segt[num[i->n]]->query(1,bln-1).min:inf);
                set[n].insert(val[i->n]);
                int wtn=white[num[i->n]].size()?*white[num[i->n]].begin():size[num[i->n]]+1;
                val2[i->n]=(wtn>1?segt2[num[i->n]]->query(1,wtn-1).min:inf);
                set2[n].insert(val2[i->n]);
            }
    }else segt[num[n]]=new SEGT(1,loc[n]),segt2[num[n]]=new SEGT(1,loc[n]),size[num[n]]=loc[n];
    if(!color[n])black[num[n]].insert(loc[n]),set2[n].insert(weight[n]);
    else set[n].insert(weight[n]),white[num[n]].insert(loc[n]);
    x.min=set[n].size()?*set[n].begin():inf;
    segt[num[n]]->update(loc[n],x);
    x.min=set2[n].size()?*set2[n].begin():inf;
    segt2[num[n]]->update(loc[n],x);
    u[n]=0;
}
int parent(int x,int d){
    for(int j=0;d;d>>=1,j++)if(d&1)x=p[x][j];
    return x;
}
void update(int k){
    for(int f,f1;;k=f){
        f1=parent(k,loc[k]-1),f=p[f1][0];
        int u,flag=0;
        deal x;
        x.min=(set[k].size()?*set[k].begin():inf);
        segt[num[k]]->update(loc[k],x);
        int bln=black[num[k]].size()?*black[num[k]].begin():size[num[k]]+1;
        u=(bln>1?segt[num[k]]->query(1,bln-1).min:inf);
        if(val[f1]!=u&&f)set[f].erase(set[f].lower_bound(val[f1])),set[f].insert(val[f1]=u),flag=1;
        x.min=(set2[k].size()?*set2[k].begin():inf);
        segt2[num[k]]->update(loc[k],x);
        int wtn=white[num[k]].size()?*white[num[k]].begin():size[num[k]]+1;
        u=(wtn>1?segt2[num[k]]->query(1,wtn-1).min:inf);
        if(val2[f1]!=u&&f)set2[f].erase(set2[f].lower_bound(val2[f1])),set2[f].insert(val2[f1]=u),flag=1;
        if(!flag)break;
    }
}
void update1(int k){
    if(!color[k])black[num[k]].erase(loc[k]),white[num[k]].insert(loc[k]),set[k].insert(weight[k]),set2[k].erase(set2[k].lower_bound(weight[k]));
    else black[num[k]].insert(loc[k]),white[num[k]].erase(loc[k]),set[k].erase(set[k].lower_bound(weight[k])),set2[k].insert(weight[k]);
    color[k]=!color[k];
    update(k);
}
void update2(int k,int w){
    if(color[k])set[k].erase(set[k].lower_bound(weight[k])),set[k].insert(w);
    else set2[k].erase(set2[k].lower_bound(weight[k])),set2[k].insert(w);
    weight[k]=w;
    update(k);
}
int query(int k){
    int ans=inf,c=color[k];
    for(;k;k=parent(k,loc[k])){
        if(color[k]!=c)break;
        if(c){
            std::set<int>::iterator it=black[num[k]].lower_bound(loc[k]);
            int bln2=(it==black[num[k]].end()?size[num[k]]+1:*it);
            int bln1=(it==black[num[k]].begin()?0:*--it);
            int t=segt[num[k]]->query(bln1+1,bln2-1).min;
            if(t<ans)ans=t;
            if(bln1>0)break;
        }else{
            std::set<int>::iterator it=white[num[k]].lower_bound(loc[k]);
            int wtn2=(it==white[num[k]].end()?size[num[k]]+1:*it);
            int wtn1=(it==white[num[k]].begin()?0:*--it);
            int t=segt2[num[k]]->query(wtn1+1,wtn2-1).min;
            if(t<ans)ans=t;
            if(wtn1>0)break;
        }
    }
    return ans;
}
void solve(){
    for(int i=1,x,y;i<n;i++)scanf("%d%d",&x,&y),addedge(x,y);
    for(int i=1;i<=n;i++)scanf("%d",&color[i]);
    for(int i=1;i<=n;i++)scanf("%d",&weight[i]),weight[i]=-weight[i];
    memset(p,0,sizeof p);
    for(int i=0;i<=n;i++)set[i].clear(),set2[i].clear(),white[i].clear(),black[i].clear();
    dfs1(1);
    m=1;loc[1]=1;dfs2(1);
    int q;for(scanf("%d",&q);q--;){
        int k,v,w;
        scanf("%d%d",&k,&v);
        if(k==0)printf("%d\n",-query(v));
        else if(k==1)update1(v);
        else scanf("%d",&w),update2(v,-w);
    }
    for(int i=1;i<=n;g[i++]=NULL)
        for(node *j=g[i],*k;j!=NULL;k=j->next,delete j,j=k);
}
int main(){
    for(;scanf("%d",&n)!=EOF;solve());
    return 0;
}
