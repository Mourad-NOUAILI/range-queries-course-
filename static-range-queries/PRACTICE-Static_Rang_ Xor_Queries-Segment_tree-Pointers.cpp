/*
    Segment tree using array
    Time complexity: O(m) + O(qlog n)
    Auxillary space complexity: O(n)
    Total space complexity:O(n) + O(m)
*/
 
#include<bits/stdc++.h>
 
struct Node {
    long val;
    Node* left;
    Node* right;

    Node(long val): val(val), left(nullptr),right(nullptr) {}
    Node(long val, Node* left, Node* right): val(val), left(left),right(right) {}
};

Node* build(long* A, int s, int e){
    if (s==e) {
        return new Node(A[s]);
    }
    int mid = (s+e)>>1;
    Node* left = build(A,s,mid);
    Node* right = build(A,mid+1,e);
    return new Node(left->val ^ right->val,left,right);
}

long query(Node* root, int s, int e, int l, int r){
    if (l > e || r < s) return 0;
    if (l <= s && r >= e) return root->val;
    int mid = (s+e)>>1;
    return (query(root->left,s,mid,l,r) ^ query(root->right,mid+1,e,l,r));
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
    
    Node* seg=build(A,0,n-1);

    for (int i = 1 ; i <= q ; ++i){
        int l,r;
        std::cin >> l >> r;
        l--;
        r--;
        std::cout << query(seg,0,n-1,l,r) << '\n';
    }
 
    delete [] A;
    return 0;
}