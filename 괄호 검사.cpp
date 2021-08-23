#include <iostream>
#define MAX_STACK_SIZE 20

using namespace std;

class ArrayStack {
private:
	int top; // 가장 최근 저장된 요소의 위치
	char data[MAX_STACK_SIZE];
public:
	ArrayStack() : top(-1) {}

	bool isEmpty() {
		if (top == -1)
			return true;
		else
			return false;
	}     // 스택이 비어있는지 확인

	bool isFull() {
		if (top - MAX_STACK_SIZE == -1)
			return true;
		else
			return false;
	}     // 스택이 꽉 차있는지 확인

	void push(char x) {
		if (!isFull())
			data[++top] = x;
		else {
			cout << "Error : overflow";
			exit(1);
		}
	}     // 스택에 빈자리가 있는지 확인 후 요소 대입

	char pop() {
		if (!isEmpty())
			return data[top--];
		else {
			cout << "Error : underflow";
			exit(1);
		}
	}     // 스택이 비어있는지 확인 후 마지막 요소 반환, 삭제

	char peek() {
		if (!isEmpty())
			return data[top];
		else {
			cout << "Error : underflow";
			exit(1);
		}
	}     // 스택이 비어있는지 확인 후 마지막 요소 반환

	void display() {
		cout << "[스택 항목의 수 = " << top + 1 << "] ==> ";
		for (int i = 0; i <= top; i++)
			cout << "<" << data[i] << ">";
		cout << "\n";
	}     // 스택 요소 출력
};

bool checkMatching(const char* filename) {
	FILE* fp = NULL;
	errno_t error;
	error = fopen_s(&fp, filename, "r");
	if (error != 0) {
		cout << "Error: 파일이 존재하지 않습니다.\n";
		exit(1);
	}

	ArrayStack stack;
	int nLine = 1;   // 검사 코드의 줄 수
	int nChar = 0;   // 검사 코드의 문자 수
	char ch;

	while ((ch = getc(fp)) != EOF) {
		nChar++;
		if (ch == '\n')
			nLine++;
		if (ch == '(' || ch == '{' || ch == '[') {
			stack.push(ch);
		}     // 왼쪽 괄호 저장
		else if (ch == ')' || ch == '}' || ch == ']') {
			char prev = stack.pop();
			if ((prev != '(' && ch == ')')
				|| (prev != '{' && ch == '}')
				|| (prev != '[' && ch == ']')) break;
		}     // 오른쪽 괄호를 만나면 쌍을 이루는지 검사
	}
	fclose(fp);

		if (!stack.isEmpty())
			cout << "Error : 문제발견(라인 수=" << nLine << ", 문자 수=" << nChar << "\n\n";
		else
			cout << " OK : 괄호닫기정상(라인 수=" << nLine << ", 문자 수=" << nChar << "\n\n";
		// 스택이 비어있지 않다면 조건 1에 어긋남

		return stack.isEmpty();
	}


int main() {
	checkMatching("테스트코드.txt");
	checkMatching("배열을 이용한 스택.cpp");

	return 0;
}