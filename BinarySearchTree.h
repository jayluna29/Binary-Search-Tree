
#include "SafeArray.h"
#include <cmath>
#include <iostream>

using namespace std;


#pragma once
template <class T>

class BSTree
{

public:
	BSTree(); 
	// constructor to initialize class data
	~BSTree(); 
	// free up any resources acquired
	void insert(const T& d); 
	// insert an element into the tree
	bool search(const T& d); 
	// search for an element in the tree
	bool remove(const T& d); 
	// remove all the elements from the tree
	int size();
	// getting size
	void printInOrder(); 
	//print the items in ascending order
	void printPreOrder(); 
	// print the items in preorder fashion
	void printPostOrder(); 
	// print the items in postorder fashion
	T findMax(); 
	// return the maximum value in the tree
	T findMin();
	// return the minimum value in the tree
	int heightOfTree(); 
	// return the height of the tree
	float percentLeaf(); 
	// return the percentage of nodes that are leaf nodes
	float percentInterior(); 
	// return the percentage of nodes that are interior nodes
	void printInTreeForm(); 
	// print the tree in tree form

private:
	struct Node
	{
		T data;
		Node* p_right;
		Node* p_left;
		int leftHeight;
		int rightHeight;

	};

	bool searchHelper(Node* p_node, T elem);
	bool insertHelper(Node*& p_node, const T& elem);
	bool removeHelper(Node*& p_node, T elem);
	void inOrderHelper(Node* p_node);
	void postOrderHelper(Node* p_node);
	void preOrderHelper(Node* p_node);
	void balanceLeft(Node*& p_node);
	void balanceRight(Node*& p_node);
	bool isBalanced(Node* p_node);
	void fillInArray(Node* p_node, int index, SafeArray <Node*>& arr);
	int setHeightHelper(Node* p_node);
	void percentLeafHelper(Node* p_node);
	void percentInteriorHelper(Node* p_node);
	void destructorHelper(Node* p_node);


	int numElements;

	int countLeaves;
	int countInterior;

	Node* root;

};
template <class T>
BSTree<T>::BSTree()
{
	root = 0;
	numElements = 0;
	countLeaves = 0;
	countInterior = 0;
}
template <class T>
BSTree <T>:: ~BSTree()
{
	destructorHelper(root);
}

