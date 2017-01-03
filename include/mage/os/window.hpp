#pragma once

#include <string>

#include <mage/noncopyable.hpp>

namespace Mage {
	namespace OS {
		class Window : Noncopyable {
		protected:
			std::string m_title;
			int m_width;
			int m_height;
			bool m_visible;

		public:
			Window() : m_title("Mage Window"), m_width(1280), m_height(720), m_visible(false) { }
			virtual ~Window() = default;

			virtual void set_title(const std::string& title) = 0;

			virtual const std::string& get_title()
			{
				return m_title;
			}
			int get_width() const
			{
				return m_width;
			}
			int get_height() const
			{
				return m_height;
			}
			bool is_visible() const
			{
				return m_visible;
			}
		};
	}
}