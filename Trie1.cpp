#include "bits/stdc++.h"
struct Node{
    Node *links[26];
    bool flag = false;

    bool containsKey(char ch){
        return (links[ch-'a'] != NULL); // returns true if at that node, the character already exists
    }
    void put(char ch, Node *node){
        links[ch-'a'] = node; // pointing to a new reference node
    }
    Node* get(char ch){
        return links[ch-'a'];
    } 
    void setEnd(){
        flag = true; // at the end of the word, sets the reference trie to be true, indiciating its end
    }
    bool isEnd(){ // return whether the word is complete or not
        return flag;
    }
};

class Trie {
private:
    Node *root;
public:
    Trie() {
        root = new Node(); // creating new root everytime a new object of trie class is instantiated 
    }
    
    // tc : O(word.size())
    void insert(string word) {
        Node* node = root; // initially pointing to root
        // inserting every character of word
        for(int i=0; i<word.size(); i++){
            if(!node->containsKey(word[i])){ // if the current node, does not contain word[i] character
                node->put(word[i], new Node()); // inserting word[i] and creating a new refercnce node for it
            }
            node = node->get(word[i]); // moving to the referece trie node
        }
        node->setEnd(); // setting the last reference node
    }
    
    // tc : O(word.size())
    bool search(string word) {
        Node *node = root;
        for(int i=0; i<word.size(); i++){
            if(!node->containsKey(word[i])){ // if word[i] doesn't exist in current trie, return false
                return false;
            }
            node = node->get(word[i]); // getting to word[i] reference trie
        }
        // if last reference node is true, it means complete word exists
        return node->isEnd();
    }
    
    // tc : O(prefix.size())
    bool startsWith(string prefix) {
        Node *node = root;
        for(int i=0; i<prefix.size(); i++){
            if(!node->containsKey(prefix[i])){ // if prefix[i] doesn't exist, it means no word has prefix = prefix
                return false;
            }
            node = node->get(prefix[i]); // go to its reference node
        }
        // if we are able to find all characters of prefix, it means even if the word is incomplete, the prefix exists
        // so return true;
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */