#include <time.h>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

int size=16;
int length=33;
int width=30;

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
    for (int i=0;i<num-1;i++)
        while (s[i].x==m.x&&s[i].y==m.y)
    {
         m.x=rand()%length;
    m.y=rand()%width;
    }
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
void game()
{
    srand(time(NULL));
    s[0].x=rand()%length;
    s[0].y=rand()%width;
    sf::RenderWindow window(sf::VideoMode(size*length+size, size*width+size), "SFML works!");

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

        for (int i=0; i<=length; i++)
         for (int j=0; j<=width; j++)
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
       if (s[i].x==s[0].x && s[i].y==s[0].y)
       {
           window.close();
           for (int i=1;i<num;i++)
            {
                s[i].x=0;
                s[i].y=0;
            }
            num=1;dir=4;
             s[0].x+=dy[dir];
    s[0].y+=dx[dir];


       }
         if (Keyboard::isKeyPressed(Keyboard::Escape))
        window.close();
        window.display();
    }

}


int main()
{
//game();
sf::RenderWindow window(sf::VideoMode(size*length+size, size*width+size), "SFML works!");
 Texture t4,t5;
    t4.loadFromFile("images/men.jpg");
    t5.loadFromFile("images/men2.jpg");
	Sprite nebunie(t4);
	Sprite nebunie2(t5);
	window.clear();
	while (window.isOpen())
    {
    Event Event;
        while (window.pollEvent(Event))
    {sf::Vector2i position = sf::Mouse::getPosition();
    //cout<<position.x<<" "<<position.y<<"\n";
            if (position.x>583&&position.x<820&&position.y>293&&position.y<319)
            {
                window.draw(nebunie2);
                if (Event::MouseButtonPressed)
                if (Event.mouseButton.button==Mouse::Left) {game();window.close();}
                }
            else window.draw(nebunie);
            window.display();
    if (Keyboard::isKeyPressed(Keyboard::Escape))
        window.close();}
    }
    return 0;
}
