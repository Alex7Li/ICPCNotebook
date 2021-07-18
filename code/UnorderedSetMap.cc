// An example of policy hashtable with a custom object in cpp. It is
// it is better than the built in unordered_map in that
// it is ~5 times faster. (https://codeforces.com/blog/entry/60737)
// No real downsides (normal map is just as annoying with custom objects),
// but be careful with the hash function, the number of buckets is a power of 2.
#include <bits/stdc++.h>
using namespace std;

struct Coordinate {
    int x;
    int y;
    bool operator==(const Coordinate &other) const {
        return x == other.x && y == other.y;
    }
};

ostream &operator<<(ostream &stream, const Coordinate &l) {
    return stream << "{" << l.x << " " << l.y << "}";
}
#include <ext/pb_ds/assoc_container.hpp>

struct chash {
    static auto const c = uint64_t(7e18) + 13; // Big prime
    uint64_t operator()(const Coordinate &l) const {
        return __builtin_bswap64((l.x + l.y) * c);
    }
};

template<class k, class v>
using hash_map = __gnu_pbds::gp_hash_table<k, v, chash>;
template<class k>
using hash_set = __gnu_pbds::gp_hash_table<k, __gnu_pbds::null_type, chash>;
template<typename k, typename v>
bool contains(hash_map<k, v> map, k val) {
    return map.find(val) != map.end();
}

int main() {
    // After importing, writing the template code, overloading ==
    // and << (print) operator like above, you can use the map
    hash_map<Coordinate, int> my_map;
    my_map[{1, 2}] = 17;
    cout << my_map[{1, 2}] << endl; // Prints 17
    assert(contains(my_map, {1, 2}));
    assert(!contains(my_map, {3, 4}));
    cout << my_map[{3, 4}] << endl; // Prints 0
    assert(my_map.size() == 2); // We just set {3, 4} to 0 by accessing it.
    for (auto pair : my_map) {
        cout << pair.first << "=" << pair.second << " "; // {3 4}=0 {1 2}=17
    }

    hash_set<Coordinate> my_set;
    assert(my_set.empty());
    my_set.insert({1, 2});
    assert(contains(my_set, {1, 2}));
    my_set.insert({4, 5});
    // hash_set does the correct thing, and when you iterate over it you get keys,
    // not key-value pairs with a null value.
    for (auto it = my_set.begin(); it != my_set.end(); it++) {
        cout << *it << " ";  // print {4, 5} {1, 2}.
    }
    // Standard C Library Equivalent Declarations:
    // unordered_map<Coordinate, int, chash> my_map;
    // unordered_set<Coordinate, chash> my_set;
}