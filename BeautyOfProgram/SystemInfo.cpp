#include "MyUtility.h"

// 取地址是取得变量的地位地址
bool isLittleEndian();  //判断系统大小端
bool isBigEndian();
void stack_heap_grow_direction();  //栈堆的生长方向

int main() {
    cout << isLittleEndian() << endl;
    cout << isBigEndian() << endl;
    stack_heap_grow_direction();
    return 0;
}

// 大端模式: 数据的低位保存在内存的高地址中，而数据的高位，保存在内存的低地址中；小端模式相反
bool isLittleEndian() {
    union w {  // 联合体union的存放顺序是所有成员都从低地址开始存放，而且所有成员共享存储空间
        int a;
        char b;
    } c;
    c.a = 1;
    return (c.b == 1);  // 低字节存的是数据的低字节数据是小端模式
}
bool isBigEndian() {
    int a = 0x11223344;  // 十六进制，一个数值占4位
    char b = *(char *)&a;  // 通过将short(2字节)强制类型转换成char单字节，b指向a的起始字节（低字节）
    return b == 0x11;  // 低字节存的是数据的高字节数据
}
void stack_heap_grow_direction() {
    int a = 1, b = 2;
    int *c = new int[2];
    int *d = new int[2];
    //栈，它的生长方式是向下的，是向着内存地址减小的方向增长
    cout << "stack grow direction : " << &a << " " << &b << endl;
    cout << "heap grow direction : " << c << " " << &c[1] << endl;
    //堆，生长方向是向上的，也就是向着内存地址增加的方向
    cout << "heap grow direction : " << c << " " << d << endl;
}
