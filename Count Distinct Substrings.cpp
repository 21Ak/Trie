// Given a string 'S', you are supposed to return 
// the number of distinct substrings(including empty substring) 
// of the given string. 
// You should implement the program using a trie.

#include "bits/stdc++.h"
class Node{
public:
    Node *links[26];

    bool containsKey(char ch){
        return links[ch-'a'] != NULL;
    }
    void put(char ch, Node *node){
        links[ch-'a'] = node;
    }
    Node *get(char ch){
        return links[ch-'a'];
    }

};
int countDistinctSubstrings(string &s)
{
    int cnt = 0;
    Node* root = new Node();

    for(int i=0; i<s.size(); i++){
        Node* node = root;
        for(int j=i; j<s.size(); j++){
            if(!node->containsKey(s[j])){
                cnt++;
                node->put(s[j], new Node());
            }
            node = node->get(s[j]);
        }
    }

    return cnt+1;
}