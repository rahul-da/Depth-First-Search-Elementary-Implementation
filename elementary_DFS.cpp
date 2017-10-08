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

const ll mod = 1e9+7;
vi v[100001];
int dp[100001];

using namespace std;

void dfs(int node , int parent)
{
    int x,mx=0,mn=1000000,size=0,tempsize,i;

    if(dp[node]!=-1)return;

    int locvec[100001];

    for(int u: v[node])
    {
        if(u==parent)continue;
        dfs(u,node);
        locvec[size]=dp[u];
        size++;
    }

    if(size==0){dp[node]=0;return;}

    sort( locvec , locvec + size );
    tempsize = size;

    fo(i,size)
    {
        locvec[i] += tempsize;
        tempsize--;
    }

    dp[node] = *std::max_element ( locvec , locvec + size );
}

int main()
{
    ll n,q,i,j,k,x,root;
    cin>>n;

    for(i=1;i<=n;i++)
    {
        dp[i]=-1;

        cin>>x;

        while(x!=0)
        {
            v[i].pb(x);
            v[x].pb(i);
            cin>>x;
        }
    }

    cin>>root;

    dfs(root , 0);

    cout<<dp[root];
}  

