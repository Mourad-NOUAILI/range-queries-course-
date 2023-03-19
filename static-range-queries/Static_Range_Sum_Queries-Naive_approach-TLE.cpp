/*
    Problem: https://cses.fi/problemset/task/1646
    Task: range sum query
    Technique: naive
    Time complexity of the RSQ: O(n)
    Time complexity of the whole code: O(q.n)
    Space complexity: O(n): input array
*/


#include<bits/stdc++.h>

/**
 * Technique: Naive gives TLE
 * This function return the sum in range BTW two positions in a given input array
 * Time complexity: O(n)
 * Auxillary space complexity: O(1)
 *
 * @param array input - The array that contains original data
 * @param int l - The left boundary of the range query
 * @param int r - The right boundary of the range query
 * @return int - return sum(input[l,r])
 **/
int range_query_naive(int* input, int l, int r){
    int s = 0;
    for (int i = l ; i <= r ; ++i) s += input[i];
    return s;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    // Read input array's size n and number of queries q
    int n,q;
    std::cin >> n >> q; 

    // Read the integers of the input array
    int* input = new int[n];
    for (int i = 0 ; i < n ; ++i) std::cin >> input[i];

    // Run over the queries
    for (int i = 1 ; i <= q ; ++i) {
        // Read left bound and the right bound of the range query
        int l,r;
        std::cin >> l >> r;

        // Compute sum(input[l,r])
        int ans = range_query_naive(input, --l, --r);

        // Display the answer
        std:: cout << ans << '\n';
    }

    delete[] input;

    return 0;
}
