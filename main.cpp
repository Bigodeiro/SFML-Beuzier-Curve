#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <math.h>

#define WIDTH 1800
#define HEIGTH 1000

#define PONTO0_CORD 614 , 900
#define PONTO1_CORD 295, 502
#define PONTO2_CORD 100 , 900
#define PONTO3_CORD 1600 , 500

#define PONTOS_PRIMARIOS   true
#define LINHAS_PRIMARIAS   true

#define PONTOS_SECUNDARIOS true
#define LINHAS_SECUNDARIAS true

#define PONTOS_TERCEARIOS  true
#define LINHAS_TERCEARIAS  true

#define PONTOS_FINAIS      true
#define LINHAS_FINAIS      true

class circleObj 
{
  public:

    int mass;
    float radius;

    sf::Vector2f pos;
    sf::Vector2f velocity;

    sf::CircleShape sfCircle;
    sf::Color color;


    void applyChanges()
    {
        sfCircle.setFillColor(color);
        sfCircle.setRadius(radius);

        pos.x += velocity.x;
        pos.y += velocity.y;

        sfCircle.setPosition(pos.x - radius, pos.y - radius);
    };


    circleObj(sf::Vector2f cPos, float cRadius, int cMass, sf::Color cColor)
    {
        radius = cRadius;
        mass = cMass;
        color = cColor;

        velocity.x = 0;
        velocity.y = 0;

        pos = cPos;

        sfCircle = sf::CircleShape(cRadius);
        sfCircle.setFillColor(color);
    };
};

float lerp(float a, float b, float t)
{
    return (1.0f - t) * a + b * t;
}

sf::Vector2f vectorLerp(sf::Vector2f a, sf::Vector2f b, float t)
{
    return sf::Vector2f(lerp(a.x, b.x, t),lerp(a.y, b.y, t));
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGTH), "SFML!", sf::Style::Close | sf::Style::Titlebar);

    circleObj ponto0(sf::Vector2f(PONTO0_CORD), 15, 0, sf::Color(237, 237, 237));
    ponto0.applyChanges();
    circleObj ponto1(sf::Vector2f(PONTO1_CORD), 15, 0, sf::Color(237, 237, 237));
    ponto1.applyChanges();
    circleObj ponto2(sf::Vector2f(PONTO2_CORD), 15, 0, sf::Color(237, 237, 237));
    ponto2.applyChanges();
    circleObj ponto3(sf::Vector2f(PONTO3_CORD), 15, 0, sf::Color(237, 237, 237));
    ponto3.applyChanges();

    circleObj lerp0(sf::Vector2f(0,0), 10,0,sf::Color::Red);
    circleObj lerp1(sf::Vector2f(0,0), 10,0,sf::Color::Red);
    circleObj lerp2(sf::Vector2f(0,0), 10,0,sf::Color::Red);

    circleObj subLerp0(sf::Vector2f(0,0), 7.5f, 0,sf::Color::Blue);
    circleObj subLerp1(sf::Vector2f(0,0), 7.5f, 0,sf::Color::Blue);

    circleObj finalLerp(sf::Vector2f(0,0), 5, 0,sf::Color::Green);

    float t = 0.0f;
    float step = 0.0001f;
    int frame = 0;
    int count = 1;

    sf::Vertex linhasPrimarias[]=
    {
        sf::Vertex(sf::Vector2f(ponto0.pos)),
        sf::Vertex(sf::Vector2f(ponto1.pos)),
        sf::Vertex(sf::Vector2f(ponto1.pos)),
        sf::Vertex(sf::Vector2f(ponto2.pos)),
        sf::Vertex(sf::Vector2f(ponto2.pos)),
        sf::Vertex(sf::Vector2f(ponto3.pos))
    };

    sf::Vertex linhasSecundarias[]=
    {
        sf::Vertex(sf::Vector2f(0,0)),
        sf::Vertex(sf::Vector2f(0,0)),
        sf::Vertex(sf::Vector2f(0,0)),
        sf::Vertex(sf::Vector2f(0,0))
    };

    sf::Vertex linhaFinal[]=
    {
        sf::Vertex(sf::Vector2f(0,0)),
        sf::Vertex(sf::Vector2f(0,0))
    };

    sf::Vertex curva[2000];

    curva[0] = ponto0.pos;
    curva[2000] = ponto0.pos;

    while (window.isOpen())//! cada iteração aqui é um frame
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                
                window.close();

                break;
            }
        }

    //!codigo a ser executado todo frame

    if (t < 1)
    {
        t += step;
        lerp0.pos = vectorLerp(ponto0.pos, ponto1.pos, t);
        lerp1.pos = vectorLerp(ponto1.pos, ponto2.pos, t);
        lerp2.pos = vectorLerp(ponto2.pos, ponto3.pos, t);

        subLerp0.pos = vectorLerp(lerp0.pos, lerp1.pos, t);
        subLerp1.pos = vectorLerp(lerp1.pos, lerp2.pos, t);


        finalLerp.pos = vectorLerp(subLerp0.pos, subLerp1.pos, t);


        linhasSecundarias[0] = lerp0.pos;
        linhasSecundarias[1] = lerp1.pos;
        linhasSecundarias[2] = lerp1.pos;
        linhasSecundarias[3] = lerp2.pos;
        linhaFinal[0] = subLerp0.pos;
        linhaFinal[1] = subLerp1.pos;



        if(frame == 10)
        {
            std::cout << count << std:: endl;
            curva[count] = finalLerp.pos;
            count++;
            curva[count] = finalLerp.pos;
            count++;

            frame = 0;
        }
        frame++;
    }


    std::cout << "tot: " << count << std::endl;

    lerp0.applyChanges();
    lerp1.applyChanges();
    lerp2.applyChanges();

    subLerp0.applyChanges();
    subLerp1.applyChanges();

    finalLerp.applyChanges();

    window.clear();

    //? renderiza algo para a tela, modificando-a

    if (LINHAS_PRIMARIAS)
    {
        window.draw(linhasPrimarias, 6, sf::Lines);
    }
    
    if (PONTOS_PRIMARIOS)
    {
        window.draw(ponto0.sfCircle);
        window.draw(ponto1.sfCircle);
        window.draw(ponto2.sfCircle);
        window.draw(ponto3.sfCircle);
    }

    if (LINHAS_SECUNDARIAS)
    {
        window.draw(linhasSecundarias, 4, sf::Lines);
    }
    
    if (PONTOS_SECUNDARIOS)
    {
        window.draw(lerp1.sfCircle);
        window.draw(lerp2.sfCircle);
        window.draw(lerp0.sfCircle);
    }

    if (LINHAS_TERCEARIAS)
    {
        window.draw(linhaFinal, 2, sf::Lines);
    }

    if (PONTOS_TERCEARIOS)
    {
        window.draw(subLerp0.sfCircle);
        window.draw(subLerp1.sfCircle);
    }

    if (LINHAS_FINAIS)
    {
        window.draw(curva, count, sf::Lines);
    }
    
    if (PONTOS_FINAIS)
    {
        window.draw(finalLerp.sfCircle);
    }

    //? recarrega a tela, fazendo com que as mudanças sejam efetivadas
    window.display();

    }
    return 0;
}