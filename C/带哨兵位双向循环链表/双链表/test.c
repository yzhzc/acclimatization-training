#include"List.h"


void TestList()
{
	LTNode* plist = ListInit();
	ListPushBack(plist, 1);
	ListPushBack(plist, 1);
	ListPushBack(plist, 3);
	ListPushBack(plist, 1);
	ListPushBack(plist, 1);

	LTNode* pos = ListFind(plist, 3);
	ListInsert(pos, 7);
	ListInsert(pos, 8);
	ListInsert(pos, 9);
	ListErase(pos);

	ListPrint(plist);

}



int main()
{
	TestList();

	return 0;
}