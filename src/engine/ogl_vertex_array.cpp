#include <mage/engine/vertex_array.hpp>

Mage::VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &m_handle);
}

Mage::VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_handle);
}

void Mage::VertexArray::bind() const
{
	glBindVertexArray(m_handle);
}
