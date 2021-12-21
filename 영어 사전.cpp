#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <conio.h>

#define MAX_WORD_SIZE 40
#define MAX_MEANING_SIZE 200

using namespace std;

class Record;
class BinaryNode;
class BinaryTree;
class BinSrchTree;
class Dictionary;

class Record {
private:
	char word[MAX_WORD_SIZE];
	char meaning[MAX_MEANING_SIZE];
public:
	Record(const char* w = "", const char* m = "") {
		set(w, m);
	}
	~Record() {}
	void set(const char* w, const char* m) {
		strcpy(word, w);
		strcpy(meaning, m);
	}
	int compare(Record* n) {
		return compare(n->word);
	}
	int compare(const char* w) {
		return strcmp(w, word);
	}
	int compareMeaning(const char* m) {
		return strcmp(meaning, m);
	}
	void display() {
		cout << " " << setw(12) << word << " : " << meaning << "\n";
	}
	void copy(Record* n) {
		set(n->word, n->meaning);
	}
};

class BinaryNode : public Record {
private:
	BinaryNode* left;
	BinaryNode* right;
public:
	BinaryNode(const char* w = "", const char* m = "") : Record(w, m), left(NULL), right(NULL) {}
	~BinaryNode() {}
	void setLeft(BinaryNode* l) {
		left = l;
	}
	void setRight(BinaryNode* r) {
		right = r;
	}
	BinaryNode* getLeft() {
		return left;
	}
	BinaryNode* getRight() {
		return right;
	}
	bool isLeaf() {
		return (left == NULL && right == NULL);
	}
};

class BinaryTree {
protected:
	BinaryNode* root;
public:
	BinaryTree() : root(NULL) {}
	~BinaryTree() {}
	bool isEmpty() {
		return root == NULL;
	}
	void inorder(BinaryNode* node) {
		if (node != NULL) {
			inorder(node->getLeft());
			node->display();
			inorder(node->getRight());
		}
	}
};

class BinSrchTree : public BinaryTree {
public:
	BinSrchTree() : BinaryTree() {}
	~BinSrchTree() {}
	BinaryNode* search(const char* key) {
		return search(root, key);
	}
	BinaryNode* search(BinaryNode* n, const char* key) {
		while (n != NULL) {
			if (n->compare(key) == 0)
				return n;
			else if (n->compare(key) < 0)
				n = n->getLeft();
			else
				n = n->getRight();
		}
		return NULL;
	}
	void insert(BinaryNode* n) {
		if (n == NULL) return;
		if (isEmpty()) root = n;
		else insert(root, n);
	}
	void insert(BinaryNode* r, BinaryNode* n) {
		while (r != NULL) {
			if (r->compare(n) == 0)
				return;
			else if (r->compare(n) < 0) {
				if (r->getLeft() == NULL) {
					r->setLeft(n);
					return;
				}
				else
					r = r->getLeft();
			}
			else {
				if (r->getRight() == NULL) {
					r->setRight(n);
					return;
				}
				else
					r = r->getRight();
			}
		}
	}
	void remove(const char* key) {
		if (isEmpty()) return;
		BinaryNode* parent = NULL;
		BinaryNode* node = root;
		while (node != NULL && node->compare(key) != 0) {
			parent = node;
			node = (node->compare(key) < 0) ? node->getLeft() : node->getRight();
		}
		if (node != NULL)
			remove(parent, node);
	}
	void remove(BinaryNode* parent, BinaryNode* n) {
		// 1. 단말노드
		if (n->isLeaf()) {
			if (parent == NULL)
				root = NULL;
			else {
				if (parent->getLeft() == n)
					parent->setLeft(NULL);
				else
					parent->setRight(NULL);
			}
		}

		// 2. 서브트리 한 쪽만 가짐
		else if (n->getLeft() == NULL || n->getRight() == NULL) {
			BinaryNode* child = (n->getLeft() != NULL) ? n->getLeft() : n->getRight();
			if (n == root) root = child;
			else {
				if (parent->getLeft() == n)
					parent->setLeft(child);
				else
					parent->setRight(child);
			}
		}

		// 3. 서브트리를 모두 가짐
		else {
			BinaryNode* succp = n;
			BinaryNode* succ = n->getRight();
			while (succ->getLeft() != NULL) {
				succp = succ;
				succ = succ->getLeft();
			}

			if (succp->getLeft() == succ)
				succp->setLeft(succ->getRight());
			else
				succp->setRight(succ->getRight());	// 삭제할 노드의 바로 오른쪽 자식

			n->copy(succ);
			n = succ;
		}
		delete n;
	}
};

class Dictionary : public BinSrchTree {
public:
	Dictionary() : BinSrchTree() {}
	~Dictionary() {}
	void printAllWords() {
		cout << "	>> 나의 단어장:\n";
		if (!isEmpty()) inorder(root);
	}
	void searchWord(const char* word) {
		BinaryNode* node = search(word);
		if (node != NULL) {
			cout << "	>> ";
			node->display();
		}
		else
			cout << "	 >> 등록되지 않은 단어: " << word << "\n";
	}
	void searchMeaning(const char* m) {
		cout << "엄준식\n";
		BinaryNode* node = (isEmpty()) ? NULL : searchByMeaning(root, m);
		if (node != NULL) {
			cout << "	>> ";
			node->display();
		}
		else
			cout << "	>> 등록되지 않은 의미: " << m << "\n";
	}
	BinaryNode* searchByMeaning(BinaryNode* n, const char* m) {
		// 순회 알고리즘으로 작성
		if (n == NULL || n->compareMeaning(m) == 0) return n;
		BinaryNode* theNode = searchByMeaning(n->getLeft(), m);
		if (theNode != NULL) return theNode;
		return searchByMeaning(n->getRight(), m);
	}
};

void help() {
	cout << "[사용법] i-추가 d-삭제 w-단어검색 m-의미검색 p-출력 q-종료 => ";
}

int main() {
	char command;
	char word[80];
	char meaning[200];
	Dictionary tree;
	do {
		help();
		command = _getche();
		cout << "\n";
		switch (command)
		{
		case 'i':
			cout << "  > 삽입 단어 : ";
			gets_s(word);
			cout << "  > 단어 설명 : ";
			gets_s(meaning);
			tree.insert(new BinaryNode(word, meaning));
			break;
		case 'd':
			cout << "  > 삭제 단어 : ";
			gets_s(word);
			tree.remove(word);
			break;
		case 'p':
			tree.printAllWords();
			cout << "\n";
			break;
		case 'w':
			cout << "  > 검색 단어 : ";
			gets_s(word);
			tree.searchWord(word);
			break;
		case 'm':
			cout << "  > 검색 의미 : ";
			gets_s(meaning);
			tree.searchMeaning(meaning);
			break;
		}
	} while (command != 'q');

	return 0;
}