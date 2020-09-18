/*
    Percolation modelled using NxN grid and Union-Find Datastructure

    author: Karan Bishwakarma
*/
#include <iostream>
#include <vector>
#include "unionfind.h"

class Percolation{
    int n;
    vector<vector<bool>> grid;

    UnionFind *uf;
    UnionFind *ufForFullness;

    int openSites;
    int virtualTop;
    int virtualBottom;

public:
    Percolation(int N){
        n = N;
        grid.assign(N, vector<bool>(N, false));

        uf = new UnionFind(N*N + 2);
        ufForFullness = new UnionFind(N*N + 1);

        openSites = 0;
        virtualTop = 0;
        virtualBottom = N*N + 1;

        for(int i = 0; i < N; ++i){
            uf->_union(virtualTop, encode(0, i));
            uf->_union(virtualBottom, encode(N-1, i));

            ufForFullness->_union(virtualTop, encode(0, i));
        }
    }

    // Opening a
    void open(int row, int column){
        if(isOpen(row, column)) return;

        grid[row][column] = true;
        ++openSites;

        // Connecting to left neighbor
        if(column > 0 && isOpen(row, column - 1)){
            uf->_union(encode(row, column), encode(row, column - 1));
            ufForFullness->_union(encode(row, column), encode(row, column - 1));
        }
        // Connecting to right neighbor
        if(column < (n-1) && isOpen(row, column + 1)){
            uf->_union(encode(row, column), encode(row, column + 1));
            ufForFullness->_union(encode(row, column), encode(row, column + 1));
        }
        // Connecting to top neighbor
        if(row > 0 && isOpen(row - 1, column)){
            uf->_union(encode(row, column), encode(row - 1, column));
            ufForFullness->_union(encode(row, column), encode(row - 1, column));
        }
        // Connecting to bottom neighbor
        if(row < (n-1) && isOpen(row + 1, column)){
            uf->_union(encode(row, column), encode(row + 1, column));
            ufForFullness->_union(encode(row, column), encode(row + 1, column));
        }
    }
    // If site is Open
    bool isOpen(int row, int column){ return grid[row][column]; }

    // If site if Full
    bool isFull(int row, int column){ return isOpen(row, column) && ufForFullness->connected(virtualTop, encode(row, column)); }

    // If grid percolates
    bool percolates(){ return uf->connected(virtualTop, virtualBottom); }

    // Returns number of open sites
    int numberOfOpenSites(){ return openSites; }

private:
    // Returns index for given row and column
    int encode(int row, int column){ return(n * row + column + 1); }
};
