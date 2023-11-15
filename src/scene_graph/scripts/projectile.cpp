#include "projectile.hpp"

namespace W3D::sg
{
const float Projectile::TRANSLATION_MOVE_STEP = 5.0f;

W3D::sg::Projectile::Projectile(float x, float y, float z)
{
	start_location = glm::vec3(x, y, z);
	location       = glm::vec3(x, y, z);
	in_motion      = false;
}

W3D::sg::Projectile::Projectile(glm::vec3 vector)
{
	start_location = vector;
	location       = vector;
	in_motion      = false;
}

void W3D::sg::Projectile::update(float delta_time)
{
	if (timer_.is_running())
	{
		timer_.tick();
	}

	if (key_pressed_[KeyCode::eF] && !in_motion)
	{
		in_motion = true;
		timer_.start_time_ = timer_.previous_tick_; //start our timer when the projectile first fires
		timer_.start();
	}

	if (timer_.elapsed() > 3)
	{
		in_motion = false;
		timer_.stop();
		location  = start_location;
	}

	if (in_motion)
	{
		glm::vec3 delta_translation(0.0f, 0.0f, 0.0f);
		delta_translation.z -= TRANSLATION_MOVE_STEP;
		delta_translation *= speed_multiplier_ * delta_time;
		location += delta_translation;
	}
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

}


