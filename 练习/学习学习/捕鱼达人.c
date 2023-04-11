#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

#define a 97    //左方向
#define d 100   //右方向
#define p 112   //暂停并查看规则
#define LEFT 75         //左方向  
#define RIGHT 77        //右方向
#define SPACE 32        //发射钩子
#define ESC 27          //退出游戏
#define NOPRINT 0          //不打印
#define L_SMALL_FISH 1      //标记为从左边游过来的小鱼
#define R_SMALL_FISH 2      //标记为从右边游过来的小鱼
#define L_BIG_FISH 3        //标记为从左边游过来的大鱼
#define R_BIG_FISH 4        //标记为从右边游过来的大鱼
#define BOMB 9      //标记为炸弹
#define NOTHING 10   //无标记
#define LAUNCHER 11      //标记为发射台
#define HOOK 12      //标记为鱼钩
#define ROPE 13     //标记为绳子
#define WALL 14		//标记为墙
#define MAX_NAME_LEN 20     //用户名最长长度

int x=70,y=44,i,j,score=0,blood=3;//声明全局变量
struct Ap {         //鱼及炸弹的位置
    int Col;
    int Row;
};
struct Ap prop[20];     
int object[150][50]={NOPRINT}, temp[150][50]={NOPRINT};    //值表示对应坐标的物体种类,temp作为临时数组存储上一帧画面的状态

typedef struct _rank{
    char name[MAX_NAME_LEN];
    int score;
    struct _rank *next;
}Rank;      //储存排名

//用户信息储存
typedef struct inf{
    char name[20];
    char account[20];
    char password[20];
    int score;
    struct inf *next;
}info;

info *infoHead;
Rank *RankHead;

//游戏主体
void Game();
//输出游戏界面
void output();
//血量、分数初始化
void System_init();
//初始化道具
void Init_Props();
//打印墙
void Wall();
//初始化发射台
void Initial_launcher(int i, int j);
//实现发射台的左右移动
void Launcher_move(char c);
//删去发射台每行最后一个方块
void Cut_tail(char c);
//在发射台移动方向前面，每行新增一个方块
void Add_head(char c);
//更新画面
void Update();
//随机决定道具出现的位置
void AppearPosition(int i);
//大鱼的运动方式
void BigFishMoving(int i);
//小鱼的运动方式
void SmallFishMoving(int i);
//炸弹的运动方式
void BombMoving(int i);
//所有非操纵道具的随机点重复性判定
void PropRandom();
//道具的运动
void Pmove();
//判断鱼和炸弹是否碰到墙
_Bool PHW(int i);
//鱼和炸弹碰到墙之后消失
void Wallvanish(int i);
//生成新的鱼或炸弹
int refresh(int x);
//发射鱼钩
void Hook_shot(int m, int n);
//判断鱼钩碰到东西，鱼钩返回（并加分或扣血）
int Judge_ahead(int m, int n);
//血量系统
void Blood_System(int n);
//计分板
void Scoreboard(int n);
//鱼或炸弹的消失
void vanish(int m,int n);
//收回鱼钩
void Hook_return(int m, int n);
//判断鱼钩已收回
int Judge_back(int n);
//暂停游戏并进入规则界面
void Rule_check();
//游戏结束界面
void Gameover();
//隐藏光标
void Hide_cursor();
//光标跳转
void Goto_xy(int x, int y);
//设置颜色
void Color(int c);
//读取文件写入链表
void Readrank(Rank *pRank);
//添加链表节点
Rank* add(Rank *pRank, char name[], int score);
//读取文件到动态数组并打印排行榜
void printrank();
//检测模块
void detect(info zh[], char l[]);
//注册模块
int _register(info zh[], int m);
//登录模块
void login(info zh[], int m);
//菜单
void menu();
//写入文件
void Writerank(char name[], int score);

