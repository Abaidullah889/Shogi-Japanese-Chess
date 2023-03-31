#include<iostream>
#include<iomanip>
#include<conio.h>
#include<fstream>
#include<math.h>
#include<windows.h>
using namespace std;




                   /////////////////////////////AB PHASE 3 KI BARI PIECES Done(Complete)



void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void SetClr(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}
struct Position
{
	int ri,ci;
};
enum Color{white=0,black=1};
void Init (char**&B ,int &dim,string PNames[],int &Turn, char*&w,char*&black,int &Wsize,int &Bsize,char***&R, char** &white_replay, char** &black_replay,int*&turn_replay)
{
	char ans;
	gotoRowCol(50, 70);
	cout << "New Game || Load Game (N/L)";
	cin >> ans;

	R = new char** [1000] {};
	for (int i = 0; i < 1000; i++)
	{
		R[i] = new char*[dim] {};
		for (int k = 0; k < dim; k++)
		{
			R[i][k]= new char [dim] {};
		}
	}

	turn_replay = new int[1000];

	white_replay = new char* [1000];
	for (int j=0; j < 1000; j++)
	{
		white_replay[j] = new char[10];
	}
	black_replay = new char* [1000];
	for (int j = 0; j < 1000; j++)
	{
		black_replay[j] = new char[10];
	}

	if (ans == 'N')
	{
		ifstream rdr("input.txt");
		rdr >> dim;
		B = new char* [dim] {};
		for (int i = 0; i < dim; i++)
		{
			B[i] = new char[dim] {};
		}

		for (int r = 0; r < dim; r++)
		{
			for (int c = 0; c < dim; c++)
			{
				rdr >> B[r][c];
			}
		}
		
		w = new char[10];
		for (int i = 0; i < 10; i++)
		{
			rdr >> w[i];
		}
		black = new char[10];
		for (int i = 0; i < 10; i++)
		{
			rdr >> black[i];
		}

		Turn = white;

		for (int i = 0; i < 2; i++)
		{
			cout << "Enter the Name of " << i + 1 << "'s Player: ";
			cin >> PNames[i];
		}
	}
	if (ans == 'L')
	{
		ifstream rdr("Save.txt");
		rdr >> dim;
		B = new char* [dim] {};
		for (int i = 0; i < dim; i++)
		{
			B[i] = new char[dim] {};
		}

		for (int r = 0; r < dim; r++)
		{
			for (int c = 0; c < dim; c++)
			{
				rdr >> B[r][c];
			}
		}
		w = new char[10];
		rdr >> Wsize;
		for (int i = 0; i < 10; i++)
		{
			rdr >> w[i];
		}
		black = new char[10];
		rdr >> Bsize;
		for (int i = 0; i < 10; i++)
		{
			rdr >> black[i];
		}
		rdr >> Turn;
		rdr >> PNames[0];
		rdr >> PNames[1];
	}
	
	

	

	


	
    cout<<endl;
    
}
void PrintBoard(char**B,int dim)
{
	for(int r=0;r<dim;r++)
	{
		for(int c=0;c<dim;c++)
		{
		    cout<<B[r][c];
		}
		cout<<endl;
	}
}
void FindKing(char** B, int dim, int& Kr, int& Kc, int Turn)
{
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (Turn == 0)
			{
				if (B[r][c] == 'K')
				{
					Kr = r;
					Kc = c;
				}
			}
			if (Turn == 1)
			{
				if (B[r][c] == 'k')
				{
					Kr = r;
					Kc = c;
				}
			}

		}
	}

}
void TurnMsg(string Name)
{
	gotoRowCol(0, 80);
	cout<<Name<<"'s Turn";
}
void DrawPawn(Position Sc)
{
	gotoRowCol(Sc.ri - 2, Sc.ci - 1);
	cout << char(-37);
	gotoRowCol(Sc.ri - 2, Sc.ci + 2);
	cout << char(-37);

	gotoRowCol(Sc.ri - 1, Sc.ci - 1);
	{
		for (int i = 0; i < 4; i++)
		{
			cout << char(-37);
		}
	}
	gotoRowCol(Sc.ri, Sc.ci);
	for (int i = 0; i < 2; i++)
	{
		cout << char(-37);
	}
	gotoRowCol(Sc.ri + 1, Sc.ci - 2);
	for (int i = 0; i < 6; i++)
	{
		cout << char(-37);
	}
}
void DrawLance(Position Sc)
{
	gotoRowCol(Sc.ri, Sc.ci - 1);
	for (int i = 0; i < 3; i++)
	{
		cout << char(-37);
	}
	gotoRowCol(Sc.ri + 1, Sc.ci - 1);
	for (int i = 0; i < 3; i++)
	{
		cout << char(-37);
	}
	gotoRowCol(Sc.ri - 1, Sc.ci - 1);
	for (int i = 0; i < 3; i++)
	{
		cout << char(-37);
	}
	gotoRowCol(Sc.ri - 2, Sc.ci);
	cout << char(-37);
	gotoRowCol(Sc.ri - 3, Sc.ci);
	cout << char(-37);

	gotoRowCol(Sc.ri + 2, Sc.ci - 2);
	for (int i = 0; i < 5; i++)
	{
		cout << char(-37);
	}
}
void DrawRook(Position Sc)
{
	gotoRowCol(Sc.ri, Sc.ci - 1);
	for (int i = 0; i < 3; i++)
	{
		cout << char(-37);
	}
	gotoRowCol(Sc.ri + 1, Sc.ci - 1);
	for (int i = 0; i < 3; i++)
	{
		cout << char(-37);
	}
	gotoRowCol(Sc.ri + 2, Sc.ci - 2);
	for (int i = 0; i < 5; i++)
	{
		cout << char(-37);
	}
	gotoRowCol(Sc.ri - 1, Sc.ci);
	cout << char(-37);
	gotoRowCol(Sc.ri - 2, Sc.ci - 1);
	for (int i = 0; i < 3; i++)
	{
		cout << char(-37);
	}

	gotoRowCol(Sc.ri - 3, Sc.ci);
	cout << char(-37);


}
void DrawBishop(Position Sc)
{
	gotoRowCol(Sc.ri, Sc.ci - 1);
	for (int i = 0; i < 3; i++)
	{
		cout << char(-37);
	}
	gotoRowCol(Sc.ri + 1, Sc.ci - 1);
	for (int i = 0; i < 3; i++)
	{
		cout << char(-37);
	}
	gotoRowCol(Sc.ri + 2, Sc.ci - 2);
	for (int i = 0; i < 5; i++)
	{
		cout << char(-37);
	}
	gotoRowCol(Sc.ri - 1, Sc.ci - 1);
	cout << char(-37);
	gotoRowCol(Sc.ri - 2, Sc.ci);
	cout << char(-37);
	gotoRowCol(Sc.ri - 3, Sc.ci + 1);
	cout << char(-37);
	gotoRowCol(Sc.ri - 1, Sc.ci + 1);
	cout << char(-37);
	gotoRowCol(Sc.ri - 3, Sc.ci - 1);
	cout << char(-37);
}
void DrawSilver(Position Sc)
{
	gotoRowCol(Sc.ri-1, Sc.ci);
	cout << char(-37);
	gotoRowCol(Sc.ri, Sc.ci-1);
	for (int i = 0; i < 3; i++)
	{
		cout << char(-37);
	}
	gotoRowCol(Sc.ri+1, Sc.ci - 2);
	for (int i = 0; i < 5; i++)
	{
		cout << char(-37);
	}
}
void DrawGold(Position Sc)
{
	gotoRowCol(Sc.ri - 2, Sc.ci - 1);
	cout << char(-37);
	gotoRowCol(Sc.ri - 2, Sc.ci+1);
	cout << char(-37);
	gotoRowCol(Sc.ri - 1, Sc.ci);
	cout << char(-37);
	gotoRowCol(Sc.ri, Sc.ci - 1);
	for (int i = 0; i < 3; i++)
	{
		cout << char(-37);
	}
	gotoRowCol(Sc.ri + 1, Sc.ci - 2);
	for (int i = 0; i < 5; i++)
	{
		cout << char(-37);
	}
}
void DrawKnight(Position Sc)
{
	gotoRowCol(Sc.ri, Sc.ci - 2);
	for (int i = 0; i < 3; i++)
	{
		cout << char(-37);
	}
	gotoRowCol(Sc.ri + 1, Sc.ci - 1);
	for (int i = 0; i < 2; i++)
	{
		cout << char(-37);
	}
	gotoRowCol(Sc.ri + 2, Sc.ci);
	cout << char(-37);
	gotoRowCol(Sc.ri + 3, Sc.ci - 2);
	for (int i = 0; i < 6; i++)
	{
		cout << char(-37);
	}
	gotoRowCol(Sc.ri - 1, Sc.ci - 1);
	for (int i = 0; i < 4; i++)
	{
		cout << char(-37);
	}
	gotoRowCol(Sc.ri, Sc.ci + 2);
	cout << char(-37);
	cout << char(-37);
	gotoRowCol(Sc.ri - 2, Sc.ci);
	cout << char(-37);
}
void DrawKing(Position Sc)
{
	gotoRowCol(Sc.ri-3, Sc.ci-2);
	cout << char(-37);
	gotoRowCol(Sc.ri - 3, Sc.ci);
	cout << char(-37);
	gotoRowCol(Sc.ri - 3, Sc.ci+2);
	cout << char(-37);
	gotoRowCol(Sc.ri, Sc.ci);
	cout << char(-37);
	gotoRowCol(Sc.ri-1, Sc.ci-1);
	for (int i = 0; i < 3; i++)
	{
		cout << char(-37);
	}
	gotoRowCol(Sc.ri - 2, Sc.ci - 2);
	for (int i = 0; i < 5; i++)
	{
		cout << char(-37);
	}
	gotoRowCol(Sc.ri + 1, Sc.ci - 1);
	for (int i = 0; i < 3; i++)
	{
		cout << char(-37);
	}
	gotoRowCol(Sc.ri + 2, Sc.ci - 2);
	for (int i = 0; i < 5; i++)
	{
		cout << char(-37);
	}


}
void DrawPiece(char sym, int row, int col)
{
	Position Sc;
	
	

    if (sym == 'P')
	{
		Sc.ri = row;
		Sc.ci = col - 1;
		SetClr(246);
		DrawPawn(Sc);
	}
	else if (sym == '1')
	{
		Sc.ri = row;
		Sc.ci = col - 1;
		SetClr(245);
		DrawPawn(Sc);
	}
	else if (sym == '2')
	{
		Sc.ri = row;
		Sc.ci = col - 1;
		SetClr(4);
		DrawPawn(Sc);
	}
	else if (sym == 'p')
	{
		Sc.ri = row;
		Sc.ci = col - 1;
		SetClr(10);
		DrawPawn(Sc);
	}
	else if (sym == 'l')
	{
		Sc.ri = row;
		Sc.ci = col - 1;
		SetClr(10);
		DrawLance(Sc);
	}
	else if (sym == '5')
	{
		Sc.ri = row;
		Sc.ci = col - 1;
		SetClr(245);
		DrawLance(Sc);
	}
	else if (sym == '6')
	{
		Sc.ri = row;
		Sc.ci = col - 1;
		SetClr(4);
		DrawLance(Sc);
	}
	else if (sym == 'L')
	{
		Sc.ri = row;
		Sc.ci = col - 1;
		SetClr(246);
		DrawLance(Sc);
	}
	else if (sym == 'r')
	{
		Sc.ri = row;
		Sc.ci = col - 1;
		SetClr(10);
		DrawRook(Sc);
	}
	else if (sym == 'Z')
	{
		Sc.ri = row;
		Sc.ci = col - 1;
		SetClr(245);
		DrawRook(Sc);
	}
	else if (sym == 'z')
	{
		Sc.ri = row;
		Sc.ci = col - 1;
		SetClr(4);
		DrawRook(Sc);
	}
	else if (sym == 'R')
	{
		Sc.ri = row;
		Sc.ci = col - 1;
		SetClr(246);
		DrawRook(Sc);
	}
	else if (sym == 'b')
	{
		Sc.ri = row;
		Sc.ci = col - 1;
		SetClr(10);
		DrawBishop(Sc);
	}
	else if (sym == 'Y')
	{
		Sc.ri = row;
		Sc.ci = col - 1;
		SetClr(245);
		DrawBishop(Sc);
	}
	else if (sym == 'y')
	{
		Sc.ri = row;
		Sc.ci = col - 1;
		SetClr(4);
		DrawBishop(Sc);
	}
	else if (sym == 'B')
	{
		Sc.ri = row;
		Sc.ci = col - 1;
		SetClr(246);
		DrawBishop(Sc);
	}
	else if (sym == 'n')
	{
		Sc.ri = row-1;
		Sc.ci = col - 1;

		SetClr(10);
		DrawKnight(Sc);
	}
	else if (sym == '3')
	{
		Sc.ri = row - 1;
		Sc.ci = col - 1;

		SetClr(245);
		DrawKnight(Sc);
	}
	else if (sym == '4')
	{
		Sc.ri = row - 1;
		Sc.ci = col - 1;

		SetClr(4);
		DrawKnight(Sc);
	}
	else if (sym == 'N')
	{
		Sc.ri = row-1;
		Sc.ci = col - 1;

		SetClr(246);
		DrawKnight(Sc);
	}
	else if (sym == 's')
	{
		Sc.ri = row;
		Sc.ci = col;
		SetClr(10);
		DrawSilver(Sc);
	}
	else if (sym == '7')
	{
		Sc.ri = row;
		Sc.ci = col;
		SetClr(245);
		DrawSilver(Sc);
	}
	else if (sym == '8')
	{
		Sc.ri = row;
		Sc.ci = col;
		SetClr(4);
		DrawSilver(Sc);
	}
	else if (sym == 'S')
	{
		Sc.ri = row;
		Sc.ci = col;
		SetClr(246);
		DrawSilver(Sc);
	}
	else if (sym == 'g')
	{
		Sc.ri = row;
		Sc.ci = col;
		SetClr(10);
		DrawGold(Sc);
	}
	else if (sym == 'G')
	{
		Sc.ri = row;
		Sc.ci = col;
		SetClr(246);
		DrawGold(Sc);
	}
	else if (sym == 'k')
	{
		Sc.ri = row;
		Sc.ci = col;
		SetClr(10);
		DrawKing(Sc);
	}
	else if (sym == 'K')
	{
		Sc.ri = row;
		Sc.ci = col;
		SetClr(246);
		DrawKing(Sc);
	}
}
void SelectPos(Position &Sc,int dim,int r,int c)
{
	int ri=0, ci=0;
	getRowColbyLeftClick(ri,ci);
	Sc.ci=ci / c;
	Sc.ri=ri / r;
}
void TurnChange(int &Turn)
{
	if(Turn==black)
	{
		Turn=white;
	}
	else
	{
		Turn=black;
	}
}
bool IsWhitePiece(char sym)
{
	return sym >='A' && sym <='Z' || sym=='1' || sym == '3' || sym == '5' || sym == '7';
}
bool IsBlackPiece(char sym)
{
	return sym >='a' && sym <='z' || sym == '2' || sym == '4' || sym == '6' || sym == '8';
}
bool IsMyPiece(char sym,int Turn)
{
	if(Turn==black)
	{
		return IsBlackPiece(sym);
	}
	else
	{
		return IsWhitePiece(sym);
	}
	
}
bool IsValid(char**B,Position Sc,int dim,int Turn)
{
	if(Sc.ri<0 || Sc.ri>=dim || Sc.ci<0 || Sc.ci>=dim)
	{
		return false;
	}
	
	return IsMyPiece(B[Sc.ri][Sc.ci],Turn);
	
}
void UpdateBoard(char** &B,char* &w,char*b,Position Sc,Position Dc,int &Wsize,int &Bsize)
{
	if (Sc.ci <= 8)
	{
		char sym = B[Sc.ri][Sc.ci];
		B[Dc.ri][Dc.ci] = sym;
		B[Sc.ri][Sc.ci] = '-';
	}

	if (Sc.ci >= 10 && Sc.ri==1)
	{
		if (Sc.ci == 10)
		{
			char sym = w[0];
			B[Dc.ri][Dc.ci] = sym;
			w[0] = '-';
			
		}
		if (Sc.ci == 11)
		{
			char sym = w[1];
			B[Dc.ri][Dc.ci] = sym;
			w[1] = '-';
			
		}
		if (Sc.ci == 12)
		{
			char sym = w[2];
			B[Dc.ri][Dc.ci] = sym;
			w[2] = '-';
			
		}
		if (Sc.ci == 13)
		{
			char sym = w[3];
			B[Dc.ri][Dc.ci] = sym;
			w[3] = '-';
			
		}
		if (Sc.ci == 14)
		{
			char sym = w[4];
			B[Dc.ri][Dc.ci] = sym;
			w[4] = '-';
			
		}
		if (Sc.ci == 15)
		{
			char sym = w[5];
			B[Dc.ri][Dc.ci] = sym;
			w[5] = '-';
			
		}
		if (Sc.ci == 16)
		{
			char sym = w[6];
			B[Dc.ri][Dc.ci] = sym;
			w[6] = '-';
			
		}
		if (Sc.ci == 17)
		{
			char sym = w[7];
			B[Dc.ri][Dc.ci] = sym;
			w[7] = '-';
			
		}
		if (Sc.ci == 18)
		{
			char sym = w[8];
			B[Dc.ri][Dc.ci] = sym;
			w[8] = '-';
			
		}
		if (Sc.ci == 19)
		{
			char sym = w[9];
			B[Dc.ri][Dc.ci] = sym;
			w[9] = '-';
			
		}
	}


	if (Sc.ci >= 10 && Sc.ri == 3)
	{
		if (Sc.ci == 10)
		{
			char sym = b[0];
			B[Dc.ri][Dc.ci] = sym;
			b[0] = '-';
			
		}
		if (Sc.ci == 11)
		{
			char sym = b[1];
			B[Dc.ri][Dc.ci] = sym;
			b[1] = '-';
			
		}
		if (Sc.ci == 12)
		{
			char sym = b[2];
			B[Dc.ri][Dc.ci] = sym;
			b[2] = '-';
			
		}
		if (Sc.ci == 13)
		{
			char sym = b[3];
			B[Dc.ri][Dc.ci] = sym;
			b[3] = '-';
			
		}
		if (Sc.ci == 14)
		{
			char sym = b[4];
			B[Dc.ri][Dc.ci] = sym;
			b[4] = '-';
			
		}
		if (Sc.ci == 15)
		{
			char sym = b[5];
			B[Dc.ri][Dc.ci] = sym;
			b[5] = '-';
			
		}
		if (Sc.ci == 16)
		{
			char sym = b[6];
			B[Dc.ri][Dc.ci] = sym;
			b[6] = '-';
			
		}
		if (Sc.ci == 17)
		{
			char sym = b[7];
			B[Dc.ri][Dc.ci] = sym;
			b[7] = '-';
			
		}
		if (Sc.ci == 18)
		{
			char sym = b[8];
			B[Dc.ri][Dc.ci] = sym;
			b[8] = '-';
			
		}
		if (Sc.ci == 19)
		{
			char sym = b[9];
			B[Dc.ri][Dc.ci] = sym;
			b[9] = '-';
			
		}
	}
	int countW = 0;
	for (int i = 0; i < 10; i++)
	{
		if (w[i]=='-')
		{
			countW++;
		}
		if (countW == 10)
		{
			Wsize = 0;
		}
	}

	int countB = 0;
	for (int i = 0; i < 10; i++)
	{
		if (b[i] == '-')
		{
			countB++;
		}
		if (countB == 10)
		{
			Bsize = 0;
		}
	}
	
}
void Box(int r,int c,int row,int col,int color,int dr,int dc,int Turn,char sym)
{
	
	int R,C;
	float mr,mc;
	for(int ri=0;ri<row;ri++)
	{
		for(int ci=0;ci<col;ci++)
		{
			R=ri+r;
			C=ci+c;
			mr=(row/2.0)+r;
			mc=(col/2.0)+c;
			SetClr(color);
			gotoRowCol(R,C);
			cout<<char(-37);
			if((R=mr) && (C=mc))
			{
				
				
				gotoRowCol(R,C);
				if(sym=='-')
				{
					if ((dr + dc) % 2 == 0)
					{
						SetClr(15);
						cout << char(-37);
					}
					else
					{
						SetClr(8);
						cout << char(-37);
					}
					
				}
				else
				{
					DrawPiece(sym, R, C);
				}
			}
		}
	}
}////
void Board(int Dim,int rows,int cols,char**B,int Turn)
{
	for(int r=0;r<Dim;r++)
	{
		for(int c=0;c<Dim;c++)
		{
			if((r+c)%2==0)
			{
				Box(r*rows,c*cols,rows,cols,15,r,c,Turn,B[r][c]);
			}
			else
			{
				Box(r*rows,c*cols,rows,cols,8,r,c,Turn,B[r][c]);
			}
		}
	}
}
bool IsHorizontal(Position Sc,Position Dc)
{
    return (Sc.ri == Dc.ri); 
}
bool IsVertical(Position Sc, Position Dc)
{
	return (Sc.ci == Dc.ci); 
	
}
bool IsDiagonal(Position Sc, Position Dc)
{
	int Dr = abs(Sc.ri - Dc.ri);
	int dc = abs(Sc.ci - Dc.ci);

	return Dr==dc;
}
bool IsHorizontalPathClear(char ** B, Position Sc, Position Dc)
{
	int cs, ce;
	if (Sc.ci < Dc.ci)
	{
		cs = Sc.ci + 1;
		ce = Dc.ci - 1;
	}
	else
	{
		cs = Dc.ci + 1;
		ce = Sc.ci - 1;
	}

	for (int i = cs; i <= ce; i++)
	{
		if (B[Sc.ri][i] != '-')
		{
			return false;
		}
	}
	return true;
}
bool IsVerticalPathClear(char** B, Position Sc, Position Dc)
{
	if (Sc.ri < Dc.ri)
	{
		for (int i = Sc.ri+1; i < Dc.ri; i++)
	     { 
			if (B[i][Sc.ci] != '-')
			{
				return false;
			}
	    }
	}
	else
	{
		for (int i = Sc.ri-1; i > Dc.ri; i--)
	     { 
			if (B[i][Sc.ci] != '-')
			{
				return false;
			}
	    }
	}
	return true;
}
bool IsDiagonalL2R(char** B, Position Sc, Position Dc)
{
	if (Sc.ri < Dc.ri)
	{
		int Dr = Dc.ri - Sc.ri;

		for (int i = 1; i < Dr; i++)
		{
			if (B[Sc.ri + i][Sc.ci + i] != '-')
				return false;
		}
		return true;
	}
	else 
	{
		int Dr = Sc.ri - Dc.ri;

		for (int i = 1; i < Dr; i++)
		{
			if (B[Sc.ri - i][Sc.ci - i] != '-')
				return false;
		}
		return true;
	}

}
bool IsDiagonalR2L (char** B, Position Sc, Position Dc)
{
	
	if (Sc.ri < Dc.ri)
	{
		int Dr = Dc.ri - Sc.ri;
		for (int i = 1; i < Dr; i++)
		{
			if (B[Sc.ri + i][Sc.ci - i] != '-')
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		int Dr = Sc.ri - Dc.ri;
		for (int i = 1; i < Dr; i++)
		{
			if (B[Sc.ri - i][Sc.ci + i] != '-')
			{
				return false;
			}
		}
		return true;
	}
}
bool (IsDiagonalPathClear(char** B, Position Sc, Position Dc))
{
	int Dr = Sc.ri - Dc.ri;
	int dc = Sc.ci - Dc.ci;
	
	if(Dr==dc)
	{
		return IsDiagonalL2R(B,Sc,Dc);
	}
	return IsDiagonalR2L(B, Sc, Dc);

}
bool Rooklegality(char**B,Position Sc,Position Dc)
{
	return ((IsHorizontal(Sc,Dc) && IsHorizontalPathClear(B,Sc,Dc)) || (IsVertical(Sc,Dc) && IsVerticalPathClear(B,Sc,Dc)));
}
bool pawnlegality(char**B,Position Sc,Position Dc)
{
	if(!(IsVertical(Sc,Dc) && IsVerticalPathClear(B,Sc,Dc)))
	{
		return false;
	}
	
	if(Dc.ri==Sc.ri-1)
	{
		return false;
	}
	return Dc.ri==Sc.ri+1;
}
bool Pawnlegality(char**B,Position Sc,Position Dc)
{
	if(!(IsVertical(Sc,Dc) && IsVerticalPathClear(B,Sc,Dc)))
	{
		return false;
	}
	
	if(Dc.ri==Sc.ri+1)
	{
		return false;
	}
	return Dc.ri==Sc.ri-1;
}
bool Bishoplegality(char**B,Position Sc,Position Dc)
{
	return (IsDiagonal(Sc,Dc) && IsDiagonalPathClear(B,Sc,Dc));
}
bool knightlegality(char** B,Position Sc,Position Dc)
{
	int dc=abs(Dc.ci-Sc.ci);
	int Dr=Dc.ri-Sc.ri;
	if(Dr==2 && dc==1)
	{
		return true;
	}
	return false;
}
bool Knightlegality(char** B,Position Sc,Position Dc)
{
	int dc=abs(Dc.ci-Sc.ci);
	int Dr=(Dc.ri-Sc.ri);
	if(Dr==-2 && dc==1)
	{
		return true;
	}
	return false;
}
bool lancelegality(char** B,Position Sc,Position Dc)
{
	if(IsVertical(Sc,Dc) && IsVerticalPathClear(B,Sc,Dc) && Dc.ri>Sc.ri)
	{
		return true;
	}
	return false;
}
bool Lancelegality(char** B,Position Sc,Position Dc)
{
	if(IsVertical(Sc,Dc) && IsVerticalPathClear(B,Sc,Dc) && Dc.ri<Sc.ri)
	{
		return true;
	}
	return false;
}
bool Silverlegality(char** B,Position Sc,Position Dc)
{
	int Dr=Dc.ri-Sc.ri;
	int dc=abs(Dc.ci-Sc.ci);
	
	if ((dc == 1) && (IsDiagonal(Sc,Dc)))
	{
		return true;
	}
	if(IsVertical(Sc,Dc) && Dr==-1)
	{
		return true;
	}
	return false;

}
bool silverlegality(char** B,Position Sc,Position Dc)
{
	int Dr=Dc.ri-Sc.ri;
	int dc=abs(Dc.ci-Sc.ci);
	if(IsDiagonal(Sc,Dc) && dc==1 )
	{
		return true;
	}
	if(IsVertical(Sc,Dc) && Dr==1)
	{
		return true;
	}
	return false;
}
bool Goldlegality(char** B,Position Sc,Position Dc)
{
	int Dr=Dc.ri-Sc.ri;
	int dc=Dc.ci-Sc.ci;
	
	if(IsDiagonal(Sc,Dc) && dc==-1 && Dr==-1)
	{
		return true;
	}
	if(IsDiagonal(Sc,Dc) && dc==1 && Dr==-1)
	{
		return true;
	}
	if(IsVertical(Sc,Dc) && (Dr==1 || Dr==-1))
	{
		return true;
	}
	if(IsHorizontal(Sc,Dc) && (dc==1 || dc==-1))
	{
		return true;
	}
	return false;
	
}
bool goldlegality(char** B,Position Sc,Position Dc)
{
	int Dr=Dc.ri-Sc.ri;
	int dc=Dc.ci-Sc.ci;
	
	if(IsDiagonal(Sc,Dc) && dc==1 && Dr==1)
	{
		return true;
	}
	if(IsDiagonal(Sc,Dc) && dc==-1 && Dr==1)
	{
		return true;
	}
	if(IsVertical(Sc,Dc) && (Dr==1 || Dr==-1))
	{
		return true;
	}
	if(IsHorizontal(Sc,Dc) && (dc==1 || dc==-1))
	{
		return true;
	}
	return false;
	
}
bool Kinglegality(char** B,Position Sc,Position Dc)
{
	int Dr=abs(Dc.ri-Sc.ri);
	int dc=abs(Dc.ci-Sc.ci);
	
	if(IsDiagonal(Sc,Dc) && dc==1)
	{
		return true;
	}
	if(IsVertical(Sc,Dc) && Dr==1)
	{
		return true;
	}
	if(IsHorizontal(Sc,Dc) && dc==1)
	{
		return true;
	}
	return false;
}
bool PromotedBishop(char** B, Position Sc, Position Dc)
{
	int Dr = abs(Dc.ri - Sc.ri);
	int dc = abs(Dc.ci - Sc.ci);

	if (IsDiagonal(Sc, Dc) && IsDiagonalPathClear(B, Sc, Dc))
	{
		return true;
	}
	if (IsVertical(Sc, Dc) && Dr == 1)
	{
		return true;
	}
	if (IsHorizontal(Sc, Dc) && dc == 1)
	{
		return true;
	}
	return false;
}
bool PromotedRook(char** B, Position Sc, Position Dc)
{
	int Dr = abs(Dc.ri - Sc.ri);
	int dc = abs(Dc.ci - Sc.ci);

	if (IsDiagonal(Sc, Dc) && dc == 1)
	{
		return true;
	}
	if (IsVertical(Sc, Dc) && IsVerticalPathClear(B, Sc, Dc))
	{
		return true;
	}
	if (IsHorizontal(Sc, Dc) && IsHorizontalPathClear(B, Sc, Dc))
	{
		return true;
	}
	return false;
}
bool IslegalMove(char** B, Position Sc, Position Dc,int dim)
{
	switch(B[Sc.ri][Sc.ci])
	{
		case'R':
		case'r':
		    return Rooklegality(B,Sc,Dc);
		case'p':
			return pawnlegality(B,Sc,Dc);
		case'P':
			return Pawnlegality(B,Sc,Dc);
		case'B':
		case'b':
			return Bishoplegality(B,Sc,Dc);
		case'L':
			return Lancelegality(B,Sc,Dc);
		case'l':
			return lancelegality(B,Sc,Dc);
			
		case'N':
			return Knightlegality(B,Sc,Dc);
		case'n':
			return knightlegality(B,Sc,Dc);
		case'S':
			return Silverlegality(B,Sc,Dc);
		case's':
			return silverlegality(B,Sc,Dc);
		case'G':
			return Goldlegality(B,Sc,Dc);
		case'g':
			return goldlegality(B,Sc,Dc);
		case'K':
		case'k':
			return Kinglegality(B,Sc,Dc);
		case'1':
			return Goldlegality(B, Sc, Dc);
		case'2':
			return goldlegality(B, Sc, Dc);
		case'3':
			return Goldlegality(B, Sc, Dc);
		case'4':
			return goldlegality(B, Sc, Dc);
		case'5':
			return Goldlegality(B, Sc, Dc);
		case'6':
			return goldlegality(B, Sc, Dc);
		case'7':
			return Goldlegality(B, Sc, Dc);
		case'8':
			return goldlegality(B, Sc, Dc);
		case'Y':
		case'y':
			return PromotedBishop(B, Sc, Dc);
		case'Z':
		case'z':
			return PromotedRook(B, Sc, Dc);

			
	}
}
bool Check(char** B, int dim, int Turn)
{
	Position Sc, Dc;
	int Kr = 0, Kc = 0;
	FindKing(B, dim, Kr, Kc, !(Turn));
	Dc.ri = Kr;
	Dc.ci = Kc;

	for (int r = 0; r < 9; r++)
	{
		for (int c = 0; c < 9; c++)
		{
			Sc.ri = r;
			Sc.ci = c;
			if (IsValid(B, Sc, dim, Turn) && IslegalMove(B, Sc, Dc, dim))
			{
				return true;
			}
		}
	}
	return false;

}
bool SelfCheck1(char** B, int dim, int Turn,Position Dc, Position Sc)
{

	char** TB;
	TB = new char* [dim];
	for (int i = 0;i < dim; i++)
	{
		TB[i] = new char[dim];
	}
	
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			TB[r][c] = B[r][c];
		}
	}

	char sym;
	sym= B[Sc.ri][Sc.ci];
	TB[Dc.ri][Dc.ci] = sym;
	TB[Sc.ri][Sc.ci] = '-';

	return (Check(TB, dim, !Turn));

}

