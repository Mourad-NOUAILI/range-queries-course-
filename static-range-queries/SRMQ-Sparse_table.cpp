/*
    Problem: https://cses.fi/problemset/task/1647/
    Task: Static range minimum queries
    Technique: Sparse table
    Time complexity of a signle RMQ: O(1)
    Time complexity of total RMQs: O(q)
    Time complexity of the whole code: O(n log n) + O(q)
    Space complexity: O(n): the original array + O(n log n): the sparse array
*/

#include<bits/stdc++.h>

void build(long* A, int n, long** & st){
    for(int i = 0 ; i < n ; ++i) st[i][0] = A[i];

    for(int j=1; (1<<j) <= n ; ++j){
        for(int i = 0 ; i+(1<<j)-1 < n ; ++i){
            st[i][j] = std::min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
        }
    }
}

long RMQ(long** st, int l, int r){
    int len = r-l+1;
    int k = log2(len);
    int p = r+1-(1<<k);
    return std::min(st[l][k],st[p][k]); 
}

int main() {

    long n,q;
    std::cin >> n >> q;

    long* A = new long[n];
    for (int i = 0 ; i < n ; ++i){
        std::cin>>A[i];
    }

    int m = log2(n)+1;

    long** st = new long*[n];
    for(int i = 0 ; i < n ; ++i) st[i] = new long[m];
    build(A,n,st);
   
    
    // Time complexity of all queries: O(q)
    for(int i = 1 ; i <= q ; ++i){
        long l,r;
        std::cin >> l >> r;
        std::cout << RMQ(st,--l,--r) << '\n';
    }

    delete[] st;
    delete[] A;

    return 0;
}
