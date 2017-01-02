#pragma once

#include <string>

#include <mage/noncopyable.hpp>
#include <mage/engine/render_canvas.hpp>

namespace Mage
{
	class Graph : Noncopyable
	{
	protected:
		std::string m_name;
		RenderingCanvas& m_canvas;

	public:
		Graph(const std::string& name, RenderingCanvas& canvas) :
		m_name(name), m_canvas(canvas)
		{
			// do nothing
		}

		virtual ~Graph() = default;
		virtual void draw() = 0;

		const std::string& get_name() const noexcept
		{
			return m_name;
		}
		const RenderingCanvas& get_canvas() const noexcept
		{
			return m_canvas;
		}
	};
}