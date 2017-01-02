#pragma once

#include <memory>
#include <vector>

#include <mage/noncopyable.hpp>
#include <mage/engine/graph.hpp>
#include <mage/engine/object.hpp>

namespace Mage
{
	class Node : Noncopyable
	{
	protected:
		std::vector<std::unique_ptr<Node>> m_children;
		RenderableObject* m_obj;

	public:

	};

	class SceneGraph : public Graph
	{
	protected:
		std::vector<std::unique_ptr<Node>> m_nodes;

	public:
		virtual ~SceneGraph() = default;

		virtual void draw() override
		{
			for (auto& obj : m_nodes)
			{
				//
			}
		}
	};
}