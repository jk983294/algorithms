#ifndef MYTHOFNUMBERS_H
#define MYTHOFNUMBERS_H

#include "myutility.h"


void find_abnormal_number();                                                    //异形数，数组中有三个数字出现一次，其余出现2次，找出3个中的任意一个
void count_one_in_binary_number(unsigned int num);                              //二进制数中1的个数
void factorial_last_zeros(int num);                                             //阶乘末尾0的个数
void count_of_ones(int num);                                                    //从1到num的整数中1出现的次数，统计个十百位1的个数
int gcd(int x, int y);                                                          //求x,y 的最大公约数
void find_fittest_number(int N);                                                //给定N，找到最小的M使得乘积N*M的十进制表达式中只有0和1
void max_sub_vector_sum();                                                      //数组子数组之和最大值
int max_sum_one_demension_vector(vector<int> &a, int &surestartpos, int &endpos);
void max_sum_sub_two_demension_vectors();                                       //二维数组最大子数组和
void max_ascend_sub_vector();                                                   //最长递增子序列
void right_shift();                                                             //右移
bool ishuiwen(int a);                                                           //正整数  判断是否为回文数字
void test_count_range();                                                        //排序好区域内数的个数
void calc_asymptotic_vlue();                                                    //渐近求值，求 y = x^2 的极小值
void antCrawlTime();                                                            //蚂蚁爬杆最短最长时间
void last_num_wangyi();                                                         //网易题目 199循环队列 逢二删除 求最后一个数字
void chinese_left_therom();                                                     //中国剩余定理

#endif
