/*
ť�� ���� ���� - 1. ���� ������ ��� 2. �ƴ� ���
1 : front�� rear ��� ���ο� ��带 ����Ű���� �Ѵ�.
2 : rear�� ����Ű�� ���� rear ��� ���ο� ��带 ����Ű���� �Ѵ�.

ť�� ���� ���� - 1. ��尡 �ϳ��� ��� 2. ���� ���� ���
1 : front�� NULL�� �ǹǷ� rear�� NULL�� ������ش�.
2 : �ӽ� �����͸� �̿��� front�� ���� ��带 ����Ű���� �� �� ���
*/
#include <iostream>

using namespace std;

class Node {
private:
	Node* link;
	int data;
public:
	Node(int val = 0) : data(val) {}
	Node* getLink() { return link; }
	void setLink(Node* next) { link = next; }
	void display() { cout << "<" << data << "> "; }
};

class LinkedQueue {
private:
	Node* front;	// ����
	Node* rear;		// �Ĵ�
public:
	LinkedQueue() : front(NULL), rear(NULL) {}
	bool isEmpty() { return front == NULL; }
	void enqueue(Node* item) {
		if (isEmpty()) {
			front = item;
			rear = item;
		}
		else {
			rear->setLink(item);
			rear = item;
		}
	}
	Node* dequeue() {
		if (isEmpty()) return NULL;
		Node* tmp = front;
		front = front->getLink();
		if (front == NULL)
			rear = NULL;
		return tmp;
	}
	Node* peek() { return front; }
	void display() {
		cout << "[ť ����] : ";
		for (Node* tmp = front; tmp != NULL; tmp = tmp->getLink())
			tmp->display();
		cout << '\n';
	}
	~LinkedQueue() {
		while (!isEmpty()) delete dequeue();
	}
};

int main() {
	LinkedQueue que;
	for (int i = 1; i < 10; i++)
		que.enqueue(new Node(i));
	que.display();
	delete que.dequeue();
	delete que.dequeue();
	delete que.dequeue();
	que.display();
}