#pragma once

#include <string>
#include <vector>

#include <mage/engine/object.hpp>

namespace Mage
{
	namespace UI
	{
		class Layer;

		class Element : public RenderableObject
		{
		protected:
			std::vector<std::unique_ptr<Element>> m_elements;
			std::string m_name;
			Layer& m_layer;

		public:
			Element(const std::string& name, Layer& layer) :
			m_name(name), m_layer(layer)
			{
				// do nothing ..
			}

			void draw() const override
			{
				for (auto& e : m_elements)
					e->draw();
			}

			std::string get_name() const noexcept
			{
				return m_name;
			}
			Layer& get_layer() const noexcept
			{
				return m_layer;
			}
		};
	}
}