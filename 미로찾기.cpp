// �Ա� ��ġ�� ���ÿ� �־� Ž�� ����

// ���ÿ��� �ϳ��� ��ġ�� ���� ���� ��ġ�� ����
// ���� ���� ��ġ�� �ⱸ�� ����
// �ƴ϶�� �����¿� ��ġ�� ���� �� ���ÿ� ����
// �ݺ�

#include <iostream>
#include <stack>
#include "Location2D.h"

using namespace std;
const int MAZE_SIZE = 6;
char map[MAZE_SIZE][MAZE_SIZE] = {
	{'1', '1', '1', '1', '1', '1'},
	{'e', '0', '1', '0', '0', '1'},
	{'1', '0', '0', '0', '1', '1'},
	{'1', '0', '1', '0', '1', '1'},
	{'1', '0', '1', '0', '0', 'x'},
	{'1', '1', '1', '1', '1', '1'}
};

bool isValidLoc(int r, int c) {
	if (r < 0 || c < 0 || r >= MAZE_SIZE || c >= MAZE_SIZE) return false;
	else return (map[r][c] == '0' || map[r][c] == 'x');
}

int main() {
	Location2D entry(1,0);   // ���� ��ġ�� (1,0)
	stack<Location2D> st;
	st.push(entry);

	cout << "�̵� ��� : ";
	while (!st.empty()) {
		Location2D here = st.top();
		st.pop();

		int r = here.row;
		int c = here.col;

		cout << '(' << r << ", " << c << ") ";
		if (map[r][c] == 'x') {
			cout << "\nŽ�� ����!\n";
			return 0;
		}
		else {
			map[r][c] = '.';
			if (isValidLoc(r, c + 1)) st.push(Location2D(r, c + 1));
			if (isValidLoc(r, c - 1)) st.push(Location2D(r, c - 1));
			if (isValidLoc(r+1, c)) st.push(Location2D(r + 1, c));
			if (isValidLoc(r-1, c)) st.push(Location2D(r - 1, c));
		}
	}
	cout << "\nŽ�� ����...\n";
}