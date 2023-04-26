#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
	m_view.setSize(BASE_WIDTH, -BASE_HEIGHT * m_aspectRatio);
	m_view.setCenter(0.0, 0.0);
	m_zoomCount = 0;
}


void ComplexPlane::zoomIn()
{
	m_zoomCount++;

	float x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);

	m_view.setSize(x, y);
}


// zoomOut()
void ComplexPlane::zoomOut()
{
	m_zoomCount--;

	float x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);

	m_view.setSize(x, y);
}

// setCenter()
void ComplexPlane::setCenter(Vector2f coord)
{
	m_view.setCenter(coord);
}

// getView()
View ComplexPlane::getView()
{
	return m_view;
}

// setMouseLocation()
void ComplexPlane::setMouseLocation(Vector2f coord)
{
	m_mouseLocation = coord;
}

// loadText()
void ComplexPlane::loadText(Text& text)
{
	stringstream ss;
	ss << "Mandelbrot Set" << endl
		<< "Center: " << "(" << m_view.getCenter().x <<"," << m_view.getCenter().y << ")" << endl
		<< "Cursor: " << "(" << m_mouseLocation.x << "," << m_mouseLocation.y << ")" << endl
		<< "Left-click to Zoom in" << endl
		<< "Right-click to Zoom out";
	string convert;
	while (ss >> convert);

	text.setString(convert);

}

size_t ComplexPlane::countIterations(Vector2f coord)
{
	complex<double> c (coord.x, coord.y);
	complex<double> z = 0.0;

	size_t iterations = 0;

	for (; iterations < MAX_ITER; iterations++)
	{
		z = pow(z, 2) + c;

		if (abs(z) > 2.0)
		{
			break;
		}
	}

	return iterations;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
}


// iterationsTORGB()
//I don't get it sorry
void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	//Count is the amount of iterations

	//Im going to start off in gray scale first
	if (count == MAX_ITER)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	else if (count >= 0 && count < MAX_ITER)
	{
		if (count >= 0 && count < 12)
		{
			r = 90;
			g = 90;
			b = 90;
		}
		else if (count >= 12 && count < 24)
		{
			r = 70;
			g = 70;
			b = 70;
		}
		else if (count >= 24 && count < 36)
		{
			r = 50;
			g = 50;
			b = 50;
		}
		else if (count >= 36 && count < 48)
		{
			r = 30;
			g = 30;
			b = 30;
		}
		else if (count >= 48)
		{
			r = 10;
			g = 10;
			b = 10;
		}
	}
}