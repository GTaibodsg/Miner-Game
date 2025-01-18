#include<bits/stdc++.h>
#include<unistd.h>
#include "windows.h"
#define clear system("cls")
#define wait sleep(3)
#define PA pair<int,int>
#define Nmax 20

using namespace std;

int n,game[2][Nmax][Nmax];
const int dx[]={-1,1,0,0},dy[]={0,0,-1,1};

struct Player
{
	string name;//����ǳ�
	int score;//�÷� 
	int health;//���� 
	int mul;//���� 
	int ign;//������
	int Round;//��ֵĻغ�
	int locate;//���ڵ�����
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
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
		cout<<"��";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
}

bool danger(int x)//Σ�շ��� 
{
	return x==2||x==3;
}

void get_player_info()
{
	cout<<"˫��ͼģʽ��������ͼ֮��ͨ�������ţ����������л��������Ų��ᱻ�ƻ������ǽ��봫���ŵĴ����� 1 ������ֵ��"<<endl;
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
		player[i].locate=0;//��ʼλ��Ϊ������
	}
	clear;
}

void initial()
{
	
	//����������
	
	int tmp=0;
	while(tmp<1)
	{
		int x=rand()%8+3;
		int y=rand()%8+3;
		if(game[0][x][y]==0)
		{
			game[0][x][y]=3;//�����ҽ� 
			tmp++;
		}
	}
	tmp=0;
	while(tmp<6)
	{
		int x=rand()%8+3;
		int y=rand()%8+3;
		if(game[0][x][y]==0&&game[0][x-1][y]!=3&&game[0][x+1][y]!=3&&game[0][x][y-1]!=3&&game[0][x][y+1]!=3)
		{
			game[0][x][y]=13;//���ô�����
			tmp++;
		}
	}
	tmp=0;
	tmp=0;
	while(tmp<1)
	{
		int x=rand()%8+3;
		int y=rand()%8+3;
		if(game[0][x][y]==0&&game[0][x-1][y]!=3&&game[0][x+1][y]!=3&&game[0][x][y-1]!=3&&game[0][x][y+1]!=3)
		{
			game[0][x][y]=2;//����TNT 
			tmp++;
		}
	}
	tmp=0;
	while(tmp<32)
	{
		int x=rand()%12+1;
		int y=rand()%12+1;
		if(game[0][x][y]==0&&game[0][x-1][y]!=3&&game[0][x+1][y]!=3&&game[0][x][y-1]!=3&&game[0][x][y+1]!=3)
		{
			game[0][x][y]=4;//����ľͷ 
			tmp++;
		}
	}
	tmp=0;
	while(tmp<20)
	{
		int x=rand()%12+1;
		int y=rand()%12+1;
		if(game[0][x][y]==0)
		{
			game[0][x][y]=6;//����ú�� 
			tmp++;
		}
	}
	tmp=0;
	while(tmp<10)
	{
		int x=rand()%12+1;
		int y=rand()%12+1;
		if(game[0][x][y]==0)
		{
			game[0][x][y]=7;//�������� 
			tmp++;
		}
	}
	tmp=0;
	while(tmp<5)
	{
		int x=rand()%12+1;
		int y=rand()%12+1;
		if(game[0][x][y]==0)
		{
			game[0][x][y]=8;//���ý�� 
			tmp++;
		}
	}
	tmp=0;
	while(tmp<2)
	{
		int x=rand()%12+1;
		int y=rand()%12+1;
		if(game[0][x][y]==0)
		{
			game[0][x][y]=9;//������ʯ 
			tmp++;
		}
	}
	tmp=0;
	while(tmp<3)
	{
		int x=rand()%12+1;
		int y=rand()%12+1;
		if(game[0][x][y]==0)
		{
			game[0][x][y]=10;//���ú챦ʯ 
			tmp++;
		}
	}
	tmp=0;
	while(tmp<3)
	{
		int x=rand()%12+1;
		int y=rand()%12+1;
		if(game[0][x][y]==0)
		{
			game[0][x][y]=11;//�����̱�ʯ 
			tmp++;
		}
	}tmp=0;
	while(tmp<3)
	{
		int x=rand()%12+1;
		int y=rand()%12+1;
		if(game[0][x][y]==0)
		{
			game[0][x][y]=12;//��������ʯ 
			tmp++;
		}
	}
	for(int i=1;i<=12;i++)
	for(int j=1;j<=12;j++)
	if(game[0][i][j]==0)
		game[0][i][j]=5;//����ʯͷ 
	
	//���ɵ���
	
	tmp=0;
	while(tmp<5)
	{
		int x=rand()%12+1;
		int y=rand()%12+1;
		if(game[1][x][y]==0)
		{
			game[1][x][y]=3;//�����ҽ� 
			tmp++;
		}
	}
	tmp=0;
	while(tmp<6)
	{
		int x=rand()%8+3;
		int y=rand()%8+3;
		if(game[1][x][y]==0&&game[1][x-1][y]!=3&&game[1][x+1][y]!=3&&game[1][x][y-1]!=3&&game[1][x][y+1]!=3)
		{
			game[1][x][y]=13;//���ô�����
			tmp++;
		}
	}
	tmp=0;
	tmp=0;
	while(tmp<2)
	{
		int x=rand()%8+3;
		int y=rand()%8+3;
		if(game[1][x][y]==0&&game[1][x-1][y]!=3&&game[1][x+1][y]!=3&&game[1][x][y-1]!=3&&game[1][x][y+1]!=3)
		{
			game[1][x][y]=2;//����TNT 
			tmp++;
		}
	}
	tmp=0;
	while(tmp<36)
	{
		int x=rand()%12+1;
		int y=rand()%12+1;
		if(game[1][x][y]==0)
		{
			game[1][x][y]=6;//����ú�� 
			tmp++;
		}
	}
	tmp=0;
	while(tmp<24)
	{
		int x=rand()%12+1;
		int y=rand()%12+1;
		if(game[1][x][y]==0)
		{
			game[1][x][y]=7;//�������� 
			tmp++;
		}
	}
	tmp=0;
	while(tmp<16)
	{
		int x=rand()%12+1;
		int y=rand()%12+1;
		if(game[1][x][y]==0)
		{
			game[1][x][y]=8;//���ý�� 
			tmp++;
		}
	}
	tmp=0;
	while(tmp<8)
	{
		int x=rand()%12+1;
		int y=rand()%12+1;
		if(game[1][x][y]==0)
		{
			game[1][x][y]=9;//������ʯ 
			tmp++;
		}
	}
	tmp=0;
	while(tmp<5)
	{
		int x=rand()%12+1;
		int y=rand()%12+1;
		if(game[1][x][y]==0)
		{
			game[1][x][y]=10;//���ú챦ʯ 
			tmp++;
		}
	}
	tmp=0;
	while(tmp<5)
	{
		int x=rand()%12+1;
		int y=rand()%12+1;
		if(game[1][x][y]==0)
		{
			game[1][x][y]=11;//�����̱�ʯ 
			tmp++;
		}
	}tmp=0;
	while(tmp<5)
	{
		int x=rand()%12+1;
		int y=rand()%12+1;
		if(game[1][x][y]==0)
		{
			game[1][x][y]=12;//��������ʯ 
			tmp++;
		}
	}
	for(int i=1;i<=12;i++)
	for(int j=1;j<=12;j++)
	if(game[1][i][j]==0)
		game[1][i][j]=5;//����ʯͷ 
}

