
#ifndef LIBCELL_MESH_IO
#define LIBCELL_MESH_IO
#include<stdio.h>
#include<Mesh/_Func_.h>
#define _ReadOff_   LibCell_ReadOff_
#define _ReadCell_  LibCell_ReadCell_
#define _WriteCell_ LibCell_WriteCell_
#define _ReadArray_ LibCell_ReadArray_
//当off文件描述单形是可以用_ReadOff_    需要在函数内部加判断给出提示
void _ReadOff_(template_m* ,char const * ,int);
void _ReadCell_(template_m*,char const *);
void _WriteCell_(template_m*,char const *);
//
void _ReadArray_(template_m*,double**,int**,int **,int*,int,int);
#endif

