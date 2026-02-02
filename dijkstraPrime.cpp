#include <bits/stdc++.h>

using namespace std;

struct Node {
    long long next_multiple;
    long long prime;

    bool operator>(const Node& other) const {
        return next_multiple > other.next_multiple;
    }
};

void dijkstraPrimes(long long limit) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    cout << "Prosti broevi do " << limit << ":  " << endl;

    for (long long n = 2; n <= limit; n++) {
        if (pq.empty() || n < pq.top().next_multiple) {
            cout << n << " ";
            
            if (n * n <= limit) {
                pq.push({n * n, n});
            }
        } 
        else {
            while (!pq.empty() && pq.top().next_multiple == n) {
                Node current = pq.top();
                pq.pop();
                current.next_multiple += current.prime;
                pq.push(current);
            }
        }
    }
    cout << endl;
}

int main() {
    long long n;
    cout << "Limit ";
    cin >> n;

    dijkstraPrimes(n);

    return 0;
}