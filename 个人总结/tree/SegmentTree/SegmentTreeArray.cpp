#include <vector>
#include <math.h>
#include <iostream>
using namespace std;

class NumArray {
public:
	NumArray() {};
	NumArray(vector<int>& nums) {
		rawData = nums;
		buildTree(nums);
	}

	void update(int i, int val) {
		int curVal = rawData[i];
		rawData[i] = val;
		int diff = val - curVal;
		if (diff == 0) {
			return;
		}
		int idx = 0;
		while (1) {
			segmentTree[idx][0] += diff;
			int left = segmentTree[idx][1];
			int right = segmentTree[idx][2];
			if (right - left == 0) {
				break;
			}
			else if (i > (right - left) / 2) {
				idx = 2 * idx + 2;
			}
			else {
				idx = 2 * idx + 1;
			}
		}
	}

	int sumRange(int i, int j) {
		return __sumRange(i, j, 0);

	}
private:
	vector<int> rawData;
	vector<vector<int> > segmentTree;
	int __sumRange(int i, int j, int idx) {
		int left = segmentTree[idx][1];
		int right = segmentTree[idx][2];

		if (i > right || j < left) {
			return 0;
		}
		else if (i <= left && j >= right) {
			return segmentTree[idx][0];
		}
		else {
			return __sumRange(i, j, 2 * idx + 1) + __sumRange(i, j, 2 * idx + 1);
		}
	}
	void buildTree(vector<int>& nums) {
		int len = nums.size();
		if (len == 0) {
			return;
		}
		int height = ceil(log2(len));
		segmentTree = vector<vector<int> >((pow(2, height) - 1), vector<int>(0));
		vector<int> addUp(1, 0);
		int sum = 0;
		for (int n : nums) {
			sum += n;
			addUp.push_back(sum);
		}
		segmentTree[0] = { sum, 0, len - 1 };
		for (int i = 0; i < segmentTree.size(); ++i) {
			if (segmentTree[i].size() == 0) {
				continue;
			}
			int left = segmentTree[i][1];
			int right = segmentTree[i][2];
			if (segmentTree[i][2] - segmentTree[i][1] == 0) {
				continue;
			}

			int mid = (right - left) / 2;

			vector<int> leftChild = { addUp[mid + 1] - addUp[left], left, mid };
			vector<int> rightChild = { addUp[right + 1] - addUp[mid + 1], mid + 1, right };
			segmentTree[i * 2 + 1] = leftChild;
			segmentTree[i * 2 + 2] = rightChild;
		}

	}
};


int main() {
	vector<int> vec = { 2,3,5,1,5,3 };
	NumArray n(vec);
	cout << n.sumRange(3, 5) << endl;
	n.update(0, 8);
	n.update(0, 4);
	cout << n.sumRange(3, 3) << endl;
	cout << n.sumRange(0, 4) << endl;
	n.update(4, 0);
	cout << n.sumRange(0, 4) << endl;
	return 0;
}