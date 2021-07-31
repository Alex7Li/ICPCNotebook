// This code is guaranteed to work in the min number of ops
// for any MAX that fits in an ll.
ll MAX = 1LL << 62;
// Binary search integers in the range [0, MAX] (or higher)
// for the last element satisfying condition.
ll lo = 0
for (ll j = 1LL << (ll) (log2(MAX)); j != 0; j >>= 1) {
    if (condition(lo + j)) {
        lo += j;
    }
}
// Binary search integers in the range (1, MAX] (or higher)
// for the first element satisfying condition.
ll hi = 1LL << (ll) (log2(MAX) + 1);
for (ll j = 1LL << (ll) (log2(MAX)); j != 0; j >>= 1) {
    if (condition(hi - j)) {
        hi -= j;
    }
}
// Search list[lo:hi], targets occur at list[bisect_left:bisect_right]
while (lo < hi) { // bisect_right
    mid = lo + (hi - lo) / 2;
    if (target < list[mid]) { hi = mid; }
    else { lo = mid + 1; }
} return lo;
while (lo < hi) { // bisect_left
    mid = lo + (hi - lo) / 2;
    if (list[mid] < target) { lo = mid + 1; }
    else { hi = mid; }
} return lo;