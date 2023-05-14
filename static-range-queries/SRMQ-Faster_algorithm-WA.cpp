/*
    Problem: https://cses.fi/problemset/task/1647/
    Task: Static range minimum queries
    Technique: Faster algorithm
    Time complexity of a signle RMQ: O(1)
    Time complexity of total RMQs: O(q)
    Time complexity of the whole code: O(n)
    Space complexity:
        O(n): the original array
        O(n/log2 n): the blocks array
        O(n): sparse table

*/

#include<bits/stdc++.h>

typedef std::unordered_map<int,std::vector<long>> BlocksList;

typedef std::unordered_map<int, std::string> BlockNorm;
typedef std::unordered_map<std::string, int> NormBlock;

typedef std::vector<std::vector<int>> vvi;
typedef std::unordered_map<std::string,vvi> NormAnswers;

#define INF std::numeric_limits<long>::max()

/**
 * This function returns the array of blocks and also a hashmap the list of elements of each block
 * Time complexity: O(n)
 * Auxillary space complexity: O(2x_b+n)
 * bs = ceil((double)log2(n)/4)
 * _b = ceil((double)n/bs)
 *
 * @param array A - The array that contains original data
 * @param int n - size of the original array
 * @param int bs - size of each block
 * @return array B: array of blocks
           map blocks_list: list of elements of each block
 **/
void build_blocks(long* A, int n, int bs, long* & B , BlocksList & blocks_list){
    for(int i = 0 ; i < n ; ++i) {
        B[i/bs] = std::min(B[i/bs],A[i]);
        blocks_list[i/bs].push_back(A[i]);
    }
}

/**
 * This function returns the sparse table of a given array of blocks B
 * Time complexity: O(n)
 * Auxillary space complexity: O(_b     * log2(_b)+1)
 *  * bs = ceil((double)log2(n)/4)
 * _b = ceil((double)n/bs)
 *
 * @param array B - The array that contains original data
 * @param int m - size of the array of blocks
 * @return 2D-array st: sparse
 **/
void build_sparse(long* B, int m, long** & st){
    for(int i = 0 ; i < m ; ++i) st[i][0] = B[i];

    for(int j=1; (1<<j) <= m ; ++j){
        for(int i = 0 ; i+(1<<j)-1 < m ; ++i){
            st[i][j] = std::min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
        }
    }
}



/**
 * This function returns the binary representation of an array based on its cartesian tree construction
 * Time complexity: O(n)
 * Auxillary space complexity: O(2n)
 * 
 * @param array A - array of integers
 * @param int n - size of the array A
 * @return string normalization
 **/
std::string build_cartesian_tree(std::vector<long> A, int n){
    std::string normalization = "";
    std::stack<int> s;
    for (int i = 0 ; i < n ; ++i){
        while (!s.empty() && s.top() > A[i]) {
            s.pop();
            normalization += "0";
        }
        normalization += "1";
        s.push(A[i]);
    }
    while (!s.empty()) {
        s.pop();
        normalization += "0";
    }
    return normalization;
}



/**
 * This function returns:
 *****a map of blocks associate to their normalization
 *****a map of normalization associate to its first block
 * Time complexity: O(n)    
 * Auxillary space complexity: O(_b*2bs+_b+2^(2bs)*_b+2^(2bs))
 *  bs = ceil((double)log2(n)/4)
 * _b = ceil((double)n/bs)
 * 
 * @param map block_lists - the list of elements of each block
 * @param int bs - size of each block
 * @return block_norm: a map of blocks associate to their normalization
 *         norm_block: a map of normalization associate to its first block
 **/
void build_blocks_cartesian_trees(BlocksList blocks_list , int bs, BlockNorm & block_norm, NormBlock & norm_block){
    std::unordered_map<std::string, bool> visited;
    for(auto p: blocks_list){
        std::string norm = build_cartesian_tree(p.second,bs);
        //std::cout << p.first <<"/"<<norm << '\n';
        block_norm[p.first]=norm;
        if (!visited[norm]){
            norm_block[norm]=p.first;
            visited[norm] = true;
        }
    }
}



/**
 * This function returns a map of normalized blocks associate to their all precomputed abswers 2D-array
 * Time complexity: O(n)    
 * Auxillary space complexity: O(2^(bs)*2bs + 2^(2bs) * (bs)²)
 *  bs = ceil((double)log2(n)/4)
 * _b = ceil((double)n/bs)
 * 
 * @param map block_lists - the list of elements of each block
 * @param map norme_block - a map of blocks associate to their normalization
 * @param int bs - size of each block
 * @return norme_answers: a map of normalized blocks associate to their all precomputed abswers 2D-array
 **/
void build_all_ranges_in_normalized_blocks(BlocksList blocks_list, NormBlock norme_block, int bs, NormAnswers & norme_answers){
    for(auto p: norme_block){
        std::string norme = p.first;
        int b = p.second;

        std::vector<long> block = blocks_list[b];   

        vvi M(bs,std::vector<int>(bs,-1));
    
        for(int i = 0 ; i < bs ; ++i){
            for(int j = i ; j < bs ; ++j){
                if (i==j){
                    M[i][j] = i;
                    continue;
                }

                if (block[M[i][j-1]] > block[j]) M[i][j] = j-1;
                else M[i][j] = M[i][j-1];
            }
        }

        norme_answers[norme] = M;
    }

}


