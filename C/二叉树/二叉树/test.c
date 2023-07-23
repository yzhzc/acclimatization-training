#include"BinaryTree.h"





int main()
{
	BTNode* A = CreateNode('A');
	BTNode* B = CreateNode('B');
	BTNode* C = CreateNode('C');
	BTNode* D = CreateNode('D');
	BTNode* E = CreateNode('E');

	A->_left = B;
	A->_right = C;
	B->_left = D;
	B->_right = E;


	PrevOrder(A);
	int size = 0;

	printf("%d", size = TreeSize(A));

	printf("%d", size = TreeSize(A));

	printf("\n%d", BinaryTreeLeve1KSize(A, 2));

	BinaryTreeLeve1order(A);

	printf("\n%d", BinaryTreeComplete(A));


	return 0;
}