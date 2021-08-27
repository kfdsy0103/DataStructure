/*
큐의 삽입 연산 - 1. 공백 상태인 경우 2. 아닌 경우
1 : front와 rear 모두 새로운 노드를 가리키도록 한다.
2 : rear가 가리키던 노드와 rear 모두 새로운 노드를 가리키도록 한다.

큐의 삭제 연산 - 1. 노드가 하나인 경우 2. 여러 개인 경우
1 : front가 NULL이 되므로 rear도 NULL로 만들어준다.
2 : 임시 포인터를 이용해 front가 다음 노드를 가리키도록 한 후 출력
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
	Node* front;	// 전단
	Node* rear;		// 후단
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
		cout << "[큐 내용] : ";
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