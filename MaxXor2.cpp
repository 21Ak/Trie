// You are given an array nums consisting of non-negative integers. 
// You are also given a queries array, where queries[i] = [xi, mi].

// The answer to the ith query is the maximum bitwise XOR value of xi and any element of nums that does not exceed mi.
//  In other words, the answer is max(nums[j] XOR xi) for all j such that nums[j] <= mi. 
//  If all elements in nums are larger than mi, then the answer is -1.

// Return an integer array answer where answer.length == queries.length and answer[i] is the answer to the ith query.

#include <vector>
#include <algorithm>
using namespace std;

// Node structure for Trie
struct Node {
    Node *links[2] = {nullptr, nullptr};  // Links to the next nodes (0 or 1)

    bool containsKey(int bit) {
        return links[bit] != nullptr;
    }

    Node* get(int bit) {
        return links[bit];
    }

    void put(int bit, Node* node) {
        links[bit] = node;
    }
};

// Trie structure
class Trie {
private:
    Node *root;
public:
    Trie() {
        root = new Node();
    }

    // Function to insert a number into the Trie
    void insertNum(int num) {
        Node *node = root;
        for (int i = 30; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!node->containsKey(bit)) {
                node->put(bit, new Node());
            }
            node = node->get(bit);
        }
    }

    // Function to get the maximum XOR for a given number
    int getMax(int num) {
        Node *node = root;
        if (!node) return -1;
        int maxXor = 0;
        for (int i = 30; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (node->containsKey(1 - bit)) {
                maxXor |= (1 << i);  // Set the i-th bit of maxXor
                node = node->get(1 - bit);
            } else {
                node = node->get(bit);
            }
        }
        return maxXor;
    }
};

class Solution {
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        // Sort the nums array
        sort(nums.begin(), nums.end());

        // Prepare queries with their original indices
        vector<vector<int>> Q;
        for (int i = 0; i < queries.size(); ++i) {
            Q.push_back({queries[i][1], queries[i][0], i});
        }

        // Sort queries based on their limits
        sort(Q.begin(), Q.end());

        Trie trie;
        vector<int> result(queries.size());
        int index = 0;

        // Processing each query
        for (auto& q : Q) {
            int limit = q[0];
            int x = q[1];
            int originalIndex = q[2];

            // Insert numbers into the Trie while they are within the current limit
            while (index < nums.size() && nums[index] <= limit) {
                trie.insertNum(nums[index]);
                ++index;
            }

            // If no numbers in Trie, return -1 for this query
            if (index == 0) {
                result[originalIndex] = -1;
            } else {
                // Get the maximum XOR value for the current query
                result[originalIndex] = trie.getMax(x);
            }
        }

        // Return the results in the order of original queries
        return result;
    }
};