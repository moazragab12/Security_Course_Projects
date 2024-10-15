#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <map>

#define int unsigned long long
using namespace std;
#define get_bit(x, shift, bit, mask)  do{ \
        bit=(x& (mask<<shift));      \
        bit=bit>>shift;\
}while(0);
map<char, int> inputKey;
int Keys_Before_Permutations_56_bit[17];
//we start with k[1] ignore k[0] and k[16] is the same as k[0] but we use it to make the code easier
int Keys_After_Permutations_48_bit[17];
int keys_Shift_for_Permutations[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
int const key_permutation_values[56] = { 57, 49, 41, 33, 25, 17, 9,
                                        1, 58, 50, 42, 34, 26, 18,
                                        10, 2, 59, 51, 43, 35, 27,
                                        19, 11, 3, 60, 52, 44, 36,
                                        63, 55, 47, 39, 31, 23, 15,
                                        7, 62, 54, 46, 38, 30, 22,
                                        14, 6, 61, 53, 45, 37, 29,
                                        21, 13, 5, 28, 20, 12, 4 };
int const Permutation_for_CDNs[48] = {
        14, 17, 11, 24, 1, 5,
        3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8,
        16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32
};
const int Data_Permutations_bits[64] = {
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7
};
const int E_bit_selection_table[48] = {
    32, 1, 2, 3, 4, 5, 4, 5, 6, 7,
    8, 9, 8, 9, 10, 11, 12, 13, 12,
    13, 14, 15, 16, 17, 16, 17, 18,
    19, 20, 21, 20, 21, 22, 23, 24,
    25, 24, 25, 26, 27, 28, 29, 28,
    29, 30, 31, 32, 1
};
const int P_table[32] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
};
const int S_box[8][4][16] = {
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    {
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
    },
    {
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
    },
    {
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
    },
    {
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
    },
    {
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    },
    {
        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
    },
    {
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    }
};
const int final_permutation_table[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};
/**
 * @brief Converts a string to its corresponding hexadecimal integer value.
 *
 * @param s String input to be converted (should be less than 8 characters).
 * @return int The resulting hexadecimal integer.
 */
 //note 64 bit to fit in long long
int BIN_To_DEC(string binary) {
    int decimal = 0;
    int counter = 0;
    for (int i = binary.size() - 1; i >= 0; i--) {
        if (binary[i] == '1') {
            decimal += pow(2, counter);
        }
        counter++;
    }
    return decimal;
}
// Function to convert Hexadecimal to Binary
string hexToBinary(string hex) {
    string binary = "";
    for (char ch : hex) {
        switch (toupper(ch)) {
        case '0': binary += "0000"; break;
        case '1': binary += "0001"; break;
        case '2': binary += "0010"; break;
        case '3': binary += "0011"; break;
        case '4': binary += "0100"; break;
        case '5': binary += "0101"; break;
        case '6': binary += "0110"; break;
        case '7': binary += "0111"; break;
        case '8': binary += "1000"; break;
        case '9': binary += "1001"; break;
        case 'A': binary += "1010"; break;
        case 'B': binary += "1011"; break;
        case 'C': binary += "1100"; break;
        case 'D': binary += "1101"; break;
        case 'E': binary += "1110"; break;
        case 'F': binary += "1111"; break;
        default: binary = "Invalid Hexadecimal Digit"; return binary;
        }
    }
    return binary;
}

// Function to convert Binary to Hexadecimal
string binaryToHex(string binary) {
    if (binary.length() % 4 != 0) {
        binary = string(4 - (binary.length() % 4), '0') + binary;
    }

    string hex = "";
    for (size_t i = 0; i < binary.length(); i += 4) {
        string fourBits = binary.substr(i, 4);
        if (fourBits == "0000") hex += "0";
        else if (fourBits == "0001") hex += "1";
        else if (fourBits == "0010") hex += "2";
        else if (fourBits == "0011") hex += "3";
        else if (fourBits == "0100") hex += "4";
        else if (fourBits == "0101") hex += "5";
        else if (fourBits == "0110") hex += "6";
        else if (fourBits == "0111") hex += "7";
        else if (fourBits == "1000") hex += "8";
        else if (fourBits == "1001") hex += "9";
        else if (fourBits == "1010") hex += "A";
        else if (fourBits == "1011") hex += "B";
        else if (fourBits == "1100") hex += "C";
        else if (fourBits == "1101") hex += "D";
        else if (fourBits == "1110") hex += "E";
        else if (fourBits == "1111") hex += "F";
        else {
            return "Invalid Binary Input";
        }
    }
    return hex;
}

// Function to permute the characters of the string 'k' based on the array 'arr'
string permute(const string& k, const int arr[], int n) {
    string permutation = "";
    for (int i = 0; i < n; ++i) {
        permutation += k[arr[i] - 1];
    }
    return permutation;
}

// Function to shift the bits of the string 'k' to the left by 'nth_shifts'
string shift_left(string k, int nth_shifts) {
    for (int i = 0; i < nth_shifts; ++i) {
        rotate(k.begin(), k.begin() + 1, k.end());
    }
    return k;
}

