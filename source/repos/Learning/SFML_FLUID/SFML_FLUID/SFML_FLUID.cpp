#include <iostream>
#include <cmath>
#include "SFML/Graphics.hpp"

const int   WindowResolution		  = 500;
const float SimulationResolution      = 100.f; //Square resolution
const float SimulationResolutionScale = 5.f; //A fluid simulation will probably run at 100x100 pixels but be rendered in a 500x500 window

sf::Color RandomColor(float min_rgb, float max_rgb) {
	int r_nums[3];

	for (int i = 0; i < 3; i++){
		r_nums[i] = trunc(min_rgb + static_cast <float> (rand()) / static_cast <float> (RAND_MAX / max_rgb));
	}

	return sf::Color(r_nums[0], r_nums[1], r_nums[2]);
}

void RandomizePixels(sf::Image& Image) {	
	for (int i = 0; i < SimulationResolution; i++){
		for (int j = 0; j < SimulationResolution; j++){
			Image.setPixel(i, j, RandomColor(0.f, 255.f));
		}
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "Euler Simulation");
	window.setFramerateLimit(0);
	sf::Clock clock;

	sf::RectangleShape rectangle(sf::Vector2f(50.0, 50.0));
	sf::Color RandomColor(255.f, 200.f, 190.f);
	
	rectangle.setFillColor(sf::Color::Green);

	// So, I think I have to create a shape -> an image (PixelsImage) -> texture from the image -> combine into sprite and display

	sf::Image PixelsImage;
	PixelsImage.create(int(SimulationResolution), int(SimulationResolution), sf::Color::White);
	RandomizePixels(PixelsImage);
	
	sf::Texture PixelTexture;
	PixelTexture.loadFromImage(PixelsImage);

	sf::Sprite PixelSprite;
	PixelSprite.setTexture(PixelTexture);
	PixelSprite.setScale(SimulationResolutionScale, SimulationResolutionScale);

	
	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		
		RandomizePixels(PixelsImage);
		PixelTexture.update(PixelsImage);
		
		window.clear();
		window.draw(PixelSprite);
		window.display();
		
		//std::cout << "Framerate: " << 1000 / clock.restart().asMilliseconds() << std::endl;
	}
}
