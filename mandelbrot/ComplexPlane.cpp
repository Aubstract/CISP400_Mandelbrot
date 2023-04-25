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


// iterationsTORGB()
//I don't get it sorry
void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{

}