int main()
{ 
    system("title 大鱼小鱼抓抓抓");         //命名控制台窗口
    system("mode con cols=150 lines=50");   //更改控制控制台窗口大小
    Hide_cursor();      //隐藏光标
    // infoHead = (info*)malloc(sizeof(info));
    RankHead = (Rank*)malloc(sizeof(Rank));
    // ReadAccount(infoHead);      //读取账号密码写入链表
    
    int m = 0;
    info zh[MAX_NAME_LEN];
    int opt;
    while(1){
        menu();
        printf("Please choose a service:");
        scanf("%d", &opt);
        switch(opt){
            case 1:
                _register(zh, m);
                m++;
                printf("%d\n\n", m);
                break;
            case 2:
                login(zh, m);
                system("cls");
                Game();
                break;

            case 3:
                printf("Thanks for using!\n");
                exit(0);

            default:
                printf("There isn't such a option!\n");
                break;
        }
    }            
    return 0;
}

//游戏主体
void Game()
{
    System_init();      //血量、分数初始化
    Initial_launcher(x+5,y);    //初始化发射台
    Init_Props();   //初始化鱼和炸弹
    output();       //初始化画面
    Wall();         //打印墙
    char c;         //声明char型的c，其值为玩家输入的键值
    while(1){
        for(i=0;i<150;i++){         
            for(j=0;j<50;j++){
                temp[i][j]=object[i][j];
            }
        }
        int t=5000;
        while(--t){
        	if(kbhit()!=0){
        		c=getch();        //读取用户输入的键
                switch(c)
                {
                case LEFT:case a:      //向左移动
                    if(x>2){
                        Launcher_move(c);
                        x-=2;
                        }
                    break;
                case RIGHT:case d:     //向右移动
                    if(x<135){
                        Launcher_move(c);
                        x+=2;
                        }
                    break;
                case SPACE:     //发射鱼钩
                    Hook_shot(x,y);
                    break;
                case p:
                    Rule_check();       //暂停并进入规则界面
                    getch();        //用户敲击键盘后返回主函数
                    main();
                case ESC:   
            		Gameover();     //暂停并进入结束界面进行选择
            		main();
                }
			}
		}
		Pmove();            //鱼和炸弹的运动
        Update();           //更新画面
    }
}

//血量和分数初始化
void System_init()
{
    Goto_xy(2,48);//血量初始
    Color(6);
    printf("剩余血量为：");
    Goto_xy(14,48);//(14,48)(17,48)(20,48)(23,48)(26,48)心的位置
    Color(4);
    printf("心 心 心");

    Goto_xy(40,48);//计分初始
    Color(6);
    printf("当前得分：0");
}

//初始化发射台
void Initial_launcher(int i, int j)
{
    Color(3);       //设置发射台颜色为湖蓝色
    object[i][j-1]=HOOK;
    object[i-2][j]=LAUNCHER;object[i][j]=LAUNCHER;object[i+2][j]=LAUNCHER;
    object[i-5][j+1]=LAUNCHER;object[i-3][j+1]=LAUNCHER;object[i-1][j+1]=LAUNCHER;
    object[i+1][j+1]=LAUNCHER;object[i+3][j+1]=LAUNCHER;object[i+5][j+1]=LAUNCHER;
    object[i][j+2]=LAUNCHER;
    object[i-2][j+3]=LAUNCHER;object[i][j+3]=LAUNCHER;object[i+2][j+3]=LAUNCHER;
}