bool SelfCheck(char** B, int dim, int Turn)
{

	return (Check(B, dim, !Turn));

}

bool IsValidDest1(char** B, Position Sc, Position Dc, int dim, int Turn)
{
	if (Sc.ri < 0 || Sc.ri >= dim || Sc.ci < 0 || Sc.ci >= dim)
	{
		return false;
	}
	/*if (IsMyPiece(B[Sc.ri][Sc.ci], Turn)==true)
	{
		return false;
	}
	if (SelfCheck(B, dim, Turn)==true)
	{
		return false;
	}*/
	/*return true;*/
	return !IsMyPiece(B[Sc.ri][Sc.ci], Turn) && !SelfCheck1(B, dim, Turn, Dc, Sc);

}

bool IsValidDest(char** B, Position Sc, int dim, int Turn)
{
	if (Sc.ri < 0 || Sc.ri >= dim || Sc.ci < 0 || Sc.ci >= dim)
	{
		return false;
	}
	/*if (IsMyPiece(B[Sc.ri][Sc.ci], Turn)==true)
	{
		return false;
	}
	if (SelfCheck(B, dim, Turn)==true)
	{
		return false;
	}*/
	/*return true;*/
	return !IsMyPiece(B[Sc.ri][Sc.ci], Turn);
}