// XOR two binary strings
string xor_str(string a, string b) {
    string result = "";
    for (size_t i = 0; i < a.size(); ++i) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

// DES Encryption function (unchanged)
string encrypt(string pt, vector<string> rkb, vector<string> rk) {
    pt = hexToBinary(pt);
    pt = permute(pt, Data_Permutations_bits, 64);
    string left = pt.substr(0, 32);
    string right = pt.substr(32, 64);

    for (int i = 0; i < 16; i++) {
        string right_expanded = permute(right, E_bit_selection_table, 48);
        string xor_x = xor_str(right_expanded, rkb[i]);
        string sbox_str = "";
        for (int j = 0; j < 8; ++j) {
            string row_bin = string(1, xor_x[j * 6]) + string(1, xor_x[j * 6 + 5]);
            int row = stoi(row_bin, nullptr, 2);  // Convert to decimal
            string col_bin = xor_x.substr(j * 6 + 1, 4);
            int col = stoi(col_bin, nullptr, 2);  // Convert to decimal
            int val = S_box[j][row][col];
            sbox_str += bitset<4>(val).to_string();  // Convert the value to 4-bit binary string
        }
        sbox_str = permute(sbox_str, P_table, 32);
        string result = xor_str(left, sbox_str);
        left = result;

        if (i != 15) {
            swap(left, right);
        }
    }

    string combine = left + right;
    string cipher_text = permute(combine, final_permutation_table, 64);
    return cipher_text;
}

string stringToBinary(string text) {
    string binary = "";
    for (char c : text) {
        string charBinary = "";
        for (int i = 0; i < 8; ++i) {
            charBinary = ((c >> i) & 1 ? '1' : '0') + charBinary;
        }
        binary += charBinary;
    }
    return binary;
}
string binaryToString(string binary) {
    string text = "";
    for (size_t i = 0; i < binary.size(); i += 8) {
        string byte = binary.substr(i, 8);
        char character = static_cast<char>(stoi(byte, nullptr, 2));
        text += character;
    }
    return text;
}

signed main() {
    string pt, key, inputType, keyType;
    cout << "Enter input type (hex, binary, or string): ";
    cin >> inputType;
    cout << "Enter key type (hex, binary, or string): ";
    cin >> keyType;

    if (inputType == "hex") {
        cout << "Enter 16-character hexadecimal plaintext: ";
        cin >> pt;
    } else if (inputType == "binary") {
        cout << "Enter 64-bit binary plaintext: ";
        cin >> pt;
        pt = binaryToHex(pt);
    } else if (inputType == "string") {
        cout << "Enter string plaintext: ";
        cin >> pt;
        pt = stringToBinary(pt);
        pt = pt.substr(0, 64) + string(64 - pt.size(), '0');
        pt = binaryToHex(pt);
    } else {
        cerr << "Error: Invalid input type!" << endl;
        return 1;
    }

    if (keyType == "hex") {
        cout << "Hex key: ";
        cin >> key;
    } else if (keyType == "binary") {
        cout << "Binary key: ";
        cin >> key;
        key = binaryToHex(key);
    } else if (keyType == "string") {
        cout << "String key: ";
        cin >> key;
        key = stringToBinary(key);
        key = key.substr(0, 64) + string(64 - key.size(), '0');
        key = binaryToHex(key);
    } else {
        cerr << "Error: Invalid key type!" << endl;
        return 1;
    }

    if (pt.length() != 16 || key.length() != 16) {
        cerr << "Error: Both plaintext and key must be 16 hexadecimal characters!" << endl;
        return 1;
    }
    key = hexToBinary(key);
    key = permute(key, key_permutation_values, 56);
    string left = key.substr(0, 28);
    string right = key.substr(28, 56);
    vector<string> rkb;
    vector<string> rk;
    for (int i = 0; i < 16; ++i) {
        left = shift_left(left, keys_Shift_for_Permutations[i]);
        right = shift_left(right, keys_Shift_for_Permutations[i]);
        string combine_str = left + right;
        string round_key = permute(combine_str, Permutation_for_CDNs, 48);
        rkb.push_back(round_key);
        rk.push_back(binaryToHex(round_key));
    }

    cout << "\n********** Encryption **********" << endl;
    string cipher_text_bin = encrypt(pt, rkb, rk);
    string cipher_text = binaryToHex(cipher_text_bin);
    cout << "Cipher Text in hexa: " << cipher_text << endl;
    //cout << "Cipher Text in binary: " << hexToBinary(cipher_text) << endl;

    cout << "\n********** Decryption **********" << endl;
    vector<string> rkb_rev = rkb;
    vector<string> rk_rev = rk;
    reverse(rkb_rev.begin(), rkb_rev.end());
    reverse(rk_rev.begin(), rk_rev.end());
    string decrypted_bin = encrypt(cipher_text, rkb_rev, rk_rev);
    string decrypted_text = binaryToHex(decrypted_bin);

    if (inputType == "string") {
        cout << "Plain Text (decrypted) string: " << binaryToString(hexToBinary(decrypted_text)) << endl;
    } else {
        cout << "Plain Text (decrypted) string: Not applicable for non-string input." << endl;
    }
    cout << "Plain Text (decrypted) hex: " << decrypted_text << endl;
    cout << "Plain Text (decrypted) bin: " << hexToBinary(decrypted_text) << endl;
    return 0;
}










