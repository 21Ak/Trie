// Problem statement
// Ninja developed a love for arrays and strings so this time 
// his teacher gave him an array of strings, ‘A’ of size ‘N’. 
// Each element of this array is a string. The teacher taught Ninja 
// about prefixes in the past, so he wants to test his knowledge.

// A string is called a complete string 
// if every prefix of this string is also present in the array ‘A’. 
// Ninja is challenged to find the longest complete string in the array ‘A’.
// If there are multiple strings with the same length, 
// return the lexicographically smallest one 
// and if no string exists, return "None".

#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node* links[26];
    bool flag = false;

    bool containsKey(char ch) {
        return (links[ch - 'a'] != NULL);
    }

    void put(char ch, Node* node) {
        links[ch - 'a'] = node;
    }

    Node* get(char ch) {
        return links[ch - 'a'];
    }

    void setEnd() {
        flag = true;
    }

    bool isEnd() {
        return flag;
    }
};

class Trie {
private:
    Node* root;

public:
    Trie() {
        root = new Node();
    }

    void insertWord(string& word) {
        Node* node = root;
        for (int i = 0; i < word.size(); i++) {
            if (!node->containsKey(word[i])) {
                node->put(word[i], new Node());
            }
            node = node->get(word[i]);
        }
        node->setEnd();
    }

    bool startsWith(string& word) {
        Node* node = root;
        for (int i = 0; i < word.size(); i++) {
            if (!node->containsKey(word[i])) {
                return false;
            }
            else{
                node = node->get(word[i]);
                if(node->isEnd()==false){ // checking for all the prefixes of word
                    return false;
                }
            }
        }
        return true;
    }
};

string completeString(int n, vector<string>& a) {
    Trie ts;
    for (auto it : a) {
        ts.insertWord(it);
    }

    string ans = "";
    for (auto it : a) {
        if(ts.startsWith(it)){
            if (it.size() > ans.size()) {
                ans = it;
            } else if (it.size() == ans.size() && it < ans) {
                ans = it;
            }
        }
    }

    return ans == "" ? "None" : ans;
}