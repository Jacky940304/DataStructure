#include <iostream>
#include <vector>
#include <string>

using namespace std;

class SuffixTreeNode {
public:
    SuffixTreeNode* children[26]; // 固定大小陣列，用於存放 a-z 字母
    vector<int> indices; // 存儲這個節點所代表子字串的起始索引

    SuffixTreeNode() {
        for (int i = 0; i < 26; ++i) {
            children[i] = nullptr;
        }
    }

    ~SuffixTreeNode() {
        for (int i = 0; i < 26; ++i) {
            delete children[i];
        }
    }
};

class SuffixTree {
private:
    SuffixTreeNode* root;
    std::string text;

    void insertSuffix(const std::string& suffix, int startIndex) {
        SuffixTreeNode* current = root;
        for (char ch : suffix) {
            int index = ch - 'a';
            if (current->children[index] == nullptr) {
                current->children[index] = new SuffixTreeNode();
            }
            current = current->children[index];
            current->indices.push_back(startIndex); // 儲存該後綴的起始位置
        }
    }

public:
    SuffixTree(const std::string& text) : text(text) {
        root = new SuffixTreeNode();
        for (size_t i = 0; i < text.length(); ++i) {
            insertSuffix(text.substr(i), i); // 插入每個後綴及其起始位置
        }
    }

    bool exist(const std::string& substring) {
        SuffixTreeNode* current = root;
        for (char ch : substring) {
            int index = ch - 'a';
            if (current->children[index] == nullptr) {
                return false;
            }
            current = current->children[index];
        }
        return true;
    }

    int count(const std::string& substring) {
        SuffixTreeNode* current = root;
        for (char ch : substring) {
            int index = ch - 'a';
            if (current->children[index] == nullptr) {
                return 0;
            }
            current = current->children[index];
        }
        return current->indices.size();
    }

    ~SuffixTree() {
        delete root;
    }
};


int main() {
    std::string text = "";
    while(true) {
      std::string temp;
      getline(std::cin, temp);
      if(temp == "")
        break;
      text += temp;
    }
    SuffixTree tree(text);

    std::string query;
    while(true) {
      getline(std::cin, query);
      if(query == "")
        break;
      std::cout << "Existence of '" << query << "': " << (tree.exist(query) ? "Yes" : "No") << std::endl;
      std::cout << "Count of '" << query << "': " << tree.count(query) << std::endl;
    }
    return 0;
}