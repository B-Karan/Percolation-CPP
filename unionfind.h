#include <iostream>
#include <vector>

using namespace std;

class UnionFind{
    std::vector<int> id;
    std::vector<int> sz;

public:
    UnionFind(int N){
        id.resize(N);
        sz.resize(N);
        for(int i = 0; i < id.size(); ++i) {id[i] = i; sz[i] = 1;}
    }
private:
    int root(int i){
        while(i != id[i]) {i = id[i];}
        return i;
    }

public:
    void _union(int p, int q){
        int i = root(p);
        int j = root(q);
        if(i == j) return;
        if(sz[i] < sz[j]) {id[i] = j; sz[j] += sz[i];}
        else {id[j] = i; sz[i] += sz[j];}
    }

    bool connected(int p, int q) {return root(p) == root(q);}

    void printId(){
        for(auto i = id.begin(); i != id.end(); ++i){
            cout << *i << " ";
        }
        cout << endl;
    }
};
