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
	}	// NULL이 아닌 노드만 후속 노드로 추가
	Node* removeNext() {
		Node* removed = link;
		if (removed != NULL)
			link = removed->link;
		return removed;
	}	// 삭제된 주소를 반환해 LinkedList에서 해제
};

class LinkedList {
private:
	Node org;	// 헤드 노드 (삽입과 삭제를 간단하게 할 목적으로 사용, 코드의 단순화)
public:
	LinkedList() : org(0) {}
	~LinkedList() { clear(); }
	void clear() { while (!isEmpty()) delete remove(0); }
	bool isEmpty() {
		return getHead() == NULL;
	}	// 공백 상태 확인
	void insert(int pos, Node* node) {
		Node* prev = getEntry(pos - 1);
		if (prev != NULL)
			prev->insertNext(node);
	}	// 삽입 연산
	Node* remove(int pos) {
		Node* prev = getEntry(pos - 1);
		return prev->removeNext();
	}	// 삭제 연산
	Node* getHead() {
		return org.getLink();
	}	// 헤드 포인터 반환
	Node* getEntry(int pos) {
		Node* n = &org;
		for (int i = -1; i < pos; i++) {
			if (n == NULL) break;
			n = n->getLink();
		}
		return n;
	}	// pos번째 노드 반환	
	Node* find(int item) {
		Node* tmp = getHead();
		while (tmp != NULL) {
			if (tmp->hasData(item)) return tmp;
		}
		return NULL;
	}	// 탐색 함수
	void replace(int pos, Node* node) {
		Node* prev = getEntry(pos-1);
		if (prev != NULL) {
			delete prev->removeNext();
			prev->insertNext(node);
		}
	}	// pos번째 노드 변경 함수
	int size() {
		int count = 0;		
		for(Node* tmp = getHead(); tmp != NULL; tmp = tmp->getLink())
			count++;
		return count;
	}	// size 반환 함수
	void display() {
		cout << "[전체 항목 수 = " << size() << "] : ";
		for (Node* tmp = getHead(); tmp != NULL; tmp = tmp->getLink())
			tmp->display();
		cout << '\n';
	}	// 출력 함수
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