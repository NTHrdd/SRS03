#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>

using namespace std;

/**
 * @brief Узел дерева выражения.
 */
struct Node {
    int value;      ///< >= 0 - операнд, -1:+, -2:-, -3:*, -4:/
    Node* left;     ///< Левый потомок
    Node* right;    ///< Правый потомок

    /**
     * @brief Конструктор узла.
     * @param val Значение (операнд или код операции)
     */
    Node(int val) : value(val), left(nullptr), right(nullptr) {}

    /**
     * @brief Деструктор, рекурсивно удаляет поддеревья.
     */
    ~Node() {
        delete left;
        delete right;
    }
};

/**
 * @brief Проверяет, является ли токен оператором.
 * @param token Строка токена
 * @return true если токен является оператором
 */
bool isOperator(const string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

/**
 * @brief Преобразует строку оператора в числовой код.
 * @param token Строка токена
 * @return Целочисленный код операции
 */
int operatorToCode(const string& token) {
    if (token == "+") return -1;
    if (token == "-") return -2;
    if (token == "*") return -3;
    if (token == "/") return -4;
    throw invalid_argument("Invalid operator: " + token);
}

/**
 * @brief Проверяет, является ли токен однозначным операндом.
 * @param token Строка токена
 * @return true если токен является цифрой
 */
bool isOperand(const string& token) {
    return token.size() == 1 && isdigit(token[0]);
}

/**
 * @brief Преобразует строку-цифру в число.
 * @param token Строка токена
 * @return Целое число
 */
int operandToValue(const string& token) {
    return token[0] - '0';
}

/**
 * @brief Рекурсивно строит дерево выражения из токенов.
 * @param tokens Вектор токенов
 * @param index Текущий индекс вектора
 * @return Указатель на корень поддерева
 */
Node* buildTree(const vector<string>& tokens, int& index) {
    if (index >= tokens.size()) throw runtime_error("Недостаточно токенов");

    string token = tokens[index++];
    if (isOperator(token)) {
        int opCode = operatorToCode(token);
        Node* node = new Node(opCode);
        node->left = buildTree(tokens, index);
        node->right = buildTree(tokens, index);
        return node;
    } else if (isOperand(token)) {
        return new Node(operandToValue(token));
    } else {
        cerr << "Неверный токен: " << token;
    }
}

/**
 * @brief Рекурсивно вычисляет значение поддерева.
 * @param node Указатель на корень поддерева
 * @return Результат вычисления
 */
int evaluate(Node* node) {
    if (!node) return 0;
    if (node->value >= 0) return node->value;

    int left = evaluate(node->left);
    int right = evaluate(node->right);

    switch (node->value) {
        case -1: return left + right;
        case -2: return left - right;
        case -3: return left * right;
        case -4:
            if (right == 0) throw runtime_error("Деление на ноль");
            return left / right;
        default: cerr << "Неизвестная операция";
    }
}

/**
 * @brief Упрощает дерево, заменяя + и - на вычисленные значения.
 * @param node Указатель на корень поддерева
 * @return Указатель на упрощённое поддерево
 */
Node* simplify(Node* node) {
    if (!node) return nullptr;

    node->left = simplify(node->left);
    node->right = simplify(node->right);

    if (node->value == -1 || node->value == -2) {
        int result = evaluate(node);
        delete node;
        return new Node(result);
    }

    return node;
}

/**
 * @brief Выводит дерево в консоль (разворот вправо).
 * @param root Указатель на корень дерева
 * @param depth Глубина текущего уровня
 */
void printTree(Node* root, int depth = 0) {
    if (!root) return;
    printTree(root->right, depth + 1);
    cout << string(3 * depth, ' ') << root->value << endl;
    printTree(root->left, depth + 1);
}

/**
 * @brief Делит строку на токены по пробелам.
 * @param str Исходная строка
 * @return Вектор токенов
 */
vector<string> tokenize(const string& str) {
    istringstream iss(str);
    vector<string> tokens;
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

/**
 * @brief Точка входа в программу.
 * @return Код завершения
 */
int main() {
    string filename = "filename.txt";
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл: " << filename << endl;
        return 1;
    }

    string expression;
    getline(file, expression);
    file.close();

    try {
        vector<string> tokens = tokenize(expression);
        int index = 0;
        Node* root = buildTree(tokens, index);

        cout << "Исходное дерево:" << endl;
        printTree(root);

        Node* simplifiedRoot = simplify(root);

        cout << "\nУпрощенное дерево:" << endl;
        printTree(simplifiedRoot);

        cout << "\nУказатель на корень упрощенного дерева: " << simplifiedRoot << endl;

        delete simplifiedRoot;
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}