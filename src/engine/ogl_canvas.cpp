#include <mage/engine/render_canvas.hpp>

Mage::RenderingCanvas::RenderingCanvas(std::unique_ptr<Mage::RenderingContext> context) :
m_context(std::move(context))
{
	m_sh_controller.loadShadersFromDir("data/shaders");
}

void Mage::RenderingCanvas::renderNextFrame(float delta) const
{
	const GLfloat color[] = { 0.0f, 0.3f, 0.7f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, color);

	m_context->swapBuffers();
}