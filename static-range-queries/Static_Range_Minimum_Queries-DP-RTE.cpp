/*
    Problem: https://cses.fi/problemset/task/1647
    Task: range minimum queries
    Technique: Dynamic programming
    Time complexity of the RMQ: O(1)
    Time complexity of the whole code: O(q)
    Space complexity: O(n): input array + O(n^2): the matrix
*/

#include <bits/stdc++.h>

#define INF std::numeric_limits<long>::max()

int main() {

    long n,q;
    std::cin >> n >> q;

    long* A = new long[n];
    for (int i = 0 ; i < n ; ++i){
        std::cin>>A[i];
    }

   
    long** M = new long*[n+1];
    for(int i = 0 ; i <= n ; ++i) M[i] = new long[n+1];

    // Time complexity: O(n^2)
    for (int i = 0 ; i <= n ; ++i){
        for (int j = 0 ; j <= n ; ++j) {
            M[i][j] = INF;
        }
    }

    for(int i = 0 ; i <= n ; ++i){
        for (int j = i ; j <= n ; ++j) {
            M[i][j] = std::min(M[i][j-1],A[j-1]);
        }
    }
    // Time complexity of all queries: O(q)
    for(int i = 1 ; i <= q ; ++i){
        long l,r;
        std::cin >> l >> r;
        // Time commpexity: O(1)
        std::cout << M[l][r] << '\n';
    }

    for(int i = 0 ; i <= n ; ++i) delete [] M[i];
    delete [] M;

    delete[] A;

    return 0;
}