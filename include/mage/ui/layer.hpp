#pragma once

#include <memory>
#include <vector>

#include <mage/engine/graph.hpp>
#include <mage/ui/element.hpp>

namespace Mage
{
	namespace UI
	{
		class Layer : public Graph
		{
		protected:
			std::vector<std::unique_ptr<Element>> m_elements;

		public:
			Layer(const std::string& name, RenderingCanvas& canvas) :
			Graph(name, canvas)
			{
				// do nothing
			}

			void draw() override;

			template<typename T, typename... Args>
			T& createElement(const std::string& name, Args&&... args)
			{
				m_elements.emplace_back(std::make_unique<T>(std::forward(args)...));
				return m_elements.back();
			}
		};
	}
}