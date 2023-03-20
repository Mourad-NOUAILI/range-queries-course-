/*
    Problem: https://cses.fi/problemset/task/1646
    Task: range sum queries 
    Technique: naive
    Time complexity of the RSQ: O(n)
    Time complexity of the whole code: O(q.n)
    Space complexity: O(n): input array
*/


#include<bits/stdc++.h>

/**
 * Technique: 
 * This function return the sum in range BTW two positions in a given input array
 * Time complexity: O(n)
 * Auxillary space complexity: O(1)
 *
 * @param array input - The array that contains original data
 * @param long l - The left boundary of the range query
 * @param long r - The right boundary of the range query
 * @return long - return sum(input[l,r])
 **/
long range_query_pre(long* pre, long l, long r){
    return pre[r+1]-pre[l];
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    // Read input array's size n and number of queries q
    long n,q;
    std::cin >> n >> q; 

    // Read the longegers of the input array
    long* pre = new long[n+1];
    pre[0] = 0;
    for (long i = 1 ; i <= n ; ++i) {
        long v;
        std::cin >> v;
        pre[i] = pre[i-1] + v;
    }

    // Run over the queries
    for (long i = 1 ; i <= q ; ++i) {
        // Read left bound and the right bound of the range query
        long l,r;
        std::cin >> l >> r;

        // Compute sum(input[l,r])
        long ans = range_query_pre(pre, --l, --r);

        // Display the answer
        std:: cout << ans << '\n';
    }

    delete[] pre;

    return 0;
}