#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <ctime>
using namespace std;
/********************************************************
*	Point.h : 棋盘点类                                  *
*	张永锋                                              *
*	zhangyf07@gmail.com                                 *
*	2010.8                                              *
*********************************************************/

int warn[13][13],warnnum;

class Point{
public:
	int x;
	int y;

	Point(int x, int y){
		this->x = x;
		this->y = y;
	}
};


bool userWin(const int x, const int y, const int M, const int N, int* const* board){
	//横向检测
    int i, j;
    int count = 0;
    for (i = y; i >= 0; i--)
        if (!(board[x][i] == 1))
            break;
    count += (y - i);
    for (i = y; i < N; i++)
        if (!(board[x][i] == 1))
            break;
    count += (i - y - 1);
    if (count >= 4) return true;

    //纵向检测
    count = 0;
    for (i = x; i < M; i++)
        if (!(board[i][y] == 1))
            break;
    count += (i - x);
    if (count >= 4) return true;

    //左下-右上
    count = 0;
    for (i = x, j = y; i < M && j >= 0; i++, j--)
        if (!(board[i][j] == 1))
            break;
    count += (y - j);
    for (i = x, j = y; i >= 0 && j < N; i--, j++)
        if (!(board[i][j] == 1))
            break;
    count += (j - y - 1);
    if (count >= 4) return true;

    //左上-右下
    count = 0;
    for (i = x, j = y; i >= 0 && j >= 0; i--, j--)
        if (!(board[i][j] == 1))
            break;
    count += (y - j);
    for (i = x, j = y; i < M && j < N; i++, j++)
        if (!(board[i][j] == 1))
            break;
    count += (j - y - 1);
    if (count >= 4) return true;

    return false;
}

bool machineWin(const int x, const int y, const int M, const int N, int* const* board){
	//横向检测
    int i, j;
    int count = 0;
    for (i = y; i >= 0; i--)
        if (!(board[x][i] == 2))
            break;
    count += (y - i);
    for (i = y; i < N; i++)
        if (!(board[x][i] == 2))
            break;
    count += (i - y - 1);
    if (count >= 4) return true;

    //纵向检测
    count = 0;
    for (i = x; i < M; i++)
        if (!(board[i][y] == 2))
            break;
    count += (i - x);
    if (count >= 4) return true;

    //左下-右上
    count = 0;
    for (i = x, j = y; i < M && j >= 0; i++, j--)
        if (!(board[i][j] == 2))
            break;
    count += (y - j);
    for (i = x, j = y; i >= 0 && j < N; i--, j++)
        if (!(board[i][j] == 2))
            break;
    count += (j - y - 1);
    if (count >= 4) return true;

    //左上-右下
    count = 0;
    for (i = x, j = y; i >= 0 && j >= 0; i--, j--)
        if (!(board[i][j] == 2))
            break;
    count += (y - j);
    for (i = x, j = y; i < M && j < N; i++, j++)
        if (!(board[i][j] == 2))
            break;
    count += (j - y - 1);
    if (count >= 4) return true;

    return false;
}

bool isTie(const int N, const int* top){
	bool tie = true;
    for (int i = 0; i < N; i++)
    {
        if (top[i] > 0)
        {
            tie = false;
            break;
        }
    }
    return tie;
}

void clearArray(int M, int N, int** board){
	for(int i = 0; i < M; i++){
		delete[] board[i];
	}
	delete[] board;
}


