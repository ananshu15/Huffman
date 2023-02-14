#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
using namespace std;
#define EMPTY_STRING ""

class Node
{
public:
	int frequency;
	Node* left, * right;
	char ch;

	Node* getNode(char ch, int frequency, Node* left, Node* right) // Function to assign a new tree nodes
	{
		Node* node = new Node();//creating new node
		node->ch = ch;
		node->frequency = frequency;
		node->left = left;
		node->right = right;
		return node;
	}
};
class comparison : public Node
{
public:
	bool operator()(const Node* lef, const Node* rig) const //highest priority item
	{
		return lef->frequency > rig->frequency;
	}

	bool isLeaf(Node* root) //function to check if Huffman Tree have single node
	{ 
		return root->left == nullptr && root->right == nullptr;
	}

	void encode(Node* root, string str, unordered_map<char, string>& huffmanCode)//traversing huffman tree and storing it
	{
		if (root == nullptr) //checking if root is null
		{
			return;
		}
		if (isLeaf(root)) // finding leaf node is there
		{
			huffmanCode[root->ch] = (str != EMPTY_STRING) ? str : "1";
		}
		encode(root->left, str + "0", huffmanCode);
		encode(root->right, str + "1", huffmanCode);
	}

	void decode(Node* root, int& index, string str) //traversing hufman tree and decoding it
	{
		if (root == nullptr)//checking if root is null
		{
			return;
		}
		if (isLeaf(root))//finding leaf node is there
		{
			cout << root->ch;
			return;
		}

		index++;

		if (str[index] == '0') {
			decode(root->left, index, str);
		}
		else {
			decode(root->right, index, str);
		}
	}

	void buildHuffmanTree(string text)//building huffman tree
	{
		if (text == EMPTY_STRING) // checking for the empty string
		{
			return;
		}
		unordered_map<char, int> freq;
		for (char ch : text)//counting the frequency of each character in string 
		{
			freq[ch]++;
		}
		priority_queue<Node*, vector<Node*>, comparison> pq;//creating priority queue

		for (auto &pair : freq) //creating leaf node for character
		{
			pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
		}
		while (pq.size() != 1)
		{
			Node* left = pq.top(); pq.pop();//removing two nodes with highest priority
			Node* right = pq.top(); pq.pop();

			int sum = left->frequency + right->frequency;
			pq.push(getNode('\0', sum, left, right));
		}
		Node* root = pq.top();//storing pointer to root node
		unordered_map<char, string> huffmanCode;
		encode(root, EMPTY_STRING, huffmanCode);

		cout << "Huffman Codes are as follows:\n" << endl;
		for (auto &pair : huffmanCode) {
			cout << pair.first << " " << pair.second << endl;
		}

		cout << "\n Original string:\n" << text << endl;

		string str;
		for (char ch : text) {
			str += huffmanCode[ch];
		}                            //printing encoded string

		cout << "\nEncoded string is:\n" << str << endl;
		cout << "\nDecoded string is:\n";

		if (isLeaf(root))
		{
			while (root->frequency--)
			{
				cout << root->ch;
			}
		}
		else
		{
			int index = -1;
			while (index < (int)str.size() - 1)//traversing huffman tree and decodeding the string
			{
				decode(root, index, str);
			}
		}
	}
};
int main()
{
	comparison c;
	string text;
	cout << "Enter the string: ";
	cin >> text;
	c.buildHuffmanTree(text);

	return 0;
}