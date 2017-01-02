#pragma once

#include <cstdint>
#include <map>
#include <memory>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include <GL/glew.h>

#include <mage/noncopyable.hpp>
#include <mage/engine/texture.hpp>
#include <mage/engine/text/engine.hpp>
#include <mage/math/vector2.hpp>

namespace Mage
{
	struct Glyph
	{
		uint32_t width;
		uint32_t height;
		int32_t left;
		int32_t top;
		float advanceX;
		float advanceY;
		unsigned char* data;
	};

	class GlyphMap : Texture
	{
	public:
		class GlyphMetrics
		{
		public:
			GlyphMetrics() :
			a(0,0), b(0,0), adv(0,0), left(0), top(0)
			{
				// do nothing
			}

			int32_t left;
			int32_t top;

			Math::Vector2f a;
			Math::Vector2f b;
			Math::Vector2f adv;
		};

	protected:
		GLuint m_handle;
		uint32_t m_width;
		uint32_t m_height;
		std::map<char32_t, GlyphMetrics> m_glyphs;

		uint32_t m_cur;
		uint32_t m_row;
		uint32_t m_size;

	public:
		GlyphMap(uint32_t size = 14, uint32_t width = 512, uint32_t height = 512);
		~GlyphMap();

		void insertGlyph(char32_t ch, Glyph& g);

		void bind() const override;
	};

	class Font : Noncopyable
	{
		// Warms up the font by loading ASCII characters into the glyph map of
		// the current font size.
		void loadAsciiCharacters();
		void loadGlyph(char32_t ch);

	protected:
		FT_Face m_face;
		FT_Glyph m_glyph;
		std::map<uint32_t, std::unique_ptr<GlyphMap>> m_maps;
		uint32_t m_size;

	public:
		Font(TextEngine::Instance& instance, const std::string& path);
		~Font();

		void setSize(uint32_t size);
	};
}