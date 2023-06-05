/*
    Segment tree using array
    Time complexity: O(m) + O(q log m)
    Auxillary space complexity: O(n)
    Total space complexity:O(n) + O(m)
*/

#include<bits/stdc++.h>
 

void build(long* & seg, long* A, int s, int e, int p){
    if (s==e) {
        seg[p] = A[s];
        return;
    }
    int mid = (s+e)>>1;
    build(seg,A,s,mid,2*p+1);
    build(seg,A,mid+1,e,2*p+2);
    seg[p]=seg[2*p+1]+seg[2*p+2];
}


long query(long* seg, int s, int e, int l, int r, int p){
    if (l > e || r < s) return 0;
    if (l <= s && r >= e) return seg[p];
    int mid = (s+e)>>1;
    return query(seg,s,mid,l,r,2*p+1) + query(seg,mid+1,e,l,r,2*p+2);
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
    for (int i = 0 ; i < m ; ++i) seg[i]=0;

    build(seg,A,0,n-1,0);

    for (int i = 1 ; i <= q ; ++i){
        int l,r;
        std::cin >> l >> r;
        l--;
        r--;

        std::cout << query(seg, 0, n - 1, l, r, 0) << '\n';
    }
 
    delete [] A;
    delete [] seg;
    return 0;
}