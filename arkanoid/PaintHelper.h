#ifndef ARKANOID_PAINT_HELPER_H
#define ARKANOID_PAINT_HELPER_H

#include <string>
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>

namespace arkanoid
{
	class PaintHelper
	{
		private:
		GLuint m_font;
		GLUquadric* m_quadric;

		public:
		PaintHelper(const HDC& p_deviceContext);
		virtual ~PaintHelper();

		inline GLUquadric* getQuadric() const;

		void drawText(const std::string& p_text) const;
	};
}

namespace arkanoid
{
	GLUquadric* PaintHelper::getQuadric() const
	{
		return m_quadric;
	}
}

#endif
