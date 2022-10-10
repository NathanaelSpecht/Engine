
/* Copyright (C) 2022 Nathanael Specht */

#ifndef UTILX_H
#define UTILX_H

#define here(); printf("%s:%d\n",__FILE__,__LINE__);

typedef char int8;
typedef short int16;
typedef long int32;
typedef long long int64;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
typedef unsigned long long uint64;

void* delete (void* ptr);
void* alloc (void* ptr, int64 n);
void* alloc_ignore_error (void* ptr, int64 n);

#endif

