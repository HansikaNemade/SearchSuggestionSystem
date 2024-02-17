
#include "trie.h"

TrieNode::TrieNode()
{
    this->IsEndWord = false;

    for(int le = 0; le < ALPHABETS_SIZE; le++)
    {
       this->children[le] = NULL;
    }
}

void TrieNode::MarkAsLeaf()
{
    this->IsEndWord = true;
}

void TrieNode::UnMarkAsLeaf()
{
    this->IsEndWord = false;
}



bool Trie::HasChildren(TrieNode* Node)
{
    for(int le = 0; le < ALPHABETS_SIZE; le++)
    {
        if(Node->children[le] != NULL)
           return true;
    }

    return false;
}

bool Trie::DeleteHelper(TrieNode* current, std::string key, int length, int level)
{
    bool SelfDelete = false;

    if(current == NULL)
    {
      return SelfDelete;
    }

    if(level == length)
    {
        if(HasChildren(current))
        {
          current->UnMarkAsLeaf();
          SelfDelete = false;
        }
        else
        {
          delete current;
          current = NULL;
          SelfDelete = true;
        }
    }
    else
    {
        bool  NodeDeleted = 0;
        int index = GetIndex((char) tolower(key[level]));

        NodeDeleted = DeleteHelper(current->children[index], key, length, level+1);

        if(NodeDeleted == true)
        {
           current->children[index] = NULL;

            if(current->IsEndWord)
               SelfDelete = false;
            else if(HasChildren(current))
               SelfDelete = false;
            else
            {
              delete current;
              current = NULL;
              SelfDelete = true;
            }
        }
        else
          SelfDelete = false;
    }

    return SelfDelete;
}

void Trie::AllKeys(TrieNode* current, std::vector<std::string>& keys, std::string& sub)
{
    if(current->IsEndWord)
        keys.push_back(sub);

    for(int le = 0; le < ALPHABETS_SIZE; le++)
    {  
        if(current->children[le] != NULL)
        {
            sub = sub + (char)('a' + le);
            AllKeys(current->children[le], keys, sub);
            sub.pop_back();
        }
    }

    return;
}

void Trie::Destroy(TrieNode* current)
{
    for(int le = 0; le < ALPHABETS_SIZE; le++)
    {
        if(current->children[le] != NULL)
        {
            Destroy(current->children[le]);
            current->children[le] = NULL;
        }
    }

    delete current;
    current = NULL;
    return;
}

Trie::Trie()
{
    this->Root = new TrieNode();
}

TrieNode* Trie::GetRoot(void)
{
    return this->Root;
}

int Trie::GetIndex(char letter)
{
    return letter - 'a';
}

void Trie::InsertNode(std::string key)
{
    if(key.empty())
        return;

    TrieNode* current = Root;
    int index = -1;

    for(int le = 0; le < key.size() ; le++) 
    {
        index = GetIndex((char)tolower(key[le]));

        if(current->children[index] == NULL)
        {
            current->children[index] = new TrieNode();
        }

        current = current->children[index];
    }

    current->MarkAsLeaf();

    return;
}

bool Trie::SearchNode(std::string key)
{
    if(key.empty())
        return(false);

    TrieNode* current = Root;
    int index = -1; 

    for(int le = 0; le < key.size(); le++)
    {
        index = GetIndex((char) tolower(key[le]));

        if(current->children[index] == NULL)
        {
           return(false);
        }

        current = current->children[index];
    }

    if(current != NULL && current->IsEndWord)
        return true;

    return false;
}

bool Trie::DeleteNode(std::string key)
{
    if(key.empty())
        return false;

    DeleteHelper(Root, key, key.size(), 0);

    return true;
}

void Trie::PrintWords(void)
{
    std::vector<std::string> keys;
    std::string  sub;

    AllKeys(Root, keys, sub);

    std::cout<< "**All words in structure**" <<std::endl;
    for(int le = 0; le < keys.size(); le++)
    {
        std::cout<< keys[le] <<std::endl;
    }
    std::cout<< "**end**\n" <<std::endl;

    return;
}

void Trie::Reset(void)
{
    if(Root != NULL)
    {
        for(int le = 0; le < ALPHABETS_SIZE; le++)
        {
            if(Root->children[le] != NULL)
            {
               Destroy(Root->children[le]);
               Root->children[le] = NULL;
            }
        }
    }

    return;
}

std::vector<std::vector<std::string>> Trie::GetSuggestions(std::string& prefix)
{
    TrieNode* current = Root;
    int index = -1;
    std::string sub = "";

    std::vector<std::vector<std::string>> output;
      
    for(int le = 0; le < prefix.size(); le++)
    {
         
        index = GetIndex((char) tolower(prefix[le]));
        sub = sub + prefix[le];

        if(current->children[index] == NULL)
        {
            break;
        }
 
        std::vector<std::string> temp;

        AllKeys(current->children[index], temp, sub);
         
        output.push_back(temp);
        temp.clear();

        current = current->children[index];
    }

    return output;
}

void Trie::BuildTrie(std::vector<std::string> keys)
{
    for(int le = 0; le < keys.size(); le++)
    {
        InsertNode(keys[le]);
    }

    return;
}

Trie::~Trie()
{
    if(Root != NULL)
    {
        Reset();
        delete Root;
    }
}

