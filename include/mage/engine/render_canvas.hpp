#pragma once

#include <memory>

#include <mage/noncopyable.hpp>
#include <mage/engine/shader.hpp>

namespace Mage
{
	/**
	 * RenderingContext abstracts an interface that can be drawn to, in most
	 * cases this is a window or screen that the user can see. The
	 * RenderingContext is the glue that sits between Mage and the OS's
	 * OpenGL layer. For example, WGL in Windows.
	 *
	 * \brief Abstract of a context that can be rendered to, ie: a window.
	 */
	class RenderingContext : Noncopyable
	{
	public:
		virtual ~RenderingContext() = default;

		virtual void swapBuffers() = 0;
	};

	/**
	 * RenderingCanvas is quite literally the canvas upon which draw calls are
	 * made. RenderingCanvas is responsible for creating an image that can be
	 * shown to the user. It is quite literally the beating heart of the Mage
	 * engine.
	 *
	 * \brief RenderingCanvas manages the drawing state and render calls.
	 */
	class RenderingCanvas final : Noncopyable
	{
	protected:
		std::unique_ptr<RenderingContext> m_context;
		Mage::ShaderController m_sh_controller;

	public:
		RenderingCanvas(std::unique_ptr<RenderingContext> context);
		~RenderingCanvas() = default;

		void renderNextFrame(float delta) const;
		
		RenderingContext& getContext() const
		{
			return *m_context;
		}

		ShaderController& getShaderController()
		{
			return m_sh_controller;
		}
	};
}