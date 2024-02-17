
//Headers
#include<iostream>
#include"trie.h"

// Entry point of Main function
int main(void)
{
   Trie* Words = new Trie();
   std::vector<std::vector<std::string>> suggestion;
   std::string Enter;
   int count_words = 0;
   int limit = 6;

   std::vector<std::string> InsertWords = {"key", "car", "cart", "cartoon", "jack", "cat", "mouse", "mousepad", "bat", "their", "the", "cup", "mice", "code", "Insert", "ink", "improvement", "incapable", "include", "incident", "idea", "identity", "impulsive", "impulse", "found", "fast", "free", "done", "time", "space", "link", "web", "dash", "drone", "movement", "money", "apple", "age", "ant", "approve", "Aim", "Air", "accept", "alter"};

   int Size = InsertWords.size();

   for(int le = 0; le < Size; le++ ) 
   {
      Words->InsertNode(InsertWords[le]);
   }

   std::cout<< "enter the Word" <<std::endl;
   std::cin>>Enter;

   suggestion = Words->GetSuggestions(Enter);

   if(suggestion.size() == 0)
   {
      std::cout<< "prefix word is not present." <<std::endl;
   }

   for(int le = (suggestion.size() - 1); le >= 0 ; le--)
   {
      for(int le2 = 0; le2 < suggestion[le].size(); le2++)
      {
        if(count_words == limit)
           break;
        std::cout<< suggestion[le][le2] << ", ";
        count_words++;
      }

      if(count_words == limit)
        break;
      std::cout<< std::endl;
   }

   delete Words;

   exit(0);
} 

