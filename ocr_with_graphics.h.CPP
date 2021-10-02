#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<iostream.h>
#include<math.h>
#include<snap.h>
#include<fstream.h>
#include<string.h>

union REGS in,out;
int k = 0, l = 0, d = 1,e=0,n = 0, counter = 0, x_i = 0, y_i = 0, x_f = 0, y_f = 0;
int x_prev, y_prev;
int arr[1000];
int gamma[1000][4];
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
void function_rectangle(int cl, int x, int y)
{
if(e != 0)
e++;
if(e > 800)
{ k= 0;
counter = 0;
e = 0;
}
if(cl == 1 && k == 0 )
{k++;
l++;
if(counter == 0)
{ x_i = x, y_i = y;
counter++;
n++;
arr[n] = 2;
gamma[n][0]= x_i, gamma[n][1] = y_i;
}
}
if(cl == 0 && l != 0)
{ cleardevice();
setfillstyle(1, 4);
bar(x_i, y_i, x, y);
l++;
gamma[n][2]= x, gamma[n][3]= y;
}
if(cl == 1 && l > 50)
{//printf("\nclick stopped");
l = 0;
e++;
}
if(l > 100)
l = 100;
if(d > 100)
d = 100;
if(e > 5000)
e = 1000;
}

/////////////////////////////////////////////
void draw()
{  for(int i = 0; i < n ; i++)
{  if(arr[i] == 1)
   { setcolor(5);
     line(gamma[i][0], gamma[i][1], gamma[i][2], gamma[i][3]);
   }
   if(arr[i] == 2)
   { setfillstyle(1, 4);
     bar(gamma[i][0], gamma[i][1], gamma[i][2], gamma[i][3]);
   }
   if(arr[i] == 3)
   { setfillstyle(1,3);
     setcolor(3);
     fillellipse(gamma[i][0], gamma[i][1], gamma[i][2], gamma[i][3]);
   }
}
}
/////////////////////////////////////////////
void function_line(int cl,int x,int y)
{

if(e != 0)
e++;
if(e > 500)
{ k= 0;
counter = 0;
e = 0;
}
if(cl == 1 && k == 0 )
{k++;
l++;
if(counter == 0)
{ x_i = x, y_i = y;
counter++;
n++;
arr[n]= 1;
gamma[n][0]= x_i, gamma[n][1] = y_i;
}
}
if(cl == 0 && l != 0)
{ cleardevice();
setcolor(5);
line(x_i, y_i, x, y);
l++;
gamma[n][2]= x, gamma[n][3]= y;
}
if(cl == 1 && l > 50)
{//printf("\nclick stopped");
l = 0;
e++;
}
if(l > 100)
l = 100;
if(d > 100)
d = 100;
if(e > 5000)
e = 1000;
}
////////////////////////////////////////////////
void function_circle(int cl,int x,int y)
{
if(e != 0)
e++;
if(e > 500)
{ k= 0;
counter = 0;
e = 0;
}
if(cl == 1 && k == 0 )
{k++;
l++;
if(counter == 0)
{ x_i = x, y_i = y;
counter++;
n++;
arr[n]= 3;
gamma[n][0]= x_i, gamma[n][1] = y_i;
}
}
if(cl == 0 && l != 0)
{ cleardevice();
setfillstyle(1,3);
setcolor(3);
int x_diff = pow(x_i - x, 2);
int y_diff = pow(y_i - y, 2);
int radius = pow(x_diff + y_diff, 0.5);
fillellipse(gamma[n][0],gamma[n][1], radius, radius);
l++;
gamma[n][2]= radius, gamma[n][3]= radius;
}
if(cl == 1 && l > 50)
{//printf("\nclick stopped");
l = 0;
e++;
}
if(l > 100)
l = 100;
if(d > 100)
d = 100;
if(e > 5000)
e = 1000;
}
////////////////////////////////////////////////
void function_write(int cl,int x,int y)
{
  if(cl == 1)
  { setcolor(6);
  setfillstyle(1, 6);
  fillellipse(x, y, 2, 2);
  }
}
////////////////////////////////////////////////
void function_erase(int cl,int x,int y)
{ if(cl == 1)
{  setcolor(0);
  setfillstyle(0, 6);
  fillellipse(x, y, 2, 2);
}
}
void save()
{ fstream f;
f.open("STAT.txt", ios::out);
f<<"1";
f.close();
}
////////////////////////////////////////////////
int main()
{
int x,y,cl,a,b;
fstream new_;
new_.open("PRED.txt", ios::out);
new_.close();
clrscr();
int g=DETECT,m;
initgraph(&g,&m,"C:\\TC\\BGI");
a=200;
b=300;
setposi(a,b);
callmouse();
int ch = 0;
do{
mouseposi(x,y,cl);
gotoxy(10, 10);
//printf("\n\tMouse Position is: %d,%d,%d",x,y,k);
delay(1);
//printf("\n\tClick: %d",cl);
//printf("\n\tPress any key to hide the mouse");
//function_rectangle(cl, x, y)
ch = inportb(0x60);

if (ch == 30)
function_line(cl, x, y);
if(ch == 31)
function_rectangle(cl, x, y);
if(ch == 32)
function_circle(cl, x, y);
draw();
if(ch == 33)
function_write(cl, x, y);
if(ch == 34)
function_erase(cl, x, y);
if(ch == 35)
save();
if(ch == 36)
cleardevice();
}while(inportb(0x60)!=1);
settextstyle(8, 0, 2);
fstream f;
f.open("PRED.txt", ios::in);
ifstream p("PRED.txt");
char s[80], line_[100] = "";
while(!f.eof())
{ f.getline(s, 80);
strcat(line_, s);
}
outtextxy(150, 150, line_);
mousehide();
while(inportb(0x60)!=37);
//printf("\n\n\tPress any key to Exit\n");
getch();
return 0;
}