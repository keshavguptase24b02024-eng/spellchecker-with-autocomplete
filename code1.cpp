#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;

// Trie Node
struct TrieNode {
    bool isEndOfWord;
    unordered_map<char, TrieNode*> children;

    TrieNode() {
        isEndOfWord = false;
    }
};

// Spell Checker class
class SpellChecker {
private:
    TrieNode* root;
    unordered_map<string, vector<string>> cache;

public:
    SpellChecker() {
        root = new TrieNode();
    }

    // Insert a word into the Trie
    void insertWord(string word) {
        TrieNode* current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        current->isEndOfWord = true;
    }

    // Search for a word in the Trie
    bool searchWord(string word) {
        TrieNode* current = root;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                return false;
            }
            current = current->children[ch];
        }
        return current->isEndOfWord;
    }

    // Auto-complete suggestions for a given prefix
    vector<string> autoComplete(string prefix) {
        if (cache.find(prefix) != cache.end()) {
            return cache[prefix];
        }

        TrieNode* current = root;
        for (char ch : prefix) {
            if (current->children.find(ch) == current->children.end()) {
                return {};
            }
            current = current->children[ch];
        }

        vector<string> suggestions;
        queue<pair<string, TrieNode*>> q;
        q.push({prefix, current});

        while (!q.empty()) {
            string word = q.front().first;
            TrieNode* node = q.front().second;
            q.pop();

            if (node->isEndOfWord) {
                suggestions.push_back(word);
            }

            for (auto& child : node->children) {
                q.push({word + child.first, child.second});
            }
        }

        cache[prefix] = suggestions;
        return suggestions;
    }
    
    // Spell check a text
    void spellCheck(string text) {
        string word = "";
        for (int i = 0; i < text.length(); i++) {
            if (isalpha(text[i])) {
                word += tolower(text[i]);
            }
            else {
                if (!word.empty()) {
                    if (!searchWord(word)) {
                        cout << "Misspelled word: " << word << endl;
                        vector<string> suggestions = autoComplete(word);
                        if (!suggestions.empty()) {
                            cout << "Suggestions: ";
                            for (const string& suggestion : suggestions) {
                                cout << suggestion << " ";
                            }
                            cout << endl;
                        }
                    }
                    word = "";
                }
            }
        }
        if (!word.empty() && !searchWord(word)) {
            cout << "Misspelled word: " << word << endl;
            vector<string> suggestions = autoComplete(word);
            if (!suggestions.empty()) {
                cout << "Suggestions: ";
                for (const string& suggestion : suggestions) {
                    cout << suggestion << " ";
                }
                cout << endl;
            }
        }
    }

    // Spell check and replace misspelled words in a text
    string spellCheckAndReplace(string text) {
        string result = "";
        string word = "";
        for (int i = 0; i < text.length(); i++) {
            if (isalpha(text[i])) {
                word += tolower(text[i]);
            }
            else {
                if (!word.empty()) {
                    if (!searchWord(word)) {
                        vector<string> suggestions = autoComplete(word);
                        if (!suggestions.empty()) {
                            word = suggestions[0]; // Replace with the best suggestion
                        }
                    }
                    result += word;
                    word = "";
                }
                result += text[i];
            }
        }
        if (!word.empty() && !searchWord(word)) {
            vector<string> suggestions = autoComplete(word);
            if (!suggestions.empty()) {
                word = suggestions[0]; // Replace with the best suggestion
            }
        }
        result += word;
        return result;
    }
};

// Example usage
int main() {
    // Create a SpellChecker object
    SpellChecker spellChecker;

    // Insert words into the Trie dictionary
    spellChecker.insertWord("hello");
    spellChecker.insertWord("world");
    spellChecker.insertWord("openai");
    spellChecker.insertWord("spell");
    spellChecker.insertWord("checker");
    spellChecker.insertWord("help");
    spellChecker.insertWord("held");
    spellChecker.insertWord("hell");
    spellChecker.insertWord("apple");
    spellChecker.insertWord("banana");
    spellChecker.insertWord("programming");
    spellChecker.insertWord("computer");
    spellChecker.insertWord("science");
    spellChecker.insertWord("algorithm");
    spellChecker.insertWord("data");
    spellChecker.insertWord("structure");
    spellChecker.insertWord("machine");
    spellChecker.insertWord("learning");
    spellChecker.insertWord("python");
    spellChecker.insertWord("java");
    spellChecker.insertWord("cplusplus");
    spellChecker.insertWord("html");
    spellChecker.insertWord("css");
    spellChecker.insertWord("javascript");
    spellChecker.insertWord("network");
    spellChecker.insertWord("database");
    spellChecker.insertWord("software");
    spellChecker.insertWord("engineering");
    spellChecker.insertWord("project");
    spellChecker.insertWord("development");

    // Get input text from the user
    string inputText;
    cout << "Enter a string: ";
    getline(cin, inputText);
    
    spellChecker.spellCheck(inputText);

    // Perform spell check and replace misspelled words
    string correctedText = spellChecker.spellCheckAndReplace(inputText);

    // Display the corrected text
    cout << "Corrected text: " << correctedText << endl;

    return 0;
}
