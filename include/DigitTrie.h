#ifndef _DIGIT_TRIE_H_
#define _DIGIT_TRIE_H_

#include "bufref.h"
#include <bitset>

#include <vector>
// define digit size
#define DIGIT_SIZE 10

typedef int16_t TriPos;

namespace utils {
 
 typedef std::vector<TriPos> TriPosArray;
 typedef TriPosArray::iterator TriPosArrayIt;
 typedef TriPosArray::const_iterator TriPosArrayCIt;


// A Class representing a DigitTrie node
class DigitTrie
{
public:
        TriPos _pos;
        DigitTrie* character[DIGIT_SIZE];

        // Constructor
        DigitTrie():_pos(-1)
        {
                for (int i = 0; i < DIGIT_SIZE; i++)
                        this->character[i] = NULL;
        }

        inline void insert(std::string, TriPos pos);
        inline TriPos search(bufrefnew& buf) const;
        inline TriPos search(std::string) const;
};

#define NOT_IN_TRI -1

class DigitTrieHeader
{
public:

   DigitTrieHeader():_size(0)
   {
      _nullPos = insert("0");      
   }
   //insert into tri and return the position
   TriPos insert(std::string val) {
      TriPos pos = search(val);
        if(NOT_IN_TRI == pos) {
         pos = _size;
         _head.insert(val, _size);
         //std::cout <<"Token: "<<val<<" pos: "<<_size<<std::endl;
         ++_size;
        }
        return pos;
   }

   TriPos search(std::string val) const  { return _head.search(val); }

  void searchAndAddToContainer(bufrefnew& key, bufrefnew& val, std::vector<bufrefnew>& container) const
   {
     //if(isdigit(*key.buf))
     {
       TriPos pos = _head.search(key);
       if (NOT_IN_TRI != pos) {container[pos] = val;}
     }
   }
   const uint16_t size() const { return _size;}
   const DigitTrie& getTrie() const {return _head; }
   const TriPos nullPos() const { return _nullPos;}

private:
   uint16_t _size; //trie entry size
   TriPos _nullPos;
   DigitTrie _head;
   
   
};


// Iterative function to insert a key in the DigitTrie
void DigitTrie::insert(std::string key, TriPos pos)
{
        // start from root node
        DigitTrie* curr = this;
        for (uint16_t i = 0; i < key.length(); i++)
        {
                // create a new node if path doesn't exists
                if (curr->character[key[i] - '0'] == NULL)
                        curr->character[key[i] - '0'] = new DigitTrie();

                // go to next node
                curr = curr->character[key[i] - '0'];
        }

        // mark current node as leaf
        curr->_pos = pos;
}

// Iterative function to search a key in DigitTrie. It returns true
// if the key is found in the DigitTrie, else it returns false
TriPos DigitTrie::search(std::string key) const
{
        // return false if DigitTrie is empty
        if (this == NULL)
                return NOT_IN_TRI;

        const DigitTrie* curr = this;
        for (uint16_t i = 0; i < key.length(); i++)
        {
                // go to next node
                curr = curr->character[key[i] - '0'];

                // if string is invalid (reached end of path in DigitTrie)
                if (curr == NULL)
                        return NOT_IN_TRI;
        }

        // if current node is a leaf and we have reached the
        // end of the string, return true
        return curr->_pos;
}

TriPos DigitTrie::search(bufrefnew& key) const
{
        // return false if DigitTrie is empty
        if (this == NULL)
                return NOT_IN_TRI;

        const DigitTrie* curr = this;
        const char* buf = key.buf;
        for (uint16_t i = 0; i < key.len; i++, ++buf)
        {
                // go to next node
                curr = curr->character[*buf - '0'];

                // if string is invalid (reached end of path in DigitTrie)
                if (curr == NULL)
                        return NOT_IN_TRI;
        }

        // if current node is a leaf and we have reached the
        // end of the string, return true
        return curr->_pos;
}
}
#endif //_DIGIT_TRIE_H_

#if 0
// C++ implementation of DigitTrie Data Structure
int main()
{
        DigitTrie* head = new DigitTrie();

        head->insert("3", 1);
        head->insert("33", 2);
        head->insert("343", 3);
        std::cout << head->search("3") << " ";          // print 1
        std::cout << head->search("34") << " ";         // print 1
        std::cout << head->search("343") << " ";        // print 1
        std::cout << std::endl;         // print 1

        return 0;
}
#endif