/*
	策略函数接口,该函数被对抗平台调用,每次传入当前状态,要求输出你的落子点,该落子点必须是一个符合游戏规则的落子点,不然对抗平台会直接认为你的程序有误
	
	input:
		为了防止对对抗平台维护的数据造成更改，所有传入的参数均为const属性
		M, N : 棋盘大小 M - 行数 N - 列数 均从0开始计， 左上角为坐标原点，行用x标记，列用y标记
		top : 当前棋盘每一列列顶的实际位置. e.g. 第i列为空,则_top[i] == M, 第i列已满,则_top[i] == 0
		_board : 棋盘的一维数组表示, 为了方便使用，在该函数刚开始处，我们已经将其转化为了二维数组board
				你只需直接使用board即可，左上角为坐标原点，数组从[0][0]开始计(不是[1][1])
				board[x][y]表示第x行、第y列的点(从0开始计)
				board[x][y] == 0/1/2 分别对应(x,y)处 无落子/有用户的子/有程序的子,不可落子点处的值也为0
		lastX, lastY : 对方上一次落子的位置, 你可能不需要该参数，也可能需要的不仅仅是对方一步的
				落子位置，这时你可以在自己的程序中记录对方连续多步的落子位置，这完全取决于你自己的策略
		noX, noY : 棋盘上的不可落子点(注:其实这里给出的top已经替你处理了不可落子点，也就是说如果某一步
				所落的子的上面恰是不可落子点，那么UI工程中的代码就已经将该列的top值又进行了一次减一操作，
				所以在你的代码中也可以根本不使用noX和noY这两个参数，完全认为top数组就是当前每列的顶部即可,
				当然如果你想使用lastX,lastY参数，有可能就要同时考虑noX和noY了)
		以上参数实际上包含了当前状态(M N _top _board)以及历史信息(lastX lastY),你要做的就是在这些信息下给出尽可能明智的落子点
	output:
		你的落子点Point
*/

                //walk(M,N,top,board,lastX,lastY,noX,noY,lastX,lastY+1,value,side,ans);

int bd(int M,int N,int lastX,int lastY,int** board,int xd, int yd, int dev)
{
    int ans=lastX+xd+yd*dev;
    if(ans<0 || ans>=M) return -10;
    return board[ans][lastY+yd];
}

int walk(const int M, const int N, int* top,  int** board, 
	const int lastX, const int lastY, const int noX, const int noY, int &x, int &y, int posx, int posy, int &value, int side, int ans) //0 投降 1 对面有三个 3 对面有两个 4 自由
{
    if(ans==5 && (posx!=x || posy!=y)) {printf("dsf");return 0;}
    x=posx;y=posy;
    return 1;
}

