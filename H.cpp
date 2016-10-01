#include <bits/stdc++.h>
#define endl '\n'
#define lli long long int

using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	int t,n;
	string cad;
	cin>>t;
	
	while(t--){
		cin>>n>>cad;
		vector<int> letter(26, 0);
		
		for(int i=0;i<n;i++)
			letter[cad[i] - 'A']++;
		
		string res = "";
		for(int i=0;i<26;i++)
			while(letter[i]>=2){
				letter[i] -= 2;
				res += char(i + 'A');
			}
			
		cout<<res;
		
		for(int i=0;i<26;i++)
			if(letter[i]){
				cout<<char(i+'A');
				break;
			}
		
		reverse(res.begin(), res.end());
		cout<<res<<endl;
	}
	return 0;
}