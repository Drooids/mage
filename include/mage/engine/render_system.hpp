#pragma once

#include <mage/noncopyable.hpp>
#include <mage/engine/render_canvas.hpp>

namespace Mage
{
	class RenderSystem : Noncopyable
	{
	public:
		virtual ~RenderSystem() = default;

		virtual RenderingCanvas& createCanvas() = 0;
	};
}