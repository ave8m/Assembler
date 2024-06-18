//関数名がParser.cと衝突するのでcomp()→code_comp()とした

#include "Parser.c"

//mnemonic、codeを入れる構造体
typedef struct {
    const char * mnemonic;
    const char * code;
} InstructionMap;

const char* code_dest(char *mnemonic) {
    static const InstructionMap table[] = {
        {"AMD", "111"},
        {"AD",  "110"},
        {"AM",  "101"},
        {"A",   "100"},
        {"MD",  "011"},
        {"D",   "010"},
        {"M",   "001"}
    };

    const char *code = "000"; //デフォルト値

    for(int i = 0; i < sizeof(table) / sizeof(table[0]); ++i) { //構造体を走査
        if ( strcmp(mnemonic, table[i].mnemonic ) == 0) {       //ニーモニックが一致した場合
            code = table[i].code;
            break;
        }
    }
    return code;
}

const char* code_comp(char *mnemonic) {
    static const InstructionMap table[] = {
        {"1",     "0111111"},
        {"-1",    "0111010"},
        {"D",     "0001100"},
        {"A",     "0110000"},
        {"!D",    "0001101"},
        {"!A",    "0110001"},
        {"-D",    "0001111"},
        {"-A",    "0110011"},
        {"D+1",   "0011111"},
        {"A+1",   "0110111"},
        {"D-1",   "0001110"},
        {"A-1",   "0110010"},
        {"D+A",   "0000010"},
        {"D-A",   "0010011"},
        {"A-D",   "0000111"},
        {"D&A",   "0000000"},
        {"D|A",   "0010101"},

        {"M",     "1110000"},
        {"!M",    "1110001"},
        {"-M",    "1110011"},
        {"M+1",   "1110111"},
        {"M-1",   "1110010"},
        {"D+M",   "1000010"},
        {"D-M",   "1010011"},
        {"M-D",   "1000111"},
        {"D&M",   "1000000"},
        {"D|M",   "1010101"}
    };

    const char *code = "0101010"; //デフォルト値

    for(int i = 0; i < sizeof(table) / sizeof(table[0]); ++i) { //構造体を走査
        if ( strcmp(mnemonic, table[i].mnemonic ) == 0) {    //ニーモニックが一致した場合
            code = table[i].code;
            break;
        }
    }
    return code;
}

const char* code_jump(char *mnemonic) {
    static const InstructionMap table[] = {
        {"JGT", "001"},
        {"JEQ", "010"},
        {"JGE", "011"},
        {"JLT", "100"},
        {"JNE", "101"},
        {"JLE", "110"},
        {"JMP", "111"}
    };

    const char *code = "000"; //デフォルト値

    for(int i = 0; i < sizeof(table) / sizeof(table[0]); ++i) { //構造体を走査
        if ( strcmp(mnemonic, table[i].mnemonic ) == 0) {    //ニーモニックが一致した場合
            code = table[i].code;
            break;
        }
    }
    return code;
}

char* decToBinary(char* str) {
    static char binary[16];
    memset(binary, '\0', sizeof(binary));

    // 2進数に変換
    int num = atoi(str);
    for (int i = 14; i >= 0; --i) {
        binary[i] = (num % 2) == 0 ? '0':'1';
        num /= 2;
    }

    // 負の値の場合2の補数  最も右側の'1'よりも左にある全ビットを反転する
    if (atoi(str) < 0) {
        for (int i = 14; i >= 0; --i) {                     //最も右側にある1を検索
            if (binary[i] == '1') {
                while(i > 0) {
                    --i;
                    binary[i] = binary[i] == '0' ? '1':'0'; //全てのビットを反転
                }
                break;
            }
        }
    }
    return binary;
}