#pragma once

#include "scene_graph/script.hpp"

namespace W3D::sg
{
class Projectile : public Script
{
  private:
	float                             speed_multiplier_ = 2.0f;
	std::unordered_map<KeyCode, bool> key_pressed_;
	glm::vec3                         location;
	glm::vec3                         start_location;
	int                               id;
	bool                              in_motion;

  public:
	static const float TRANSLATION_MOVE_STEP;

	/*
	 * Constructor with 3 starting cords.
	 */
	Projectile(float x, float y, float z);
	/*
	    Alt constructor for a glm::vec3
	*/
	Projectile(glm::vec3);
	/*
	 * Called each frame, this function updates the projectile's state.
	 */
	void update(float delta_time) override;

	/*
	 * Processes events, like key presses.
	 */
	void process_event(const Event &event) override;
	glm::vec3 getLocation();
};
}