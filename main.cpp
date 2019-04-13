#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main()
{
    // Create the main window
    RenderWindow app(VideoMode(800, 600), "SFML window");

    // Load a sprite to display
    Texture texture;
    if (!texture.loadFromFile("cb.bmp"))
        return EXIT_FAILURE;
    Sprite sprite(texture);

	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == Event::Closed)
                app.close();
        }

        // Clear screen
        app.clear();

        // Draw the sprite
        app.draw(sprite);

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
