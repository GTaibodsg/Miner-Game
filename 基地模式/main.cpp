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
	int cap;//��������
	int w;//��������
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
	else if(x==12)
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
	cout<<"����ģʽ���ڸ�ģʽ�£�����ڵ����κη��鶼��Ҫ���ػ��ز��ܼƷ֣������ڵ��ķ����������ޡ�"<<endl;
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
			game[x][y]=3;//�����ҽ� 
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
			game[x][y]=2;//����TNT 
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
			game[x][y]=4;//����ľͷ 
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
			game[x][y]=6;//����ú�� 
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
			game[x][y]=7;//�������� 
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
			game[x][y]=8;//���ý�� 
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
			game[x][y]=9;//������ʯ 
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
			game[x][y]=10;//���ú챦ʯ 
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
			game[x][y]=11;//�����̱�ʯ 
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
			game[x][y]=12;//��������ʯ 
			tmp++;
		}
	}
	for(int i=1;i<=16;i++)
	for(int j=1;j<=16;j++)
	if(game[i][j]==0)
		game[i][j]=5;//����ʯͷ 
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
		cout<<"��ң�"<<player[i].name<<endl;
		cout<<"�÷֣�"<<player[i].score<<" | ";
		cout<<"����ֵ��"<<player[i].health<<" | ";
		cout<<"����������"<<player[i].w<<" / "<<player[i].cap<<" | ";
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
		if(game[x+i][y+j]>=4&&game[x+i][y+j]!=13)
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
		int x=rand()%16+1;
		int y=rand()%16+1;
		
		
		
		cout<<"�������("<<x<<","<<y<<")��";
		print(game[x][y]);
		cout<<endl;
		wait;
		if(game[x][y]==1)
			cout<<"ʲô��û�з���......"<<endl;
		else if(game[x][y]==2)
		{
			if(rand()%100<player[cur].ign)
				cout<<"��ϲ�㣬���ܳɹ���"<<endl;
			else
			{
				cout<<"��⣬��������ը����"<<endl;
				player[cur].health=max(0,player[cur].health-2);
				TNT_act(x,y);
			}			
		}
		else if(game[x][y]==3)
		{
			if(rand()%100<player[cur].ign)
				cout<<"��ϲ�㣬���ܳɹ���"<<endl;
			else
			{
				cout<<"��⣬��������ҽ�"<<endl;
				player[cur].health=max(0,player[cur].health-1);
			}
		}
		else if(game[x][y]==4)
		{
			cout<<"�㷢����ľͷ��"<<endl;
			if(player[cur].w+1>player[cur].cap)
			{
				wait;
				cout<<"��⣬��ı����������㣡"<<endl;
			}
			else
			{
				player[cur].w+=1;
				game[x][y]=1;
			}
				
		}
		else if(game[x][y]==5)
		{
			cout<<"���ڵ���ʯͷ��"<<endl;
			game[x][y]=1;
		}
		else if(game[x][y]==6)
		{
			cout<<"�㷢����ú��"<<endl;
			if(player[cur].w+3>player[cur].cap)
			{
				wait;
				cout<<"��⣬��ı����������㣡"<<endl;
			}
			else
			{
				player[cur].w+=3;
				game[x][y]=1;
			}
		}
		else if(game[x][y]==7)
		{
			cout<<"�㷢��������"<<endl;
			if(player[cur].w+8>player[cur].cap)
			{
				wait;
				cout<<"��⣬��ı����������㣡"<<endl;
			}
			else
			{
				player[cur].w+=8;
				game[x][y]=1;
			}
		}
		else if(game[x][y]==8)
		{
			cout<<"�㷢���˽��"<<endl;
			if(player[cur].w+24>player[cur].cap)
			{
				wait;
				cout<<"��⣬��ı����������㣡"<<endl;
			}
			else
			{
				player[cur].w+=24;
				game[x][y]=1;
			}
		}
		else if(game[x][y]==9)
		{
			cout<<"�㷢������ʯ��"<<endl;
			if(player[cur].w+64>player[cur].cap)
			{
				wait;
				cout<<"��⣬��ı����������㣡"<<endl;
			}
			else
			{
				player[cur].w+=64;
				game[x][y]=1;
			}
		}
		else if(game[x][y]==10)
		{
			cout<<"���ڵ��˺챦ʯ��"<<endl;
			wait;
			int tmp=rand()%5+1;
			player[cur].health+=tmp;
			cout<<"��ϲ�㣬����� "<<tmp<<" ������ֵ��"<<endl;
			game[x][y]=1;
		}
		else if(game[x][y]==11)
		{
			cout<<"���ڵ����̱�ʯ��"<<endl;
			wait;
			int tmp=rand()%10+1;
			player[cur].mul+=tmp;
			cout<<"��ϲ�㣬����� "<<tmp/10<<"."<<tmp%10<<" �㱶��������"<<endl;
			game[x][y]=1;
		}
		else if(game[x][y]==12)
		{
			cout<<"���ڵ�������ʯ��"<<endl;
			wait;
			int tmp=rand()%30+1;
			player[cur].ign=min(90,player[cur].ign+tmp);
			cout<<"��ϲ�㣬����� "<<tmp<<"% �������ʣ�"<<endl;
			game[x][y]=1;
		}
		else
		{
			cout<<"�㷵���˻��أ�"<<endl;
			player[cur].score+=player[cur].w*player[cur].mul/10;
			player[cur].cap+=player[cur].w;
			player[cur].w=0;
		}
		
		wait;
		if(player[cur].health==0)
		{
			sur--;
			cout<<"����������"<<endl;
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
