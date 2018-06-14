#include <iomanip>
#include <iostream>

using namespace std;

struct Data {
    int av1;
    double ap1;
    int av2;
    double ap2;
    int av3;
    double ap3;
    int av4;
    double ap4;
    int av5;
    double ap5;
    int bv1;
    double bp1;
    int bv2;
    double bp2;
    int bv3;
    double bp3;
    int bv4;
    double bp4;
    int bv5;
    double bp5;
};

std::ostream& operator<<(std::ostream& os, const Data& d) {
    os << "av1: " << d.av1 << " ap1: " << d.ap1 << " av2: " << d.av2 << " ap2: " << d.ap2 << " av3: " << d.av3
       << " ap3: " << d.ap3 << " av4: " << d.av4 << " ap4: " << d.ap4 << " av5: " << d.av5 << " ap5: " << d.ap5
       << " bv1: " << d.bv1 << " bp1: " << d.bp1 << " bv2: " << d.bv2 << " bp2: " << d.bp2 << " bv3: " << d.bv3
       << " bp3: " << d.bp3 << " bv4: " << d.bv4 << " bp4: " << d.bp4 << " bv5: " << d.bv5 << " bp5: " << d.bp5;
    return os;
}

void printHex(void* a, size_t size) {
    uint8_t* address = reinterpret_cast<uint8_t*>(a);
    for (size_t i = 0; i < size; ++i) {
        uint8_t x = *(address + i);
        cout << hex << ((x & 0xF0) >> 4) << (x & 0x0F) << " ";
        if ((i + 1) % 16 == 0) {
            cout << endl;
        }
    }
    cout << endl;
}

template <class T>
void printStructHex(T& t) {
    printHex(&t, sizeof(T));
}

void diff(uint8_t* v1, uint8_t* v2) {
    cout << std::dec;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 16; ++j) {
            int result = v1[i * 16 + j] - v2[i * 16 + j];
            cout << setw(6) << result;
        }
        cout << endl;
    }
    cout << endl;
}

static int delta[] = {70, 252, 0, 0, 0, 0, 0, 0, 154, 154, 154, 154, 154, 122, 150, 192};

void encrypt(uint8_t* v1, uint8_t* v2) {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 16; ++j) {
            v2[i * 16 + j] = static_cast<uint8_t>((v1[i * 16 + j] + delta[j]) & 0xFF);
        }
    }
}

void decrypt(uint8_t* v1, uint8_t* v2) {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 16; ++j) {
            v2[i * 16 + j] = static_cast<uint8_t>(((v1[i * 16 + j] & 0x1FF) - delta[j]) & 0xFF);
        }
    }
}

int main() {
    Data data;
    data.av1 = 2122;
    data.ap1 = 1000.9;
    data.av2 = 33125;
    data.ap2 = 1100.8;
    data.av3 = 21343;
    data.ap3 = 1200.7;
    data.av4 = 1234;
    data.ap4 = 1260.2;
    data.av5 = 2099;
    data.ap5 = 1384.1;
    data.bv1 = 8821;
    data.bp1 = 990.5;
    data.bv2 = 7413;
    data.bp2 = 987.3;
    data.bv3 = 31123;
    data.bp3 = 960.9;
    data.bv4 = 8732;
    data.bp4 = 957.8;
    data.bv5 = 3130;
    data.bp5 = 924.1;

    uint8_t encrypt1[160];
    encrypt(reinterpret_cast<uint8_t*>(&data), encrypt1);
    uint8_t decrypt1[160];
    decrypt(encrypt1, decrypt1);
    diff(decrypt1, encrypt1);

    Data data1 = *reinterpret_cast<Data*>(decrypt1);
    cout << data << endl << data1 << endl;

    uint8_t raw[160]{0x0e, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x33, 0x33, 0x33, 0x33, 0xad, 0x27, 0x00,
                     0x5b, 0x76, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0x3d, 0x28, 0x00,
                     0x74, 0x2c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x67, 0x66, 0x66, 0x66, 0x66, 0xcc, 0x2a, 0x00,
                     0x7e, 0x2c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x67, 0x66, 0x66, 0x66, 0x66, 0xba, 0x2b, 0x00,
                     0x48, 0x4e, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xaa, 0x2d, 0x00,
                     0xd9, 0x54, 0x01, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0x9a, 0x9a, 0x9a, 0x9a, 0x9a, 0x84, 0x27, 0x00,
                     0xc7, 0x1d, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0x77, 0x26, 0x00,
                     0xcd, 0x75, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x33, 0x33, 0x33, 0x33, 0x0d, 0x26, 0x00,
                     0xf6, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xcd, 0xcd, 0xcd, 0xcd, 0xcd, 0x01, 0x26, 0x00,
                     0xd3, 0x76, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7a, 0x26, 0x00};

    uint8_t decrypt2[160];
    decrypt(raw, decrypt2);
    Data data2 = *reinterpret_cast<Data*>(decrypt2);
    cout << data2 << endl;
    return 0;
}
