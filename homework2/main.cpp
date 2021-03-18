#include <iostream>
#include "polynomial.h"
#include <sstream>
#include <assert.h>


using namespace std;


int main() {
    Polynomial p1(0, 2, new int[3]{1, 2, 3});
    Polynomial p2(5, 5, new int[1]{5});
    Polynomial p3 = p1 + p2;
    p3.show();
    Polynomial p4 = p3 * 3;
    p3*=3;
    p3.show();
    p4.show();
    cout << p4[4] << endl;
    return 0;
}