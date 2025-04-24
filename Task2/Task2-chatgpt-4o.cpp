#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>

using namespace std;

// Класс узла дерева
struct Node {
    int val; // -1: +, -2: -, -3: *, -4: /, >=0: операнд
    Node* left;
    Node* right;

    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

// Преобразование символа в код операции
int getOpCode(char op) {
    switch (op) {
        case '+': return -1;
        case '-': return -2;
        case '*': return -3;
        case '/': return -4;
        default: return op - '0'; // Операнд
    }
}

// Построение дерева из потока (префиксный разбор)
Node* buildTree(istringstream& iss) {
    string token;
    if (!(iss >> token)) return nullptr;

    int val;
    if (isdigit(token[0])) {
        val = stoi(token);
        return new Node(val);
    } else {
        val = getOpCode(token[0]);
        Node* node = new Node(val);
        node->left = buildTree(iss);
        node->right = buildTree(iss);
        return node;
    }
}

// Вычисление значения поддерева
int evaluate(Node* root) {
    if (!root) return 0;
    if (root->val >= 0) return root->val;

    int l = evaluate(root->left);
    int r = evaluate(root->right);

    switch (root->val) {
        case -1: return l + r;
        case -2: return l - r;
        case -3: return l * r;
        case -4: return r != 0 ? l / r : 0;
        default: return 0;
    }
}

// Упрощение дерева: заменяет + и - на значения
Node* simplify(Node* root) {
    if (!root) return nullptr;

    root->left = simplify(root->left);
    root->right = simplify(root->right);

    if (root->val == -1 || root->val == -2) {
        // Удаляем старые поддеревья
        int result = evaluate(root);
        delete root->left;
        delete root->right;
        return new Node(result);
    }

    return root;
}

// Печать дерева (для отладки)
void printTree(Node* root, int depth = 0) {
    if (!root) return;
    for (int i = 0; i < depth; ++i) cout << "  ";
    if (root->val >= 0) cout << root->val << endl;
    else cout << root->val << endl;
    printTree(root->left, depth + 1);
    printTree(root->right, depth + 1);
}

// Очистка памяти
void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    string filename = "filename.txt"; // Укажите имя файла

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл." << endl;
        return 1;
    }

    string expression;
    getline(file, expression);
    file.close();

    istringstream iss(expression);
    Node* root = buildTree(iss);

    // Упростить дерево
    Node* simplified = simplify(root);

    // Вывод указателя на корень
    cout << "Указатель на корень дерева: " << simplified << endl;

    // Если нужно, можно вывести дерево
    printTree(simplified);

    // Очистка
    deleteTree(simplified);

    return 0;
}