//初始化道具（鱼和炸弹）
void Init_Props() {
	int x,y,z;
	srand((unsigned)time(NULL));
	int rnd[20];
	for(j=0;j<20;j++){
	 	rnd[j]=rand()%100;
	}
	for(i<0;i<20;i++){
        if (i < 2) {
                prop[i].Col = 2+rnd[i];
                prop[i].Row=i+33;
        }
        else if (i < 4) {
                prop[i].Col = 145-rnd[i];
                prop[i].Row=i+36;
        }
        else if (i < 7) {
                prop[i].Col = 2+rnd[i];
                prop[i].Row=3*i-10;
        }
        else if (i < 10) {
                prop[i].Col = 145-rnd[i];
                prop[i].Row=3*i-10;
		}
		else if(i<20){
				prop[i].Col = 10+rnd[i];
				prop[i].Row=i+10;
			}
	    x=prop[i].Col;
	    y=prop[i].Row;
        if (i < 2) {
			for(int k=0;k<11;k++){
				object[x+k][y] = L_BIG_FISH;
			}
		}
        else if (i < 4) {
        	for(int k=0;k<11;k++)
                object[x-k][y] = R_BIG_FISH;
        }
        else if (i < 7) {
        	for(int k=0;k<11;k++)
                object[x+k][y] = L_SMALL_FISH;
        }
        else if (i < 10) {
			for(int k=0;k<11;k++)
                object[x-k][y] = R_SMALL_FISH;
		}
        else {
		        object[x][y] = BOMB;
	    }
    }
}

//输出游戏界面
void output()
{
	for(i=0;i<150;i++){
		for(j=0;j<50;j++){
			if(object[i][j]==LAUNCHER){
                Color(3);
                Goto_xy(i,j);
                printf("■");
                Color(6);
            }else if(object[i][j]==HOOK){
                Color(3);
                Goto_xy(i,j);
                printf("▲");
                Color(6);
            }
			else if(object[i][j]==L_SMALL_FISH&&(object[i-1][j]==NOPRINT|| object[i - 1][j] == NOTHING)){
                Goto_xy(i,j);Color(3);printf("≡≡≡(◎:)");
            }else if(object[i][j]==R_SMALL_FISH&& (object[i - 1][j] == NOPRINT || object[i - 1][j] == NOTHING)){
                Goto_xy(i,j);Color(3);printf("(:◎)≡≡≡");
            }else if(object[i][j]==L_BIG_FISH&& (object[i - 1][j] == NOPRINT || object[i - 1][j] == NOTHING)){
                Goto_xy(i,j);Color(3);printf("≥(▓▓▓▓▓(O>");
            }else if(object[i][j]==R_BIG_FISH&& (object[i - 1][j] == NOPRINT || object[i - 1][j] == NOTHING)){
                Goto_xy(i,j);Color(3);printf("<O)▓▓▓▓▓)≦");
            }else if(object[i][j]==BOMB&&(object[i-1][j]==NOTHING||object[i-1][j]==NOPRINT)){
                Goto_xy(i,j);Color(4);printf("■");
            }
		}
	}
}

//打印墙
void Wall()
{
    Color(6);       //设置墙的颜色为黄色
    for(i=0;i<=148;i++){
	Goto_xy(i,49);
    printf("■");
	}
    for(i=0;i<=148;i++){
	Goto_xy(i,0);
    printf("■");
	}
	for(i=1;i<49;i++){
		Goto_xy(0,i);
        printf("■");	
	}
	for(i=1;i<49;i++){
		Goto_xy(148,i);
        printf("■");	
	}
}

//实现发射台的左右移动
void Launcher_move(char c)
{
    Cut_tail(c);        //删去发射台每行最后一个方块
    Add_head(c);        //在发射台移动方向前面，每行新增一个方块
}

//删去发射台每行最后一个方块
void Cut_tail(char c)

    {
    if(c==RIGHT||c==d){       //如果向右移动，覆盖左侧方块

        object[x+5][y-1]=NOTHING;
        object[x+3][y]=NOTHING;
        object[x][y+1]=NOTHING;
        object[x+5][y+2]=NOTHING;
        object[x+3][y+3]=NOTHING;
    }else{          //如果向左移动，覆盖右侧方块

        object[x+5][y-1]=NOTHING;
        object[x+7][y]=NOTHING;
        object[x+10][y+1]=NOTHING;
        object[x+5][y+2]=NOTHING;
        object[x+7][y+3]=NOTHING;
    }
}

