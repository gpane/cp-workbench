#ifndef CPP_PRIME_SIEVE_HPP
#define CPP_PRIME_SIEVE_HPP

#include <vector>

#define ll long long

using namespace std;

struct prime_sieve {
public:
    prime_sieve(int n) {
        MAXN = n;
        // smallest_prime_factor[i << 1] = smallest prime factor of i
        // smallest_prime_factor[i << 1 | 1] = i / smallest_prime_factor[i << 1]
        smallest_prime_factor = vector<int>(2 * MAXN + 2, 0);
        for (int i = 2; i <= MAXN; i++) {
            int spf = smallest_prime_factor[i << 1];
            if (spf == 0) {
                smallest_prime_factor[i << 1] = i;
                smallest_prime_factor[i << 1 | 1] = 1;
                spf = i;
                primes.push_back(i);
            }
            for (int p : primes) {
                if (p > spf) break;
                ll prod = (ll) p * i;
                if (prod > MAXN) break;
                smallest_prime_factor[prod << 1] = p;
                smallest_prime_factor[prod << 1 | 1] = i;
            }
        }
    }

    bool is_prime(int x) {
        assert(x <= MAXN);
        return smallest_prime_factor[x << 1] == x;
    }

    vector<int> prime_factorization(int x) {
        vector<int> ans;
        int curr = x;
        while (curr > 1) {
            ans.push_back(smallest_prime_factor[curr << 1]);
            curr = smallest_prime_factor[curr << 1 | 1];
        }
        return ans;
    }

    // prime, exp
    map<int, int> prime_factorization_map(int x) {
        map<int, int> prime_factors;
        int curr = x;
        while (curr > 1) {
            prime_factors[smallest_prime_factor[curr << 1]]++;
            curr = smallest_prime_factor[curr << 1 | 1];
        }
        return prime_factors;
    }

    // includes 1 and x
    int count_divisors(int x) {
        map<int, int> prime_factors = prime_factorization_map(x);
        int ans = 0;
        for (auto& [_, freq] : prime_factors) ans += freq * (ans + 1);
        return ans + 1;
    }

  private:
    int MAXN;
    vector<int> smallest_prime_factor;
    vector<int> primes;
};

#endif // CPP_PRIME_SIEVE_HPP