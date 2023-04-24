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


// setCenter()


// getView()


// setMouseLocation()


// loadText()


size_t ComplexPlane::countIterations(Vector2f coord)
{
	complex<double> c = sqrt(pow(coord.x, 2) + pow(coord.y, 2));
	complex<double> z = 0.0;

	size_t iterations = 0;

	for (; iterations < MAX_ITER; iterations++)
	{
		z = pow(z, 2) + c;

		// break condition
		if (abs(z) > 2.0)
		{
			break;
		}
	}

	return iterations;
}


// iterationsTORGB()