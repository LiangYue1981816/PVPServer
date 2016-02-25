#pragma once


typedef int                            BOOL;     // 4BYTE
typedef char                           CHAR;     // 1BYTE
typedef short                          SHORT;    // 2BYTE
typedef int                            INT;      // 4BYTE
typedef unsigned int                   UINT;     // 4BYTE
typedef float                          FLOAT;    // 4BYTE
typedef double                         DOUBLE;   // 8BYTE

typedef long long                      INT64;    // 8BYTE
typedef unsigned long long             UINT64;   // 8BYTE

#ifdef WIN32
typedef long                           LONG;     // 4BYTE
typedef unsigned long                  ULONG;    // 4BYTE

typedef unsigned char                  BYTE;     // 1BYTE
typedef unsigned short                 WORD;     // 2BYTE
typedef unsigned long                  DWORD;    // 4BYTE
#else
typedef int                            LONG;     // 4BYTE
typedef unsigned int                   ULONG;    // 4BYTE

typedef unsigned char                  BYTE;     // 1BYTE
typedef unsigned short                 WORD;     // 2BYTE
typedef unsigned int                   DWORD;    // 4BYTE
#endif

#ifdef __LP64__
#define POINTER_SIZE                   8         // 8BYTE
#else
#define POINTER_SIZE                   4         // 4BYTE
#endif


#ifndef TRUE
#define TRUE                           1
#endif

#ifndef FALSE
#define FALSE                          0
#endif


#ifndef max
#define max(a,b)                       (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)                       (((a) < (b)) ? (a) : (b))
#endif


#ifdef _SERVER_
#define PACK_BUFFER_SIZE               8*1024
#define RECV_BUFFER_SIZE               64*1024
#define SEND_BUFFER_SIZE               128*1024
#else
#define MAX_BUFFER_SIZE                4*1024
#define PACK_BUFFER_SIZE               8*1024
#define RECV_BUFFER_SIZE               128*1024
#define SEND_BUFFER_SIZE               64*1024
#endif

#define MAX_GAMES                      100
#define MAX_GAME_PLAYERS               16
#define MAX_CONTEXTS                   (MAX_GAMES*MAX_GAME_PLAYERS)


extern DWORD HashValue(const char *szString);