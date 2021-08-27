#include <iostream>
#include <iomanip>

using namespace std;

int** alloc2DInt(int rows, int cols) {
	if (rows <= 0 || cols <= 0) return NULL;

	int** mat = new int* [rows];
	for (int i = 0; i < rows; i++)
		mat[i] = new int[cols];
	return mat;
}	// 1차원 배열을 담을 rows 크기의 공간 할당 > cols 크기의 1차원 배열을 순서대로 대입해 2차원 구현

void free2DInt(int** m, int r, int c) {
	if (m != NULL) {
		for (int i = 0; i < r; i++)
			delete[] m[i];
		delete[] m;
	}
}	// 할당의 역순으로 해제

void set2DRandom(int** mat, int rows, int cols) {
	for (int i = 0; i < rows; i++)
		for (int k = 0; k < cols; k++)
			mat[i][k] = rand() % 100;
}	// 랜덤 값 할당

void print2DInt(int** mat, int rows, int cols) {
	cout << "행의 수 = " << rows << ", 열의 수 = " << cols << "\n";
	for (int i = 0; i < rows; i++) {
		for (int k = 0; k < cols; k++)
			cout << setw(4) << mat[i][k];
		cout << '\n';
	}
}	// 출력 함수

int main() {
	int a, b;

	cout << "행과 열의 크기를 입력하세요: ";
	cin >> a >> b;

	int** mat = alloc2DInt(a, b);
	set2DRandom(mat, a, b);
	print2DInt(mat, a, b);
	free2DInt(mat, a, b);
	
	return 0;
}