#include <LPC21xx.H>

#define NULL 0
#define MAX_TOKEN_NR 3
#define MAX_KEYWORD_STRING_LTH 10
#define MAX_KEYWORD_NR 3

typedef enum Result {OK, ERROR} Result;
enum CompResult {DIFFERENT, EQUAL};

void ReplaceCharactersInString(char pcString[],char cOldChar, char cNewChar)
{
	unsigned char ucCharCounter;
	
	for(ucCharCounter = 0; pcString[ucCharCounter] != NULL; ucCharCounter++)
	{
		if( pcString[ucCharCounter] == cOldChar )
		{
			pcString[ucCharCounter] = cNewChar;
		}
	}
}

enum CompResult eCompareString(char pcStr1[], char pcStr2[])
{
	unsigned char ucCharCounter;
	
	for(ucCharCounter = 0; pcStr1[ucCharCounter] != NULL; ucCharCounter++)
	{
		if( pcStr1[ucCharCounter] != pcStr2[ucCharCounter] )
		{
			return DIFFERENT;
		}
	}
	
	if( pcStr1[ucCharCounter] != pcStr2[ucCharCounter] )
	{
		return DIFFERENT;
	}
	
	return EQUAL;
}

enum Result eHexStringToUInt(char pcStr[],unsigned int *puiValue)
{
	unsigned char ucCharacterCounter;
	unsigned char ucCurrentCharacter;
	
	if((pcStr[0]!='0') || (pcStr[1]!='x') || (pcStr[2]==NULL))
	{
		return ERROR;
	}
	*puiValue = 0;
	for(ucCharacterCounter=2; ucCharacterCounter<7; ucCharacterCounter++)
	{
		ucCurrentCharacter=pcStr[ucCharacterCounter];
		if(ucCurrentCharacter==NULL)
		{
			return OK;
		}
		else if(ucCharacterCounter==6)
		{
			return ERROR;
		}
		*puiValue = *puiValue << 4;
		if(ucCurrentCharacter >= '0' && ucCurrentCharacter <= '9')
		{
			ucCurrentCharacter = ucCurrentCharacter-'0';
		}
		else if(ucCurrentCharacter >= 'A' && ucCurrentCharacter <= 'F')
		{
			ucCurrentCharacter = (ucCurrentCharacter-'A'+10);
		}
		else
		{
			return ERROR;
		}
		*puiValue = (*puiValue) | ucCurrentCharacter;
	}
	return ERROR;
}


typedef enum TokenType {KEYWORD, NUMBER, STRING} TokenType;
typedef enum KeywordCode {LD, ST, RST} KeywordCode;

typedef union TokenValue
{
	enum KeywordCode eKeyword; //jezeli Keyword
	unsigned int uiNumber;     //jezeli Number
	char * pcString;           //jezeli string
} TokenValue;

typedef struct Token
{
	enum TokenType eType;      //keyword number string
	union TokenValue uValue;   //enum, unsigned int, char*
}Token;

struct Token asToken[MAX_TOKEN_NR];

typedef struct Keyword
{
	enum KeywordCode eCode;
	char cString[MAX_KEYWORD_STRING_LTH+1];
}Keyword;

struct Keyword asKeywordList[MAX_KEYWORD_NR]=
{
	{RST,"reset"},
	{LD,"load"},
	{ST,"store"}
};

unsigned char ucFindTokensInString(char *pcString)
{
	unsigned char ucTokenPointer;
	unsigned char ucTokenNumber = 0;
	char cCurrentChar;
	enum State {TOKEN, DELIMITER};
	enum State eState = DELIMITER;
	for(ucTokenPointer = 0 ;; ucTokenPointer++)
	{
		cCurrentChar = pcString[ucTokenPointer];
		switch(eState)
		{
			case DELIMITER:
				if(cCurrentChar == '\0')
				{
					return ucTokenNumber;
				}
				else if(cCurrentChar == ' ')
				{
					eState = DELIMITER;
				}
				else
				{
					eState = TOKEN;
					asToken[ucTokenPointer].uValue.pcString=pcString+ucTokenPointer;
					ucTokenNumber++;
				}
				break;
			case TOKEN:
				if(ucTokenNumber == MAX_TOKEN_NR)
				{
					return ucTokenNumber;
				}
				else if(cCurrentChar == '\0')
				{
					return ucTokenNumber;
				}
				else if(cCurrentChar != ' ')
				{
					eState = TOKEN;
				}
				else
				{
					eState = DELIMITER;
				}
				break;
				
		}
	}
}

enum Result eStringToKeyword(char pcStr[], enum KeywordCode *peKeywordCode)
{
	unsigned char ucKeywordCounter;
	
	for(ucKeywordCounter = 0; ucKeywordCounter < MAX_KEYWORD_NR; ucKeywordCounter++)
	{
		if(eCompareString(asKeywordList[ucKeywordCounter].cString, pcStr)==EQUAL)
		{
			*peKeywordCode = asKeywordList[ucKeywordCounter].eCode;
			return OK;
		}
	}
	return ERROR;
}

void DecodeTokens(void)
{
	unsigned char ucTokenCounter;
	Token *tTokenValue;
	for(ucTokenCounter = 0; ucTokenCounter < MAX_TOKEN_NR; ucTokenCounter++)
	{
		if(eStringToKeyword(tTokenValue->uValue.pcString, &tTokenValue->uValue.eKeyword) == OK)
		{
			tTokenValue->eType = KEYWORD;
		}
		else if(eHexStringToUInt(tTokenValue->uValue.pcString, &tTokenValue->uValue.uiNumber) == OK)
		{
			tTokenValue->eType = NUMBER;
		}
		else
		{
			tTokenValue->eType = STRING;
		}
	}
}

void DecodeMsg(char *pcString)
{
	ucFindTokensInString(pcString);
	ReplaceCharactersInString(pcString, ' ', NULL);
	DecodeTokens();
}

int main()
{
	char test1[] = "            ";
	char test2[] = "Token1 Token2";
	char test3[] = "Token1     Token2";
	unsigned char wynik;
	unsigned char wynik1;
	unsigned char wynik2;
	wynik = ucFindTokensInString(test1);
	wynik1 = ucFindTokensInString(test2);
	wynik2 = ucFindTokensInString(test3);
}


