// 가로, 세로 인접한 화소끼리 같은 색으로 칠하기
#include <iostream>
#define ROW 10
#define COL 10
using namespace std;

int img[ROW][COL] = {
	{0,0,0,0,0,0,0,0,0,0},
	{0,9,9,9,0,0,0,0,0,0},
	{0,9,9,9,0,0,0,0,0,0},
	{0,9,9,9,0,0,0,9,0,0},
	{0,0,0,0,0,0,9,9,9,0},
	{0,0,0,0,0,0,0,9,0,0},
	{0,0,0,9,9,0,0,0,0,0},
	{0,0,9,9,9,9,0,0,0,0},
	{0,0,9,9,9,9,0,0,0,0},
	{0,0,0,9,9,0,0,0,0,0},
};

void labelComponent(int x, int y, int label) {
	if (x < 0 || y < 0 || x >= ROW || y >= COL)
		return;
	
	if (img[y][x] == 9) {
		img[y][x] = label;
		labelComponent(x, y + 1, label);
		labelComponent(x, y - 1, label);
		labelComponent(x + 1, y, label);
		labelComponent(x - 1, y, label);
	}
}

void blobColoring() {
	int label = 1;

	for (int y = 0; y < COL; y++)
	for (int x = 0; x < ROW; x++)
		if (img[y][x] == 9)
			labelComponent(x, y, label++);	
}

void printImg(const char* msg) {
	cout << msg << "\n";
	for (int y = 0; y < ROW; y++) {
		for (int x = 0; x < COL; x++) {
			if (img[y][x] == 0)
				cout << '.';
			else
				cout << img[y][x];
		}
		cout << "\n";
	}
	cout << "\n";
}

int main() {
	printImg("<Original image>");
	blobColoring();
	printImg("<Labelled image>");

	return 0;
}