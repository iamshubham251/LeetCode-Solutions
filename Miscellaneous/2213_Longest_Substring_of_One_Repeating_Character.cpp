class Solution {
public:
    struct Node {
        int len = 0;
        char lc = 0, rc = 0;
        int pre = 0, suf = 0, best = 0;
    };
    vector<Node> tree;
    string str;
    Node merge(const Node& L, const Node& R) {
        Node res;
        res.len = L.len + R.len;
        res.lc = L.lc;
        res.rc = R.rc;
        res.pre = L.pre;
        if (L.pre == L.len && L.rc == R.lc) {
            res.pre += R.pre;
        }
        res.suf = R.suf;
        if (R.suf == R.len && R.lc == L.rc) {
            res.suf += L.suf;
        }
        res.best = max(L.best, R.best);
        if (L.rc == R.lc) {
            res.best = max(res.best, L.suf + R.pre);
        }
        return res;
    }
    void build(int node, int start, int end) {
        if (start == end) {
            char c = str[start];
            tree[node] = {1, c, c, 1, 1, 1};
            return;
        }
        int mid = (start + end) / 2;
        build(2*node, start, mid);
        build(2*node+1, mid+1, end);
        tree[node] = merge(tree[2*node], tree[2*node+1]);
    }
    void update(int node, int start, int end, int idx, char ch) {
        if (start == end) {
            tree[node] = {1, ch, ch, 1, 1, 1};
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid) update(2*node, start, mid, idx, ch);
        else update(2*node+1, mid+1, end, idx, ch);
        tree[node] = merge(tree[2*node], tree[2*node+1]);
    }
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        str = s;
        int n = s.size();
        tree.assign(4 * n, Node());
        build(1, 0, n - 1);
        int k = queryCharacters.size();
        vector<int> ans(k);
        for (int i = 0; i < k; i++) {
            int idx = queryIndices[i];
            char ch = queryCharacters[i];
            if (str[idx] != ch) {
                str[idx] = ch;
                update(1, 0, n - 1, idx, ch);
            }
            ans[i] = tree[1].best;
        }
        return ans;
    }
};
