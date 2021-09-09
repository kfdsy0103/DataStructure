#include <iostream>

using namespace std;

class Node {
private:
	int data;
	Node* link;
public:
	Node(int val) : data(val), link(NULL) {}
	Node* getLink() { return link; }
	void setLink(Node* next) { link = next; }
	void display() {
		cout << " <" << data << ">";
	}
	bool hasData(int val) {
		return data == val;
	}
	void insertNext(Node* node) {
		if (node != NULL) {
			node->link = link;
			link = node;
		}	
	}	// NULL�� �ƴ� ��常 �ļ� ���� �߰�
	Node* removeNext() {
		Node* removed = link;
		if (removed != NULL)
			link = removed->link;
		return removed;
	}	// ������ �ּҸ� ��ȯ�� LinkedList���� ����
};

class LinkedList {
private:
	Node org;	// ��� ��� (���԰� ������ �����ϰ� �� �������� ���, �ڵ��� �ܼ�ȭ)
public:
	LinkedList() : org(0) {}
	~LinkedList() { clear(); }
	void clear() { while (!isEmpty()) delete remove(0); }
	bool isEmpty() {
		return getHead() == NULL;
	}	// ���� ���� Ȯ��
	void insert(int pos, Node* node) {
		Node* prev = getEntry(pos - 1);
		if (prev != NULL)
			prev->insertNext(node);
	}	// ���� ����
	Node* remove(int pos) {
		Node* prev = getEntry(pos - 1);
		return prev->removeNext();
	}	// ���� ����
	Node* getHead() {
		return org.getLink();
	}	// ��� ������ ��ȯ
	Node* getEntry(int pos) {
		Node* n = &org;
		for (int i = -1; i < pos; i++) {
			if (n == NULL) break;
			n = n->getLink();
		}
		return n;
	}	// pos��° ��� ��ȯ	
	Node* find(int item) {
		Node* tmp = getHead();
		while (tmp != NULL) {
			if (tmp->hasData(item)) return tmp;
		}
		return NULL;
	}	// Ž�� �Լ�
	void replace(int pos, Node* node) {
		Node* prev = getEntry(pos-1);
		if (prev != NULL) {
			delete prev->removeNext();
			prev->insertNext(node);
		}
	}	// pos��° ��� ���� �Լ�
	int size() {
		int count = 0;		
		for(Node* tmp = getHead(); tmp != NULL; tmp = tmp->getLink())
			count++;
		return count;
	}	// size ��ȯ �Լ�
	void display() {
		cout << "[��ü �׸� �� = " << size() << "] : ";
		for (Node* tmp = getHead(); tmp != NULL; tmp = tmp->getLink())
			tmp->display();
		cout << '\n';
	}	// ��� �Լ�
};

int main() {
	LinkedList list;
	
	list.insert(0, new Node(10));
	list.insert(0, new Node(20));
	list.insert(1, new Node(30));
	list.display();
	list.replace(0, new Node(40));
	list.replace(1, new Node(50));
	list.display();

	return 0;
}