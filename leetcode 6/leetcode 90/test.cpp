class Solution {
public:
    vector<vector<int> > subsetsWithDup(vector<int> &S) {
        vector<vector<int> > result;
        map<vector<int>, bool> m;
        int size = S.size();
        for(int i = 0; i < pow(2.0, size); i ++)
        {
            int tag = i;
            vector<int> cur;
            for(int j = size-1; j >= 0; j --)
            {
                if(!tag)
                    break;
                if(tag%2 == 1)
                {
                    cur.push_back(S[j]);
                }
                tag >>= 1;
            }
            sort(cur.begin(), cur.end());
            if(m.find(cur) == m.end()) 
            {
                m[cur] = true;
                result.push_back(cur);
            }
        }
        return result;
    }
};