#include<bits/stdc++.h>
#include<unistd.h>
#include "windows.h"
#define clear system("cls")
#define wait sleep(3)
#define PA pair<int,int>
#define Nmax 20

using namespace std;

int n,game[Nmax][Nmax];
const int dx[]={-1,1,0,0},dy[]={0,0,-1,1};

struct Player
{
	string name;//玩家昵称
	int score;//得分 
	int health;//生命 
	int mul;//倍率 
	int ign;//闪避率
	int Round;//坚持的回合
	int cap;//背包限重
	int w;//矿物重量
	bool operator < (const Player tmp) const
	{
		return score>tmp.score;
	}
}player[Nmax];

void print(int x)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
	if(x==1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0);
		cout<<"空";	
	} 
	else if(x==2)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
		cout<<"炸";
	}
	else if(x==3)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
		cout<<"浆";
	}
	else if(x==4)
		cout<<"木";
	else if(x==5)
		cout<<"石";
	else if(x==6)
		cout<<"煤";
	else if(x==7)
		cout<<"铁";
	else if(x==8)
		cout<<"金";
	else if(x==9)
		cout<<"钻";
	else if(x==10)
		cout<<"红";
	else if(x==11)
		cout<<"绿";
	else if(x==12)
		cout<<"蓝";
	else
		cout<<"家";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
}

bool danger(int x)//危险方块 
{
	return x==2||x==3;
}

void get_player_info()
{
	cout<<"基地模式：在该模式下，玩家挖掉的任何方块都需要返回基地才能计分，且能挖掉的方块容量有限。"<<endl;
	cout<<"请输入游戏人数：";
	cin>>n;
	while(!(n>=2&&n<=16))
	{
		cout<<"游戏人数必须是 2 到 16 之间的整数，请重新输入：";
		cin>>n;
	}
	for(int i=1;i<=n;i++)
	{
		cout<<"请输入玩家 "<<i<<" 昵称：";
		cin>>player[i].name;
		player[i].score=0;
		player[i].health=6;
		player[i].mul=10;
		player[i].ign=0;
		player[i].cap=10;
		player[i].w=0;
	}
	random_shuffle(player+1,player+n+1);
	clear;
}

void initial()
{
	for(int i=6;i<=11;i++)
	for(int j=6;j<=11;j++)
		game[i][j]=13;
	int tmp=0;
	while(tmp<2)
	{
		int x=rand()%16+1;
		int y=rand()%16+1;
		if(game[x][y]==0)
		{
			game[x][y]=3;//放置岩浆 
			tmp++;
		}
	}
	tmp=0;
	while(tmp<1)
	{
		int x=rand()%12+3;
		int y=rand()%12+3;
		if(game[x][y]==0&&game[x-1][y]!=3&&game[x+1][y]!=3&&game[x][y-1]!=3&&game[x][y+1]!=3)
		{
			game[x][y]=2;//放置TNT 
			tmp++;
		}
	}
	tmp=0;
	while(tmp<48)
	{
		int x=rand()%16+1;
		int y=rand()%16+1;
		if(game[x][y]==0&&game[x-1][y]!=3&&game[x+1][y]!=3&&game[x][y-1]!=3&&game[x][y+1]!=3)
		{
			game[x][y]=4;//放置木头 
			tmp++;
		}
	}
	tmp=0;
	while(tmp<32)
	{
		int x=rand()%16+1;
		int y=rand()%16+1;
		if(game[x][y]==0)
		{
			game[x][y]=6;//放置煤矿 
			tmp++;
		}
	}
	tmp=0;
	while(tmp<20)
	{
		int x=rand()%16+1;
		int y=rand()%16+1;
		if(game[x][y]==0)
		{
			game[x][y]=7;//放置铁矿 
			tmp++;
		}
	}
	tmp=0;
	while(tmp<10)
	{
		int x=rand()%16+1;
		int y=rand()%16+1;
		if(game[x][y]==0)
		{
			game[x][y]=8;//放置金矿 
			tmp++;
		}
	}
	tmp=0;
	while(tmp<5)
	{
		int x=rand()%16+1;
		int y=rand()%16+1;
		if(game[x][y]==0)
		{
			game[x][y]=9;//放置钻石 
			tmp++;
		}
	}
	tmp=0;
	while(tmp<5)
	{
		int x=rand()%16+1;
		int y=rand()%16+1;
		if(game[x][y]==0)
		{
			game[x][y]=10;//放置红宝石 
			tmp++;
		}
	}
	tmp=0;
	while(tmp<5)
	{
		int x=rand()%16+1;
		int y=rand()%16+1;
		if(game[x][y]==0)
		{
			game[x][y]=11;//放置绿宝石 
			tmp++;
		}
	}
	tmp=0;
	while(tmp<5)
	{
		int x=rand()%16+1;
		int y=rand()%16+1;
		if(game[x][y]==0)
		{
			game[x][y]=12;//放置蓝宝石 
			tmp++;
		}
	}
	for(int i=1;i<=16;i++)
	for(int j=1;j<=16;j++)
	if(game[i][j]==0)
		game[i][j]=5;//放置石头 
}

