#include <iostream>
#include <string>
using namespace std;

// Function to perform XOR on two bits
char xor_bit(char a, char b) {
    return (a == b) ? '0' : '1';
}

// Function to perform Modulo-2 Division
string mod2_division(string dividend, string divisor) {
    int pick = divisor.length();
    string temp = dividend.substr(0, pick);

    while (pick < dividend.length()) {
        if (temp[0] == '1') {
            // XOR with divisor
            for (int i = 1; i < divisor.length(); i++)
                temp[i] = xor_bit(temp[i], divisor[i]);

        } else {
            // XOR with all 0's
            for (int i = 1; i < divisor.length(); i++)
                temp[i] = xor_bit(temp[i], '0');
        }

        temp.erase(temp.begin());
        temp += dividend[pick];
        pick++;
    }

    // Last step
    if (temp[0] == '1') {
        for (int i = 1; i < divisor.length(); i++)
            temp[i] = xor_bit(temp[i], divisor[i]);
    } else {
        for (int i = 1; i < divisor.length(); i++)
            temp[i] = xor_bit(temp[i], '0');
    }

    temp.erase(temp.begin());
    return temp;  // Remainder
}

int main() {
    string data, generator;

    cout << "Enter the data bitstream: ";
    cin >> data;

    cout << "Enter generator polynomial in binary (example x^4 + x + 1 = 10011): ";
    cin >> generator;

    int r = generator.length() - 1;

    // Append r zeros to data
    string data_appended = data + string(r, '0');

    // Perform modulo-2 division
    string remainder = mod2_division(data_appended, generator);

    // Final transmitted frame
    string transmitted = data + remainder;

    cout << "\nCRC Remainder: " << remainder << endl;
    cout << "Transmitted Bit String: " << transmitted << endl;

    return 0;
}

