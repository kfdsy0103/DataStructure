#include <iostream>
#define MAX_QUEUE_SIZE 100

using namespace std;

class CircularQueue;
class BinaryNode;
class BinaryTree;

class CircularQueue {
private:
	int front;
	int rear;
	BinaryNode* data[MAX_QUEUE_SIZE];
public:
	CircularQueue() : front(0), rear(0) {}
	bool isEmpty() {
		return front == rear;
	}
	bool isFull() {
		return (rear + 1) % MAX_QUEUE_SIZE == front;
	}
	void enqueue(BinaryNode* n) {
		if (isFull()) {
			cout << "Full";
			exit(1);
		}
		rear = (rear + 1) % MAX_QUEUE_SIZE;
		data[rear] = n;
	}
	BinaryNode* dequeue() {
		if (isEmpty()) {
			cout << "Empty";
			exit(1);
		}
		front = (front + 1) % MAX_QUEUE_SIZE;
		return data[front];
	}
};

class BinaryNode {
private:
	int data;
	BinaryNode* left;
	BinaryNode* right;
public:
	BinaryNode(int val, BinaryNode* l, BinaryNode* r) : data(val), left(l), right(r) {}
	~BinaryNode() {}
	void setData(int val) {
		data = val;
	}
	void setLeft(BinaryNode* l) {
		left = l;
	}
	void setRight(BinaryNode* r) {
		right = r;
	}
	int getData() {
		return data;
	}
	BinaryNode* getLeft() {
		return left;
	}
	BinaryNode* getRight() {
		return right;
	}
	bool isLeaf() {
		return (left == NULL && right == NULL);
	}
	void preorder() {
		cout << " [ " << (char)getData() << " ] ";
		if (left != NULL) left->preorder();
		if (right != NULL) right->preorder();
	}
	void inorder() {
		if (left != NULL) left->inorder();
		cout << " [ " << (char)getData() << " ] ";
		if (right != NULL) right->inorder();
	}
	void postorder() {
		if (left != NULL) left->postorder();
		if (right != NULL) right->postorder();
		cout << " [ " << (char)getData() << " ] ";
	}
};

class BinaryTree {
private:
	BinaryNode* root;
public:
	BinaryTree() : root(NULL) {}
	~BinaryTree() {}
	void setRoot(BinaryNode* node) {
		root = node;
	}
	BinaryNode* getRoot() {
		return root;
	}
	bool isEmpty() {
		return root == NULL;
	}
	void preorder() {
		cout << "\n     preorder :  ";
		if(!isEmpty()) root->preorder();
	}
	void inorder() {
		cout << "\n     inorder :   ";
		if (!isEmpty()) root->inorder();
	}
	void postorder() {
		cout << "\n    postorder :  ";
		if (!isEmpty()) root->preorder();
	}
	void levelorder() {
		cout << "\n    levelorder : ";
		if (!isEmpty()) {
			CircularQueue q;
			q.enqueue(root);
			while (!q.isEmpty()) {
				BinaryNode* n = q.dequeue();
				if (n != NULL) {
					cout << " [ " << (char)n->getData() << " ] ";
					q.enqueue(n->getLeft());
					q.enqueue(n->getRight());
				}
			}
		}
		cout << "\n";
	}
	int getCount() {
		return isEmpty() ? 0 : getCount(root);
	}
	int getCount(BinaryNode* node) {
		if (node == NULL)
			return 0;
		return 1 + getCount(node->getLeft()) + getCount(node->getRight());
	}
	int getLeafCount() {
		return isEmpty() ? 0 : getLeafCount(root);
	}
	int getLeafCount(BinaryNode* node) {
		if (node == NULL) return 0;
		if (node->isLeaf()) return 1;
		else return getLeafCount(node->getLeft()) + getLeafCount(node->getRight());
	}
	int getHeight() {
		return isEmpty() ? 0 : getHeight(root);
	}
	int getHeight(BinaryNode* node) {
		if (node == NULL) return 0;
		int hLeft = getHeight(node->getLeft());
		int hRight = getHeight(node->getRight());
		return hLeft > hRight ? hLeft + 1 : hRight + 1;
	}
};

int main() {
	BinaryTree tree;
	BinaryNode* d = new BinaryNode('D', NULL, NULL);
	BinaryNode* e = new BinaryNode('E', NULL, NULL);
	BinaryNode* b = new BinaryNode('B' , d, e);
	BinaryNode* f= new BinaryNode('F', NULL, NULL);
	BinaryNode* c = new BinaryNode('C', f, NULL);
	BinaryNode* a = new BinaryNode('A', b, c);
	tree.setRoot(a);

	tree.preorder();
	tree.inorder();
	tree.postorder();
	tree.levelorder();
	cout << "    Count : " << tree.getCount();
	cout << "\n    LeafCount : " << tree.getLeafCount();
	cout << "\n    Height : " << tree.getHeight();
	cout << "\n";
}