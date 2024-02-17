

// Macro
#pragma once

// Headers
#include<iostream>
#include<string.h>
#include<vector>
#include<cstdio>

#define  ALPHABETS_SIZE   26


class TrieNode
{
 public:
  // data members
  TrieNode*  children[ALPHABETS_SIZE];
  bool   IsEndWord;

  // member functions
  
  // constructor
  TrieNode();

  void MarkAsLeaf();
  void UnMarkAsLeaf();  

  
};

class Trie
{
 private:
  // data members
  TrieNode*   Root;

  // member functions
  bool HasChildren(TrieNode* Node);
  bool DeleteHelper(TrieNode* current, std::string key, int length, int level);
  void AllKeys(TrieNode* current, std::vector<std::string>& keys, std::string& sub);
  void Destroy(TrieNode* current);

 public:
  // member functions
 
  // constructor
  Trie();

  TrieNode* GetRoot(void);
  int GetIndex(char letter);
  void InsertNode(std::string key);
  bool SearchNode(std::string key);
  bool DeleteNode(std::string key);
  void PrintWords(void);
  void Reset(void);
  void BuildTrie(std::vector<std::string> keys); 
  std::vector<std::vector<std::string>> GetSuggestions(std::string& prefix);

  // destructor
  ~Trie();

};

