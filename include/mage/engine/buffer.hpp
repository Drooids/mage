#pragma once

#include <algorithm>
#include <type_traits>

#include <GL/glew.h>

#include <mage/exception.hpp>
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

		GLuint get_handle()
		{
			return m_handle;
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

		size_t dist = std::distance(first, last);
		if (dist > m_size)
			throw Exception("out of bounds");

		auto* ptr = reinterpret_cast<typename Iterator::value_type*>(
			glMapNamedBuffer(m_handle, GL_WRITE_ONLY));

		std::copy(first, last, ptr);
		glUnmapNamedBuffer(m_handle);
	}

	template <typename Iterator>
	void Buffer::data(size_t offset, Iterator first, Iterator last)
	{
		if (first == last) return;
		
		size_t dist = std::distance(first, last);
		if (dist > m_size - offset)
			throw Exception("out of bounds");

		auto* ptr = reinterpret_cast<typename Iterator::value_type*>(
			glMapNamedBufferRange(
				m_handle, 
				offset, dist * sizeof(Iterator::value_type), 
				GL_WRITE_ONLY));

		std::copy(first, last, ptr);
		glUnmapNamedBuffer(m_handle);
	}
}
