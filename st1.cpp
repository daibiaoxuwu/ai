#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;
/********************************************************
*	Point.h : 棋盘点类                                  *
*	张永锋                                              *
*	zhangyf07@gmail.com                                 *
*	2010.8                                              *
*********************************************************/


class Point{
public:
	int x;
	int y;

	Point(int x, int y){
		this->x = x;
		this->y = y;
	}
};



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

                //walk(M,N,top,board,lastX,lastY,noX,noY,lastX,lastY+1,value,side);
void walk(const int M, const int N, int* top,  int** board, 
	const int lastX, const int lastY, const int noX, const int noY, int &x, int &y, int posx, int posy, int &value, int side) //0 投降 1 对面有三个 3 对面有两个 4 自由
{
    x=posx;y=posy;
    return;
}

int force(const int M, const int N, int* top,  int** board, 
	const int lastX, const int lastY, const int noX, const int noY, int &x, int &y, int &value, int side) //0 投降 1 对面有三个 3 对面有两个 4 自由
{
    //for debug!
    do { y=rand()%N; } while(top[y]==0);
    x=top[y]-1;
    //先看自己能不能连四个

    //再看对手的三个
    //上下
    if(lastX<M-2 && board[lastX+1][lastY]==side && board[lastX+2][lastY]==side && lastX>0){x=lastX-1;y=lastY;return 1;}
    //左右
    if(lastY<N-2 && board[lastX][lastY+1]==side && board[lastX][lastY+2]==side)//_xoo_
    {
        if(lastY>0 && top[lastY-1]==lastX+1)
            {if(lastY<N-3 && top[lastY+3]==lastX+1)return 0;else {y=lastY-1;x=lastX;return 1;}}
        if(lastY<N-3 && top[lastY+3]==lastX+1){y=lastY+3;x=lastX;return 1;}
    }
    if(lastY<N-3 && board[lastX][lastY+1]==side && board[lastX][lastY+3]==side && top[lastY+2]==lastX+1){y=lastY+2;x=lastX;return 1;}//xo_o
    if(lastY<N-3 && board[lastX][lastY+2]==side && board[lastX][lastY+3]==side && top[lastY+1]==lastX+1){y=lastY+1;x=lastX;return 1;}//x_oo
    if(lastY<N-2 && board[lastX][lastY+2]==side && lastY>0 && board[lastX][lastY-1]==side && top[lastY+1]==lastX+1){y=lastY+1;x=lastX;return 1;}//ox_o
    if(lastY<N-1 && board[lastX][lastY+1]==side && lastY>0 && board[lastX][lastY-1]==side)//_oxo_
    {
        if(lastY>1 && top[lastY-2]==lastX+1)
            {if(lastY<N-2 && top[lastY+2]==lastX+1)return 0;else {y=lastY-2;x=lastX;return 1;}}
        if(lastY<N-2 && top[lastY+2]==lastX+1){y=lastY+2;x=lastX;return 1;}
    }
    if(lastY>1 && board[lastX][lastY-1]==side && board[lastX][lastY-2]==side)//_oox_
    {
        if(lastY>2 && top[lastY-3]==lastX+1)
            {if(lastY<N-1 && top[lastY+1]==lastX+1)return 0;else {y=lastY-3;x=lastX;return 1;}}
        if(lastY<N-1 && top[lastY+1]==lastX+1){y=lastY+1;x=lastX;return 1;}
    }
    if(lastY<N-1 && board[lastX][lastY+1]==side && lastY>1 && board[lastX][lastY-2]==side && top[lastY-1]==lastX+1){y=lastY-1;x=lastX;return 1;}//o_xo
    if(lastY>2 && board[lastX][lastY-3]==side && board[lastX][lastY-2]==side && top[lastY-1]==lastX+1){y=lastY-1;x=lastX;return 1;}//oo_x
    if(lastY>2 && board[lastX][lastY-3]==side && board[lastX][lastY-1]==side && top[lastY-2]==lastX+1){y=lastY-2;x=lastX;return 1;}//o_ox
        //重新触发 
    if(lastX>0)
    {
        if(lastY<M-3 && board[lastX-1][lastY+1]==side && board[lastX-1][lastY+2]==side && board[lastX-1][lastY+3]==side){y=lastY;x=lastX;return 1;}//=ooo
        if(lastY<M-2 && board[lastX-1][lastY+1]==side && board[lastX-1][lastY+2]==side && lastY>=1  && board[lastX-1][lastY-1]==side){y=lastY;x=lastX;return 1;}//o=oo
        if(lastY<M-1 && board[lastX-1][lastY+1]==side && lastY>=2 && board[lastX-1][lastY-2]==side  && board[lastX-1][lastY-1]==side){y=lastY;x=lastX;return 1;}//oo=o
        if(lastY>=3 && board[lastX-1][lastY-1]==side && board[lastX-1][lastY-2]==side && board[lastX-1][lastY-3]==side){y=lastY;x=lastX;return 1;}//=ooo
    }

    


    
//攻击性>两个点
//两个点
    value=0;
    if(lastY<N-2 && board[lastX][lastY+1]==side && lastY>0 && top[lastY-1]==lastX+1 && top[lastY+2]==lastX+1)
    {
        if(lastY>=2 && top[lastY-2]==lastX+1)
        {
            if(lastY<N-3 && top[lastY+3]==lastX+1)
            {
                walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY-1,value,side);
                walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY+2,value,side);
                return 3;
            }
            else
            {
                walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY-1,value,side);
                walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY+2,value,side);
                walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY-2,value,side);
                return 3;
            }
        }
        else if(lastY<N-3 && top[lastY+3]==lastX+1)
        {
            walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY-1,value,side);
            walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY+2,value,side);
            walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY+3,value,side);
            return 3;
        }
    }

    if(lastY<N-1 && lastY>1 && board[lastX][lastY-1]==side && top[lastY+1]==lastX+1 && top[lastY-2]==lastX+1)
    {
        if(lastY<N-2 && top[lastY+2]==lastX+1)
        {
            if(lastY>2 && top[lastY-3]==lastX+1)
            {
                walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY-2,value,side);
                walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY+1,value,side);
                return 3;
            }
            else
            {
                walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY-2,value,side);
                walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY+1,value,side);
                walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY+2,value,side);
                return 3;
            }
        }
        else if(lastY>2 && top[lastY-3]==lastX+1)
        {
            walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY-3,value,side);
            walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY-2,value,side);
            walk(M,N,top,board,lastX,lastY,noX,noY,x,y,lastX,lastY+1,value,side);
            return 3;
        }
    }
    //random
    return 4;

                




    //左下至右上
    /*
    if(lastY<N-2 && lastX>=2 && board[lastX-1][lastY+1]==side && board[lastX-2][lastY+2]==side)//_xoo_
        if(lastY>0 && top[lastY-1]=lastX+2)
            {if(lastY<N-3 && top[lastY+3]=lastX-2)return 0;else {y=lastY-1;x=lastX+1;return 1;}}
        if(lastY<N-3 && top[lastY+3]=lastX+1){y=lastY+3;x=lastX-3;return 1;}

    if(lastY<N-3 && board[lastX][lastY+1]==side && board[lastX][lastY+3]==side && top[lastY+2]=lastX+1){y=lastY+2;x=lastX;return;}//xo_o
    if(lastY<N-3 && board[lastX][lastY+2]==side && board[lastX][lastY+3]==side && top[lastY+1]=lastX+1){y=lastY+1;x=lastX;return;}//x_oo
    if(lastY<N-2 && board[lastX][lastY+2]==side && lastY>0 && board[lastX][lastY-1]==side && top[lastY+1]=lastX+1){y=lastY+1;x=lastX;return;}//ox_o
    if(lastY<N-1 && board[lastX][lastY+1]==side && lastY>0 && board[lastX][lastY-1]==side)//_oxo_
        if(lastY>1 && top[lastY-2]=lastX+1)
            {if(lastY<N-2 && top[lastY+2]=lastX+1)return 0;else {y=lastY-2;x=lastX;return 1;}}
        if(lastY<N-2 && top[lastY+2]=lastX+1){y=lastY+2;x=lastX;return 1;}
    if(lastY>1 && board[lastX][lastY-1]==side && board[lastX][lastY-2]==side)//_oox_
        if(lastY>2 && top[lastY-3]=lastX+1)
            {if(lastY<N-1 && top[lastY+1]=lastX+1)return 0;else {y=lastY-3;x=lastX;return 1;}}
        if(lastY<N-1 && top[lastY+1]=lastX+1){y=lastY+1;x=lastX;return 1;}
    if(lastY<N-1 && board[lastX][lastY+1]==side && lastY>1 && board[lastX][lastY-2]==side && top[lastY-1]=lastX+1){y=lastY-1;x=lastX;return;}//o_xo
    if(lastY>2 && board[lastX][lastY-3]==side && board[lastX][lastY-2]==side && top[lastY-1]=lastX+1){y=lastY-1;x=lastX;return;}//oo_x
    if(lastY>2 && board[lastX][lastY-3]==side && board[lastX][lastY-1]==side && top[lastY-2]=lastX+1){y=lastY-2;x=lastX;return;}//o_ox
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
void putpoint(int* top,int** board,int y,int &lastX, int &lastY,int side)
{
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


 Point* getPoint(const int M, const int N,  int* top,  int** board, 
	 int lastX,  int lastY, const int noX, const int noY){

//    board[noX][noY]=-1; !!!!!!!!!!!!!!!!!!!!!!!!!!
    int x=0,y=0,value;
//    putpoint(top,board,0,lastX,lastY,1);
//    putpoint(top,board,1,lastX,lastY,2);
//    putpoint(top,board,2,lastX,lastY,2);
//    putpoint(top,board,4,lastX,lastY,2);
    //board[lastX][lastY]=4;
    //printboard(M,N,board);

    printf("%d\n",force(M,N,top,board,lastX,lastY,noX,noY,x,y,value,2));
    board[x][y]=3;
    printboard(M,N,board);

    //mkvalue(M,N,top,board,lastX,lastY,noX,noY,10,x,y,value);
	//clearArray(M, N, board);
	return new Point(x, y);
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
    int M=10,N=10;
//	int x = -1, y = -1;//最终将你的落子点存到x,y中
	int** board = new int*[M];
	for(int i = 0; i < M; i++){
		board[i] = new int[N];
        memset(board[i],0,sizeof(board[i]));
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
    for(int round=0;round<M*N;++round)
    {
        int x,y,value=0;
        int ans=force( M,  N,  top,  board, lastX, lastY, noX, noY,x,y,value,side);//side为对手的代号
        side=3-side;

        printf("%d %d %d\n",ans,x,y);
        putpoint(top,board,y,lastX,lastY,side);
        board[x][y]+=2;
        printboard(M,N,board);
        board[x][y]-=2;
        if(ans==0)
        {
            printf("%d conceded.",side);
            break;
        }
        getchar();
    }
    return 0;
}
