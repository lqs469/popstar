// GAME.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "windows.h"
#include "time.h"
#include "conio.h"
#include "stdlib.h"

int a[11][11],x,y,point=0,p,times=0,flag=0;
bool f[11][11];

void color_white()
{
   HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
   WORD att;
   att=FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY;
   SetConsoleTextAttribute(handle,att);
}

void color_red()
{
   HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
   WORD att;
   att=FOREGROUND_RED|FOREGROUND_INTENSITY;
   SetConsoleTextAttribute(handle,att);
}

void color_blue()
{
   HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
   WORD att;
   att=FOREGROUND_BLUE|FOREGROUND_INTENSITY;
   SetConsoleTextAttribute(handle,att);
}

void color_green()
{
   HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
   WORD att;

   att=FOREGROUND_GREEN|FOREGROUND_INTENSITY;
   SetConsoleTextAttribute(handle,att);
}

void color_yellow()
{
   HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);
   WORD att;

   att=FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY;
   SetConsoleTextAttribute(handle,att);
}



void mapmake()
{
    int i,j,k;
	srand((unsigned)time(NULL));

	for(i=1;i<=10;i++) 
	{
		for(j=1;j<=10;j++)
		{
			k=rand()%4+1;
			if(k==1){color_red();   a[i][j]=1;   printf("●");}
            if(k==2){color_green(); a[i][j]=2;   printf("●");}
			if(k==3){color_blue();  a[i][j]=3;   printf("●");}
			if(k==4){color_yellow();a[i][j]=4;   printf("●");}
		}
		printf("\n");
	}
}

//○●
int getpoint(int x) 
{
	int i,ans=0;
	for(i=1;i<=x;i++)ans=ans+i;
    return ans;
}

void remap()
{
	int i,j;
	system("CLS");

	color_white();
	printf("第%d关\n\n",times);

	for(i=1;i<=10;i++) 
	{
		for(j=1;j<=10;j++)
		{
			if(a[i][j]<1||a[i][j]>8) 
			{
				if(i==x&&j==y)
				{ color_white();printf("[]"); }
				else 
					printf("  ");
			}
		

			if(a[i][j]==1) {color_red();printf("●");}
			if(a[i][j]==5) {color_red();printf("○");}
		    
            if(a[i][j]==2) {color_green();printf("●");}
            if(a[i][j]==6) {color_green();printf("○");}
		     	
			if(a[i][j]==3) {color_blue();printf("●");}
			if(a[i][j]==7) {color_blue();printf("○");}
		     	
			if(a[i][j]==4) {color_yellow();printf("●");}
			if(a[i][j]==8) {color_yellow();printf("○");}		     	
		}
		printf("\n");
	}
	color_white();
	printf("\n使用“wsad”控制上下左右，“空格键”消除,同色相连越多得分越高\n\n总得分: ");
	color_yellow();
	printf("%d\n\n",point);
	color_red();
	printf("目标：%d\n\n",getpoint(times)*100+200);
}

void run(int x,int y,int k)
{
	int i;
	if(x>=1&&x<=10&&y>=1&&y<=10&&(a[x][y]==k))
	{
		p++;
     	for (i=1;i<=4;i++)
		{		
          if(i==1)
		  {			   
			   a[x][y]=0;
		       run(x-1,y,k);			   
		  }
	      if(i==2)
		  {		    	 
				 a[x][y]=0;
				 run(x+1,y,k);				 
		  }
	      if(i==3)
		  {	 
				 a[x][y]=0;
		         run(x,y-1,k);		 
		  }
	      if(i==4)
		  {	 
				 a[x][y]=0;
		         run(x,y+1,k);			 
		  }
		}
	}
}

void fall()
{
	int i,j,k,temp,u,v;
	for (i=1;i<=10;i++)	
		for(j=10;j>1;j--)
			if(a[j][i]>8||a[j][i]<1)
			{
				temp=0;
				for(k=j;k>=1;k--)temp=temp+a[k][i];
				if(temp==0) break;
				else
				{
					u=0;
				    while(a[j][i]<1||a[j][i]>8)
					{
                     u++; 
				     for(k=j;k>1;k--)a[k][i]=a[k-1][i];			 
					}
					k=1;
					while(a[k][i]==0)k++;
					for(v=k;v<=u;v++)a[v][i]=0;
				}
			}
}

int judge()
{
	int i,j,t;
	t=0;
	for(i=1;i<=10;i++)
		for(j=1;j<=10;j++)
			t=t+a[i][j];
    if(t==0)return 1;
	else return 0;
}

void move(int m,int n)
{
	int k;	
    x=m;y=n;

    
	while(1)
	{
		if(judge()==1) 
		{
			color_white();
		    break;
		}	 
     k=getch();
	 if(k==32)
	 {		 
		   p=0;
		   a[x][y]=a[x][y]-4;
		   if(a[x][y]==0)break;
		   run(x,y,a[x][y]);
		   
		   if(p>1)point=point+getpoint(p);
		   
		   fall(); 
		   if(a[x][y]!=0)a[x][y]=a[x][y]+4;
		   remap();		 
	 }
	 
	 if((k==119)&&(x>1)&&(a[x-1][y]>0||a[x-1][y]<9))  
	 {
		 if(a[x][y]!=0)a[x][y]=a[x][y]-4;	     	 
		 if(a[x-1][y]!=0)a[x-1][y]=a[x-1][y]+4;
		 x--;
		 remap();
	 }
	 if((k==115)&&(x<10)&&(a[x+1][y]>0||a[x+1][y]<9)) 
	 {
		 if(a[x][y]!=0)a[x][y]=a[x][y]-4;
		 if(a[x+1][y]!=0)a[x+1][y]=a[x+1][y]+4;
		 x++;
		 remap();
	 }
     if((k==97)&&(y>1)&&(a[x][y-1]>0||a[x][y-1]<9))   
	 {
		 if(a[x][y]!=0)a[x][y]=a[x][y]-4;
	     if(a[x][y-1]!=0)a[x][y-1]=a[x][y-1]+4;
	     y--;
     	 remap();
	 }
     if((k==100)&&(y<10)&&(a[x][y+1]>0||a[x][y+1]<9))
	 {
		 if(a[x][y]!=0)a[x][y]=a[x][y]-4;
		 if(a[x][y+1]!=0)a[x][y+1]=a[x][y+1]+4;
		 y++;
		 remap();
	 }
	}
}


int main()
{
    int i;
 
    color_green();
	printf("\n\n\n\n                            POPSTAR\n\n\n");
	color_yellow();
    printf("                         1、开始游戏\n\n\n                         2、退出游戏\n\n\n\n");
	color_white();
	printf("                                                  制作：JK1206_LQS(12281144)\n\n");	

    i=getch();

	while(i==49)
	{ 
	  if(flag==1){point=0;times=0;flag=0;}
	  if(i==50) return 0;
	  if(i==49)
	  {
	     system("CLS");
	 	      
	     times++;

    	 mapmake();
         a[1][1]=a[1][1]+4;
         remap();
         move(1,1);
	  }

	  if (point>=getpoint(times)*100+200)
	  {
		  printf("1、继续下一关      2、我要退出");
          i=getch();
	  }
	  else 
	  {
        color_red();
		printf("game over\n");
		color_white();
		printf("1、重新开始      2、我要退出\n\n\n制作：计科1206李芩硕(12281144)\n");
		
		
		i=getch();
		if(i==2)return 0;
		  else flag=1;
	  } 
    }


	return 0;
}