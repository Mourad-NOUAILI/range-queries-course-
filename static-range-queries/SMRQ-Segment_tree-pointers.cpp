/*
    Segment tree using array
    Time complexity: O(m) + O(qlog n)
    Auxillary space complexity: O(n)
    Total space complexity:O(n) + O(m)
*/
 
#include<bits/stdc++.h>
 
#define INF std::numeric_limits<long>::max()


// Define a node
struct Node{
    long val;
    Node* left;
    Node* right;

    Node(long val): val(val),left(nullptr),right(nullptr){};
    Node(long val,Node *left,Node* right): val(val),left(left),right(right){};
};


/**
 * This function return a pointer to the root of the segment tree
 * Time complexity: O(m)
 * Auxillary space complexity: O(m)
 * Total space complexity: O(n)+O(m)
 * 
 * @param array A - The input array
 * @param int start_pos - the first boundary of the actual node in the segment tree in the array that represents the segment tree
 * @param int end_pos - the second boundary of the actual node in the segment tree in the array that represents the segment tree
 * @return Node* - return a pointer to the root of the segment tree
 */
Node* build(long* A, int start_pos,int end_pos) {
    if(start_pos==end_pos){
        return new Node(A[start_pos]);
    }
    int mid=(start_pos+end_pos)>>1;
    Node* left=build(A,start_pos,mid);
    Node* right=build(A,mid+1,end_pos);
    return new Node(std::min(left->val,right->val), left,right);
}

long RMQ(Node* root, int s, int e, int l, int r){
    if (l > e || r < s) return INF;
    if (l <= s && r >= e) return root->val;
    int mid=(s+e)>>1;
    return std::min(RMQ(root->left,s,mid,l,r),RMQ(root->right,mid+1,e,l,r));
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
    Node* seg = build(A,0,n-1);
    /***************************************/
 
    for (int i = 1 ; i <= q ; ++i){
        int l,r;
        std::cin >> l >> r;
        l--;
        r--;

        std::cout << RMQ(seg,0,n-1,l,r) << '\n';
    }
 
    delete [] A;
    return 0;
}