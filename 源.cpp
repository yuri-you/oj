#include<iostream>
using std::cin;
using std::cout;
int n, m;
class linetree {
	struct node {
		int number, leftrange, rightrange, mid;
		node* lchild, * rchild;
		node(int left, int right) {
			leftrange = left;
			rightrange = right;
			number = right - left + 1;
			mid = (left + right) >> 1;
			if (left == right) {
				lchild = rchild = 0;
			}
			else {
				lchild = new node(left, mid);
				rchild = new node(mid + 1, right);
			}
		}
		~node() {
			if (lchild) {
				delete lchild, rchild;
			}
		}
	};
	node* root;
	int numberofrange(int left, int right, node* ptr) {
		if (ptr->leftrange == left && ptr->rightrange == right)return ptr->number;
		else {
			if (right <= ptr->mid)return numberofrange(left, right, ptr->lchild);
			else {
				if (left > ptr->mid)return numberofrange(left, right, ptr->rchild);
				else return numberofrange(left, ptr->mid, ptr->lchild) + numberofrange(ptr->mid + 1, right, ptr->rchild);
			}
		}
	}
	void deletenode(int position, node* ptr) {
		--ptr->number;
		if (ptr->leftrange == ptr->rightrange)return;
		if (ptr->mid < position)deletenode(position, ptr->rchild);
		else deletenode(position, ptr->lchild);
	}
	int findnumber(int now, int direction, node* ptr) {

	}
public:
	linetree(int i) {
		root = new node(1, i);
	}
	int numberofrange(int left, int right) {
		if (left > right)return 0;
		else return numberofrange(left, right, root);
	}
	void deletenode(int position) { return deletenode(position, root); }
	int remain() {
		node* tmp = root;
		while (tmp->lchild || tmp->rchild) {
			if (tmp->lchild && tmp->lchild->number)tmp = tmp->lchild;
			else tmp = tmp->rchild;
		}
		return tmp->leftrange;
	}
	int lastnumber() {
		node* tmp = root;
		while (tmp->leftrange != tmp->rightrange) {
			if (tmp->rchild->number)tmp = tmp->rchild;
			else tmp = tmp->lchild;
		}
		return tmp->leftrange;
	}
	int firstnumber() {
		node* tmp = root;
		while (tmp->leftrange != tmp->rightrange) {
			if (tmp->lchild->number)tmp = tmp->lchild;
			else tmp = tmp->rchild;
		}
		return tmp->leftrange;
	}
	int findnumber(int now, bool direction, int length) {
		int number;
		node* ptr = root;
		if (direction) {//true Íùºó
			do {
				if (ptr->leftrange == ptr->rightrange)return ptr->leftrange;
				number = numberofrange(now + 1, ptr->lchild->rightrange);
				if (number < length)ptr = ptr->rchild;
				else ptr = ptr->lchild;
			} while (true);
		}
		else {
			do {
				if (ptr->leftrange == ptr->rightrange)return ptr->leftrange;
				number = numberofrange(ptr->rchild->leftrange, now - 1);
				if (number < length)ptr = ptr->lchild;
				else ptr = ptr->rchild;
			} while (true);
		}
	}
	~linetree() { delete root; }
};
linetree* data1;
int main() {
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	if (n == 1)return 1;
	if (n == 2)return (m) ? 2 : 1;
	data1 = new linetree(n);
	int now = 0, step, record, size = n;
	bool direction = true, tmpsignal = false;//true Íùºó£¬falseÍùÇ°
	for (int j = 0; j < n - 1; ++j) {
		step = (m - 1) % (2 * size - 2) + 1;
		do {
			if (direction) {
				record = data1->numberofrange(now + 1, n);
				if (record < step) {
					step -= record;
					direction = false;
					now = data1->lastnumber();
				}
				else {
					if (record == step) {
						direction = false;
						now = data1->lastnumber();
						tmpsignal = true;
					}
					break;
				}
			}
			else {
				record = data1->numberofrange(1, now - 1);
				if (record < step) {
					step -= record;
					direction = true;
					now = data1->firstnumber();
				}
				else {
					if (record == step) {
						direction = true;
						now = data1->firstnumber();
						tmpsignal = true;
					}
					break;
				}
			}
		} while (true);
		if (tmpsignal) {
			tmpsignal = false;
		}
		else now = data1->findnumber(now, direction, step);
		--size;
		data1->deletenode(now);
		//cout << now << '\n';
	}
	cout << data1->remain();
	return 0;
}