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
			cout << "탐색 성공 : 키 값이 " << key << "인 노드 = " << node << "\n";
		else
			cout << "탐색 실패 : 키 값이 " << key << "인 노드 없음\n";
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
		// 1. 삭제하려는 노드가 단말노드인 경우 ( 알아야 하는 노드 : 삭제할 노드, 삭제할 노드의 부모 ) 
		if (node->isLeaf()) {
			if (parent == NULL)	 // 삭제되는 노드가 루트노드인 경우
				root = NULL;
			else {
				if (parent->getLeft() == node)
					parent->setLeft(NULL);
				else
					parent->setRight(NULL);
			}
		}
		
		// 2. 삭제하려는 노드가 하나의 서브트리만 갖는 경우 ( 알아야 하는 노드 : 삭제할 노드, 삭제할 노드의 부모, 삭제할 노드의 유일 자식 )
		else if (node->getLeft() == NULL || node->getRight() == NULL) {
			BinaryNode* child = (node->getLeft() != NULL) ? node->getLeft() : node->getRight();		// 유일한 자식 노드 가져오기
			if (node == root)	 // 삭제되는 노드가 루트노드인 경우
				root = child;	 // 자식이 루트가 됨
			else {
				if (parent->getLeft() == node)
					parent->setLeft(child);
				else
					parent->setRight(child);
			}
		}

		// 3. 삭제하려는 노드가 두 개의 서브트리를 갖는 경우 ( 알아야 하는 노드 : 삭제할 노드, 삭제할 노드의 부모, 후계 노드, 후계 노드의 부모 )
		// 삭제하는 노드와 가장 값이 비슷한 노드를 가져와서 연결
		// 비슷한 값은 왼쪽 서브트리에서 가장 큰 값 or 오른쪽 서브트리에서 가장 작은 값. 둘 중 어느 것을 연결해도 상관 없다.
		else {
			BinaryNode* succ = node;				// 후계 노드 : 오른쪽 서브트리에서 가장 작은 값
			BinaryNode* succp = node->getRight();	// 후계 노드의 부모 노드
			while (succ->getLeft() != NULL) {
				succp = succ;
				succ = succ->getLeft();
			}

			// 후계 노드의 부모와 후계 노드의 오른쪽 자식을 연결
			if (succp->getLeft() == succ)
				succp->setLeft(succ->getRight());
			else
				succp->setRight(succ->getRight());	// 후계 노드가 삭제 노드의 바로 오른쪽 자식인 경우
			
			node->setData(succ->getData());			// 실제 node를 삭제하는 것이 아닌 데이터를 복사하고 후계 노드를 삭제하는 방법임
			node = succ;							// 삭제할 노드를 succ로 변경
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
