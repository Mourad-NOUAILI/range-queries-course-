#include<bits/stdc++.h>

typedef std::vector<int> veci;
typedef std::unordered_map<int,veci> mivi;
typedef std::unordered_map<int,int> mii;

void build_map(int* pre, int n , mivi & val_indexes){
    for(int i = 0 ; i < n ; ++i) val_indexes[pre[i]].push_back(i);
}

// O(n)
void build_pre(std::string s, int n, int* & pre){
    pre[0]=0;
    for(int i = 1 ; i < n ; ++i){
        char c=s[i-1];
        if (c=='(') pre[i] = pre[i-1]+1;
        if (c==')') pre[i] = pre[i-1]-1;
    }
}

// O(n log n)
void build_sparse(int* pre, int n, int** &  st){
    for(int i = 0 ; i < n ; ++i) st[i][0] = pre[i];

    for(int j=1 ; (1<<j) <= n ; ++j){
        for(int i = 0 ; i+(1<<j)-1 < n ; ++i){
            st[i][j] = std::min(st[i][j-1] , st[i+(1<<(j-1))][j-1]);
        }
    }
}

// O(1)
int RMQ(int** st, int l, int r){
    int len = r-l+1;
    int k = log2(len);
    int p = r+1-(1<<k);
    return std::min(st[l][k],st[p][k]);
}

// Amortized O(n)
void solve(int** st, int* pre, mivi val_indexes){
    int max_len = -1;
    mii nb;
    for(auto p: val_indexes){
        veci indexes = p.second;
        
        if (indexes.size() < 2) continue;

        int m = indexes.size();
        int i = 0;
        int j = 1;
        while (j < indexes.size()){

            int l = indexes[i];
            int r = indexes[j];

            int vi = pre[indexes[i]];

            int mi = RMQ(st,l++,r);

            if (mi >= vi) {
                int len = r-l+1;
                if (max_len <= len) {
                    max_len = len;
                    nb[max_len]++;
                }
                j++;
            }
            else {
                i++;
                j=i+1;
            }
        }
    }

    nb.size() == 0?std::cout << "0 1":std::cout << max_len << " " << nb[max_len] << '\n';
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::string s;
    std::cin >> s;

    int n = s.size();
    int* pre = new int[n+1];
    build_pre(s,n+1,pre);

    /*for(int i = 0 ; i <= n ; ++i) std::cout << pre[i] << ' ';
    std::cout <<'\n';*/

    mivi val_indexes;
    build_map(pre,n+1,val_indexes);

    int m = log2(n+1)+1;
    int** st = new int*[n+1];
    for (int i = 0 ; i < n+1 ; ++i) st[i] = new int[m];
    build_sparse(pre,n+1,st);

    solve(st,pre,val_indexes);


    /*for(auto p: val_indexes){
        std::cout << p.first <<": ";
        for(auto e: p.second) std::cout << e << ' ';
        std::cout << '\n';
    }*/

    delete[] st;
    delete[] pre;


    return 0;
}