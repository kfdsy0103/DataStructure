// 입구 위치를 스택에 넣어 탐색 시작

// 스택에서 하나의 위치를 꺼내 현재 위치로 설정
// 만약 현재 위치가 출구면 성공
// 아니라면 상하좌우 위치를 살핀 후 스택에 삽입
// 반복

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
	Location2D entry(1,0);   // 시작 위치는 (1,0)
	stack<Location2D> st;
	st.push(entry);

	cout << "이동 경로 : ";
	while (!st.empty()) {
		Location2D here = st.top();
		st.pop();

		int r = here.row;
		int c = here.col;

		cout << '(' << r << ", " << c << ") ";
		if (map[r][c] == 'x') {
			cout << "\n탐색 성공!\n";
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
	cout << "\n탐색 실패...\n";
}