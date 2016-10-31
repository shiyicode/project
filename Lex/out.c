//%{ start
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int KEY_NUM = 32;
const char* KEY_SET[] = {
    "auto", "break", "case", "char", "const", "continue",
	"default", "do", "double", "else", "enum", "extern",
	"float", "for", "goto", "if", "int", "long", "register",
	"return", "short", "signed", "sizeof", "static", "struct",
	"switch", "typedef", "union", "unsigned", "void", "volatile",
	"while"
};

int isDigit(char ch)
{
	if(ch <= '9' && ch >= '0')
		return 1;
	return 0;
}

int isLetter(char ch)
{
	if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return 1;
	return 0;
}

int getKeyId(char *str)
{
	for(int i=0; i<KEY_NUM; i++)
	{
		if(strcmp(KEY_SET[i], str) == 0)
			return i+1;
	}
	return 0;
}

int isNoOne(char ch)
{
	if(ch != '\'' && ch != '\0')
		return 1;
	return 0;
}

int isNoTow(char ch)
{
	if(ch != '\"' && ch != '\0')
		return 1;
	return 0;
}

//%} end
//%! start
//%! end
//%% start
//%% end
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SYLEX_MAXSIZE_TEXT 120
#define SYLEX_MAXSIZE_BUFF 1024

char SYLEX_FILE_NAME[100];
char SYLEX_OUT_FILE_NAME[100];
int SYLEX_LINE = 0;
int SYLEX_STATE = 0;
int SYLEX_TEXT_LEN = 0;
char SYLEX_TEXT[SYLEX_MAXSIZE_TEXT];
char SYLEX_BUFF[SYLEX_MAXSIZE_BUFF];

//扫描函数
void SYLEX_scanner(char *str)
{
    char ch = ' ';
    while(ch != '\0')
    {
        //printf("%c %d\n", ch, SYLEX_STATE);
        switch(SYLEX_STATE) {
        case 0:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == ' '){
                SYLEX_STATE = 1;
            }
            else
            if(ch == '#'){
                SYLEX_STATE = 2;
            }
            else
            if(ch == '&'){
                SYLEX_STATE = 3;
            }
            else
            if(ch == '('){
                SYLEX_STATE = 4;
            }
            else
            if(ch == ')'){
                SYLEX_STATE = 5;
            }
            else
            if(ch == '*'){
                SYLEX_STATE = 6;
            }
            else
            if(ch == '+'){
                SYLEX_STATE = 7;
            }
            else
            if(ch == ','){
                SYLEX_STATE = 8;
            }
            else
            if(ch == '-'){
                SYLEX_STATE = 9;
            }
            else
            if(ch == '.'){
                SYLEX_STATE = 10;
            }
            else
            if(ch == '/'){
                SYLEX_STATE = 11;
            }
            else
            if(ch == ';'){
                SYLEX_STATE = 12;
            }
            else
            if(ch == '<'){
                SYLEX_STATE = 13;
            }
            else
            if(ch == '='){
                SYLEX_STATE = 14;
            }
            else
            if(ch == '>'){
                SYLEX_STATE = 15;
            }
            else
            if(ch == '['){
                SYLEX_STATE = 16;
            }
            else
            if(ch == '\"'){
                SYLEX_STATE = 17;
            }
            else
            if(ch == '\''){
                SYLEX_STATE = 18;
            }
            else
            if(ch == '\n'){
                SYLEX_STATE = 19;
            }
            else
            if(ch == '\t'){
                SYLEX_STATE = 20;
            }
            else
            if(ch == ']'){
                SYLEX_STATE = 21;
            }
            else
            if(ch == '^'){
                SYLEX_STATE = 22;
            }
            else
            if(ch == '_'){
                SYLEX_STATE = 23;
            }
            else
            if(isDigit(ch)){
                SYLEX_STATE = 24;
            }
            else
            if(isLetter(ch)){
                SYLEX_STATE = 25;
            }
            else
            if(ch == '{'){
                SYLEX_STATE = 26;
            }
            else
            if(ch == '|'){
                SYLEX_STATE = 27;
            }
            else
            if(ch == '}'){
                SYLEX_STATE = 28;
            }
            else
            if(ch == '~'){
                SYLEX_STATE = 29;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 1:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{}
//**************e
            }
            break;
        }
        case 2:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == 'i'){
                SYLEX_STATE = 30;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 3:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '&'){
                SYLEX_STATE = 31;
            }
            else
            if(ch == '='){
                SYLEX_STATE = 32;
            }
            else
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 4:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 5:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 6:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 7:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '+'){
                SYLEX_STATE = 33;
            }
            else
            if(ch == '='){
                SYLEX_STATE = 34;
            }
            else
            if(isDigit(ch)){
                SYLEX_STATE = 24;
            }
            else
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 8:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 9:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '-'){
                SYLEX_STATE = 35;
            }
            else
            if(ch == '='){
                SYLEX_STATE = 36;
            }
            else
            if(isDigit(ch)){
                SYLEX_STATE = 24;
            }
            else
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 10:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 11:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '='){
                SYLEX_STATE = 37;
            }
            else
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 12:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 13:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '<'){
                SYLEX_STATE = 38;
            }
            else
            if(ch == '='){
                SYLEX_STATE = 39;
            }
            else
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 14:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '='){
                SYLEX_STATE = 40;
            }
            else
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 15:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '='){
                SYLEX_STATE = 41;
            }
            else
            if(ch == '>'){
                SYLEX_STATE = 42;
            }
            else
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 16:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 17:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '\"'){
                SYLEX_STATE = 43;
            }
            else
            if(isNoTow(ch)){
                SYLEX_STATE = 17;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 18:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '\''){
                SYLEX_STATE = 44;
            }
            else
            if(isNoOne(ch)){
                SYLEX_STATE = 18;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 19:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{}
//**************e
            }
            break;
        }
        case 20:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{}