void print_grid()
{
	for(int i=1;i<=16;i++)
	{
		for(int j=1;j<=16;j++)
		{
			print(game[i][j]);
			if(j%4==0)
				cout<<" ";
		}
		cout<<endl;	
		if(i%4==0)
			cout<<endl;
	}
}

void print_player_info(bool show_Round)
{
	for(int i=1;i<=n;i++)
	{
		cout<<"玩家："<<player[i].name<<endl;
		cout<<"得分："<<player[i].score<<" | ";
		cout<<"生命值："<<player[i].health<<" | ";
		cout<<"背包容量："<<player[i].w<<" / "<<player[i].cap<<" | ";
		cout<<"倍率："<<player[i].mul/10<<"."<<player[i].mul%10<<" | ";
		if(show_Round)
		{
			cout<<"闪避率："<<player[i].ign<<" %"<<" | ";
			cout<<"坚持的回合数："<<player[i].Round<<endl;
		}
		else
			cout<<"闪避率："<<player[i].ign<<" %"<<endl;
	}
}

void TNT_act(int x,int y)
{
	game[x][y]=1;
	for(int i=-2;i<=2;i++)
	for(int j=-2;j<=2;j++)
	if(abs(i)+abs(j)<=2)
	{
		if(game[x+i][y+j]>=4&&game[x+i][y+j]!=13)
			game[x+i][y+j]=1;
		else if(game[x+i][y+j]==2)
		{
			cout<<"炸弹触发连锁反应！"<<endl;
			wait;
			TNT_act(x+i,y+j);
		}
	}	
}

bool checklava()
{
	queue<PA> q;
	set<PA> s;
	for(int i=1;i<=16;i++)
	for(int j=1;j<=16;j++)
	if(game[i][j]==3)
		q.push({i,j});

	while(q.size())
	{
		auto [x,y]=q.front();
		q.pop();
		if(s.count({x,y}))
			continue;
		s.insert({x,y});
		for(int i=0;i<4;i++)
		{
			int xx=x+dx[i];
			int yy=y+dy[i];
			if(xx<1||xx>16||yy<1||yy>16||s.count({xx,yy}))
				continue;
			if(game[xx][yy]==1||game[xx][yy]==4)
			{
				game[xx][yy]=3;
				q.push({xx,yy});
			}
			else if(game[xx][yy]==2)
			{
				cout<<"岩浆触发了炸弹！"<<endl;
				TNT_act(xx,yy);
				wait;
				return true;
			}
		}
	}
	return false;
}

void EndMessage()
{
	clear;
	wait;
	print_grid();
	sort(player+1,player+n+1);
	print_player_info(true);
}

