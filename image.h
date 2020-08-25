#include "dic_list.h"

typedef int Label;
typedef int SegID;
class Segments {
public:
	int* seg_array;
	List<SegID, Label>* unlabeled;

	Segments(int n) {
		seg_array = new int[n];
		for (int i = 0; i < n; i++)
			seg_array[i] = 0;
		unlabeled = new List<SegID, Label>();
		for (int i = 0; i < n; i++) { // inside list we need the unlabled ones 
			unlabeled->Insert(i, seg_array[i]);
		}
	}

	~Segments() {
		delete[] seg_array;
		delete unlabeled;
	}

	bool segmentAddLabel(SegID segmentID, Label label) {
		if (seg_array[segmentID] != 0)
			return false;

		seg_array[segmentID] = label;
		unlabeled->Delete(segmentID);
		return true;
	}

	int segmentGetLabel(SegID segmentID) {
		if (seg_array[segmentID] == 0)
			return 0;
		return seg_array[segmentID];
	}

	bool segmentDeleteLabel(SegID segmentID) {
		if (seg_array[segmentID] == 0)
			return false;
		seg_array[segmentID] = 0;
		unlabeled->Insert(segmentID, seg_array[segmentID]);
		return true;
	}
};