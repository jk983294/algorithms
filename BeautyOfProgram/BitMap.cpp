#include "MyUtility.h"

class BitMap {
public:
    vector<uint8_t> bitmap;
    int byteSize;   // how many char needed, bitmap.size()
    int indexBase;  // 起始值

public:
    BitMap(int size, int start);  // bitmap的大小, start起始值

    /**
     * 将值index的对应位设为1
     * @param index
     */
    bool set(int index);

    /**
     * 取bitmap第index位的值
     * @param index
     * @return
     */
    bool get(int index);

    /**
     * 返回index位对应的值
     * @param index
     * @return
     */
    int data(int index);
};

int main() {
    int a[] = {5, 8, 7, 6, 3, 2, 1, 10, 78, 56, 34, 23, 12, 43, 54, 65, 76, 87, 98, 89, 100};
    int size = sizeof(a) / sizeof(int);
    int i;
    BitMap bm(100, 0);
    for (i = 0; i < size; i++) {
        bm.set(a[i]);
    }
    for (i = 0; i <= 100; i++) {
        if (bm.get(i) > 0) cout << bm.data(i) << " ";
    }
    cout << endl;
    return 0;
}

BitMap::BitMap(int size, int start) {
    byteSize = size / 8 + 1;
    indexBase = start;
    bitmap.resize(byteSize);
    fill(bitmap.begin(), bitmap.end(), 0x0);
}

bool BitMap::set(int index) {
    int byteOffset = (index - indexBase) / 8;        //确定所在的字节
    int withinByteOffset = (index - indexBase) % 8;  //字节内的偏移
    uint8_t x = static_cast<uint8_t>(0x1 << withinByteOffset);
    if (byteOffset > byteSize) return false;
    bitmap[byteOffset] |= x;  //所在字节内的特定位置为1  该位或
    return true;
}

bool BitMap::get(int index) {
    int byteOffset = (index) / 8;
    int withinByteOffset = (index) % 8;
    uint8_t x = static_cast<uint8_t>(0x1 << withinByteOffset);
    if (byteOffset > byteSize) return -1;
    return bitmap[byteOffset] & x;
}

int BitMap::data(int index) { return (index + indexBase); }
