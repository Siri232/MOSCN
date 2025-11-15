#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int getRedundantBits(int m) {
    int r = 0;
    while (pow(2, r) < (m + r + 1)) r++;
    return r;
}

vector<int> generateHamming(vector<int> data) {
    int m = data.size();
    int r = getRedundantBits(m);
    int total = m + r;

    vector<int> hamming(total + 1);
    int j = 0;

    for (int i = 1; i <= total; i++) {
        if ((i & (i - 1)) == 0) {
            hamming[i] = 0;
        } else {
            hamming[i] = data[j++];
        }
    }

    for (int i = 0; i < r; i++) {
        int pos = pow(2, i);
        int parity = 0;
        for (int k = 1; k <= total; k++) {
            if (k & pos) parity ^= hamming[k];
        }
        hamming[pos] = parity;
    }

    return hamming;
}

int detectError(vector<int> code) {
    int total = code.size() - 1;
    int r = 0;

    while (pow(2, r) <= total) r++;

    int errorPos = 0;

    for (int i = 0; i < r; i++) {
        int pos = pow(2, i);
        int parity = 0;
        for (int k = 1; k <= total; k++) {
            if (k & pos) parity ^= code[k];
        }
        if (parity != 0) errorPos += pos;
    }
    return errorPos;
}

int main() {
    string input;
    cout << "Enter original binary data: ";
    cin >> input;

    vector<int> data;

    // FIXED: works on all compilers
    for (int i = 0; i < input.length(); i++) {
        data.push_back(input[i] - '0');
    }

    vector<int> hamming = generateHamming(data);

    cout << "\nGenerated Hamming Code: ";
    for (int i = 1; i < hamming.size(); i++)
        cout << hamming[i];
    cout << endl;

    string received;
    cout << "\nEnter received Hamming Code: ";
    cin >> received;

    vector<int> rec(received.size() + 1);
    for (int i = 1; i <= received.size(); i++)
        rec[i] = received[i - 1] - '0';

    int errorPos = detectError(rec);

    if (errorPos == 0) {
        cout << "\nNo error detected.\n";
    } else {
        cout << "\nError detected at bit position: " << errorPos << endl;
        rec[errorPos] ^= 1;

        cout << "Corrected Code: ";
        for (int i = 1; i < rec.size(); i++)
            cout << rec[i];
        cout << endl;
    }

    return 0;
}



