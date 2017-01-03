#include <mage/ui/layer.hpp>

void Mage::UI::Layer::draw()
{
	for (auto& elem : m_elements)
	{
		elem->draw();
	}
}