int force(const int M, const int N, int* top,  int** board, 
	const int lastX, const int lastY, const int noX, const int noY, int &x, int &y, int &value, int side, int dev, int ans) //0 投降 1 对面有三个 2 竖着的3个 3 对面有两个 4 自由
{
    //先看自己能不能连四个

    //再看对手的三个
    //上下
    if(lastX<M-2 && bd(M,N,lastX,lastY,board,+1,0,dev)==side && bd(M,N,lastX,lastY,board,+2,0,dev)==side && lastX>0){x=lastX-1;y=lastY;return 6;}
    //左右
    if(lastY<N-2 && bd(M,N,lastX,lastY,board,0,+1,dev)==side && bd(M,N,lastX,lastY,board,0,+2,dev)==side)//_xoo_
    {
        if(lastY>0)
        {
            if(top[lastY-1]==lastX+1)
            {
                if(lastY<N-3 && top[lastY+3]==lastX+1)return 0;else {y=lastY-1;x=lastX;return 5;}
            }
            else if(top[lastY-1]<lastX+1)
            {
                warn[lastX+1][lastY-1]=side;
                if(lastY<N-3 && top[lastY+3]<lastX+1) warn[lastX+1][lastY+3]=side;
            }
        }
        if(lastY<N-3)
        {
            if(top[lastY+3]==lastX+1){y=lastY+3;x=lastX;return 5;}
            if(top[lastY+3]<lastX+1)warn[lastX+1][lastY+3]=side;
        }
    }
    if(lastY<N-3 && bd(M,N,lastX,lastY,board,0,+1,dev)==side && bd(M,N,lastX,lastY,board,0,+3,dev)==side)
        if(top[lastY+2]==lastX+1){y=lastY+2;x=lastX;return 5;} else if(top[lastY+2]<lastX+1) warn[lastX+1][lastY+2]=side;//xo_o
    if(lastY<N-3 && bd(M,N,lastX,lastY,board,0,+2,dev)==side && bd(M,N,lastX,lastY,board,0,+3,dev)==side)
        if(top[lastY+1]==lastX+1){y=lastY+1;x=lastX;return 5;} else if(top[lastY+1]<lastX+1) warn[lastX+1][lastY+1]=side;//x_oo
    if(lastY<N-2 && bd(M,N,lastX,lastY,board,0,+2,dev)==side && lastY>0 && bd(M,N,lastX,lastY,board,0,-1,dev)==side)
        if(top[lastY+1]==lastX+1){y=lastY+1;x=lastX;return 5;} else if(top[lastY+1]<lastX+1) warn[lastX+1][lastY+1]=side;//ox_o
    if(lastY<N-1 && bd(M,N,lastX,lastY,board,0,+1,dev)==side && lastY>0 && bd(M,N,lastX,lastY,board,0,-1,dev)==side)//_oxo_
    {
        if(lastY>1)
        {
            if(top[lastY-2]==lastX+1)
            {
                if(lastY<N-2 && top[lastY+2]==lastX+1)return -1;else {y=lastY-2;x=lastX;return 5;}
            }
            else if(top[lastY-2]<lastX+1)
            {
                warn[lastX+1][lastY-2]=side;
                if(lastY<N-2 && top[lastY+2]<lastX+1) warn[lastX+1][lastY+2]=side;
            }
        }
        if(lastY<N-2)
        {
            if(top[lastY+2]==lastX+1){y=lastY+2;x=lastX;return 5;}
            if(top[lastY+2]<lastX+1) warn[lastX+1][lastY+2]=side;
        }
    }
    if(lastY>1 && bd(M,N,lastX,lastY,board,0,-1,dev)==side && bd(M,N,lastX,lastY,board,0,-2,dev)==side)//_oox_
    {
        if(lastY>2)
        {
            if(top[lastY-3]==lastX+1)
            {
                if(lastY<N-1 && top[lastY+1]==lastX+1)return -2;else {y=lastY-3;x=lastX;return 5;}
            }
            else if(top[lastY-3]<lastX+1)
            {
                warn[lastX+1][lastY-3]=side;
                if(lastY<N-1 && top[lastY+1]<lastX+1) warn[lastX+1][lastY+1]=side;
            }
        }
        if(lastY<N-1)
        {
            if(top[lastY+1]==lastX+1){y=lastY+1;x=lastX;return 5;}
            if(top[lastY+1]<lastX+1) warn[lastX+1][lastY+1]=side;
        }
    }
    if(lastY<N-1 && bd(M,N,lastX,lastY,board,0,+1,dev)==side && lastY>1 && bd(M,N,lastX,lastY,board,0,-2,dev)==side)
        if(top[lastY-1]==lastX+1){y=lastY-1;x=lastX;return 5;} else if(top[lastY-1]<lastX+1) warn[lastX+1][lastY-1]=side;//o_xo
    if(lastY>2 && bd(M,N,lastX,lastY,board,0,-3,dev)==side && bd(M,N,lastX,lastY,board,0,-2,dev)==side)
        if(top[lastY-1]==lastX+1){y=lastY-1;x=lastX;return 5;} else if(top[lastY-1]<lastX+1) warn[lastX+1][lastY-1]=side;//oo_x
    if(lastY>2 && bd(M,N,lastX,lastY,board,0,-3,dev)==side && bd(M,N,lastX,lastY,board,0,-1,dev)==side)
        if(top[lastY-2]==lastX+1){y=lastY-2;x=lastX;return 5;} else if(top[lastY-2]<lastX+1) warn[lastX+1][lastY-2]=side;//o_ox
        //重新触发 
    if(lastX>0)
    {
        if(lastY<M-3 && bd(M,N,lastX,lastY,board,-1,+1,dev)==side && bd(M,N,lastX,lastY,board,-1,+2,dev)==side && bd(M,N,lastX,lastY,board,-1,+3,dev)==side){y=lastY;x=lastX-1;return 8;}//=ooo
        if(lastY<M-2 && bd(M,N,lastX,lastY,board,-1,+1,dev)==side && bd(M,N,lastX,lastY,board,-1,+2,dev)==side && lastY>=1  && bd(M,N,lastX,lastY,board,-1,-1,dev)==side){y=lastY;x=lastX-1;return 8;}//o=oo
        if(lastY<M-1 && bd(M,N,lastX,lastY,board,-1,+1,dev)==side && lastY>=2 && bd(M,N,lastX,lastY,board,-1,-2,dev)==side  && bd(M,N,lastX,lastY,board,-1,-1,dev)==side){y=lastY;x=lastX-1;return 8;}//oo=o
        if(lastY>=3 && bd(M,N,lastX,lastY,board,-1,-1,dev)==side && bd(M,N,lastX,lastY,board,-1,-2,dev)==side && bd(M,N,lastX,lastY,board,-1,-3,dev)==side){y=lastY;x=lastX-1;return 8;}//=ooo
    }

    


    
//攻击性>两个点
//两个点
    value=0;
    if(lastY<N-2 && bd(M,N,lastX,lastY,board,0,+1,dev)==side && lastY>0 && top[lastY-1]==lastX+1 && top[lastY+2]==lastX+1)
    {
        if(lastY>=2 && top[lastY-2]==lastX+1)
        {
            if(lastY<N-3 && top[lastY+3]==lastX+1)
            {
                if(walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY-1,value,side,ans)==0 &&
                walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY+2,value,side,ans)==0)return -3;else return 3;
            }
            else
            {
                if(walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY-1,value,side,ans)==0 &&
                walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY+2,value,side,ans)==0 &&
                walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY-2,value,side,ans)==0)return -4;else return 3;
            }
        }
        else if(lastY<N-3 && top[lastY+3]==lastX+1)
        {
            if(walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY-1,value,side,ans)==0 &&
            walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY+2,value,side,ans)==0 &&
            walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY+3,value,side,ans)==0)return -5;else return 3;
        }
    }

    if(lastY<N-1 && lastY>1 && bd(M,N,lastX,lastY,board,0,-1,dev)==side && top[lastY+1]==lastX+1 && top[lastY-2]==lastX+1)
    {
        if(lastY<N-2 && top[lastY+2]==lastX+1)
        {
            if(lastY>2 && top[lastY-3]==lastX+1)
            {
                walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY-2,value,side,ans);
                walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY+1,value,side,ans);
                return 3;
            }
            else
            {
                walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY-2,value,side,ans);
                walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY+1,value,side,ans);
                walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY+2,value,side,ans);
                return 3;
            }
        }
        else if(lastY>2 && top[lastY-3]==lastX+1)
        {
            walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY-3,value,side,ans);
            walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY-2,value,side,ans);
            walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY+1,value,side,ans);
            return 3;
        }
    }
    if(lastY<N-1 && lastY>=3 && bd(M,N,lastX,lastY,board,0,-2,dev)==side && top[lastY-1]==lastX+1 && top[lastY-3]==lastX+1&& top[lastY+1]==lastX+1)//_o_x_
    {
        walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY-3,value,side,ans);
        walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY-1,value,side,ans);
        walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY+1,value,side,ans);
        return 3;
    }
    if(lastY<N-3 && lastY>=1 && bd(M,N,lastX,lastY,board,0,+2,dev)==side && top[lastY+1]==lastX+1 && top[lastY+3]==lastX+1&& top[lastY-1]==lastX+1)//_x_o_
    {
        walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY+3,value,side,ans);
        walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY-1,value,side,ans);
        walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY+1,value,side,ans);
        return 3;
    }
    //random
    return 4;

                




    //左下至右上
    /*
    if(lastY<N-2 && lastX>=2 && bd(M,N,lastX,lastY,board,-1,+1,dev)==side && bd(M,N,lastX,lastY,board,-2,+2,dev)==side)//_xoo_
        if(lastY>0 && top[lastY-1]=lastX+2)
            {if(lastY<N-3 && top[lastY+3]=lastX-2)return 0;else {y=lastY-1;x=lastX+1;return 5;}}
        if(lastY<N-3 && top[lastY+3]=lastX+1){y=lastY+3;x=lastX-3;return 5;}

    if(lastY<N-3 && bd(M,N,lastX,lastY,board,0,+1,dev)==side && bd(M,N,lastX,lastY,board,0,+3,dev)==side && top[lastY+2]=lastX+1){y=lastY+2;x=lastX;return;}//xo_o
    if(lastY<N-3 && bd(M,N,lastX,lastY,board,0,+2,dev)==side && bd(M,N,lastX,lastY,board,0,+3,dev)==side && top[lastY+1]=lastX+1){y=lastY+1;x=lastX;return;}//x_oo
    if(lastY<N-2 && bd(M,N,lastX,lastY,board,0,+2,dev)==side && lastY>0 && bd(M,N,lastX,lastY,board,0,-1,dev)==side && top[lastY+1]=lastX+1){y=lastY+1;x=lastX;return;}//ox_o
    if(lastY<N-1 && bd(M,N,lastX,lastY,board,0,+1,dev)==side && lastY>0 && bd(M,N,lastX,lastY,board,0,-1,dev)==side)//_oxo_
        if(lastY>1 && top[lastY-2]=lastX+1)
            {if(lastY<N-2 && top[lastY+2]=lastX+1)return 0;else {y=lastY-2;x=lastX;return 5;}}
        if(lastY<N-2 && top[lastY+2]=lastX+1){y=lastY+2;x=lastX;return 5;}
    if(lastY>1 && bd(M,N,lastX,lastY,board,0,-1,dev)==side && bd(M,N,lastX,lastY,board,0,-2,dev)==side)//_oox_
        if(lastY>2 && top[lastY-3]=lastX+1)
            {if(lastY<N-1 && top[lastY+1]=lastX+1)return 0;else {y=lastY-3;x=lastX;return 5;}}
        if(lastY<N-1 && top[lastY+1]=lastX+1){y=lastY+1;x=lastX;return 5;}
    if(lastY<N-1 && bd(M,N,lastX,lastY,board,0,+1,dev)==side && lastY>1 && bd(M,N,lastX,lastY,board,0,-2,dev)==side && top[lastY-1]=lastX+1){y=lastY-1;x=lastX;return;}//o_xo
    if(lastY>2 && bd(M,N,lastX,lastY,board,0,-3,dev)==side && bd(M,N,lastX,lastY,board,0,-2,dev)==side && top[lastY-1]=lastX+1){y=lastY-1;x=lastX;return;}//oo_x
    if(lastY>2 && bd(M,N,lastX,lastY,board,0,-3,dev)==side && bd(M,N,lastX,lastY,board,0,-1,dev)==side && top[lastY-2]=lastX+1){y=lastY-2;x=lastX;return;}//o_ox
        */
}
    
