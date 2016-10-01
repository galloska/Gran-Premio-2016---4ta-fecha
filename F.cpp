#include <bits/stdc++.h>
#define endl '\n'
#define pii pair<int,int>
#define psi pair<int,pii>

using namespace std;

const int inf = 1e8;
const int MAXN = 301;

int r;
int n,m;
string mat[MAXN];
int M[MAXN][MAXN];
int vis[MAXN][MAXN];
int dist[MAXN][MAXN];
vector<pii> node[MAXN];
int mov[5] = {0, 0, 1, -1};
int mov2[5] = {1, -1, 0, 0};

void bfs(int x,int y){
	queue<pii> q;
	q.push(pii(x, y));
	vis[x][y] = 0;
	
	while(!q.empty()){
		x = q.front().first;
		y = q.front().second;
		q.pop();
		node[r].push_back( pii( x, y ) );
		
		for(int i=0;i<4;i++){
			int a = x + mov[i];
			int b = y + mov2[i];
			if(a>=0 && a<n && b>=0 && b<m && vis[x][y] + 1 < vis[a][b] && mat[a][b]=='X'){
				vis[a][b] = vis[x][y] + 1;
				q.push(pii( a, b ));
			}
		}
	}
}

vector<int> bfs2(int u){
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			dist[i][j] = inf;
		
	queue<pii> q;
	for(int i=0;i<node[u].size();i++){
		int x = node[u][i].first;
		int y = node[u][i].second;
		dist[x][y] = 0;
		q.push( pii(x, y) );
	}
	
	while(!q.empty()){
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		
		for(int i=0;i<4;i++){
			int a = x + mov[i];
			int b = y + mov2[i];
			if(a>=0 && a<n && b>=0 && b<m && dist[x][y] + 1 < dist[a][b]){
				dist[a][b] = dist[x][y] + 1;
				q.push(pii( a, b ));
			}
		}
	}
	
	vector<int> res;
	for(int i=0;i<r;i++){
		int mini = inf;
		for(int j=0;j<node[i].size();j++)
			mini = min( mini , dist[ node[i][j].first ][ node[i][j].second ] );
		res.push_back(mini - 1);
	}
	
	return res;
}

struct UnionFind {
    int nconjuntos;
    vector<int> padre;
    vector<int> tamano;

    UnionFind(int n) : nconjuntos(n),
        padre(n), tamano(n, 1) {
        for(int i = 0; i < n; ++i)
            padre[i] = i;
    }

    int Encontrar(int u) {
        if (padre[u] == u) return u;
        return padre[u] = Encontrar(padre[u]);
    }

    void Unir(int u, int v) {
        int Ru = Encontrar(u);
        int Rv = Encontrar(v);
        if (Ru == Rv) return;
        -- nconjuntos, padre[Ru] = Rv;
        tamano[Rv] += tamano[Ru];
    }

    bool MismoConjunto(int u, int v) {
        return Encontrar(u) == Encontrar(v);
    }

    int TamanoConjunto(int u) {
        return tamano[Encontrar(u)];
    }
};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin>>t;
	
	while(t--){
		cin>>n>>m;
		
		for(int i=0;i<n;i++)
			cin>>mat[i];
		
		for(int i=0;i<MAXN;i++)
			node[i].clear();
		
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				vis[i][j] = inf;
		
		r = 0;
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				if(vis[i][j] == inf && mat[i][j]=='X'){
					bfs(i, j);
					r++;
				}
			
		vector<psi> aristas;
		for(int i=0;i<r;i++){
			vector<int> num = bfs2(i);
			for(int j=i+1;j<r;j++)
				aristas.push_back( psi( num[j] , pii(i, j) ) );
		}
		sort(aristas.begin(), aristas.end());
		
		UnionFind graph(r);
		
		int r = 0;
		for(int i=0;i<aristas.size();i++){
			int p = aristas[i].first;
			int u = aristas[i].second.first;
			int v = aristas[i].second.second;
			
			if(!graph.MismoConjunto(u, v)){
				graph.Unir( u , v );
				r += p;
			}
		}
		
		cout<<r<<endl;
	}
	return 0;
}