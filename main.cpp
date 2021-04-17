/*
时间：2021.4.12
目的：表示出选定迷宫的一条可行路线
博客：www.mygoddess.icu
github:mygoddess-007700
*/
# include <iostream>
using namespace std;

enum _map{start = 1, finish, road, wall, end}; //表示地图的二维数组的每个元素都会包含该枚举类型，用于表示它们的属性
enum direction{east = 1, south = 2, west = 3, north = 4}; //没有用到的原因是为了和书类似，
                                                        // 所以用int的1来表示东而不是用(direction)1来表示

struct Map //表示地图的二维数组的每个元素
{
//    char wall = '0';
//    char road = '1';
    char date = '0';
    _map m = (_map)3;
};

struct coord //坐标简便表示法
{
    int x;
    int y;
};

typedef struct BLOCK //表示迷宫路线链表结点元素的数据域，没用order是懒
{
    int order;
    coord xy;
    int direction;
}Block, *pBlock;

typedef struct Node //表示迷宫路线链表结点元素
{
    Block date; //数据域
    Node * pNext; //指针域
}NODE, *pNODE;

class ZouMiGong
{
private:
    const static int size = 10; //迷宫的长和宽(可以修改成让用户输入，不过需要稍稍改动，下一次更新再说吧)
    pNODE pHead; //定义一个迷宫路线链表头结点(动态分配在构造函数里)
    int len; //链表的长度
    Map map[size][size]; //如何让用户选择迷宫大小呢(有办法了，下次再说，因为懒)
    coord start = {0, 0}; //先随便初始化一个开始位置坐标和结束位置坐标
    coord finish = {9, 9}; //在prepare函数里会让用户输入(人性化的设计)

public:
    ZouMiGong(); //迷宫类的构造函数(在主函数生成迷宫类的对象的时候会自动调用)
    void push_list(pBlock e); //迷宫路线链表插入一个结点
    void delete_list(pBlock e); //迷宫路线链表删除一个结点
    bool empty_list(); //判断迷宫路线链表是否为空
    void travel_list(); //输出一遍迷宫路线链表
    void destroy_list(); //毁灭迷宫路线链表(奇怪：为什么不使用这个函数，程序不报错)

    void prepare(); //一个主要开始和用户交互的函数
    bool pass(coord curPos); //通过该二维数组行列转换成的坐标代表的元素的属性枚举类型，判断这个点能否存入迷宫路线链表
    static coord nextPos(coord curPos, int di); //通过输入的坐标返回一个在当前方向走一格后的坐标
    friend bool operator==(coord c1, coord c2); //重载等号运算符(C++特性)
    friend ostream & operator<<(ostream & os, const coord & pos); //重载输入运算符(C++特性)

    bool construct(); //构造迷宫路线链表函数(主要函数)
};

int main()
{
    ZouMiGong Z;
    Z.prepare();
    Z.construct();
    Z.travel_list();
//    Z.destroy_list(); //为什么不报错呢？
    getchar();

    return 0;
}

ZouMiGong::ZouMiGong()
{
    pHead = new Node;
    pHead->pNext = nullptr;
    len = 0;
}

ostream & operator<<(ostream & os, const coord & pos)
{
    cout<<'('<<pos.x<<", "<<pos.y<<')';
    return os;
}

