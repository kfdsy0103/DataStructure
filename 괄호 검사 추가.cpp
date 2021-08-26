#include <iostream>
#define MAX_STACK_SIZE 20

using namespace std;

class ArrayStack {
private:
	int top; // ���� �ֱ� ����� ����� ��ġ
	char data[MAX_STACK_SIZE];
public:
	ArrayStack() : top(-1) {}

	bool isEmpty() {
		if (top == -1)
			return true;
		else
			return false;
	}     // ������ ����ִ��� Ȯ��

	bool isFull() {
		if (top - MAX_STACK_SIZE == -1)
			return true;
		else
			return false;
	}     // ������ �� ���ִ��� Ȯ��

	void push(char x) {
		if (!isFull())
			data[++top] = x;
		else {
			cout << "Error : overflow";
			exit(1);
		}
	}     // ���ÿ� ���ڸ��� �ִ��� Ȯ�� �� ��� ����

	char pop() {
		if (!isEmpty())
			return data[top--];
		else {
			cout << "Error : underflow";
			exit(1);
		}
	}     // ������ ����ִ��� Ȯ�� �� ������ ��� ��ȯ, ����

	char peek() {
		if (!isEmpty())
			return data[top];
		else {
			cout << "Error : underflow";
			exit(1);
		}
	}     // ������ ����ִ��� Ȯ�� �� ������ ��� ��ȯ

	void display() {
		cout << "[���� �׸��� �� = " << top + 1 << "] ==> ";
		for (int i = 0; i <= top; i++)
			cout << "<" << data[i] << ">";
		cout << "\n";
	}     // ���� ��� ���
};

void Error(const char* cause) {
	cout << "Error: " << cause << "\n";
	exit(1);
}

bool checkMatching(const char* filename) {
	FILE* fp = NULL;
	errno_t error;
	error = fopen_s(&fp, filename, "r");
	if (error != 0)
		Error("������ �������� �ʽ��ϴ�.");

	ArrayStack stack;
	int nLine = 1;   // �˻� �ڵ��� �� ��
	int nChar = 0;   // �˻� �ڵ��� ���� ��
	char ch;
	bool small = false, big = false;   // ���� ����ǥ, ū����ǥ
	bool note = false, notes = false;   // ���� �ּ�, ������ �ּ�

	while ((ch = getc(fp)) != EOF) {
		nChar++;
		if (ch == '\n')
			nLine++;

		if (ch == '\n' && note == true)
			note = false;

		if (ch == '*' && notes == true) {
			ch = getc(fp);
			nChar++;
			if (ch == '/')
				notes = false;
			else
				Error("�ּ��� ������ �ʾҽ��ϴ�.");
		}

		if (ch == '/') {
			ch = getc(fp);
			nChar++;
			if (ch == '/' && note == false)
				note = true;
			else if (ch == '*' && notes == false)
				notes = true;
		}		
		
		if (ch == '\'' && small == false)
			small = true; 
		else if (ch == '\'' && small == true)
			small = false; 

		if (ch == '\"' && big == false)
			big = true; 
		else if (ch == '\"' && big == true)
			big = false; 

		if ((ch == '(' || ch == '{' || ch == '[') && note == false && notes == false && small == false && big == false) {
			stack.push(ch);
		}     // ���� ��ȣ ����
		else if (ch == ')' || ch == '}' || ch == ']') {
			char prev = stack.pop();
			if ((prev != '(' && ch == ')')
				|| (prev != '{' && ch == '}')
				|| (prev != '[' && ch == ']')) break;
		}     // ������ ��ȣ�� ������ ���� �̷���� �˻�
	}
	fclose(fp);

	if (!stack.isEmpty()) 
		Error("�����߻�");		
	else
		cout << "��ȣ�ݱ⼺��";

	return stack.isEmpty();
}

int main() {
	checkMatching("�׽�Ʈ�ڵ�.txt");

	return 0;
}