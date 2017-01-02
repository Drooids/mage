#pragma once

#include <mage/engine/object.hpp>
#include <mage/math/matrix.hpp>

namespace Mage
{
	namespace UI
	{
		class Frame : public RenderableObject
		{
			Math::Matrix<float, 2, 2> m_scale;
			Math::Matrix<float, 2, 2> m_position;

		public:
			void draw() const override;
		};
	}
}