bool operator==(coord c1, coord c2)
{
    if(c1.x == c2.x && c1.y == c2.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool ZouMiGong::empty_list()
{
    if(len == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ZouMiGong::push_list(pBlock e)
{
    pNODE p = pHead;
    for(int i = 0; i < len; ++i)
    {
        p = p->pNext;
    }
    pNODE pNew = new Node;
    pNew->date = *e;
    pNew->pNext = nullptr;
    p->pNext = pNew;
    ++len;
}

void ZouMiGong::delete_list(pBlock e)
{
    pNODE p = pHead;
    for(int i = 0; i < len-1; ++i)
    {
        p = p->pNext;
    }

    *e = p->pNext->date;
    pNODE q = p->pNext;
    p->pNext = nullptr;
    delete q;
    q = nullptr;
    --len;
}

void ZouMiGong::destroy_list()
{
    pNODE p = pHead;
    while(pHead->pNext != nullptr)
    {
        for(int i = 0; i < len-1; ++i)
        {
            p = p->pNext;
        }
        Block M;
        pBlock m = &M;
        delete_list(m);
    }
    delete pHead;
}

void ZouMiGong::travel_list()
{
    if(pHead == nullptr)
    {
        cout<<"该迷宫没有出口！"<<endl;
    }
    pNODE p = pHead;
    while(p->pNext != nullptr)
    {
        p = p->pNext;
        cout<<p->date.xy<<"——";
    }
    cout<<"结束"<<endl;
}

void ZouMiGong::prepare()
{
    cout<<"请输入一个大小为10*10的迷宫，1代表路，0代表墙"<<endl;
    for(int m = 0; m < size; ++m)
    {
        for(int n = 0; n < size; ++n)
        {
            cin>>map[m][n].date;
            if(map[m][n].date == '0')
            {
                map[m][n].m = (_map)4;
            }
            else if(map[m][n].date == '1')
            {
                map[m][n].m = (_map)3;
            }
            else
            {
                cout<<"输出格式错误！"<<endl;
            }
        }
    }
    cout<<"请输入这个迷宫的起点坐标和终点坐标！"<<endl;
    int x1, y1, x2, y2;
    cin>>x1>>y1>>x2>>y2;
    map[x1][y1].m = (_map)1;
    map[x2][y2].m = (_map)2;
    start.x = x1;
    start.y = y1;
    finish.x = x2;
    finish.y = y2;
}

bool ZouMiGong::construct()
{
    coord curPos = start;
    int curStep = 1;
    do
    {
        if(pass(curPos))
        {
            map[curPos.x][curPos.y].m = (_map)5; //留下足迹
            Block E = {curStep, curPos, 1};
            pBlock e = &E;
            push_list(e);
            if(curPos == finish)
            {
                return true;
            }
            curPos = nextPos(curPos, 1);
            curStep++;
        }
        else
        {
            if(!empty_list())
            {
                Block b;
                pBlock e = &b;
                delete_list(e);
                while (e->direction == 4 && !empty_list())
                {
                    map[e->xy.x][e->xy.y].m = (_map)5;
                    delete_list(e);
                }
                if(e->direction < 4)
                {
                    e->direction++;
                    push_list(e);
                    curPos = nextPos(e->xy, e->direction);
                }
            }
        }
    }while(!empty_list());
    return false;
}

bool ZouMiGong::pass(coord curPos)
{
    if(map[curPos.x][curPos.y].m == (_map)4 || map[curPos.x][curPos.y].m == (_map)5)
    {
        return false;
    }
    else
    {
        return true;
    }
}

coord ZouMiGong::nextPos(coord curPos, int di)
{
    if(1 == di)
    {
        curPos.y++;
        return curPos;
    }
    else if(2 == di)
    {
        curPos.x++;
        return curPos;
    }
    else if(3 == di)
    {
        curPos.y--;
        return curPos;
    }
    else if(4 == di)
    {
        curPos.x--;
        return curPos;
    }
    else
    {
        exit(-1);
    }
}

/*
备注一个测试数据：
0000000000
0110111010
0110111010
0111100110
0100011110
0111011110
0101110110
0100010010
0011111110
0000000000
1 1 8 8
clion输出结果是：
(1, 1)——(1, 2)——(2, 2)——(3, 2)——(3, 1)——(4, 1)——(5, 1)——(5, 2)——(5, 3)——(6, 3)
 ——(6, 4)——(6, 5)——(7, 5)——(8, 5)——(8, 6)——(8, 7)——(8, 8)——结束
*/