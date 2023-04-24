// Assignment: Mandelbrot Set
// Names: Aubrey Fields, William Garcia-Cortes

#include "ComplexPlane.h"
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
	// Init values
	unsigned int width = VideoMode::getDesktopMode().width;
	unsigned int height = VideoMode::getDesktopMode().height;
	float aspectRatio = static_cast<float>(height) / width;

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

	// Main loop:
	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/



		/*
		****************************************
		Update the scene
		****************************************
		*/



		/*
		****************************************
		Draw the scene
		****************************************
		*/



	} // End main loop

	return 0;
}