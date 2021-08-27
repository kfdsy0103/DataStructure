#include <iostream>
#include <iomanip>

using namespace std;

int** alloc2DInt(int rows, int cols) {
	if (rows <= 0 || cols <= 0) return NULL;

	int** mat = new int* [rows];
	for (int i = 0; i < rows; i++)
		mat[i] = new int[cols];
	return mat;
}	// 1���� �迭�� ���� rows ũ���� ���� �Ҵ� > cols ũ���� 1���� �迭�� ������� ������ 2���� ����

void free2DInt(int** m, int r, int c) {
	if (m != NULL) {
		for (int i = 0; i < r; i++)
			delete[] m[i];
		delete[] m;
	}
}	// �Ҵ��� �������� ����

void set2DRandom(int** mat, int rows, int cols) {
	for (int i = 0; i < rows; i++)
		for (int k = 0; k < cols; k++)
			mat[i][k] = rand() % 100;
}	// ���� �� �Ҵ�

void print2DInt(int** mat, int rows, int cols) {
	cout << "���� �� = " << rows << ", ���� �� = " << cols << "\n";
	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < cols; k++)
			cout << setw(4) << mat[i][k];
		cout << '\n';
	}
}	// ��� �Լ�

int main() {
	int a, b;

	cout << "��� ���� ũ�⸦ �Է��ϼ���: ";
	cin >> a >> b;

	int** mat = alloc2DInt(a, b);
	set2DRandom(mat, a, b);
	print2DInt(mat, a, b);
	free2DInt(mat, a, b);
	
	return 0;
}