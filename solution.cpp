#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;

struct Interval {
    int l, r;
    
    Interval(int left, int right) : l(left), r(right) {}
    
    bool operator<(const Interval& other) const {
        if (l != other.l) return l < other.l;
        return r < other.r;
    }
};

bool overlaps(const Interval& a, const Interval& b) {
    return max(a.l, b.l) <= min(a.r, b.r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    set<Interval> activities;
    
    for (int i = 0; i < n; i++) {
        char op;
        cin >> op;
        
        if (op == 'A') {
            int l, r;
            cin >> l >> r;
            
            Interval new_interval(l, r);
            int removed_count = 0;
            
            // Find intervals that overlap with [l, r]
            auto it = activities.lower_bound(Interval(l, -1));
            
            // Check intervals starting from or after l
            vector<Interval> to_remove;
            for (auto curr = it; curr != activities.end() && curr->l <= r; ++curr) {
                if (overlaps(*curr, new_interval)) {
                    to_remove.push_back(*curr);
                }
            }
            
            // Check intervals starting before l
            if (it != activities.begin()) {
                auto curr = it;
                --curr;
                while (true) {
                    if (overlaps(*curr, new_interval)) {
                        to_remove.push_back(*curr);
                    }
                    if (curr == activities.begin()) break;
                    --curr;
                }
            }
            
            // Remove overlapping intervals
            for (const auto& interval : to_remove) {
                activities.erase(interval);
                removed_count++;
            }
            
            // Add the new activity
            activities.insert(new_interval);
            
            cout << removed_count << '\n';
        } else if (op == 'B') {
            cout << activities.size() << '\n';
        }
    }
    
    return 0;
}