/*
    Problem: https://cses.fi/problemset/task/1646
    Task: range sum queries 
    Technique: SQRT decomposition
    Time complexity of the RSQ: O(sqrt(n))
    Time complexity of the whole code: O(qxO(sqrt(n)))
    Space complexity: O(sqrt(n)): the SQRTs array
*/


#include<bits/stdc++.h>

std::vector<long> build(long* A, int n, int m) {
    std::vector<long> B(m,0);
    for(int i = 0 ; i < n ; ++i) B[i/m] += A[i];
    return B;
}

long range_query(long* A, std::vector<long> B, int m, int l, int r){
    long ans = 0;
    while(l <= r){
        if (l%m == 0 && l+m <= r) {
            ans += B[l/m];
            l += m;
        }
        else ans += A[l++];
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    // Read input array's size n and number of queries q
    long n,q;
    std::cin >> n >> q; 
    
    long* A = new long[n];
    for (long i = 0 ; i < n ; ++i) std::cin >> A[i];

    int m = ceil(sqrt(n));
    std::vector<long> B = build(A,n,m);

    // Run over the queries
    for (long i = 1 ; i <= q ; ++i) {
        // Read left bound and the right bound of the range query
        long l,r;
        std::cin >> l >> r;

        // Compute sum(input[l,r]

        // Display the answer
        long ans = range_query(A,B,m,--l,--r);
        std:: cout << ans << '\n';
    }

    delete[] A;

    return 0;
}