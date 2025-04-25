#include "expression_tree.h"
#include <sstream>

bool isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

int operatorToCode(const std::string& token) {
    if (token == "+") return -1;
    if (token == "-") return -2;
    if (token == "*") return -3;
    if (token == "/") return -4;
    std::cerr << "Error: Invalid operator token encountered: " << token << std::endl;
    return 0;
}

bool isOperand(const std::string& token) {
    if (token.empty()) return false;
    for (char c : token) {
        if (!isdigit(c)) return false;
    }
    return token.size() == 1;
}

int operandToValue(const std::string& token) {
    try {
        return stoi(token);
    } catch (const std::invalid_argument& ia) {
        std::cerr << "Error: Invalid argument for operand conversion: " << token << ". " << ia.what() << std::endl;
        return 0;
    } catch (const std::out_of_range& oor) {
        std::cerr << "Error: Operand value out of range: " << token << ". " << oor.what() << std::endl;
        return 0;
    }
}

Node* buildTree(const std::vector<std::string>& tokens, int& index) {
    if (index >= tokens.size()) {
        std::cerr << "Error: Insufficient tokens to build tree." << std::endl;
        return nullptr;
    }

    std::string token = tokens[index++];

    if (isOperator(token)) {
        int opCode = operatorToCode(token);
        if (opCode == 0) {
            return nullptr;
        }

        Node* node = new Node(opCode);

        node->left = buildTree(tokens, index);
        if (!node->left) {
            delete node;
            return nullptr;
        }

        node->right = buildTree(tokens, index);
        if (!node->right) {
            delete node;
            return nullptr;
        }
        return node;

    } else if (isOperand(token)) {
        int value = operandToValue(token);
        return new Node(value);
    } else {
        std::cerr << "Error: Invalid token encountered during tree build: " << token << std::endl;
        return nullptr;
    }
}

bool evaluate(Node* node, int& result) {
    if (!node) {
        std::cerr << "Error: Attempt to evaluate null node." << std::endl;
        result = 0;
        return false;
    }
    if (node->value >= 0) {
        result = node->value;
        return true;
    }

    int leftVal = 0;
    int rightVal = 0;

    if (!evaluate(node->left, leftVal)) {
        result = 0;
        return false;
    }
    if (!evaluate(node->right, rightVal)) {
        result = 0;
        return false;
    }

    switch (node->value) {
        case -1: result = leftVal + rightVal; return true; // +
        case -2: result = leftVal - rightVal; return true; // -
        case -3: result = leftVal * rightVal; return true; // *
        case -4: // /
            if (rightVal == 0) {
                std::cerr << "Error: Division by zero." << std::endl;
                result = 0;
                return false;
            }
            result = leftVal / rightVal;
            return true;
        default:
            std::cerr << "Error: Unknown operation code in node: " << node->value << std::endl;
            result = 0;
            return false;
    }
}


Node* simplify(Node* node) {
    if (!node) {
        return nullptr;
    }

    node->left = simplify(node->left);
    node->right = simplify(node->right);

    if ((node->value == -1 || node->value == -2) && node->left && node->right) {
        int result = 0;
        bool success = evaluate(node, result);
        if (success) {
            delete node;
            return new Node(result);
        } else {
            return node;
        }
    }
    return node;
}


void printTree(Node* root, int depth) {
    if (!root) {
        return;
    }
    const int indent_step = 4;
    printTree(root->right, depth + 1);

    std::cout << std::string(indent_step * depth, ' ');

    if (root->value == -1) std::cout << "+" << std::endl;
    else if (root->value == -2) std::cout << "-" << std::endl;
    else if (root->value == -3) std::cout << "*" << std::endl;
    else if (root->value == -4) std::cout << "/" << std::endl;
    else std::cout << root->value << std::endl;

    printTree(root->left, depth + 1);
}


std::vector<std::string> tokenize(const std::string& str) {
    std::istringstream iss(str);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}