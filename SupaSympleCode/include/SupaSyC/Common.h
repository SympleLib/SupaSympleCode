#pragma once
#pragma warning(disable: 26812, 6031)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct
{
	uint32_t Number;
	const char *Name;
	const char *Source;

	FILE *Stream;
} File;

typedef enum
{
	FILEMODE_READ,        // Read Only
	FILEMODE_WRITE,       // Write Only
	FILEMODE_APPEND,      // Append Only
	FILEMODE_READ_WRITE,  // Read and Write
	FILEMODE_READ_APPEND, // Read and Append
} FileMode;

File *OpenFile(const char *name, FileMode mode);
void CloseFile(const File *);

typedef enum
{
	TK_Identifier,
} TokenKind;

typedef struct
{
	bool StartOfLine : 1;
	bool AfterSpace : 1;
} TokenTrivia;

typedef union
{
	int32_t Int32Eval;
	uint32_t UInt32Eval;
} Evaluation;

typedef struct Token Token;
struct Token
{
	TokenKind Kind;
	const char *Text;
	uint32_t Length; // Length of text

	const File *File;
	uint32_t Line;
	uint32_t DisplayLine; // For #line
	TokenTrivia Trivia;
	Evaluation Eval;
	
	Token* Next;
};

Token* NewToken(TokenKind, const char *text, const char *textEnd, const File *file, uint32_t line, uint32_t displayLine, TokenTrivia trivia, Evaluation, Token* next);
void DeleteToken(const Token*, bool deleteNext);
Token* Lex(const File* file);

#define Alloc(count, ty) (ty*)_Alloc(count, sizeof(ty))
#define Free(ptr) free((void*)ptr)

inline void *_Alloc(uint32_t count, uint32_t sz)
{
	void *ptr = calloc(count, sz);
	assert(ptr);
	return ptr;
}