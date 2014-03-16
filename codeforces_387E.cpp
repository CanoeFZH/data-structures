#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 1000086;

int position[N], c[N];
bool keep[N];
set <int> keep_set;

int add(int x, int delta) {
    for (; x < N; x += x & -x) {
        c[x] += delta;
    }
}

int sum(int x) {
    int ret = 0;
    for(; x > 0; x -= x & -x) {
        ret += c[x];
    }
    return ret;
}

int main() {
    int n, m;
    while (cin >> n >> m) { 
        keep_set.clear();
        memset(c, 0, sizeof(c));
        memset(keep, false, sizeof(keep));
        int x;
        for (int i = 1; i <= n; i++) {
            cin >> x;
            position[x] = i;
            add(i, 1);
        }
        for (int i = 1; i <= m; i++) {
            cin >> x;
            keep[x] = true;
        }
        long long ans = 0;
        keep_set.insert(0);
        keep_set.insert(n + 1);
        for (int i = 1; i <= n; i++) {
            if (keep[i]) {
                keep_set.insert(position[i]);
            } else { 
                auto l = keep_set.upper_bound(position[i]);
                auto r = l--;
                ans += sum(*r - 1) - sum(*l);
                add(position[i], -1);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
