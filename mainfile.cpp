#include <iostream>
#include "percolation.cpp"

using namespace std;

int main()
{
    Percolation p(5);
    p.open(3, 3);
    p.open(0, 1);
    p.open(2, 2);
    p.open(1, 2);
    p.open(4, 3);
    p.open(1, 1);
    p.open(3, 2);
    p.open(4, 0);
    p.open(3, 0);
    p.printGrid();
    cout << endl << "Percolates: " << p.percolates() << endl;
    cout << p.numberOfOpenSites() << " sites are open." << endl;
    return 0;
}
