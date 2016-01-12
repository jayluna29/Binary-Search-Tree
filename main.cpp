#include <iostream>
#include <iomanip>
#include <string>
#include "BSTree.h"
#include "SafeArray.h"
#include "SafeArrayOutOfBoundsException.h"

using namespace std;

template < class T >
void insert(BSTree < T >& tree, const T& insertItem);

template < class T >
void remove(BSTree < T >& tree, const T& elem);

int main()
{
	//create the tree
	BSTree < int > tree;

	//do some inserts
	insert(tree, 14);
	insert(tree, 34);
	insert(tree, 2);
	insert(tree, 12);
	insert(tree, 23);
	insert(tree, 6);
	insert(tree, 67);
	insert(tree, 45);
	insert(tree, 44);
	insert(tree, 67);
	insert(tree, 23);

	//do some removes
	remove(tree, 67);
	remove(tree, 44);
	remove(tree, 2);
	remove(tree, 45);
	remove(tree, 100);
	remove(tree, 23);
	remove(tree, 12);
	remove(tree, 14);
	remove(tree, 6);
	remove(tree, 23);
	remove(tree, 67);
	remove(tree, 34);

	return 0;
}
//*****************************************************************************
template < class T >
void insert(BSTree < T >& tree, const T& insertItem)
{
	//insert into the tree
	cout << "Inserting " << insertItem << " into the tree" << endl;

	tree.insert(insertItem);

	//print the new tree
	cout << "The tree looks like this: " << endl << endl;
	tree.printInTreeForm();
	cout << endl;

	//print some stats about the tree
	cout << "The maximum value is " << tree.findMax() << endl;
	cout << "The minimum value is " << tree.findMin() << endl;
	cout << "The height of the tree is " << tree.heightOfTree() << endl;
	cout << "The percentage of leaf nodes is " << setprecision(5) << 100 * tree.percentLeaf() << "%" << endl;
	cout << "The percentage of interior nodes is " << setprecision(5) << 100 * tree.percentInterior() << "%" << endl << endl << endl;
}
//*****************************************************************************
template < class T >
void remove(BSTree < T >& tree, const T& elem)
{
	//attempt to remove elem
	cout << "Removing " << elem;

	//if the item is found
	if (tree.search(elem))
	{
		//remove it
		cout << ", " << elem << " was found" << endl;
		tree.remove(elem);

		//print the new tree
		cout << "The tree now looks like this:" << endl;
		tree.printInTreeForm();
		cout << endl << endl;
	}
	else //the item was not found
	{
		//print error message
		cout << ", " << elem << " was not found" << endl << endl;
	}
}



//*******************************************************************
