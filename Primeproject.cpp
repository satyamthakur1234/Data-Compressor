#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

// Function to generate the first N prime numbers using the Sieve of Eratosthenes
vector<int> generatePrimes(int n) {
    int limit = max(1000, static_cast<int>(n * log(n) * 1.5)); // Approximate upper bound for n primes
    vector<bool> isPrime(limit, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i < limit; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j < limit; j += i)
                isPrime[j] = false;
        }
    }

    vector<int> primes;
    for (int i = 2; i < limit && primes.size() < n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

// Function to assign prime numbers to characters
unordered_map<char, int> assignPrimes(const string& text) {
    unordered_map<char, int> primeMap;
    vector<int> primes = generatePrimes(256);
    int index = 0;

    for (char ch : text) {
        if (primeMap.find(ch) == primeMap.end()) {
            primeMap[ch] = primes[index++];
        }
    }
    return primeMap;
}

// Function to compress text using prime multiplication
string compressText(const string& text, unordered_map<char, int>& primeMap) {
    string compressedText = "";
    for (char ch : text) {
        compressedText += to_string(primeMap[ch]) + " ";
    }
    return compressedText;
}

// Function to decompress text using stored prime values
string decompressText(const string& compressedText, unordered_map<char, int>& primeMap) {
    string decompressedText = "";
    unordered_map<int, char> reverseMap;
    for (auto& pair : primeMap) {
        reverseMap[pair.second] = pair.first;
    }

    size_t pos = 0;
    size_t nextPos;
    while ((nextPos = compressedText.find(" ", pos)) != string::npos) {
        int prime = stoi(compressedText.substr(pos, nextPos - pos));
        decompressedText += reverseMap[prime];
        pos = nextPos + 1;
    }
    return decompressedText;
}

int main() {
    string text;
    cout << "Enter text to compress: ";
    getline(cin, text);
    
    unordered_map<char, int> primeMap = assignPrimes(text);
    string compressedText = compressText(text, primeMap);
    
    cout << "Compressed Data: " << compressedText << endl;
    
    string decompressedText = decompressText(compressedText, primeMap);
    cout << "Decompressed Text: " << decompressedText << endl;
    
    return 0;
}