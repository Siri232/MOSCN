#include <iostream>
#include <string>
using namespace std;

// XOR operation between two binary strings (skip the first bit)
string xorOp(string a, string b) {
    string result = "";
    for (int i = 1; i < b.size(); i++) {
        if (a[i] == b[i])
            result += '0';
        else
            result += '1';
    }
    return result;
}

// Perform Modulo-2 Division
string mod2Division(string dividend, string divisor) {
    int pick = divisor.size();
    string tmp = dividend.substr(0, pick);
    int n = dividend.size();

    while (pick < n) {
        if (tmp[0] == '1')
            tmp = xorOp(divisor, tmp) + dividend[pick];
        else
            tmp = xorOp(string(pick, '0'), tmp) + dividend[pick];
        pick++;
    }

    if (tmp[0] == '1')
        tmp = xorOp(divisor, tmp);
    else
        tmp = xorOp(string(pick, '0'), tmp);

    return tmp;
}

// Flip (invert) a bit at a given position
string flipBit(string s, int pos) {
    if (pos < 0 || pos >= s.size())
        return s;
    if (s[pos] == '0')
        s[pos] = '1';
    else
        s[pos] = '0';
    return s;
}

int main() {
    string data = "10011101";   // Given data bits
    string generator = "1001";  // Given generator polynomial (x^3 + 1)
    int genDegree = generator.size() - 1;

    cout << "Data bits:       " << data << endl;
    cout << "Generator bits:  " << generator << endl;

    // Step 1: Append (m-1) zeros
    string appended = data + string(genDegree, '0');
    cout << "Appended data:   " << appended << endl;

    // Step 2: Perform division to find remainder (CRC)
    string remainder = mod2Division(appended, generator);
    cout << "Calculated CRC (remainder): " << remainder << endl;

    // Step 3: Form transmitted frame
    string transmitted = data + remainder;
    cout << "Transmitted frame (data + CRC): " << transmitted << endl;

    // Step 4: Simulate bit error (flip 3rd bit from left)
    int flipIndex = 2; // 0-based index
    string received = flipBit(transmitted, flipIndex);
    cout << "\nSimulate error: flip 3rd bit from left" << endl;
    cout << "Received frame: " << received << endl;

    // Step 5: Receiver checks CRC again
    string recvRemainder = mod2Division(received, generator);
    cout << "Receiver remainder: " << recvRemainder << endl;

    // Step 6: Check if remainder is all zeros
    bool isZero = true;
    for (int i = 0; i < recvRemainder.size(); i++) {
        if (recvRemainder[i] != '0') {
            isZero = false;
            break;
        }
    }

    if (isZero)
        cout << "Receiver: No error detected (remainder is zero)." << endl;
    else
        cout << "Receiver: Error detected (non-zero remainder)." << endl;

    return 0;
}




