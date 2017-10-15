#ifndef CGRAPHICS_H
#define CGRAPHICS_H
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

class CGraphics
{
private:
    unsigned int m_uNodeCount;    //结点个数
    vector<char> m_vNodeName;   //各结点名字
    vector< vector<int> > m_vMatrix;    //无向图的邻接矩阵,到自身为0,不可到达为-1
    vector<int> m_vH;   //各节点的启发值

    vector< vector<int> > m_vOpen;     //open表,vector<int>第一个值为当前路径的耗散值,后面各种为该路径所经过结点
    vector< vector<int> > m_vClose;    //close表,vector<int>第一个值为当前路径的耗散值,后面各种为该路径所经过结点

public:
    CGraphics();
    CGraphics(const int nodeCount, const char *nodeName, const int *h);
    CGraphics(const int nodeCount, const char *nodeName, const int *h, const int *matrix);
    ~CGraphics();

    void setMatrix(const int nodeCount);   //用结点数量初始化邻接矩阵
    void setMatrix(const int nodeCount, const int *matrix);   //用结点数量和一维整型数组初始化无向图
    void setNodeName(const char *nodeName);   //用一维字符数组设置各结点名字
    void setNodeH(const int *h);  //用一维整型数组设置各结点的启发值
    void printGraphics();   //打印无向图的矩阵

    int nodeNumber(char node);  //获取结点对应的编号(编号与矩阵的下标相对应),找不到返回-1
    bool isIn(int nodeNumber, const vector<int> list);  //判断对应编号的结点是否在list表中
    bool isInclose(int nodeNumber);  //判断对应编号的结点是否在close表中
    void sortOpen();    //依据open表每个元素的第一个元素(即各路径的耗散值)对open进行升序排序
    void addToOpen(vector<int> &road);  //将路径添加到open表，如果存在到当前结点的路径,且耗散值比新路径高,则更新为新路径
    void addToClose(vector<int> &road);  //将路径添加到close表，如果存在到当前结点的路径,且耗散值比新路径高,则更新为新路径
    int countLength(vector<int> &road); //依据路径road算出其长度
    void countG(vector<int> &road);  //依据路径road算出其耗散值,road第一个元素存储耗散值,其后为结点
    void countF(vector<int> &road);  //依据路径road算出其评估值,存在road第一个元素,其后为结点
    void addNewNode(vector<int> &road, int nodeNew); //将nodeNew添加到路径road中,并算出路径的耗散值
    void aStarFindWay(char nodeA, char nodeB);  //aStar算法查找路径
};

#endif // CGRAPHICS_H
