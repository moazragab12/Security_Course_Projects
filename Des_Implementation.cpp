#include<bits/stdc++.h>

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
int keys_Shift_for_Permutations[17] = {0, 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
int const key_permutation_values[56] = {57, 49, 41, 33, 25, 17, 9,
                                        1, 58, 50, 42, 34, 26, 18,
                                        10, 2, 59, 51, 43, 35, 27,
                                        19, 11, 3, 60, 52, 44, 36,
                                        63, 55, 47, 39, 31, 23, 15,
                                        7, 62, 54, 46, 38, 30, 22,
                                        14, 6, 61, 53, 45, 37, 29,
                                        21, 13, 5, 28, 20, 12, 4};
int const Premutation_for_CDNs[48] = {
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
/**
 * @brief Converts a string to its corresponding hexadecimal integer value.
 *
 * @param s String input to be converted (should be less than 8 characters).
 * @return int The resulting hexadecimal integer.
 */
//note 64 bit to fit in long long
int convert_string_to_hex(string s) {
    if (s.size() > 8) {
        cout << "String is too long";
        return 0;
    }
    int x = 0b0;
    int n = s.size();
    int shiftchar = 0;
    for (long long i = n - 1; i >= 0; i--) {
        x |= ((int) s[i]) << shiftchar;

        shiftchar += 8;
    }

    return x;
}
/**
 * @brief Converts a hexadecimal key string into an integer.
 *
 * @param key A string representing the hexadecimal key.
 * @return int The resulting integer.
 */
int convert_hexaKey_into_hex(string key) {
    int x = 0;
    for (int i = 0; i < key.size(); i++) {
        x = (x << 4) | inputKey[key[i]];
    }
    return x;
}
/**
 * @brief Generates the initial key (key0) for DES encryption by applying a permutation to the 64-bit key.
 *
 * This function performs a permutation on the provided 64-bit key (denoted as `s`) based on
 * predefined permutation values (`key_permutation_values`). The result is a 56-bit key used
 * for further key scheduling steps. This function is crucial for setting up the initial state
 * of the DES key schedule.
 *
 * @param s A 64-bit integer representing the input key.
 * @return int The 56-bit permuted key (key0) used for the first round of DES.
 */
int generate_key0(int s) {
    int ret = 0;


    for (int i = 0; i < 56; i++) {
        int temp = 0;
        get_bit(s, 64 - key_permutation_values[i], temp, 1ULL);
        ret |= temp << (56 - i - 1);

    }
    Keys_Before_Permutations_56_bit[0] = ret;
    return ret;

}

/**
 * @brief Generates the 48-bit keys after permutation for each round (from key1 to key16).
 */
void generate_Keys_Permutation() {
    for (int i = 0; i < 17; i++) {
        int ret = 0;
        for (int j = 0; j < 48; j++) {
            int temp = 0;
            get_bit(Keys_Before_Permutations_56_bit[i], (56ULL - Premutation_for_CDNs[j]), temp, 1ULL);
            // cout << temp;
            //  if (j % 4 == 0 & 1) cout << " ";
            ret |= temp << (48 - j - 1);

        }
        Keys_After_Permutations_48_bit[i] = ret;
    }
    //  Keys_After_Permutations_48_bit[16]=Keys_After_Permutations_48_bit[0];

}
//uncomplete yet
int Encode_64_bit_Data(string s) {
    int x = convert_string_to_hex(s);
    int ret = 0;

    return ret;
}

/**
 * @brief Generates 16 subkeys from the initial key0 by left-shifting C and D components.
 */
void generete_key1_to_key15() {
    int C = 0, D = 0;
   // Keys_Before_Permutations_56_bit[0] = 0b11110000110011001010101011110101010101100110011110001111;
    // Split key0 into C and D
    C = Keys_Before_Permutations_56_bit[0] >> 28;
    D = Keys_Before_Permutations_56_bit[0] & 0xFFFFFFF;

    // Generate 16 subkeys
    for (int i = 0; i < 17; i++) {
        // Left shift C and D
        C = ((C << keys_Shift_for_Permutations[i]) | (C >> (28 - keys_Shift_for_Permutations[i]))) & 0xFFFFFFF;
        D = ((D << keys_Shift_for_Permutations[i]) | (D >> (28 - keys_Shift_for_Permutations[i]))) & 0xFFFFFFF;

        // Combine C and D to form the subkey
        int CD = (C << 28) | D;


        Keys_Before_Permutations_56_bit[i] = CD;
    }

}

/**
 * @brief Converts a hexadecimal integer back into a string.
 *
 * @param x The input hexadecimal integer.
 * @return string The resulting string after conversion.
 */
string convert_hex_to_string(int x) {
    string s = "";
    int mask = 0xff;
    for (int i = 0; i < 8 && x > 0; i++) {

        s = s + char((x) & mask);
        x >>= 8;
    }
    reverse(s.begin(), s.end());
    return s;
}

/**
 * @brief Main solving function that sets up the DES algorithm by generating keys and permutations.
 */
void solve() {
    string PlainText;
    string Key = "4A45B36C89948598";
    string CipherText;


    int x = convert_hexaKey_into_hex(Key);
    generate_key0(x);
    generete_key1_to_key15();
    generate_Keys_Permutation();
    //end
}

signed main() {

    int t = 1;
    for (int i = 0; i < 10; i++) {
        inputKey['0' + i] = i;
    }
    for (int i = 0; i < 6; i++) {
        inputKey['A' + i] = 10 + i;
    }
    // cin >> t;
    while (t--) solve();

    return 0;
}
