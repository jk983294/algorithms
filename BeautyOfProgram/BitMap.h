#ifndef BITMAP_H
#define BITMAP_H

#include "myutility.h"

class BitMap{
public:
    vector<char> bitmap;
    int bytesize;                                   //g_size 为size bit对应的byte位数
    int indexbase;                                  //起始值
public:
    BitMap(int size, int start);                    //size：bitmap的大小，即bit位的个数
    int bitmap_set(int index);                      //将值index的对应位设为1
    int bitmap_get(int i);                          //取bitmap第i位的值
    int bitmap_data(int index) ;                    //功能：返回index位对应的值
};

void test_bitmap();

#endif
