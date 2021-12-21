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

	cout << " ����� ���� = " << tree.getCount();
	cout << "\n �ܸ��� ���� = " << tree.getLeafCount();
	cout << "\n Ʈ���� ���� = " << tree.getHeight();
	
	tree.preorder();
	tree.inorder();
	tree.postorder();
	tree.levelorder();
	
	tree.search(26);
	tree.search(25);

	cout << "  ���� : case 1 ==> ���  3 ����";
	tree.remove( 3);
	tree.levelorder();
	cout << "  ���� : case 2 ==> ��� 68 ����";
	tree.remove(68);
	tree.levelorder();
	cout << "  ���� : case 3 ==> ��� 18 ����";
	tree.remove(18);
	tree.levelorder();
	cout << "  ���� : case 4 ==> ��� 35 ����";
	tree.remove(35);
	tree.levelorder();

	cout << " ����� ���� = " << tree.getCount();
	cout << "\n �ܸ��� ���� = " << tree.getLeafCount();
	cout << "\n Ʈ���� ���� = " << tree.getHeight();

	return 0;
}