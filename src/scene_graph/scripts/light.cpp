// IN THIS FILE WE'LL BE DECLARING METHODS DECLARED INSIDE THIS HEADER FILE
#include "light.hpp"

namespace W3D::sg
{

const float Light::TRANSLATION_MOVE_STEP = 5.0f;
glm::vec3   location;

Light::Light(float x, float y, float z)
{
	start_location = glm::vec3(x, y, z);
	location = glm::vec3(x, y, z);
}

Light::Light(glm::vec3 vector)
{
	start_location = vector;
	location = vector;
}



// This method is called every frame. Responsible for updating a node's state
void Light::update(float delta_time)
{
	glm::vec3 delta_translation(0.0f, 0.0f, 0.0f);

	// Caveat: The models are rotated! Therefore, we translate the objects in model space in z-direction
	if (key_pressed_[KeyCode::eW])
	{
		delta_translation.y += TRANSLATION_MOVE_STEP;
	}

	if (key_pressed_[KeyCode::eS])
	{
		delta_translation.y -= TRANSLATION_MOVE_STEP;
	}

	if (key_pressed_[KeyCode::eA])
	{
		delta_translation.x -= TRANSLATION_MOVE_STEP;
	}

	if (key_pressed_[KeyCode::eD])
	{
		delta_translation.x += TRANSLATION_MOVE_STEP;
	}

	if (key_pressed_[KeyCode::eR])
	{
		location = start_location;
	}

	// WE NEED TO SCALE BECAUSE WE HAVE A VARIABLE TIMER
	delta_translation *= speed_multiplier_ * delta_time;

	// Update Location
	location += delta_translation;
}

void Light::process_event(const Event &event)
{
	if (event.type == EventType::eKeyInput)
	{
		const auto &key_event = static_cast<const KeyInputEvent &>(event);

		// WE DO THIS SO WE CAN RESPOND TO HOLDING DOWN A KEY FOR MULTIPLE FRAMES
		// WHICH WE THEN DO INSIDE THE update FUNCTION
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
glm::vec3 Light::getLocation()
{
	return location;
}

}        // namespace W3D::sg

// void Renderer::move_light(int light_num, int cord)
//{
//	glm::vec3 current_light   = LIGHT_POSITIONS[0];
//	glm::vec3 new_light_value = glm::vec3(current_light.x + .01, current_light.y, current_light.z);
//	LIGHT_POSITIONS[0]        = new_light_value;
// }