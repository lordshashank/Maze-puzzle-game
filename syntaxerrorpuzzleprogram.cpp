#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>

using namespace std;
int check=0;
class MAZE
{
	public:
		struct node
		{
			int x, y;
			struct node *next;
		};
		struct visit
		{
			int x, y;
			struct visit *next;
		};
		node *head;
		visit *head1;
		bool node_search(int, int);
		void add(int, int);
		void create();
		char **Maze;
		int row, col, dir, p[2], start[2], end[2];
		MAZE (int, int);
			MAZE (int, int, int, int);
			void set_right();
		void set_left();
		void move_right();
		void move_left();
		void show();
		bool is_solved();
		void user();
	
};
MAZE::MAZE (int r, int c, int a, int b)
{
	row = r;
	col = c;
dir=4;

	p[0] = a; p[1] = b;
	
	Maze = new char *[col];
			
	for (int n = 0; n < col; n++)
		Maze[n] = new char [row];
}


MAZE::MAZE (int r, int b)
{
	node *newnode;
	visit *newvisit;
	row = r - 2;
	col = b - 2;
	
	newnode = new node;
	newnode -> next = NULL;
	newvisit = new visit;
	newvisit -> next = NULL;
	
	Maze = new char *[col];
			
	for (int n = 0; n < col; n++)
		Maze[n] = new char [row];

	for (int n = 1; n <= row; ++n)
		for (int m = 1; m <= col; m++)
			Maze[n - 1][m - 1] = '#';
			

	newnode -> x = 0; newnode -> y = col - 1;
	newvisit -> x = 0; newvisit -> y = col - 1;	
	start[0] = newvisit -> x; start[1] = newvisit -> y;
	
	head = newnode;
	head1 = newvisit;
	
	Maze[newvisit -> x][newvisit -> y] = '.';
}

bool MAZE::node_search(int a, int b)
{
	int j = 0;
	visit *ptr = head1;

	while (ptr)	
	{
		if (ptr -> x == a && ptr -> y == b)
			j = 1;
		
		ptr = ptr -> next;
	}	
		
	return (j == 1 ? true : false);
}

void MAZE::add(int a, int b)
{
	node *newnode, *ptr;
	visit *newvisit, *visitptr;
		
	newnode = new node;
	newnode -> x = a;
	newnode -> y = b;
	newvisit = new visit;
	newvisit -> x = a;
	newvisit -> y = b;
	newnode -> next = NULL;
	newvisit -> next = NULL;
	ptr = head;
	visitptr = head1;
		
	while (ptr -> next)
		ptr = ptr -> next;
			
	ptr -> next = newnode;
	
	while (visitptr -> next)
		visitptr = visitptr -> next;
			
	visitptr -> next = newvisit;
}

