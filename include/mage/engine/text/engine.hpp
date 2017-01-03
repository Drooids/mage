#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <mage/noncopyable.hpp>

namespace Mage
{
	class TextEngine : Noncopyable
	{
	public:
		class Instance : Noncopyable
		{
		protected:
			FT_Library m_handle;

		public:
			Instance();
			~Instance();

			FT_Library& getHandle()
			{
				return m_handle;
			}
		};

	protected:
		Instance instance;

	public:
		TextEngine() = default;

		Instance& get_instance()
		{
			return instance;
		}
	};
}