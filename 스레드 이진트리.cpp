#include <iostream>

using namespace std;

class ThreadedBinNode {
private:
	int data;
	ThreadedBinNode* left;
	ThreadedBinNode* right;
public:
	bool bThread;
	ThreadedBinNode(int val, ThreadedBinNode* l, ThreadedBinNode* r, bool bTh) : data(val), left(l), right(r), bThread(bTh) {}
	~ThreadedBinNode() {}
	int getData() {
		return data;
	}
	void setRight(ThreadedBinNode* r) {
		right = r;
	}
	ThreadedBinNode* getLeft() {
		return left;
	}
	ThreadedBinNode* getRight() {
		return right;
	}
};

class ThreadedBinTree {
private:
	ThreadedBinNode* root;
public:
	ThreadedBinTree() : root(NULL) {}
	~ThreadedBinTree() {}
	void setRoot(ThreadedBinNode* node) {
		root = node;
	}
	bool isEmpty() {
		return root == NULL;
	}

	void threadedInorder() {
		if (!isEmpty()) {
			cout << "  스레드 이진트리: ";
			ThreadedBinNode* p = root;
			while (p->getLeft())
				p = p->getLeft();
			
			do {
				cout << (char)p->getData() << " ";
				p = findSuccessor(p);
			} while (p);
		}
	}

	ThreadedBinNode* findSuccessor(ThreadedBinNode* p) {
		ThreadedBinNode* q = p->getRight();
		
		if (q == NULL || p->bThread)
			return q;
		
		while (q->getLeft())
			q = q->getLeft();
		return q;
	}
};

int main() {
	ThreadedBinTree tree;
	
	ThreadedBinNode* n1 = new ThreadedBinNode('A', NULL, NULL, true);
	ThreadedBinNode* n2 = new ThreadedBinNode('B', NULL, NULL, true);
	ThreadedBinNode* n3 = new ThreadedBinNode('C', n1, n2, false);
	ThreadedBinNode* n4 = new ThreadedBinNode('D', NULL, NULL, true);
	ThreadedBinNode* n5 = new ThreadedBinNode('E', NULL, NULL, false);
	ThreadedBinNode* n6 = new ThreadedBinNode('F', n4, n5, false);
	ThreadedBinNode* n7 = new ThreadedBinNode('G', n3, n6, false);
	tree.setRoot(n7);

	n1->setRight(n3);
	n2->setRight(n7);
	n4->setRight(n6);
	
	tree.threadedInorder();
}