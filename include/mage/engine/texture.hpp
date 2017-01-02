#pragma once

#include <cstdint>

#include <GL/glew.h>

#include <mage/noncopyable.hpp>

namespace Mage
{
	class Texture : Noncopyable
	{
	public:
		virtual ~Texture() = default;

		virtual void bind() const = 0;
	};

	class Texture2D : public Texture
	{
	protected:
		GLuint m_handle;
		uint32_t m_width;
		uint32_t m_height;

	public:
		Texture2D(uint32_t width, uint32_t height);
		~Texture2D();

		void bind() const override;
		GLuint getHandle() const
		{
			return m_handle;
		}
	};
}