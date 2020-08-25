#include "library2.h"
#include "dic_avl.h"
#include "dic_list.h"
#include "image.h"

void *Init(int segments) {

	Avl<int, Segments*> *DS;
	
	try {
		DS = new Avl<int, Segments*>(segments);
	}
	catch (std::bad_alloc& e) {
		return NULL;
	}
	return DS;
}

StatusType AddImage(void *DS, int imageID) {
	if (DS == NULL || imageID <= 0)
		return INVALID_INPUT;
	try {
		if (((Avl<int, Segments*>*)DS)->Find(imageID))
			return FAILURE;
		Segments* image = new Segments(((Avl<int, Segments*>*)DS)->segments);
		((Avl<int, Segments*>*)DS)->Insert(imageID, image);
		return SUCCESS;
	}
	catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	}
}

StatusType DeleteImage(void *DS, int imageID) {
	if (DS == NULL || imageID <= 0)
		return INVALID_INPUT;
	try {
		if (!((Avl<int, Segments*>*)DS)->Find(imageID))
			return FAILURE;
		((Avl<int, Segments*>*)DS)->Delete(imageID);
		return SUCCESS;
	}
	catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	}
}

StatusType AddLabel(void *DS, int imageID, int segmentID, int label) {
	if (DS == NULL || imageID <= 0 || segmentID < 0 || segmentID >= ((Avl<int, Segments*>*)DS)->segments || label <= 0)
		return INVALID_INPUT;
	try {
		if (!((Avl<int, Segments*>*)DS)->Find(imageID))
			return FAILURE;
		Avl<int, Segments*>::Node* temp = ((Avl<int, Segments*>*)DS)->Find(imageID);
		if (!temp->value->segmentAddLabel(segmentID, label))
			return FAILURE;
		return SUCCESS;
	}
	catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	}
}

StatusType GetLabel(void *DS, int imageID, int segmentID, int *label) {
	if (DS == NULL || imageID <= 0 || segmentID < 0 || segmentID >= ((Avl<int, Segments*>*)DS)->segments || label == NULL)
		return INVALID_INPUT;
	try {
		if (!((Avl<int, Segments*>*)DS)->Find(imageID))
			return FAILURE;
		Avl<int, Segments*>::Node* temp = ((Avl<int, Segments*>*)DS)->Find(imageID);
		int res = temp->value->segmentGetLabel(segmentID);
		if (res == 0)
			return FAILURE;
		*label = res;
		return SUCCESS;
	}
	catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	}
}

StatusType DeleteLabel(void *DS, int imageID, int segmentID) {
	if (DS == NULL || imageID <= 0 || segmentID < 0 || segmentID >= ((Avl<int, Segments*>*)DS)->segments)
		return INVALID_INPUT;
	try {
		if (!((Avl<int, Segments*>*)DS)->Find(imageID))
			return FAILURE;
		Avl<int, Segments*>::Node* temp = ((Avl<int, Segments*>*)DS)->Find(imageID);
		if (!temp->value->segmentDeleteLabel(segmentID))
			return FAILURE;
		return SUCCESS;
	}
	catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	}
}

void Quit(void** DS) {
	if (*DS == NULL)
		return;
	delete (Avl<int, Segments*>*) *DS;
	*DS = NULL;
}