#include <vector>
#include <string>

class Solution {
public:
    std::vector<int> validSequence(std::string word1, std::string word2) {
        int n = word1.length();
        int m = word2.length();
        
        std::vector<int> last(m, -1);
        int ptr = n - 1;
        
        for (int j = m - 1; j >= 0; --j) {
            while (ptr >= 0 && word1[ptr] != word2[j]) {
                ptr--;
            }
            if (ptr >= 0) {
                last[j] = ptr;
                ptr--;
            }
        }
        
        std::vector<int> ans;
        int j = 0;
        bool changed = false;
        
        for (int i = 0; i < n && j < m; ++i) {
            
            if (word1[i] == word2[j]) {
                ans.push_back(i);
                j++;
            } 

            else if (!changed) {
                
                if (j == m - 1 || last[j + 1] > i) {
                    ans.push_back(i);
                    j++;
                    changed = true;
                }
            }
        }
        
        return ans.size() == m ? ans : std::vector<int>();
    }
};
