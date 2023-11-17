#pragma once

#include "scene_graph/script.hpp"
#include "common/timer.hpp"

namespace W3D::sg
{
class Projectile : public Script
{
  private:
	float                             speed_multiplier_ = 2.0f;
	std::unordered_map<KeyCode, bool> key_pressed_;
	glm::vec3                         location; // current location
	glm::vec3                         rotation; // current rotation (for spinning)
	float							  angle; // current angle (for spinning)
	glm::vec3                         start_location; // location to return to after reset
	int                               id;
	bool                              in_motion; // bool for has the bullet been fired and in motion
	Timer                             timer_; // timer to track bullet airtime
	glm::vec3                         camera_location; // transformation to apply to follow the camera
	bool                              should_render = false;


  public:
	static const float TRANSLATION_MOVE_STEP;
	static const float ROTATION_MOVE_WEIGHT;
	static const float ANGLE_MOVE_WEIGHT;

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
	
	/*
	* Get location of projectile
	*/
	glm::vec3 getLocation();

	/*
	* Get rotation of projectile
	*/
	glm::vec3 getRotation();

	float getAngle();

	void setDistanceToCamera(glm::vec3 num);

	bool get_render();
};
}