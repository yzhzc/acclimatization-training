#include"SList.h"

void TestSList()
{
	SLTNode* plist = NULL;



	SListPushFront(&plist, 1);
	SListPushFront(&plist, 2);
	SListPushFront(&plist, 3);
	SListPushFront(&plist, 4);
	SListPushFront(&plist, 3);
	SListPushFront(&plist, 1);




	SLTNode* pos1 = SListFind(plist, 2);
	SListInsert(&plist, 9, pos1);
	SListErase(&plist, pos1);

	SListPrint(plist);

	SListDestory(&plist);


	SListPrint(plist);





}


int main()
{
	TestSList();

	return 0;
}