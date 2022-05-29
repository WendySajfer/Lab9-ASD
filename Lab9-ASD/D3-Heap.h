#ifndef _D3_Heap_H_
#define _D3_Heap_H_
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class D3_Heap {
private:
	int* Root = new int[0];
	int Size = 0;
	void Overwrite_1(int key_) {
		int* Root_ = new int[Size + 1];
		for (int i = 0; i < Size; i++) {
			Root_[i] = Root[i];
		}
		Root_[Size] = key_;
		Root = Root_;
		Size = Size + 1;
	}
	void Overwrite_2() {
		int* Root_ = new int[Size - 1];
		for (int i = 0; i < Size - 1; i++) {
			Root_[i] = Root[i];
		}
		Root = Root_;
		Size = Size - 1;
	}
	int search_index(int key_) {
		for (int i = 0; i < Size; i++) {
			if (Root[i] == key_) return i;
		}
		return -1;
	}
	int pred(int index_) {
		if (index_ > 0 && index_ < Size) return ((index_ - 1) / 3);
		else return -1;
	}
	int minchild(int index_) {
		if (index_ * 3 + 1 < Size && index_ >= 0) {
			int min = index_ * 3 + 1;
			if (index_ * 3 + 2 < Size) {
				if (Root[min] > Root[index_ * 3 + 2]) {
					min = index_ * 3 + 2;
				}
				if (index_ * 3 + 3 < Size) {
					if (Root[min] > Root[index_ * 3 + 3]) {
						min = index_ * 3 + 3;
					}
				}
			}
			return min;
		}
		else return -1;
	}
	bool Swap(int index_1, int index_2) {
		if (index_1 < 0 || index_1 >= Size || index_2 < 0 || index_2 >= Size) return false;
		int buf = Root[index_1];
		Root[index_1] = Root[index_2];
		Root[index_2] = buf;
	}
	bool ShiftUp(int index_) {
		if (index_ >= Size) return false;
		while (index_ > 0 && Root[index_] < Root[pred(index_)]) {
			Swap(index_, pred(index_));
			index_ = pred(index_);
		}
		return true;
	}
	bool ShiftDown(int index_) {
		if (index_ < 0) return false;
		while (index_*3 + 1 < Size && Root[index_] > Root[minchild(index_)]) {
			int index_1 = minchild(index_);
			Swap(index_, index_1);
			index_ = index_1;
		}
		return true;
	}
	void display(int buf_root, string position, string previousPicture) {
		cout << (previousPicture.substr(0, previousPicture.size() - 1) + "—");
		int index = search_index(buf_root);
		if (index == -1) {
			cout << position << "\033[91m-\033[0m" << endl;
			return;
		}
		else cout << position << buf_root << endl;

		if (index * 3 + 1 < Size) {
			previousPicture += "|";
			display(Root[index*3 + 1], "[:", previousPicture);
			if (index * 3 + 2 < Size) {
				previousPicture[previousPicture.size() - 1] = ' ';
				display(Root[index * 3 + 2], "[:", previousPicture);
				if (index * 3 + 3 < Size) {
					previousPicture[previousPicture.size() - 1] = ' ';
					display(Root[index * 3 + 3], "[:", previousPicture);
				}
			}
		}
	}
public:
	D3_Heap();
	~D3_Heap();
	bool insert_Item(int key_);
	bool create(vector<int> keys_);
	void Output();
	bool delete_min();
};
D3_Heap::D3_Heap() {
}
D3_Heap::~D3_Heap() {
}
inline bool D3_Heap::create(vector<int> keys_)
{
	vector<int> error_keys = {};
	for (int i = 0; i < keys_.size(); i++) {
		if (!insert_Item(keys_[i]))
			error_keys.push_back(keys_[i]);
	}
	return (error_keys.size() == 0);
}
inline bool D3_Heap::insert_Item(int key_)
{
	int index_key = search_index(key_);
	if (search_index(key_) != -1) return false;
	Overwrite_1(key_);
	if (!(ShiftUp(Size - 1))) {
		Overwrite_2();
		return false;
	}
	return true;
}
inline void D3_Heap::Output()
{
	display(Root[0], "—", " ");
	cout << endl;
}
inline bool D3_Heap::delete_min()
{
	if (Size < 1) return false;
	int result = Root[0];
	Swap(0, Size - 1);
	Overwrite_2();
	ShiftDown(0);
	return true;
}

#endif _D3_Heap_H_