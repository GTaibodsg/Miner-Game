#include<bits/stdc++.h>
#include<unistd.h>
#include "windows.h"
#define clear system("cls")
#define wait sleep(3)
#define PA pair<int,int>
#define Nmax 20

using namespace std;

int n,game[Nmax][Nmax],mst[Nmax][Nmax];
const int dx[]={-1,1,0,0},dy[]={0,0,-1,1};

struct Player
{
	string name;//玩家昵称
	int score;//得分 
	int health;//生命 
	int mul;//倍率 
	int ign;//闪避率
	int Round;//坚持的回合
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
	else
		cout<<"蓝";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
}

void print_mst(int x)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
	if(x==1)
		cout<<"史";
	else if(x==2)
		cout<<"僵";
	else
		cout<<"骷";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
}

bool danger(int x)//危险方块 
{
	return x==2||x==3;
}

bool danger_mst(int x,int y)
{
	return mst[x][y]!=0;
}

void get_player_info()
{
	cout<<"打怪模式在地图生成完毕后会在除了岩浆和木头以外的方块上生成三种怪物，分别是史莱姆、僵尸和骷髅。"<<endl;
	cout<<"玩家进入有怪物的方块会与该怪物发生战斗，可能击败怪物，也可能被怪物攻击。击败怪物会获得丰厚的分数奖励（倍率依旧适用）。"<<endl;
	cout<<"此外，僵尸的索敌范围为以自己为中心的3×3范围内，骷髅的索敌范围为所有与自己同行或者同列的方块。进入怪物的索敌范围可能被怪物攻击。"<<endl;
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
	}
	random_shuffle(player+1,player+n+1);
	clear;
}

void initial()
{
	int tmp=0;
	while(tmp<3)
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
	while(tmp<0)
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
	while(tmp<64)
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
	while(tmp<16)
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
	while(tmp<8)
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
	while(tmp<3)
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
	
	tmp=0;
	while(tmp<24)
	{
		int x=rand()%16+1;
		int y=rand()%16+1;
		if(mst[x][y]==0&&game[x][y]!=3&&game[x][y]!=4)
		{
			mst[x][y]=1;//放置史莱姆
			tmp++;
		}
	}
	tmp=0;
	while(tmp<6)
	{
		int x=rand()%16+1;
		int y=rand()%16+1;
		if(mst[x][y]==0&&game[x][y]!=3&&game[x][y]!=4)
		{
			mst[x][y]=2;//放置僵尸
			tmp++;
		}
	}
	tmp=0;
	while(tmp<2)
	{
		int x=rand()%16+1;
		int y=rand()%16+1;
		if(mst[x][y]==0&&game[x][y]!=3&&game[x][y]!=4)
		{
			mst[x][y]=3;//放置骷髅
			tmp++;
		}
	}
}

