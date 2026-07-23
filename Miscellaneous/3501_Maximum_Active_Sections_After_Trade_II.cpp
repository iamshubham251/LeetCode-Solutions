class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.size();
        vector<int> val, st_, en, len;
        {
            int i = 0;
            while (i < n) {
                int j = i;
                while (j < n && s[j] == s[i]) j++;
                val.push_back(s[i] - '0');
                st_.push_back(i);
                en.push_back(j - 1);
                len.push_back(j - i);
                i = j;
            }
        }
        int m = val.size();

        const long long POS = LLONG_MAX / 4;
        const long long NEG = LLONG_MIN / 4;

        vector<long long> arrA(m), arrZ(m), arrB(m, NEG);
        for (int i = 0; i < m; i++) {
            arrA[i] = (val[i] == 1) ? len[i] : POS;  
            arrZ[i] = (val[i] == 0) ? len[i] : NEG;  
        }
        for (int i = 1; i < m - 1; i++)
            if (val[i] == 1) arrB[i] = (long long)len[i - 1] + len[i + 1];
        vector<int> logt(m + 1, 0);
        for (int i = 2; i <= m; i++) logt[i] = logt[i / 2] + 1;
        int K = (m > 0) ? logt[m] + 1 : 1;

        vector<vector<long long>> stMin(K, vector<long long>(max(m,1)));
        vector<vector<long long>> stMaxZ(K, vector<long long>(max(m,1)));
        vector<vector<long long>> stMaxB(K, vector<long long>(max(m,1)));
        if (m > 0) {
            stMin[0] = arrA; stMaxZ[0] = arrZ; stMaxB[0] = arrB;
            for (int k = 1; k < K; k++) {
                int half = 1 << (k - 1);
                for (int i = 0; i < m; i++) {
                    if (i + half < m) {
                        stMin[k][i]  = min(stMin[k-1][i],  stMin[k-1][i+half]);
                        stMaxZ[k][i] = max(stMaxZ[k-1][i], stMaxZ[k-1][i+half]);
                        stMaxB[k][i] = max(stMaxB[k-1][i], stMaxB[k-1][i+half]);
                    } else {
                        stMin[k][i] = stMin[k-1][i];
                        stMaxZ[k][i] = stMaxZ[k-1][i];
                        stMaxB[k][i] = stMaxB[k-1][i];
                    }
                }
            }
        }

        auto qMin = [&](int lo, int hi) -> long long {
            if (lo > hi) return POS;
            int k = logt[hi - lo + 1];
            return min(stMin[k][lo], stMin[k][hi - (1 << k) + 1]);
        };
        auto qMaxZ = [&](int lo, int hi) -> long long {
            if (lo > hi) return NEG;
            int k = logt[hi - lo + 1];
            return max(stMaxZ[k][lo], stMaxZ[k][hi - (1 << k) + 1]);
        };
        auto qMaxB = [&](int lo, int hi) -> long long {
            if (lo > hi) return NEG;
            int k = logt[hi - lo + 1];
            return max(stMaxB[k][lo], stMaxB[k][hi - (1 << k) + 1]);
        };

        long long totalOnes = count(s.begin(), s.end(), '1');
        vector<int> ans;
        ans.reserve(queries.size());

        for (auto& qr : queries) {
            int l = qr[0], r = qr[1];
            int p = (int)(upper_bound(st_.begin(), st_.end(), l) - st_.begin()) - 1;
            int q = (int)(upper_bound(st_.begin(), st_.end(), r) - st_.begin()) - 1;

            long long gain = 0;
            if (p != q) {
                long long cL = en[p] - l + 1;
                long long cR = r - st_[q] + 1;
                int numMid = q - p - 1;

                if (numMid == 0) {
                    gain = 0;
                } else if (numMid == 1) {
                    int mid = p + 1;
                    if (val[mid] == 1) {
                        long long minA = len[mid], pairSum = cL + cR, mz = NEG;
                        if (val[p] == 0) mz = max(mz, cL);
                        if (val[q] == 0) mz = max(mz, cR);
                        long long cand = (mz != NEG) ? (mz - minA) : NEG;
                        gain = max({0LL, cand, pairSum});
                    }
                } else {
                    long long minA = qMin(p + 1, q - 1);
                    if (minA != POS) {
                        long long mz = qMaxZ(p + 1, q - 1);
                        if (val[p] == 0) mz = max(mz, cL);
                        if (val[q] == 0) mz = max(mz, cR);

                        long long pair_p1  = (val[p+1] == 1) ? cL + len[p+2] : NEG;
                        long long pair_qm1 = (val[q-1] == 1) ? (long long)len[q-2] + cR : NEG;
                        long long maxPairFull = (p+2 <= q-2) ? qMaxB(p+2, q-2) : NEG;

                        long long maxPair = max({pair_p1, pair_qm1, maxPairFull});
                        long long cand = (mz != NEG) ? (mz - minA) : NEG;
                        gain = max({0LL, cand, maxPair});
                    }
                }
            }
            ans.push_back((int)(totalOnes + gain));
        }
        return ans;
    }
};