bool CanIMove(char** B, int dim, int Turn)
{
	Position Sc, Dc;

	for (int sr = 0; sr < dim; sr++)
	{
		for (int sc = 0; sc < dim; sc++)
		{
			for (int dr = 0; dr < dim; dr++)
			{
				for (int dc = 0; dc < dim; dc++)
				{
					Sc.ri = sr;
					Sc.ci = sc;
					Dc.ri = dr;
					Dc.ci = dc;

					if (IsValid(B, Sc, dim, Turn) && IsValidDest(B, Dc, dim, Turn) && IslegalMove(B, Sc, Dc, dim) && !SelfCheck(B, dim, Turn))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}
bool**CompHighlight(char** B, Position Sc,int dim,int Turn)
{
	Position Dc;
	bool** b = new bool* [dim]{};
	for (int r = 0; r < dim; r++)
	{
		b[r] = new bool[dim];
	}

	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			Dc.ci = c;
			Dc.ri = r;
			if (IsValidDest(B, Dc, dim, Turn) && IslegalMove(B, Sc, Dc, dim))
			{
				if(!SelfCheck1(B,dim,Turn,Dc,Sc))
				b[r][c] = true;
			}
			 
		}
	}

	return b;

}
void HBox(int r, int c, int row, int col, int color, int dr, int dc, char sym)
{

	int R, C;
	float mr, mc;
	for (int ri = 0; ri < row; ri++)
	{
		for (int ci = 0; ci < col; ci++)
		{
			R = ri + r;
			C = ci + c;
			mr = (row / 2.0) + r;
			mc = (col / 2.0) + c;
			if (C == c || R == r || C == c+col-1 || R == r+row-1)
			{

					SetClr(242);
			}
			else
			{
				SetClr(color);
			}
			gotoRowCol(R, C);
			cout << char(-37);
			if ((R = mr) && (C = mc))
			{


				gotoRowCol(R, C);
				if (sym == '-')
				{
					if ((dr + dc) % 2 == 0)
					{
						SetClr(15);
						cout << char(-37);
					}
					else
					{
						SetClr(8);
						cout << char(-37);
					}

				}
				else
				{
					DrawPiece(sym, R, C);
				}
			}

		}
	}
}
void Highlighting(char** B,bool**b , int rows, int cols, int dim, int Turn)
{
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (b[r][c] == true)
			{
				if ((r + c) % 2 == 0)
				{
					HBox(r * rows, c * cols, rows, cols, 15, r, c, B[r][c]);
				}
				else
				{
					HBox(r * rows, c * cols, rows, cols, 8, r, c, B[r][c]);
				}
			}
		}
	}
}
void UnHighlighting(char** B, bool** b, int rows, int cols, int dim, int Turn)
{
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			if (b[r][c] == true)
			{
				if ((r + c) % 2 == 0)
				{
					Box(r * rows, c * cols, rows, cols, 15, r, c, Turn, B[r][c]);
				}
					
				else
				{
					Box(r * rows, c * cols, rows, cols, 8, r, c, Turn, B[r][c]);
				}
			}
		}
	}
}
void Save(char** B, int dim,char*w,char*b,int Wsize,int Bsize,int Turn,string PNames[])
{

	ofstream writer("save.txt");
	writer << dim<<endl;
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			writer << B[r][c];
		}
		writer << endl;
	}
	writer << endl;
	writer << Wsize;
	writer << endl;
	for (int i = 0; i < 10; i++)
	{
		writer << w[i];
	}
	writer << endl;
	writer << Bsize;
	writer << endl;
	for (int i = 0; i < 10; i++)
	{
		writer << b[i];
	}
	writer << endl;
	writer << Turn;
	writer << endl;
	writer << PNames[0];
	writer << endl;
	writer << PNames[1];
}
void promotion(char** b, Position Sc, Position Dc, int dim, int Turn)
{
	char ans;

	// White Pieces
	if (Turn == 0 && Dc.ri <= 2)
	{
		if (b[Sc.ri][Sc.ci] == 'P')
		{
			if (Dc.ri <= 2 && Dc.ri != 0)
			{
				gotoRowCol(1, 80);
				cout << "Do you want to promote the piece? (Y/N)" << endl;
				cin >> ans;
				gotoRowCol(1, 80);
				cout << "                                        " << endl;
				if (ans == 'Y')
				{
					b[Sc.ri][Sc.ci] = '1';
				}
				else
				{
					b[Sc.ri][Sc.ci] = 'P';
				}
			}
			if (Dc.ri == 0)
			{
				b[Sc.ri][Sc.ci] = '1';
			}
		}

		if (b[Sc.ri][Sc.ci] == 'N')
		{
			if (Dc.ri == 2)
			{
				gotoRowCol(1, 80);
				cout << "Do you want to promote the piece? (Y/N)" << endl;
				cin >> ans;
				gotoRowCol(1, 80);
				cout << "                                        " << endl;
				if (ans == 'Y')
				{
					b[Sc.ri][Sc.ci] = '3';
				}
				else
				{
					b[Sc.ri][Sc.ci] = 'N';
				}
			}
			if (Dc.ri <= 1)
			{
				b[Sc.ri][Sc.ci] = '3';
			}
		}

		if (b[Sc.ri][Sc.ci] == 'L')
		{
			if (Dc.ri <= 2 && Dc.ri != 0)
			{
				gotoRowCol(1, 80);
				cout << "Do you want to promote the piece? (Y/N)" << endl;
				cin >> ans;
				gotoRowCol(1, 80);
				cout << "                                        " << endl;
				if (ans == 'Y')
				{
					b[Sc.ri][Sc.ci] = '5';;
				}
				else
				{
					b[Sc.ri][Sc.ci] = 'L';
				}
			}
			if (Dc.ri == 0)
			{
				b[Sc.ri][Sc.ci] = '5';
			}
		}

		if (b[Sc.ri][Sc.ci] == 'S')
		{
			if (Dc.ri <= 2)
			{
				gotoRowCol(1, 80);
				cout << "Do you want to promote the piece? (Y/N)" << endl;
				cin >> ans;
				gotoRowCol(1, 80);
				cout << "                                        " << endl;
				if (ans == 'Y')
				{
					b[Sc.ri][Sc.ci] = '7';;
				}
				else
				{
					b[Sc.ri][Sc.ci] = 'S';
				}
			}
		}
		if (b[Sc.ri][Sc.ci] == 'B')
		{
			if (Dc.ri <= 2)
			{
				gotoRowCol(1, 80);
				cout << "Do you want to promote the piece? (Y/N)" << endl;
				cin >> ans;
				gotoRowCol(1, 80);
				cout << "                                        " << endl;
				if (ans == 'Y')
				{
					b[Sc.ri][Sc.ci] = 'Y';
				}
				else
				{
					b[Sc.ri][Sc.ci] = 'B';
				}
			}
		}
		if (b[Sc.ri][Sc.ci] == 'R')
		{
			if (Dc.ri <= 2)
			{
				gotoRowCol(1, 80);
				cout << "Do you want to promote the piece? (Y/N)" << endl;
				cin >> ans;
				gotoRowCol(1, 80);
				cout << "                                        " << endl;
				if (ans == 'Y')
				{
					b[Sc.ri][Sc.ci] = 'Z';
				}
				else
				{
					b[Sc.ri][Sc.ci] = 'R';
				}
			}
		}
	}


	// Black Pieces
	if (Turn == 1 && Dc.ri >= 6)
	{
		if (b[Sc.ri][Sc.ci] == 'p')
		{
			if (Dc.ri >= 6 && Dc.ri != 8)
			{
				gotoRowCol(1, 80);
				cout << "Do you want to promote the piece? (Y/N)" << endl;
				cin >> ans;
				gotoRowCol(1, 80);
				cout << "                                        " << endl;

				if (ans == 'Y')
				{
					b[Sc.ri][Sc.ci] = '2';
				}
				else
				{
					b[Sc.ri][Sc.ci] = 'p';
				}
			}
			if (Dc.ri == 8)
			{
				b[Sc.ri][Sc.ci] = '2';
			}
		}
		if (b[Sc.ri][Sc.ci] == 'n')
		{
			if (Dc.ri == 6)
			{
				gotoRowCol(1, 80);
				cout << "Do you want to promote the piece? (Y/N)" << endl;
				cin >> ans;
				gotoRowCol(1, 80);
				cout << "                                        " << endl;

				if (ans == 'Y')
				{
					b[Sc.ri][Sc.ci] = '4';
				}
				else
				{
					b[Sc.ri][Sc.ci] = 'n';
				}
			}
			if (Dc.ri >= 7)
			{
				b[Sc.ri][Sc.ci] = '4';
			}
		}

		if (b[Sc.ri][Sc.ci] == 'l')
		{
			if (Dc.ri >= 6 && Dc.ri !=8)
			{
				gotoRowCol(1, 80);
				cout << "Do you want to promote the piece? (Y/N)" << endl;
				cin >> ans;
				gotoRowCol(1, 80);
				cout << "                                        " << endl;

				if (ans == 'Y')
				{
					b[Sc.ri][Sc.ci] = '6';
				}
				else
				{
					b[Sc.ri][Sc.ci] = 'l';
				}
			}
			if (Dc.ri == 8)
			{
				b[Sc.ri][Sc.ci] = '6';
			}
		}

		if (b[Sc.ri][Sc.ci] == 's')
		{
			if (Dc.ri >= 6)
			{
				gotoRowCol(1, 80);
				cout << "Do you want to promote the piece? (Y/N)" << endl;
				cin >> ans;
				gotoRowCol(1, 80);
				cout << "                                        " << endl;

				if (ans == 'Y')
				{
					b[Sc.ri][Sc.ci] = '8';
				}
				else
				{
					b[Sc.ri][Sc.ci] = 's';
				}
			}
		}
			if (b[Sc.ri][Sc.ci] == 'b')
			{
				if (Dc.ri >= 6)
				{
					gotoRowCol(1, 80);
					cout << "Do you want to promote the piece? (Y/N)" << endl;
					cin >> ans;
					gotoRowCol(1, 80);
					cout << "                                        " << endl;

					if (ans == 'Y')
					{
						b[Sc.ri][Sc.ci] = 'y';
					}
					else
					{
						b[Sc.ri][Sc.ci] = 'b';
					}
				}
			}

			if (b[Sc.ri][Sc.ci] == 'r')
			{
				if (Dc.ri >= 6)
				{
					gotoRowCol(1, 80);
					cout << "Do you want to promote the piece? (Y/N)" << endl;
					cin >> ans;
					gotoRowCol(1, 80);
					cout << "                                        " << endl;

					if (ans == 'Y')
					{
						b[Sc.ri][Sc.ci] = 'z';
					}
					else
					{
						b[Sc.ri][Sc.ci] = 'r';
					}
				}
			}
		

	}
}
void Capturing(char** b,char*w,char*black, Position Sc, Position Dc, int dim, int Turn,int &Wsize,int &Bsize)
{
	char y;
	if (b[Dc.ri][Dc.ci] != '-')
	{
		if (Turn == 0 && !IsMyPiece(b[Dc.ri][Dc.ci], Turn))
		{
			if (b[Dc.ri][Dc.ci] == 'p')
			{
				w[Wsize++] = 'P';
			}
			else if (b[Dc.ri][Dc.ci] == 'l')
			{
				w[Wsize++] = 'L';
			}
			else if (b[Dc.ri][Dc.ci] == 'n')
			{
				w[Wsize++] = 'N';
			}
			else if (b[Dc.ri][Dc.ci] == 'r')
			{
				w[Wsize++] = 'R';
			}
			else if (b[Dc.ri][Dc.ci] == 'b')
			{
				w[Wsize++] = 'B';
			}
			else if (b[Dc.ri][Dc.ci] == 'g')
			{
				w[Wsize++] = 'G';
			}
			else if (b[Dc.ri][Dc.ci] == 's')
			{
				w[Wsize++] = 'S';
			}
			else if (b[Dc.ri][Dc.ci] == '2')
			{
				w[Wsize++] = 'P';
			}
			else if (b[Dc.ri][Dc.ci] == '4')
			{
				w[Wsize++] = 'N';
			}
			else if (b[Dc.ri][Dc.ci] == '6')
			{
				w[Wsize++] = 'L';
			}
			else if (b[Dc.ri][Dc.ci] == '8')
			{
				w[Wsize++] = 'S';
			}
			else if (b[Dc.ri][Dc.ci] == 'y')
			{
				w[Wsize++] = 'B';
			}
			else if (b[Dc.ri][Dc.ci] == 'z')
			{
				w[Wsize++] = 'R';
			}

		}
		else
		{
			if (b[Dc.ri][Dc.ci] == 'P')
			{
				black[Bsize++] = 'p';
			}
			else if (b[Dc.ri][Dc.ci] == 'N')
			{
				black[Bsize++] = 'n';
			}
			else if (b[Dc.ri][Dc.ci] == 'L')
			{
				black[Bsize++] = 'l';
			}
			else if (b[Dc.ri][Dc.ci] == 'G')
			{
				black[Bsize++] = 'g';
			}
			else if (b[Dc.ri][Dc.ci] == 'S')
			{
				black[Bsize++] = 's';
			}
			else if (b[Dc.ri][Dc.ci] == 'R')
			{
				black[Bsize++] = 'r';
			}
			else if (b[Dc.ri][Dc.ci] == 'B')
			{
				black[Bsize++] = 'b';
			}
			else if (b[Dc.ri][Dc.ci] == '1')
			{
				black[Bsize++] = 'p';
			}
			else if (b[Dc.ri][Dc.ci] == '3')
			{
				black[Bsize++] = 'n';
			}
			else if (b[Dc.ri][Dc.ci] == '5')
			{
				black[Bsize++] = 'l';
			}
			else if (b[Dc.ri][Dc.ci] == '7')
			{
				black[Bsize++] = 's';
			}
			else if (b[Dc.ri][Dc.ci] == 'Y')
			{
				black[Bsize++] = 'b';
			}
			else if (b[Dc.ri][Dc.ci] == 'Z')
			{
				black[Bsize++] = 'r';
			}
		}
	}
}
void DisplayCapture(char* w, char* black, int Wsize, int Bsize,int Turn)
{
	int rows = 8;
	int col = 80;
	gotoRowCol(6, 80);
	cout << "White's Capture";
	gotoRowCol(8, 80);

	

	for (int r = 1; r <= 1; r++)
	{
		for (int c = 0; c<10; c++)
		{
			if ((r + c) % 2 == 0)
			{
				Box(r * rows, (c * 8) + col, 8, 8, 15, r, c, w[c], Turn);
			}
			else
			{
				Box(r * rows, (c * 8) + col, 8, 8,0, r, c, w[c], Turn);
			}
		}
	}

	
	gotoRowCol(22, 80);
	cout << "Black's Capture";
	gotoRowCol(24, 80);
	int rows1 = 24;
	int col1 = 80;

	for (int r = 1; r <= 1; r++)
	{
		for (int c = 0; c < 10; c++)
		{
			if ((r + c) % 2 == 0)
			{
				Box(r * rows1, (c * 8) + col1, 8, 8, 15, r, c, black[c], Turn);
			}
			else
			{
				Box(r * rows1, (c * 8) + col1, 8, 8, 0, r, c, black[c], Turn);
			}
		}
	}
	
}
bool IsValidDropSelection(char* w, char* black, Position Sc, int Wsize, int Bsize,int r,int c,int Turn)
{
	if (Sc.ci <10  || Sc.ci >=20)
	{
		return false;
	}

	if (Sc.ri <= 0 && Sc.ri>=3)
	{
		return false;
	}

	if (Sc.ri == 1)
	{
		if (Sc.ci == 10)
		{
			Sc.ci = 0;
		}
		else if (Sc.ci == 11)
		{
			Sc.ci = 1;
		}
		else if (Sc.ci == 12)
		{
			Sc.ci = 2;
		}
		else if (Sc.ci == 13)
		{
			Sc.ci = 3;
		}
		else if (Sc.ci == 14)
		{
			Sc.ci = 4;
		}
		else if (Sc.ci == 15)
		{
			Sc.ci = 5;
		}
		else if (Sc.ci == 16)
		{
			Sc.ci = 6;
		}
		else if (Sc.ci == 17)
		{
			Sc.ci = 7;
		}
		else if (Sc.ci == 18)
		{
			Sc.ci = 8;
		}
		else if (Sc.ci == 19)
		{
			Sc.ci = 9;
		}
		else if (Sc.ci == 20)
		{
			Sc.ci = 10;
		}
	}

	if (Sc.ri == 3)
	{
		if (Sc.ci == 10)
		{
			Sc.ci = 0;
		}
		else if (Sc.ci == 11)
		{
			Sc.ci = 1;
		}
		else if (Sc.ci == 12)
		{
			Sc.ci = 2;
		}
		else if (Sc.ci == 13)
		{
			Sc.ci = 3;
		}
		else if (Sc.ci == 14)
		{
			Sc.ci = 4;
		}
		else if (Sc.ci == 15)
		{
			Sc.ci = 5;
		}
		else if (Sc.ci == 16)
		{
			Sc.ci = 6;
		}
		else if (Sc.ci == 17)
		{
			Sc.ci = 7;
		}
		else if (Sc.ci == 18)
		{
			Sc.ci = 8;
		}
		else if (Sc.ci == 19)
		{
			Sc.ci = 9;
		}
		else if (Sc.ci == 20)
		{
			Sc.ci = 10;
		}
	}
	
	if (Turn == 0)
	{
		return IsMyPiece(w[Sc.ci], Turn);
	}
	else
	{
		return IsMyPiece(black[Sc.ci], Turn);
	}
	
}
bool DropPawn(char** B, Position Sc, Position Dc, int dim,int Turn)
{
	int Kr = 0, Kc = 0;
	if (Dc.ri==0)
	{
		return false;
	}
	if (Turn == 0)
	{
		FindKing(B, dim, Kr, Kc, !Turn);
		if (Dc.ri - 1 == Kr && Dc.ci == Kc)
		{
			return false;
		}
	}
	if (B[Dc.ri][Dc.ci] != '-')
	{
		return false;
	}
	for (int i = 0; i < dim; i++)
	{
		if (B[i][Dc.ci] == 'P')
		{
			return false;
		}
	}

	return true;
}
bool DropLance(char** B, Position Sc, Position Dc, int dim)
{
	if (Dc.ri == 0)
	{
		return false;
	}
	if (B[Dc.ri][Dc.ci] != '-')
	{
		return false;
	}
	return true;
}
bool DropKnight(char** B, Position Sc, Position Dc, int dim)
{
	if (Dc.ri <= 1)
	{
		return false;
	}
	if (B[Dc.ri][Dc.ci] != '-')
	{
		return false;
	}
	return true;
}
bool DropSilver(char** B, Position Sc, Position Dc, int dim)
{
	if (B[Dc.ri][Dc.ci] != '-')
	{
		return false;
	}
	return true;
}
bool Droppawn(char** B, Position Sc, Position Dc, int dim,int Turn)
{
	int Kr = 0, Kc = 0;
	if (Dc.ri == 8)
	{
		return false;
	}
	if (B[Dc.ri][Dc.ci] != '-')
	{
		return false;
	}
	if (Turn == 1)
	{
		FindKing(B, dim, Kr, Kc, !Turn);
		if (Dc.ri + 1 == Kr && Dc.ci == Kc)
		{
			return false;
		}
	}
	for (int i = 0; i < dim; i++)
	{
		if (B[i][Dc.ci] == 'p')
		{
			return false;
		}
	}

	return true;
}
bool Droplance(char** B, Position Sc, Position Dc, int dim)
{
	if (Dc.ri == 8)
	{
		return false;
	}
	if (B[Dc.ri][Dc.ci] != '-')
	{
		return false;
	}
	return true;
}
bool Dropknight(char** B, Position Sc, Position Dc, int dim)
{
	if (Dc.ri >= 7)
	{
		return false;
	}
	if (B[Dc.ri][Dc.ci] != '-')
	{
		return false;
	}
	return true;
}
bool Dropsilver(char** B, Position Sc, Position Dc, int dim)
{
	if (B[Dc.ri][Dc.ci] != '-')
	{
		return false;
	}
	return true;
}
bool IslegalDrop(char**B,char* w, char* black, Position Sc, Position Dc,int Turn,int dim)
{

	if (Sc.ri == 1)
	{
		if (Sc.ci == 10)
		{
			Sc.ci = 0;
		}
		else if (Sc.ci == 11)
		{
			Sc.ci = 1;
		}
		else if (Sc.ci == 12)
		{
			Sc.ci = 2;
		}
		else if (Sc.ci == 13)
		{
			Sc.ci = 3;
		}
		else if (Sc.ci == 14)
		{
			Sc.ci = 4;
		}
		else if (Sc.ci == 15)
		{
			Sc.ci = 5;
		}
		else if (Sc.ci == 16)
		{
			Sc.ci = 6;
		}
		else if (Sc.ci == 17)
		{
			Sc.ci = 7;
		}
		else if (Sc.ci == 18)
		{
			Sc.ci = 8;
		}
		else if (Sc.ci == 19)
		{
			Sc.ci = 9;
		}
		else if (Sc.ci == 20)
		{
			Sc.ci = 10;
		}
	}

	if (Sc.ri == 3)
	{
		if (Sc.ci == 10)
		{
			Sc.ci = 0;
		}
		else if (Sc.ci == 11)
		{
			Sc.ci = 1;
		}
		else if (Sc.ci == 12)
		{
			Sc.ci = 2;
		}
		else if (Sc.ci == 13)
		{
			Sc.ci = 3;
		}
		else if (Sc.ci == 14)
		{
			Sc.ci = 4;
		}
		else if (Sc.ci == 15)
		{
			Sc.ci = 5;
		}
		else if (Sc.ci == 16)
		{
			Sc.ci = 6;
		}
		else if (Sc.ci == 17)
		{
			Sc.ci = 7;
		}
		else if (Sc.ci == 18)
		{
			Sc.ci = 8;
		}
		else if (Sc.ci == 19)
		{
			Sc.ci = 9;
		}
		else if (Sc.ci == 20)
		{
			Sc.ci = 10;
		}
	}



	if (Turn== 0 && IsMyPiece(w[Sc.ci], Turn))
	{
		switch (w[Sc.ci])
		{
		case'P':
			return DropPawn(B, Sc, Dc, dim,Turn);
		case'L':
			return DropLance(B, Sc, Dc, dim);
		case'N':
			return DropKnight(B, Sc, Dc, dim);
		case'S':
			return DropSilver(B, Sc, Dc, dim);
		case'G':
			return DropSilver(B, Sc, Dc, dim);
		case'R':
			return DropSilver(B, Sc, Dc, dim);
		case'B':
			return DropSilver(B, Sc, Dc, dim);

		}
	}

	if (Turn == 1 && IsMyPiece(black[Sc.ci],Turn))
	{
		switch (black[Sc.ci])
		{
		case'p':
			return Droppawn(B, Sc, Dc, dim,Turn);
		case'l':
			return Droplance(B, Sc, Dc, dim);
		case'n':
			return Dropknight(B, Sc, Dc, dim);
		case's':
			return Dropsilver(B, Sc, Dc, dim);
		case'g':
			return Dropsilver(B, Sc, Dc, dim);
		case'b':
			return Dropsilver(B, Sc, Dc, dim);
		case'r':
			return Dropsilver(B, Sc, Dc, dim);


		}
	}
	



}
bool** CompDropHighlight(char** B,char*w,char*black, Position Sc, int dim, int Turn)
{
	Position Dc;
	bool** b = new bool* [dim] {};
	for (int r = 0; r < dim; r++)
	{
		b[r] = new bool[dim];
	}

	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			Dc.ci = c;
			Dc.ri = r;
			if (IsValidDest(B, Dc, dim, Turn) && IslegalDrop(B,w,black, Sc, Dc,Turn, dim))
			{
				b[r][c] = true;
			}

		}
	}

	return b;

}
void DisplayCapture1(char* w, char* black,int Turn)
{
	int rows = 24;
	int col = 80;
	gotoRowCol(23, 80);
	cout << "White's Capture";
	gotoRowCol(24, 80);



	for (int r = 1; r <= 1; r++)
	{
		for (int c = 0; c < 10; c++)
		{
			if ((r + c) % 2 == 0)
			{
				Box(r * rows, (c * 8) + col, 8, 8, 15, r, c,Turn, w[c]);
			}
			else
			{
				Box(r * rows, (c * 8) + col, 8, 8, 8, r, c,Turn, w[c]);
			}
		}
	}


	gotoRowCol(7, 80);
	cout << "Black's Capture";
	gotoRowCol(8, 80);
	int rows1 = 8;
	int col1 = 80;

	for (int r = 1; r <= 1; r++)
	{
		for (int c = 0; c < 10; c++)
		{
			if ((r + c) % 2 == 0)
			{
				Box(r * rows1, (c * 8) + col1, 8, 8, 15, r, c,Turn,black[c]);
			}
			else
			{
				Box(r * rows1, (c * 8) + col1, 8, 8, 8, r, c, Turn, black[c]);
			}
		}
	}

}
void UpdateBoard1(char**& B, char*& w, char* b, Position Sc, Position Dc, int& Wsize, int& Bsize,int Turn)
{
	if (Sc.ci <= 8)
	{
		char sym = B[Sc.ri][Sc.ci];
		B[Dc.ri][Dc.ci] = sym;
		B[Sc.ri][Sc.ci] = '-';

		if ((Dc.ri + Dc.ci) % 2 == 0)
		{
			Box((Dc.ri * 8), (Dc.ci * 8), 8, 8, 15, Dc.ri, Dc.ci, Turn, B[Dc.ri][Dc.ci]);
		}
		else
		{
			Box((Dc.ri * 8), (Dc.ci * 8), 8, 8, 8, Dc.ri, Dc.ci, Turn, B[Dc.ri][Dc.ci]);
		}
		if ((Sc.ri + Sc.ci) % 2 == 0)
		{
			Box((Sc.ri * 8), (Sc.ci * 8), 8, 8, 15, Sc.ri, Sc.ci, Turn, B[Sc.ri][Sc.ci]);
		}
		else
		{
			Box((Sc.ri * 8), (Sc.ci * 8), 8, 8, 8, Sc.ri, Sc.ci, Turn, B[Sc.ri][Sc.ci]);
		}

	}



	if (Sc.ci >= 10 && Sc.ri == 1)
	{

		char sym = b[Sc.ci - 10];
		B[Dc.ri][Dc.ci] = sym;
		b[Sc.ci - 10] = '-';


		

		if ((Dc.ri + Dc.ci) % 2 == 0)
		{
			Box((Dc.ri * 8), (Dc.ci * 8), 8, 8, 15, Dc.ri, Dc.ci, Turn, B[Dc.ri][Dc.ci]);
		}
		else
		{
			Box((Dc.ri * 8), (Dc.ci * 8), 8, 8, 8, Dc.ri, Dc.ci, Turn, B[Dc.ri][Dc.ci]);
		}

		if ((Sc.ri + Sc.ci) % 2 == 0)
		{
			Box((Sc.ri * 8), (Sc.ci * 8), 8, 8, 15, Sc.ri, Sc.ci, Turn, b[Sc.ci - 10]);
		}
		else
		{
			Box((Sc.ri * 8), (Sc.ci * 8), 8, 8, 8, Sc.ri, Sc.ci, Turn, b[Sc.ci - 10]);
		}
	}


	if (Sc.ci >= 10 && Sc.ri == 3)
	{

		char sym = w[Sc.ci - 10];
		B[Dc.ri][Dc.ci] = sym;
		w[Sc.ci - 10] = '-';


		if ((Dc.ri + Dc.ci) % 2 == 0)
		{
			Box((Dc.ri * 8), (Dc.ci * 8), 8, 8, 15, Dc.ri, Dc.ci, Turn, B[Dc.ri][Dc.ci]);
		}
		else
		{
			Box((Dc.ri * 8), (Dc.ci * 8), 8, 8, 8, Dc.ri, Dc.ci, Turn, B[Dc.ri][Dc.ci]);
		}
		if ((Sc.ri + Sc.ci) % 2 == 0)
		{
			Box((Sc.ri * 8), (Sc.ci * 8), 8, 8, 15, Sc.ri, Sc.ci, Turn, w[Sc.ci - 10]);
		}
		else
		{
			Box((Sc.ri * 8), (Sc.ci * 8), 8, 8, 8, Sc.ri, Sc.ci, Turn, w[Sc.ci - 10]);
		}
		
	}

	int countW = 0;
	for (int i = 0; i < 10; i++)
	{
		if (w[i] == '-')
		{
			countW++;
		}
		if (countW == 10)
		{
			Wsize = 0;
		}
	}

	int countB = 0;
	for (int i = 0; i < 10; i++)
	{
		if (b[i] == '-')
		{
			countB++;
		}
		if (countB == 10)
		{
			Bsize = 0;
		}
	}

}
void Capturing1(char** b, char* w, char* black, Position Sc, Position Dc, int dim, int Turn, int& Wsize, int& Bsize)
{
	char y;
	if (b[Dc.ri][Dc.ci] != '-')
	{
		if (Turn == 0 && !IsMyPiece(b[Dc.ri][Dc.ci], Turn))
		{
			if (b[Dc.ri][Dc.ci] == 'p')
			{
				w[Wsize++] = 'P';
			}
			else if (b[Dc.ri][Dc.ci] == 'l')
			{
				w[Wsize++] = 'L';
			}
			else if (b[Dc.ri][Dc.ci] == 'n')
			{
				w[Wsize++] = 'N';
			}
			else if (b[Dc.ri][Dc.ci] == 'r')
			{
				w[Wsize++] = 'R';
			}
			else if (b[Dc.ri][Dc.ci] == 'b')
			{
				w[Wsize++] = 'B';
			}
			else if (b[Dc.ri][Dc.ci] == 'g')
			{
				w[Wsize++] = 'G';
			}
			else if (b[Dc.ri][Dc.ci] == 's')
			{
				w[Wsize++] = 'S';
			}
			else if (b[Dc.ri][Dc.ci] == '2')
			{
				w[Wsize++] = 'P';
			}
			else if (b[Dc.ri][Dc.ci] == '4')
			{
				w[Wsize++] = 'N';
			}
			else if (b[Dc.ri][Dc.ci] == '6')
			{
				w[Wsize++] = 'L';
			}
			else if (b[Dc.ri][Dc.ci] == '8')
			{
				w[Wsize++] = 'S';
			}
			else if (b[Dc.ri][Dc.ci] == 'y')
			{
				w[Wsize++] = 'B';
			}
			else if (b[Dc.ri][Dc.ci] == 'z')
			{
				w[Wsize++] = 'R';
			}
		}
		else
		{
			if (b[Dc.ri][Dc.ci] == 'P')
			{
				black[Bsize++] = 'p';
			}
			else if (b[Dc.ri][Dc.ci] == 'N')
			{
				black[Bsize++] = 'n';
			}
			else if (b[Dc.ri][Dc.ci] == 'L')
			{
				black[Bsize++] = 'l';
			}
			else if (b[Dc.ri][Dc.ci] == 'G')
			{
				black[Bsize++] = 'g';
			}
			else if (b[Dc.ri][Dc.ci] == 'S')
			{
				black[Bsize++] = 's';
			}
			else if (b[Dc.ri][Dc.ci] == 'R')
			{
				black[Bsize++] = 'r';
			}
			else if (b[Dc.ri][Dc.ci] == 'B')
			{
				black[Bsize++] = 'b';
			}
			else if (b[Dc.ri][Dc.ci] == '1')
			{
				black[Bsize++] = 'p';
			}
			else if (b[Dc.ri][Dc.ci] == '3')
			{
				black[Bsize++] = 'n';
			}
			else if (b[Dc.ri][Dc.ci] == '5')
			{
				black[Bsize++] = 'l';
			}
			else if (b[Dc.ri][Dc.ci] == '7')
			{
				black[Bsize++] = 's';
			}
			else if (b[Dc.ri][Dc.ci] == 'Y')
			{
				black[Bsize++] = 'b';
			}
			else if (b[Dc.ri][Dc.ci] == 'Z')
			{
				black[Bsize++] = 'r';
			}
		}
	}
}
void Replay(char*** &R, char** B,char*w,char*b, int dim, int& Rsize,char**white,char**black,int &wsize,int &bsize,int*turn_replay,int Turn,int &turnsize)
{

	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			R[Rsize][r][c] = B[r][c];
		}

	}
	Rsize++;

	for (int c = 0; c < dim; c++)
	{
		white[wsize][c] = w[c];
	}
	wsize++;
	for (int c = 0; c < dim; c++)
	{
		black[bsize][c] = b[c];
	}
	bsize++;

	turn_replay[turnsize++] = Turn;

}
void DisplayReplay(char*** R, int Dim, int rows, int cols, char** B, int Turn, int Rsize, char** white, char** black, int Wsize, int Bsize,int*turnreplay,string Names[])
{
	system("cls");
	for (int r = 0; r < Dim; r++)
	{
		for (int c = 0; c < Dim; c++)
		{
			if ((r + c) % 2 == 0)
			{
				Box(r * rows, c * cols, rows, cols, 15, r, c, Turn, R[0][r][c]);
			}
			else
			{
				Box(r * rows, c * cols, rows, cols, 8, r, c, Turn, R[0][r][c]);
			}

		}
	}

	TurnMsg(Names[turnreplay[0]]);

	gotoRowCol(7, 80);
	cout << "Black's Capture";
	gotoRowCol(8, 80);
	int rows1 = 8;
	int col1 = 80;

	for (int r = 1; r <= 1; r++)
	{
		for (int c = 0; c < 10; c++)
		{
			if ((r + c) % 2 == 0)
			{
				Box(r * rows1, (c * 8) + col1, 8, 8, 15, r, c, Turn, black[0][c]);
			}
			else
			{
				Box(r * rows1, (c * 8) + col1, 8, 8, 8, r, c, Turn, black[0][c]);
			}
		}
	}


	int rows2 = 24;
	int col2 = 80;
	gotoRowCol(23, 80);
	cout << "White's Capture";
	gotoRowCol(24, 80);



	for (int r = 1; r <= 1; r++)
	{
		for (int c = 0; c < 10; c++)
		{
			if ((r + c) % 2 == 0)
			{
				Box(r * rows2, (c * 8) + col2, 8, 8, 15, r, c, Turn, white[0][c]);
			}
			else
			{
				Box(r * rows2, (c * 8) + col2, 8, 8, 8, r, c, Turn, white[0][c]);
			}
		}
	}




	for (int i = 1; i < Rsize; i++)
	{
		TurnMsg(Names[turnreplay[i]]);

		for (int r = 0; r < Dim; r++)
		{
			for (int c = 0; c < Dim; c++)
			{
				if ((r + c) % 2 == 0)
				{
					Box(r * rows, c * cols, rows, cols, 15, r, c, Turn, R[i][r][c]);
				}
				else
				{
					Box(r * rows, c * cols, rows, cols, 8, r, c, Turn, R[i][r][c]);
				}
			}
		}

		gotoRowCol(7, 80);
		cout << "Black's Capture";
		gotoRowCol(8, 80);
		int rows1 = 8;
		int col1 = 80;

		for (int r = 1; r <= 1; r++)
		{
			for (int c = 0; c < 10; c++)
			{
				if ((r + c) % 2 == 0)
				{
					Box(r * rows1, (c * 8) + col1, 8, 8, 15, r, c, Turn, black[i][c]);
				}
				else
				{
					Box(r * rows1, (c * 8) + col1, 8, 8, 8, r, c, Turn, black[i][c]);
				}
			}
		}

		int rows2 = 24;
		int col2 = 80;
		gotoRowCol(23, 80);
		cout << "White's Capture";
		gotoRowCol(24, 80);



		for (int r = 1; r <= 1; r++)
		{
			for (int c = 0; c < 10; c++)
			{
				if ((r + c) % 2 == 0)
				{
					Box(r * rows2, (c * 8) + col2, 8, 8, 15, r, c, Turn, white[0][c]);
				}
				else
				{
					Box(r * rows2, (c * 8) + col2, 8, 8, 8, r, c, Turn, white[0][c]);
				}
			}
		}
	}




}
void Box1(int r, int c, int row, int col)
{

	int R, C;
	float mr, mc;
	for (int ri = 0; ri < row; ri++)
	{
		for (int ci = 0; ci < col; ci++)
		{
			R = ri + r;
			C = ci + c;
			mr = (row / 2.0) + r;
			mc = (col / 2.0) + c;
			SetClr(8);
			gotoRowCol(R, C);
			cout << char(-37);
			if ((R = mr) && (C = mc))
			{

				gotoRowCol(R, C-2);
				cout << "undo";
				
			}
		}
	}
}////
void DisplayUndoButton()
{
	Box1(60, 120, 8, 8);

}

