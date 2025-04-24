#include <iostream>
#include <fstream>
#include <string>

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Функция для построения дерева из префиксного выражения
Node* buildTree(const std::string& expr, int& pos) {
    if (pos >= expr.length()) {
        return nullptr;
    }

    char c = expr[pos++];

    if (c == '+') {
        Node* node = new Node(-1); // Код для сложения
        node->left = buildTree(expr, pos);
        node->right = buildTree(expr, pos);
        return node;
    } else if (c == '-') {
        Node* node = new Node(-2); // Код для вычитания
        node->left = buildTree(expr, pos);
        node->right = buildTree(expr, pos);
        return node;
    } else if (c == '*') {
        Node* node = new Node(-3); // Код для умножения
        node->left = buildTree(expr, pos);
        node->right = buildTree(expr, pos);
        return node;
    } else if (c == '/') {
        Node* node = new Node(-4); // Код для деления
        node->left = buildTree(expr, pos);
        node->right = buildTree(expr, pos);
        return node;
    } else if (c >= '0' && c <= '9') {
        return new Node(c - '0'); // Преобразование символа в число
    }

    return nullptr;
}

// Функция для вычисления значения поддерева
int evaluateTree(Node* root) {
    if (!root) {
        return 0;
    }

    if (root->value >= 0) { // Если это операнд
        return root->value;
    }

    int leftVal = evaluateTree(root->left);
    int rightVal = evaluateTree(root->right);

    if (root->value == -1) { // Сложение
        return leftVal + rightVal;
    } else if (root->value == -2) { // Вычитание
        return leftVal - rightVal;
    } else if (root->value == -3) { // Умножение
        return leftVal * rightVal;
    } else if (root->value == -4) { // Деление
        return leftVal / rightVal;
    }

    return 0;
}

// Функция для преобразования дерева
Node* transformTree(Node* root) {
    if (!root) {
        return nullptr;
    }

    // Если это операнд, просто возвращаем его
    if (root->value >= 0) {
        return root;
    }

    // Рекурсивно преобразуем левое и правое поддеревья
    root->left = transformTree(root->left);
    root->right = transformTree(root->right);

    // Если текущая операция - сложение или вычитание
    if (root->value == -1 || root->value == -2) {
        int result = evaluateTree(root);

        // Удаляем поддеревья
        delete root->left;
        delete root->right;

        // Заменяем операцию на значение
        root->value = result;
        root->left = nullptr;
        root->right = nullptr;
    }

    return root;
}

// Функция для вывода дерева (для отладки)
void printTree(Node* root, int level = 0) {
    if (!root) {
        return;
    }

    printTree(root->right, level + 1);

    for (int i = 0; i < level; i++) {
        std::cout << "   ";
    }

    std::cout << root->value << std::endl;

    printTree(root->left, level + 1);
}

// Функция для освобождения памяти
void freeTree(Node* root) {
    if (!root) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    std::string filename = "filename.txt"; // Имя файла
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла" << std::endl;
        return 1;
    }

    std::string expr;
    std::getline(file, expr);
    file.close();

    // Удаляем пробелы из выражения
    std::string exprNoSpaces;
    for (char c : expr) {
        if (c != ' ') {
            exprNoSpaces += c;
        }
    }

    int pos = 0;
    Node* root = buildTree(exprNoSpaces, pos);

    if (!root) {
        std::cerr << "Ошибка построения дерева" << std::endl;
        return 1;
    }

    std::cout << "Исходное дерево:" << std::endl;
    printTree(root);

    Node* transformedRoot = transformTree(root);

    std::cout << "Преобразованное дерево:" << std::endl;
    printTree(transformedRoot);

    std::cout << "Указатель на корень преобразованного дерева: " << transformedRoot << std::endl;

    freeTree(transformedRoot);

    return 0;
}