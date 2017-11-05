#include <iostream>  
#include <memory.h>  
using namespace std;  
  
#define DIM 50  
  
//正向深搜，从起点出发   
void ForwardDFS(char map[DIM][DIM],//输入矩阵   
                bool sign[DIM][DIM],//返回标记结果图，true表示可以到达这个点，false表示不能到达   
                int Row,int Col,//矩阵规模   
                int curR, int curC)//当前点   
{  
    //若 当前点已走过 或 当前点是障碍物，停止递归   
    if (sign[curR][curC] || map[curR][curC] == '#')  
    {  
        return ;  
    }  
    //标记此点可达   
    sign[curR][curC] = true;  
    //标记可以往哪个方向移动  
    bool up,down,left,right;  
    up = down = left = right = false;   
    if (map[curR][curC] == '.')//向下移动   
    {  
        down = true;  
    }  
    else if (map[curR][curC] == '-')//左右移动   
    {  
        left = right = true;  
    }  
    else if (map[curR][curC] == '|')//上下移动   
    {  
        up = down = true;  
    }  
    else if (map[curR][curC] == '+' || map[curR][curC] == 'S' || map[curR][curC] == 'T')//上下左右移动   
    {  
        up = down = left = right = true;  
    }  
    //上  
    if (up && curR-1 >= 0)  
    {  
        ForwardDFS(map,sign,Row,Col,curR-1,curC);  
    }  
    //下   
    if (down && curR+1 < Row)  
    {  
        ForwardDFS(map,sign,Row,Col,curR+1,curC);  
    }  
    //左  
    if (left && curC-1 >= 0)  
    {  
        ForwardDFS(map,sign,Row,Col,curR,curC-1);  
    }  
    //右  
    if (right && curC+1 < Col)  
    {  
        ForwardDFS(map,sign,Row,Col,curR,curC+1);  
    }  
}  
  
//从终点出发，反向DFS   
void ReserveDFS(char map[DIM][DIM],//输入矩阵   
                bool sign[DIM][DIM],//返回标记结果图，true表示可以到达这个点，false表示不能到达   
                int Row,int Col,//矩阵规模   
                int curR, int curC,//当前点   
                int preR, int preC)//上一个点   
{  
    //若 当前点已走过 或 当前点是障碍物，停止递归   
    if (sign[curR][curC] || map[curR][curC] == '#')  
    {  
        return ;  
    }  
    //从下面来的，可以返回去，其他方向来的无法原路返回  
    if (map[curR][curC] == '.' && preR == curR+1 && preC == curC)  
    {     
        sign[curR][curC] = true;  
    }  
    //从左右来的可以返回去  
    else if (map[curR][curC] == '-' && preR == curR)  
    {     
        sign[curR][curC] = true;  
    }  
    //必须从上下来   
    else if (map[curR][curC] == '|' && preC == curC)  
    {  
        sign[curR][curC] = true;  
    }  
    //可随便返回   
    else if (map[curR][curC] == 'S' || map[curR][curC] == '+' || map[curR][curC] == 'T')  
    {  
        sign[curR][curC] = true;  
    }  
    //不可达，返回   
    if (sign[curR][curC] == false)  
    {  
        return ;  
    }  
    //上  
    if (curR-1 >= 0)  
    {  
        ReserveDFS(map,sign,Row,Col,curR-1,curC,curR,curC);  
    }  
    //下  
    if (curR+1 < Row)  
    {  
        ReserveDFS(map,sign,Row,Col,curR+1,curC,curR,curC);  
    }  
    //左  
    if (curC-1 >= 0)  
    {  
        ReserveDFS(map,sign,Row,Col,curR,curC-1,curR,curC);  
    }  
    //右  
    if (curC+1 < Col)  
    {  
        ReserveDFS(map,sign,Row,Col,curR,curC+1,curR,curC);  
    }  
}  
  
  
int main()  
{  
    int R,C;  
    cin>>R>>C;  
    char map[DIM][DIM];  
    bool sCanReach[DIM][DIM];//起点能到达的矩阵   
    bool tCanReach[DIM][DIM];//终点能到的矩阵    
    for (int i=0; i<R; i++)  
    {  
        for (int j=0; j<C; j++)  
        {  
            cin>>map[i][j];  
        }  
    }  
    memset(sCanReach,0,DIM*DIM);  
    memset(tCanReach,0,DIM*DIM);  
    //处理  
    for (int i=0; i<R; i++)  
    {  
        for (int j=0; j<C; j++)  
        {  
            if (map[i][j] == 'S')  
            {  
                ForwardDFS(map,sCanReach,R,C,i,j);  
            }  
        }  
    }  
    for (int i=0; i<R; i++)  
    {  
        for (int j=0; j<C; j++)  
        {  
            if (map[i][j] == 'T')  
            {  
                if (sCanReach[i][j] == false)  
                {  
                    cout<<"I'm stuck!"<<endl;  
                    return 0;  
                }  
                ReserveDFS(map,tCanReach,R,C,i,j,i,j);  
            }  
        }  
    }  
      
    int num = 0;  
  
/*  for (int i=0; i<R; i++) 
    { 
        for (int j=0; j<C; j++) 
        { 
            cout<<map[i][j]<<" "; 
        } 
        cout<<endl; 
    } 
    for (int i=0; i<R; i++) 
    { 
        for (int j=0; j<C; j++) 
        { 
            cout<<sCanReach[i][j]<<" "; 
        } 
        cout<<endl; 
    } 
    cout<<endl; 
    for (int i=0; i<R; i++) 
    { 
        for (int j=0; j<C; j++) 
        { 
            cout<<tCanReach[i][j]<<" "; 
        } 
        cout<<endl; 
    } 
    cout<<endl; 
*/  
    for (int i=0; i<R; i++)  
    {  
        for (int j=0; j<C; j++)  
        {  
            if (map[i][j] != 'S' && map[i][j] != 'T' &&  
                sCanReach[i][j]  && !tCanReach[i][j])  
            {  
                num++;   
            }  
        }  
    }  
    cout<<num<<endl;  
    return 0;  
}  