/*
 void force(const int M, const int N, const int* top, const int** board, 
	const int lastX, const int lastY, const int noX, const int noY, int x, int y){
{
    if force(M,N,top,board,lastX,lastY,noX,noY,step,x,y,value)return;

    
    //输入step:还剩多少步
	for (int i = N-1; i >= 0; i--) {
		if (top[i] > 0) {
			newx = top[i] - 1;
			newy = i;
            int x,y,value;
			break;
		}

}*/
void putpoint(int* top,int** board,int x,int y,int &lastX, int &lastY,int side)
{
    if(x!=top[y]-1){printf("putpoint error!");getchar();}
    board[top[y]-1][y]=side;
    top[y]--;
    lastX=top[y];lastY=y;
}
void removepoint(int* top,int** board,int x,int y,int &lastX, int &lastY,int side)
{
    if(x!=top[y] || board[x][y]!=side){printf("putpoint error!");getchar();}
    board[top[y]-1][y]=side;
    top[y]--;
    lastX=top[y];lastY=y;
}
void printboard(int M, int N, int** board)
{
    for(int i=0;i<M;++i)
    {
        for(int j=0;j<N;++j)
        {
            if(board[i][j]!=0) printf("%d ",board[i][j]);else printf("  ");
        }
        printf("\n");
    }
}


