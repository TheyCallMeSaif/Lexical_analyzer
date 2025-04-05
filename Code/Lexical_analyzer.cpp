// lexical_analyzer.cpp - A lexical analyzer for simple arithmetic expressions

#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>

using namespace std;

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define END_OF_FILE -1

int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int nextToken;
ifstream in_fp;

void addChar();
void getChar();
void getNonBlank();
int lex();
int lookup(char ch);

int main() {
    in_fp.open("front.in");
    if (!in_fp) {
        cout << "ERROR - cannot open front.in" << endl;
        return 1;
    }
    getChar();
    do {
        lex();
    } while (nextToken != END_OF_FILE);
    in_fp.close();
    return 0;
}

int lookup(char ch) {
    switch (ch) {
    case '(': addChar(); nextToken = LEFT_PAREN; break;
    case ')': addChar(); nextToken = RIGHT_PAREN; break;
    case '+': addChar(); nextToken = ADD_OP; break;
    case '-': addChar(); nextToken = SUB_OP; break;
    case '*': addChar(); nextToken = MULT_OP; break;
    case '/': addChar(); nextToken = DIV_OP; break;
    default:  addChar(); nextToken = END_OF_FILE; break;
    }
    return nextToken;
}

void addChar() {
    if (lexLen < 99) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = '\0';
    }
    else {
        cout << "Error - lexeme is too long" << endl;
    }
}

void getChar() {
    if (in_fp.get(nextChar)) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    }
    else {
        charClass = END_OF_FILE;
    }
}

void getNonBlank() {
    while (isspace(nextChar))
        getChar();
}

int lex() {
    lexLen = 0;
    getNonBlank();
    switch (charClass) {
    case LETTER:
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = IDENT;
        break;
    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = INT_LIT;
        break;
    case UNKNOWN:
        lookup(nextChar);
        getChar();
        break;
    case END_OF_FILE:
        nextToken = END_OF_FILE;
        strcpy_s(lexeme, "EOF");
        break;
    }
    cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << endl;
    return nextToken;
}
