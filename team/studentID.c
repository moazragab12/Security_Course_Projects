#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h>
unsigned long long Keys_Before_Permutations_56_bit[17];
unsigned long long Keys_After_Permutations_48_bit[17];
unsigned long long keys_Shift_for_Permutations[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
const int key_permutation_values[56] = { 57, 49, 41, 33, 25, 17, 9,
                                        1, 58, 50, 42, 34, 26, 18,
                                        10, 2, 59, 51, 43, 35, 27,
                                        19, 11, 3, 60, 52, 44, 36,
                                        63, 55, 47, 39, 31, 23, 15,
                                        7, 62, 54, 46, 38, 30, 22,
                                        14, 6, 61, 53, 45, 37, 29,
                                        21, 13, 5, 28, 20, 12, 4 };
const int Permutation_for_CDNs[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};
const int permutation_table[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};
const int E_table[48] = {
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
char* hexToBinary(const char* hex) {
    static char binary[65];
    binary[0] = '\0';
    for (size_t i = 0; i < strlen(hex); ++i) {
        switch (hex[i]) {
        case '0': strcat(binary, "0000"); break;
        case '1': strcat(binary, "0001"); break;
        case '2': strcat(binary, "0010"); break;
        case '3': strcat(binary, "0011"); break;
        case '4': strcat(binary, "0100"); break;
        case '5': strcat(binary, "0101"); break;
        case '6': strcat(binary, "0110"); break;
        case '7': strcat(binary, "0111"); break;
        case '8': strcat(binary, "1000"); break;
        case '9': strcat(binary, "1001"); break;
        case 'A': strcat(binary, "1010"); break;
        case 'B': strcat(binary, "1011"); break;
        case 'C': strcat(binary, "1100"); break;
        case 'D': strcat(binary, "1101"); break;
        case 'E': strcat(binary, "1110"); break;
        case 'F': strcat(binary, "1111"); break;
        default: return "Invalid Hex Input";
        }
    }
    return binary;
}
char* binaryToHex(const char* binary) {
    static char hex[17];
    hex[0] = '\0';
    char paddedBinary[65];
    strcpy(paddedBinary, binary);
    if (strlen(paddedBinary) % 4 != 0) {
        char padding[5] = "0000";
        strncat(padding, paddedBinary, 4 - (strlen(paddedBinary) % 4));
        strcpy(paddedBinary, padding);
    }
    for (size_t i = 0; i < strlen(paddedBinary); i += 4) {
        char fourBits[5];
        strncpy(fourBits, paddedBinary + i, 4);
        fourBits[4] = '\0';
        if (strcmp(fourBits, "0000") == 0) strcat(hex, "0");
        else if (strcmp(fourBits, "0001") == 0) strcat(hex, "1");
        else if (strcmp(fourBits, "0010") == 0) strcat(hex, "2");
        else if (strcmp(fourBits, "0011") == 0) strcat(hex, "3");
        else if (strcmp(fourBits, "0100") == 0) strcat(hex, "4");
        else if (strcmp(fourBits, "0101") == 0) strcat(hex, "5");
        else if (strcmp(fourBits, "0110") == 0) strcat(hex, "6");
        else if (strcmp(fourBits, "0111") == 0) strcat(hex, "7");
        else if (strcmp(fourBits, "1000") == 0) strcat(hex, "8");
        else if (strcmp(fourBits, "1001") == 0) strcat(hex, "9");
        else if (strcmp(fourBits, "1010") == 0) strcat(hex, "A");
        else if (strcmp(fourBits, "1011") == 0) strcat(hex, "B");
        else if (strcmp(fourBits, "1100") == 0) strcat(hex, "C");
        else if (strcmp(fourBits, "1101") == 0) strcat(hex, "D");
        else if (strcmp(fourBits, "1110") == 0) strcat(hex, "E");
        else if (strcmp(fourBits, "1111") == 0) strcat(hex, "F");
        else return "Invalid Binary Input";
    }
    return hex;
}
char* expand(const char* input, const int* E_table, size_t table_size) {
    static char output[49];
    output[0] = '\0';
    for (size_t i = 0; i < table_size; ++i) {
        if (E_table[i] - 1 < strlen(input)) {
            strncat(output, input + E_table[i] - 1, 1);
        } else {
            strcat(output, "0");
        }
    }
    return output;
}
void substitute(const char* input, char* output) {
    output[0] = '\0';
    for (int i = 0; i < 8; i++) {
        char six_bit_block[7] = { input[i * 6], input[i * 6 + 1], input[i * 6 + 2], input[i * 6 + 3], input[i * 6 + 4], input[i * 6 + 5], '\0' };
        int row = (six_bit_block[0] - '0') * 2 + (six_bit_block[5] - '0');
        int col = (six_bit_block[1] - '0') * 8 + (six_bit_block[2] - '0') * 4 + (six_bit_block[3] - '0') * 2 + (six_bit_block[4] - '0');
        int val = S_box[i][row][col];
        char val_bin[5];
        for (int j = 3; j >= 0; --j) {
            val_bin[3 - j] = ((val >> j) & 1) ? '1' : '0';
        }
        val_bin[4] = '\0';
        strcat(output, val_bin);
    }
}
char* permute(const char* input, const int* permutation_table, size_t table_size) {
    static char output[33];
    output[0] = '\0';
    for (size_t i = 0; i < table_size; ++i) {
        if (permutation_table[i] - 1 < strlen(input)) {
            strncat(output, input + permutation_table[i] - 1, 1);
        } else {
            strcat(output, "0");
        }
    }
    return output;
}
char* xor_str(const char* a, const char* b) {
    static char output[49];
    output[0] = '\0';
    for (size_t i = 0; i < strlen(a); ++i) {
        strcat(output, a[i] == b[i] ? "0" : "1");
    }
    return output;
}
char* shift_left(const char* input, size_t nth_shifts) {
    static char output[65];
    strcpy(output, input);
    for (size_t i = 0; i < nth_shifts; ++i) {
        char first = output[0];
        memmove(output, output + 1, strlen(output) - 1);
        output[strlen(output) - 1] = first;
    }
    return output;
}
void generateRoundKeys(const char* keyBinary, char rkb[16][49], char rk[16][17]) {
    char permuted_key[57];
    strcpy(permuted_key, permute(keyBinary, key_permutation_values, 56));
    char left[29], right[29];
    strncpy(left, permuted_key, 28);
    left[28] = '\0';
    strncpy(right, permuted_key + 28, 28);
    right[28] = '\0';
    for (int i = 0; i < 16; ++i) {
        strcpy(left, shift_left(left, keys_Shift_for_Permutations[i]));
        strcpy(right, shift_left(right, keys_Shift_for_Permutations[i]));
        char combine_str[57];
        snprintf(combine_str, sizeof(combine_str), "%s%s", left, right);
        strcpy(rkb[i], permute(combine_str, Permutation_for_CDNs, 48));
        strcpy(rk[i], binaryToHex(rkb[i]));
    }
}
char* byteToBinary(char byte) {
    static char binary[9];
    binary[0] = '\0';
    for (int i = 7; i >= 0; --i) {
        strcat(binary, ((byte >> i) & 1) ? "1" : "0");
    }
    return binary;
}
char* stringToBinary(const char* input) {
    static char output[1025];
    output[0] = '\0';
    for (size_t i = 0; i < strlen(input); ++i) {
        char byte[9] = {'\0'};
        for (int j = 7; j >= 0; --j) {
            strcat(byte, ((input[i] >> j) & 1) ? "1" : "0");
        }
        strcat(output, byte);
    }
    return output;
}
char* binaryToString(const char* binary) {
    static char output[65];
    output[0] = '\0';
    for (size_t i = 0; i < strlen(binary); i += 8) {
        char byte[9];
        strncpy(byte, binary + i, 8);
        byte[8] = '\0';
        char* endptr;
        long int num = strtol(byte, &endptr, 2);
        if (*endptr != '\0') {
            return "Invalid Binary Input";
        }
        snprintf(output + strlen(output), sizeof(output) - strlen(output), "%c", num);
    }
    return output;
}
char* encrypt(const char* pt, char rkb[16][49], char rk[16][17]) {
    static char cipher_text[65];
    char permuted_pt[65];
    strcpy(permuted_pt, permute(pt, permutation_table, 64));
    char left[33], right[33];
    strncpy(left, permuted_pt, 32); left[32] = '\0';
    strncpy(right, permuted_pt + 32, 32); right[32] = '\0';
    for (int i = 0; i < 16; i++) {
        char right_expanded[49];
        strcpy(right_expanded, expand(right, E_table, 48));
        char xor_x[49];
        strcpy(xor_x, xor_str(right_expanded, rkb[i]));
        char sbox_str[33];
        substitute(xor_x, sbox_str);
        char p_str[33];
        strcpy(p_str, permute(sbox_str, P_table, 32));
        char result[33];
        strcpy(result, xor_str(left, p_str));
        strcpy(left, result);
        if (i != 15) {
            char temp[33];
            strcpy(temp, left);
            strcpy(left, right);
            strcpy(right, temp);
        }
    }
    char combine[65];
    snprintf(combine, sizeof(combine), "%s%s", left, right);
    strcpy(cipher_text, permute(combine, final_permutation_table, 64));
    return cipher_text;
}
char* decrypt(const char* ct, char rkb[16][49], char rk[16][17]) {
    static char plain_text[65];
    char permuted_ct[65];
    strcpy(permuted_ct, permute(ct, permutation_table, 64));
    char left[33], right[33];
    strncpy(left, permuted_ct, 32); left[32] = '\0';
    strncpy(right, permuted_ct + 32, 32); right[32] = '\0';
    for (int i = 0; i < 16; i++) {
        char right_expanded[49];
        strcpy(right_expanded, expand(right, E_table, 48));
        char xor_x[49];
        strcpy(xor_x, xor_str(right_expanded, rkb[15 - i]));
        char sbox_str[33];
        substitute(xor_x, sbox_str);
        char p_str[33];
        strcpy(p_str, permute(sbox_str, P_table, 32));
        char result[33];
        strcpy(result, xor_str(left, p_str));
        strcpy(left, result);
        if (i != 15) {
            char temp[33];
            strcpy(temp, left);
            strcpy(left, right);
            strcpy(right, temp);
        }
    }
    char combine[65];
    snprintf(combine, sizeof(combine), "%s%s", left, right);
    strcpy(plain_text, permute(combine, final_permutation_table, 64));
    return plain_text;
}
unsigned char* load_file(const char *fn, int *len) {
    struct stat info = {0};
    if (stat(fn, &info)) return 0;  // If file is inaccessible

    FILE *fsrc = fopen(fn, "rb");
    if (!fsrc) return 0;

    unsigned char *data = (unsigned char *)malloc(info.st_size);
    if (!data) exit(1);

    size_t nread = fread(data, 1, info.st_size, fsrc);
    fclose(fsrc);
    *len = (int)nread;
    return data;
}
int save_file(const char *fn, unsigned char *data, int len) {
    FILE *fdst = fopen(fn, "wb");
    if (!fdst) return 0;
    fwrite(data, 1, len, fdst);
    fclose(fdst);
    return 1;
}
unsigned char* addPadding(const unsigned char* input, int input_len, int *padded_len) {
    int block_size = 8;
    *padded_len = ((input_len + block_size - 1) / block_size) * block_size;  // Round up to nearest block size
    unsigned char* padded_input = (unsigned char*)malloc(*padded_len);

    if (!padded_input) return NULL;

    memcpy(padded_input, input, input_len);
    memset(padded_input + input_len, 0, *padded_len - input_len);  // Pad with zeroes

    return padded_input;
}
unsigned char* removePadding(unsigned char* input, int input_len, int *unpadded_len) {
    *unpadded_len = input_len;
    while (*unpadded_len > 0 && input[*unpadded_len - 1] == 0) {
        (*unpadded_len)--;
    }
    unsigned char* unpadded_output = (unsigned char*)malloc(*unpadded_len);
    if (!unpadded_output) return NULL;

    memcpy(unpadded_output, input, *unpadded_len);
    return unpadded_output;
}
char* encryptECB(const unsigned char* input, int input_len, char rkb[16][49], char rk[16][17]) {
    int padded_len;
    unsigned char* padded_input = addPadding(input, input_len, &padded_len);
    if (!padded_input) return NULL;

    char* output = (char*)malloc(padded_len + 1); // allocate enough space for the padded input + null terminator
    if (!output) return NULL;
    output[0] = '\0';

    for (int i = 0; i < padded_len; i += 64) {
        char block[65];
        strncpy(block, (char*)padded_input + i, 64);
        block[64] = '\0';
        char* encrypted_block = encrypt(block, rkb, rk);
        strcat(output, encrypted_block);
    }

    free(padded_input);
    return output;
}
char* decryptECB(const unsigned char* input, int input_len, char rkb[16][49], char rk[16][17]) {
    char* output = (char*)malloc(input_len + 1); // allocate enough space for the input + null terminator
    if (!output) return NULL;
    output[0] = '\0';

    for (int i = 0; i < input_len; i += 64) {
        char block[65];
        strncpy(block, (char*)input + i, 64);
        block[64] = '\0';
        char* decrypted_block = decrypt(block, rkb, rk);
        strcat(output, decrypted_block);
    }

    int unpadded_len;
    unsigned char* unpadded_output = removePadding((unsigned char*)output, strlen(output), &unpadded_len);
    if (!unpadded_output) return NULL;
    strncpy(output, (char*)unpadded_output, unpadded_len);
    output[unpadded_len] = '\0';

    free(unpadded_output);
    return output;

}
int main(int argc, char **argv) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <e|d> <keyfile> <inputfile> <outputfile>\n", argv[0]);
        return 1;
    }

    char *mode = argv[1];
    char *keyFile = argv[2];
    char *inputFile = argv[3];
    char *outputFile = argv[4];

    int key_len, input_len;
    unsigned char *key = load_file(keyFile, &key_len);
    if (!key) {
        fprintf(stderr, "Error: Could not load key file %s\n", keyFile);
        return 1;
    }

    unsigned char *input = load_file(inputFile, &input_len);
    if (!input) {
        fprintf(stderr, "Error: Could not load input file %s\n", inputFile);
        free(key);
        return 1;
    }

    char rkb[16][49], rk[16][17];
    generateRoundKeys((char*)key, rkb, rk);
    free(key);

    char *output = NULL;
    int output_len = 0;

    if (strcmp(mode, "e") == 0) {
        output = encryptECB(input, input_len, rkb, rk);
        output_len = strlen(output);
    } else if (strcmp(mode, "d") == 0) {
        output = decryptECB(input, input_len, rkb, rk);
        output_len = strlen(output);
    } else {
        fprintf(stderr, "Invalid mode. Use 'e' for encryption or 'd' for decryption.\n");
        free(input);
        return 1;
    }

    if (!output) {
        fprintf(stderr, "Error: Encryption/Decryption failed.\n");
        free(input);
        return 1;
    }

    if (!save_file(outputFile, (unsigned char*)output, output_len)) {
        fprintf(stderr, "Error: Could not save to output file %s\n", outputFile);
        free(input);
        return 1;
    }

    free(input);
    return 0;
}