int getPoint(const int M, const int N, int* top,  int** board, 
	const int lastX, const int lastY, const int noX, const int noY, int &x, int &y, int &value, int side) //0 投降 1 对面有三个 2 竖着的3个 3 对面有两个 4 自由
{

//    board[noX][noY]=-1; !!!!!!!!!!!!!!!!!!!!!!!!!!
    //for debug!
    do { y=rand()%N; } while(top[y]==0);
    x=top[y]-1;
//    putpoint(top,board,0,lastX,lastY,1);
//    putpoint(top,board,1,lastX,lastY,2);
//    putpoint(top,board,2,lastX,lastY,2);
//    putpoint(top,board,4,lastX,lastY,2);
    //bd(M,N,lastX,lastY,board,0,0,dev)=4;
    //printboard(M,N,board);

    int maxans=0, finalx=x, finaly=y, ans=0;

//    for(int dev=-1;dev<=1;++dev)
int dev=0;
        ans=force(M,N,top,board,lastX,lastY,noX,noY,x,y,value,side,dev,ans);
//        if(ans>maxans) {maxans=ans;finalx=x;finaly=y;}


    //mkvalue(M,N,top,board,lastX,lastY,noX,noY,10,x,y,value);
	//clearArray(M, N, board);
	return ans;
}


