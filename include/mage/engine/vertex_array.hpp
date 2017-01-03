#pragma once

#include <GL/glew.h>

#include <mage/noncopyable.hpp>

namespace Mage
{
	class VertexArray : Noncopyable
	{
	protected:
		GLuint m_handle;


	public:
		VertexArray();
		~VertexArray();

		void bind() const;

		GLuint get_handle() const noexcept
		{
			return m_handle;
		}
	};
}