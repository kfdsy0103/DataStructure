#include <iostream>
#include "BinSrchTree.h"

using namespace std;

int main() {
	BinSrchTree tree;
	
	tree.insert( new BinaryNode(35) );
	tree.insert( new BinaryNode(18) );
	tree.insert( new BinaryNode( 7) );
	tree.insert( new BinaryNode(26) );
	tree.insert( new BinaryNode(12) );
	tree.insert( new BinaryNode( 3) );
	tree.insert( new BinaryNode(68) );
	tree.insert( new BinaryNode(22) );
	tree.insert( new BinaryNode(30) );
	tree.insert( new BinaryNode(99) );

	cout << " 노드의 개수 = " << tree.getCount();
	cout << "\n 단말의 개수 = " << tree.getLeafCount();
	cout << "\n 트리의 높이 = " << tree.getHeight();
	
	tree.preorder();
	tree.inorder();
	tree.postorder();
	tree.levelorder();
	
	tree.search(26);
	tree.search(25);

	cout << "  삭제 : case 1 ==> 노드  3 삭제";
	tree.remove( 3);
	tree.levelorder();
	cout << "  삭제 : case 2 ==> 노드 68 삭제";
	tree.remove(68);
	tree.levelorder();
	cout << "  삭제 : case 3 ==> 노드 18 삭제";
	tree.remove(18);
	tree.levelorder();
	cout << "  삭제 : case 4 ==> 노드 35 삭제";
	tree.remove(35);
	tree.levelorder();

	cout << " 노드의 개수 = " << tree.getCount();
	cout << "\n 단말의 개수 = " << tree.getLeafCount();
	cout << "\n 트리의 높이 = " << tree.getHeight();

	return 0;
}