void print_grid()
{
	for(int i=1;i<=16;i++)
	{
		for(int j=1;j<=16;j++)
		{
			if(mst[i][j]==0)
				print(game[i][j]);
			else
				print_mst(mst[i][j]);
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
		mst[x+i][y+j]=0;
		if(game[x+i][y+j]>=4)
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
				mst[xx][yy]=0;
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
		
		if(mst[x][y])
			print_mst(mst[x][y]);
		else
			print(game[x][y]);
		cout<<endl;
		wait;
		
		if(mst[x][y]!=0)
		{
			if(mst[x][y]==1)
			{
				cout<<"你偶遇了怪物史莱姆！"<<endl;
				wait;
				if(rand()%100<15)
				{
					if(rand()%100<player[cur].ign)
						cout<<"史莱姆攻击了你，但是你成功闪避了本次攻击。"<<endl;
					else
					{
						cout<<"糟糕，你被攻击了！"<<endl;
						player[cur].health=max(0,player[cur].health-1);
					}
				}
				else
				{
					cout<<"你击败了史莱姆！"<<endl;
					mst[x][y]=0;
					player[cur].score+=12*player[cur].mul/10;
				}
			}
			else if(mst[x][y]==2)
			{
				cout<<"你偶遇了怪物僵尸！"<<endl;
				wait;
				if(rand()%100<40)
				{
					if(rand()%100<player[cur].ign)
						cout<<"僵尸攻击了你，但是你成功闪避了本次攻击。"<<endl;
					else
					{
						cout<<"糟糕，你被攻击了！"<<endl;
						player[cur].health=max(0,player[cur].health-1);
					}
				}
				else
				{
					cout<<"你击败了僵尸！"<<endl;
					mst[x][y]=0;
					player[cur].score+=40*player[cur].mul/10;
				}
			}
			else
			{
				cout<<"你偶遇了怪物骷髅！"<<endl;
				wait;
				if(rand()%100<25)
				{
					if(rand()%100<player[cur].ign)
						cout<<"骷髅攻击了你，但是你成功闪避了本次攻击。"<<endl;
					else
					{
						cout<<"糟糕，你被攻击了！"<<endl;
						player[cur].health=max(0,player[cur].health-1);
					}
				}
				else
				{
					cout<<"你击败了骷髅！"<<endl;
					mst[x][y]=0;
					player[cur].score+=100*player[cur].mul/10;
				}
			}
		}
		else if(game[x][y]==1)
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
			cout<<"你挖掉了木头！"<<endl;
			player[cur].score+=player[cur].mul/10;
			game[x][y]=1;
		}
		else if(game[x][y]==5)
		{
			cout<<"你挖掉了石头！"<<endl;
			game[x][y]=1;
		}
		else if(game[x][y]==6)
		{
			cout<<"你挖掉了煤矿！"<<endl;
			player[cur].score+=3*player[cur].mul/10;
			game[x][y]=1;
		}
		else if(game[x][y]==7)
		{
			cout<<"你挖掉了铁矿！"<<endl;
			player[cur].score+=8*player[cur].mul/10;
			game[x][y]=1;
		}
		else if(game[x][y]==8)
		{
			cout<<"你挖掉了金矿！"<<endl;
			player[cur].score+=24*player[cur].mul/10;
			game[x][y]=1;
		}
		else if(game[x][y]==9)
		{
			cout<<"你挖掉了钻石！"<<endl;
			player[cur].score+=64*player[cur].mul/10;
			game[x][y]=1;
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
		else
		{
			cout<<"你挖掉了蓝宝石！"<<endl;
			wait;
			int tmp=rand()%30+1;
			player[cur].ign=min(90,player[cur].ign+tmp);
			cout<<"恭喜你，获得了 "<<tmp<<"% 点闪避率！"<<endl;
			game[x][y]=1;
		}
		
		wait;
		
		for(int i=-1;i<=1;i++)
		for(int j=-1;j<=1;j++)
		if(mst[x+i][y+j]==2&&(i!=0||j!=0))
		{
			cout<<"糟糕！你进入了位于("<<x+i<<","<<y+j<<")的僵尸的攻击范围！"<<endl;
			wait;
			if(rand()%100<40)
			{
				if(rand()%100<player[cur].ign)
					cout<<"僵尸攻击了你，但是你成功闪避了本次攻击。"<<endl;
				else
				{
					cout<<"僵尸对你造成了伤害"<<endl;
					player[cur].health=max(0,player[cur].health-1);
				}
			}
			else
				cout<<"很幸运，僵尸未对你造成伤害。"<<endl;
			wait;
		}
		
		for(int i=1;i<=16;i++)
		{
			if(mst[x][i]==3&&i!=y)
			{
				cout<<"糟糕！你进入了位于("<<x<<","<<i<<")的骷髅的攻击范围！"<<endl;
				wait;
				if(rand()%100<25)
				{
					if(rand()%100<player[cur].ign)
						cout<<"骷髅攻击了你，但是你成功闪避了本次攻击。"<<endl;
					else
					{
						cout<<"骷髅对你造成了伤害"<<endl;
						player[cur].health=max(0,player[cur].health-1);
					}
				}
				else
					cout<<"很幸运，骷髅未对你造成伤害。"<<endl;
				wait;
			}
			if(mst[i][y]==3&&i!=x)
			{
				cout<<"糟糕！你进入了位于("<<i<<","<<y<<")的骷髅的攻击范围！"<<endl;
				wait;
				if(rand()%100<25)
				{
					if(rand()%100<player[cur].ign)
						cout<<"骷髅攻击了你，但是你成功闪避了本次攻击。"<<endl;
					else
					{
						cout<<"骷髅对你造成了伤害"<<endl;
						player[cur].health=max(0,player[cur].health-1);
					}
				}
				else
					cout<<"很幸运，骷髅未对你造成伤害。"<<endl;
				wait;
			}
		}
		
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
