// IN THIS FILE WE'LL BE DECLARING METHODS DECLARED INSIDE THIS HEADER FILE
#include "controller.hpp"

// OUR OWN TYPES
#include "scene_graph/components/aabb.hpp"
#include "scene_graph/components/mesh.hpp"
#include "scene_graph/event.hpp"
#include "scene_graph/node.hpp"
#include "scene_graph/script.hpp"
#include "scene_graph/scripts/light.hpp"
#include "scene_graph/scripts/projectile.hpp"

namespace W3D
{
// Class that is responsible for dispatching events and answering collision queries

Controller::Controller(sg::Node &camera_node, sg::Node &player_1_node, sg::Node &player_2_node, sg::Node &player_3_node, sg::Node &player_4_node, sg::Node &player_5_node,
	sg::Light &light_1_obj, sg::Light &light_2_obj, sg::Light &light_3_obj, sg::Light &light_4_obj, sg::Projectile &projectile_1_obj) :
    camera_(camera_node),
    player_1(player_1_node),
    player_2(player_2_node),
    player_3(player_3_node),
    player_4(player_4_node),
    player_5(player_5_node),
	//Added light objects.
    light_1(light_1_obj),
    light_2(light_2_obj),
    light_3(light_3_obj),
    light_4(light_4_obj),
    projectile_1(projectile_1_obj)
{
}

void Controller::process_event(const Event &event)
{
	// IF IT'S A KEY PRESS WE NEED TO CHECK TO SEE IF WE SHOULD SWITCH MODES
	if (event.type == EventType::eKeyInput)
	{
		const auto &key_input_event = static_cast<const KeyInputEvent &>(event);

		// When we create a new instance.
		if (key_input_event.code == KeyCode::eQ)
		{
			switch_mode(key_input_event.code);
			return;
		}

		// NUMBER KEYS ARE ALL GREATER
		if (key_input_event.code > KeyCode::eR)
		{
			switch_mode(key_input_event.code);
			return;
		}

		// If event is the R-key we need to reset ALL objects
		if (key_input_event.code == KeyCode::eR)
		{
			reset_locations(event);
			return;
		}
	}

	// DELIVER IT TO THE SCRIPT
	deliver_event(event);
}

void Controller::reset_locations(const Event &event)
{
	sg::Script *p_script;
	p_script = &player_1.get_component<sg::Script>();
	p_script->process_event(event);
	p_script = &player_2.get_component<sg::Script>();
	p_script->process_event(event);
	p_script = &camera_.get_component<sg::Script>();
	p_script->process_event(event);

	light_1.process_event(event);
	light_2.process_event(event);
	light_3.process_event(event);
	light_4.process_event(event);
	projectile_1.process_event(event);

	//Reset the added players
	player_3.set_render(false);
	player_4.set_render(false);
	player_5.set_render(false);

	//Reset the rotation of a player

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
	else if (code == KeyCode::e8 && player_3.get_render()) //Also check if it has been spawned.
	{
		mode_ = ControllerMode::ePlayer3;
	}
	else if (code == KeyCode::e9 && player_4.get_render())
	{
		mode_ = ControllerMode::ePlayer4;
	}
	else if (code == KeyCode::e0 && player_5.get_render())
	{
		mode_ = ControllerMode::ePlayer5;
	}
	else if (code == KeyCode::e0)
	{
		mode_ = ControllerMode::ePlayer5;
	}
	else if (code == KeyCode::eQ)
	{
		mode_ = ControllerMode::eCreatePlayer;
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
	set_players_rotate_false();
	if (mode_ == ControllerMode::ePlayer1)
	{
		p_script = &player_1.get_component<sg::Script>();
		player_1.set_rotate(true);
	}
	else if (mode_ == ControllerMode::ePlayer2)
	{
		p_script = &player_2.get_component<sg::Script>();
		player_2.set_rotate(true);
	}
	else if (mode_ == ControllerMode::ePlayer3)
	{
		p_script = &player_3.get_component<sg::Script>();
		player_3.set_rotate(true);
	}
	else if (mode_ == ControllerMode::ePlayer4)
	{
		p_script = &player_4.get_component<sg::Script>();
		player_4.set_rotate(true);
	}
	else if (mode_ == ControllerMode::ePlayer5)
	{
		p_script = &player_5.get_component<sg::Script>();
		player_5.set_rotate(true);
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
	else if (mode_ == ControllerMode::eCreatePlayer)
	{
		mode_ = ControllerMode::eCamera;
		spawn_player();
		return;
	}
	else
	{
		p_script = &camera_.get_component<sg::Script>();
		projectile_1.process_event(event);
	}

	// AND NOW ASK THE SCRIPT TO PROVIDE A PROGRAMMED RESPONSE
	p_script->process_event(event);
}

void Controller::spawn_player()
{
	sg::Node *possible_players[] = {&player_3, &player_4, &player_5};
	for (sg::Node *current_player : possible_players)
	{
		// Iterate through the possible players, the first one that is false rendered, make it true then return
		if (!current_player->get_render())
		{
			current_player->get_transform().set_tranlsation(glm::vec3(0.0f, 0.0f, 0.0f));
			current_player->set_render(true);
			if (current_player->get_name().compare(player_3.get_name()) == 0)
			{
				mode_ = ControllerMode::ePlayer3;
			}
			if (current_player->get_name().compare(player_4.get_name()) == 0)
			{
				mode_ = ControllerMode::ePlayer4;
			}
			if (current_player->get_name().compare(player_5.get_name()) == 0)
			{
				mode_ = ControllerMode::ePlayer5;
			}
			return;
		}
	}
	// If we fall through all were already rendered.
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
void Controller::set_players_rotate_false()
{
	player_1.set_rotate(false);
	player_2.set_rotate(false);
	player_3.set_rotate(false);
	player_4.set_rotate(false);
	player_5.set_rotate(false);

}

}        // namespace W3D