// An example of using an ordered map with a custom object.
// Also include code for the gnu policy tree, which gives
// a easy (~2x slower) segment tree by implementing
// find_by_order and order_of_key
#include <bits/stdc++.h>

using namespace std;

struct Coordinate {
    int x;
    int y;

    // Overloaded for ordered map. If !(c1<c2), !(c2<c1), then
    // c1 will be considered equal to c2.
    bool operator<(const Coordinate &o) const {
        return x == o.x ? y < o.y : x < o.x;
    }
};

ostream &operator<<(ostream &stream, const Coordinate &l) {
    return stream << "{" << l.x << " " << l.y << "}";
}

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
template<class k, class v>
using ordered_map = tree<k, v, less<k>,
        rb_tree_tag, // Red black tree. Can use splay_tree_tag for a splay tree,
        // but split operation for splay is linear time so it may be terrible.
        tree_order_statistics_node_update // To get find_by_order and order_of_key methods
>;
template<class k> // Same as ordered map almost
using ordered_set = tree<k, null_type, less<k>,
        rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    map<Coordinate, int> c_map; // Standard C Library Ordered Map
    set<Coordinate> c_set; // Standard C Library Ordered Set
    ordered_map<Coordinate, int> gnu_map; // Gnu map declaration
    ordered_set<Coordinate> gnu_set;// Gnu set declaration
    for (int i = 0; i < 10; i++) {
        gnu_set.insert({0, i*10});
    }
    cout << *gnu_set.find({0, 30}) << endl; // {0, 30}
    cout << *gnu_set.lower_bound({0, 53}) << endl; // {0, 60}
    cout << *gnu_set.upper_bound({0, 53}) << endl; // {0, 60}
    cout << *gnu_set.lower_bound({0, 50}) << endl; // {0, 50}
    cout << *gnu_set.upper_bound({0, 50}) << endl; // {0, 60}
    // Example of the operations only supported by gnu_set
    cout << *gnu_set.find_by_order(2) << endl; // {0 20}
    cout << *gnu_set.find_by_order(4) << endl; // {0 40}
    assert(end(gnu_set) == gnu_set.find_by_order(10));
    cout << gnu_set.order_of_key({0, -99}) << endl; // 0
    cout << gnu_set.order_of_key({0, 0}) << endl; // 0
    cout << gnu_set.order_of_key({0, 11}) << endl; // 2
    cout << gnu_set.order_of_key({0, 999}) << endl; // 10
}