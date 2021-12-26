// 입력 데이터의 문자 빈도수를 가지고 최소힙을 구성해 데이터를 효율적으로 압축하는 방법
// 아스키 코드는 모든 문자를 동일한 비트수로 표현하는데, 이것은 압축의 관점에서 적절하지 않다. (고정 길이 코드)
// 따라서 많이 사용되는 문자는 적은 비트수를 부여하고, 그렇지 않은 문자는 많은 비트 수를 부여해 압축 용량을 줄인다. (가변 길이 코드)
//
// ex) e : 127회, z : 1회 사용됐을 때, 
// (1) 모든 문자를 7비트로 표현		: 7bits * (127 + 1)			=  868 bits (고정 길이 코드)
// (2) e는 2비트, z는 20비트로 표현	: 2bits * 127 + 20bits * 1	=  266 bits (가변 길이 코드)
//
// (2)와 같이 압축된 가변 길이 코드를 해석하기 위해서는 각각의 문자가 어떤 비트 코드로 표현되는지를 알려주는 테이블이 필요하다.
// 가변 길이 코드의 해석 방법은, 코드를 앞에서부터 읽으면서 테이블에 일치하는 코드가 있으면 그것을 한 문자로 처리하고, 이 과정을 반복하는 것이다.
// 이러한 해석 과정이 가능하려면 테이블을 구성할 때, 어떤 코드가 다른 코드의 접두어가 되어선 안된다.
// 따라서 위 조건을 만족하는 특수한 코드를 만들기 위해 허프만 알고리즘을 사용하고, 그 코드를 허프만 코드라고 한다.

#include <iostream>
#include "MinHeap.h"

using namespace std;

void makeTree(int freq[], int n) {
	MinHeap heap;
	for (int i = 0; i < n; i++)
		heap.insert(freq[i]);
	
	// 전체 문자 수가 n개면, 최소 노드 2개를 뽑는 과정은 n-1번 이루어짐.
	for (int i = 1; i < n; i++) {
		const HeapNode& e1 = heap.remove();
		const HeapNode& e2 = heap.remove();
		heap.insert(e1.getKey() + e2.getKey());
		cout << " (" << e1.getKey() << " + " << e2.getKey() << ")\n";
	}
}

int main() {
	const int SIZE = 5;
	int freq[SIZE] = { 15, 12, 8, 6, 4 };
	makeTree(freq, SIZE);
}