//**************e
            }
            break;
        }
        case 21:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 22:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '='){
                SYLEX_STATE = 45;
            }
            else
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 23:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '_'){
                SYLEX_STATE = 46;
            }
            else
            if(isDigit(ch)){
                SYLEX_STATE = 47;
            }
            else
            if(isLetter(ch)){
                SYLEX_STATE = 48;
            }
            else
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	int id = getKeyId(SYLEX_TEXT);	if(id != 0)		printf("<%s,->\n", SYLEX_TEXT);	else	{		printf("<$ID,%s>\n", SYLEX_TEXT);	}}
//**************e
            }
            break;
        }
        case 24:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '.'){
                SYLEX_STATE = 49;
            }
            else
            if(ch == 'E'){
                SYLEX_STATE = 50;
            }
            else
            if(isDigit(ch)){
                SYLEX_STATE = 24;
            }
            else
            if(ch == 'e'){
                SYLEX_STATE = 51;
            }
            else
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<$NUM,%s>\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 25:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '_'){
                SYLEX_STATE = 46;
            }
            else
            if(isDigit(ch)){
                SYLEX_STATE = 47;
            }
            else
            if(isLetter(ch)){
                SYLEX_STATE = 48;
            }
            else
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	int id = getKeyId(SYLEX_TEXT);	if(id != 0)		printf("<%s,->\n", SYLEX_TEXT);	else	{		printf("<$ID,%s>\n", SYLEX_TEXT);	}}
//**************e
            }
            break;
        }
        case 26:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 27:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '='){
                SYLEX_STATE = 52;
            }
            else
            if(ch == '|'){
                SYLEX_STATE = 53;
            }
            else
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 28:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 29:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '='){
                SYLEX_STATE = 54;
            }
            else
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 30:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == 'n'){
                SYLEX_STATE = 55;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 31:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 32:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 33:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 34:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 35:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 36:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 37:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 38:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 39:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 40:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 41:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 42:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 43:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<$STR,%s>\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 44:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<$STR,%s>\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 45:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 46:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '_'){
                SYLEX_STATE = 46;
            }
            else
            if(isDigit(ch)){
                SYLEX_STATE = 47;
            }
            else
            if(isLetter(ch)){
                SYLEX_STATE = 48;
            }
            else
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	int id = getKeyId(SYLEX_TEXT);	if(id != 0)		printf("<%s,->\n", SYLEX_TEXT);	else	{		printf("<$ID,%s>\n", SYLEX_TEXT);	}}
//**************e
            }
            break;
        }
        case 47:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '_'){
                SYLEX_STATE = 46;
            }
            else
            if(isDigit(ch)){
                SYLEX_STATE = 47;
            }
            else
            if(isLetter(ch)){
                SYLEX_STATE = 48;
            }
            else
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	int id = getKeyId(SYLEX_TEXT);	if(id != 0)		printf("<%s,->\n", SYLEX_TEXT);	else	{		printf("<$ID,%s>\n", SYLEX_TEXT);	}}
//**************e
            }
            break;
        }
        case 48:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '_'){
                SYLEX_STATE = 46;
            }
            else
            if(isDigit(ch)){
                SYLEX_STATE = 47;
            }
            else
            if(isLetter(ch)){
                SYLEX_STATE = 48;
            }
            else
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	int id = getKeyId(SYLEX_TEXT);	if(id != 0)		printf("<%s,->\n", SYLEX_TEXT);	else	{		printf("<$ID,%s>\n", SYLEX_TEXT);	}}
//**************e
            }
            break;
        }
        case 49:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(isDigit(ch)){
                SYLEX_STATE = 56;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 50:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(isDigit(ch)){
                SYLEX_STATE = 57;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 51:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(isDigit(ch)){
                SYLEX_STATE = 57;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 52:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 53:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 54:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<%s,->\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 55:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == 'c'){
                SYLEX_STATE = 58;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 56:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == 'E'){
                SYLEX_STATE = 50;
            }
            else
            if(isDigit(ch)){
                SYLEX_STATE = 56;
            }
            else
            if(ch == 'e'){
                SYLEX_STATE = 51;
            }
            else
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<$NUM,%s>\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 57:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(isDigit(ch)){
                SYLEX_STATE = 57;
            }
            else
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("<$NUM,%s>\n", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 58:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == 'l'){
                SYLEX_STATE = 59;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 59:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == 'u'){
                SYLEX_STATE = 60;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 60:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == 'd'){
                SYLEX_STATE = 61;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 61:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == 'e'){
                SYLEX_STATE = 62;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 62:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == ' '){
                SYLEX_STATE = 63;
            }
            else
            if(ch == '"'){
                SYLEX_STATE = 64;
            }
            else
            if(ch == '<'){
                SYLEX_STATE = 65;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 63:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == ' '){
                SYLEX_STATE = 63;
            }
            else
            if(ch == '"'){
                SYLEX_STATE = 64;
            }
            else
            if(ch == '<'){
                SYLEX_STATE = 65;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 64:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '_'){
                SYLEX_STATE = 66;
            }
            else
            if(isLetter(ch)){
                SYLEX_STATE = 67;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 65:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '_'){
                SYLEX_STATE = 68;
            }
            else
            if(isLetter(ch)){
                SYLEX_STATE = 69;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 66:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '.'){
                SYLEX_STATE = 70;
            }
            else
            if(ch == '_'){
                SYLEX_STATE = 71;
            }
            else
            if(isDigit(ch)){
                SYLEX_STATE = 72;
            }
            else
            if(isLetter(ch)){
                SYLEX_STATE = 73;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 67:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '.'){
                SYLEX_STATE = 70;
            }
            else
            if(ch == '_'){
                SYLEX_STATE = 71;
            }
            else
            if(isDigit(ch)){
                SYLEX_STATE = 72;
            }
            else
            if(isLetter(ch)){
                SYLEX_STATE = 73;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 68:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '.'){
                SYLEX_STATE = 74;
            }
            else
            if(ch == '_'){
                SYLEX_STATE = 75;
            }
            else
            if(isDigit(ch)){
                SYLEX_STATE = 76;
            }
            else
            if(isLetter(ch)){
                SYLEX_STATE = 77;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 69:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '.'){
                SYLEX_STATE = 74;
            }
            else
            if(ch == '_'){
                SYLEX_STATE = 75;
            }
            else
            if(isDigit(ch)){
                SYLEX_STATE = 76;
            }
            else
            if(isLetter(ch)){
                SYLEX_STATE = 77;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 70:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == 'h'){
                SYLEX_STATE = 78;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 71:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '.'){
                SYLEX_STATE = 70;
            }
            else
            if(ch == '_'){
                SYLEX_STATE = 71;
            }
            else
            if(isDigit(ch)){
                SYLEX_STATE = 72;
            }
            else
            if(isLetter(ch)){
                SYLEX_STATE = 73;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 72:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '.'){
                SYLEX_STATE = 70;
            }
            else
            if(ch == '_'){
                SYLEX_STATE = 71;
            }
            else
            if(isDigit(ch)){
                SYLEX_STATE = 72;
            }
            else
            if(isLetter(ch)){
                SYLEX_STATE = 73;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 73:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '.'){
                SYLEX_STATE = 70;
            }
            else
            if(ch == '_'){
                SYLEX_STATE = 71;
            }
            else
            if(isDigit(ch)){
                SYLEX_STATE = 72;
            }
            else
            if(isLetter(ch)){
                SYLEX_STATE = 73;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 74:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == 'h'){
                SYLEX_STATE = 79;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 75:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '.'){
                SYLEX_STATE = 74;
            }
            else
            if(ch == '_'){
                SYLEX_STATE = 75;
            }
            else
            if(isDigit(ch)){
                SYLEX_STATE = 76;
            }
            else
            if(isLetter(ch)){
                SYLEX_STATE = 77;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 76:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '.'){
                SYLEX_STATE = 74;
            }
            else
            if(ch == '_'){
                SYLEX_STATE = 75;
            }
            else
            if(isDigit(ch)){
                SYLEX_STATE = 76;
            }
            else
            if(isLetter(ch)){
                SYLEX_STATE = 77;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 77:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '.'){
                SYLEX_STATE = 74;
            }
            else
            if(ch == '_'){
                SYLEX_STATE = 75;
            }
            else
            if(isDigit(ch)){
                SYLEX_STATE = 76;
            }
            else
            if(isLetter(ch)){
                SYLEX_STATE = 77;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 78:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '"'){
                SYLEX_STATE = 80;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 79:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            if(ch == '>'){
                SYLEX_STATE = 81;
            }
            else
            {
printf("Error in line %d\n", SYLEX_LINE);
exit(1);
            }
            break;
        }
        case 80:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("%s 应该预处理的，暂时先忽略", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        case 81:
        {
            ch = *str++;
            SYLEX_TEXT[SYLEX_TEXT_LEN++]=ch;
            {
SYLEX_TEXT[SYLEX_TEXT_LEN-1] = '\0';
SYLEX_TEXT_LEN=0;
SYLEX_STATE=0;
str--;
//**************s
{	printf("%s 应该预处理的，暂时先忽略", SYLEX_TEXT);}
//**************e
            }
            break;
        }
        }
    }
}

int main(int argc, char **args)
{
    if(argc == 1)
    {
        printf("没有输入源文件名");
        return 0;
    }
    else if(argc == 2)
    {
        strcpy(SYLEX_FILE_NAME, args[1]);
        sprintf(SYLEX_OUT_FILE_NAME, "%s.out", SYLEX_FILE_NAME);
    }
    else
    {
        strcpy(SYLEX_FILE_NAME, args[1]);
        strcpy(SYLEX_OUT_FILE_NAME, args[2]);
    }
    FILE* file = fopen(SYLEX_FILE_NAME, "r");
    while(NULL != fgets(SYLEX_BUFF, SYLEX_MAXSIZE_BUFF, file))
    {
        ++SYLEX_LINE;
        SYLEX_scanner(SYLEX_BUFF);
    }
    return 0;
}
