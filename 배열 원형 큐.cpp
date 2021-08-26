/* 
���� ť�� front�� rear���� ��� ������Ű�� ������ �޸� ���� �߻���

���� ť�� �������� ������ rear���� MAX_SIZE-1�� �����ϸ�
���� �ε��� ���� 0�� �ǵ��� �ϴ� ���� ���� ť�� ����

���� ť������ �ϳ��� �ڸ��� ����־� ��
�� ������ ���� ���¿� ��ȭ ���¸� �����ϱ� ���ؼ��ε�,
���� ������� �ʴ´ٸ� rear == front �϶� �������� ��ȭ���� ������ �� ����
*/

#include <iostream>
#define MAX_SIZE 100

using namespace std;

void Error(const char* ErrorMessage) {
	cout << ErrorMessage << '\n';
	exit(1);
}

class CircularQueue {
protected :
	int front;
	int rear;
	int data[MAX_SIZE];
public:
	CircularQueue() : front(0), rear(0) {}
	bool isEmpty() { return front == rear; }   // front == rear �� ��� empty
	bool isFull() { return (rear + 1) % MAX_SIZE == front; }   // front�� rear �տ� ������ full
	void enqueue(int val) {
		if (isFull())
			Error("  Error: ť�� ��ȭ �����Դϴ�.");
		rear = (rear + 1) % MAX_SIZE;
		data[rear] = val;
	}
	int dequeue() {
		if (isEmpty())
			Error("  Error: ť�� ���� �����Դϴ�.");
		front = (front + 1) % MAX_SIZE;
		return data[front];
	}
	int peek() {
		if (isEmpty())
			Error("  Error: ť�� ���� �����Դϴ�.");
		return data[(front + 1) % MAX_SIZE];
	}
	void display() {
		cout << "ť ���� : ";
		int maxi = (front < rear) ? rear : rear + MAX_SIZE;
		for (int i = front + 1; i <= maxi; i++)
			cout << '[' << data[i % MAX_SIZE] << ']';
		cout << '\n';
	}
};

int main() {
	CircularQueue que;

	for (int i = 1; i < 10; i++)
		que.enqueue(i);

	que.display();
	que.dequeue();
	que.dequeue();
	que.dequeue();
	que.display();

	return 0;
}