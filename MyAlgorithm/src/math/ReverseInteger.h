#ifndef ALGORITHMS_REVERSE_INTEGER_H
#define ALGORITHMS_REVERSE_INTEGER_H

class ReverseInteger {
public:
    int reverse(int x) {
        int result = 0;
        while (x) {
            int tmp = result * 10 + (x % 10);
            if (tmp / 10 != result) {  // check overflow
                return 0;
            }
            result = tmp;
            x /= 10;
        }
        return result;
    }
};

#endif
