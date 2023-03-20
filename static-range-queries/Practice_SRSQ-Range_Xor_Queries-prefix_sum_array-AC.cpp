// Whole time complexity: O(q)
// Whole space complexity: O(n)

#include <bits/stdc++.h>


int main() {
    long n,q;
    std::cin >> n >> q;

    // Build prefix sume array in O(n) time complexity
    long* pre = new long [n+1];
    pre[0] = 0;
    for (long i = 1 ; i <= n ; ++i) {
        long v;
        std::cin >> v;

        pre[i] = pre[i-1] ^ v;
    }

    for (long i = 1 ; i <= q ; ++i) {
        long l,r;
        std::cin >> l >> r;
        // O(1)
        long ans = pre[--r+1] ^ pre[--l];
        std:: cout << ans << '\n';
    }

    delete[] pre;

    return 0;
}