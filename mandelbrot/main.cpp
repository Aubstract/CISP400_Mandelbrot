// Assignment: Mandelbrot Set
// Names: Aubrey Fields, William Garcia-Cortes


#include "ComplexPlane.h"
#include <SFML/System.hpp>
#include <thread>
#include <vector>


using namespace sf;
using namespace std;


void processRow(unsigned int width, int i,  VertexArray& vArray, RenderWindow& window, ComplexPlane& plane)
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


int main()
{
	// Get the number of threads the CPU has
	static unsigned int PROCESSOR_COUNT = std::thread::hardware_concurrency();
	// Create vect of half as many threads
	vector<sf::Thread> threads(PROCESSOR_COUNT / 2);

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
			for (int i = 0; i < (height - 4); i+=4)
			{
				// Dispatch SFML threads
				threads.at(0) = sf::Thread(&processRow, width, i, vArray, window, plane);
				thread th2(processRow, width, (i+1), vArray, window, plane);
				thread th3(processRow, width, (i+2), vArray, window, plane);
				thread th4(processRow, width, (i+3), vArray, window, plane);
				
				// Wait for threads to finish
				th1.join();
				th2.join();
				th3.join();
				th4.join();
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
