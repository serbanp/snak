#include <time.h>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

int size=16;
int length=20;
int width=40;

int dir=4,dx[5]={1,0,-1,0,0},dy[5]={0,-1,0,1,0},viteza=5,num=1;


struct sarpe{
    int x,y;
};

struct mancare{
    int x,y;
} m;
sarpe s[100];

void FaMancare(mancare &m)
{
    int ok=0;
    while (ok == 0)
    {
        m.x=rand()%length;
        m.y=rand()%width;
        ok = 1;
        for (int i=0;i<num-1;i++)
         if (s[i].x==m.x && s[i].y==m.y)
          {
            ok = 0;
            break;
          }
    }
    std::cout<<m.x<<' '<<m.y;
}

int inteligent()
{
    int  prim,ultim,i,coada[2][10500]={0},x,y,mat[200][200]={0},moveAI[100000]={0},nrMovesAI;

    coada[0][0]=s[0].x;
    coada[1][0]=s[0].y;

    for (i=1;i<num;i++)
     mat[s[i].x][s[i].y] = -1;

    prim=0;
    ultim=0;
    while (prim<=ultim)
    {
        for (i=0;i<4;i++)
        {
            x = coada[0][prim] + dx[i];
            y = coada[1][prim] + dy[i];
            if (mat[x][y]==0 && x>=0 && x<length && y>=0 && y<width)
            {
                mat[x][y]=mat[x-dx[i]][y-dy[i]] + 1;
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
        if (mat[s[0].x + dx[i]][s[0].y + dy[i]] != -1) return i;
      return 0;
    }
    nrMovesAI = 0;
    while (x!=s[0].x || y!=s[0].y)
    {
        if (mat[x][y]==1)
        {
         for (i=0;i<4;i++)
          if ( x+dx[i]==s[0].x && y+dy[i]==s[0].y )
          {
            nrMovesAI++;
            moveAI[nrMovesAI] = (i+2)%4;
            x=x+dx[i];
            y=y+dy[i];
            break;
          }
        }
        else
        for (i=0;i<4;i++)
         if ( mat[x+dx[i]][y+dy[i]] + 1 == mat[x][y] )
        {
            nrMovesAI++;
            moveAI[nrMovesAI] = (i+2)%4;
            x=x+dx[i];
            y=y+dy[i];
            break;
        }
    }
    return moveAI[nrMovesAI];

}


void Miscare()
{
    for (int i=num;i>0;i--)
    {
        s[i].x=s[i-1].x;
        s[i].y=s[i-1].y;
    }
    s[0].x += dx[dir];
    s[0].y += dy[dir];
    if (s[0].x==m.x && s[0].y==m.y)
    {
        num++;
        FaMancare(m);
    }

    if (s[0].x>=length) s[0].x=0;
    if (s[0].x<0) s[0].x=length-1;
    if (s[0].y>=width) s[0].y=0;
    if (s[0].y<0) s[0].y=width-1;
    //inteligent
    dir=inteligent();
}


int main()
{
    srand(time(NULL));
    s[0].x=rand()%length;
    s[0].y=rand()%width;
    sf::RenderWindow window(sf::VideoMode(size*length, size*width), "Snake");

    Texture t1,t2,t3;
	t1.loadFromFile("images/white.png");
	t2.loadFromFile("images/corpsarpe.png");
    t3.loadFromFile("images/mancare.png");

	Sprite patratAlb(t1);
	Sprite patratSarpe(t2);
	Sprite patratMancare(t3);

    sf:Clock clock;
    m.x=rand()%length;
    m.y=rand()%width;
    //inteligent
    dir=inteligent();


    while (window.isOpen())
    {
        sf::Event event;
        float timp = clock.getElapsedTime().asMilliseconds();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) dir=3;
        if (Keyboard::isKeyPressed(Keyboard::Left)) dir=2;
        if (Keyboard::isKeyPressed(Keyboard::Up)) dir=1;
	    if (Keyboard::isKeyPressed(Keyboard::Right))  dir=0;

        if (timp>viteza)
        {
            clock.restart();
            Miscare();
        }
        window.clear();

        for (int i=0; i<length; i++)
         for (int j=0; j<width; j++)
		  {
		    patratAlb.setPosition(i*size,j*size);
		    window.draw(patratAlb);
          }

        for (int i=0;i<num;i++)
	     {
	        patratSarpe.setPosition(s[i].x*size, s[i].y*size);
	        window.draw(patratSarpe);
         }

        patratMancare.setPosition(m.x*size,  m.y*size);
        window.draw(patratMancare);
        for (int i=1;i<num;i++)
         if (s[i].x==s[0].x && s[i].y==s[0].y) window.close();

        window.display();
    }

    return 0;
}
