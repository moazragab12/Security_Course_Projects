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
    for (int i = 1; i < 17; i++) {
        /* i = 0 can be useless as we already ignore k[0] */
        int ret = 0;
        for (int j = 0; j < 48; j++) {
            int temp = 0;
            get_bit(Keys_Before_Permutations_56_bit[i], (56ULL - Permutation_for_CDNs[j]), temp, 1ULL);
            // cout << temp;
            //  if (j % 4 == 0 & 1) cout << " ";
            ret |= temp << (48 - j - 1);

        }
        Keys_After_Permutations_48_bit[i] = ret;
    }
    //  Keys_After_Permutations_48_bit[16]=Keys_After_Permutations_48_bit[0];

}


/*We want to expand each block R(n-1) from 32 bits to 48 bits*/
int expand(int input) {
    int output = 0;
    for (int i = 0; i < 48; i++) {
        output |= ((input >> (32 - E_bit_selection_table[i])) & 1) << (47 - i);
    }
    return output;
}

/*After we finished expanding...
We now have 48 bits , 8 blocks (6 bits each)
So, every block will be of 4 bits, thus we have 32 bits in total*/
int substitute(int input) {
    int output = 0;
    for (int i = 0; i < 8; i++) {
        int row = ((input & (1 << 6 * i)) >> (6 * i)) + ((input & (1 << 6 * i + 5)) >> (6 * i + 5));
        int col = (input & (0b011110 << 6 * i + 1)) >> (6 * i + 1);
        output |= S_box[i][row][col] << (4 * i);
    }
    return output;
}

/*We have to do the permutation of the S-box output which leads to "Avalanche effect"*/
int permutation(int input) {
    int output = 0;
    for (int i = 0; i < 32; i++) {
        output |= ((input >> (32 - P_table[i])) & 1) << (31 - i);
    }
    return output;
}

/*XOR*/
int XOR(int a, int b) {
    return a ^ b;
}

/*Feistel function that expands, substitutes, permutates, and 'XOR's*/
int feistel(int R, int key) {
    int expanded = expand(R);
    int substituted = substitute(XOR(expanded, key));
    return permutation(substituted);
}

/*Apply initial permutation IP*/
int initial_permutation(int input) {
    int output = 0;
    for (int i = 0; i < 64; i++) {
        output |= ((input >> (64 - Data_Permutations_bits[i])) & 1) << (63 - i);
    }
    return output;
}


/*Apply final permutation IP^-1*/
int final_permutation(int input) {
    int output = 0;
    for (int i = 0; i < 64; i++) {
        output |= ((input >> (64 - final_permutation_table[i])) & 1) << (63 - i);
    }
    return output;
}

/*Encode 64-bit block using Feistel rounds*/
int Encode_64_bit_Data(string s){
    int x = convert_string_to_hex(s);
    int block = initial_permutation(x);
    int L = block >> 32;
    int R = block & 0xFFFFFFFF;
    for (int i = 1; i < 17; i++) {
        int temp = R;
        R = XOR(L, feistel(R, Keys_After_Permutations_48_bit[i]));
        L = temp;
    }
    //combine L and R
    int output = (R << 32) | L;
    return final_permutation(output);
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



