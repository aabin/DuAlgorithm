#pragma once
#include "common.h"

namespace BinarySearch {
	// find peak element in an array
	int peakIndexInMountainArray(vector<int>& A) {
		int l = 0, r = (int)A.size();
		while (l < r) {
			int p = (l + r) >> 1;
			if (A[p] > A[p + 1]) {
				r = p;
			}
			else {
				l = p + 1;
			}
		}
		return l;
	}
}