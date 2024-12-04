#include <iostream>
#include <string>

using namespace std;

class TrieNode{
public:
    TrieNode* children[26];
    int wordCount;
    int level;
    int childrenCount;

    TrieNode(int nodeLevel){
        wordCount = 0;
        level = nodeLevel;
        childrenCount = 0;
        for(int i = 0;i < 26;i++)
            children[i] = nullptr;
    }
};

class Trie
{
private:
    TrieNode* root;

    void insert(TrieNode* node, string& key){
        TrieNode* currentNode = node;

        for(auto c : key){
            if(currentNode->children[c - 'a'] == nullptr){
                TrieNode* newNode = new TrieNode(currentNode->level + 1);
                currentNode->children[c - 'a'] = newNode;
                currentNode->childrenCount++;
            }

            currentNode = currentNode->children[c - 'a'];
        }

        currentNode->wordCount++;
    }

    bool search(TrieNode* node, string& key){
        TrieNode* currentNode = node;

        for(auto c : key){
            if(currentNode->children[c - 'a'] == nullptr) return 0;

            currentNode = currentNode->children[c - 'a'];
        }

        return (currentNode->wordCount > 0);
    }

	void preorder(TrieNode* node, bool endLine) {
        for (int i = 0; i < 26; i++) {
            if (node->children[i] != nullptr) {
                if(endLine) {
					for(int j = 0;j < node->children[i]->level * 2;j++)cout << " ";
				}
				cout << char(i + 'a');
				int nextIndex;
				if(node->children[i]->childrenCount > 1){
					cout << endl;
					preorder(node->children[i], 1); //子節點大於二要換行
				}
				else if(node->children[i]->childrenCount == 1){
					for(int j = 0;j < 26;j++){
						if(node->children[i]->children[j] != nullptr)
							nextIndex = j;
					}

					if(node->children[i]->children[nextIndex]->wordCount < 1){
						preorder(node->children[i], 0); //不是詞結尾不用換行
					}
					else {
						cout << endl;
						preorder(node->children[i], 1); //是詞結尾不用換行
					}
				}
				else cout << endl;
        	}
    	}
	}
public:
	/*
	construct a Trie.
	*/
	Trie(){
        root = new TrieNode(0);
    }
	/*
	search trie for key, return true if exist, false if not.
	*/
	bool search(string key){
        return search(root, key);
    }
	/*
	insert value into trie.
	*/
	void insert(string value){
        insert(root, value);
    }
	/*
	display trie in pre-order, each element in a line, display space befoer element base on the level of 	the element. level 1 for 2 space, level 2 for 4 space, level 3 for 6 space and so on, root is level 	0.
	*/
	void preorder() {
        cout << "[]" << endl;
        preorder(root, 1);
    }
};

int main()
{
	Trie *trie = new Trie();
	string command, key, value;
	while(1)
	{
		cin>>command;
		if(command == "insert")
		{
			cin>>value;
			trie->insert(value);
		}
		else if(command == "search")
		{
			cin>>key;
			if(trie->search(key))
				cout << "exist" << endl;
			else
				cout << "not exist" << endl;
		}
		else if(command == "print")
		{
			trie->preorder();
		}
		else if(command == "exit")
		{
			break;
		}
	}
}