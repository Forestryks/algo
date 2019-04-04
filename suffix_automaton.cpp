#include <bits/stdc++.h>
using namespace std;

namespace automaton {
	const int MAXN = 5e5 + 5;

	int sz, last;
	int len[MAXN], link[MAXN];
	map<char, int> to[MAXN];

	void init() {
		sz = 1;
		last = 0;
		len[0] = 0;
		link[0] = -1;
	}

	void extend(char ch) {
		int v = sz++;
		len[v] = len[last] + 1;

		int p;
		for (p = last; p != -1 && !to[p].count(ch); p = link[p]) {
			to[p][ch] = v;
		}

		if (p == -1) {
			link[v] = 0;
		} else {
			int q = to[p][ch];
			if (len[p] + 1 == len[q]) {
				link[v] = q;
			} else {
				len[sz] = len[p] + 1;
				to[sz] = to[q];
				link[sz] = link[q];
				for (; p != -1 && to[p][ch] == q; p = link[p]) {
					to[p][ch] = sz;
				}

				link[q] = link[v] = sz;
			}
		}
		last = v;
	}
};

int main() {
	string s;
	cin >> s;

	automaton::init();
	for (auto ch : s) {
		automaton::extend(ch);
	}
}