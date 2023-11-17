// IN THIS FILE WE'LL BE DECLARING METHODS DECLARED INSIDE THIS HEADER FILE
#include "node.hpp"
#include "scene_graph/components/mesh.hpp"
namespace W3D::sg
{
Node::Node(const size_t id, const std::string &name) :
    id_(id),
    name_(name),
    T_(*this)
{
	set_component(T_);
}

//Copy constructor
Node::Node(Node &t) :
    id_(t.id_ + 1),
    name_(t.name_),
    T_(*this),
    parent_(t.parent_),
    children_(t.children_),
    should_render(false)        // Copies do not render by default.
{
	set_component(T_);
	set_component(t.get_component<sg::Mesh>());
	T_.set_scale(glm::vec3(.175f, .175f, .175f));
}

void Node::add_child(Node &child)
{
	children_.push_back(&child);
}

void Node::set_parent(Node &parent)
{
	parent_ = &parent;
	T_.invalidate_local_M();
}

void Node::set_component(Component &component)
{
	auto it = components_.find(component.get_type());
	if (it != components_.end())
	{
		it->second = &component;
	}
	else
	{
		components_.insert(std::make_pair(component.get_type(), &component));
	}
}

const size_t Node::get_id() const
{
	return id_;
};

const std::string &Node::get_name() const
{
	return name_;
};

Node *Node::get_parent() const
{
	return parent_;
};

const std::vector<Node *> &Node::get_children() const
{
	return children_;
};

Component &Node::get_component(const std::type_index index)
{
	return *components_.at(index);
};

sg::Transform &Node::get_transform() const
{
	return dynamic_cast<sg::Transform &>(*components_.at(typeid(sg::Transform)));
}

bool Node::has_component(const std::type_index index)
{
	return components_.count(index) > 0;
}

void Node::set_render(bool val)
{
	should_render = val;
}
bool Node::get_render()
{
	return should_render;
}

void Node::set_name(std::string new_name)
{
	name_ = new_name;
}

}	// namespace W3D::sg