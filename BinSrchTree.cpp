#include <iostream>
#include "BinaryTree.h"

using namespace std;

class BinSrchTree : public BinaryTree {
public:
	BinSrchTree() {}
	~BinSrchTree() {}
	
	BinaryNode* search(int key) {
		BinaryNode* node = search(root, key);
		if (node != NULL)
			cout << "Ž�� ���� : Ű ���� " << key << "�� ��� = " << node << "\n";
		else
			cout << "Ž�� ���� : Ű ���� " << key << "�� ��� ����\n";
		return node;	
	}
	BinaryNode* search(BinaryNode* n, int key) {
		while (n != NULL) {
			if (key == n->getData())
				return n;
			else if (key < n->getData())
				n = n->getLeft();
			else
				n = n->getRight();
		}
		return NULL;
	}
	
	void insert(BinaryNode* n) {
		if (n == NULL) return;
		if (isEmpty()) root = n;
		else insert(root, n);
	}
	void insert(BinaryNode* r, BinaryNode* n) {
		while (r != NULL) {
			if (n->getData() == r->getData())
				return;
			else if (n->getData() < r->getData()) {
				if (r->getLeft() == NULL) {
					r->setLeft(n);
					return;
				}
				else {
					r = r->getLeft();
				}
			}
			else {
				if (r->getRight() == NULL) {
					r->setRight(n);
					return;
				}
				else {
					r = r->getRight();
				}
			}
		}
	}

	void remove(int key) {
		if (isEmpty()) return;

		BinaryNode* parent = NULL;
		BinaryNode* node = root;
		while (node != NULL && node->getData() != key) {
			parent = node;
			node = (key < node->getData()) ? node->getLeft() : node->getRight();
		}

		if (node == NULL)
			cout << " Error: key is not in the tree!\n";
		else
			remove(parent, node);
	}
	void remove(BinaryNode* parent, BinaryNode* node) {
		// 1. �����Ϸ��� ��尡 �ܸ������ ��� ( �˾ƾ� �ϴ� ��� : ������ ���, ������ ����� �θ� ) 
		if (node->isLeaf()) {
			if (parent == NULL)	 // �����Ǵ� ��尡 ��Ʈ����� ���
				root = NULL;
			else {
				if (parent->getLeft() == node)
					parent->setLeft(NULL);
				else
					parent->setRight(NULL);
			}
		}
		
		// 2. �����Ϸ��� ��尡 �ϳ��� ����Ʈ���� ���� ��� ( �˾ƾ� �ϴ� ��� : ������ ���, ������ ����� �θ�, ������ ����� ���� �ڽ� )
		else if (node->getLeft() == NULL || node->getRight() == NULL) {
			BinaryNode* child = (node->getLeft() != NULL) ? node->getLeft() : node->getRight();		// ������ �ڽ� ��� ��������
			if (node == root)	 // �����Ǵ� ��尡 ��Ʈ����� ���
				root = child;	 // �ڽ��� ��Ʈ�� ��
			else {
				if (parent->getLeft() == node)
					parent->setLeft(child);
				else
					parent->setRight(child);
			}
		}

		// 3. �����Ϸ��� ��尡 �� ���� ����Ʈ���� ���� ��� ( �˾ƾ� �ϴ� ��� : ������ ���, ������ ����� �θ�, �İ� ���, �İ� ����� �θ� )
		// �����ϴ� ���� ���� ���� ����� ��带 �����ͼ� ����
		// ����� ���� ���� ����Ʈ������ ���� ū �� or ������ ����Ʈ������ ���� ���� ��. �� �� ��� ���� �����ص� ��� ����.
		else {
			BinaryNode* succ = node;				// �İ� ��� : ������ ����Ʈ������ ���� ���� ��
			BinaryNode* succp = node->getRight();	// �İ� ����� �θ� ���
			while (succ->getLeft() != NULL) {
				succp = succ;
				succ = succ->getLeft();
			}

			// �İ� ����� �θ�� �İ� ����� ������ �ڽ��� ����
			if (succp->getLeft() == succ)
				succp->setLeft(succ->getRight());
			else
				succp->setRight(succ->getRight());	// �İ� ��尡 ���� ����� �ٷ� ������ �ڽ��� ���
			
			node->setData(succ->getData());			// ���� node�� �����ϴ� ���� �ƴ� �����͸� �����ϰ� �İ� ��带 �����ϴ� �����
			node = succ;							// ������ ��带 succ�� ����
		}	
		delete node;
	}
};

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