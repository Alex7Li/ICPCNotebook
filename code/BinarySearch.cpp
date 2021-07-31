// This code is guaranteed to work in the min number of ops
// for any MAX that fits in an ll.
ll MAX = 1LL << 63;
// Binary search integers in the range [0, MAX)
// for the last element satisfying condition.
for (int j = 1LL << (int) (log2(MAX)); j != 0; j >>= 1) {
    if (condition(lo + j)) {
        lo += j;
    }
}
// Binary search integers in the range (1, MAX]
// for the first element satisfying condition.
ll hi = 1LL << (int) (log2(MAX) + 1);
for (int j = 1LL << (int) (log2(MAX)); j != 0; j >>= 1) {
    if (condition(hi - j)) {
        hi -= j;
    }
}
