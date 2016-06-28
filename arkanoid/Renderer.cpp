#include "Renderer.h"

#include <Windows.h>
#include <gl/GL.h>

#include <iostream>

#define FONT_LISTS_NUMBER 96

Renderer::Renderer(int p_width, int p_height, const std::string& p_title)
	: m_width(p_width)
	, m_height(p_height)
	, m_title(p_title)
	, m_listsFont(0)
{
}

Renderer::~Renderer()
{
}

void
Renderer::init()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	buildFont();
}

void
Renderer::cleanup()
{
	if(m_listsFont)
	{
		glDeleteLists(m_listsFont, FONT_LISTS_NUMBER);
	}
}

void
Renderer::resize(int p_width, int p_height)
{
	glViewport(0, 0, p_width, p_height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, 0, p_width, p_height, -1, 1);

	glTranslatef(-1.0f, 1.0f, 0.0f);
	glScalef(1.0f / static_cast<float>(p_width), -1.0f / static_cast<float>(p_height), 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	m_width = p_width;
	m_height = p_height;
}

void
Renderer::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(100.0f, 100.0f, 0.0f);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	glVertex3f(100.0f, 100.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	glEnd();

	glPopMatrix();
}

void
Renderer::onKeyDown(unsigned int p_vk)
{
}

void
Renderer::onKeyUp(unsigned int p_vk)
{
}

void
Renderer::buildFont()
{
	HFONT font = CreateFont(
		-24,                           // Size (best match mode)
		0,                             // Width (default)
		0,                             // Angle of escapement
		0,                             // Orientation angle
		FW_BOLD,                       // Weight
		FALSE,                         // Italic
		FALSE,                         // Underline
		FALSE,                         // Strikeout
		ANSI_CHARSET,                  // Charset
		OUT_TT_PRECIS,                 // Conflict resolution strategy (truetype first)
		CLIP_DEFAULT_PRECIS,           // Clipping strategy,
		ANTIALIASED_QUALITY,           // Output quality
		FF_DONTCARE | DEFAULT_PITCH,   // Family and pitch
		"Courier New"                  // Name
	);

	m_listsFont = glGenLists(FONT_LISTS_NUMBER);

	// TODO
}