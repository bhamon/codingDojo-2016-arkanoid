#ifndef ARKANOID_RENDERER_H
#define ARKANOID_RENDERER_H

#include <string>
#include <gl/GL.h>

class Renderer
{
	private:
	int m_width;
	int m_height;
	std::string m_title;
	GLuint m_listsFont;

	public:
	Renderer(int p_width, int p_height, const std::string& p_title);
	Renderer(const Renderer&) = delete;
	virtual ~Renderer();

	inline int getWidth() const;
	inline int getHeight() const;
	inline const std::string& getTitle() const;

	void init();
	void cleanup();
	void resize(int p_width, int p_height);
	void draw();

	void onKeyDown(unsigned int p_vk);
	void onKeyUp(unsigned int p_vk);

	private:
	void buildFont();
};

int
Renderer::getWidth() const
{
	return m_width;
}

int
Renderer::getHeight() const
{
	return m_height;
}

const std::string&
Renderer::getTitle() const
{
	return m_title;
}

#endif
