#include <mage/engine/text/font.hpp>
#include <mage/engine/text/exception.hpp>

Mage::GlyphMap::GlyphMap(uint32_t size, uint32_t width, uint32_t height) :
m_width(width), m_height(height), m_cur(0), m_row(0), m_size(size)
{
	glCreateTextures(GL_TEXTURE_2D, 1, &m_handle);
	glTextureStorage2D(m_handle, 1, GL_R8, m_width, m_height);
}

Mage::GlyphMap::~GlyphMap()
{
	glDeleteTextures(1, &m_handle);
}

void Mage::GlyphMap::insert_glyph(char32_t ch, Glyph& g)
{
	if (m_glyphs.find(ch) != m_glyphs.end())
	{
		return;
	}

	// If this glyph is an asinine size for some reason, discard it.
	if (g.width > m_width || g.height > m_height)
	{
		throw Exception("Glyph is larger than texture");
	}

	// Is there room for this glyph?
	if (m_cur + g.width > m_width)
	{
		// If the next row is too small, that's a problem.
		if ((m_row+1) * m_size > m_height)
		{
			throw Exception("Out of texture space");
		}

		m_row++;
		m_cur = 0;
	}
	
	// Write font data.
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTextureSubImage2D(
		m_handle, 0,
		m_cur, m_row * m_size, // (x, y)
		g.width, g.height,
		GL_RED, GL_UNSIGNED_BYTE,
		g.data
	);

	// Reset back to defaults.
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	// Calculate and insert font metrics.
	GlyphMetrics met;

	met.left = g.left;
	met.top = g.top;
	met.a.x = (float)m_cur * (1 / (float)m_width);
	met.b.x = ((float)m_cur + (float)g.width) * (1 / (float)m_width);
	met.a.y = (float)m_row * (float)m_size * (1 / (float)m_height);
	met.b.y = ((float)m_row * (float)m_size + (float)g.height) * (1 / (float)m_height);
	met.adv.x = g.advanceX;
	met.adv.y = g.advanceY;

	m_glyphs[ch] = met;

	// Advance the cursor past this glyph.
	m_cur += g.width;
}

void Mage::GlyphMap::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_handle);
}

Mage::Font::Font(TextEngine::Instance& instance, const std::string& path) :
m_glyph(nullptr), m_size(14)
{
	auto error = FT_New_Face(
		instance.getHandle(),
		path.c_str(),
		0,
		&m_face
	);

	if (error)
	{
		throw TextException("could not load font face", error);
	}
}

Mage::Font::~Font()
{
	FT_Done_Face(m_face);
}

void Mage::Font::set_size(uint32_t size)
{
	m_size = size;
	FT_Set_Pixel_Sizes(m_face, 0, m_size);

	if (m_maps.find(size) == m_maps.end())
	{
		m_maps[size] = std::make_unique<GlyphMap>(size);

		load_ascii_characters();
	}
}

void Mage::Font::load_ascii_characters()
{
	for (char32_t ch = 32; ch < 127; ++ch)
	{
		load_glyph(ch);
	}
}

void Mage::Font::load_glyph(char32_t ch)
{
	auto index = FT_Get_Char_Index(m_face, ch);
	
	auto error = FT_Load_Glyph(m_face, index, FT_LOAD_DEFAULT);
	if (error)
	{
		throw TextException("Could not load glyph", error);
	}

	error = FT_Get_Glyph(m_face->glyph, &m_glyph);
	if (error)
	{
		throw TextException("Could not get glyph", error);
	}

	error = FT_Glyph_To_Bitmap(&m_glyph, FT_RENDER_MODE_NORMAL, nullptr, true);
	if (error)
	{
		throw TextException("Could not convert glyph to bitmap", error);
	}

	auto bitmap = reinterpret_cast<FT_BitmapGlyph>(m_glyph);

	Glyph g;
	g.data = bitmap->bitmap.buffer;
	g.width = bitmap->bitmap.width;
	g.height = bitmap->bitmap.rows;
	g.left = bitmap->left;
	g.top = bitmap->top;
	g.advanceX = static_cast<float>(m_face->glyph->advance.x >> 6);
	g.advanceY = static_cast<float>(m_face->glyph->advance.y >> 6);

	m_maps[m_size]->insert_glyph(ch, g);
	FT_Done_Glyph(m_glyph);
}
