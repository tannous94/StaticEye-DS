#include "library2.h"
#include "dic_avl.h"
#include "test.h"
#include "image.h"

int key(void** node){
	Avl<int, Segments>::Node* temp = ((Avl<int, Segments>::Node*)*node);
	return temp->key;
}

int satelite(void** value){
	int temp = **(int**)value;
	return temp;
}

bool testInit(){
void* DS= Init(5);
Quit(&DS);
ASSERT_TRUE(DS == NULL);
return true;
}

StatusType AddImage(void *DS, int imageID);

bool test(){
	void* DS = Init(3);
	ASSERT_TRUE(AddImage(NULL, 1) == INVALID_INPUT);
	ASSERT_TRUE(AddImage(DS, -1) == INVALID_INPUT);


	ASSERT_TRUE(AddImage(DS, 12) == SUCCESS);
	ASSERT_TRUE(((Avl<int, Segments*>*)DS)->Find(12)->key, 12);
	ASSERT_TRUE(AddImage(DS, 12) == FAILURE);

	ASSERT_TRUE(DeleteImage(DS, 1) == FAILURE);
	ASSERT_TRUE(DeleteImage(DS, -1) == INVALID_INPUT);
	ASSERT_TRUE(DeleteImage(NULL, 1) == INVALID_INPUT);
	ASSERT_TRUE(DeleteImage(DS, 12) == SUCCESS);
	ASSERT_TRUE(DeleteImage(DS, 12) == FAILURE);

	ASSERT_TRUE(AddImage(DS, 2) == SUCCESS); //success
	ASSERT_TRUE(AddLabel(DS, 3, 1, 3) == FAILURE);
	ASSERT_TRUE(AddLabel(NULL, 2, 1, 3) == INVALID_INPUT);
	ASSERT_TRUE(AddLabel(DS, 2, -1, 3) == INVALID_INPUT);
	ASSERT_TRUE(AddLabel(DS, 2, 1, -1) == INVALID_INPUT);
	ASSERT_TRUE(AddLabel(DS, 2, 3, 2) == INVALID_INPUT);

	ASSERT_TRUE(AddLabel(DS, 2, 1, 13) == SUCCESS); // success
	ASSERT_TRUE(AddLabel(DS, 2, 1, 5) == FAILURE);

	Avl<int, Segments*>::Node* temp = (((Avl<int, Segments*>*)DS)->Find(2));
	ASSERT_TRUE(temp->value->unlabeled->getSize() == 2);
	int t1 = 2;
	int* t = &t1;
	ASSERT_TRUE(GetLabel(NULL, 2, 1, t) == INVALID_INPUT);
	ASSERT_TRUE(GetLabel(DS, -2, 1, t) == INVALID_INPUT);
	ASSERT_TRUE(GetLabel(DS, 2, -1, t) == INVALID_INPUT);
	ASSERT_TRUE(GetLabel(DS, 2, 1, NULL) == INVALID_INPUT);
	ASSERT_TRUE(GetLabel(DS, 1, 1, t) == FAILURE);
	ASSERT_TRUE(GetLabel(DS, 2, 2, t) == FAILURE);
	ASSERT_TRUE(GetLabel(DS, 2, 1, t) == SUCCESS); // success
	ASSERT_TRUE(*t == 13);

	ASSERT_TRUE(DeleteLabel(NULL, 2, 1) == INVALID_INPUT);
	ASSERT_TRUE(DeleteLabel(DS, 2, -1) == INVALID_INPUT);
	ASSERT_TRUE(DeleteLabel(DS, 2, 3) == INVALID_INPUT);
	ASSERT_TRUE(DeleteLabel(DS, 0, 1) == INVALID_INPUT);
	ASSERT_TRUE(DeleteLabel(DS, 2, 2) == FAILURE);
	ASSERT_TRUE(DeleteLabel(DS, 1, 1) == FAILURE);
	ASSERT_TRUE(DeleteLabel(DS, 2, 1) == SUCCESS); //success
	temp = (((Avl<int, Segments*>*)DS)->Find(2));
	ASSERT_TRUE(DeleteLabel(DS, 2, 1) == FAILURE); 

	Quit(&DS);
	ASSERT_TRUE(DS == NULL);
	return true;
}

int main() {
	RUN_TEST(testInit);
	RUN_TEST(test);
}