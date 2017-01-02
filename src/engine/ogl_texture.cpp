#include <mage/engine/texture.hpp>

Mage::Texture2D::Texture2D(uint32_t width, uint32_t height) :
m_width(width), m_height(height), m_handle(0)
{
	glCreateTextures(GL_TEXTURE_2D, 1, &m_handle);
	glTextureStorage2D(m_handle, 1, GL_R8, m_width, m_height);
}

Mage::Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_handle);
}

void Mage::Texture2D::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_handle);
}
