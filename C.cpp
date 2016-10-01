#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

const int MAXN = 1000001;
const int LOGMAXN = 20;

int aux[MAXN];
int logTable[MAXN];
int M[MAXN][LOGMAXN];

void process(int n){
	int i, j;

	for (i = 0; i < n; i++)
		M[i][0] = i;

	for (j = 1; 1 << j <= n; j++)
		for (i = 0; i + (1 << j) - 1 < n; i++)
			if (aux[M[i][j - 1]] >= aux[M[i + (1 << (j - 1))][j - 1]])
				M[i][j] = M[i][j - 1];
			else
				M[i][j] = M[i + (1 << (j - 1))][j - 1];
}

int query(int i,int j){
	if(i>j) return 0;
	int k = logTable[j-i+1];
	if(aux[ M[i][k] ]>=aux[ M[j-(1<<k)+1][k] ])
		return aux[ M[i][k] ];
	return aux[ M[j-(1<<k)+1][k] ];
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	for(int i=2;i<MAXN;i++)
		logTable[i]=logTable[i >> 1]+1;
	
	int t;
	cin>>t;
	
	while(t--){
		int n,k;
		cin>>n>>k;
		
		for(int i=0;i<n;i++)
			cin>>aux[i];
		
		process(n);
		
		for(int i=0;i+k-1<n;i++){
			if(i) cout<<" ";
			cout<<query(i, i + k - 1);
		}
		cout<<endl;
	}
	return 0;
}