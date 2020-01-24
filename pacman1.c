#include <stdio.h>
#include<stdlib.h>
#include<windows.h>

void gotoxy(int x, int y)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorCoord;
	cursorCoord.X=x;
	cursorCoord.Y=y;
	SetConsoleCursorPosition(consoleHandle, cursorCoord);
}

int printmap(char map[4][4],int *s,int *t)
{
	gotoxy(30,11);
	
	int i,j,score=0;
	for(i=0;i<6;i++)
	printf("%c",254);
	printf("\n");
	
	for(i=0;i<4;i++)
	{
		gotoxy(30,12+i);
		
		printf("%c",254);
		
		for(j=0;j<4;j++)
		{
			if(map[i][j]=='0')
			{
				printf("%c",1);
				*s=i;
				*t=j;
			}
			if(map[i][j]=='1')
			printf(" ");
			if(map[i][j]=='*')
			{
				printf(".");
				score++;
			}

			if(map[i][j]=='#')
			printf("%c",254);	
		}
	
		printf("%c",254);
		printf("\n");
	}
	
	gotoxy(30,16);

	for(i=0;i<6;i++)
	printf("%c",254);
	printf("\n");
	
	return score;
}

int main()
{
	int i=0,j=0,s,t,score;
	char map[4][4];
	int check[1000]={0};
	FILE *p;
	p=fopen("Testcase01.txt","r");
	
	while(feof(p)==0)
	fgets(map[i++],100,p);
	
	fclose(p);
	
	score=printmap(map,&s,&t);
	check[0]=1;
	while(score!=0)
	{
	    if(map[s+1][t]=='*' && s<3)
	    {
	    	map[s][t]='1';
	    	map[s+1][t]='0';
		}
		else if(map[s][t+1]=='*' && t<3)
	    {
	    	map[s][t]='1';
	    	map[s][t+1]='0';
		}
		else if(map[s-1][t]=='*' && s>0)
	    {
	    	map[s][t]='1';
	    	map[s-1][t]='0';
		}
		else if(map[s][t-1]=='*' && t>0)
	    {
	    	map[s][t]='1';
	    	map[s][t-1]='0';
		}
		else if(map[s+1][t]!='#' && !check[(s+1)*4 + t] && s<3)
	    {
	    	map[s][t]='1';
	    	map[s+1][t]='0';
	    	check[(s+1)*4 + t]=1;
		}
		else if(map[s][t+1]!='#' && !check[s*4 + t+1] && t<3)
	    {
	    	map[s][t]='1';
	    	map[s][t+1]='0';
	    	check[s*4 + t+1]=1;
		}
		else if(map[s-1][t]!='#' && !check[(s-1)*4 + t] && s>0)
	    {
	    	map[s][t]='1';
	    	map[s-1][t]='0';
	    	check[(s-1)*4 + t]=1;
		}
		else if(map[s][t-1]!='#' && !check[s*4 + t-1] && t>0)
	    {
	    	map[s][t]='1';
	    	map[s][t-1]='0';
	    	check[s*4 + t-1]=1;
		}
		sleep(1);
		score=printmap(map,&s,&t);
	}
	printf("Pacman finished eating!");
}
