#include <mage/engine/text/engine.hpp>
#include <mage/exception.hpp>

Mage::TextEngine::Instance::Instance()
{
	auto error = FT_Init_FreeType(&m_handle);
	if (error)
	{
		throw Exception("Could not initialize FreeType");
	}
}

Mage::TextEngine::Instance::~Instance()
{
	FT_Done_FreeType(m_handle);
}