//在发射台移动方向前面，每行新增一个方块
void Add_head(char c)
{
    if(c==RIGHT||c==d){       //如果向右移动，在右侧新增
        object[x+7][y-1]=HOOK;
        object[x+9][y]=LAUNCHER;
        object[x+12][y+1]=LAUNCHER;
        object[x+7][y+2]=LAUNCHER;
        object[x+9][y+3]=LAUNCHER;
    }else{      //如果向左移动，在左侧新增
        object[x+3][y-1]=HOOK;
        object[x+1][y]=LAUNCHER;
        object[x-2][y+1]=LAUNCHER;
        object[x+3][y+2]=LAUNCHER;
        object[x+1][y+3]=LAUNCHER;
    }
}

//发射鱼钩
void Hook_shot(int m,int n)
{
    while (1)
	{
        int t=5000;
        while(--t){
            if(kbhit()!=0){}
        }
		if(Judge_ahead(m+5,n-1)){       //判断鱼钩碰到东西，鱼钩返回（并加分或扣血）
            Update();
            Hook_return(m,n);
            break;
        }   
        if(kbhit()){        
            if(getch()==SPACE){     //如果玩家敲击空格键，鱼钩返回
                Hook_return(m,n);
                break;
            }
        }
        for(i=0;i<150;i++){         //存储上一帧画面物体状态
            for(j=0;j<50;j++){
                temp[i][j]=object[i][j];
            }
        }
        for(i=y-1;i>=n-1;i--){
            object[m+5][i]=ROPE;
        }
        object[m+6][n-1]=NOTHING;
        object[m+5][n-2]=HOOK;
        n--;
		Pmove();
        Update();       //每一轮循环更新画面
	}
}

//判断鱼钩碰到东西，鱼钩返回（并加分或扣血）
int Judge_ahead(int m ,int n)
{
    int t=1;        //若t=1，鱼钩返回
    if (n == 1) {
        //碰到墙
    }else if(object[m][n-1]!=NOTHING&&object[m][n-1]!=NOPRINT){
        int o=object[m][n-1];
        if(o==L_BIG_FISH||o==R_BIG_FISH){
            score+=10;
        }else if(o==L_SMALL_FISH||o==R_SMALL_FISH){
            score+=50;
        }else if(o==BOMB){
            blood--;
        }
        for(i=0;i<150;i++){
            if(object[i][n-1]!=NOTHING&&object[i][n-1]!=NOPRINT){
                object[i][n-1]=NOTHING;
            }
        }
        refresh(n-1);
        
    	Blood_System(blood);//血量系统
        Scoreboard(score);//得分系统
    }else{
        t=0;    //什么也没碰到
    }
    return t;       //返回值为t
}

//收回鱼钩
void Hook_return(int m,int n)
{
    while (1)
	{
        for(i=0;i<150;i++){         //存储上一帧画面中物体状态
            for(j=0;j<50;j++){
                temp[i][j]=object[i][j];
            }
        }
        while(kbhit()){         //清空缓冲区，防止出现鱼钩收回瞬间发射台瞬移等情况
            getch();
        }
        //鱼钩返回时，将右上一格改为NOPRINT，与NOTHING区分开，防止下一次发射鱼钩无法对绳子右侧鱼钩进行覆盖
        object[m+6][n-1]=NOPRINT;       
        object[m+5][n-1]=NOTHING;
        object[m+5][n]=HOOK;
        for(i=n+1;i<=y-1;i++){
            object[m+5][i]=ROPE;
        }
        n++;
        Pmove();
        Update();           //每一次循环更新画面
        int t=5000;
        while(--t){
            if(kbhit()!=0){}
        }
		if(Judge_back(n)){      //判断鱼钩已收回（回到原位）
            object[m+6][n-1]=NOPRINT;   //将鱼钩右侧一格状态修改为NOPRINT，理由同上
            break;
        }
    }
}

