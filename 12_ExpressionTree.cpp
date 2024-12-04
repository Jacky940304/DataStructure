#include <bits/stdc++.h>

using namespace std;

class ExpressionTree {
private:
    struct Node {
        string value;
        Node* left;
        Node* right;

        Node(const string& val) : value(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Helper function to determine operator precedence
    int precedence(const string& op) {
        if (op == "+" || op == "-") return 1;
        if (op == "*" || op == "/" || op == "%") return 2;
        return 0;
    }

    // Helper function to build expression tree from postfix expression
    Node* buildTreeFromPostfix(const vector<string>& postfix) {
        stack<Node*> st;
        for (const auto& token : postfix) {
            if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-' && isdigit(token[1]))) {
                st.push(new Node(token));
            } else {
                Node* node = new Node(token);
                node->right = st.top(); st.pop();
                node->left = st.top(); st.pop();
                st.push(node);
            }
        }
        return st.top();
    }

    // Convert infix expression to postfix expression
    vector<string> infixToPostfix(const std::string& infix) {
        vector<string> postfix;    // 存放後綴表達式
        stack<string> opStack;     // 存放運算符堆疊
        string number;             // 存放數字（可能是負數）
        string infixWithoutSpaces; // 用來儲存刪除空格後的 infix 表達式

        // 移除空格
        for (char ch : infix) {
            if (!isspace(ch)) {
                infixWithoutSpaces += ch;
            }
        }

        // 開始處理不含空格的 infix 表達式
        for (size_t i = 0; i < infixWithoutSpaces.length(); i++) {
            char ch = infixWithoutSpaces[i];

            if (isdigit(ch)) {
                number += ch;  // 數字加到暫存變數中
                // 檢查是否還有連續的數字
                while (i + 1 < infixWithoutSpaces.size() && isdigit(infixWithoutSpaces[i + 1])) {
                    number += infixWithoutSpaces[++i];
                }
                postfix.push_back(number);  // 把數字加入後綴表達式
                number.clear();  // 清空數字暫存變數
            }
            // 處理負數
            else if (ch == '-' && (i == 0 || infixWithoutSpaces[i - 1] == '(' || isOperator(infixWithoutSpaces[i - 1]))) {
                number += ch;  // 如果是負數，將 '-' 和後面的數字一起當作一個整體處理
                while (i + 1 < infixWithoutSpaces.size() && isdigit(infixWithoutSpaces[i + 1])) {
                    number += infixWithoutSpaces[++i];
                }
                postfix.push_back(number);  // 加入後綴表達式
                number.clear();  // 清空暫存變數
            }
            // 處理左括號
            else if (ch == '(') {
                opStack.push(string(1, ch));  // 把 '(' 放入堆疊
            }
            // 處理右括號
            else if (ch == ')') {
                while (!opStack.empty() && opStack.top() != "(") {
                    postfix.push_back(opStack.top());
                    opStack.pop();
                }
                opStack.pop();  // 彈出左括號
            }
            // 處理運算符
            else if (isOperator(ch)) {
                string op(1, ch);  // 把運算符轉換為 string
                // 處理運算符優先級
                while (!opStack.empty() && precedence(opStack.top()) >= precedence(op)) {
                    postfix.push_back(opStack.top());
                    opStack.pop();
                }
                opStack.push(op);  // 把運算符推入堆疊
            }
        }

        // 把堆疊中的運算符彈出並加入後綴表達式
        while (!opStack.empty()) {
            postfix.push_back(opStack.top());
            opStack.pop();
        }

        return postfix;
    }

    // 輔助函數：判斷是否是運算符
    bool isOperator(char ch) {
        return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%');
    }

public:
    ExpressionTree(const string &expression) : root(nullptr) {
        vector<string> postfix = infixToPostfix(expression);
        root = buildTreeFromPostfix(postfix);
    }

    ~ExpressionTree() { deleteTree(root); }

    void deleteTree(Node* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    // Infix order traversal
    void printInFixOrder(Node* node) {
        if (!node) return;
        if (node->left) cout << "(";
        printInFixOrder(node->left);
        cout << node->value << " ";
        printInFixOrder(node->right);
        if (node->right) cout << ")";
    }

    void printInFixOrder() {
        printInFixOrder(root);
        cout << endl;
    }

    // Prefix order traversal
    void printPreFixOrder(Node* node) {
        if (!node) return;
        cout << node->value << " ";
        printPreFixOrder(node->left);
        printPreFixOrder(node->right);
    }

    void printPreFixOrder() {
        printPreFixOrder(root);
        cout << endl;
    }

    // Postfix order traversal
    void printPostFixOrder(Node* node) {
        if (!node) return;
        printPostFixOrder(node->left);
        printPostFixOrder(node->right);
        cout << node->value << " ";
    }

    void printPostFixOrder() {
        printPostFixOrder(root);
        cout << endl;
    }

    // Evaluate the expression tree
    int evaluate(Node* node) {
        if (!node->left && !node->right) return stoi(node->value);

        int leftVal = evaluate(node->left);
        int rightVal = evaluate(node->right);

        if (node->value == "+") return leftVal + rightVal;
        if (node->value == "-") return leftVal - rightVal;
        if (node->value == "*") return leftVal * rightVal;
        if (node->value == "/") return leftVal / rightVal;
        if (node->value == "%") return leftVal % rightVal;
    }

    int eval() {
        return evaluate(root);
    }
};

int main() {
    string infix = "( -12 + 3 ) * 4 % 5";
    ExpressionTree exprTree(infix);

    cout << "Inorder: ";
    exprTree.printInFixOrder();
    cout << "Preorder: ";
    exprTree.printPreFixOrder();
    cout << "Postorder: ";
    exprTree.printPostFixOrder();
    cout << "Evaluated result: " << exprTree.eval() << endl;

    return 0;
}
