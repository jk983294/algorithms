#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H
#include "myutility.h"


// 取地址是取得变量的地位地址
bool isLittleEndian();                              //判断系统大小端
bool isBigEndian();
void stack_heap_grow_direction();                   //栈堆的生长方向


#endif
