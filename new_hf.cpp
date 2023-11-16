#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

// Node structure for the Huffman tree
struct HuffmanNode {
    char data;
    unsigned freq;
    HuffmanNode *left, *right;

    HuffmanNode(char c, unsigned f) : data(c), freq(f), left(nullptr), right(nullptr) {}
};

// Comparison function for the priority queue
struct CompareNodes {
    bool operator()(HuffmanNode* left, HuffmanNode* right) {
        return left->freq > right->freq;
    }
};

// Build Huffman Tree and return the root
HuffmanNode* buildHuffmanTree(const unordered_map<char, unsigned>& freqMap) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> minHeap;

    // Create a leaf node for each character and push it to the priority queue
    for (const auto& pair : freqMap) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    // Build the Huffman Tree
    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();

        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        HuffmanNode* internalNode = new HuffmanNode('$', left->freq + right->freq);
        internalNode->left = left;
        internalNode->right = right;

        minHeap.push(internalNode);
    }

    return minHeap.top();
}

// Traverse the Huffman Tree and generate codes
void generateHuffmanCodes(HuffmanNode* root, const string& code, unordered_map<char, string>& huffmanCodes) {
    if (root == nullptr) {
        return;
    }

    if (root->data != '$') {
        huffmanCodes[root->data] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

// Display Huffman Codes
void displayHuffmanCodes(const unordered_map<char, string>& huffmanCodes) {
    cout << "Char | Huffman code\n";
    cout << "------------------\n";

    for (const auto& pair : huffmanCodes) {
        cout << pair.first << "    | " << pair.second << "\n";
    }
}

int main() {
    char arr[] = {'A', 'B', 'C', 'D'};
    int freq[] = {5, 1, 6, 3};

    int size = sizeof(arr) / sizeof(arr[0]);

    // Create a frequency map
    unordered_map<char, unsigned> freqMap;
    for (int i = 0; i < size; ++i) {
        freqMap[arr[i]] = freq[i];
    }

    // Build Huffman Tree
    HuffmanNode* root = buildHuffmanTree(freqMap);

    // Generate Huffman Codes
    unordered_map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    // Display Huffman Codes
    displayHuffmanCodes(huffmanCodes);

    return 0;
}
