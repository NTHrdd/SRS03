#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <stdexcept> // For exceptions like invalid_argument

// Node structure for the expression tree
struct Node {
    int value; // Operator code (-1 to -4) or operand value (0-9)
    Node *left;
    Node *right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}

    // Destructor for memory cleanup (optional, but good practice)
    ~Node() {
        delete left;
        delete right;
    }
};

// --- Helper functions for parsing ---

// Checks if a string token is an operator
bool isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

// Converts operator string to its integer code
int operatorToCode(const std::string& token) {
    if (token == "+") return -1;
    if (token == "-") return -2;
    if (token == "*") return -3;
    if (token == "/") return -4;
    throw std::invalid_argument("Invalid operator token: " + token);
}

// Checks if a string token is a single digit operand
bool isOperand(const std::string& token) {
    return token.length() == 1 && std::isdigit(token[0]);
}

// Converts a single digit operand string to an integer
int operandToValue(const std::string& token) {
    if (isOperand(token)) {
        return token[0] - '0';
    }
    throw std::invalid_argument("Invalid operand token: " + token);
}

// --- Tree Building Function ---

// Recursively builds the expression tree from tokens
// index is passed by reference to keep track of the current token being processed
Node* buildTree(const std::vector<std::string>& tokens, int& index) {
    if (index >= tokens.size()) {
        // Should not happen with valid prefix expression unless file is empty
        throw std::runtime_error("Unexpected end of tokens");
    }

    const std::string& token = tokens[index];
    index++; // Move to the next token

    if (isOperator(token)) {
        Node* node = new Node(operatorToCode(token));
        node->left = buildTree(tokens, index); // Build left subtree
        node->right = buildTree(tokens, index); // Build right subtree
        return node;
    } else if (isOperand(token)) {
        Node* node = new Node(operandToValue(token));
        return node; // Operand nodes are leaves
    } else {
        throw std::invalid_argument("Invalid token in expression: " + token);
    }
}

// --- Tree Simplification Function ---

// Evaluates an operation given the operator code and operand values
int evaluateOperation(int op_code, int val1, int val2) {
    switch (op_code) {
        case -1: return val1 + val2; // +
        case -2: return val1 - val2; // -
        case -3: { // *
            // Note: Multiplication is not evaluated during simplification unless its children are already values
            // This function is primarily used by simplifyTree for + and -
            // If called for * or /, it implies the children were already values.
            return val1 * val2;
        }
        case -4: { // /
            // Integer division
            if (val2 == 0) {
                throw std::runtime_error("Division by zero");
            }
            return val1 / val2;
        }
        default:
            throw std::invalid_argument("Unknown operator code for evaluation");
    }
}

// Recursively simplifies the tree by evaluating + and - subtrees
Node* simplifyTree(Node* node) {
    if (node == nullptr) {
        return nullptr;
    }

    // If it's a leaf node (operand), return it as is
    if (node->left == nullptr && node->right == nullptr) {
        return node;
    }

    // Recursively simplify children first (post-order traversal logic)
    node->left = simplifyTree(node->left);
    node->right = simplifyTree(node->right);

    // After children are simplified, check if the current node is + or -
    if (node->value == -1 || node->value == -2) { // If it's + or -
        // Children must be operands (or have been simplified into operand nodes)
        // Evaluate the operation
        int result = evaluateOperation(node->value, node->left->value, node->right->value);

        // Create a new node with the result
        Node* result_node = new Node(result);

        // Delete the original children nodes to free memory
        // We need to delete the children pointed to by node->left and node->right *before*
        // setting them to nullptr or deleting the node itself if we were doing that.
        // Since we are replacing the *current* node's value and making it a leaf,
        // we delete its original children.
        delete node->left;
        delete node->right;

        // Update the current node to be the result node (turn it into a leaf)
        node->value = result_node->value; // Copy the result value
        node->left = nullptr; // Make it a leaf
        node->right = nullptr;

        // Delete the temporary result_node
        delete result_node;

        // Return the modified current node (which is now a leaf)
        return node;
    } else {
        // If it's * or /, keep the node but its children are now simplified.
        return node;
    }
}

// --- Main function ---

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream infile(filename);

    if (!infile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    // Read all tokens from the file
    std::vector<std::string> tokens;
    std::string token;
    while (infile >> token) {
        tokens.push_back(token);
    }

    infile.close();

    if (tokens.empty()) {
        std::cerr << "File is empty." << std::endl;
        return 1;
    }

    Node* root = nullptr;
    try {
        // Build the initial tree
        int index = 0;
        root = buildTree(tokens, index);

        // Check if all tokens were consumed (basic validation)
        if (index < tokens.size()) {
            std::cerr << "Warning: Not all tokens were used in building the tree (input might be invalid prefix expression)." << std::endl;
            // Attempt to delete partially built tree to prevent leaks
            // delete root; // This calls the destructor recursively
            // root = nullptr; // Prevent double deletion if exception occurs later
            // return 1; // Or handle as error
        }

        // Simplify the tree
        Node* simplified_root = simplifyTree(root);

        // Output the pointer to the root of the simplified tree
        // Note: Printing the pointer value itself might not be very informative,
        // but the problem specifically asks for a pointer to the root.
        // A more useful output would be printing the tree structure or evaluating it.
        std::cout << simplified_root << std::endl;

        // To verify the simplified tree structure (optional):
        /*
        std::cout << "Simplified Tree (value print):" << std::endl;
        // Need a print function, e.g., pre-order
        // printTree(simplified_root);
        */

        // Clean up memory by deleting the simplified tree
        // The Node destructor handles recursive deletion
        delete simplified_root;

    } catch (const std::invalid_argument& e) {
        std::cerr << "Input error: " << e.what() << std::endl;
        // Clean up any partially built tree
        delete root;
        return 1;
    } catch (const std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
        // Clean up any partially built tree
        delete root;
        return 1;
    } catch (...) {
        std::cerr << "An unexpected error occurred." << std::endl;
        // Clean up any partially built tree
        delete root;
        return 1;
    }


    return 0;
}

/*
// Example of a simple tree print function (e.g., pre-order) for verification
void printTree(Node* node) {
    if (node == nullptr) {
        return;
    }
    if (node->value <= -1 && node->value >= -4) {
        char op_char;
        switch (node->value) {
            case -1: op_char = '+'; break;
            case -2: op_char = '-'; break;
            case -3: op_char = '*'; break;
            case -4: op_char = '/'; break;
             default: op_char = '?'; break; // Should not happen
        }
        std::cout << op_char << " ";
    } else {
        std::cout << node->value << " ";
    }
    printTree(node->left);
    printTree(node->right);
}
*/