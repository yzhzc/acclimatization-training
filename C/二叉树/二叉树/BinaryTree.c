#include"BinaryTree.h"



//ǰ�������ӡ���ڵ�
void PrevOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}
	printf("%c ", root->_data);
	PrevOrder(root->_left);
	PrevOrder(root->_right);
}

//�ڵ�ĸ���
int TreeSize(BTNode* root)
{
	if (root == NULL)
		return 0;
	else
		return 1 + TreeSize(root->_left) + TreeSize(root->_right);
}

//Ҷ�ӽڵ�ĸ���
int TreeLeafSize(BTNode* root)
{
	if (root == NULL)
		return 0;
	if (root->_left == root->_right == NULL)
		return 1;

	return TreeLeafSize(root->_left) + TreeLeafSize(root->_right);
}

//���ص�k��ڵ����
int BinaryTreeLeve1KSize(BTNode* root, int k)
{
	if (root == NULL)
		return 0;

	if (k == 1)
		return 1;

	return BinaryTreeLeve1KSize(root->_left, k - 1) + BinaryTreeLeve1KSize(root->_right, k - 1);
}

//Ѱ��ֵΪk�Ľڵ�
BTNode* TreeFind(BTNode* root, int k)
{
	if (root == NULL)
		return NULL;
	if (root->_data == k)
		return root;

	BTNode* node = TreeFind(root->_left, k);
	if (node)
		return node;

	node = TreeFind(root->_right, k);
	if (node)
		return node;

	return NULL;
}

//�����½ڵ�
BTNode* CreateNode(BTDataNode x)
{
	BTNode* newnode = (BTNode*)malloc(sizeof(BTNode));
	newnode->_data = x;
	newnode->_left = NULL;
	newnode->_right = NULL;

	return newnode;
}

//�����
void BinaryTreeLeve1order(BTNode* root)
{
	Queue q;
	QueueInit(&q);
	QueuePush(&q, root);
	while (!QueueEmpty(&q))
	{
		BTNode* prev = QueueFront(&q);
		QueuePop(&q);
		printf("%c", prev->_data);

		if (prev->_left != NULL)
		{
			QueuePush(&q, prev->_left);
		}
		if (prev->_right != NULL)
		{
			QueuePush(&q, prev->_right);
		}
	}
	QueueDestory(&q);
}

//�ж��Ƿ�Ϊ��ȫ������
int BinaryTreeComplete(BTNode* root)
{
	Queue q;
	QueueInit(&q);
	QueuePush(&q, root);
	while (1)
	{
		BTNode* front = QueueFront(&q);
		QueuePop(&q);

		if (front)
			break;

		QueuePush(&q, front->_left);
		QueuePush(&q, front->_right);
	}
	while (!QueueEmpty(&q))
	{
		BTNode* front = QueueFront(&q);

		if (front != NULL)
		{
			QueueDestory(&q);
			return 0;
		}
			
		QueuePop(&q);
	}
	QueueDestory(&q);
	
	return 1;
}

//���ٶ�����
void DestoryTree(BTNode* root)
{
	if (root == NULL)
		return;
	
	DestoryTree(root->_left);
	DestoryTree(root->_right);


	free(root);
	root = NULL;
}












