#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main()
{
    // Create the main window
    RenderWindow app(VideoMode(800, 600), "SFML window");

    Text text;
    Font font;
    font.loadFromFile("arial.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setString("asdf");
    text.setFillColor(Color::Red);
    string input="as";

    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed){
                app.close();
            }

            if(event.type==Event::TextEntered){
                input+=static_cast<char>(event.text.unicode);
            }


        }
        app.clear(Color::White);

        text.setString(input);
        app.draw(text);

        app.display();
    }

    return EXIT_SUCCESS;
}
