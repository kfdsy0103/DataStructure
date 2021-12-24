// ���� ���� ���� Ʈ���� ��������, �켱���� ť�� �����ϱ� ���� ������� �ڷᱸ���̴�.
// ���԰� ���� ��� �ð����⵵�� O(log2n)����, �迭�̳� ��ũ�� ����Ʈ�� �����ϴ� �� ���� ȿ�����̴�.
// �θ��� �� >= �ڽĳ�� ���� �ִ� ��,
// �θ��� �� <= �ڽĳ�� ���� �ּ� ���� �ִ�.
// ���� Ž�� Ʈ���� �ߺ����� ������� �ʾ�����, �� Ʈ���� �ߺ����� ����Ѵ�.
// ���� ���� ���� Ʈ���̹Ƿ� �߰��� ����ִ� ��Ұ� ����. ���� ���� �����ϴ� ȿ������ �ڷᱸ���� �迭�̴�.
/*	
	�θ� �ε��� = �ڽ� �ε��� / 2, 
	���� �ڽ�	= �θ� * 2,
	������ �ڽ� = �θ� * 2 + 1
*/
// �ִ� �� ����, ���Ǽ��� ���� 0�� �ε����� ������� �ʰ� ��� ��ȣ�� �ε��� �״�� ����Ѵ�.
#include <iostream>
#include <iomanip>

#define MAX_ELEMENT 200

using namespace std;

class HeapNode {
private:
	int key;
public:
	HeapNode() {}
	HeapNode(int k) : key(k) {}
	~HeapNode() {}
	void setKey(int k) { key = k; }
	int getKey() { return key; }
	void display() { cout << setw(4) << key; }
};

class MaxHeap {
private:
	HeapNode node[MAX_ELEMENT];
	int size;
public:
	MaxHeap() : size(0) {}
	~MaxHeap() {}
	bool isEmpty() { return size == 0; }
	bool isFull() { return size == MAX_ELEMENT - 1; }

	HeapNode& getParent(int i) { return node[i / 2]; }
	HeapNode& getLeft(int i) { return node[i * 2]; }
	HeapNode& getRight(int i) { return node[i * 2 + 1]; }
	
	// ���� ������ ���ο� ��Ҹ� ���� ��ġ�� ����, �θ� ���� ���� �����ذ��� ������� ����
	void insert(int key) {
		if (isFull()) return;
		int idx = ++size;

		while (idx != 1 && key > getParent(idx).getKey()) {	// ��Ʈ�� �ƴϰ� �θ� ��庸�� ���� ũ��
			node[idx] = getParent(idx);						// �θ� �������
			idx /= 2;										// �� ���� ���� ������Ʈ
		}
		node[idx].setKey(key);
	}

	// ���� ������ ���� ��带 ��Ʈ�� ����, ���� �ڽİ� ������ �ڽ��� ���� �� ū ���� �����ذ��� ���
	HeapNode remove() {
		HeapNode item = node[1];
		HeapNode last = node[size--];

		int parent = 1;		// ��Ʈ ���� ����
		int child = 2;		// �� ū �ڽ� ��带 ã������ ����
		while (child <= size) {
			if (child < size && getLeft(parent).getKey() < getRight(parent).getKey())
				child++;	// �� ū �ڽ� ��� ã��
			
			if (last.getKey() >= node[child].getKey()) break; // ���� ��尡 �� ū �ڽ� ��庸�� ũ��. �̵� �Ϸ�
			else {
				node[parent] = node[child];	// �ƴ϶�� �� ū �ڽ��� �ø��� 
				parent = child;				
				child *= 2;					// parent�� child ������Ʈ
			}
		}
		node[parent] = last;	// ���� ��尡 �� ���� ��ġ�� parent�� ���� ��� ���� 
		return item;
	}
	HeapNode find() {
		return node[1];
	}
	void display() {
		for (int i = 1, level = 1; i <= size; i++) {
			if (i == level) {
				cout << "\n";
				level *= 2;
			}
			node[i].display();
		}
		cout << "\n----------------------------";
	}
};

int main() {
	MaxHeap heap;
	
	heap.insert(10);
	heap.insert( 5);
	heap.insert(30);
	heap.insert( 8);
	heap.insert( 9);
	heap.insert( 3);
	heap.insert( 7);
	heap.display();

	heap.remove();
	heap.display();
	heap.remove();
	heap.display();
	cout << "\n";

	return 0;
}