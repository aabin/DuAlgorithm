#pragma once
#include "common.h"

namespace MergeSort {
	// Merge sort of a vector
	// Time: O(N log N)
	// Space: O(N)
	void mergeSort(vector<int> &nums, int l, int r) {
		if (l == r) return;
		int p = (l + r) >> 1;
		mergeSort(nums, l, p);
		mergeSort(nums, p + 1, r);
		int i = l, j = p + 1;
		int n = r - l + 1;

		// Merge [l, p] and [p+1, r] to a temporary array
		vector<int> tmp(n);
		for (int k = 0; k < n; ++k) {
			if (j > r || (i <= p && nums[i] < nums[j])) {
				tmp[k] = nums[i];
				++i;
			}
			else {
				tmp[k] = nums[j];
				++j;
			}
		}

		// Copy the temporary array back to the vector
		for (int k = 0, i = l; k < n; ++k, ++i) {
			nums[i] = tmp[k];
		}
	}

	// Merge sort of a linked list
	// Time: O(N log N)
	// Space: O(1)
	ListNode* mergeTwoLists(ListNode* left, ListNode* right) {
		ListNode dummy(-1);
		for (ListNode* p = &dummy; left || right; p = p->next) {
			int l = left ? left->val : INT_MAX;
			int r = right ? right->val : INT_MAX;
			if (l <= r) {
				p->next = left;
				left = left->next;
			}
			else {
				p->next = right;
				right = right->next;
			}
		}
		return dummy.next;
	}

	ListNode* sortList(ListNode* head) {
		if (!head || !head->next) return head;

		// find the central element in O(n)
		ListNode *fast = head, *slow = head;
		while (fast->next && fast->next->next) {
			fast = fast->next->next;
			slow = slow->next;
		}

		// break into two linked list
		fast = slow;
		slow = slow->next;
		fast->next = NULL;

		ListNode *left = sortList(head);
		ListNode *right = sortList(slow);

		return mergeTwoLists(left, right);
	}

	// 327. Count of Range Sum
	// Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.
	// Time: O(N log N), see multiset.h for BST solution
	// Space: O(N)
	int countAndMergeSort(vector<long long> *sums, int start, int end, int lower, int upper) {
		// The number of range [start, end] of which size is less than 2 is always 0.
		if (end - start <= 0) {
			return 0;
		}
		int mid = start + (end - start) / 2;
		int count = countAndMergeSort(sums, start, mid, lower, upper) +
			countAndMergeSort(sums, mid + 1, end, lower, upper);
		int j = mid + 1, k = mid + 1, r = mid + 1;

		vector<long long> tmp;
		for (int i = start; i <= mid; ++i) {
			// Count the number of range sums that lie in [lower, upper].
			while (k <= end && (*sums)[k] - (*sums)[i] < lower) {
				++k;
			}
			while (j <= end && (*sums)[j] - (*sums)[i] <= upper) {
				++j;
			}
			count += j - k;

			// Merge the two sorted arrays into tmp.
			while (r <= end && (*sums)[r] < (*sums)[i]) {
				tmp.emplace_back((*sums)[r++]);
			}
			tmp.emplace_back((*sums)[i]);
		}
		// Copy tmp back to sums.
		copy(tmp.begin(), tmp.end(), sums->begin() + start);
		return count;
	}

	int countRangeSum(vector<int>& nums, int lower, int upper) {
		vector<long long> sums(nums.size() + 1);
		for (int i = 0; i < nums.size(); ++i) {
			sums[i + 1] = sums[i] + nums[i];
		}
		return countAndMergeSort(&sums, 0, (int)sums.size() - 1, lower, upper);
	}
}