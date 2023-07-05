#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<math.h>
union REGS in,out;
int maxx,maxy;

struct Drawing
{
  int color;
  int figure;
}user;

char *figure[]={"Line","Rectangle","Circle"};

//Declaration of functions
int callmouse();
void mouseposi(int &xpos,int &ypos,int &click);
int mousehide();
void setposi(int &xpos,int &ypos);
void drawApp();
void userMenu();
void userDraw();

//Main Function
int main()
{
int x,y,cl,a,b;
clrscr();
maxx=getmaxx();
maxy=getmaxy();
int g=DETECT,m;
a=0;
b=0;
initgraph(&g,&m,"../bgi");
setposi(a,b);
drawApp();
callmouse();
int mx=getmaxx();
int my=getmaxy();
do
{
	mouseposi(x,y,cl);
	//checking region of mouse
	setviewport(0,0,mx,my,0);
	if(cl==1)
	{
		if(x<=160)
		{
			//mouse is in menu region
			userMenu();
		}
		if(x>160)
		{
			//mouse is in drawing area
			userDraw();
		}
	}
}while(!kbhit());
getch();
mousehide();
//printf("\n\n\tPress any key to Exit");
getch();
return 0;
}

//UserDraw
void userDraw()
{
  int x,y,cl,x1,y1,x2,y2;
  int xradius,yradius,midx,midy;
  mouseposi(x,y,cl);
  if(cl==1)
  {
    x1=x;
    y1=y;
    while(cl==1)
    {
	mouseposi(x,y,cl);
	x2=x;
	y2=y;
    }
    setcolor(user.color);
    if(user.figure==1)
	line(x1,y1,x2,y2);
    else if(user.figure==2)
	rectangle(x1,y1,x2,y2);
    else if(user.figure==3)
    {
	midx = (x1+x2)/2;
	midy = (y1+y2)/2;
	xradius = abs((x1-x2))/2;
	yradius = abs((y1-y2))/2;
	ellipse(midx, midy, 0, 360,xradius, yradius);

    }

  }
}


//UserMenu
void userMenu()
{
  int x,y,cl;
  mouseposi(x,y,cl);
  if(cl==1)
  {
	//for first line of Color
	if(y>=70 && y<=90)
	{
		//for Black Color i.e. 0
		if(x>=18 && x<=38)  user.color=0;
		//for Blue Color i.e. 1
		if(x>=43 && x<=63)  user.color=1;
		//for Green Color i.e. 2
		if(x>=68 && x<=88)  user.color=2;
		//for Aqua Color i.e. 3
		if(x>=93 && x<=113) user.color=3;
		//for Red Color i.e. 4
		if(x>=118 && x<=138) user.color=4;
	}
	//for second line of Color
	if(y>=100 && y<=120)
	{
		//for Purple Color i.e. 5
		if(x>=18 && x<=38)   user.color=5;
		//for Yellow Color i.e. 6
		if(x>=43 && x<=63)   user.color=6;
		//for Gray Color i.e. 8
		if(x>=68 && x<=88)   user.color=8;
		//for Light Blue Color i.e. 9
		if(x>=93 && x<=113)  user.color=9;
		//for Light Green Color i.e. 10
		if(x>=118 && x<=138) user.color=10;
	}
	//for third line of Color
	if(y>=130 && y<=150)
	{
		//for Light Aqua i.e. 11
		if(x>=18 && x<=38)   user.color=11;
		//for Light Red Color i.e. 12
		if(x>=43 && x<=63)   user.color=12;
		//for Light Purple i.e. 13
		if(x>=68 && x<=88)   user.color=13;
		//for Light Yellow Color i.e. 14
		if(x>=93 && x<=113)  user.color=14;
		//for Bright White Color i.e. 15
		if(x>=118 && x<=138) user.color=15;
	}

	//for Figure Line
	if(y>=220 && y<=260 && x>=8 && x<=156) user.figure=1;
	//for Rectangle Line
	if(y>=265 && y<=305 && x>=8 && x<=156) user.figure=2;
	//for Circle Line
	if(y>=310 && y<=350 && x>=8 && x<=156) user.figure=3;
  }
}


//Mouse Functions

int callmouse()
{
      in.x.ax=1;
      int86(51,&in,&out);
      return 1;
}
void mouseposi(int &xpos,int &ypos,int &click)
{
      in.x.ax=3;
      int86(51,&in,&out);
      click=out.x.bx;
      xpos=out.x.cx;
      ypos=out.x.dx;
}

int mousehide()
{
      in.x.ax=2;
      int86(51,&in,&out);
      return 1;
}
void setposi(int &xpos,int &ypos)
{
      in.x.ax=4;
      in.x.cx=xpos;
      in.x.dx=ypos;
      int86(51,&in,&out);
}

//Function for views
void drawApp()
{
    int mx = getmaxx();
    int my = getmaxy();
    int midx= mx/2;
    int midy= my/2;
    int x,y;
    char *title="Paint Application";
 //header and footer
    setcolor(1);
    setviewport(0,0 ,mx ,my, 0);
    setfillstyle(SOLID_FILL,1);
    rectangle(0,0,mx,25);
    floodfill(3,3,10);

    setcolor(15);
    outtextxy(midx -(textwidth(title)/2),7,title);


 //footer
    setcolor(1);
    setviewport(0,my-30 ,mx ,my-25, 0);
    setfillstyle(SOLID_FILL,1);
    rectangle(0,0,mx,25);
    floodfill(3,3,10);

    setcolor(15);
    outtextxy(midx-70,7,"Copyright by Gouri Upadhyay");


 //tab
    setcolor(6);
    setviewport(5,27 ,45 ,my, 0);
    setfillstyle(SOLID_FILL,7);
    rectangle(0,0,155,420);
    floodfill(3,3,6);

    //Color Buttons
    setviewport(8,50,108,300,0);
    int color=0,j;
    x=10;
    y=20;


    for(j=0;j<15;j++)
    {
	if(color==7)
		color++;
	setfillstyle(SOLID_FILL,color++);
	bar(x,y,x+20,y+20);
	x=x+25;
	if(x==135)
	{
		x=10;
		y=y+30;
	}
    }


    //Figure Buttons
    setviewport(8,200,108,300,0);
    x=0;
    y=20;

    color=3;
    for(j=0;j<3;j++)
    {
	setfillstyle(SOLID_FILL,color);
	bar(x,y,x+148,y+40);
	setcolor(5);
	settextstyle(10,HORIZ_DIR,1); //7,8,10
	outtextxy(x+5,y-5,figure[j]);
	x=0;
	y+=40+5;
    }

 //body
    setcolor(6);
    setviewport(162,27 ,mx ,my, 0);
    setfillstyle(SOLID_FILL,15);      //3 8 10 15
    rectangle(0,0,472,420);
    floodfill(3,3,6);
}