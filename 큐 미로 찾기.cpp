#include <iostream>
#include <queue>
#define MAZE_SIZE 6

using namespace std;

char Maze[MAZE_SIZE][MAZE_SIZE] = {
	{'1', '1', '1', '1', '1', '1'},
	{'e', '0', '1', '0', '0', '1'},
	{'1', '0', '0', '0', '1', '1'},
	{'1', '0', '1', '0', '1', '1'},
	{'1', '0', '1', '0', '0', 'x'},
	{'1', '1', '1', '1', '1', '1'}
};

struct Location2D {
	int row;
	int col;
	Location2D(int a, int b) : row(a), col(b) {}
};

bool isValidLoc(int row, int col) {
	if (col < 0 && col >= MAZE_SIZE && row < 0 && row >= MAZE_SIZE) return false;
	else return (Maze[row][col] == '0' || Maze[row][col] == 'x');
}

int main() {
	queue<Location2D> locQueue;
	locQueue.push(Location2D(1, 0));
	
	while (!locQueue.empty()) {
		Location2D a = locQueue.front();
		locQueue.pop();
		
		int r = a.row;
		int c = a.col;
		
		cout << '(' << r << ", " << c << ") ";

		if (Maze[r][c] == 'x') {
			cout << "\n미로 탐색 성공!";
			return 0;
		}
		else {
			Maze[r][c] = '.';
			if (isValidLoc(r - 1, c)) locQueue.push(Location2D(r - 1, c));
			if (isValidLoc(r + 1, c)) locQueue.push(Location2D(r + 1, c));
			if (isValidLoc(r, c - 1)) locQueue.push(Location2D(r, c - 1));
			if (isValidLoc(r, c + 1)) locQueue.push(Location2D(r, c + 1));
		}
	}
	cout << "\n미로 탐색 실패..";
}