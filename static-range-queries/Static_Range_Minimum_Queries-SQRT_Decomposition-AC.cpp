
/*
    Problem: https://cses.fi/problemset/task/1647/
    Task: Static range minimum queries
    Technique: Square root decompoition
    Time complexity of one RMQ: O(sqrt(n))
    Time complexity of the total of RMQs: O(q sqrt(n))
    Time complexity of the whole code: O(n) + O(q sqrt(n))
    Space complexity: O(n): the prefix array + O(sqrt(n)): the blocks array
*/

#include <bits/stdc++.h>

#define INF std::numeric_limits<long>::max()

/**
 * This function return an array of size ceil(sqrt(n)), will store the minimum of
 * each m cells of the original array into a cell in the result array
 * Time complexity: O(n)
 * Auxillary space complexity: O(n)
 *
 * @param array A - The original array
 * @param int n - The size of the original array
 * @param int m - The size of the result array
 * @return array - return array of size m
 **/
long* build(long* A, int n, int m){
    long* B = new long[m];
    for (int i = 0 ; i < m ; ++i) B[i] = INF;

    for(int i = 0 ; i < n ; ++i) B[i/m] = std::min(B[i/m],A[i]);
    return B;
}

/**
 * @param array A - The original array
 * @param array B - The precomputed array
 * @param int m - The size of the array B
 * @param int l - The left boundary of the range query
 * @param int r - The right boundary of the range query
 * @return long - return min(A[l,r])
 **/
long range_query(long* A, long* B, int m, int l, int r){
    long ans = INF;
    while(l<=r){
        if(l % m == 0 && l+m <= r) {
            ans = std::min(ans,B[l/m]);
            l = l + m;
        }
        else ans = std::min(ans,A[l++]);
    }
    return ans;
}


int main() {

    int n,q;
    std::cin >> n >> q;

    long* A = new long[n];
    for (int i = 0 ; i < n ; ++i) std::cin>>A[i];

    int m = ceil(sqrt(n));

    long* B = build(A,n,m);

    for (int i = 1 ; i <= q ; ++i) {
        int l,r;
        std::cin >> l >> r;
        std::cout << range_query(A,B,m,--l,--r) << '\n';
    }

    return 0;
}