#include <iostream>
#include "CircularQueue.h"
#define MAX_SIZE 100

using namespace std;

void Error(const char* ErrorMessage) {
	cout << ErrorMessage << '\n';
	exit(1);
}

class CircularQueue {
protected:
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

class CircularDequeue : public CircularQueue {
public:
	CircularDequeue() {}
	void addRear(int val) { enqueue(val); }
	int deleteFront() { return dequeue(); }
	int getFront() { return peek(); }
	void addFront(int val) {
		if (isFull())
			Error("  Error: ���� ��ȭ �����Դϴ�.");
		data[front] = val;
		front = (front - 1 + MAX_SIZE) % MAX_SIZE;
	}
	int deleteRear() {
		if (isEmpty())
			Error("  Error: ���� ���� �����Դϴ�.");
		int ret = data[rear];
		rear = (rear - 1 + MAX_SIZE) % MAX_SIZE;
		return ret;
	}
	int getRear() {
		if (isEmpty())
			Error("  Error: ���� ��ȭ �����Դϴ�.");
		return data[rear];
	}
	void display() {
		cout << "���� ���� : ";
		int maxi = (front < rear) ? rear : rear + MAX_SIZE;
		for (int i = front + 1; i <= maxi; i++)
			cout << '[' << data[i % MAX_SIZE] << ']';
		cout << '\n';
	}
};

int main() {
	CircularDequeue deq;

	for (int i = 1; i < 10; i++) {
		if (i % 2 == 1) deq.addFront(i);
		else deq.addRear(i);
	}
	deq.display();
	deq.deleteFront();
	deq.deleteRear();
	deq.deleteFront();
	deq.display();

	return 0;
}