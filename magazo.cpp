#include <bits/stdc++.h>
#define pii pair<int,int>
#define MAXV 20001
#define LOGV 20
#define endl '\n'

using namespace std;

int loga[MAXV];
int level[MAXV]; // Level of vertex u from root.
vector<int> dist;
int parent[MAXV]; // Direct parent of vertex u.
int P[MAXV][LOGV];
vector<int> lista[MAXV];

int aux;
int ini[MAXV];
int fin[MAXV];

pii maxi(pii a,pii b){
	if(a.first>b.first) return a;
	return b;
}

struct Segment{
	pii nodo;
	int l,r;
	Segment *left, *right;
	
	Segment(int a,int b) : left('\0') , right('\0'), l(a) , r(b) {}
	
	void build(){
		if(l==r)
			nodo = pii( dist[ ini[l] ] , l );
		else{
			int mid = ( l + r ) / 2;
			left = new Segment( l , mid );
			right = new Segment( mid + 1 , r );
			
			left->build();
			right->build();
			
			nodo = maxi( left->nodo , right->nodo );
		}
	}
	
	pii query(int a,int b){
		if(b<l || a>r) return pii( -1 , -1 );
		if(l==r) return nodo;
		
		return maxi( left->query(a , b) , right->query(a , b) );
	}
};

void dfs(int u,int p){
	ini[u] = aux++;
	
	for(int i=0;i<lista[u].size();i++){
		int v = lista[u][i];
		
		if(p!=v) dfs( v , u );
	}
	
	fin[u] = aux;
}

int logarithm(int v){ // O(log v)		
	return loga[v];
}

void PreprocessDP(int v){ // O(v log v)
	int log = logarithm(v);
	for(int i = 0; i < v; i++)
		P[i][0] = parent[i];

	for(int j = 1; j <= log; j++)
		for(int i = 0; i < v; i++)
			P[i][j] = P[P[i][j - 1]][j - 1];
}

int LCA(int v, int a, int b){ // O(log v)
	int log = logarithm(v);
	if(level[a] < level[b]) swap(a, b);
	for(int i = log; i >= 0; i--)
		if(level[a] - (1 << i) >= level[b])
			a = P[a][i];
	if(a == b) return a;

	for(int i = log; i >= 0; i--)
		if(P[a][i] != P[b][i])
			a = P[a][i], b = P[b][i];
	return P[a][0];
}

int Sube(int v,int a,int d){
	int log = logarithm(v);

	for(int i = log; i >= 0; i--)
		if(d - (1 << i) >= 0){
			a = P[a][i];
			d -= (1<<i);
		}
			
	return a;
}

void bfs(int s,int n){
	dist.assign( n , 1e8 );
	
	queue<int> q;
	q.push(s);
	dist[s] = 0;
	parent[s] = s;
	
	while(!q.empty()){
		int u = q.front();
		q.pop();
		
		for(int i=0;i<lista[u].size();i++){
			int v = lista[u][i];
			
			if(dist[v]>dist[u] + 1){
				dist[v] = dist[u] + 1;
				parent[v] = u;
				q.push( v );
			}
			
		}
		
	}
}

int main(){

	loga[0] = 0;
	for(int i = 1;i<MAXV; i++)
		loga[i] = loga[i>>1] + 1;
		
	int n,q,a,b;
	cin>>n>>q;
	
	for(int i=0;i<n-1;i++){
		cin>>a>>b;
		a--,b--;
		lista[a].push_back(b);
		lista[b].push_back(a);
	}
	
	bfs(0, n);
	PreprocessDP(n);
	
	dfs( 0 , -1 );
	
	Segment *tree = new Segment( 0 , n - 1 );
	tree->build();
	
	while(q--){
		cin>>a>>b;
		a--;
		
		if(dist[a]>=b) cout<<Sube( n , a , b ) + 1<<endl;
		else{
			pii res = maxi( tree->query( 0 , ini[a] - 1 ) , tree->query( fin[a] + 1 , n - 1 ) );
			
			cout<<res.first<<" "<<res.second+1<<endl;
			if(res.first>=b){
				cout<<Sube( n , res.second , b )+1<<endl;
				continue;
			}
			
			res = tree->query( ini[a] , fin[a] );
			res.first = res.first - dist[a];
			
			if(res.first>=b){
				cout<<Sube( n , res.second , b )+1<<endl;
				continue;
			}
			
			cout<<0<<endl;
			
		}
	}
	return 0;
}















