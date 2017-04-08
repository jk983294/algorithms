#ifndef NETWORKFLOW_H
#define NETWORKFLOW_H

#include<iostream>
#include<deque>
using namespace std;


class NetworkFlow
{
public:
     int ** cMatrix;//capacity matrix
     int ** fMatrix;//max flow
     int ** rMatrix;//residual flow
     int * SPPiRecorder;//an array used to record the parents node in shortest path
     bool * visited;// during the BFS, record whether a node has been visited
     int nodeNumber;
     int source;
     int sink;


public:
     NetworkFlow();//constructor
    // NetworkFlow(int, int **, int **);
     void printInfo();
     void residualBuilder();
     bool FindSP();//find the SP from source to sink, if not found, return false;
     void mineMaxFlow();

};


NetworkFlow::NetworkFlow()// s and t represent the index of source node and sink node
{
     int i,j;
     cout<<"please input the Source node ID"<<endl;
     cin>>source;
     cout<<"please input the sink node ID"<<endl;
     cin>>sink;
     int s = source, t = sink;
     cout<<"Please input the number of nodes"<<endl;
     cin>>nodeNumber;

     cout<<"please input the matrix of capacity!"<<endl;
     cMatrix = new int*[nodeNumber];
     fMatrix = new int*[nodeNumber];//initialize the flow matrix to be all 0
     rMatrix = new int*[nodeNumber];
     for(i = 0;i<nodeNumber;i++)
     {
      rMatrix[i] = new int[nodeNumber];
      cMatrix[i] = new int[nodeNumber];
      fMatrix[i] = new int[nodeNumber];
      for(j = 0;j<nodeNumber;j++)
      {
       cin>>cMatrix[i][j];
       fMatrix[i][j] = 0;
       rMatrix[i][j] = 0;
      }
     }
    /* for(i = 0;i<nodeNumber;i++)
     {
      if(cMatrix[s][i]!=0)
      {
       fMatrix[s][i] = cMatrix[s][i];
       fMatrix[i][s] = -1*cMatrix[s][i];
       if(i!=t)
       excessNode.push_back(i);//the sink cannot puch flow back!
      }
     }//all the outgoing links from source should be satuated first*/

     residualBuilder();//compose the residual network.
     printInfo();

}
bool NetworkFlow::FindSP()//Use BFS to find a SP
{
   int i,j;
   SPPiRecorder = new int[nodeNumber];
   visited = new bool[nodeNumber];


   for(i = 0;i<nodeNumber;i++)
   {
    visited[i] = false;
   }
   visited[source] = true;
   SPPiRecorder[source] = source;//special node
   deque<int> nodeSet;
   nodeSet.push_back(source);


   while(nodeSet.size()!=0)
   {
    //cout<<"yes"<<endl;
    int temp = nodeSet.at(0);
    nodeSet.pop_front();//get the first node in the queue


    for(i = 0;i<nodeNumber;i++)
    {
     if(rMatrix[temp][i]>0 && !visited[i])
     {
      nodeSet.push_back(i);
      SPPiRecorder[i] = temp;
      visited[i] = true;
     }
     if(i == sink)
     {
      break;
     }
    }



   }


   if(visited[i])
    return true;
   else
    return false;//SP not found
}
void NetworkFlow::mineMaxFlow()
{
   int i,j,temp,r,k;
   int augumentWeight = INT_MAX;

   while(FindSP())
   {
        temp = sink;
        while(1)
        {
               r = rMatrix[SPPiRecorder[temp]][temp];
             if(augumentWeight>r && temp!=source)
             {
              augumentWeight = r;
             }
             if(temp == source)
             {break;}
             else
             {temp = SPPiRecorder[temp];}
        }
        cout<<augumentWeight<<endl;
        //cin.get();
        temp = sink;
        while(1)
        {
             k = SPPiRecorder[temp];
             if(cMatrix[k][temp]>0)
             {
                   fMatrix[k][temp] += augumentWeight;
                   fMatrix[temp][k] = -1*fMatrix[k][temp];
             }
             else
             {
                fMatrix[temp][k]-= augumentWeight;
                fMatrix[k][temp] = -1*fMatrix[temp][k];
             }
             rMatrix[k][temp]-=augumentWeight;
             rMatrix[temp][k]+=augumentWeight;

             if(k == source){break;}
             else{temp = SPPiRecorder[temp];}
        }
        printInfo();
    }
}
void NetworkFlow::residualBuilder()
{
     int i,j;
     for(i = 0;i<nodeNumber;i++)
     {
          for(j = 0;j<nodeNumber;j++)
          {
               if(fMatrix[i][j]>=0)
               {
                rMatrix[i][j] = cMatrix[i][j]-fMatrix[i][j];
               }
               else
               {
                rMatrix[i][j] = fMatrix[j][i];
               }
          }
     }
}
void NetworkFlow::printInfo()
{
    int i,j;
/* cout<<"the capacity situation of this graph is:"<<endl;


 for(i = 0;i<nodeNumber;i++)
 {
  for(j = 0;j<nodeNumber;j++)
  {
   cout<<cMatrix[i][j]<<" ";
  }
  cout<<endl;
 }*/
     cout<<"the flow situation of this graph is: "<<endl;
     for(i = 0;i<nodeNumber;i++)
     {
          for(j = 0;j<nodeNumber;j++)
          {
           cout<<fMatrix[i][j]<<" ";
          }
        cout<<endl;
     }
     cout<<"the residual network looks like: "<<endl;
     for(i = 0;i<nodeNumber;i++)
     {
          for(j = 0;j<nodeNumber;j++)
          {
           cout<<rMatrix[i][j]<<" ";
          }
          cout<<endl;
     }

     int sum = 0;
     for(i= 0;i<nodeNumber;i++)
     {
           sum+=fMatrix[i][sink];
     }
    cout<<"the current flow is "<<sum<<endl;
    cout<<endl;
}
void test_networkflow()
{
     Graph a;

     a.mineMaxFlow();
     a.printInfo();
}

#endif
