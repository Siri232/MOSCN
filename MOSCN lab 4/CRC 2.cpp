#include <iostream>
#include <string>
using namespace std;

char xor_bit(char a, char b) {
    return (a == b) ? '0' : '1';
}

string mod2_division(string dividend, string divisor) {
    int pick = divisor.length();
    string temp = dividend.substr(0, pick);

    while (pick < dividend.length()) {
        if (temp[0] == '1') {
            for (int i = 1; i < divisor.length(); i++)
                temp[i] = xor_bit(temp[i], divisor[i]);
        } else {
            for (int i = 1; i < divisor.length(); i++)
                temp[i] = xor_bit(temp[i], '0');
        }
        temp.erase(temp.begin());
        temp += dividend[pick];
        pick++;
    }

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

    cout << "Enter generator polynomial in binary (example x^3 + 1 = 1001): ";
    cin >> generator;

    int r = generator.length() - 1;

    // Append zeros
    string appended = data + string(r, '0');

    // CRC remainder
    string remainder = mod2_division(appended, generator);

    // Transmitted codeword
    string transmitted = data + remainder;

    cout << "\nCRC Remainder: " << remainder << endl;
    cout << "Actual transmitted bit string: " << transmitted << endl;

    // Simulate error: invert 3rd bit
    string received = transmitted;
    if (received.length() >= 3)
        received[2] = (received[2] == '0') ? '1' : '0';

    cout << "\nSimulated received bit string (3rd bit inverted): " << received << endl;

    // Receiver performs CRC check
    string receiver_remainder = mod2_division(received, generator);

    if (receiver_remainder.find('1') != string::npos) {
        cout << "\nReceiver Remainder: " << receiver_remainder << endl;
        cout << "ERROR DETECTED: Received frame is corrupted.\n";
    } else {
        cout << "\nReceiver Remainder: " << receiver_remainder << endl;
        cout << "NO ERROR DETECTED: Frame is correct.\n";
    }

    return 0;
}

