#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;
int n = 1000001;


int hashx(long x)
{
    return abs((int)(x*0.618) % n);
}

int main()
{
    ifstream fin("set.in");
    ofstream fout("set.out");
    long x;

    string cmd;
    vector<list<long>> array(n);
    while (fin >> cmd && fin >> x)
    {
        if (cmd == "insert")
        {
            int h = hashx(x);
            bool is_found = false;
            for (auto i : array[h])
                if (i == x)
                {
                    is_found = true;
                    break;
                }
            if (!is_found)
            {
                array[h].push_front(x);
            }

        }
        else
        {
            if (cmd == "exists")
            {
                int h = hashx(x);
                bool is_found = false;
                for (auto i : array[h])
                    if (i == x)
                    {
                        is_found = true;
                        break;
                    }
                if (is_found) {
                    fout << "true\n";
                }
                else {
                    fout << "false\n";
                }
            }
            else
            {
                if (cmd == "delete")
                {
                    int h = hashx(x);
                    array[h].remove(x);
                }
            }
        }
    }
}