#pragma once

class Heap
{
public:
	Heap();

	void Insert(Node* node);
	void UpdateUpper(int index);
	
	Node* DeleteRoot();
	void UpdateLower(int index);

	void Swap(int n1, int n2);

	void Clear();

	bool Empty() { return heap.empty(); }
private:
	vector<Node*> heap;

};
