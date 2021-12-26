#include <iostream>

using namespace std;

template <class T>
class Queue
{
private:
	class elem
	{
	public:
		elem(T data = 0, elem* next = NULL) : data(data), next(next) {}

		T data;
		elem* next;
	};

	elem* head;
	elem* last;

public:
	Queue()
	{
		head = NULL;
		last = NULL;
	};

	~Queue() {
		while (!empty())
		{
			pop();
		}
	};

	void pop() {//delete
		if (empty())
		{
			throw out_of_range("No more elements");
		}
		else
		{
			elem* tmp = head;
			head = head->next;
			delete tmp;
		}
	};

	void push(T data) {//add
		elem* tmp = new elem(data);
		if (empty())
		{
			head = tmp;
			last = tmp;
		}
		else
		{
			last->next = tmp;
			last = tmp;
		}
	};

	bool empty() {
		return head == NULL;

	};

	T front() {//first element
		if (empty())
		{
			throw out_of_range("Empty");
		}
		else
		{
			return head->data;
		}
	};

	T back() {//last element
		if (empty())
		{
			throw out_of_range("Empty");
		}
		else
		{
			return last->data;
		}

	};

};
class Node
{
public:
	Node(int data = 0, Node* left = NULL, Node* right = NULL, Node* prev = NULL) :data(data), left(left), right(right), prev(prev) {}
	~Node() = default;
	int getData() { return data; }

	void setData(int newData) { data = newData; }
	void setLeft(Node* newnleft) { left = newnleft; }
	void setRight(Node* newright) { right = newright; }
	void setPrev(Node* newprev) { prev = newprev; }


	Node* getLeft() { return left; }
	Node* getRight() { return right; }
	Node* getPrev() { return prev; }
	Node* makeNull() { return left = NULL; }

private:
	Node* left, * right, * prev;
	int data;
};
class Iterator
{
public:
	virtual int next() = 0;
	virtual bool has_next() = 0;
	virtual ~Iterator() {};
};
template <class T>
class Stack
{
private:
	class elem
	{
	public:
		elem(T data, elem* next = NULL) :data(data), next(next) {}
		~elem() = default;
		void setNext(elem* newnext) { next = newnext; }
		elem* getNext() { return next; }
		T getData() { return data; }
	private:
		T data;
		elem* next;
	};

	elem* head;
public:
	Stack() {
		head = NULL;
	};

	~Stack() {
		while (!empty())
		{
			pop();
		}
	};

	void pop() {//delete
		if (empty())
		{
			throw out_of_range("No more elements");
		}
		else
		{
			elem* tmp = head;
			head = head->getNext();
			delete tmp;
		}
	};

	void push(T data) {//add
		elem* tmp = new elem(data);
		elem* cur = head;
		head = tmp;
		head->setNext(cur);

	};

	bool empty() {
		return head == nullptr;
	};

	T top() {//first element
		if (empty())
		{
			throw out_of_range("Empty");
		}
		else
		{
			return head->getData();
		}

	};
};

class Heap
{
private:

	class Node
	{
	public:
		Node* left, * right, * prev; int data;
		Node(int data = 0, Node* left = NULL, Node* right = NULL, Node* prev = NULL) :data(data), left(left), right(right), prev(prev) {}
		~Node() = default;
	};
	Node* root;
	int hight, numberNode;//hight of our heap and vertical number of nodes on last lay
public:
	Heap() { root = NULL; hight = 0; numberNode = 0; }//create heap with 0 nodes

	Heap(int data)//heap with 1/first node
	{
		Node* elem = new Node(data);
		root = elem;
		hight = 1; numberNode = 1;
	}

	class dfs_iterator : public Iterator //depth first search 
	{
	public:
		friend class BinaryHeap;

		dfs_iterator(Node* root) {
			cur = root;
			stack = new Stack<Node*>();
		}
		~dfs_iterator() { delete stack; }

		bool has_next() override;

		int next() override;
		Stack<Node*>* stack;

		Node* cur;
	};

	class bfs_iterator : public Iterator //breath first search
	{
	public:
		friend class BinaryHeap;

		bfs_iterator(Node* root) {
			cur = root;
			queue = new Queue<Node*>();
		}

		~bfs_iterator() { delete queue; }

		bool has_next() override;

		int next() override;


		Queue<Node*>* queue;
		Node* cur;
	};
	Iterator* create_dfs() {
		return new dfs_iterator(root);
	}

