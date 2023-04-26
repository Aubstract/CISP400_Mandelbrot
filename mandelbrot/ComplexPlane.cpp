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


void ComplexPlane::zoomOut()
{
	m_zoomCount--;

	float x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);

	m_view.setSize(x, y);
}


void ComplexPlane::setCenter(Vector2f coord)
{
	m_view.setCenter(coord);
}


View ComplexPlane::getView()
{
	return m_view;
}


void ComplexPlane::setMouseLocation(Vector2f coord)
{
	m_mouseLocation = coord;
}


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
	int step = MAX_ITER / 5;
	//Im going to start off in gray scale first
	if (count == MAX_ITER)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	else if (count >= 0 && count < step)
	{
		r = 90 + (MAX_ITER % (count + 1));
		g = 10;
		b = 90 + (MAX_ITER % (count + 1));
	}
	else if (count >= step && count < step * 2)
	{
		r = 10;
		g = 90 + (MAX_ITER % count);
		b = 90 + (MAX_ITER % count);
	}
	else if (count >= step * 2 && count < step * 3)
	{
		r = 1;
		g = 90 + (MAX_ITER % count);
		b = 1;
	}
	else if (count >= step * 3 && count < step * 4)
	{
		r = 90 + (MAX_ITER % count);
		g = 90 + (MAX_ITER % count);
		b = 10;
	}
	else if (count >= step * 4)
	{
		r = 90 + (MAX_ITER % count);
		g = 10;
		b = 10;
	}
}
