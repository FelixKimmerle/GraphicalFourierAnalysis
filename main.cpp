#include <iostream>
#include "Math/MathParser.hpp"
#include <SFML/Graphics.hpp>
#include <Plot/RoundChart.hpp>
#include <FT/FT.hpp>
#include "Plot/RectanglePlot.hpp"
int main(int argc, char **argv)
{
    std::string sSource = "";
    if (argc == 1)
    {
        std::cout << "Formel: ";
        std::cin >> sSource;
    }
    else
    {
        sSource = argv[1];
        std::cout << "Formel: " << sSource << std::endl;
    }

    MathParser mp;
    mp.Parse(sSource);
    auto programm = mp.Calc();
    programm.Print();

    sf::ContextSettings settings(0, 0, 4);

    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    RoundChart chart(200, 1000);
    chart.setPosition(100, 200);
    std::vector<float> data(1000);

    RectanglePlot rp(sf::Vector2f(600, 100),0.1f);
    rp.setPosition(100, 600);

    for (size_t i = 0; i < 1000; i++)
    {
        data[i] = programm.Calc(i/100.f).real();
    }
    sf::Clock clock;
    unsigned int uiFrames = 0;

    FT ft(data);
    unsigned int c = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }
            else if (event.type == sf::Event::Resized)
            {
                window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                chart.setPosition(event.size.width / 2, 200);
            }
        }

        window.clear();
        window.draw(chart);
        window.draw(rp);
        window.display();
        uiFrames++;
        for (size_t i = 0; i < 5; i++)
        {
            ft.Update(0.001);
        }
        
        auto center = ft.Update(0.001);
        rp.Add(center.real());
        c++;
        chart.Update(ft.GetData(), center);
        if (clock.getElapsedTime().asMilliseconds() >= 1000)
        {
            std::cout << uiFrames << "FPS" << std::endl;
            uiFrames = 0;
            clock.restart();
        }
    }

    return EXIT_SUCCESS;
}