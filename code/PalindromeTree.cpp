// Find all distinct palindromes in O(n).
struct PalindromeTree {
  struct Node {
    Node *suffix;   // largest palindromic suffix of this node
    Node *next[26]; // add a letter to the right and left side of the node
    int length;     // length of this palindrome
  };
  Node *rootm1 = new Node();
  Node *root0 = new Node();
  // optional: list of all the palindromes sorted such that a
  // node->suffix comes before node in the list
  vector<Node *> nodes; 
  void init() {
    rootm1->length = -1;
    rootm1->suffix = rootm1;
    root0->length = 0;
    root0->suffix = rootm1;
  }
  Node *makeNode(const string &s, int i, Node *prevNode) {
    Node *newNode = new Node(); // allocate on heap
    char c = s[i];
    prevNode->next[c - 'a'] = newNode;
    newNode->length = prevNode->length + 2;
    if (newNode->length == 1) {
      newNode->suffix = root0;
    } else {
      do {
        prevNode = prevNode->suffix;
      } while (s[i - (prevNode->length + 1)] != c);
      if (!(newNode->suffix = prevNode->next[c - 'a'])) {
        newNode->suffix = makeNode(s, i, prevNode);
      }
    }
    nodes.push_back(newNode);
    return newNode;
  }
  PalindromeTree(string s) {
    init();
    Node *state = rootm1;
    s = '@' + s;
    for (int i = 1; i < s.length(); i++) {
      char c = s[i];
      while (s[i - (state->length + 1)] != c) {
        state = state->suffix;
      }
      Node *endState = state->next[c - 'a'];
      if (!endState) {
        endState = makeNode(s, i, state);
      }
      state = endState;
    }
  }
};