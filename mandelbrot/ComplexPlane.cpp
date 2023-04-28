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
	float y = -BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);

	m_view.setSize(x, y);
}


void ComplexPlane::zoomOut()
{
	m_zoomCount--;

	float x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float y = -BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);

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
	ss << noskipws << "Mandelbrot Set" << '\n'
		<< "Center: " << "(" << m_view.getCenter().x <<"," << m_view.getCenter().y << ")" << '\n'
		<< "Cursor: " << "(" << m_mouseLocation.x << "," << m_mouseLocation.y << ")" << '\n'
		<< "Left-click to Zoom in" << '\n'
		<< "Right-click to Zoom out";
	
	text.setString(ss.str());
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
	// SCALE_FACTOR is used to map values from [0, MAX_ITER] to [0, UINT8_MAX]
	const unsigned int SCALE_FACTOR = MAX_ITER / UINT8_MAX;

	if (!count) { count++; }

	r = (MAX_ITER - count) * SCALE_FACTOR;
	g = ((MAX_ITER / 2) - count) * SCALE_FACTOR;
	b = count * SCALE_FACTOR;

	if (count == MAX_ITER) { r = 0, g = 0, b = 0; }
}
