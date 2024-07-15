#include <bits/stdc++.h> 
struct Node{
    Node *links[26];
    int endWith = 0;
    int cntPre = 0;

    bool containsKey(char ch){
        return (links[ch-'a']!=NULL);
    }
    void put(char ch, Node *node){
        links[ch-'a'] = node;
    }
    Node* get(char ch){
        return links[ch-'a'];
    }
    void increaseEnd(){
        endWith++;
    }
    void increasePrefix(){
        cntPre++;
    }
    void deleteEnd(){
        endWith--;
    }
    void reducePrefix(){
        cntPre--;
    }
    
};

class Trie{
private:
    Node *root;
public:

    Trie(){
        root = new Node();
    }

    void insert(string &word){
        Node *node = root;
        for(int i=0; i<word.size(); i++){
            if(!node->containsKey(word[i])){
                node->put(word[i], new Node());
            }
            node = node->get(word[i]);
            node->increasePrefix();
        }
        node->increaseEnd();
    }

    int countWordsEqualTo(string &word){
        Node *node = root;
        for(int i=0; i<word.size(); i++){
            if(!node->containsKey(word[i])){
                return 0;
            }
            node = node->get(word[i]);
        }
        return node->endWith;
    }

    int countWordsStartingWith(string &word){
        Node *node = root;
        for(int i=0; i<word.size(); i++){
            if(!node->containsKey(word[i])){
                return 0;
            }
            node = node->get(word[i]);
        }
        return node->cntPre;
    }

    void erase(string &word){
        Node *node = root;
        for(int i=0; i<word.size(); i++){
            if(!node->containsKey(word[i])){
                return; // word already doesn't exists
            }
            node = node->get(word[i]);
            node->reducePrefix();
        }
        node->deleteEnd();
    }
};
