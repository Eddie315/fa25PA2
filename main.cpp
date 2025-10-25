//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // TODO:
    // Min heap object easier
    // int temp = 0;
    // int temp2 = 0;
    // int storage=0;
    // for (int i=0; i<weightArr[]; i++) {
    //     temp= leftArr[i];
    //     if (temp < rightArr[i]) {
    //         temp = storage;
    //     }
    //     if (leftArr[i] < temp) {
    //         temp = leftArr[i];
    //     }
    //     for (int j=0; j<weightArr[]; i++) {
    //         if (rightArr[j] < temp2) {
    //             temp2 = rightArr[j];
    //         }
    //         if (temp > temp2) {
    //             pop(weightArr[&temp2]);
    //         }
    //     }
    // }
    // creating a min heap object
    MinHeap minHeap;

    for (int i=0; i<nextFree; i++) {
        minHeap.push(i, weightArr);
    }
    //while the object size is greater than 1
    while (minHeap.size > 1) {
        // declaring left and right weight
        int left = minHeap.pop(weightArr);
        int right = minHeap.pop(weightArr);

        //int root = minHeap.pop(weightArr);
        // makes the root to be the next free slot
        int root = nextFree++;
        // creating the new parent with the new weights
        weightArr[root] = weightArr[left] + weightArr[right];
        //declaring the new pointers left and right
        leftArr[root] = left;
        rightArr[root] = right;
        // push parent into the last of the remainding
        minHeap.push(root, weightArr);
    }

    // 1. Create a MinHeap object.
    // 2. Push all leaf node indices into the heap.
    // 3. While the heap size is greater than 1:
    //    - Pop two smallest nodes
    //    - Create a new parent node with combined weight
    //    - Set left/right pointers
    //    - Push new parent index back into the heap
    // 4. Return the index of the last remaining node (root)

    // returns the index of the last remaining node
    int root = minHeap.pop(weightArr);
    return root; // placeholder
}


// Step 4: Use an STL stack to generate codes
// using the huffman code video to shrink the size of the message being printed to a lower amohnt of bits
void generateCodes(int root, string codes[]) {
    // TODO:
    // using the stl provided to get the code
    stack<pair<int, string>> st;
    st.push({root, ""});
    // while the stack isnt empty pop the top elment
while (!st.empty()) {
    pair<int, string> p = st.top();
    st.pop();
    // have a current node to be the first
    int current =p.first;
    string code = p.second;
    if (leftArr[current] == -1 && rightArr[current] == -1) {
        char ch = charArr[current];
        // shows the code in huffmans binary form
        codes[ch - 'a'] = code;
    }
    else {
        // right edge code
        if (rightArr[current] != -1) {
            st.push({rightArr[current], code + "1"});
        }
        // left edge code
        if (leftArr[current] != -1) {
            st.push({leftArr[current], code + "0"});
        }
    }
}

    // Use stack<pair<int, string>> to simulate DFS traversal.
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}