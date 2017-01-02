#pragma once

#include <algorithm>
#include <type_traits>

#include <GL/glew.h>

#include <mage/noncopyable.hpp>

namespace Mage
{
	class Buffer : Noncopyable
	{
	protected:
		GLuint m_handle;
		size_t m_size;

	public:
		Buffer(size_t size) : m_size(size)
		{
			glCreateBuffers(1, &m_handle);
			glNamedBufferStorage(m_handle, m_size, nullptr, GL_MAP_WRITE_BIT);
		}

		~Buffer()
		{
			glDeleteBuffers(1, &m_handle);
		}

		size_t size() const noexcept
		{
			return m_size;
		}

		template<typename Iterator>
		void data(Iterator first, Iterator last);

		template<typename Iterator>
		void data(size_t offset, Iterator first, Iterator last);	
	};

	template <typename Iterator>
	void Buffer::data(Iterator first, Iterator last)
	{
		if (first == last) return;

		auto* ptr = glMapNamedBuffer(m_handle, GL_WRITE_ONLY);
		typename Iterator::value_type* cptr = reinterpret_cast<typename Iterator::value_type*>(ptr);

		std::copy(first, last, cptr);
		glUnmapNamedBuffer(m_handle);
	}

	template <typename Iterator>
	void Buffer::data(size_t offset, Iterator first, Iterator last)
	{
		if (first == last) return;

		void* ptr = glMapNamedBufferRange(
			m_handle, 
			offset, std::distance(first, last) * sizeof(Iterator::value_type), 
			GL_WRITE_ONLY);

		typename Iterator::value_type* cptr = reinterpret_cast<typename Iterator::value_type*>(ptr);
		std::copy(first, last, cptr);
		glUnmapNamedBuffer(m_handle);
	}
}
