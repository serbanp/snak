#include <time.h>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

int size=16;
int length=33;
int width=30;

int dx[5]={1,0,-1,0,0},dy[5]={0,-1,0,1,0};
int viteza=100;
int num1=1,num2=1,dir1=4,dir2=4;
int ok;

int modulo(int a, int b)
{
    return (a%b+b)%b;
}

struct sarpe{
    int x,y;
};

struct mancare{
    int x,y;
} m;

sarpe s1[10000],s2[10000];

void FaMancare(mancare &m)
{
    int ok=0;
    while (ok == 0)
    {
        m.x=abs(rand())%length;
        m.y=abs(rand())%width;
        ok = 1;
        for (int i=0;i<num1;i++)
         if (s1[i].x==m.x && s1[i].y==m.y)
          {
            ok = 0;
            break;
          }
        for (int i=0;i<num2;i++)
         if (s2[i].x==m.x && s2[i].y==m.y)
          {
            ok = 0;
            break;
          }
    }
}


int inteligent()
{
    int  prim=0,ultim=0,i,coada[2][10500]={0},x,y,mat[200][200]={0},moveAI[100000]={0},nrMovesAI;

    coada[0][0]=s2[0].x;
    coada[1][0]=s2[0].y;

    for (i=1;i<num2;i++)
     mat[s2[i].x][s2[i].y] = -1;

    while (prim<=ultim)
    {
        for (i=0;i<4;i++)
        {
            x = modulo(coada[0][prim] + dx[i],length);
            y = modulo(coada[1][prim] + dy[i],width);
            if (mat[x][y]==0)// && x>=0 && x<length && y>=0 && y<width)
            {
                mat[x][y]=mat[modulo(x-dx[i],length)][modulo(y-dy[i],width)] + 1;
                ultim++;
                coada[0][ultim] = x;
                coada[1][ultim] = y;
            }
        }
        if(mat[m.x][m.y]>0) break;
        prim++;
    }

    x=m.x;
    y=m.y;
    if(mat[m.x][m.y]==0)
    {
      for (i=0;i<4;i++)
        if (mat[modulo(s2[0].x + dx[i],length)][modulo(s2[0].y + dy[i],width)] != -1) return i;
      return 0;
    }

    nrMovesAI = 0;
    while (x!=s2[0].x || y!=s2[0].y)
    {
        if (mat[x][y]==1)
        {
         for (i=0;i<4;i++)
          if ( modulo(x+dx[i],length)==s2[0].x && modulo(y+dy[i],width)==s2[0].y )
          {
            nrMovesAI++;
            moveAI[nrMovesAI] = (i+2)%4;
            x=modulo(x+dx[i],length);
            y=modulo(y+dy[i],width);
            break;
          }
        }
        else
        for (i=0;i<4;i++)
         if ( mat[modulo(x+dx[i],length)][modulo(y+dy[i],width)] + 1 == mat[x][y] )
        {
            nrMovesAI++;
            moveAI[nrMovesAI] = (i+2)%4;
            x=modulo(x+dx[i],length);
            y=modulo(y+dy[i],width);
            break;
        }
    }
    return moveAI[nrMovesAI];

}


void Miscare()
{
    for (int i=num1;i>0;i--)
    {
        s1[i].x=s1[i-1].x;
        s1[i].y=s1[i-1].y;
    }
    s1[0].x += dx[dir1];
    s1[0].y += dy[dir1];

    if (s1[0].x>=length) s1[0].x=0;
    if (s1[0].x<0) s1[0].x=length-1;
    if (s1[0].y>=width) s1[0].y=0;
    if (s1[0].y<0) s1[0].y=width-1;

    for (int i=num2;i>0;i--)
    {
        s2[i].x=s2[i-1].x;
        s2[i].y=s2[i-1].y;
    }
    s2[0].x += dx[dir2];
    s2[0].y += dy[dir2];

    if (s2[0].x>=length) s2[0].x=0;
    if (s2[0].x<0) s2[0].x=length-1;
    if (s2[0].y>=width) s2[0].y=0;
    if (s2[0].y<0) s2[0].y=width-1;

    if (s1[0].x==m.x && s1[0].y==m.y)
    {
        num1++;
        FaMancare(m);
    }
    else
     if (s2[0].x==m.x && s2[0].y==m.y)
    {
        num2++;
        FaMancare(m);
    }

    //inteligent
    if (ok==2) dir2=inteligent();
}

