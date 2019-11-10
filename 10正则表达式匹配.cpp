#给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。
#'.' 匹配任意单个字符
#'*' 匹配零个或多个前面的那一个元素

class Solution {
    struct Node {
        char a;
        bool ok;
        bool operator==(char b) {
            if (a == b || a == '.')
                return true;
            else
                return false;
        }
        Node(char a, bool ok=false): a(a), ok(ok) {}
    };   
public:
    bool isMatch(string s, string p) {
        if (s.empty() && p.empty())
            return true;
        int p_len = p.length();
        vector<Node> rec;
        for (int i = 0; i < p_len;) {
            auto w = p[i];
            if (i + 1 < p_len && p[i + 1] == '*') {
                rec.push_back(Node(w, true));
                i = i + 2;
            } else {
                rec.push_back(Node(w));
                i++;
            }
        }
        p_len = rec.size();
        int s_len = s.length();
        vector<vector<bool>> dp = vector<vector<bool>>(s_len + 1, vector<bool>(p_len + 1, false));
        for (int i = 0; i < s_len + 1; i++) {
            for (int j = 0; j < p_len + 1; j++) {
                if (i == 0 && j == 0)
                    dp[i][j] = true;
                else if (j == 0)
                    dp[i][j] = false;
                else if (i == 0)
                    dp[i][j] = dp[i][j - 1] && rec[j - 1].ok;
                else {
                    if (!rec[j - 1].ok) {
                        dp[i][j] = dp[i - 1][j - 1] && (rec[j - 1] == s[i - 1]);
                        continue;
                    }
                    bool tmp = false;
                    int k = i - 1;
                    while (k >= 0 && !tmp && (rec[j - 1] == s[k])) {
                        tmp = tmp || dp[k][j - 1];
                        k--;
                    }
                    dp[i][j] = tmp;
                    dp[i][j] = dp[i][j - 1] || dp[i][j];
                }
            }
        }
      
        return dp[s_len][p_len];
    }
};
    
