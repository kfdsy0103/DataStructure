// 힙은 완전 이진 트리의 일종으로, 우선순위 큐를 구현하기 위해 만들어진 자료구조이다.
// 삽입과 삭제 모두 시간복잡도가 O(log2n)으로, 배열이나 링크드 리스트로 구현하는 것 보다 효율적이다.
// 부모노드 값 >= 자식노드 값인 최대 힙,
// 부모노드 값 <= 자식노드 값인 최소 힙이 있다.
// 이진 탐색 트리는 중복값을 허용하지 않았지만, 힙 트리는 중복값을 허용한다.
// 힙은 완전 이진 트리이므로 중간에 비어있는 요소가 없다. 따라서 힙을 저장하는 효과적인 자료구조는 배열이다.
/*	
	부모 인덱스 = 자식 인덱스 / 2, 
	왼쪽 자식	= 부모 * 2,
	오른쪽 자식 = 부모 * 2 + 1
*/
// 최대 힙 구현, 편의성을 위해 0번 인덱스는 사용하지 않고 노드 번호를 인덱스 그대로 사용한다.
//
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
	
	// 삽입 연산은 새로운 요소를 말단 위치에 놓고, 부모 값과 비교해 스왑해가는 방식으로 구현
	void insert(int key) {
		if (isFull()) return;
		int idx = ++size;

		while (idx != 1 && key > getParent(idx).getKey()) {	// 루트가 아니고 부모 노드보다 값이 크면
			node[idx] = getParent(idx);			// 부모를 끌어내리고
			idx /= 2;					// 한 레벨 위로 업데이트
		}
		node[idx].setKey(key);
	}

	// 삭제 연산은 말단 노드를 루트에 놓고, 왼쪽 자식과 오른쪽 자식을 비교해 더 큰 값과 스왑해가는 방식
	HeapNode remove() {
		HeapNode item = node[1];
		HeapNode last = node[size--];

		int parent = 1;		// 루트 부터 시작
		int child = 2;		// 더 큰 자식 노드를 찾기위한 변수
		while (child <= size) {
			if (child < size && getLeft(parent).getKey() < getRight(parent).getKey())
				child++;	// 더 큰 자식 노드 찾기
			
			if (last.getKey() >= node[child].getKey()) break;	// 말단 노드가 더 큰 자식 노드보다 크면. 이동 완료
			else {
				node[parent] = node[child];			// 아니라면 더 큰 자식을 올리고 
				parent = child;				
				child *= 2;					// parent와 child 업데이트
			}
		}
		node[parent] = last;	// 말단 노드가 들어갈 최종 위치인 parent에 말단 노드 삽입 
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
