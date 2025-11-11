#include <iostream>
#include <string>
using namespace std;

// Function to perform XOR operation between two binary strings
string xorOperation(string a, string b) {
    string result = "";
    for (size_t i = 1; i < b.size(); i++)
        result += (a[i] == b[i]) ? '0' : '1';
    return result;
}

// Function to perform modulo-2 division
string mod2Division(string dividend, string divisor) {
    int pick = divisor.size();
    string tmp = dividend.substr(0, pick);
    int n = dividend.size();

    while (pick < n) {
        if (tmp[0] == '1')
            tmp = xorOperation(divisor, tmp) + dividend[pick];
        else
            tmp = xorOperation(string(pick, '0'), tmp) + dividend[pick];
        pick++;
    }

    // For the last n bits
    if (tmp[0] == '1')
        tmp = xorOperation(divisor, tmp);
    else
        tmp = xorOperation(string(pick, '0'), tmp);

    return tmp;
}

int main() {
    string data = "1101011011";
    string generator = "10011";

    int m = generator.size();
    string appendedData = data + string(m - 1, '0'); // Append (m-1) zeros

    cout << "Data bits: " << data << endl;
    cout << "Generator: " << generator << endl;
    cout << "Appended data: " << appendedData << endl;

    string remainder = mod2Division(appendedData, generator);
    cout << "Remainder (CRC bits): " << remainder << endl;

    // XOR remainder with appended data to get transmitted codeword
    string transmitted = data + remainder;
    cout << "Transmitted frame (data + CRC): " << transmitted << endl;

    return 0;
}



