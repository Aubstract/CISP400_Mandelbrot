// Assignment: Mandelbrot Set
// Names: Aubrey Fields, William Garcia-Cortes

#include "ComplexPlane.h"
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
	// Setting up the enum class state variable
	enum State { CALCULATING, DISPLAYING };
	// Initialize it to CALCULATING
	State state = State::CALCULATING;

	// Init values
	unsigned int width = VideoMode::getDesktopMode().width;
	unsigned int height = VideoMode::getDesktopMode().height;
	float aspectRatio = static_cast<float>(height) / width;
	
	// Variables that may be used later...maybe
	Vector2f mousePosition;
	Vector2f mouseClick;
	ComplexPlane plane(aspectRatio);

	VideoMode vm(width, height);
	RenderWindow window(vm, "Mandelbrot Set Plotter");

	Font font;
	if (!font.loadFromFile("./fonts/Comic_Sans_MS.ttf"))
	{
		cout << "Failed to find font..." << endl;
	}

	Text information;
	information.setFont(font);
	information.setCharacterSize(18);
	
	VertexArray pointColor;
	pointColor.setPrimitiveType(Points);
	pointColor.resize(width* height);

	// Main loop:
	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
					{
						window.close();
					}

			if (event.type == Event::MouseButtonPressed)
			{
				//Might have flubbed the inputs
				mouseClick = window.mapPixelToCoords(Mouse::getPosition(), plane.getView());

				if (Mouse::isButtonPressed(Mouse::Left))
				{
					plane.zoomIn();
					plane.setCenter(mouseClick);
				}
				if (Mouse::isButtonPressed(Mouse::Right))
				{
					plane.zoomOut();
					plane.setCenter(mouseClick);

				}
				state = State::CALCULATING;
			}
			if (event.type == Event::MouseMoved)
			{
				mousePosition = window.mapPixelToCoords(Mouse::getPosition(), plane.getView());
				plane.setMouseLocation(mousePosition);
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
		}

		
		/*
		****************************************
		Update the scene
		****************************************
		*/
		if (state == State::CALCULATING)
		{

		}


		/*
		****************************************
		Draw the scene
		****************************************
		*/



	} // End main loop

	return 0;
}