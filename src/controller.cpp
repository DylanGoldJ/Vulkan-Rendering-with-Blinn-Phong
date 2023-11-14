// IN THIS FILE WE'LL BE DECLARING METHODS DECLARED INSIDE THIS HEADER FILE
#include "controller.hpp"

// OUR OWN TYPES
#include "scene_graph/components/aabb.hpp"
#include "scene_graph/components/mesh.hpp"
#include "scene_graph/event.hpp"
#include "scene_graph/node.hpp"
#include "scene_graph/script.hpp"
#include "scene_graph/scripts/light.hpp"

namespace W3D
{
// Class that is responsible for dispatching events and answering collision queries

Controller::Controller(sg::Node &camera_node, sg::Node &player_1_node, sg::Node &player_2_node, 
	sg::Light &light_1_obj, sg::Light &light_2_obj, sg::Light &light_3_obj, sg::Light &light_4_obj) :
    camera_(camera_node),
    player_1(player_1_node),
    player_2(player_2_node),
	//Added light objects.
    light_1(light_1_obj),
    light_2(light_2_obj),
    light_3(light_3_obj),
    light_4(light_4_obj)
{

}

void Controller::process_event(const Event &event)
{
	// IF IT'S A KEY PRESS WE NEED TO CHECK TO SEE IF WE SHOULD SWITCH MODES
	if (event.type == EventType::eKeyInput)
	{
		const auto &key_input_event = static_cast<const KeyInputEvent &>(event);
		// NUMBER KEYS ARE ALL GREATER
		if (key_input_event.code > KeyCode::eR)
		{
			switch_mode(key_input_event.code);
			return;
		}
	}

	// DELIVER IT TO THE SCRIPT
	deliver_event(event);
}

void Controller::switch_mode(KeyCode code)
{
	// THE 1 KEY SWITCHES CONTROL TO THE PLAYER 1 CUBE
	if (code == KeyCode::e1)
	{
		mode_ = ControllerMode::ePlayer1;
	}
	// THE 2 KEY SWITCHES CONTROL TO THE PLAYER 2 CUBE
	else if (code == KeyCode::e2)
	{
		mode_ = ControllerMode::ePlayer2;
	}
	else if (code == KeyCode::e4)
	{
		mode_ = ControllerMode::eLight1;
	}
	else if (code == KeyCode::e5)
	{
		mode_ = ControllerMode::eLight2;
	}
	else if (code == KeyCode::e6)
	{
		mode_ = ControllerMode::eLight3;
	}
	else if (code == KeyCode::e7)
	{
		mode_ = ControllerMode::eLight4;
	}
	// THE DEFAULT IS TO SWITCH CONTROL TO THE CAMERA
	else
	{
		mode_ = ControllerMode::eCamera;
	}
}

void Controller::deliver_event(const Event &event)
{
	// NOTIFY THE ASSOCIATED SCRIPT FOR THE GAME OBJECT SO IT CAN PROVIDE
	// A FURTHER REPONSE. FIRST GET THE ASSOCIATED SCRIPT
	sg::Script *p_script;
	if (mode_ == ControllerMode::ePlayer1)
	{
		p_script = &player_1.get_component<sg::Script>();
	}
	else if (mode_ == ControllerMode::ePlayer2)
	{
		p_script = &player_2.get_component<sg::Script>();
	}
	else if (mode_ == ControllerMode::eLight1)
	{
		light_1.process_event(event);
		return;
	}
	else if (mode_ == ControllerMode::eLight2)
	{
		light_2.process_event(event);
		return;
	}
	else if (mode_ == ControllerMode::eLight3)
	{
		light_3.process_event(event);
		return;
	}
	else if (mode_ == ControllerMode::eLight4)
	{
		light_4.process_event(event);
		return;
	}
	else
	{
		p_script = &camera_.get_component<sg::Script>();
	}

	// AND NOW ASK THE SCRIPT TO PROVIDE A PROGRAMMED RESPONSE
	p_script->process_event(event);
}

bool Controller::are_players_colliding()
{
	glm::mat4 p1_M              = player_1.get_transform().get_world_M();
	glm::mat4 p2_M              = player_2.get_transform().get_world_M();
	sg::AABB  p1_transformed_bd = player_1.get_component<sg::Mesh>().get_bounds().transform(p1_M);
	sg::AABB  p2_transformed_bd = player_2.get_component<sg::Mesh>().get_bounds().transform(p2_M);

	// NOTE THIS AABB FUNCTION DOES THE ACTUAL COLLISION TEST
	return p1_transformed_bd.collides_with(p2_transformed_bd);
}

}        // namespace W3D