//判断鱼钩已收回
int Judge_back(int n)
{
    int t=0;
    if(n==44){      //鱼钩已回到原处（用纵坐标判断）
        t=1;
    }
    return t;
}

//更新画面
void Update()
{
    for(i=0;i<150;i++){
        for(j=0;j<50;j++){
            if(object[i][j]==L_SMALL_FISH&&(object[i-1][j]==NOTHING||object[i-1][j]==NOPRINT)){
                    Goto_xy(i,j);Color(3);printf("≡≡≡(◎:)");//11个格子
                }else if(object[i][j]==R_SMALL_FISH&&(object[i-1][j]==NOTHING||object[i-1][j]==NOPRINT)){
                    Goto_xy(i,j);Color(3);printf("(:◎)≡≡≡");
                }else if(object[i][j]==L_BIG_FISH&&(object[i-1][j]==NOTHING||object[i-1][j]==NOPRINT)){
                    Goto_xy(i,j);Color(3);printf("≥(▓▓▓▓▓(0>");//11个格子
                }else if(object[i][j]==R_BIG_FISH&&(object[i-1][j]==NOTHING||object[i-1][j]==NOPRINT)){
                    Goto_xy(i,j);Color(3);printf("<0)▓▓▓▓▓)≦");
                }else if(object[i][j]==BOMB&&(object[i-1][j]==NOTHING||object[i-1][j]==NOPRINT)){
                    Goto_xy(i,j);Color(4);printf("■");
                }else if(object[i][j]==ROPE){
                    Color(3);
                    Goto_xy(i,j);
                    printf("║");
                    Color(6);
                }else if(object[i][j]==NOTHING){
                    Goto_xy(i,j);printf("  ");      //用空格覆盖原有的物体
                }
            if(temp[i][j]!=object[i][j]){       //如果该坐标处物体状态与上一帧画面中物体状态不同，再打印；
                if(object[i][j]==LAUNCHER){
                    Color(3);
                    Goto_xy(i,j);
                    printf("■");
                    Color(6);
                }else if(object[i][j]==HOOK){
                    Color(3);
                    Goto_xy(i,j);
                    printf("▲");
                    Color(6);
                }
            }
        }
    }
    for(i=0;i<150;i++){             //每轮打印结束，将NOTHING全部换为NOPRINT，减少打印次数
        for(j=0;j<50;j++){
            if(object[i][j]==NOTHING){
                object[i][j]=NOPRINT;
            }
        }
    }
}

//鱼和炸弹的运动
void Pmove() 
{
    for(i=0;i<20;i++){
		if(!PHW(i)){
            if (i < 4)
            BigFishMoving(i);
        else if (i < 10) 
			SmallFishMoving(i);
		else if(i<20)
			BombMoving(i);
        }else{
		    Wallvanish(i);
            AppearPosition(i);
        }
	}
}

//大鱼的运动
void BigFishMoving(int i) 
{
    //当是左边的大鱼时
	if (i<2) {
	        object[prop[i].Col] [prop[i].Row] = NOTHING;
	        prop[i].Col++;
            for(int k=0;k<11;k++){
				object[prop[i].Col+k][prop[i].Row] = L_BIG_FISH;
			}
	}
	//当是右边的大鱼时
	else{
	        object[prop[i].Col     ][prop[i].Row] = NOTHING;
	        prop[i].Col --;
            for(int k=0;k<11;k++)
                object[prop[i].Col-k][prop[i].Row] = R_BIG_FISH;
	}
}

//小鱼的运动
void SmallFishMoving(int i) 
{
	//当是左边的小鱼时
	if(i<7){
	        object[prop[i].Col     ][prop[i].Row] = NOTHING;
	        prop[i].Col ++;
            for(int k=0;k<11;k++)
                object[prop[i].Col+k][prop[i].Row] = L_SMALL_FISH;
	}
	//当是右边的小鱼时
	else{
	        object[prop[i].Col	   ][prop[i].Row] = NOTHING;
	        prop[i].Col--;
            for(int k=0;k<11;k++)
                object[prop[i].Col-k][prop[i].Row] = R_SMALL_FISH;
	}
}

