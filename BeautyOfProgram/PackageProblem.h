#ifndef PACKAGEPROBLEM_H
#define PACKAGEPROBLEM_H

#include "myutility.h"

/************************************************************************/
/* 背包问题：物品 i 的性质 ( weights[i], prices[i] )        空间和价格
   袋子有总空间W， 求如何放置，使得袋子中的总价值最大*/
/************************************************************************/

class Sack
{
public:
    vector<int> weights, prices, Mi;                            //每种物品的空间和价格和物品最大个数
    int totalWeight, M    ;                                     //总空间, M件物品
    int initvalue;                                              //初始值，如果是最终结果==背包totalWeight则为-inf； 如果<=背包totalWeight则为0
public:
    Sack(int *w,int *p, int *m, int len, int totalW);
    void zero_one_sack_basic();                                 //0-1背包 基本解法
    void zero_one_sack_space_opt();                             //0-1背包 空间优化解法
    void muilti_sack();                                         //多重背包
};

void test_Sack();
void test_b_o_p_1_6();






#endif