int main()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
	srand(time(NULL));
	get_player_info();
	initial();
	
	int sur=n;
	int cur=1;
	while(1)
	{
		clear;
		print_grid();
		print_player_info(false);
		cout<<"当前玩家："<<player[cur].name<<endl; 
		player[cur].Round++;
		wait;
		int x=rand()%16+1;
		int y=rand()%16+1;
		
		
		
		cout<<"随机坐标("<<x<<","<<y<<")：";
		print(game[x][y]);
		cout<<endl;
		wait;
		if(game[x][y]==1)
			cout<<"什么都没有发生......"<<endl;
		else if(game[x][y]==2)
		{
			if(rand()%100<player[cur].ign)
				cout<<"恭喜你，闪避成功！"<<endl;
			else
			{
				cout<<"糟糕，你引爆了炸弹！"<<endl;
				player[cur].health=max(0,player[cur].health-2);
				TNT_act(x,y);
			}			
		}
		else if(game[x][y]==3)
		{
			if(rand()%100<player[cur].ign)
				cout<<"恭喜你，闪避成功！"<<endl;
			else
			{
				cout<<"糟糕，你掉进了岩浆"<<endl;
				player[cur].health=max(0,player[cur].health-1);
			}
		}
		else if(game[x][y]==4)
		{
			cout<<"你发现了木头！"<<endl;
			if(player[cur].w+1>player[cur].cap)
			{
				wait;
				cout<<"糟糕，你的背包容量不足！"<<endl;
			}
			else
			{
				player[cur].w+=1;
				game[x][y]=1;
			}
				
		}
		else if(game[x][y]==5)
		{
			cout<<"你挖掉了石头！"<<endl;
			game[x][y]=1;
		}
		else if(game[x][y]==6)
		{
			cout<<"你发现了煤矿！"<<endl;
			if(player[cur].w+3>player[cur].cap)
			{
				wait;
				cout<<"糟糕，你的背包容量不足！"<<endl;
			}
			else
			{
				player[cur].w+=3;
				game[x][y]=1;
			}
		}
		else if(game[x][y]==7)
		{
			cout<<"你发现了铁矿！"<<endl;
			if(player[cur].w+8>player[cur].cap)
			{
				wait;
				cout<<"糟糕，你的背包容量不足！"<<endl;
			}
			else
			{
				player[cur].w+=8;
				game[x][y]=1;
			}
		}
		else if(game[x][y]==8)
		{
			cout<<"你发现了金矿！"<<endl;
			if(player[cur].w+24>player[cur].cap)
			{
				wait;
				cout<<"糟糕，你的背包容量不足！"<<endl;
			}
			else
			{
				player[cur].w+=24;
				game[x][y]=1;
			}
		}
		else if(game[x][y]==9)
		{
			cout<<"你发现了钻石！"<<endl;
			if(player[cur].w+64>player[cur].cap)
			{
				wait;
				cout<<"糟糕，你的背包容量不足！"<<endl;
			}
			else
			{
				player[cur].w+=64;
				game[x][y]=1;
			}
		}
		else if(game[x][y]==10)
		{
			cout<<"你挖掉了红宝石！"<<endl;
			wait;
			int tmp=rand()%5+1;
			player[cur].health+=tmp;
			cout<<"恭喜你，获得了 "<<tmp<<" 点生命值！"<<endl;
			game[x][y]=1;
		}
		else if(game[x][y]==11)
		{
			cout<<"你挖掉了绿宝石！"<<endl;
			wait;
			int tmp=rand()%10+1;
			player[cur].mul+=tmp;
			cout<<"恭喜你，获得了 "<<tmp/10<<"."<<tmp%10<<" 点倍率提升！"<<endl;
			game[x][y]=1;
		}
		else if(game[x][y]==12)
		{
			cout<<"你挖掉了蓝宝石！"<<endl;
			wait;
			int tmp=rand()%30+1;
			player[cur].ign=min(90,player[cur].ign+tmp);
			cout<<"恭喜你，获得了 "<<tmp<<"% 点闪避率！"<<endl;
			game[x][y]=1;
		}
		else
		{
			cout<<"你返回了基地！"<<endl;
			player[cur].score+=player[cur].w*player[cur].mul/10;
			player[cur].cap+=player[cur].w;
			player[cur].w=0;
		}
		
		wait;
		if(player[cur].health==0)
		{
			sur--;
			cout<<"你已阵亡！"<<endl;
			wait; 
		}
		while(checklava());

		if(sur==0)
			break;
		
		while(1)
		{
			cur=cur+1;
			if(cur>n)
				cur-=n;
			if(player[cur].health>0)
				break;
		}
	}

	EndMessage();
	system("pause");
}
