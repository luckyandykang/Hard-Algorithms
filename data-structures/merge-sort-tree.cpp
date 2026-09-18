#include <vector>
#include <algorithm>
#include <utility>

template<typename T> class MergeSortTree{
	std::vector<std::vector<T>> tree;
    
    MergeSortTree(vector<T>& vec){
        int n = vec.size();
        tree.resize(n << 1 | 1);
        for (int i = 0; i < n; i++) tree[n + i].push_back(vec[i]);
        for (int i = n - 1; i > 0; i--){
            tree[i].resize(tree[i << 1].size() + tree[i << 1 | 1].size());
            std::merge(tree[i << 1].begin(), tree[i << 1].end(), tree[i << 1 | 1].begin(), tree[i << 1 | 1].end(), tree[i].begin());
        }
    }
};