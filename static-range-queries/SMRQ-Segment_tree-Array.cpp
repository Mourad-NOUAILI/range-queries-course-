/*
    Segment tree using array
    Time complexity: O(m) + O(q log m)
    Auxillary space complexity: O(n)
    Total space complexity:O(n) + O(m)
*/

#include<bits/stdc++.h>
 
#define INF std::numeric_limits<long>::max()

/**
 * 
 * Time complexity: O(m)
 * Auxillary space complexity: O(m)
 * Total space complexity: O(n)+O(m)
 * 
 * @param array A - The input array
 * @param array seg_tree - The segment tree to build
 * @param int start_pos - the first boundary of the actual node in the segment tree in the array that represents the segment tree
 * @param int end_pos - the second boundary of the actual node in the segment tree in the array that represents the segment tree
 * @param int pos - The the index of the actual node of the segment tree in the array that represents the segment tree
 * @return array - return the segment tree as an array
 */
void build(long* A, long* & seg, int start_pos, int end_pos, int pos){
    if (start_pos==end_pos){
        seg[pos] = A[start_pos];
        return;
    }
    int mid = (start_pos+end_pos)>>1;
    build(A,seg,start_pos,mid,2*pos+1);
    build(A,seg,mid+1,end_pos,2*pos+2);
    seg[pos] = std::min(seg[2*pos+1],seg[2*pos+2]);
} 


/**
 * This function return the minimun value in range BTW two positions in a given input array
 * Time complexity: O(log2(m))
 * Auxillary space complexity: O(m)
 * Total space complexity: O(n)+O(m)
 * 
 * @param array A - The input array
 * @param array seg_tree - The segment tree to build
 * @param int start_pos - the first boundary of the actual node in the segment tree in the array that represents the segment tree
 * @param int end_pos - the second boundary of the actual node in the segment tree in the array that represents the segment tree
 * @param int pos - The the index of the actual node of the segment tree in the array that represents the segment tree
 * @return array - return the segment tree as an array
 */
long RMQ(long* seg, int start_pos, int end_pos, int l, int r, int pos){
    if (l > end_pos || r < start_pos) return INF;
    if (l <= start_pos && r >= end_pos) return seg[pos];
    int mid=(start_pos+end_pos)>>1;
    return std::min(RMQ(seg,start_pos,mid,l,r,2*pos+1),RMQ(seg,mid+1,end_pos,l,r,2*pos+2));
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
    
    
    /*********Build segment tree*************/
    int k = ceil(log2(n));
    int m =2*(1<<k)-1;
    
    long* seg = new long[m];
    for(int i = 0 ; i < m ; ++i) seg[i]=INF;
    build(A,seg,0,n-1,0);

 
    for (int i = 1 ; i <= q ; ++i){
        int l,r;
        std::cin >> l >> r;
        l--;
        r--;

        std::cout << RMQ(seg,0,n-1,l,r,0) << '\n';
    }
 
    delete [] A;
    delete [] seg;
    return 0;
}