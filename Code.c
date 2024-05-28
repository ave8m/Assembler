//関数名がParser.cと衝突するのでcomp()→code_comp()とした

#include "Parser.c"

//mnemonic、codeを入れる構造体
typedef struct {
    const char * mnemonic;
    const char * code;
} InstructionMap;

char* code_dest(char *mnemonic) {
    static const InstructionMap table[] = {
        {"AMD", "111"},
        {"AD",  "110"},
        {"AM",  "101"},
        {"A",   "100"},
        {"MD",  "011"},
        {"D",   "010"},
        {"M",   "001"}
    };

    char *code = "000"; //デフォルト値

    for(int i = 0; i < sizeof(table) / sizeof(table[0]); ++i) { //構造体を走査
        if ( strcmp(mnemonic, table[i].mnemonic ) == 0) {       //ニーモニックに一致したものがあった場合
            code = table[i].code;
            break;
        }
    }
    return code;
}

char* code_comp(char *mnemonic) {
    static const InstructionMap table[] = {
        {"1",     "1111111"},
        {"-1",    "0101010"},
        {"D",     "0111111"},
        {"A",     "0111010"},
        {"!D",    "0001100"},
        {"!A",    "0001101"},
        {"-D",    "0110001"},
        {"-A",    "0001111"},
        {"D+1",   "0110011"},
        {"D-1",   "0011111"},
        {"A-1",   "0001110"},
        {"D+A",   "0110010"},
        {"D-A",   "0110010"},
        {"A-D",   "0010011"},
        {"D&A",   "0010011"},
        {"D|A",   "0000111"},
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
        if ( strcmp(mnemonic, table[i].mnemonic ) == 0) {    //ニーモニックに一致したものがあった場合
            code = table[i].code;
            break;
        }
    }

    return code;
}

char* code_jump(char *mnemonic) {
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
        if ( strcmp(mnemonic, table[i].mnemonic ) == 0) {    //ニーモニックに一致したものがあった場合
            code = table[i].code;
            break;
        }
    }
    return code;
}