void MAZE::create()
{
	node *ptr = head;
	
	int a, b, c, j = 1;
	
	while (j < ((row * col) % 2 == 1 ? ((row + 1) * (col + 1)) / 4 : (row * col) / 4))
	{
		a = 0; b = 1;
		while (a == 0 && !(b % 2 == 0 && b % 3 == 0 && b% 5 == 0 && b % 7 == 0))
		{
			c = rand() % 4;
			
			switch (c)
			{
				case 0 :
					{
						if (!(*this).node_search(ptr -> x - 2, ptr -> y) && (ptr -> x != 1 && ptr -> x != 0 && ptr -> x != -1))
						{	
							(*this).add(ptr -> x - 2, ptr -> y);				
							(*this).Maze[ptr -> x - 1][ptr -> y] = '.';
							(*this).Maze[ptr -> x - 2][ptr -> y] = '.';	
							a = 1;
							j++;
						}	
						else b *= 2;				
						break;
					}
				
				case 1 :
					{
						if (!(*this).node_search(ptr -> x, ptr -> y + 2) && (ptr -> y != col - 2 && ptr -> y != col - 1 && ptr -> y != col))
						{
							(*this).add(ptr -> x, ptr -> y + 2);
							(*this).Maze[ptr -> x][ptr -> y + 1] = '.';
							(*this).Maze[ptr -> x][ptr -> y + 2] = '.';						
							a = 1;
							j++;
						}
						else b*= 3;
						break;
					}
					
				case 2 :
					{
						if (!(*this).node_search(ptr -> x + 2, ptr -> y) && (ptr -> x != row - 2 && ptr -> x != row - 1 && ptr -> x != row))
						{
							(*this).add(ptr -> x + 2, ptr -> y);													
							(*this).Maze[ptr -> x + 1][ ptr -> y] = '.';	
							(*this).Maze[ptr -> x + 2][ ptr -> y] = '.';							
							a = 1;
							j++;
						}
						else b*= 5;
						break;
					}
					
				case 3 :
					{
						if (!(*this).node_search(ptr -> x, ptr -> y - 2) && (ptr -> y != 1 &&ptr -> y != 0 && ptr -> y != -1))
						{
							(*this).add(ptr -> x, ptr -> y - 2);													
							(*this).Maze[ptr -> x][ptr -> y- 1] = '.';
							(*this).Maze[ptr -> x][ptr -> y - 2] = '.';													
							a = 1;
							j++;
						}
						else b*= 7;
						break;
					}
			}
		}
		
		if (b % 2 == 0 && b % 3 == 0 && b% 5 == 0 && b % 7 == 0)
			while (((*this).node_search(ptr -> x - 2, ptr -> y) || ptr -> x == 1 || ptr -> x == 0 || ptr -> x == -1) && ((*this).node_search(ptr -> x, ptr -> y + 2) || ptr -> y == col - 2 || ptr -> y == col - 1 || ptr -> y == col) && ((*this).node_search(ptr -> x + 2, ptr -> y) || ptr -> x == row - 2 || ptr -> x == row - 1 || ptr -> x == row) && ((*this).node_search(ptr -> x, ptr -> y - 2) || ptr -> y == 1 ||ptr -> y == 0 || ptr -> y == -1))
			{
				ptr = head;
				
				while (ptr -> next -> next)
					ptr = ptr -> next;
					
				delete ptr -> next;
				ptr -> next = NULL;
			}
		else ptr = ptr -> next;
	}
}
	
void MAZE::show ()
{
	HANDLE console_color;
    console_color = GetStdHandle(
        STD_OUTPUT_HANDLE);
	for (int n = 1; n <= row; ++n)
	{
		for (int m = 1; m <= col; m++)
		{
			if(Maze[n - 1][m - 1]=='@')
			{
				SetConsoleTextAttribute(
            console_color, 381);
				cout << Maze[n - 1][m - 1] << "   ";
				SetConsoleTextAttribute(
            console_color, 368);	
			}
		else if(Maze[n - 1][m - 1]=='#')
			{
				SetConsoleTextAttribute(
            console_color, 369);
				cout << Maze[n - 1][m - 1] << "   ";
				SetConsoleTextAttribute(
            console_color, 368);	
			}
			else
			cout << Maze[n - 1][m - 1] << "   ";
				
			if (m == col)
				cout << endl;
		}	
	}
	
	cout << endl;
}
bool check_left(MAZE &A)
{
	if (A.dir == 1)
		return (A.Maze[A.p[0]][A.p[1] - 1] == '#' ? true : false);
	else
	if (A.dir == 2)
		return (A.Maze[A.p[0] - 1][A.p[1]] == '#' ? true : false);
	else
	if (A.dir == 3)
		return (A.Maze[A.p[0]][A.p[1] + 1] == '#' ? true : false);
	else return (A.Maze[A.p[0] + 1][A.p[1]] == '#' ? true : false);
}

bool check_right(MAZE &A)
{
	if (A.dir == 1)
		return (A.Maze[A.p[0]][A.p[1] + 1] == '#' ? true : false);
	else
	if (A.dir == 2)
		return (A.Maze[A.p[0] + 1][A.p[1]] == '#' ? true : false);
	else
	if (A.dir == 3)
		return (A.Maze[A.p[0]][A.p[1] - 1] == '#' ? true : false);
	else return (A.Maze[A.p[0] - 1][A.p[1]] == '#' ? true : false);
}

bool check_top(MAZE &A)
{
	if (A.dir == 1)
		return (A.Maze[A.p[0] - 1][A.p[1]] == '#' ? true : false);
	else
	if (A.dir == 2)
		return (A.Maze[A.p[0]][A.p[1] + 1] == '#' ? true : false);
	else
	if (A.dir == 3)
		return (A.Maze[A.p[0] + 1][A.p[1]] == '#' ? true : false);
	else return (A.Maze[A.p[0]][A.p[1] - 1] == '#' ? true : false);
}

