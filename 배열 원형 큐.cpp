/* 
선형 큐는 front와 rear값을 계속 증가시키기 때문에 메모리 낭비가 발생함

따라서 큐를 원형으로 생각해 rear값이 MAX_SIZE-1에 도달하면
다음 인덱스 값은 0이 되도록 하는 것이 원형 큐의 개념

원형 큐에서는 하나의 자리를 비워둬야 함
그 이유는 공백 상태와 포화 상태를 구분하기 위해서인데,
만약 비워두지 않는다면 rear == front 일때 공백인지 포화인지 구분할 수 없음
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
	bool isEmpty() { return front == rear; }   // front == rear 일 경우 empty
	bool isFull() { return (rear + 1) % MAX_SIZE == front; }   // front가 rear 앞에 있으면 full
	void enqueue(int val) {
		if (isFull())
			Error("  Error: 큐가 포화 상태입니다.");
		rear = (rear + 1) % MAX_SIZE;
		data[rear] = val;
	}
	int dequeue() {
		if (isEmpty())
			Error("  Error: 큐가 공백 상태입니다.");
		front = (front + 1) % MAX_SIZE;
		return data[front];
	}
	int peek() {
		if (isEmpty())
			Error("  Error: 큐가 공백 상태입니다.");
		return data[(front + 1) % MAX_SIZE];
	}
	void display() {
		cout << "큐 내용 : ";
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