//炸弹的运动
void BombMoving(int i) 
{
    object[prop[i].Col ][prop[i].Row] = NOTHING;
    object[prop[i].Col + 2][prop[i].Row] = BOMB;
    prop[i].Col ++;
}

//判断鱼或炸弹是否碰到墙
_Bool PHW(int i){
	int hit=0;
	if(i<2){
		if(prop[i].Col==136) hit =1;
	}
	else if(i<4){
		if (prop[i].Col==13) hit =1;
	}
	else if(i<7){
		if (prop[i].Col==136) hit =1;
	}
	else if(i<10){
		if (prop[i].Col==13) hit =1;
	}
	else if(i<20){
		if (prop[i].Col==145) hit =1;
	}
	return hit;
}

//墙边的鱼和炸弹消失
void Wallvanish(int i)
{
	if(i<2||(i>=4&&i<7)){
		for(j=0;j<11;j++){
	    	object[prop[i].Col+j][prop[i].Row]=NOTHING;
		}
	}else if(i<10){
		    for(j=0;j<11;j++){
				object[prop[i].Col-j][prop[i].Row]=NOTHING;
			}                  
		}else{
		for(j=0;j<2;j++){
				object[prop[i].Col+j][prop[i].Row]=NOTHING;
			}
		}
}

//生成新的鱼或炸弹
int refresh(int x){
	int n;
	if(x==33||x==34){
        n=x-33;
    }else if(x==38||x==39){
        n=x-36;
    }else if(x>=20&&x<=29){
        n=x-10;
    }else if(x>=2&&x<=17){
        n=(x+10)/3;
    }
	AppearPosition(n);
}

//随机确定一个两边的点为出生点，并写入Ap数组中
void AppearPosition(int i)
{
	if (i < 2) {
                prop[i].Col = 2;
                prop[i].Row=i+33;
                for(int k=0;k<11;k++){
				object[prop[i].Col+k][prop[i].Row] = L_BIG_FISH;
			}
        }
        else if (i < 4) {
                prop[i].Col = 145;
                prop[i].Row=i+36;
                for(int k=0;k<11;k++)
                object[prop[i].Col-k][prop[i].Row] = R_BIG_FISH;
        }
        else if (i < 7) {
                prop[i].Col = 2;
                prop[i].Row=3*i-10;
                for(int k=0;k<11;k++)
                object[prop[i].Col+k][prop[i].Row] = L_SMALL_FISH;
        }
        else if (i < 10) {
                prop[i].Col = 145;
                prop[i].Row=3*i-10;
                for(int k=0;k<11;k++)
                object[prop[i].Col-k][prop[i].Row] = R_SMALL_FISH;
		}
		else if(i<20){
				prop[i].Col = 2;
				prop[i].Row=i+10;
                object[prop[i].Col][prop[i].Row] = BOMB;
		}
}

//血量显示及游戏终止
void Blood_System(int n)
{
    int last=3;//用于判断是否需要覆盖
    int place=20;//标记覆盖位置x
    if(n!=3){
    while(last!=n){
                Goto_xy(place,48);
                printf("  ");
                last-=1;place-=3;//last=blood+1或=blood
    }
    }
     if(n==0)  Gameover();
}

//计分板
void Scoreboard(int n)
{
    int last=0;//储存上一时刻的得分
    Color(6);
    while(last!=n){
        Goto_xy(50,48);
        printf("%d",n);
        last=n;
    }
}

