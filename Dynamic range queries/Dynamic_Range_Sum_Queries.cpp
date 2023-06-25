/*
    Problem: Dynamic Range Sum Queries: https://cses.fi/problemset/task/1648/
    Technique: Segment tree
    Single update time complexity: O(log m)
    Single query time complexity: O(log m)
    Overall time complexity: O(m) + O(q log m)
    Auxillary space complexity: O(m)
    Overall space complexity: O(n) + O(n)
*/

#include<bits/stdc++.h>
 

void build(long*& seg, long* A, int s, int e, int pos){
    if (s==e) {
        seg[pos]=A[s];
        return;
    }
    int mid = (s+e)>>1;
    build(seg,A,s,mid,2*pos+1);
    build(seg,A,mid+1,e,2*pos+2);
    seg[pos] = seg[2*pos+1]+seg[2*pos+2];
}

long query(long*& seg, int s, int e, int p, int l, int r){
    if (l > e || r < s) return 0;
    if (l<=s && r >= e) return seg[p];
    int mid = (s+e)>>1;
    return query(seg,s,mid,2*p+1,l,r)+query(seg,mid+1,e,2*p+2,l,r);
}

void point_update(long*& seg, int s, int e, int p, int i, long val){
    if (s==e) {
        seg[p] = val;
        return;
    }
    int mid = (s+e)>>1;
    if (i>= s && i <= mid) point_update(seg,s,mid,2*p+1,i,val);
    else point_update(seg,mid+1,e,2*p+2,i,val);

    seg[p] =  seg[2*p+1]+seg[2*p+2];
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
 
    int n,q;
    std::cin >> n >> q;
 
    long* A = new long[n];
    for(int i = 0 ; i < n ; ++i) {
        std::cin >> A[i];
    };

    int k=ceil(log2(n));
    int m= 2*(1<<k)-1;
    long* seg=new long[m];
    for (int i=0;i < m; ++i) seg[i]=0;
    build(seg,A,0,n-1,0);

    for (int i = 1 ; i <= q ; ++i) {
        int op,a,b;
        std::cin >> op >> a >> b;
        if (op == 1) point_update(seg,0,n-1,0,--a,b);
        else std::cout << query(seg,0,n-1,0,--a,--b) << '\n'; 
    }

    delete[] seg;
    delete [] A;

    
    return 0;
}