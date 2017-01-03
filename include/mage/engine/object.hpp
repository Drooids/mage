#pragma once

#include <mage/noncopyable.hpp>
#include <mage/engine/vertex_array.hpp>

namespace Mage
{
	class RenderableObject : Noncopyable
	{
	protected:
		VertexArray m_vao;

	public:
		virtual ~RenderableObject() = default;

		virtual void draw() = 0;
	};
}