void AI()
{
    s2[0].x=abs(rand())%length;
    s2[0].y=abs(rand())%width;
    num2=1;
}

void Player()
{
    s1[0].x=abs(rand())%length;
    s1[0].y=abs(rand())%width;
    num1=1;
}
void game()
{
    sf::RenderWindow window(sf::VideoMode(size*length, size*width), "Snake");

    Texture teren,cs,mancare,capsarpe,corpai,capai;

	teren.loadFromFile("images/teren.jpg");
	cs.loadFromFile("images/corpsarpe.jpg");
    mancare.loadFromFile("images/mancare.jpg");
    capsarpe.loadFromFile("images/capsarpe.jpg");
    corpai.loadFromFile("images/corpai.jpg");
    capai.loadFromFile("images/capai.jpg");


	Sprite patratP(teren);
	Sprite patratSarpe(cs);
	Sprite patratMancare(mancare);
    Sprite patratCap(capsarpe);
    Sprite corpsai(corpai);
    Sprite capsai(capai);
	srand(time(NULL));

    sf:Clock clock;
    m.x=abs(rand())%length;
    m.y=abs(rand())%width;
    AI();Player();
    while (window.isOpen())
    {
        sf::Event event;
        float timp = clock.getElapsedTime().asMilliseconds();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) dir1=3;
        if (Keyboard::isKeyPressed(Keyboard::Left)) dir1=2;
        if (Keyboard::isKeyPressed(Keyboard::Up)) dir1=1;
	    if (Keyboard::isKeyPressed(Keyboard::Right))  dir1=0;

        if (timp>viteza)
        {
            clock.restart();
            Miscare();
        }
        window.clear();

        for (int i=0; i<length; i++)
         for (int j=0; j<width; j++)
		  {
		    patratP.setPosition(i*size,j*size);
		    window.draw(patratP);
          }


        //DrawAI(window);
        if (ok==2)
          {
              for (int i=1;i<num2;i++)
	        {corpsai.setPosition(s2[i].x*size, s2[i].y*size);
	        window.draw(corpsai);
         }
              capsai.setPosition(s2[0].x*size,s2[0].y*size);
          window.draw(capsai);
            for (int i=1;i<num2;i++)
         if (s2[i].x==s2[0].x && s2[i].y==s2[0].y) window.close();
    }


        //DrawPlayer(window);
        for (int i=1;i<num1;i++)
	     {
	        patratSarpe.setPosition(s1[i].x*size, s1[i].y*size);
	        window.draw(patratSarpe);
         }
        patratCap.setPosition(s1[0].x*size,s1[0].y*size);
        window.draw(patratCap);

        for (int i=1;i<num1;i++)
         if (s1[i].x==s1[0].x && s1[i].y==s1[0].y) window.close();
        patratMancare.setPosition(m.x*size,  m.y*size);
        window.draw(patratMancare);
            if (Keyboard::isKeyPressed(Keyboard::Escape))
        window.close();
        window.display();
    }

}
void meniu()
{
    sf::RenderWindow window(sf::VideoMode(size*length+size, size*width+size), "Snake");
 Texture meniup,meniu2,meniu3;
 int m1x,m1y;
    meniup.loadFromFile("images/meniu.jpg");
    meniu2.loadFromFile("images/meniu2.jpg");
    meniu3.loadFromFile("images/meniu3.jpg");
	Sprite menp(meniup);
	Sprite men2(meniu2);
	Sprite men3(meniu3);

	while (window.isOpen())
    {sf::Vector2u size = window.getSize();
unsigned int width = size.x;
unsigned int height = size.y;
sf::Vector2i localPosition = sf::Mouse::getPosition(window);
m1x=size.x*100/localPosition.x;
m1y=size.y*100/localPosition.y;
    Event Event;
        while (window.pollEvent(Event))
    {
    if (m1x>136&&m1x<332&&m1y>324&&m1y<393)
            {
                window.draw(men2);
                if (Event::MouseButtonPressed)
                if (Event.mouseButton.button==Mouse::Left) {window.close();ok=1;game();}
                }
    else if (m1x>123&&m1x<332&&m1y>207&&m1y<237)
     {
                window.draw(men3);
                if (Event::MouseButtonPressed)
                if (Event.mouseButton.button==Mouse::Left) {window.close();ok=2;game();}
                }
            else window.draw(menp);


            window.display();
    if (Keyboard::isKeyPressed(Keyboard::Escape))
        window.close();}
    }
}

int main()
{
    meniu();
}
