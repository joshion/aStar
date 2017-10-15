#include "cgraphics.h"

CGraphics::CGraphics()
{
}

CGraphics::CGraphics(const int nodeCount, const char *nodeName, const int *h)
{
    m_uNodeCount = nodeCount;
    setMatrix(m_uNodeCount);
    setNodeH(h);
    setNodeName(nodeName);
}

CGraphics::CGraphics(const int nodeCount, const char *nodeName, const int *h, const int *matrix)
{
    m_uNodeCount = nodeCount;
    setNodeH(h);
    setNodeName(nodeName);
    setMatrix(m_uNodeCount, matrix);

}

CGraphics::~CGraphics()
{

}

void CGraphics::setNodeName(const char *nodeName)
{
    for(unsigned int i = 0; i < m_uNodeCount; ++i)
    {
        m_vNodeName.push_back(nodeName[i]);
    }
}

void CGraphics::setNodeH(const int *h)
{
    for(unsigned int i = 0; i < m_uNodeCount; ++i)
    {
        m_vH.push_back(h[i]);
    }
}

void CGraphics::setMatrix(const int nodeCount)
{
    for(int i = 0; i < nodeCount; ++i)
    {
        vector<int> temp;
        for(int j = 0; j < nodeCount; ++j)
        {
            if(i == j)//i等于j,即为结点到其自身,值设为0
            {
                temp.push_back(0);
            }
            else
            {
                temp.push_back(-1);
            }
        }
        m_vMatrix.push_back(temp);
    }
}

void CGraphics::setMatrix(const int nodeCount, const int *matrix)
{
    for(int i = 0; i < nodeCount; ++i)
    {
        vector<int> temp;
        for(int j = 0; j < nodeCount; ++j)
        {
            temp.push_back(matrix[i*nodeCount+j]);  //矩阵的第i行从i*nodeCount开始
        }
        m_vMatrix.push_back(temp);
    }
}

void CGraphics::printGraphics()
{
    //打印结点名字
    cout << "The nodes' name is:" << endl;
    for(unsigned int i =0 ; i < m_vNodeName.size(); ++i)
    {
        cout << setw(3)  << m_vNodeName[i] << " ";
    }
    cout << endl;

    //打印各结点的启发值
    cout << "The nodes' h value is:" << endl;
    for(unsigned int i =0 ; i < m_vH.size(); ++i)
    {
        cout << setw(3) << m_vH[i] << " ";
    }
    cout << endl;

    //打印无向图的邻接矩阵
    cout << "The graphics's matrix is:" << endl;
    for(unsigned int i =0 ; i < m_vMatrix.size(); ++i)
    {
        for(unsigned int j =0 ; j < m_vMatrix[i].size(); ++j)
        {
            cout << setw(3)  << m_vMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

int CGraphics::nodeNumber(char node)
{
    for(unsigned int i = 0; i < m_vNodeName.size(); ++i)
    {
        if(node == m_vNodeName[i])
            return i;
    }
    return -1;
}

bool CGraphics::isIn(int nodeNumber, const vector<int> list)
{
    for(auto a : list)
    {
        if(a == nodeNumber)
            return true;
    }
    return false;
}

bool CGraphics::isInclose(int nodeNumber)
{//判断对应编号的结点是否在close表中

    for(auto a: m_vClose)
    {
        if(a.back() == nodeNumber)
            return true;
    }
    return false;
}

void CGraphics::sortOpen()
{
    for(unsigned int i = 0; i < m_vOpen.size(); ++i)
    {
        for(unsigned int j = i; j < m_vOpen.size(); ++j)
        {
            if(m_vOpen[i][0] > m_vOpen[j][0])
            {
                vector<int> temp = m_vOpen[i];
                m_vOpen[i] = m_vOpen[j];
                m_vOpen[j] = temp;
            }
        }
    }
}

void CGraphics::addToOpen(vector<int> &road)
{
//将路径添加到open表，如果存在到当前结点的路径,且耗散值比新路径高,则更新为新路径
    unsigned int i = 0;
    for(; i < m_vOpen.size(); ++i)
    {
        if(road.back() == m_vOpen[i].back() && m_vOpen[i][0] > road[0])
        {
            m_vOpen[i] = road;
            break;
        }
    }
    if(i >= m_vOpen.size())    //m_vClsoe不存在到当前结点的路径,将路径road添加到close
        m_vOpen.push_back(road);
}

void CGraphics::addToClose(vector<int> &road)
{
//将路径road添加到close,如果存在到当前结点的路径,且耗散值比新路径高,则更新为新路径
    unsigned int i = 0;
    for(; i < m_vClose.size(); ++i)
    {
        if(road.back() == m_vClose[i].back() && m_vClose[i][0] > road[0])
        {
            m_vClose[i] = road;
            break;
        }
    }
    if(i >= m_vClose.size())    //m_vClsoe不存在到当前结点的路径,将路径road添加到close
        m_vClose.push_back(road);
}

void CGraphics::countG(vector<int> &road)
{
//依据路径road算出其耗散值,road第一个元素存储耗散值,后面为结点
    road[0] = 0;
    for(unsigned int i = 1; i < road.size()-1 ; ++i)
    {
        road[0] += m_vMatrix[road[i]][road[i+1]];
    }
}

int CGraphics::countLength(vector<int> &road)
{
//依据路径road算出其长度
    int length = 0;
    for(unsigned int i = 1; i < road.size()-1 ; ++i)
    {
        length += m_vMatrix[road[i]][road[i+1]];
    }
    return length;
}

void CGraphics::countF(vector<int> &road)
{//依据路径road算出其评估值,存在road第一个元素,其后为结点
    road[0] += m_vH[road.back()]; //将到当前结点路径的耗散值加上启发值等于评估值
}

void CGraphics::addNewNode(vector<int> &road, int nodeNew)
{
//将nodeNew添加到路径road中,并算出路径的评价值
    road.push_back(nodeNew);
    countG(road);   //算出路径的耗散值
    countF(road);   //算出路径的评价值
}

void CGraphics::aStarFindWay(char nodeA, char nodeB)
{
    int begin = nodeNumber(nodeA);
    int end = nodeNumber(nodeB);
    vector<int> temp;
    temp.push_back(m_vH[begin]);
    temp.push_back(begin);
    m_vOpen.push_back(temp); //把起始结点加入open表
    temp.clear();
    while(m_vOpen[0].back() != end)
    {
        sortOpen(); //对open表进行排序
        temp = m_vOpen[0];
        int nodeToExtend = temp.back(); //需要扩展的结点编号
        if(nodeToExtend ==  end)    //如果结点为终点则不需扩展
            continue;
        for(unsigned int i = 0; i < m_vMatrix.size(); ++i)
        {
            if(m_vMatrix[nodeToExtend][i] > 0 && !isInclose(i))
            {
                temp = m_vOpen[0];
                addNewNode(temp, i);
                addToOpen(temp);    //将路径添加到open表
            }
        }
        temp = m_vOpen[0];
        addToClose(temp);   //
        m_vOpen.erase(m_vOpen.begin()); //删除open表的第一个元素
    }

    //打印结点名字
    cout << "The aStarFindway is:" << endl;
    for(unsigned int i = 1 ; i < m_vOpen[0].size(); ++i)
    {
        cout << setw(3)  << m_vNodeName[m_vOpen[0][i]] << " ";
    }
    cout << endl;
    cout << " The road's length is " << countLength(m_vOpen[0]) << endl;

}