void Undo(char*** Replay, int Rsize, char** B, char* w,char**white,char**black, char* b, int wsize, int bsize,int*turn_replay,int Tsize,string Names[],int &Turn)
{

	Rsize--;
	wsize--;
	bsize--;
	Tsize--;
	int ct = 0;
	int r, c;
	getRowColbyLeftClick(r, c);
	if (r >= 60 && r <= 68 && c >= 120 && c <= 128)
	{
		ct = 1;
	}
	else
		ct = 0;


	while (ct == 1)
	{

		for (int r = 0; r < 9; r++)
		{
			for (int c = 0; c < 9; c++)
			{
				B[r][c] = Replay[Rsize-1][r][c];
			}
			w[r]=white[wsize-1][r];
			b[r] = black[bsize-1][r];
		}
		int Turn = turn_replay[Tsize-1];

		TurnMsg(Names[Turn]);
		Board(9, 8, 8, B, Turn);
		DisplayCapture1(w, b,Turn);


		Rsize--;
		wsize--;
		bsize--;
		Tsize--;

		getRowColbyLeftClick(r, c);
		if (r >= 60 && r <= 68 && c >= 120 && c <= 128)
		{
			ct = 1;
		}
		else
			ct = 0;

	}


}


int main()
{
	
	int dim=9,Wsize=0,Bsize=0,Rsize=0,Kr=0,Kc=0,wrsize=0,brsize=0,turnsize=0;
	int r = 8;
	int c = 8;
	int rr = 0;
	int rc = 0;

	char**B;
	int* turn_replay;
	char*** replay;
	char* white;
	char** white_replay;
	char* black;
	char** black_replay;
	bool** b;
	bool valid=false;
	bool legal = false;
	int count=0,s=0;
	string PNames[2];
	int Turn;
	Position Sc,Dc,Kp;
	SetClr(15);
	Init(B,dim,PNames,Turn,white,black,Wsize,Bsize,replay,white_replay,black_replay,turn_replay);
	system("cls");
	Board(dim,r,c,B,Turn);
	DisplayCapture1(white, black, Turn);
	DisplayUndoButton();
	cout<<endl<<endl<<endl<<endl;
	while (true)
	{
		SetClr(15);
		TurnMsg(PNames[Turn]);
	do{	do
		{
			do
			{
				do
				{
					SelectPos(Sc, dim, r, c);

					if (IsValid(B, Sc, dim, Turn) || IsValidDropSelection(white, black, Sc, Wsize, Bsize, r, c, Turn))
					{
						valid = false;
					}
					else
					{
						valid = true;
					}

				} while (valid == true);

				if (Sc.ri >= 0 && Sc.ri < dim && Sc.ci >= 0 && Sc.ci < dim)
				{
					b = CompHighlight(B, Sc, dim, Turn);////
					Highlighting(B, b, r, c, dim, Turn);
					SelectPos(Dc, dim, r, c);
					UnHighlighting(B, b, r, c, dim, Turn);

				}
				else
				{
					if (Sc.ri == 3 && Turn == 0)
					{
						b = CompDropHighlight(B, white, black, Sc, dim, Turn);////
						Highlighting(B, b, r, c, dim, Turn);
						SelectPos(Dc, dim, r, c);
						UnHighlighting(B, b, r, c, dim, Turn);

					}
					else if (Sc.ri == 1 && Turn == 1)
					{
						b = CompDropHighlight(B, white, black, Sc, dim, Turn);////
						Highlighting(B, b, r, c, dim, Turn);
						SelectPos(Dc, dim, r, c);
						UnHighlighting(B, b, r, c, dim, Turn);
					}

				}

			} while (!IsValidDest(B, Dc, dim, Turn));

			if (Sc.ri >= 0 && Sc.ri < dim && Sc.ci >= 0 && Sc.ci < dim)
			{
				if (IslegalMove(B, Sc, Dc, dim))
				{
					legal = false;
				}
				else
				{
					legal = true;
				}
			}
			else
			{
				if (IslegalDrop(B, white, black, Sc, Dc, Turn, dim))
				{
					legal = false;
				}
				else
				{
					legal = true;
				}
			}

		} while (legal == true);

	}while (SelfCheck1(B, dim, Turn, Dc, Sc));

		promotion(B, Sc, Dc, dim, Turn);
		Capturing1(B, white, black, Sc, Dc, dim, Turn, Wsize, Bsize);
		DisplayCapture1(white, black,Turn);
		UpdateBoard1(B,white,black,Sc,Dc,Wsize,Bsize,Turn);
		DisplayCapture1(white, black,Turn);
		//Board(dim,r,c,B);
		FindKing(B, dim,Kr,Kc, Turn);
		
	    TurnChange(Turn);
		TurnMsg(PNames[Turn]);
		Replay(replay, B, white, black, dim, Rsize, white_replay, black_replay, wrsize, brsize, turn_replay, Turn, turnsize);
		Save(B, dim, white, black, Wsize, Bsize, Turn,PNames);
		getRowColbyLeftClick(rr, rc);
		if (rr >= 60 && rr <= 68 && rc >= 120 && rc <= 128)
		{
			Undo(replay, Rsize, B, white, white_replay, black_replay, black, wrsize, brsize, turn_replay, turnsize, PNames,Turn);
			Turn = !Turn;
		}
		

		if (Check(B,dim,Turn))
		{
			if (CanIMove(B, dim,Turn))
			{
				char ans;
				gotoRowCol(60, 80);
				cout<<PNames[Turn] << " You win the Game";
				gotoRowCol(61, 80);
				cout << "Do you want to see the replay? (Y/N)";
				cin >> ans;
				if (ans == 'Y')
				{
					DisplayReplay(replay, dim, r, c, B, Turn, Rsize,white_replay,black_replay,wrsize,brsize,turn_replay,PNames);
					break;
				}
				else if (ans == 'N')
				{
					break;
				}
				
			}
		}
		else
		{
			
			continue;
		}

		
	}
	
	

	return _getch();
}

