class SegTree{
	int sz;
	vector<int>val;
	vector<int>opt;
	vector<int>cnt;
	int NOP=0;
	int NEU=0;
public:
	SegTree (int n){
		sz=1;
		while(sz<n){
			sz = sz*2;
		}
		val.assign(2*sz,NEU);
		opt.assign(2*sz,0LL);
		cnt.assign(2*sz,0LL);
	}
	void Build(vector<int>&a,int n,int curr,int left,int right){
		if(right-left==1){ 
			if(left<n){
				cnt[curr]=1;
				val[curr]=a[left];
			}
			return;
		}
		int mid=(left+right)/2;
		Build(a,n,2*curr+1,left,mid);
		Build(a,n,2*curr+2,mid,right);
		cnt[curr]=cnt[2*curr+1]+cnt[2*curr+2];
		val[curr]=val[2*curr+1]+val[2*curr+2];
	}
	void Build(vector<int>&a,int n){
		Build(a,n,0,0,sz);
	}
	void Propogate(int curr,int left,int right){
		if((right-left)==1){
			return;
		}
		if(opt[curr]!=NOP){
			opt[2*curr+1]+=opt[curr];
			val[2*curr+1]+=opt[curr]*cnt[2*curr+1];
			opt[2*curr+2]+=opt[curr];
			val[2*curr+2]+=opt[curr]*cnt[2*curr+2];
			opt[curr]=NOP;
		}
	}
	void UpdateRange(int l,int r,int value,int curr,int left,int right){
		if(left>=r || right<=l){
			return;
		}
		Propogate(curr,left,right);
		if(left>=l && right<=r){
			opt[curr]+=value;
			val[curr]+=value*cnt[curr];
			return;
		}
		int mid=(left+right)/2;
		UpdateRange(l,r,value,2*curr+1,left,mid);   
		UpdateRange(l,r,value,2*curr+2,mid,right);
		val[curr]=val[2*curr+1]+val[2*curr+2];
	}
	void UpdateRange(int l,int r,int value){
		UpdateRange(l,r,value,0,0,sz);
	}
	void UpdateIndex(int i,int value,int curr,int left,int right){
		if(right-left==1){
			opt[curr]+=value;
			val[curr]+=value*cnt[curr];
			return;
		}
		int mid=(left+right)/2;
		if(i<mid){
			UpdateIndex(i,value,2*curr+1,left,mid);
		}else{
			UpdateIndex(i,value,2*curr+2,mid,right);
		}   
		val[curr]=val[2*curr+1]+val[2*curr+2];
	}
	void UpdateIndex(int i,int value){
		UpdateIndex(i,value,0,0,sz);
	}
	int QueryIndex(int i,int curr,int left,int right){
		if(right-left==1){
			return val[curr];
		}		
		Propogate(curr,left,right);
		int mid=(left+right)/2;
		if(i<mid){
			return QueryIndex(i,2*curr+1,left,mid);
		}else{
			return QueryIndex(i,2*curr+2,mid,right);
		}
	}
	int QueryIndex(int i){
		return QueryIndex(i,0,0,sz);
	}
	int QueryRange(int l,int r,int curr,int left,int right){
		if(left>=r || right<=l){
			return NEU;
		}
		Propogate(curr,left,right);
		if(left>=l && right<=r){
			return val[curr];
		}
		int mid=(left+right)/2;
		int c1=QueryRange(l,r,2*curr+1,left,mid);
		int c2=QueryRange(l,r,2*curr+2,mid,right);
		return c1+c2;
	}
	int QueryRange(int l,int r){
		return QueryRange(l,r,0,0,sz);
	}
	int Kth(int k,int curr,int left,int right){
		if(right-left==1){
			return left;
		}		
		Propogate(curr,left,right);
		int mid=(left+right)/2;
		if(val[2*curr+1]>k){
			return Kth(k,2*curr+1,left,mid);
		}else{
			return Kth(k-val[2*curr+1],2*curr+2,mid,right);
		}
	}
	int Kth(int k){
		return Kth(k,0,0,sz);
	}
};
