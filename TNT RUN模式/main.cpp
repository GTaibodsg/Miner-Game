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
	string name;//����ǳ�
	int score;//�÷� 
	int health;//���� 
	int mul;//���� 
	int ign;//������
	int Round;//��ֵĻغ�
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
		cout<<"��";	
	} 
	else if(x==2)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
		cout<<"ը";
	}
	else if(x==3)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
		cout<<"��";
	}
	else if(x==4)
		cout<<"ľ";
	else if(x==5)
		cout<<"ʯ";
	else if(x==6)
		cout<<"ú";
	else if(x==7)
		cout<<"��";
	else if(x==8)
		cout<<"��";
	else if(x==9)
		cout<<"��";
	else if(x==10)
		cout<<"��";
	else if(x==11)
		cout<<"��";
	else
		cout<<"��";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
}

bool danger(int x)//Σ�շ��� 
{
	return x==2||x==3;
}

void get_player_info()
{
	cout<<"��������Ϸ������";
	cin>>n;
	while(!(n>=2&&n<=16))
	{
		cout<<"��Ϸ���������� 2 �� 16 ֮������������������룺";
		cin>>n;
	}
	for(int i=1;i<=n;i++)
	{
		cout<<"��������� "<<i<<" �ǳƣ�";
		cin>>player[i].name;
		player[i].score=0;
		player[i].health=6;
		player[i].mul=10;
		player[i].ign=0; 
	}
	clear;
}

void initial()
{
	for(int i=1;i<=4;i++)
	for(int j=1;j<=4;j++)
		game[i][j]=5;
}

int nex(int x)
{
	if(x==5)
		return 4;
	else if(x==4)
		return 6;
	else if(x==6)
		return 7;
	else if(x==7)
		return 8;
	else if(x==8)
		return 9;
	else if(x==9)
		return rand()%3+10;
	else
		return 3;
}

void print_grid()
{
	for(int i=1;i<=4;i++)
	{
		for(int j=1;j<=4;j++)
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
		cout<<"��ң�"<<player[i].name<<endl;
		cout<<"�÷֣�"<<player[i].score<<" | ";
		cout<<"����ֵ��"<<player[i].health<<" | ";
		cout<<"���ʣ�"<<player[i].mul/10<<"."<<player[i].mul%10<<" | ";
		if(show_Round)
		{
			cout<<"�����ʣ�"<<player[i].ign<<" %"<<" | ";
			cout<<"��ֵĻغ�����"<<player[i].Round<<endl;
		}
		else
			cout<<"�����ʣ�"<<player[i].ign<<" %"<<endl;
	}
}

void TNT_act(int x,int y)
{
	game[x][y]=1;
	for(int i=-2;i<=2;i++)
	for(int j=-2;j<=2;j++)
	if(abs(i)+abs(j)<=2)
	{
		if(game[x+i][y+j]>=4)
			game[x+i][y+j]=1;
		else if(game[x+i][y+j]==2)
		{
			cout<<"ը������������Ӧ��"<<endl;
			wait;
			TNT_act(x+i,y+j);
		}
	}	
}

bool checklava()
{
	queue<PA> q;
	set<PA> s;
	for(int i=1;i<=4;i++)
	for(int j=1;j<=4;j++)
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
			if(xx<1||xx>4||yy<1||yy>4||s.count({xx,yy}))
				continue;
			if(game[xx][yy]==1||game[xx][yy]==4)
			{
				game[xx][yy]=3;
				q.push({xx,yy});
			}
			else if(game[xx][yy]==2)
			{
				cout<<"�ҽ�������ը����"<<endl;
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
		cout<<"��ǰ��ң�"<<player[cur].name<<endl; 
		player[cur].Round++;
		wait;
		int x=rand()%4+1;
		int y=rand()%4+1;
		while(danger(game[x][y])&&rand()%100<player[cur].ign)
		{
			cout<<"�������("<<x<<","<<y<<")�����ܳɹ���"<<endl;
			wait; 
			x=rand()%4+1;
			y=rand()%4+1;
		}
		
		
		
		cout<<"�������("<<x<<","<<y<<")��";
		print(game[x][y]);
		cout<<endl;
		wait;
		if(game[x][y]==1)
			cout<<"ʲô��û�з���......"<<endl;
		else if(game[x][y]==2)
		{
			cout<<"��⣬��������ը����"<<endl;
			player[cur].health=max(0,player[cur].health-2);
			TNT_act(x,y);
			
		}
		else if(game[x][y]==3)
		{
			cout<<"��⣬��������ҽ���"<<endl;
			player[cur].health=max(0,player[cur].health-1);
		}
		else if(game[x][y]==4)
		{
			cout<<"���ڵ���ľͷ��"<<endl;
			player[cur].score+=player[cur].mul/10;
		}
		else if(game[x][y]==5)
			cout<<"���ڵ���ʯͷ��"<<endl;
		else if(game[x][y]==6)
		{
			cout<<"���ڵ���ú��"<<endl;
			player[cur].score+=3*player[cur].mul/10;
		}
		else if(game[x][y]==7)
		{
			cout<<"���ڵ�������"<<endl;
			player[cur].score+=8*player[cur].mul/10;
		}
		else if(game[x][y]==8)
		{
			cout<<"���ڵ��˽��"<<endl;
			player[cur].score+=24*player[cur].mul/10;
		}
		else if(game[x][y]==9)
		{
			cout<<"���ڵ�����ʯ��"<<endl;
			player[cur].score+=64*player[cur].mul/10;
		}
		else if(game[x][y]==10)
		{
			cout<<"���ڵ��˺챦ʯ��"<<endl;
			wait;
			int tmp=rand()%3+1;
			player[cur].health+=tmp;
			cout<<"��ϲ�㣬����� "<<tmp<<" ������ֵ��"<<endl;
		}
		else if(game[x][y]==11)
		{
			cout<<"���ڵ����̱�ʯ��"<<endl;
			wait;
			int tmp=rand()%10+1;
			player[cur].mul+=tmp;
			cout<<"��ϲ�㣬����� "<<tmp/10<<"."<<tmp%10<<" �㱶��������"<<endl;
		}
		else
		{
			cout<<"���ڵ�������ʯ��"<<endl;
			wait;
			int tmp=rand()%6+1;
			player[cur].ign+=tmp;
			cout<<"��ϲ�㣬����� "<<tmp<<"% �������ʣ�"<<endl;
		}
		wait;
		
		game[x][y]=nex(game[x][y]);
		
		if(player[cur].health==0)
		{
			sur--;
			cout<<"����������"<<endl;
			wait; 
		}

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