void MAZE::set_left()
{
	if (check_left((*this)) && check_top((*this)))
	{
		if (check_right((*this)))
		{
			dir += 2;
			Maze[p[0]][p[1]] = '.';
		}
		else dir += 1;
	}
	else
	if (check_top((*this)) || (!check_top((*this)) && !check_left((*this))))
		dir += 3;
	
	if (dir > 4)
		dir -= 4; 
	
	dir == 1 ? p[0] -= 1 : dir == 2 ? p[1] += 1 : dir == 3 ? p[0] += 1 : p[1] -= 1;
}

void MAZE::set_right()
{
	if (check_right((*this)) && check_top((*this)))
	{
		if (check_left((*this)))
		{
			dir += 2;
			Maze[p[0]][p[1]] = '.';
		}	
		else dir += 3;
	}
	else
	if (check_top((*this)) || (!check_top((*this)) && !check_right((*this))))
		dir += 1;
	
	if (dir > 4)
		dir -= 4; 
	
	dir == 1 ? p[0] -= 1 : dir == 2 ? p[1] += 1 : dir == 3 ? p[0] += 1 : p[1] -= 1;
}

void MAZE::move_left()
{
	if (Maze[p[0]][p[1]] != '@')
		Maze[p[0]][p[1]] = '@';
	else
	{
		int a[2] = {p[0], p[1]}, b = dir;
		
		(*this).set_left();
		
		if (Maze[p[0]][p[1]] == '@')
			Maze[a[0]][a[1]] = '.';
			
		p[0] = a[0]; p[1] = a[1];
		dir = b;
	}
}

void MAZE::move_right()
{
	if (Maze[p[0]][p[1]] != '@')
		Maze[p[0]][p[1]] = '@';
	else
	{
		int a[2] = {p[0], p[1]}, b = dir;
		
		(*this).set_right();
		
		if (Maze[p[0]][p[1]] == '@')
			Maze[a[0]][a[1]] = '.';
			
		p[0] = a[0]; p[1] = a[1];
		dir = b;
	}
}

bool MAZE::is_solved()
{
	if (p[0] == 0 || p[0] == row - 1 || p[1] == 0 || p[1] == col - 1)	
		return true;
	else return false;
}
void MAZE::user()
{
		cout<<"enter \nA to move left\nD to move right\nW to move up\nS to move down\nG to give up\n";
	char move,temp;
	cin>>move;
	temp=move;
	move=toupper(temp);
	
		switch (move)
	{
		case 'D':
			if (Maze[p[0]][p[1]+1]=='.')
			{
				Maze[p[0]][p[1]+1]='@';
				p[1]+=1;
						system("cls");
	show();
			Sleep(100);
			}
			else if (Maze[p[0]][p[1]+1]=='@')
			{
				Maze[p[0]][p[1]]='.';
				p[1]+=1;
						system("cls");
	show();
			Sleep(100);
			}
			else
			{
				cout<<"WRONG INPUT\n";
			}
			break;
		case 'A':
			if (Maze[p[0]][p[1]-1]=='.')
			{
				Maze[p[0]][p[1]-1]='@';
				p[1]-=1;
						system("cls");
	show();
			Sleep(100);
	
			}
			else if (Maze[p[0]][p[1]-1]=='@')
			{
				Maze[p[0]][p[1]]='.';
				p[1]-=1;
						system("cls");
	show();
			Sleep(100);
	
			}
			else
			{
				cout<<"WRONG INPUT\n";
			}
			break;
		case 'W':
			if (Maze[p[0]-1][p[1]]=='.')
			{
				Maze[p[0]-1][p[1]]='@';
				p[0]-=1;
						system("cls");
	show();
			Sleep(100);
	
			}
		else if (Maze[p[0]-1][p[1]]=='@')
			{
				Maze[p[0]][p[1]]='.';
				p[0]-=1;
						system("cls");
	show();
			Sleep(100);
	
			}
			else
			{
				cout<<"WRONG INPUT\n";
			}
			break;
		case 'S':
			if (Maze[p[0]+1][p[1]]=='.')
			{
				Maze[p[0]+1][p[1]]='@';
				p[0]+=1;
						system("cls");
	show();
			Sleep(100);
	
			}
			else if (Maze[p[0]+1][p[1]]=='@')
			{
				Maze[p[0]][p[1]]='.';
				p[0]+=1;
						system("cls");
	show();
			Sleep(100);
	
			}
			else
			{
				cout<<"WRONG INPUT\n";
			}
			break;
			case 'G':
				check=1;
				break;
		default:
			cout<<"PLEASE ENTER THE VALID LETTER\n";
	}

}

