#pragma once

#include <memory>

#include <mage/noncopyable.hpp>
#include <mage/engine/shader.hpp>
#include <mage/engine/buffer.hpp>
#include <mage/ui/layer.hpp>

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

		virtual void swap_buffers() = 0;
		virtual uint64_t get_client_width() = 0;
		virtual uint64_t get_client_height() = 0;
	};

	/**
	 * RenderingCanvas is quite literally the canvas upon which draw calls are
	 * made. RenderingCanvas is responsible for creating an image that can be
	 * shown to the user. It is quite literally the beating heart of the Mage
	 * engine.
	 *
	 * \brief RenderingCanvas manages the drawing state and render calls.
	 */
	class RenderingCanvas : Noncopyable
	{
	protected:
		std::unique_ptr<RenderingContext> m_context;
		Mage::ShaderController m_sh_controller;
		Buffer m_quad_buf;
		Mage::UI::Layer m_ui_layer;

		uint64_t m_height;
		uint64_t m_width;

	public:
		RenderingCanvas(std::unique_ptr<RenderingContext> context);
		~RenderingCanvas() = default;

		void render_next_frame(float delta);
		
		RenderingContext& get_context() const
		{
			return *m_context;
		}

		ShaderController& get_shader_controller()
		{
			return m_sh_controller;
		}

		UI::Layer& get_ui_layer()
		{
			return m_ui_layer;
		}

		uint64_t get_viewport_height() const
		{
			return m_height;
		}

		uint64_t get_viewport_width() const
		{
			return m_width;
		}

		Buffer& get_basic_quad()
		{
			return m_quad_buf;
		}
	};
}