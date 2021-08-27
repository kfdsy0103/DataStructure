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
		cout << " �й�: " << id << " ����: " << name << " �а�: " << dept << '\n';
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
	Node* top; // ��� ������
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

	stack.push(new Node(2015130007, "ȫ�浿", "��ǻ�Ͱ��а�"));
	stack.push(new Node(2015130100, "�̼���", "�����а�"));
	stack.push(new Node(2015130135, "Ȳ��", "���а�"));
	stack.display();

	Node* node = stack.pop();
	cout << "[Pop�׸�]\n";
	node->display();
	cout << '\n';
	delete node; // ���� �Ҵ�� �޸� ����
	stack.display();

	return 0;
}