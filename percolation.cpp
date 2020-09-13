#include <iostream>
#include <vector>
#include "unionfind.h"

class Percolation{
    int n;
    vector<vector<bool>> grid;
    UnionFind *uf;
    int openSites;

public:
    Percolation(int N){
        n = N;
        grid.assign(N, vector<bool>(N, false));
        uf = new UnionFind(N*N + 2);
        openSites = 0;

        for(int i = 0; i < N; ++i){
            uf->_union(0, encode(0, i));
            uf->_union(N*N + 1, encode(N-1, i));
        }
    }

    void open(int row, int column){
        if(isOpen(row, column)) return;
        if(row < 0 || row > n-1 || column < 0 || column > n-1) return;
        grid[row][column] = true;
        openSites++;
        if(row-1 >=0 && row-1 < n && isOpen(row-1, column)){
            uf->_union(encode(row-1, column), encode(row, column));
        }
        if(row+1 >= 0 && row+1 < n && isOpen(row+1, column)){
            uf->_union(encode(row+1, column), encode(row, column));
        }
        if(column-1 >= 0 && column-1 < n && isOpen(row, column-1)){
            uf->_union(encode(row, column-1), encode(row, column));
        }
        if(column+1 >= 0 && column+1 < n && isOpen(row, column+1)){
            uf->_union(encode(row, column+1), encode(row, column));
        }
    }

    bool isOpen(int row, int column){ return grid[row][column]; }

    bool isFull(int row, int column){ return isOpen(row, column) && uf->connected(0, encode(row, column)); }

    bool percolates(){ return uf->connected(0, n*n +1); }

    int numberOfOpenSites(){ return openSites; }

    void printGrid(){
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                cout << grid[i][j] << " ";
            }
        cout << endl;
        }
    cout << endl;
    uf->printId();
    }

private:
    int encode(int row, int column){ return(n * row + column + 1); }
};
