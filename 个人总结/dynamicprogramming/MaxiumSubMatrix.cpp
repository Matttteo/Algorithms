#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//������������ݽṹ
struct Res {
	int sum = 0;
	vector<int> idxs = {0, 0, 0, 0};
};

//�����ƹ㵽Nά�����飬�����Ƕ�ά�����
Res MaxSumSubMatrix(vector<vector<int> >& matrix) {
	Res r;
	int n_rows = matrix.size();
	if (n_rows == 0) {
		return r;
	}
	int n_cols = matrix[0].size();

	vector<vector<int> > sum(n_rows + 1, vector<int>(n_cols, 0));
	sum[0] = vector<int>(n_cols, 0);
	sum[1] = matrix[0];
	for (int i = 2; i <= n_rows; ++i) {
		for (int j = 0; j < n_cols; ++j) {
			sum[i][j] = sum[i - 1][j] + matrix[i - 1][j];
		}
	}

	for (int i = 0; i < n_rows; ++i) {
		for (int j = i; j < n_rows; ++j) {
			vector<int> cur_row(n_cols);
			for (int k = 0; k < n_cols; ++k) {
				cur_row[k] = sum[j + 1][k] - sum[i][k];
			}
			int right = 0;
			int left = 0;
			int cur_sum = 0;
			while (right < n_cols) {
				cur_sum += cur_row[right];
				if (cur_sum > 0) {
					if (r.sum < cur_sum) {
						r.idxs = { i, j, left, right };
					}
					r.sum = max(r.sum, cur_sum);
				}
				else {
					left = right + 1;
					cur_sum = 0;
				}
				right++;
			}
		}
	}
	return r;
}

int main() {
	int M, N;
	cin >> M;
	cin >> N;
	vector<vector<int> > matrix(M, vector<int>(N,0));
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> matrix[i][j];
		}
	}
	Res r = MaxSumSubMatrix(matrix);
	return 0;
}