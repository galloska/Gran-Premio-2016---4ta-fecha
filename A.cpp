#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

const int MAXN = 100001;

int cant[MAXN][10];

struct Segment{
	int val;
	int l,r;
	int lazy;
	Segment *left, *right;
	
	Segment(int a, int b): l(a), r(b), lazy(-1), left('\0'), right('\0') {}
	
	~Segment(){
		delete left;
		delete right;
	}
	
	void build(int id){
		if(l==r){
			val = cant[l][id];
			return;
		}
		int med = (l + r)>>1;
		left = new Segment(l, med);
		right = new Segment(med + 1, r);
		
		left->build(id);
		right->build(id);
		
		val = left->val + right->val;
	}
	
	void propagate(){
		if(lazy!=-1){
			if(lazy){
				left->val = (left->r - left->l + 1) * lazy;
				right->val = (right->r - right->l + 1) * lazy;
				
			}
			else{
				left->val = 0;				
				right->val = 0;
			}
			
			left->lazy = lazy;
			right->lazy = lazy;
			
			lazy = -1;
		}
	}
	
	void update(int a,int b,int v){
		if(b<l || a>r) return;
		if(a<=l && r<=b){
			if(v) val = (r - l + 1) * v;
			else val = 0;
			
			lazy = v;
			return;
		}
		propagate();
		
		left->update(a, b, v);
		right->update(a, b, v);
		
		val = left->val + right->val;
	}
	
	int query(int a,int b){
		if(b<l || a>r) return 0;
		if(a<=l && r<=b){
			return val;
		}
		propagate();
		
		int uno = left->query(a, b);
		int dos = right->query(a, b);
		
		return uno + dos;
	}
};

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,q,op,a,b;
	string cad;
	
	cin>>n>>q;
	
	Segment *tree[10];
	
	for(int i=0;i<n;i++){
		cin>>cad;
		for(int j=0;j<cad.size();j++)
			cant[i][cad[j] - 48]++;
	}
	
	for(int i=0;i<10;i++){
		tree[i] = new Segment(0, n - 1);
		tree[i]->build(i);
	}
	
	while(q--){
		cin>>op>>a>>b;
		a--,b--;
		
		if(op==0){
			int maxi = 0;
			int id = 0;
			
			for(int i=0;i<10;i++){
				int r = tree[i]->query(a, b);
				if(r>maxi){
					maxi = r;
					id = i;
				}
			}
			
			cout<<id<<endl;
		}
		else{
			for(int i=0;i<10;i++)
				tree[i]->update(a, b, 0);
			
			cin>>cad;
			
			vector<int> num(10, 0);
			
			for(int i=0;i<cad.size();i++)
				num[cad[i] - 48]++;
			
			for(int i=0;i<10;i++)
				tree[i]->update(a, b, num[i]);
		}
	}
	return 0;
}