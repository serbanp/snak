#include <time.h>
#include <SFML/Graphics.hpp>
using namespace sf;

int size=16;
int length=20;
int width=40;

int dir=4,dx[5]={1,0,-1,0,0},dy[5]={0,-1,0,1,0},viteza=100,num=1;

struct sarpe{
    int x,y;
};

struct mancare{
    int x,y;
} m;
sarpe s[100];

void FaMancare(mancare &m)
{
    m.x=rand()%length;
    m.y=rand()%width;
}

void Miscare()
{
    for (int i=num;i>0;i--)
    {
        s[i].x=s[i-1].x;
        s[i].y=s[i-1].y;
    }
    s[0].x+=dy[dir];
    s[0].y+=dx[dir];
    if (s[0].x==m.x && s[0].y==m.y)
    {
        num++;
        FaMancare(m);
    }

    if (s[0].x>length) s[0].x=0;
    if (s[0].x<0) s[0].x=length;
    if (s[0].y>width) s[0].y=0;
    if (s[0].y<0) s[0].y=width;

}


int main()
{
    srand(time(NULL));
    s[0].x=rand()%length;
    s[0].y=rand()%width;
    sf::RenderWindow window(sf::VideoMode(size*length, size*width), "SFML works!");

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

    while (window.isOpen())
    {
        sf::Event event;
        float timp = clock.getElapsedTime().asMilliseconds();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) dir=1;
	    if (Keyboard::isKeyPressed(Keyboard::Right))  dir=3;
	    if (Keyboard::isKeyPressed(Keyboard::Up)) dir=2;
		if (Keyboard::isKeyPressed(Keyboard::Down)) dir=0;


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