//暂停游戏并进入规则界面
void Rule_check()
{
    system("cls");      //清屏
    Color(7);       //设置颜色为白色
    Goto_xy(70,10);printf("游戏已暂停！");
    Goto_xy(66,12);printf("请仔细阅读游戏规则！");
    Goto_xy(50, 14); printf("1、玩家可以通过"); Color(6); printf("方向键或者a、d键"); Color(7); printf("控制发射台的左右移动；");
    Goto_xy(50,15);printf("2、按");Color(6);printf("空格键");Color(7);printf("直线发射鱼钩，鱼钩在前、左、右碰到物体即算成功钩到；");
    Goto_xy(50,16);printf("3、在鱼钩射出且尚未收回时，玩家无法控制发射台的左右移动；");
    Goto_xy(50,17);printf("4、鱼钩钩到");Color(6);printf("小鱼加2分");Color(7);printf("，钩到");Color(6);printf("大鱼加1分");Color(7);printf("；");
    Goto_xy(50,18);printf("5、每个玩家初始血量为");Color(6);printf("5");Color(7);printf("，鱼钩钩到炸弹时");Color(6);printf("减一滴血");
    Color(7);printf("，血量为");Color(6);printf("0");Color(7);printf("时游戏结束；");
    Goto_xy(50,19);printf("6、按");Color(6);printf("p");Color(7);printf("暂停游戏并查看规则；");
    Goto_xy(50,20);printf("7、按");Color(6);printf("esc键");Color(7);printf("进入结束页面，进行选择。");
    Goto_xy(50,25);printf("按任意键回到游戏界面，祝您玩得愉快！");
}

//结束界面
void Gameover()
{
    system("cls") ;
    Goto_xy(63,24); 
    Color(7);
    printf("Would you like another try(Y/N)?:");//结束界面选择，重新或结束游戏
  	while(1){
    	int c=getch();
	 	switch(c){
    	case 'y':
    	case 'Y':system("cls") ; //返回主函数，重新游戏
           blood=5;
           for(i=1;i<148;i++)
                    for(j=1;j<41;j++)
                    object[i][j]=NOTHING;
                    Game();
					break;
    	case 'n':
    	case 'N':system("cls");     //进入排行榜页面
            char name[MAX_NAME_LEN];
            printf("Please enter your name:");  scanf("%s", name);
            Writerank(name, score);
            printrank();
            break;
		}
    }
}

//隐藏光标 
void Hide_cursor()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cur;
	GetConsoleCursorInfo(hOut, &cur);
	cur.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &cur);
}

//光标跳转
void Goto_xy(int x, int y)
{   
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x,y};
    SetConsoleCursorPosition(hOut, pos);
}

//设置颜色
void Color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); 
}

//读取账号密码写入链表
void ReadAccount(info *pRank)
{
    FILE *fr = fopen("user.txt","r");
    char _name[MAX_NAME_LEN];
    char _password[MAX_NAME_LEN];
    info *tmp;
    info *tail = pRank;
    if(fr == NULL){
        printf("File doesn't exist!\n");
        exit(0);
    }
    while(fscanf(fr, "%s %d", _name, &score) == 2){
        tmp = (info*)malloc(sizeof(info));
        strcpy(tmp->name, _name);
        strcpy(tmp->password, _password);

        tail->next = tmp;
        tail = tmp;
    }
    tail->next = NULL;
    fclose(fr);
}

//读取分数写入链表
void Readrank(Rank *pRank)
{
    FILE *fr = fopen("Rank.txt","r");
    char _name[20];
    int score;
    Rank *tmp;
    Rank *tail = pRank;
    if(fr == NULL){
        printf("File doesn't exist!\n");
        exit(0);
    }
    while(fscanf(fr, "%s %d", _name, &score) == 2){
        tmp = (Rank*)malloc(sizeof(Rank));
        strcpy(tmp->name, _name);
        tmp->score = score;

        tail->next = tmp;
        tail = tmp;
    }
    tail->next = NULL;
    fclose(fr);
}

//写入文件
void Writerank(char name[], int score)
{
    FILE *fw = fopen("Rank.txt", "a");
    fprintf(fw, "%s %d\n", name, score);
    fclose(fw);
}

