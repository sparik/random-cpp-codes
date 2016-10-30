#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// multiply a and b modulo m in O(log(b))
long long multmod (long long a, long long b, long long m) {
	long long res = 0;

	while (b) {
		if (b&1) {
			res = (res+a)%m;
		}
		a = (a+a)%m;
		b /= 2;
	}

	return res;
}

// calculate  (a^p)%m in O(log^2(p))
// additional log factor is due tue multiplication of large numbers
long long powmod(long long a, long long p, long long m) {
	long long res = 1;

	while (p) {
		if (p&1) {
			res = multmod(res, a, m);
		}
		a = multmod(a, a, m);
		p /= 2;
	}

	return res;
}

// get a random nonnegative integer in range [a;b)
long long getRand(long long a, long long b) {
	return a + (((rand()*1ull) << 48UL) + ((rand()*1ull) << 32UL)
			 + ((rand()*1ull << 16UL)) + rand()) % (b - a);
}

// test primality by simple trial division in O(sqrt(n))
bool checkPrimeNaive(long long n) {
	for (int i = 2; i*1ll*i <= n; ++i) {
		if (n % i == 0) {
			return false;
		}
	}

	return true;
}

// test primality by Miller-Rabin test
bool checkPrime(long long n, int k = 15) {
	if (n < 100) {
		return checkPrimeNaive(n);
	}

	long long d = n - 1;

	int r = 0;
	while (d % 2 == 0) {
		++r;
		d /= 2;
	}
	// n = d*2^r

	while (k--) {
		// generate a random witness in range [2, n - 1]
		long long a = getRand(2, n - 1);

		long long x = powmod(a, d, n);

		if (x == 1 || x == n - 1) {
			continue;
		}

		bool found = true;

		for (int i = 0; i < r - 1; ++i) {
			x = multmod(x, x, n);
			if (x == n - 1) {
				found = false;
				break;
			}
		}

		if (found) {
			return false;
		}
	}

	return true;
}

int main() {
	srand(time(0));

	long long n = getRand(1e9, 1e18);

	while (checkPrime(n) == false) {
		n = getRand(1e9, 1e18);
	}

	printf("%lld", n);

	return 0;
}