#include <iostream>
#include <cmath>
#include <vector>
#include <set>
using namespace std;

/***********************************************************************
 一般需要将其他算法的include注释掉，因为定义的数据结构可能相同
***********************************************************************/

///数据结构
/************************************************************************
稀疏图  邻接表
单源最短路径算法   Dijkstra 斐波那契堆实现  O(NlgN + E)
单源最短路径算法   bellman ford处理负环路 O(VE)
单源最短路径算法   SPFA 处理负环路 O(kE) k=2
图的遍历算法  如果该图的边较少，则用此方法比邻接矩阵O(n^2)快
************************************************************************/
//#include "SparseGraph.h"
/************************************************************************
 稀疏图  邻接矩阵
所有点对间最短路径   FloydWarshall  O(n^3), 稠密图，效率要高于执行|V|次Dijkstra算法
单源最短路径算法   Dijkstra 斐波那契堆实现  O(NlgN + N^2)


单源最短路径算法   bellmanford处理负环路 O(VE)
单源最短路径算法   SPFA 处理负环路 O(kE) k=2
图的遍历算法  如果该图的边较少，则用此方法比邻接矩阵O(n^2)快
************************************************************************/
//#include "DenseGraph.h"

///单源最短路径
//#include "DAG.h"                                      //邻接表表示，有向无环路图，拓扑排序，单源最短路径

#include "perm.h"                                       //递归求全排列
//#include "AStar.h"                                    //A* algorithm
//#include "postfixedexp.h"                             //中缀计算表达式转为后缀表达式
#include "BinaryTree.h"                                 //二叉树

///堆算法
//#include "MyHeap.h"                                   //堆,MaxHeap和双堆
//#include "MaxHeap.h"                                  //二叉最大堆
//#include "MinHeap.h"                                  //二叉最小堆
//#include "Deap.h"                                     //二叉双堆，维护最大最小子树
//#include "leftist.h"                                  //最大最小左偏树，支持合并两个堆
//#include "BinomialHeap.h"                             //最小二项堆
//#include "FibonacciHeap.h"                            //最小斐波那契堆

// greedy algorithm, locally optimal choice is globally optimal
#include "graph_MST_Kruskal.h"                          // graph minimum spanning tree
#include "graph_MST_Prim.h"                             // graph minimum spanning tree

///动态规划算法
#include "LongestCommonString.h"                        //最长公共子序列
//#include "EggDropPuzzle.h"
//#include "MatrixMultiple.h"                           //矩阵乘法
//#include "KMP.h"                                      //字符串匹配
//#include "Viterbi.h"

///排序算法
#include "SortAlgorithm.h"

///查找算法   (key , value)
//#include "BinarySearchTree.h"                         //二叉查找树
#include "slist.h"                                      //带头节点的单向链表，HashTable使用它做为处理碰撞的方法
#include "HashTable.h"
//#include "RedBlackTree.h"                             //红黑树
//#include "Set.h"                                      //以红黑树实现的set
//#include "TrieTree.h"                                 //前缀树

//笔试算法
#include "AddFactor.h"                                  //分解给定的数，输出所有的加法因子
#include "MaxSumSubVector.h"                            //最大子序列和


using namespace std;
