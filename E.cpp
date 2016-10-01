#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int

using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	lli n;
	while(cin>>n && n){
		int cont = 0;
		for(lli i=1;i*i*i<=n;i++)
			if(n%(i*i*i)==0)
				cont++;
		cout<<cont<<endl;
	}
	return 0;
}