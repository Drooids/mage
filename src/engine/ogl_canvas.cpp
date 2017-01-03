#include <mage/engine/render_canvas.hpp>
#include <mage/engine/exception.hpp>

Mage::RenderingCanvas::RenderingCanvas(std::unique_ptr<Mage::RenderingContext> context) :
m_context(std::move(context)),
m_quad_buf(sizeof(float) * 4 * 6),
m_ui_layer("UIParent", *this),
m_width(m_context->get_client_width()),
m_height(m_context->get_client_height())
{
	std::vector<float> quad_vertex = {
		-1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f,

		 1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 1.0f,
	};

	m_sh_controller.load_shaders_from_dir("data/shaders");
	m_quad_buf.data(quad_vertex.begin(), quad_vertex.end());

	glDisable(GL_CULL_FACE);
}

void Mage::RenderingCanvas::render_next_frame(float delta)
{
	// Get client size and update the viewport.
	auto h = m_context->get_client_height();
	auto w = m_context->get_client_width();

	if (h != m_height || w != m_width)
	{
		glViewport(0, 0, w, h);
		m_height = h;
		m_width = w;
	}

	const GLfloat color[] = { 0.0f, 0.3f, 0.7f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, color);

	// Draw the UI last.
	m_ui_layer.draw();
	m_context->swap_buffers();

	auto err = glGetError();
	if (err)
	{
		throw OGLException("OGL Error", err);
	}
}