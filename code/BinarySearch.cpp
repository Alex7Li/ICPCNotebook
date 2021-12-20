// This code is guaranteed to work in the min number of ops
// for any MAX that fits in an ll.
ll MAX = 1LL << 62;
// Binary search integers in the range [0, MAX] (or higher)
// for the last element satisfying condition.
ll lo = 0;
for (ll j = 1LL << (ll)(log2(MAX)); j != 0; j >>= 1)
{ if (condition(lo + j)) { lo += j; } }
