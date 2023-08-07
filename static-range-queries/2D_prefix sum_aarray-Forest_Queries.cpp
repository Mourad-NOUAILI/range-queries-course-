#include<bits/stdc++.h>

typedef unsigned long long ull;
typedef std::vector<std::vector<ull>> vvull;

void build_prefix(vvull& grid, vvull& pre, int n){
    for(ull i=1 ; i<=n; ++i){
        for(ull j=1 ; j<=n; ++j){
            pre[i][j] = pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1]+grid[i-1][j-1]*1ull;
        }
    }
}

int main(){
    ull n,q;
    std::cin>>n>>q;
    
    vvull grid(n,std::vector<ull>(n));
    for(ull i=0 ; i<n ; ++i){
        for(ull j=0 ; j<n ; ++j){
            char c;
            std::cin>>c;
            grid[i][j]=c=='*'?1:0;
        }
    }

    vvull pre(n+1,std::vector<ull>(n+1,0));
    build_prefix(grid,pre,n);

    /*for(ull i=0 ; i<=n ; ++i){
        for(ull j=0 ; j<=n ; ++j){
            std::cout << pre[i][j] << " ";
        }
        std::cout << '\n';
    }*/

    for(ull i=1 ; i<=q ; ++i){
        ull row1,col1,row2,col2;
        std::cin>>row1>>col1>>row2>>col2;
        std::cout << pre[row2][col2]-pre[row1-1][col2]-pre[row2][col1-1]+pre[row1-1][col1-1] << '\n';
    }
    
    return 0;
}