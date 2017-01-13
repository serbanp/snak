#include <time.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace sf;
using namespace std;

int size=16;
int length=33;
int width=30;
int score1=0,score2=0;
int dx[5]={1,0,-1,0,0},dy[5]={0,-1,0,1,0};
int viteza=100;
int num1=1,num2=1,dir1=4,dir2=4;
int ok=0;
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
void meniu();
void game();
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
        num1++;score1++;
        FaMancare(m);
    }
    else
     if (s2[0].x==m.x && s2[0].y==m.y)
    {
        num2++;score2++;
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
        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            if (num1==1||dir1!=1)
        dir1=3;
        }
        else  if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            if (num1==1||dir1!=3)
        dir1=1;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            if (num1==1||dir1!=0)
        dir1=2;
            }
	    else if (Keyboard::isKeyPressed(Keyboard::Right))
	    {
	        if (num1==1||dir1!=2)
        dir1=0;
	    }

        if (ok==3)

    {

            if (Keyboard::isKeyPressed(Keyboard::S))
        {
            if (num2==1||dir2!=1)
        dir2=3;
        }
        else if (Keyboard::isKeyPressed(Keyboard::A))
        {
            if (num2==1||dir2!=0)
        dir2=2;
        }
        else if (Keyboard::isKeyPressed(Keyboard::W))
        {
            if (num2==1||dir2!=3)
        dir2=1;
        }
	    else if (Keyboard::isKeyPressed(Keyboard::D))
	    {
	        if (num2==1||dir2!=2)
        dir2=0;
	    }
    }
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
        if (ok>=2)
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
         if (s1[i].x==s1[0].x && s1[i].y==s1[0].y)
         {window.close();
         sf::RenderWindow window(sf::VideoMode(size*length, size*width), "INTRODU NUMELE");
         String sentence;
         Font font;
         font.loadFromFile("arial.ttf");

         Text text(sentence,font,40);
         text.setColor(Color(44,127,255));
         text.setStyle(Text::Bold);

         while (window.isOpen())
         {Event Event;
         while (window.pollEvent(Event))
         {if (Event::TextEntered)
         if (Event.text.unicode>=97&&Event.text.unicode<=122)
         sentence+=(char)Event.text.unicode;
         else if (Event.text.unicode==8&&sentence.getSize()>0)
         sentence.erase(sentence.getSize()-1,sentence.getSize());
         text.setString(sentence);
         break;
         }
        window.draw(text);
         window.display();
         window.clear();
         if (Keyboard::isKeyPressed(Keyboard::Escape))
        window.close();
         }
         }

        patratMancare.setPosition(m.x*size,  m.y*size);
        window.draw(patratMancare);
            if (Keyboard::isKeyPressed(Keyboard::Escape))
        {window.close();meniu();score1=0;score2=0;}

    if (ok==1)
        {
       sf::Font arial;
    arial.loadFromFile("arial.ttf");
    std::ostringstream ssScor;
    ssScor<<"Player : "<<score1;
    sf::Text Scor;
    Scor.setCharacterSize(20    );
    Scor.setPosition({10,10});
    Scor.setFont(arial);
    Scor.setString(ssScor.str());
    window.draw(Scor);}

    else if (ok==2)

    {sf::Font arial;
    arial.loadFromFile("arial.ttf");
    std::ostringstream ssScor;
    ssScor<<"Player : "<<score1;
    sf::Text Scor;
    Scor.setCharacterSize(20);
    Scor.setPosition({10,10});
    Scor.setFont(arial);
    Scor.setString(ssScor.str());
    window.draw(Scor);

    std::ostringstream ssScor2;
    ssScor2<<"200 IQ : "<<score2;
    sf::Text Scor2;
    Scor2.setCharacterSize(20);
    Scor2.setPosition({10,50});
    Scor2.setFont(arial);
    Scor2.setString(ssScor2.str());
    window.draw(Scor2);
}
    else if (ok==3)
   {
       sf::Font arial;
    arial.loadFromFile("arial.ttf");
    std::ostringstream ssScor;
    ssScor<<"Player 1 : "<<score1;
    sf::Text Scor;
    Scor.setCharacterSize(20);
    Scor.setPosition({10,10});
    Scor.setFont(arial);
    Scor.setString(ssScor.str());
    window.draw(Scor);

    std::ostringstream ssScor2;
    ssScor2<<"Player 2 : "<<score2;
    sf::Text Scor2;
    Scor2.setCharacterSize(20);
    Scor2.setPosition({10,50});
    Scor2.setFont(arial);
    Scor2.setString(ssScor2.str());
    window.draw(Scor2);
}
        window.display();
    }


}


void meniu()
{
    sf::RenderWindow window(sf::VideoMode(size*length+size, size*width+size), "Snake");
 Texture meniup,meniu2,meniu3,meniu4,meniu5;
 int m1x,m1y;
    meniup.loadFromFile("images/meniu.jpg");
    meniu2.loadFromFile("images/meniu2.jpg");
    meniu3.loadFromFile("images/meniu3.jpg");
    meniu4.loadFromFile("images/meniu4.jpg");
    meniu5.loadFromFile("images/meniu5.jpg");
	Sprite menp(meniup);
	Sprite men2(meniu2);
	Sprite men3(meniu3);
	Sprite men4(meniu4);
	Sprite men5(meniu5);
    window.draw(menp);
    window.display();
	while (window.isOpen())
    {sf::Vector2u size = window.getSize();
unsigned int width = size.x;
unsigned int height = size.y;
sf::Vector2i localPosition = sf::Mouse::getPosition(window);
if (localPosition.x>0&&localPosition.y>0)
{m1x=size.x*100/localPosition.x;
m1y=size.y*100/localPosition.y;}
    Event Event;
        while (window.pollEvent(Event))
    {
    if (m1x>136&&m1x<332&&m1y>324&&m1y<393)
            {
                window.draw(men2);
                if (Event::MouseButtonPressed)
                if (Event.mouseButton.button==Mouse::Left)
                {  score1=0;score2=0;
                    window.close();ok=1;game();}
}
    else if (m1x>123&&m1x<332&&m1y>207&&m1y<237)
     {
                window.draw(men3);
                if (Event::MouseButtonPressed)
                if (Event.mouseButton.button==Mouse::Left) {score1=0;score2=0;
                    window.close();ok=2;game();}
                }
    else if (m1x>149&&m1x<332&&m1y>155&&m1y<172)
    {
        window.draw(men4);
                if (Event::MouseButtonPressed)
                if (Event.mouseButton.button==Mouse::Left) {score1=0;score2=0;
                    window.close();ok=3;game();}
    }
    else if (m1x>130&&m1x<332&&m1y>123&&m1y<131)
        {
    window.draw(men5);
                if (Event::MouseButtonPressed)
                if (Event.mouseButton.button==Mouse::Left) {int urmeaza=1;}//leaderboard}
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
