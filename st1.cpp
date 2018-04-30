#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;
/********************************************************
*	Point.h : ���̵���                                  *
*	������                                              *
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
	���Ժ����ӿ�,�ú������Կ�ƽ̨����,ÿ�δ��뵱ǰ״̬,Ҫ�����������ӵ�,�����ӵ������һ��������Ϸ��������ӵ�,��Ȼ�Կ�ƽ̨��ֱ����Ϊ��ĳ�������
	
	input:
		Ϊ�˷�ֹ�ԶԿ�ƽ̨ά����������ɸ��ģ����д���Ĳ�����Ϊconst����
		M, N : ���̴�С M - ���� N - ���� ����0��ʼ�ƣ� ���Ͻ�Ϊ����ԭ�㣬����x��ǣ�����y���
		top : ��ǰ����ÿһ���ж���ʵ��λ��. e.g. ��i��Ϊ��,��_top[i] == M, ��i������,��_top[i] == 0
		_board : ���̵�һά�����ʾ, Ϊ�˷���ʹ�ã��ڸú����տ�ʼ���������Ѿ�����ת��Ϊ�˶�ά����board
				��ֻ��ֱ��ʹ��board���ɣ����Ͻ�Ϊ����ԭ�㣬�����[0][0]��ʼ��(����[1][1])
				board[x][y]��ʾ��x�С���y�еĵ�(��0��ʼ��)
				board[x][y] == 0/1/2 �ֱ��Ӧ(x,y)�� ������/���û�����/�г������,�������ӵ㴦��ֵҲΪ0
		lastX, lastY : �Է���һ�����ӵ�λ��, ����ܲ���Ҫ�ò�����Ҳ������Ҫ�Ĳ������ǶԷ�һ����
				����λ�ã���ʱ��������Լ��ĳ����м�¼�Է������ಽ������λ�ã�����ȫȡ�������Լ��Ĳ���
		noX, noY : �����ϵĲ������ӵ�(ע:��ʵ���������top�Ѿ����㴦���˲������ӵ㣬Ҳ����˵���ĳһ��
				������ӵ�����ǡ�ǲ������ӵ㣬��ôUI�����еĴ�����Ѿ������е�topֵ�ֽ�����һ�μ�һ������
				��������Ĵ�����Ҳ���Ը�����ʹ��noX��noY��������������ȫ��Ϊtop������ǵ�ǰÿ�еĶ�������,
				��Ȼ�������ʹ��lastX,lastY�������п��ܾ�Ҫͬʱ����noX��noY��)
		���ϲ���ʵ���ϰ����˵�ǰ״̬(M N _top _board)�Լ���ʷ��Ϣ(lastX lastY),��Ҫ���ľ�������Щ��Ϣ�¸������������ǵ����ӵ�
	output:
		������ӵ�Point
*/

                //walk(M,N,top,board,lastX,lastY,noX,noY,lastX,lastY+1,value,side);
void walk(const int M, const int N, int* top,  int** board, 
	const int lastX, const int lastY, const int noX, const int noY, int &x, int &y, int posx, int posy, int &value, int side) //0 Ͷ�� 1 ���������� 3 ���������� 4 ����
{
    x=posx;y=posy;
    return;
}

int force(const int M, const int N, int* top,  int** board, 
	const int lastX, const int lastY, const int noX, const int noY, int &x, int &y, int &value, int side) //0 Ͷ�� 1 ���������� 3 ���������� 4 ����
{
    //for debug!
    do { y=rand()%N; } while(top[y]==0);
    x=top[y]-1;
    //�ȿ��Լ��ܲ������ĸ�

    //�ٿ����ֵ�����
    //����
    if(lastX<M-2 && board[lastX+1][lastY]==side && board[lastX+2][lastY]==side && lastX>0){x=lastX-1;y=lastY;return 1;}
    //����
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
        //���´��� 
    if(lastX>0)
    {
        if(lastY<M-3 && board[lastX-1][lastY+1]==side && board[lastX-1][lastY+2]==side && board[lastX-1][lastY+3]==side){y=lastY;x=lastX;return 1;}//=ooo
        if(lastY<M-2 && board[lastX-1][lastY+1]==side && board[lastX-1][lastY+2]==side && lastY>=1  && board[lastX-1][lastY-1]==side){y=lastY;x=lastX;return 1;}//o=oo
        if(lastY<M-1 && board[lastX-1][lastY+1]==side && lastY>=2 && board[lastX-1][lastY-2]==side  && board[lastX-1][lastY-1]==side){y=lastY;x=lastX;return 1;}//oo=o
        if(lastY>=3 && board[lastX-1][lastY-1]==side && board[lastX-1][lastY-2]==side && board[lastX-1][lastY-3]==side){y=lastY;x=lastX;return 1;}//=ooo
    }

    


    
//������>������
//������
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

                




    //����������
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

    
    //����step:��ʣ���ٲ�
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
	getPoint�������ص�Pointָ�����ڱ�dllģ���������ģ�Ϊ��������Ѵ���Ӧ���ⲿ���ñ�dll�е�
	�������ͷſռ䣬����Ӧ�����ⲿֱ��delete
*/
 void clearPoint(Point* p){
	delete p;
	return;
}

/*
	���top��board����
*/
int main()
{
    int M=10,N=10;
//	int x = -1, y = -1;//���ս�������ӵ�浽x,y��
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
        int ans=force( M,  N,  top,  board, lastX, lastY, noX, noY,x,y,value,side);//sideΪ���ֵĴ���
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