	Iterator* create_bfs() {
		bfs_iterator* new_bfs_iterator = new bfs_iterator(root);
		new_bfs_iterator->queue->push(root);
		return new_bfs_iterator;
	}
	Node* LastParent(int lay)  //find parent int the end to insert node 
	{
		Node* last = root;
		int tmp_lay = lay;
		int tmp_Number = numberNode;
		if (numberNode > lay) { tmp_lay = tmp_lay * 2; }

		while (tmp_lay != 2)
		{
			if (tmp_Number <= (tmp_lay / 2))
			{
				last = last->left;
				tmp_lay = tmp_lay / 2;
			}
			else
			{
				last = last->right;
				tmp_Number = tmp_Number - tmp_lay / 2;
				tmp_lay = tmp_lay / 2;
			}
		}
		return last;
	}
	void siftDown(Node* tmp)// sift small node deeper
	{
		if (tmp->left == NULL && tmp->right == NULL)
		{
			return;
		}
		Node* max = tmp;
		if (tmp->right == NULL)
		{
			if (tmp->data < tmp->left->data) { max = tmp->left; }
		}
		else { return; }
		if (tmp->left != NULL && tmp->right != NULL)
		{
			if ((tmp->data < tmp->right->data) || (tmp->data < tmp->left->data))
			{
				if (tmp->left->data > tmp->right->data) { max = tmp->left; }
			}
			else { max = tmp->right; }
		}
		else
		{
			return;
		}
		swap(tmp->data, max->data);

		siftDown(max);
	}
	void siftUp(Node* tmp) //sift big nod higher 
	{
		if (tmp->prev == NULL) { return; }
		else
		{
			if (tmp->data > tmp->prev->data)
			{
				swap(tmp->data, tmp->prev->data);
				siftUp(tmp->prev);
			}
			else
			{
				return;
			}
		}
	}
	void Heapify(Node* tmp)//to understand what we should do with inserted node
	{
		if (tmp->prev == NULL) { siftDown(tmp); }
		else
		{
			if (tmp->data > tmp->prev->data)
			{
				siftUp(tmp);
			}
			else
			{
				siftDown(tmp);
			}
		}
	}
	bool contains(int data)
	{
		try
		{
			findNode(data);
			return true;
		}
		catch (out_of_range)
		{
			return false;
		}
	}
	Node* findNode(int data)
	{
		Node* elem = NULL;
		dfs_iterator* dfs = new dfs_iterator(root);
		while (dfs->has_next())
		{
			elem = dfs->cur;
			if (dfs->next() == data) { delete dfs; return elem; }
		}
		delete dfs; throw out_of_range("Element ot found");
	}
	void insert(int elem)
	{
		if (root == NULL) {
			Node* node = new Node(elem);
			root = node;
			numberNode = 1;
			hight = 1;
		}
		else
		{
			Node* tmp = new Node(elem);
			Node* cur = root;
			int last = 1;
			numberNode++;
			for (int i = 0; i < hight - 1; i++) { last = last * 2; }
			if (last < numberNode) { numberNode = 1; hight++; last = last * 2; }
			cur = LastParent(last);
			if (cur->left == NULL)
			{
				cur->left = tmp; tmp->prev = cur;
			}
			else { cur->right = tmp; tmp->prev = cur; }
			Heapify(tmp);

		}
	}

	void remove(int data)
	{
		Node* deleteNode = findNode(data);
		if ((root->left == NULL) && (root->right == NULL))
		{
			delete root; root = NULL; hight = 0; numberNode = 0;
		}
		int last = 1;
		for (int i = 0; i < hight - 1; i++) { last = last * 2; }
		Node* lastElem = LastParent(last);
		if (lastElem->right != NULL)
		{
			lastElem = lastElem->right;
			lastElem->prev->right = NULL;
			numberNode--;
		}
		else
		{
			lastElem = lastElem->left;
			lastElem->prev->left = NULL;
			numberNode--;
		}
		if (numberNode == 0)
		{
			numberNode = 1;
			hight--;
			for (int i = 0; i < hight - 1; i++)
			{
				numberNode = numberNode * 2;
			}
		}
		if (deleteNode == lastElem) { delete lastElem; }
		else
		{
			swap(lastElem->data, deleteNode->data);
			Heapify(deleteNode);
		}
	}

};

bool Heap::dfs_iterator::has_next() {
	return cur != NULL;
}
bool Heap::bfs_iterator::has_next() {
	return cur != NULL;
}
int Heap::bfs_iterator::next()
{
	if (!has_next()) { 
		throw out_of_range("No moe elements"); 
	}
	int tmp = cur->data;
	if (cur->left != NULL) { 
		queue->push(cur->left); 
	}
	if (cur->right != NULL) { 
		queue->push(cur->right); 
	}
	queue->pop();
	try {
		cur = queue->front(); 
	}catch (out_of_range) {
		cur = NULL; 
	}
	return tmp;
}
int Heap::dfs_iterator::next()
{
	if (!has_next()) { 
		throw out_of_range("No more elements");
	}
	int tmp = cur->data;
	if ((cur->right) != NULL) {
		stack->push(cur->right); 
	}
	if ((cur->left) != NULL) {
		cur = cur->left; 
	}
	else {
		try { 
			cur = stack->top(); stack->pop(); 
		}
		catch (out_of_range) { 
			cur = NULL; 
		}
	}
	return tmp;
}

int main() {
	Heap heap(1);
	Iterator* dfs_1, * dfs_2, * bfs_1, * bfs_2;
	heap.insert(1);
	heap.insert(2);
	heap.insert(15);
	heap.insert(4);
	heap.insert(42);
	heap.insert(4);
	heap.insert(19);
	heap.insert(7);
	/*
	Heap status
	.				42
	.			  /		\
	.			 19		15
	.		   /   \   /   \
	.		  7     2  1    4
	.		/  \
	.      1    4
	*/
	if (heap.contains(4)) {
		cout << "node exists\n";
	}
	else
	cout << "NODE SEARCH";
	dfs_1 = heap.create_dfs();
	bfs_1 = heap.create_bfs();
	cout << "DFS:\n";
	if (dfs_1->has_next()) {
		while (dfs_1->has_next()) { cout << dfs_1->next() << endl; }
	}
	cout << endl;
	cout << "BFS:\n";
	if (bfs_1->has_next()) {
		while (bfs_1->has_next()) { cout << bfs_1->next() << endl; }
	}
	cout << endl;
	heap.remove(4);
	cout << "NODE SEARCH (ONE NODE REMOVED)";
	dfs_2 = heap.create_dfs();
	bfs_2 = heap.create_bfs();
	cout << "BFS:\n";
	if (bfs_2->has_next()) {
		while (bfs_2->has_next()) { cout << bfs_2->next() << endl; }
	}
	cout << endl;
	cout << "DFS:\n";
	if (dfs_2->has_next()) {
		while (dfs_2->has_next()) { cout << dfs_2->next() << endl; }
	}
	cout << endl;
	delete dfs_1, dfs_2, bfs_1, bfs_2;
	return 0;
}