void print_grid()
{
	cout<<"�����磺"<<endl;
	cout<<endl;
	for(int i=1;i<=12;i++)
	{
		for(int j=1;j<=12;j++)
		{
			print(game[0][i][j]);
			if(j%4==0)
				cout<<" ";
		}
		cout<<endl;	
		if(i%4==0)
			cout<<endl;
	}
	cout<<"������"<<endl;
	cout<<endl;
	for(int i=1;i<=12;i++)
	{
		for(int j=1;j<=12;j++)
		{
			print(game[1][i][j]);
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
		cout<<"�����ʣ�"<<player[i].ign<<" %"<<" | ";
		if(show_Round)
			cout<<"��ֵĻغ�����"<<player[i].Round<<endl;
		else
			cout<<"�������磺"<<(player[i].locate==0?"������":"����")<<endl;
	}
}

void TNT_act(int x,int y,int loc)
{
	game[loc][x][y]=1;
	for(int i=-2;i<=2;i++)
	for(int j=-2;j<=2;j++)
	if(abs(i)+abs(j)<=2)
	{
		if(game[loc][x+i][y+j]>=4&&game[loc][x+i][y+j]<=12)
			game[loc][x+i][y+j]=1;
		else if(game[loc][x+i][y+j]==2)
		{
			cout<<"ը������������Ӧ��"<<endl;
			wait;
			TNT_act(x+i,y+j,loc);
		}
	}	
}

bool checklava(int loc)
{
	queue<PA> q;
	set<PA> s;
	for(int i=1;i<=12;i++)
	for(int j=1;j<=12;j++)
	if(game[loc][i][j]==3)
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
			if(xx<1||xx>12||yy<1||yy>12||s.count({xx,yy}))
				continue;
			if(game[loc][xx][yy]==1||game[loc][xx][yy]==4)
			{
				game[loc][xx][yy]=3;
				q.push({xx,yy});
			}
			else if(game[loc][xx][yy]==2)
			{
				cout<<"�ҽ�������ը����"<<endl;
				TNT_act(xx,yy,loc);
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
		int x=rand()%12+1;
		int y=rand()%12+1;
		int loc=player[cur].locate;
		
		
		
		cout<<"�������("<<x<<","<<y<<")��";
		print(game[loc][x][y]);
		cout<<endl;
		wait;
		if(game[loc][x][y]==1)
			cout<<"ʲô��û�з���......"<<endl;
		else if(game[loc][x][y]==2)
		{
			if(rand()%100<player[cur].ign)
				cout<<"��ϲ�㣬���ܳɹ���"<<endl;
			else
			{
				cout<<"��⣬��������ը����"<<endl;
				player[cur].health=max(0,player[cur].health-2);
				TNT_act(x,y,loc);
			}			
		}
		else if(game[loc][x][y]==3)
		{
			if(rand()%100<player[cur].ign)
				cout<<"��ϲ�㣬���ܳɹ���"<<endl;
			else
			{
				cout<<"��⣬��������ҽ�"<<endl;
				player[cur].health=max(0,player[cur].health-1);
			}
		}
		else if(game[loc][x][y]==4)
		{
			cout<<"���ڵ���ľͷ��"<<endl;
			player[cur].score+=player[cur].mul/10;
			game[loc][x][y]=1;
		}
		else if(game[loc][x][y]==5)
		{
			cout<<"���ڵ���ʯͷ��"<<endl;
			game[loc][x][y]=1;
		}
		else if(game[loc][x][y]==6)
		{
			cout<<"���ڵ���ú��"<<endl;
			player[cur].score+=3*player[cur].mul/10;
			game[loc][x][y]=1;
		}
		else if(game[loc][x][y]==7)
		{
			cout<<"���ڵ�������"<<endl;
			player[cur].score+=8*player[cur].mul/10;
			game[loc][x][y]=1;
		}
		else if(game[loc][x][y]==8)
		{
			cout<<"���ڵ��˽��"<<endl;
			player[cur].score+=24*player[cur].mul/10;
			game[loc][x][y]=1;
		}
		else if(game[loc][x][y]==9)
		{
			cout<<"���ڵ�����ʯ��"<<endl;
			player[cur].score+=64*player[cur].mul/10;
			game[loc][x][y]=1;
		}
		else if(game[loc][x][y]==10)
		{
			cout<<"���ڵ��˺챦ʯ��"<<endl;
			wait;
			int tmp=rand()%5+1;
			player[cur].health+=tmp;
			cout<<"��ϲ�㣬����� "<<tmp<<" ������ֵ��"<<endl;
			game[loc][x][y]=1;
		}
		else if(game[loc][x][y]==11)
		{
			cout<<"���ڵ����̱�ʯ��"<<endl;
			wait;
			int tmp=rand()%10+1;
			player[cur].mul+=tmp;
			cout<<"��ϲ�㣬����� "<<tmp/10<<"."<<tmp%10<<" �㱶��������"<<endl;
			game[loc][x][y]=1;
		}
		else if(game[loc][x][y]==12)
		{
			cout<<"���ڵ�������ʯ��"<<endl;
			wait;
			int tmp=rand()%30+1;
			player[cur].ign=min(90,player[cur].ign+tmp);
			cout<<"��ϲ�㣬����� "<<tmp<<"% �������ʣ�"<<endl;
			game[loc][x][y]=1;
		}
		else
		{
			if(loc==0)
				cout<<"�㴫�͵��˵�����"<<endl;
			else
				cout<<"�㴫�͵��������硣"<<endl;
			player[cur].health=max(0,player[cur].health-1);
			player[cur].locate=1-player[cur].locate;
		}
		wait;
		if(player[cur].health==0)
		{
			sur--;
			cout<<"����������"<<endl;
			wait; 
		}
		while(checklava(loc));

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
