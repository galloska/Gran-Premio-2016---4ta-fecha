#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

const int MAXN = 2001;

int A[MAXN];
int num[MAXN];

int NoSwap(int n,int i,int can){	
	int j = n;
	int cont = 0, next = 1;
	
	while(j){
		if(j==1){
			if(num[i]!=next) return -1;
			i = (i + 1) % n;
			next++;
			j--;
			can = 1;
			continue;
		}
		
		if(num[i]==next){
			next++;
			i = (i + 1) % n;
			j--;
			can = 1;
			continue;
		}
		
		if(can){
			cont+=2;
			swap( num[i] , num[(i+1)%n] );
			can = 0;
		}
		else can = 1;
			
		if(num[i]!=next) return -1;
		
		next++;
		i = (i + 1) % n;
		j--;
	}
	
	return cont;
}

int Solve(int n){
	int i = 0;
	while(num[i]!=1) i++;
	
	int a = NoSwap(n, i, 1);
	if(a!=-1) return a;
	
	for(int j=0;j<n;j++)
		num[j] = A[j];
	
	swap( num[i] , num[(i-1+n)%n] );
	a = NoSwap(n, (i-1+n)%n, 0);
	if(a!=-1) return a + 2;
	
	for(int j=0;j<n;j++)
		num[j] = A[j];
	
	swap( num[i] , num[(i+1)%n] );
	return NoSwap(n, (i+1)%n, 0) + 2;	
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t,n;
	cin>>t;
	
	while(t--){
		cin>>n;
		
		for(int i=0;i<n;i++)
			cin>>num[i];

		for(int i=0;i<n;i++)
			A[i] = num[i];
		
		cout<<Solve(n)<<endl;
	}
	return 0;
}