#include "PrefixSorting.h"
#include "PackageProblem.h"
#include "GraphColoring.h"
#include "MythOfNumbers.h"
#include "MinDistancePointPair.h"
#include "stringhandle.h"
#include "TreeHandle.h"
#include "SystemInfo.h"
#include "BitMap.h"
#include "QueueWithMax.h"

void test_QueueWithMax();                                   //No 3.7
int main(){

//  test_PrefixSort();                                      // No 1.3  烙饼排序
//  test_Sack();                                            // No 1.6  背包问题        饮料供应
//  test_GraphColoring();                                   //着色问题  No 1.9 见面会安排
//  test_is_BiPartite();                                    //检测一个图是不是二部图
//  count_one_in_binary_number(7);                          //二进制数中1的个数  No. 2.1
//  factorial_last_zeros(26);                               //阶乘末尾0的个数    No. 2.2
//  count_of_ones(9999);                                    //从1到num的整数中1出现的次数  No. 2.4
//  cout<<gcd(9,4)<<endl;                                   //求最大公约数 No. 2.7
//  find_fittest_number(22);                                //给定N，找到最小的M使得乘积N*M的十进制表达式中只有0和1  No. 2.8
//  test_MinDistancePointPair();                            //计算点对之间的最短距离  No. 2.11
//  max_sub_vector_sum();                                   //数组子数组之和最大值 No.2.14
//  max_sum_sub_two_demension_vectors();                    //二维数组最大子数组和  No. 2.15
//  max_ascend_sub_vector();                                //最长递增子序列   No. 2.16
//  right_shift();                                          //右移k位  No. 2.17
//  cout<<ishuiwen(122)<<endl;                              //正整数  判断是否为回文数字
//  test_count_range();                                     //排序好的数组中，在 [ startnum, endnum ] (都是闭区间)之间的数有多少个
//  calc_asymptotic_vlue();                                 //渐近求值，求 y = x^2 的极小值
//  last_num_wangyi();                                      //网易题目 199循环队列 逢二删除 求最后一个数字
//  chinese_left_therom();                                  //中国剩余定理
//  find_abnormal_number();                                 //异形数，数组中有三个数字出现一次，其余出现2次，找出3个中的任意一个

//  basic_string_app();                                     //kmp
//  longest_huiwen_substr();                                //最长回文串
//  cout<<str_contain_circle_shift("AABCD","CDAA")<<endl;   //字符串移位包含问题  No. 3.1
//  cout<<simlarity_of_two_string("dfjsdf","kdfasd")<<endl; //字符串相似度            No. 3.3
//  bulid_by_preorder_inorder();                            //重建二叉树 No. 3.9  层次遍历 No. 3.10
//  antCrawlTime();                                         //蚂蚁爬杆最短最长时间        No. 4.7

    //SYS
//  cout<<isLittleEndian()<<endl;
//  cout<<isBigEndian()<<endl;
//  stack_heap_grow_direction();

//  test_bitmap();

    int a;
    cin>>a;
    return 0;
}
void test_QueueWithMax(){
    QueueWithMax qwm;
    qwm.insertQueue(5);
}
