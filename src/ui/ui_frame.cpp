#include <mage/ui/frame.hpp>
#include <mage/engine/render_canvas.hpp>
#include <mage/engine/exception.hpp>

#include <math/transform.hpp>

Mage::UI::Frame::Frame(const std::string& name, Layer& layer) :
Element(name, layer), 
m_prog(m_layer.get_canvas().get_shader_controller().get_program("frame"))
{
	glVertexArrayAttribBinding(m_vao.get_handle(), 0, 0);
	glVertexArrayAttribFormat(m_vao.get_handle(), 0, 4, GL_FLOAT, GL_FALSE, 0);
	glEnableVertexArrayAttrib(m_vao.get_handle(), 0);

	glVertexArrayVertexBuffer(
		m_vao.get_handle(),
		0,
		m_layer.get_canvas().get_basic_quad().get_handle(),
		0, 4 * sizeof(GLfloat));
}

void Mage::UI::Frame::draw()
{
	auto w = m_layer.get_canvas().get_viewport_width();
	auto h = m_layer.get_canvas().get_viewport_height();

	m_projection = Math::ortho<float>(
		-static_cast<float>(w) / static_cast<float>(h), 
		 static_cast<float>(w) / static_cast<float>(h),
		-1.0f, 1.0f,
		-1.0f, 1.0f);

	// Bind our program and VAO.
	m_vao.bind();
	
	m_prog.use();
	glUniformMatrix4fv(1, 1, GL_FALSE, m_projection.unsafe_ptr());

	glDrawArrays(GL_TRIANGLES, 0, 6);
}