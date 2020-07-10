#include <iostream>
#include <string>
#include "DStack.h"
#include "DArray.h"
#include "DVector.h"
#include "DSingleLinkList.h"
#include "DQueue.h"
#include "Config.h"
#include "DGenTree.h"
#include "DBinTree.h"
#include "DString.h"

using namespace DLib;
using namespace std;
int main()
{
    /*
    DGenTree<char> tree;
    DGenTreeNode<char>* node = DGenTreeNode<char>::newNode('A');
    DGenTreeNode<char>* temp=NULL;

    tree.insert(node);

    temp = tree.find(tree.root(), 'A');
    tree.insert(temp,'B');
    tree.insert(temp,'C');
    tree.insert(temp, 'D');

    temp = tree.find('B');
    tree.insert(temp, 'E');
    tree.insert(temp, 'F');

    temp = tree.find('E');
    tree.insert(temp, 'K');
    tree.insert(temp, 'L');

    temp = tree.find('C');
    tree.insert(temp, 'G');

    temp = tree.find('G');
    tree.insert(temp, 'N');

    temp = tree.find('D');
    tree.insert(temp, 'H');
    tree.insert(temp, 'I');
    tree.insert(temp, 'J');

    temp = tree.find('H');
    tree.insert(temp, 'M');

    cout << "count node: " << tree.count() << endl;
    cout << "height: " << tree.height() << endl;
    cout << "degree: " << tree.degree() << endl;

    tree.levelTravese();

    DVector<char> result = tree.getTravese();

    for(size_t i=0; i<result.length(); i++)
        cout << result[i] << ' ';
    cout << endl;


    DSharedPointer<DGenTree<char>> removed =  tree.removeNodeAndChild('H');

    const char* s ="KLFNMIJ";

    for(int i=0; i<7; i++){
        DGenTreeNode<char>* node =  tree.find(s[i]);
        while(node!=NULL){
            cout << node->nodeValue << " ";
            node = node->parent;
        }
        cout << endl ;
    }
    */


    return 0;
}

