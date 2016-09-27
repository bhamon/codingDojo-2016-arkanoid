#include "PaintHelper.h"

namespace arkanoid
{
	PaintHelper::PaintHelper(const HDC& p_deviceContext)
		: m_font(0)
		, m_quadric(0)
	{
		m_font = glGenLists(96);
		HFONT font = CreateFont(
			-24,								// Height (based on CHARACTER, not CELL)
			0,									// Cell width
			0,									// Angle of escapment
			0,									// Orientation angle
			FW_BOLD,							// Weight
			0,									// Italic
			0,									// Underline
			0,									// Strikeout
			ANSI_CHARSET,						// Charset
			OUT_TT_PRECIS,						// Output precision: select TTF by default
			CLIP_DEFAULT_PRECIS,				// Clipping precision
			ANTIALIASED_QUALITY,				// Output quality: antialiased
			FF_DONTCARE | DEFAULT_PITCH,		// Family and pitch
			"Bauhaus 93"						// Name
			);

		HFONT oldfont = static_cast<HFONT>(SelectObject(p_deviceContext, font));
		wglUseFontBitmaps(p_deviceContext, 32, 96, m_font);
		SelectObject(p_deviceContext, oldfont);
		DeleteObject(font);

		m_quadric = gluNewQuadric();
	}

	PaintHelper::~PaintHelper()
	{
		gluDeleteQuadric(m_quadric);
		glDeleteLists(m_font, 96);
	}

	void PaintHelper::drawText(const std::string& p_text) const
	{
		glPushAttrib(GL_LIST_BIT);
		glListBase(m_font - 32);
		glCallLists(p_text.length(), GL_UNSIGNED_BYTE, p_text.c_str());
		glPopAttrib();
	}
}
