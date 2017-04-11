#include <iostream>
#include <vector>
using namespace std;

vector< vector<int> > parityCheckTranspose = {
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1},
        {0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1},
        {0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
        {0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1},
        {1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1},
        {1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1},
        {0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1},
        {1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1},
        {0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}
};

vector < vector<int> > P = {
        {1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1},
        {0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1},
        {0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
        {0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1},
        {1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1},
        {1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1},
        {0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1},
        {1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1},
        {0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}
};

vector < vector<int> > u = {
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
};

vector<int> vectorMatrixMult(const vector<int> &vec, vector< vector<int> > mat) {
	int n = mat[0].size();

	vector <int> res(n);
	for (int i = 0; i < n; ++i) {
		res[i] = 0;
		for (int j = 0; j < vec.size(); ++j) {
			res[i] += vec[j] * mat[j][i];
		}
		res[i] %= 2;
	}

	return res;
}

int weight(const vector <int> &vec) {
	int res = 0;
	for (int i = 0; i < vec.size(); ++i) {
		res += vec[i];
	}

	return res;
}

vector <int> add(const vector <int> &a, const vector <int> &b) {
	vector <int> res(a.size());

	for (int i = 0; i < (int)a.size(); ++i) {
		res[i] = a[i] + b[i];
		if (res[i] == 2) {
			res[i] = 0;
		}
	}

	return res;
}

vector <int> concat(const vector <int> &a, const vector <int> &b) {
	vector <int> res(a.size() + b.size());

	for (int i = 0; i < (int)a.size(); ++i) {
		res[i] = a[i];
	}
	for (int i = 0; i < (int)b.size(); ++i) {
		res[(int)a.size() + i] = b[i];
	}

	return res;
}

vector <int> zero = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

vector <int> golay_decode(const vector <int> &seq) {
	vector <int> syndrome = vectorMatrixMult(seq, parityCheckTranspose);
	vector <int> e;


	if (weight(syndrome) <= 3) {
		e = concat(syndrome, zero);

		return add(seq, e);
	}
	
	for (int i = 0; i < 12; ++i) {
		vector <int> spi = add(syndrome, P[i]);

		if (weight(spi) <= 2) {
			e = concat(spi, u[i]);
			return add(seq, e);
		}
	}


	vector <int> sp = vectorMatrixMult(syndrome, P);

	if (weight(sp) == 2 || weight(sp) == 3) {
		e = concat(zero, sp);

		return add(seq, e);
	}

	for (int i = 0; i < 12; ++i) {
		vector <int> sppi = add(sp, P[i]);

		if (weight(sppi) == 2) {
			e = concat(u[i], sppi);
			return add(seq, e);
		}
	}

	return {};
}

int main() {

	vector <int> inputSeq(24);

	cout << "enter the sequence of 24 space-separated 0/1 bits\n";
	for (int i = 0; i < 24; ++i) {
		cin >> inputSeq[i];
	}

	vector <int> decoded = golay_decode(inputSeq);


	if (decoded.size() == 0) {
		cout << "decoding failure" << endl;
		return 0;
	}
	cout << "decoded\n";
	for (int i = 0; i < 24; ++i) {
		cout << decoded[i] << " ";
	}
	
	return 0;
}
