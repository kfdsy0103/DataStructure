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

bool checkMatching(const char* filename) {
	FILE* fp = NULL;
	errno_t error;
	error = fopen_s(&fp, filename, "r");
	if (error != 0) {
		cout << "Error: ������ �������� �ʽ��ϴ�.\n";
		exit(1);
	}

	ArrayStack stack;
	int nLine = 1;   // �˻� �ڵ��� �� ��
	int nChar = 0;   // �˻� �ڵ��� ���� ��
	char ch;

	while ((ch = getc(fp)) != EOF) {
		nChar++;
		if (ch == '\n')
			nLine++;
		if (ch == '(' || ch == '{' || ch == '[') {
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
			cout << "Error : �����߰�(���� ��=" << nLine << ", ���� ��=" << nChar << "\n\n";
		else
			cout << " OK : ��ȣ�ݱ�����(���� ��=" << nLine << ", ���� ��=" << nChar << "\n\n";
		// ������ ������� �ʴٸ� ���� 1�� ��߳�

		return stack.isEmpty();
	}


int main() {
	checkMatching("�׽�Ʈ�ڵ�.txt");
	checkMatching("�迭�� �̿��� ����.cpp");

	return 0;
}