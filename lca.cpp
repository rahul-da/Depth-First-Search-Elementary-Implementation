#include <bits/stdc++.h>
using namespace std;
#define gc getchar_unlocked
#define fo(i,n) for(i=0;i<n;i++)
#define Fo(i,k,n) for(i=k;i<n;i++)
#define ll long long
#define pii pair < int , int >
#define vi vector < int >
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define clr(x) memset(x, 0, sizeof(x))
#define init(x, a) memset(x, a, sizeof(x))
#define vll vector < long long int >
#define sll set < long long int >
#define fastIO ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;
const ll mod = 1e9+7;
ll ancestor[100001][21],n,height[100001];
vector < ll > graph[100001];
void dfs(ll node,ll parent)
{
	if(parent>0)
	{
		ancestor[node][0] = parent;
		height[node] = height[parent] + 1;
	}
	for(ll x:graph[node])
	{
		if(x==parent)continue;
		dfs(x,node);
	}
}
void build_ancestor()
{
	ll i,j,k;
	for(i=1;i<21;i++)
	{
		Fo(j,1,n+1)
		{
			if(ancestor[j][i-1]!=-1)
				ancestor[j][i] = ancestor[ancestor[j][i-1]][i-1];
		}
	}
}
ll lca(ll u,ll v)
{
	if(height[u]<height[v])swap(u,v);
	ll temp = 20;
	while(temp>=0 and height[u]>height[v])
	{
		if(ancestor[u][temp]!=-1 and 
			height[ancestor[u][temp]]>=height[v])
		{
			u = ancestor[u][temp];
		}
		temp--;
	}
	if(u==v)return(u);
	temp = 20;
	while(temp>=0)
	{
		if(ancestor[u][temp]!=-1 and 
			ancestor[u][temp]!=ancestor[v][temp])
		{
			u = ancestor[u][temp];
			v = ancestor[v][temp];
		}
		temp--;
	}
	u = ancestor[u][0];
	v = ancestor[v][0];
	return(u);
}
ll fun(ll u,ll v,ll w)
{
	if(u==w or v==w)return(0);
	if(lca(u,w)==w and lca(v,w)!=w)return(0);
	if(lca(u,w)!=w and lca(v,w)==w)return(0);
	ll t,n,i,j,p,q,r,s,d1,d2,d3,ans=0;
	if(height[u]>height[v])swap(u,v);
	p = lca(u,v);
	q = lca(u,w);
	r = lca(v,w);
	if(p==u)
	{
		if(r==v)return(height[w]-height[v]);
		if(height[r]>height[u])return(height[w]-height[r]);
		return(height[u]+height[w]-2*height[q]);
	}
	if(q==u){return(height[w]-height[u]);}
	if(r==v){return(height[w]-height[v]);}
	if(height[q]>height[p])
		return(height[q]+height[w]-2*height[lca(q,w)]);
	if(height[r]>height[p])
		return(height[r]+height[w]-2*height[lca(r,w)]);
	return(height[p]+height[w]-2*height[lca(p,w)]);
	return(ans);
}
int main()
{
	fastIO;
	ll q,i,j,k,l;
	cin>>n>>q;
	fo(i,100001)fo(j,21)ancestor[i][j]=-1;
	fo(i,n-1)
	{
		cin>>j;
		graph[i+2].pb(j);
		graph[j].pb(i+2);
	}
	height[1] = 1;
	dfs(1,0);
	build_ancestor();
	while(q--)
	{
		cin>>i>>j>>k;
		ll ans = 0;
		ans = max(ans,fun(i,j,k));
		ans = max(ans,fun(i,k,j));
		ans = max(ans,fun(k,i,j));
		ans = max(ans,fun(j,i,k));
		ans = max(ans,fun(j,k,i));
		ans = max(ans,fun(k,j,i));
		cout<<ans+1<<endl;
	}
}