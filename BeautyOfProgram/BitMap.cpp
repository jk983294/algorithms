#include "BitMap.h"


void test_bitmap(){
    int a[] = {5,8,7,6,3,2,1,10,78,56,34,23,12,43,54,65,76,87,98,89,100};
    int size = sizeof(a)/sizeof(int);
    int i;
    BitMap bm(100,0);
    for(i=0; i<size; i++){
        bm.bitmap_set(a[i]);
    }
    for(i=0; i<=100; i++)  {
        if(bm.bitmap_get(i) > 0 )  cout << bm.bitmap_data(i)<< " ";
    }
    cout << endl;
}
//功能：初始化bitmap
//参数： size：bitmap的大小，即bit位的个数
//      start：起始值
BitMap::BitMap(int size, int start){
    bytesize = size/8+1;
    indexbase = start;
    bitmap.resize(bytesize);
    fill(bitmap.begin(),bitmap.end(),0x0);
}

//功能：将值index的对应位设为1
//index:要设的值
//返回值：0表示失败，1表示成功
int BitMap::bitmap_set(int index)  {
    int quo = (index-indexbase)/8 ;             //确定所在的字节
    int remainder = (index-indexbase)%8;        //字节内的偏移
    unsigned char x = (0x1<<remainder);
    if( quo > bytesize)  return 0;
    bitmap[quo] |= x;                           //所在字节内的特定位置为1  该位或
    return 1;
}
//功能：取bitmap第i位的值
//i：待取位
//返回值：-1表示失败，否则返回对应位的值
int BitMap::bitmap_get(int i)
{
    int quo = (i)/8 ;
    int remainder = (i)%8;
    unsigned char x = (0x1<<remainder);
    unsigned char res;
    if( quo > bytesize)  return -1;
    res = bitmap[quo] & x;
    return res > 0 ? 1 : 0;
}

//功能：返回index位对应的值
int BitMap::bitmap_data(int index) {
    return (index + indexbase);
}
