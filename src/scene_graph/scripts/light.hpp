#pragma once

#include "scene_graph/script.hpp"

namespace W3D::sg
{
/*
 * This is the script for a player, which in our demo is just a cube in
 * the scene. The update function specifically
 */
class Light : public Script
{
  private:
	float                             speed_multiplier_ = 2.0f;
	std::unordered_map<KeyCode, bool> key_pressed_;
	glm::vec3                         location;
	glm::vec3                         start_location;

  public:
	static const float TRANSLATION_MOVE_STEP;

	/*
	 * Constructor sends the 3 starting cords.
	 */
	Light(float x, float y, float z);
	/*
		Extra constructor for just a glm::vec3
	*/
	Light(glm::vec3);
	/*
	 * Called each frame, this function updates the lights's state. Note, if a key
	 * for controlling the player is pressed it will respond here for movement.
	 */
	void update(float delta_time) override;

	/*
	 * When the lights is the active object that can be moved it will be asked to
	 * respond to events like key presses.
	 */
	void process_event(const Event &event) override;

	/*
		Get the light position.
	*/
	glm::vec3 getLocation();
};        // class light

}        // namespace W3D::sg

// void move_light(int light_num, int cord);