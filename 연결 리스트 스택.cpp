#include <iostream>

using namespace std;

class Student {
protected:
	int id;
	const char* name;
	const char* dept;
public:
	Student(int i = 0, const char* n = "", const char* d = "") : id(i), name(n), dept(d) {}
	void display() {
		cout << " 학번: " << id << " 성명: " << name << " 학과: " << dept << '\n';
	}
};

class Node : public Student{
private: 
	Node* link;
public:
	Node(int id, const char* name, const char* dept) : Student(id, name, dept), link(NULL) {}
	Node* getLink() { return link; }
	void setLink(Node* next) { link = next; }
};

class LinkedStack {
private:
	Node* top; // 헤드 포인터
public:
	LinkedStack() : top(NULL) {}
	bool isEmpty() { return top == NULL; }
	void push(Node* p) {
		if (isEmpty()) top = p;
		else{
			p->setLink(top);
			top = p;
		}
	}
	Node* pop() {
		if (isEmpty()) return NULL;
		else {
			Node* tmp = top;
			top = top->getLink();
			return tmp;
		}
	}
	Node* peek() { return top; }
	void display() {
		cout << "[LinkedStack]\n";
		for (Node* tmp = top; tmp != NULL; tmp = tmp->getLink()) 
			tmp->display();
		cout << '\n';
	}
	~LinkedStack() { while (!isEmpty()) delete pop(); }
};

int main() {
	LinkedStack stack;

	stack.push(new Node(2015130007, "홍길동", "컴퓨터공학과"));
	stack.push(new Node(2015130100, "이순신", "기계공학과"));
	stack.push(new Node(2015130135, "황희", "법학과"));
	stack.display();

	Node* node = stack.pop();
	cout << "[Pop항목]\n";
	node->display();
	cout << '\n';
	delete node; // 동적 할당된 메모리 해제
	stack.display();

	return 0;
}