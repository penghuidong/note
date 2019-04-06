#include <iostream>
using namespace std;

template <typename T>
class templateTest{
public:
    T* tpointer;
    int* intpointer;
public:
    templateTest(T* addr= NULL)
    {
        cout << "addr:" << addr << endl;
        intpointer = new int(1);
        tpointer = addr;
    }
};

int main()
{
    templateTest<int> t = new int;
    cout <<"t.tpointer: " << t.tpointer << ",intpointer: "
        << t.intpointer << endl;

    return 0;
}
