#include <iostream>
#include <queue>
#include <vector>

// Node structure representing a node in the Huffman Tree
struct imp_Node {
    char imp_ch;       // Character being stored
    int imp_freq;      // Frequency of the character
    imp_Node *imp_left, *imp_right; // Pointers to left and right children

    // Constructor initializing a node with character and frequency
    imp_Node(char imp_character, int imp_frequency) {
        imp_ch = imp_character;
        imp_freq = imp_frequency;
        imp_left = imp_right = nullptr;
    }
};

// Custom comparator for the priority queue to order nodes by frequency
struct imp_compare {
    bool operator()(imp_Node* imp_l, imp_Node* imp_r) {
        return imp_l->imp_freq > imp_r->imp_freq;
    }
};

// Printing the Huffman Codes in preorder traversal
void imp_printHuffmanCodes(imp_Node* imp_root, std::string imp_code) {
    if (!imp_root)
        return;

    // Checking if this is a leaf node containing one of the input characters
    if (imp_root->imp_left == nullptr && imp_root->imp_right == nullptr) {
        std::cout << imp_code << " "; // Printing the code for this character
    }

    // Recurring for the left and right children with appended code
    imp_printHuffmanCodes(imp_root->imp_left, imp_code + "0");
    imp_printHuffmanCodes(imp_root->imp_right, imp_code + "1");
}

// Building the Huffman Tree and generating the codes
void imp_buildHuffmanTree(const std::string& imp_S, const std::vector<int>& imp_freq) {
    // Creating a priority queue to store nodes of the Huffman tree, ordering nodes by frequency
    std::priority_queue<imp_Node*, std::vector<imp_Node*>, imp_compare> imp_pq;

    // Creating a leaf node for each character and adding it to the priority queue
    for (int imp_i = 0; imp_i < imp_S.size(); ++imp_i) {
        imp_pq.push(new imp_Node(imp_S[imp_i], imp_freq[imp_i]));
    }

    // Iterating until the size of the priority queue becomes one
    while (imp_pq.size() != 1) {
        // Removing the two nodes with the lowest frequency
        imp_Node* imp_left = imp_pq.top(); imp_pq.pop();
        imp_Node* imp_right = imp_pq.top(); imp_pq.pop();

        // Creating a new internal node with a frequency equal to the sum of the two nodes' frequencies
        int imp_sum = imp_left->imp_freq + imp_right->imp_freq;
        imp_Node* imp_newNode = new imp_Node('\0', imp_sum);

        // Setting the two removed nodes as the children of the new node
        imp_newNode->imp_left = imp_left;
        imp_newNode->imp_right = imp_right;

        // Adding the new node to the priority queue
        imp_pq.push(imp_newNode);
    }

    // The remaining node is now the root node and the tree is complete
    imp_Node* imp_root = imp_pq.top();

    // Traversing the Huffman Tree and printing the Huffman Codes
    imp_printHuffmanCodes(imp_root, "");

    std::cout << std::endl;
}

int main() {
    std::string imp_S;
    std::vector<int> imp_freq;

    // Prompting the user to enter the characters
    std::cout << "Enter the characters: ";
    std::cin >> imp_S;

    // Prompting the user to enter the frequencies for each character
    std::cout << "Enter the frequencies: ";
    for (int imp_i = 0; imp_i < imp_S.size(); ++imp_i) {
        int imp_f;
        std::cin >> imp_f;
        imp_freq.push_back(imp_f);
    }

    // Building the Huffman Tree and printing the codes
    imp_buildHuffmanTree(imp_S, imp_freq);

    return 0;
}
