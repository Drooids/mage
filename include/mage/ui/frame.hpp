#pragma once

#include <string>

#include <mage/engine/shader.hpp>
#include <mage/ui/layer.hpp>
#include <mage/ui/element.hpp>
#include <math/matrix.hpp>

namespace Mage
{
	namespace UI
	{
		class Frame : public Element
		{
		protected:
			Math::Matrix<float, 4, 4> m_model;
			Math::Matrix<float, 4, 4> m_view;
			Math::Matrix<float, 4, 4> m_projection;
			Program& m_prog;

		public:
			Frame(const std::string& name, Layer& layer);

			void draw() override;
		};
	}
}