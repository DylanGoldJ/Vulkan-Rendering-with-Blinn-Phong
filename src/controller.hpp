#pragma once

#include "scene_graph/scripts/light.hpp"
#include "scene_graph/scripts/projectile.hpp"

namespace W3D
{
struct Event;
enum class KeyCode;
namespace sg
{
class Node;
}

/*
* Enum that represents which node the user is currently controlling.
*/ 
enum class ControllerMode
{
	eCamera,
	ePlayer1,
	ePlayer2,
	ePlayer3,
	ePlayer4,
	ePlayer5,
	eLight1,
	eLight2,
	eLight3,
	eLight4,
	eProjectile1,
	eCreatePlayer
};

/*
* This class serves as the traffic cop for directing user interactions to be
* handled by the appropriate code. Note, game demo components are associated
* with Script objects that provide those responses.
*/
class Controller
{
  private:
	// OUR Controller PROVIDES ACCESS TO ALL THE CONTROLLABLE GAME OBJECTS,
	// OF WHICH THERE ARE CURRENTLY THREE: THE CAMERA, AND PLAYER 1 AND 
	// PLAYER 2, WHICH ARE REALLY JUST SIMPLY CUBES
	sg::Node      &camera_;		
	sg::Node      &player_1;
	sg::Node      &player_2;
	sg::Node      &player_3;
	sg::Node      &player_4;
	sg::Node      &player_5;

	//Here are lights that are also controllable
	sg::Light &light_1;
	sg::Light &light_2;
	sg::Light &light_3;
	sg::Light &light_4;

	sg::Projectile &projectile_1;
	// THIS KEEPS TRACK OF WHICH GAME OBJECT WE ARE CURRENTLY CONTROLLING
	// WITH THIS OBJECT
	ControllerMode mode_;

  public:
	/*
	* Constructor that initializes all the controllable game objects.
	*/
	Controller(sg::Node &camera_node, sg::Node &player_1_node, sg::Node &player_2_node, sg::Node &player_3_node, sg::Node &player_4_node, sg::Node &player_5_node,
		sg::Light &light_1_obj, sg::Light &light_2_obj, sg::Light &light_3_obj, sg::Light &light_4_obj, sg::Projectile &projectile_1_obj);

	/*
	* This function handles events. If it's a key event it will provide a programmed
	* response because it may need to switch modes. It will always follow that with a
	* call to deliver the event, which will ask the associated script to respond.
	*/
	void process_event(const Event &event);

	// Called when the R-key is pressed, it resets the locations of the players, lights, and camera back to its original position
	void reset_locations(const Event &event);

	/*
		This is called when we spawn a player
	*/
	void spawn_player();

	/*
	* This function changes the game object that is affected by interactions.
	*/
	void switch_mode(KeyCode code);

	/*
	* This function delivers event information to the script associated with the
	* active game mode object.
	*/
	void deliver_event(const Event &event);

	/*
	* This function tests to see if the two player (i.e. cube) objects are currently
	* overlapping and returns true if they are, false otherwise.
	* 
	* Note: this method could and should probably have a more suitable home, but we
	* are not implementing any physics in this application so keeping it here keeps
	* it simple.
	*/
	bool are_players_colliding();

	/*
		This function creates a new player object
		It does this by just duplicating the player1 object to keep it simple with a slight translation.
	*/

	void set_players_rotate_false();

};	// class Controller

}	// namespace W3D

// This is a test comment