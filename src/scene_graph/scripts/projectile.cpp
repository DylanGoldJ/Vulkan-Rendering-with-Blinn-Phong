#include "projectile.hpp"

namespace W3D::sg
{
const float Projectile::TRANSLATION_MOVE_STEP = 5.0f;
const float Projectile::ROTATION_MOVE_WEIGHT  = 8.0f;
const float Projectile::ANGLE_MOVE_WEIGHT     = 0.05f;

W3D::sg::Projectile::Projectile(float x, float y, float z)
{
	start_location = glm::vec3(x, y, z);
	location       = glm::vec3(x, y, z);
	rotation       = glm::vec3(0.0f, 0.0f, 0.0f);
	angle          = 0.0f;
	in_motion      = false;
	location_behind_camera = glm::vec3(x, y, z);
}

W3D::sg::Projectile::Projectile(glm::vec3 vector)
{
	start_location = vector;
	location       = vector;
	rotation       = glm::vec3(0.0f, 0.0f, 0.0f);
	angle          = 0.0f;
	in_motion      = false;
	location_behind_camera = vector;
}

void W3D::sg::Projectile::update(float delta_time)
{
	glm::vec3 delta_rotation(0.0f, 0.0f, 0.0f);
	glm::vec3 delta_translation(0.0f, 0.0f, 0.0f);

	// Timer controls
	if (timer_.is_running())
	{
		timer_.tick();
	}
	if (timer_.elapsed() > 3)
	{
		in_motion = false;
		timer_.stop();
		location = location_behind_camera;
	}

	// Key press functions
	if (key_pressed_[KeyCode::eF] && !in_motion) // Fired
	{
		in_motion = true;
		timer_.start_time_ = timer_.previous_tick_;
		timer_.start();
	}

	// Location updates
	if (in_motion)
	{
		delta_translation.z -= TRANSLATION_MOVE_STEP;
	}

	location_behind_camera += distance_to_camera;

	delta_rotation.x += ROTATION_MOVE_WEIGHT;
	delta_rotation.y += ROTATION_MOVE_WEIGHT;

	delta_translation *= speed_multiplier_ * delta_time;
	if (!in_motion)
		delta_translation += distance_to_camera;
	location += delta_translation;


	delta_rotation *= delta_time;
	rotation += delta_rotation;
}

void W3D::sg::Projectile::process_event(const Event &event)
{
	if (event.type == EventType::eKeyInput)
	{
		const auto &key_event = static_cast<const KeyInputEvent &>(event);

		if (key_event.action == KeyAction::eDown || key_event.action == KeyAction::eRepeat)
		{
			key_pressed_[key_event.code] = true;
		}
		else
		{
			key_pressed_[key_event.code] = false;
		}
	}
}
glm::vec3 Projectile::getLocation()
{
	return location;
}

glm::vec3 Projectile::getRotation()
{
	return rotation;
}

float Projectile::getAngle()
{
	angle += ANGLE_MOVE_WEIGHT;
	return angle;
}

void Projectile::setDistanceToCamera(glm::vec3 *num)
{
	distance_to_camera = glm::vec3(num->x, num->y, num->z);
}

}