int main ()
{
	HANDLE console_color;
    console_color = GetStdHandle(
        STD_OUTPUT_HANDLE);
	srand(time(0));
	system ("color 7f");
		SetConsoleTextAttribute(
            console_color, 368);
	int r,c;
	cout<<"\t\t\t***THIS IS THE MAZE PUZZLE GAME***\n\nInstructions:\n\n1) You are recommended to run this in full screen mode\n2) Complete the maze and finish at the bottom left corner (If you can!!!)\n3) If the maze is large (dimension > 29), reducing console font size is recommended to prevent overlapping (assuming font size as 20)\n4) You may give up if you wish at any time by entering g\n\n***************************************************************************************************************";
	cout<<"\nPress 1 for a quick game\nPress 2 to specify the dimension of the square puzzle yourself\n";
	cin>>c;
	switch (c)
	{
		case 1:
			{
				cout<<"\nPress 1 for easy\nPress 2 for medium\nPress 3 for hard\n";
				int l;
				cin>>l;
				switch (l)
				{
					case 1:
						r=7;
						break;
					case 2:
						r=15;
						break;
					case 3:
						r=23;
					default:
						cout<<"Invalid input";			
				}
				break;
			}
		case 2:
			{
				cout<<"\nEnter the dimension : ";
				cin>>r;
				break;
			}
		default:
			cout<<"Invalid input";
				
			
	}
	if (r%2==0)
	{
		r++;
	}
	cout << endl;
	
	MAZE A(r, r);
	
	A.create();

	char *B[r];
	
	for (int n = 0; n < r; n++)
		B[n] = new char [r];
		
	for (int n = 1; n <= r; ++n)
		for (int m = 1; m <= r; m++)
			B[n - 1][m - 1] = '#';
			
	for (int n = 1; n <= r - 2; ++n)
		for (int m = 1; m <= r - 2; m++)
			B[n][m] = A.Maze[n - 1][m - 1];
	B[1][r - 1] = '@'; B[r - 2][0] = '.';
		
	for (int n = 1; n <= r; ++n)
	{
		for (int m = 1; m <= r; m++)
		{
				if(B[n - 1][m - 1]=='@')
			{
				SetConsoleTextAttribute(
            console_color, 370);
				cout << B[n - 1][m - 1] << "   ";
				SetConsoleTextAttribute(
            console_color, 368);	
			}
			else	if(B[n - 1][m - 1]=='#')
			{
				SetConsoleTextAttribute(
            console_color, 369);
				cout << B[n - 1][m - 1] << "   ";
				SetConsoleTextAttribute(
            console_color, 368);	
			}
			else
			cout << B[n - 1][m - 1] << "   ";
		
				
			if (n == 2 && m == r)
				cout << "<= START HERE!!!";
			if (m == r)
				cout << endl;
		}	
	}
	
	cout << endl;
	MAZE Z(r,r,1,r-1);
	Z.Maze=B;
	MAZE p(r,r,1,r-1);
	char f[r][r];
	for (int i=0;i<r;i++)
	{
			for (int j=0;j<r;j++)
	{
		p.Maze[i][j]=B[i][j];
	}		
	}


	while(p.Maze[r-2][0]!='@')
	{
		p.user();
		if(check==1)
			break;
	}
	if(p.Maze[r-2][0]=='@')
	{
		cout<<"CONGRATULATIONS!!! you have solved the puzzle\n";
	}
	Z.set_left();
	Z.move_left();
	
	while (!Z.is_solved())
	{
		Z.set_left();
		Z.move_left();
}
	
	cout << endl;
	cout<<"solution is\n";
		
	Z.show();
	return 0;
}
