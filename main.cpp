/*
ʱ�䣺2021.4.12
Ŀ�ģ���ʾ��ѡ���Թ���һ������·��
���ͣ�www.mygoddess.icu
github:mygoddess-007700
*/
# include <iostream>
using namespace std;

enum _map{start = 1, finish, road, wall, end}; //��ʾ��ͼ�Ķ�ά�����ÿ��Ԫ�ض��������ö�����ͣ����ڱ�ʾ���ǵ�����
enum direction{east = 1, south = 2, west = 3, north = 4}; //û���õ���ԭ����Ϊ�˺������ƣ�
                                                        // ������int��1����ʾ����������(direction)1����ʾ

struct Map //��ʾ��ͼ�Ķ�ά�����ÿ��Ԫ��
{
//    char wall = '0';
//    char road = '1';
    char date = '0';
    _map m = (_map)3;
};

struct coord //�������ʾ��
{
    int x;
    int y;
};

typedef struct BLOCK //��ʾ�Թ�·��������Ԫ�ص�������û��order����
{
    int order;
    coord xy;
    int direction;
}Block, *pBlock;

typedef struct Node //��ʾ�Թ�·��������Ԫ��
{
    Block date; //������
    Node * pNext; //ָ����
}NODE, *pNODE;

class ZouMiGong
{
private:
    const static int size = 10; //�Թ��ĳ��Ϳ�(�����޸ĳ����û����룬������Ҫ���ԸĶ�����һ�θ�����˵��)
    pNODE pHead; //����һ���Թ�·������ͷ���(��̬�����ڹ��캯����)
    int len; //����ĳ���
    Map map[size][size]; //������û�ѡ���Թ���С��(�а취�ˣ��´���˵����Ϊ��)
    coord start = {0, 0}; //������ʼ��һ����ʼλ������ͽ���λ������
    coord finish = {9, 9}; //��prepare����������û�����(���Ի������)

public:
    ZouMiGong(); //�Թ���Ĺ��캯��(�������������Թ���Ķ����ʱ����Զ�����)
    void push_list(pBlock e); //�Թ�·���������һ�����
    void delete_list(pBlock e); //�Թ�·������ɾ��һ�����
    bool empty_list(); //�ж��Թ�·�������Ƿ�Ϊ��
    void travel_list(); //���һ���Թ�·������
    void destroy_list(); //�����Թ�·������(��֣�Ϊʲô��ʹ��������������򲻱���)

    void prepare(); //һ����Ҫ��ʼ���û������ĺ���
    bool pass(coord curPos); //ͨ���ö�ά��������ת���ɵ���������Ԫ�ص�����ö�����ͣ��ж�������ܷ�����Թ�·������
    static coord nextPos(coord curPos, int di); //ͨ����������귵��һ���ڵ�ǰ������һ��������
    friend bool operator==(coord c1, coord c2); //���صȺ������(C++����)
    friend ostream & operator<<(ostream & os, const coord & pos); //�������������(C++����)

    bool construct(); //�����Թ�·��������(��Ҫ����)
};

int main()
{
    ZouMiGong Z;
    Z.prepare();
    Z.construct();
    Z.travel_list();
//    Z.destroy_list(); //Ϊʲô�������أ�
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
        cout<<"���Թ�û�г��ڣ�"<<endl;
    }
    pNODE p = pHead;
    while(p->pNext != nullptr)
    {
        p = p->pNext;
        cout<<p->date.xy<<"����";
    }
    cout<<"����"<<endl;
}

void ZouMiGong::prepare()
{
    cout<<"������һ����СΪ10*10���Թ���1����·��0����ǽ"<<endl;
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
                cout<<"�����ʽ����"<<endl;
            }
        }
    }
    cout<<"����������Թ������������յ����꣡"<<endl;
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
            map[curPos.x][curPos.y].m = (_map)5; //�����㼣
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
��עһ���������ݣ�
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
clion�������ǣ�
(1, 1)����(1, 2)����(2, 2)����(3, 2)����(3, 1)����(4, 1)����(5, 1)����(5, 2)����(5, 3)����(6, 3)
 ����(6, 4)����(6, 5)����(7, 5)����(8, 5)����(8, 6)����(8, 7)����(8, 8)��������
*/