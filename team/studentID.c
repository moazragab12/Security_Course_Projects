#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h>
uint64_t Keys_Before_Permutations_56_bit[16];
uint64_t Keys_After_Permutations_48_bit[16];
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
int S_BOXES[8][64] = {
    {
        14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
        0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
        4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
        15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13
    },
    {
        15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
        3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
        0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
        13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9
    },
    {
        10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
        13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
        13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
        1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12
    },
    {
        7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
        13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
        10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
        3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14
    },
    {
        2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
        14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
        4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
        11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3
    },
    {
        12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
        10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
        9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
        4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13
    },
    {
        4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
        13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
        1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
        6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12
    },
    {
        13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
        1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
        7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
        2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
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
char* binaryToHex(const char* binary) {
    static char hex[17] = {0};
    size_t len = strlen(binary) / 4;
    for (size_t i = 0; i < len; ++i) {
        int idx = (binary[i * 4] - '0') * 8 + (binary[i * 4 + 1] - '0') * 4 + (binary[i * 4 + 2] - '0') * 2 + (binary[i * 4 + 3] - '0');
        hex[i] = "0123456789ABCDEF"[idx];
    }
    return hex;
}
char* expand(const char* input, const int* E_table, size_t table_size) {
    static char output[49];
    size_t input_len = strlen(input);
    for (size_t i = 0; i < table_size; ++i) {
        output[i] = (E_table[i] - 1 < input_len) ? input[E_table[i] - 1] : '0';
    }
    output[table_size] = '\0';
    return output;
}
void substitute(const char* input, char* output) {
    char* output_ptr = output;
    for (int i = 0; i < 8; i++) {
        int six_bit_block = 0;
        for (int j = 0; j < 6; ++j) {
            six_bit_block = (six_bit_block << 1) | (input[i * 6 + j] - '0');
        }
        int index = (six_bit_block & 0x20) | ((six_bit_block & 1) << 4) | ((six_bit_block >> 1) & 0x0F);
        int val = S_BOXES[i][index];
        for (int j = 3; j >= 0; --j) {
            *output_ptr++ = (val & (1 << j)) ? '1' : '0';
        }
    }
    *output_ptr = '\0';
}
char* permute(const char* input, const int* permutation_table, size_t table_size) {
    static char output[65] = {0};
    for (size_t i = 0; i < table_size; ++i) {
        output[i] = input[permutation_table[i] - 1];
    }
    output[table_size] = '\0';
    return output;
}
void xor_str(char* a, char* b, char* result) {
    for (size_t i = 0; i < strlen(a); ++i) {
        result[i] = (a[i] == b[i]) ? '0' : '1';
    }
    result[strlen(a)] = '\0';
}
void shift_left(char* input, size_t shifts) {
    size_t len = strlen(input);
    shifts %= len;
    for (size_t i = 0; i < shifts; ++i) {
        char first = input[0];
        memmove(input, input + 1, len - 1);
        input[len - 1] = first;
    }
}
void generateRoundKeys(const char* keyBinary, char rkb[16][49], char rk[16][17]) {
    char permuted_key[57] = {0};
    memcpy(permuted_key, permute(keyBinary, key_permutation_values, 56), 56);
    char left[29] = {0}, right[29] = {0};
    memcpy(left, permuted_key, 28);
    memcpy(right, permuted_key + 28, 28);
    for (int i = 0; i < 16; ++i) {
        shift_left(left, keys_Shift_for_Permutations[i]);
        shift_left(right, keys_Shift_for_Permutations[i]);
        char combined_key[57];
        snprintf(combined_key, sizeof(combined_key), "%s%s", left, right);
        memcpy(rkb[i], permute(combined_key, Permutation_for_CDNs, 48), 48);
        memcpy(rk[i], binaryToHex(rkb[i]), 16);
    }
}
char* encrypt(const char* pt, char rkb[16][49], char rk[16][17]) {
    static char cipher_text[65];
    char permuted_pt[65];
    memcpy(permuted_pt, permute(pt, permutation_table, 64), 64);
    char left[33] = {0}, right[33] = {0};
    memcpy(left, permuted_pt, 32);
    memcpy(right, permuted_pt + 32, 32);
    for (int i = 0; i < 16; i++) {
        char right_expanded[49];
        memcpy(right_expanded, expand(right, E_table, 48), 48);
        char xor_x[49];
        xor_str(right_expanded, rkb[i], xor_x);
        char sbox_str[33];
        substitute(xor_x, sbox_str);
        char p_str[33];
        memcpy(p_str, permute(sbox_str, P_table, 32), 32);
        char result[33];
        xor_str(left, p_str, result);
        memcpy(left, result, 32);
        if (i != 15) {
            char temp[33];
            memcpy(temp, left, 32);
            memcpy(left, right, 32);
            memcpy(right, temp, 32);
        }
    }
    char combine[65];
    snprintf(combine, sizeof(combine), "%s%s", left, right);
    memcpy(cipher_text, permute(combine, final_permutation_table, 64), 64);
    return cipher_text;
}
char* decrypt(const char* ct, char rkb[16][49], char rk[16][17]) {
    static char plain_text[65];
    char permuted_ct[65];
    memcpy(permuted_ct, permute(ct, permutation_table, 64), 64);
    char left[33] = {0}, right[33] = {0};
    memcpy(left, permuted_ct, 32);
    memcpy(right, permuted_ct + 32, 32);
    for (int i = 0; i < 16; i++) {
        char right_expanded[49];
        memcpy(right_expanded, expand(right, E_table, 48), 48);
        char xor_x[49];
        xor_str(right_expanded, rkb[15 - i], xor_x);
        char sbox_str[33];
        substitute(xor_x, sbox_str);
        char p_str[33];
        memcpy(p_str, permute(sbox_str, P_table, 32), 32);
        char result[33];
        xor_str(left, p_str, result);
        memcpy(left, result, 32);
        if (i != 15) {
            char temp[33];
            memcpy(temp, left, 32);
            memcpy(left, right, 32);
            memcpy(right, temp, 32);
        }
    }
    char combine[65];
    snprintf(combine, sizeof(combine), "%s%s", left, right);
    memcpy(plain_text, permute(combine, final_permutation_table, 64), 64);
    return plain_text;
}
unsigned char* load_file(const char *fn, int *len) {
    struct stat info = {0};
    if (stat(fn, &info)) return 0;
    FILE *fsrc = fopen(fn, "rb");
    unsigned char *data = (unsigned char *)malloc(info.st_size);
    size_t nread = fread(data, 1, info.st_size, fsrc);
    fclose(fsrc);
    *len = (int)nread;
    return data;
}
int save_file(const char *fn, unsigned char *data, int len) {
    FILE *fdst = fopen(fn, "wb");
    fwrite(data, 1, len, fdst);
    fclose(fdst);
    return 1;
}
char* encryptECB(const unsigned char* input, int input_len, char rkb[16][49], char rk[16][17]) {
    char* output = (char*)malloc((input_len / 64 + 1) * 65);
    output[0] = '\0';
    char* output_ptr = output;
    for (int i = 0; i < input_len; i += 64) {
        char block[65] = {0};
        memcpy(block, input + i, 64);
        char* encrypted_block = encrypt(block, rkb, rk);
        memcpy(output_ptr, encrypted_block, 64);
        output_ptr += 64;
    }
    *output_ptr = '\0';
    return output;
}
char* decryptECB(const unsigned char* input, int input_len, char rkb[16][49], char rk[16][17]) {
    char* output = (char*)malloc((input_len / 64 + 1) * 65);
    output[0] = '\0';
    char* output_ptr = output;
    for (int i = 0; i < input_len; i += 64) {
        char block[65] = {0};
        memcpy(block, input + i, 64);
        char* decrypted_block = decrypt(block, rkb, rk);
        memcpy(output_ptr, decrypted_block, 64);
        output_ptr += 64;
    }
    *output_ptr = '\0';
    return output;
}
int main(int argc, char** argv) {
    char* mode = argv[1];
    char* keyFile = argv[2];
    char* inputFile = argv[3];
    char* outputFile = argv[4];
    int key_len, input_len;
    unsigned char* key = load_file(keyFile, &key_len);
    unsigned char* input = load_file(inputFile, &input_len);
    char rkb[16][49], rk[16][17];
    generateRoundKeys((char*)key, rkb, rk);
    free(key);
    char* output = (strcmp(mode, "e") == 0) ? encryptECB(input, input_len, rkb, rk) : decryptECB(input, input_len, rkb, rk);
    int output_len = strlen(output);
    save_file(outputFile, (unsigned char*)output, output_len);
    free(input);
    free(output);
    return 0;
}