/*
	getPoint函数返回的Point指针是在本dll模块中声明的，为避免产生堆错误，应在外部调用本dll中的
	函数来释放空间，而不应该在外部直接delete
*/
 void clearPoint(Point* p){
	delete p;
	return;
}

/*
	清除top和board数组
*/
int main()
{
  //  srand((unsigned)time(NULL));
    int M=10,N=10;
//	int x = -1, y = -1;//最终将你的落子点存到x,y中
	int** board = new int*[M];
	for(int i = 0; i < M; i++){
		board[i] = new int[N];
        memset(board[i],0,4*N);
        memset(warn[i],0,4*13);
	}
    int* top=new int[N];
    for(int i=0;i<N;++i){top[i]=M;}

    int lastY=rand()%N;
    int lastX=M-1;
    int noX,noY;
    do { noX=rand()%M; noY=rand()%N;}while (noX==lastX and noY == lastY);
    //putpoint(top,board,lastY,lastX,lastY);
   // board[noX][noY]=-1; 

    int side=2;
    while(1)
    {
        lastX=0;
        lastY=0;
        for(int round=0;round<M*N;++round)
        {
            int x,y,value=0;
            int ans=getPoint( M,  N,  top,  board, lastX, lastY, noX, noY,x,y,value,side);//side为对手的代号
            if(x!=top[y]-1){printf("errtop!");getchar();}
            side=3-side;

            printf("%d %d %d\n",ans,x,y);
            if(board[x][y]!=0) {printf("error\n");getchar();}
            putpoint(top,board,y,lastX,lastY,side);
            board[x][y]+=2;
            printboard(M,N,board);
            board[x][y]-=2;
//            if(side==1 && userWin(x,y,M,N,board)){printf("1win");getchar();break;}
//            if(side==2 && machineWin(x,y,M,N,board)){printf("2win");getchar();break;}
            if(ans<=0)
            {
                printf("%d conceded.",side);
                getchar();
                break;
            }
    //        if(ans!=4 and ans!=2) getchar();
        }
        printf("game end.");
        for(int i = 0; i < M; i++){
            memset(board[i],0,4*N);
            memset(warn[i],0,4*13);
        }
        for(int i=0;i<N;++i){top[i]=M;}
    }
    return 0;
}