//菜单
void menu(void)
{
    printf("---------------------------------------\n");
    printf("        1  --- Register\n");
    printf("        2  --- Login\n");
    printf("        3  --- Exit\n");
    printf("---------------------------------------\n");
}

//添加链表节点
Rank* add(Rank *pRank, char name[], int score)
{
    Rank *tmp = (Rank*)malloc(sizeof(Rank));
    tmp->score = score;
    strcpy(tmp->name, name);
    tmp->next = NULL;

    Rank *last = pRank->next;
    if(last){
        while(last->next){
            last = last->next;
        }
        last->next = tmp;
    }
    else{
        last->next = tmp;
    }
    last = tmp;
    last->next = NULL;
}

//读取文件到动态数组并打印排行榜
void printrank()
{
    FILE *pf = fopen("Rank.txt", "r");
    int n;//记录有多少玩家数据
	char buf[100];
	while (!feof(pf)){
		memset(buf, 0, sizeof(buf));//每次读取一行之前都把这个buf清空
		fgets(buf, sizeof(buf), pf);//从文件中读取一行
		n++;
	}
	n--;
	fclose(pf);

	pf = fopen("Rank.txt", "r");
	Rank* arr = (Rank*)malloc(n * sizeof(Rank));
	int i=0;
	while(!feof(pf)){
		fscanf(pf, "%s %d", arr[i].name, &arr[i].score);
		i++;
	}
    fclose(pf);

    int _score;
    char _name[MAX_NAME_LEN];
    for(int j = n; j >= 0; j--){
        for(int i = 0; i<j; i++){
            if(arr[i].score < arr[j-1].score){
                _score = arr[i].score;
                strcpy(_name, arr[i].name);
                printf("\a");
                arr[i].score = arr[j-1].score;
                strcpy(arr[i].name, arr[j-1].name);
                arr[j-1].score = _score;
                strcpy(arr[j-1].name, _name);
            }
        }
    }
    for(int i = 0; i<n && i<5; i++){
        printf("%d %s %d\n",i+1, arr[i].name, arr[i].score);
    }
}

//检测模块
void detect(info zh[], char l[])
{
    int i;
    char z[20];
    strcpy(z, l);
    for (i = 0; i < MAX_NAME_LEN; i++)
    {
        while (strcmp(zh[i].name, z) == 0)
        {
            printf("This username has been registered!\n");
            i = 0;
            printf("Please enter your username:");
            scanf("%s", &z);
        }
    }
    strcpy(l, z);
}

//注册模块
int _register(info zh[], int m)
{
    char account[20], e[20], l[20];
    printf("Please enter your username:");     scanf("%s", &l);
    detect(zh, l);
    printf("Please enter your account:");       scanf("%s", &account);
    printf("\n");
    printf("Please enter your password:");         scanf("%s", &e);
    printf("\n");
    strcpy(zh[m].name, l);
    strcpy(zh[m].account, account);
    strcpy(zh[m].password, e);
    printf("Success!\n");
    printf("%s\n%s\n", zh[m].password, zh[m].account);
    m++;
    return m;
}

//登录模块
void login(info zh[], int m)
{
    int g, f, i;
    char account[20], e[20], n[20];
    printf("Please enter your username:");
    scanf("%s", &n);
    printf("Please enter your account:");
    scanf("%s", &account);
    printf("Please enter your password:");
    scanf("%s", &e);
    printf("\n");

    for (i = 0; i < MAX_NAME_LEN; i++)
    {
        if (strcmp(zh[i].name, n) == 0)
        {
            g = strcmp(zh[i].account, account);
            f = strcmp(zh[i].password, e);
            if ((g == 0) && (f == 0))
            {
                printf("%s,Welcome back!\n\n", zh[i].name);
    
            }
            else
            {
                printf("False account or password!\n\n");
            }
        }
    }
}