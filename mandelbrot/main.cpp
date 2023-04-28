// Assignment: Mandelbrot Set
// Names: Aubrey Fields, William Garcia-Cortes

#include "ComplexPlane.h"
#include <thread>

using namespace sf;
using namespace std;

int main()
{
	// Get the number of threads the CPU has
	const unsigned int PROCESSOR_COUNT = std::thread::hardware_concurrency();

	// Setting up the enum class state variable
	enum State { CALCULATING, DISPLAYING };
	// Initialize it to CALCULATING
	State state = State::CALCULATING;

	// Init values
	unsigned int width = VideoMode::getDesktopMode().width;
	unsigned int height = VideoMode::getDesktopMode().height;
	float aspectRatio = static_cast<float>(height) / width;
	
	Vector2f mousePosition;
	Vector2f mouseClick;
	ComplexPlane plane(aspectRatio);


	VideoMode vm(width, height);
	RenderWindow window(vm, "Mandelbrot Set Plotter");

	Font font;
	if (!font.loadFromFile("./fonts/Comic_Sans_MS.ttf") && !font.loadFromFile("mandelbrot/fonts/Comic_Sans_MS.ttf"))
	{
		cout << "Failed to find font..." << endl;
	}

	Text information;
	information.setFont(font);
	information.setCharacterSize(18); 
	
	VertexArray vArray;
	vArray.setPrimitiveType(Points);
	vArray.resize(size_t(width) * height);

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
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					vArray[j + i * width].position = { (float)j, (float)i };
					Vector2i point(j, i);
					Vector2f pixel = window.mapPixelToCoords(point, plane.getView());
					size_t iterations = plane.countIterations(pixel);
					Uint8 r;
					Uint8 g;
					Uint8 b;

					plane.iterationsToRGB(iterations, r, g, b);

					vArray[j + i * width].color = { r,g,b };
				}
			}
			state = State::DISPLAYING;
			
		}
		plane.loadText(information);


		/*
		****************************************
		Draw the scene
		****************************************
		*/
		if (state == State::DISPLAYING)
		{
			window.clear();
			window.draw(vArray);
			window.draw(information);

			window.display();
		}


	} // End main loop

	return 0;
}