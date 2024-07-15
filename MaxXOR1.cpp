// Given an integer array nums, return the maximum result of nums[i] XOR nums[j], where 0 <= i <= j < n.

class Node{
public:
    Node *links[2]; // 0 or 1
    bool containsKey(int bit){
        return (links[bit] != NULL);
    }
    void put(int bit, Node *node){
        links[bit] = node;
    }
    Node *get(int bit){
        return links[bit];
    }
};
class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        int n = nums.size();

        Node *root = new Node();

        // insert all nums in trie
        for(auto& it: nums){
            Node* node = root;
            for(int i=31; i>=0; i--){
                int bit = (it>>i) & 1; // i'th bit

                if(!node->containsKey(bit)){
                    node->put(bit, new Node());
                }
                node = node->get(bit);
            }
        }

        // searching for the number with desirable bits in trie and updating maxXor
        int maxXor = 0;
        for(int i=0; i<n; i++){
            int x = nums[i];
            Node *node = root;
            int currXor = 0;

            for(int k=31; k>=0; k--){
                int bit = (x>>k) & 1;

                if(node->containsKey(1-bit)){ // if node contains opposite bit, currXor's k'th bit turns on
                    currXor = currXor | (1<<k);
                    node = node->get(1-bit); // moving to the reference node
                }
                else{
                    node = node->get(bit); // moving to the reference node
                }
            }
            maxXor = max(maxXor, currXor);
        }

        return maxXor;
    }
};