/**
 * This function returns the range minimum query on B[l,r] using a built sparse table
 * Time complexity: O(1)    
 * Auxillary space complexity: O(1)
 * 
 * @param array st - the 2D-array
 * @param int l - left boundary
 * @param int r - right boundary
 * @return int: min B[l,r]s
 **/
long RMQ(long** st, int l, int r){
    if (r < l) return INF;
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


    //std::cout <<A[175680] <<"----"<<A[175681] << '\n';
    // 398 654 360----891 148 615
    //59 786 073

    /*for(int i=0 ; i < n ; ++i) {
        if (A[i]==59786073) std::cout << i << "//" ; //175686
    }
    std::cout << '\n';*/

    //  Block's size
    int bs = ceil((double)log2(n)/4);


    // Block's array size
    int _b = ceil((double)n/bs);
    
S
    // Build the array of blocks and the map of blocks
    long* B = new long[_b];
    for(int i = 0 ; i < _b ; ++i) B[i] = INF;
    BlocksList blocks_list;
    build_blocks(A,n,bs,B,blocks_list);


    // Build sparse table
    long** st = new long*[_b];
    int m = log2(_b)+1;
    for(int i = 0 ; i < _b ; ++i) st[i] = new long[m];
    build_sparse(B,_b,st);

    // Associate blocks with their normalizations
    BlockNorm block_norm;
    NormBlock norm_block;
    build_blocks_cartesian_trees(blocks_list,bs,block_norm,norm_block);

    // Precompute all the answers of each block
    NormAnswers norm_answers;
    build_all_ranges_in_normalized_blocks(blocks_list,norm_block,bs,norm_answers);

    //std::cout << bs <<"/"<<_b << '\n';
    /*for(int i = 0 ; i < _b ; ++i) std::cout << B[i] << ' ';
    std::cout << '\n';
    for(auto e: block_norme) std::cout << e.first <<":" << e.second << '\n';
    std::cout << '\n';
    for(auto e: norme_block) std::cout << e.first <<":" << e.second << '\n';
    std::cout << '\n';
    std::cout << "********\n";

    for(auto p: norme_answers){
        std::string norme = p.first;
        std::cout << norme << ":\n";
        vvi M = p.second;
       for(int i = 0 ; i < bs ; ++i){
            for(int j = 0 ; j < bs ; ++j){
                std::cout << M[i][j] <<' ';
            }
            std::cout << '\n';
        }
    }*/
   
    
    
    // Time complexity of all queries: O(q)
    //std::cout << "-------------------\n";
    for(int i = 1 ; i <= q ; ++i){
        int l,r;
        std::cin >> l >> r;

        l--;
        r--;

        // Minimum of one element is that element,
        // No need to do all the work
        if (l==r) {
            std::cout << A[l] << '\n';
            continue;
        }

        // If the range [l,r] makes a list of entire blocks
        // Just use the sparse table
        if (l%bs==0 && (r+1)%bs==0){
            std::cout << RMQ(st,l/bs,r/bs)  << '\n';
            continue;
        }

        // Otherwise:
        /// Left boundary is not the beginning of the actual block
        /// Right boundary is not the end of the actual block

        // Compute to which blocks corresponds the left boundary
        // and the right boundary (lb: left block, rb: right block)
        int lb = l/bs;
        int rb = r/bs;

        // If the left boundary is not the beginning of the actual block
        // compute the beginning of the next block
        int l1 = l;
        if (l1%bs !=0) {
            l1=l1-l1%bs+bs;
        }

        // If the right boundary is not the end of the current block
        // Compute its beginning  
        int r1=r;
        if ((r1+1)%bs != 0) {
            r1=r1-r1%bs;
        }

        // Get the normalization string of the left block
        std::string norm_left=block_norm[lb];
        // Get all the answers of the left block
        vvi M_left = norm_answers[norm_left];

        // Get the normalization string of the right block
        std::string norm_right=block_norm[rb];  
        // Get all the answers of the right block
        vvi M_right = norm_answers[norm_right];

        /*std::cout << "---" <<  lb <<"///" << norme_left << '\n';
        std::cout << "*****" << M_left[l%bs][l1%bs] << '\n';
        std::cout << "---" <<  rb << "///" << norme_right << '\n';
        std::cout << "*****" <<M_right[r1%bs][r%bs] << '\n';*/

        // Compute the min of the part on the left and the part on the right
        long x = std::min(A[M_left[l%bs][(l1-1)%bs]+lb*bs],A[M_right[r1%bs][r%bs]+rb*bs]);
        
        //r1=(f)?r1:r1-1;
        
        /*std::cout << "rmq" <<l1+1 << '\n';
        std::cout << "rmq" << r1-1 << '\n';*/

        // Compute the min of entire blocks
        long y = RMQ(st,l1/bs,(r1-1)/bs);
        
        /*std::cout << "y:" << y << '\n';
        std::cout << "rmq" << l1+1 << '\n';
        std::cout << "rmq" << r1-1 << '\n';*/


        long ans = std::min(x,y);

        std::cout << ans << '\n';
    }

    delete[] st;
    delete[] B;
    delete[] A;

    return 0;
}


/*
for(int i=0; i < log2(n)+1 ; ++i){
    for(int j = 0 ; j < n ; ++j){
        // operations
    }
}

for(int i = 0 ; i < n/bs ;++i){
    for(int j = 0 ; j < log2(n/bs)+1 ;++j){
        // operations
    }
}

*/