template <class T>
void BSTree <T>::destructorHelper(Node* p_node)
{
	//if p_node is not null it will recurse down the tree and begin deleting the tree upwards
	if (p_node != 0)
	{
		destructorHelper(p_node->p_left);
		destructorHelper(p_node->p_right);
		delete p_node;
		numElements--;
	}
}
template <class T>
void BSTree<T>::insert(const T& elem)
{
	insertHelper(root, elem);
}
// The insert and the remove are very much alike
template <class T>
bool BSTree<T>::insertHelper(Node*& p_node, const T& elem)
{
	bool retVal = false;

	if (p_node == 0)
	{
		p_node = new Node;

		p_node->p_right = 0;
		p_node->p_left = 0;

		p_node->data = elem;

		p_node->leftHeight = 0;
		p_node->rightHeight = 0;

		// adding one here by number of elements 
		numElements++;

		//will reset the heights after being balanced
		setHeightHelper(root);

	}
	else
	{
		if (elem <= p_node->data)
		{
			insertHelper(p_node->p_left, elem);

			if (!isBalanced(p_node))
			{
				balanceLeft(p_node);
				setHeightHelper(root);
				if (!isBalanced(p_node))
				{
					balanceLeft(p_node->p_right);
					balanceRight(p_node);
					//will reset the heights after being balanced
					setHeightHelper(root);
				}
			}
		}
		else
		{
			insertHelper(p_node->p_right, elem);

			if (!isBalanced(p_node))
			{
				balanceRight(p_node);
				//will reset the heights after being balanced
				setHeightHelper(root);
				if (!isBalanced(p_node))
				{
					balanceRight(p_node->p_left);
					balanceLeft(p_node);
					//will reset the heights after being balanced
					setHeightHelper(root);
				}
			}

		}

	}
	return retVal;
}
template <class T>
bool BSTree<T>::search(const T& elem)
{
	return searchHelper(root, elem);
}
template <class T>
bool BSTree <T>::searchHelper(Node* p_node, T elem)
{
	if (p_node->data == elem)
	{
		return true;
	}
	else if (p_node->p_right == 0 && p_node->p_left == 0)
	{
		return false;
	}
	else if (p_node->data < elem)
	{
		return searchHelper(p_node->p_right, elem);
	}
	else
	{
		return searchHelper(p_node->p_left, elem);
	}
}
template <class T>
bool BSTree<T>::remove(const T& elem)
{
	return removeHelper(root, elem);
}
template <class T>
bool BSTree<T>::removeHelper(Node*& p_node, T elem)
{
	bool retVal = false;
	if (p_node != 0)
	{
		if (p_node->data == elem)
		{
			retVal = true;
			if (p_node->p_right == 0 && p_node->p_left == 0)
			{
				delete p_node;
				p_node = 0;
				numElements--;
			}
			else if (p_node->p_right == 0 && p_node->p_left != 0)
			{
				Node* node = p_node;
				p_node = p_node->p_left;
				delete node;
				numElements--;
			}
			else if (p_node->p_left == 0 && p_node->p_right != 0)
			{
				Node* node = p_node;
				p_node = p_node->p_right;
				delete node;
				numElements--;
			}
			else
			{
				Node* left = p_node->p_left;
				while (left->p_right != 0)
				{
					left = left->p_right;
				}

				p_node->data = left->data;

				removeHelper(p_node->p_left, p_node->data);
			}
			//will reset the heights after being balanced
			setHeightHelper(root);

		}
		else if (p_node->data <= elem)
		{
			retVal = removeHelper(p_node->p_right, elem);

			// this is just going to find the height of the tree and will balance tree
			if (!isBalanced(p_node))
			{
				balanceLeft(p_node);	

				//will reset the heights after being balanced
				setHeightHelper(root);

				// this is just going to find the height of the tree and will balance tree
				if (!isBalanced(p_node))
				{
					balanceRight(p_node->p_left);
					balanceLeft(p_node);

					//will reset the heights after being balanced
					setHeightHelper(root);
				}
			}
		}

		else
		{
			retVal = removeHelper(p_node->p_left, elem);

			// this is just going to find the height of the tree and will balance tree
			if (!isBalanced(p_node))
			{
				balanceRight(p_node);

				//will reset the heights after being balanced
				setHeightHelper(root);

				// this is just going to find the height of the tree and will balance tree
				if (!isBalanced(p_node))
				{
					balanceLeft(p_node->p_right);
					balanceRight(p_node);

					//will reset the heights after being balanced
					setHeightHelper(root);
				}
			}
		}

	}

	return retVal;
}
template <class T>
int BSTree<T>::size()
{
	return numElements;
}
//watching the videos helped with pre order,post order, and in order
//used professor's algorithms and implemented as shown below
template <class T>
void BSTree<T>::printPreOrder()
{
	preOrderHelper(root);
}
template <class T>
void BSTree<T>::preOrderHelper(Node* p_node)
{
	if (p_node != 0)
	{
		preOrderHelper(p_node->p_right);
		preOrderHelper(p_node->p_left);

		cout << p_node->data << " " << endl;
	}
}
//watching the videos helped with pre order,post order, and in order
template <class T>
void BSTree<T>::printInOrder()
{
	inOrderHelper(root);
}
template <class T>
void BSTree<T>::inOrderHelper(Node* p_node)
{
	if (p_node != 0)
	{
		inOrderHelper(p_node->p_left);
		cout << p_node->data << " " << endl;
		inOrderHelper(p_node->p_right);
	}
}
//watching the videos helped with pre order,post order, and in order
template <class T>
void BSTree<T>::printPostOrder()
{
	postOrderHelper(root);
}
template <class T>
void BSTree<T>::postOrderHelper(Node* p_node)
{
	if (p_node != 0)
	{
		postOrderHelper(p_node->p_left);
		postOrderHelper(p_node->p_right);
		cout << p_node->data << " " << endl;
	}
}
template <class T>
void BSTree<T>::balanceLeft(Node*& p_node)
{
	if (p_node != 0)
	{
		//balancing actual node
		Node* p_current = p_node;
		Node* p_newRoot = p_current->p_left;
		Node* p_newRootRight = p_newRoot->p_right;
		p_newRoot->p_right = p_current;
		p_current->p_left = p_newRootRight;
		p_node = p_newRoot;
	}
}
template <class T>
void BSTree <T>::balanceRight(Node*& p_node)
{
	if (p_node != 0)
	{
		//balancing actual node
		Node* p_current = p_node;
		Node* p_newRoot = p_current->p_right;
		Node* p_newRootLeft = p_newRoot->p_left;
		p_newRoot->p_left = p_current;
		p_current->p_right = p_newRootLeft;
		p_node = p_newRoot;
	}
}
template <class T>
int BSTree <T>::setHeightHelper(Node* p_node)
{
	//will be used to reset the heights when they are altered by inserting or removing from the tree
	if (p_node != 0)
	{
		p_node->leftHeight = setHeightHelper(p_node->p_left) + 1;
		p_node->rightHeight = setHeightHelper(p_node->p_right) + 1;

		if (p_node->leftHeight >= p_node->rightHeight)
		{
			return p_node->leftHeight;
		}
		else
		{
			return p_node->rightHeight;
		}
	}
	else
	{
		return -1;
	}
}
//creating a node in a safe array and finds position from within
//think about drawing all the number of elements and spaces into the safe array
//went over this in tutoring session thursday
template <class T>
void BSTree <T>::fillInArray(Node* p_node, int index, SafeArray <Node*>& arr)
{
	if (p_node != 0)
	{
		arr[index] = p_node;
		fillInArray(p_node->p_left, (2 * index) + 1, arr);
		fillInArray(p_node->p_right, (2 * index) + 2, arr);
	}
}
template <class T>
bool BSTree <T>::isBalanced(Node* p_node)
{
	if (p_node->rightHeight - p_node->leftHeight > 1 || p_node->rightHeight - p_node->leftHeight < -1)
	{
		return false;
	}
	else
	{
		return true;
	}
}
//the nodes that have nothing hanging off of them at the bottom of the tree
template <class T>
float BSTree <T>::percentLeaf()
{
	countInterior = 0;
	countLeaves = 0;

	percentLeafHelper(root);

	return ((float)countLeaves / (float)numElements);
}
template <class T>
void BSTree <T>::percentLeafHelper(Node* p_node)
{
	if (p_node != 0)
	{
		//if you get to the bottom of the tree at any point it will add to the counter
		percentLeafHelper(p_node->p_left);
		if (p_node->p_right == 0 && p_node->p_left == 0)
		{
			countLeaves++;
		}
		percentLeafHelper(p_node->p_right);
	}
}
template <class T>
float BSTree <T>::percentInterior()
{
	countInterior = 0;
	countInterior = 0;

	percentInteriorHelper(root);

	return((float)countInterior / (float)numElements);
}
template <class T>
void BSTree <T>::percentInteriorHelper(Node* p_node)
{
	//will keep track of the number of non leaf nodes in the tree
	if (p_node != 0)
	{
		// when this is not at the very bottom of the tree point then it will just add to the actually counter of the interior
		percentInteriorHelper(p_node->p_left);
		if (!(p_node->p_right == 0 && p_node->p_left == 0))
		{
			countInterior++;
		}
		percentInteriorHelper(p_node->p_right);
	}
}
//will iterate and search to the right of the tree to find the largest value
//right of tree
template <class T>
T BSTree <T>::findMax()
{
	Node* p_max = root;
	while (p_max->p_right != 0)
	{
		p_max = p_max->p_right;
	}

	return p_max->data;
}
//will iterate and search to the left of the tree to find the smallest value
//left of tree
template <class T>
T BSTree <T>::findMin()
{
	Node* p_min = root;
	while (p_min->p_left != 0)
	{
		p_min = p_min->p_left;
	}
	return p_min->data;
}
template <class T>
int BSTree <T>::heightOfTree()
{
	if (numElements > 0)
	{
		if (root->rightHeight > root->leftHeight)
		{
			return root->rightHeight + 1;
		}
		else
		{
			return root->leftHeight + 1;
		}
	}
	else
	{
		return 0;
	}
}
//need help with sara 
template <class T>
void BSTree <T>::printInTreeForm()
{
	if (heightOfTree() > 0)
	{
		int l = heightOfTree();

		// "pow" function
		int length = ((int)(pow(2.0, (float)heightOfTree()) - 1.0));

		SafeArray <Node*> array(length);

		//initialize all node pointers in array to null
		for (int i = 0; i < array.size(); i++)
		{
			array[i] = 0;
		}

		//set the nodes to the array
		fillInArray(root, 0, array);

		float current = 0.0;
		//this will begin printing in tree form
		for (int i = 0; i < array.size(); i++)
		{
			//if the node is not null it will print the data
			if (array[i] != 0)
			{
				if (i == 0)
				{
					//this makes leading spaces
					for (int j = 0; j < ((int)pow(2.0, ((float)heightOfTree() - 1) - current) - 1); j++)
					{
						cout << "  ";
					}
				}
				//check if 1 digit or not
				if (array[i]->data / 10 < 1)
				{
					cout << " ";
				}
				cout << array[i]->data;

				//We are wanting to just make spaces between the values
				for (int k = 0; k < ((int)pow(2.0, (float)heightOfTree() - current) - 1); k++)
				{
					cout << "  ";
				}
				//this will keep track of the row of the tree that we are on and end the lines.
				if (i == 0 || i == ((int)pow(2.0, (current + 1)) - 2))
				{
					cout << endl;
					current = current + 1;

					for (int j = 0; j < ((int)pow(2.0, (float)heightOfTree() - 1 - current) - 1); j++)
					{
						cout << "  ";
					}
				}
			}
			else
			{
				//show empty spacing
				cout << "**";

				for (int k = 0; k < ((int)pow(2.0, (float)heightOfTree() - current) - 1); k++)
				{
					cout << "  ";
				}
			}
		}
	}
	else
	{
		cout << "There is no longer a tree." << endl;
	}
}//complicated process and got help with printing out the tree
//everything else went fair as to using recursion... it required a lot of copy and pasting and switching p_right and p_left
