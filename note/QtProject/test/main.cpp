#include <iostream>
#include "header.h"

using namespace std;
using namespace DLib;

int main()
{
    DSharedPointer<int> p = new int(999);
    DSharedPointer<int> p1 = p;

    return 0;

}

