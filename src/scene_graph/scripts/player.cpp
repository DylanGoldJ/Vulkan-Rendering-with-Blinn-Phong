// IN THIS FILE WE'LL BE DECLARING METHODS DECLARED INSIDE THIS HEADER FILE
#include "player.hpp"

namespace W3D::sg
{

const float Player::TRANSLATION_MOVE_STEP = 5.0f;

Player::Player(Node &node) :
    NodeScript(node)

{
	distance_from_start = glm::vec3(0.0f, 0.0f, 0.0f);
}

// This method is called every frame. Responsible for updating a node's state
void Player::update(float delta_time)
{
	glm::vec3 delta_translation(0.0f, 0.0f, 0.0f);

	// Caveat: The models are rotated! Therefore, we translate the objects in model space in z-direction
	if (key_pressed_[KeyCode::eW])
	{
		delta_translation.y += TRANSLATION_MOVE_STEP;
		distance_from_start.y -= TRANSLATION_MOVE_STEP;
	}

	if (key_pressed_[KeyCode::eS])
	{
		delta_translation.y -= TRANSLATION_MOVE_STEP;
		distance_from_start.y += TRANSLATION_MOVE_STEP;
	}

	if (key_pressed_[KeyCode::eA])
	{
		delta_translation.x -= TRANSLATION_MOVE_STEP;
		distance_from_start.x += TRANSLATION_MOVE_STEP;
	}

	if (key_pressed_[KeyCode::eD])
	{
		delta_translation.x += TRANSLATION_MOVE_STEP;
		distance_from_start.x -= TRANSLATION_MOVE_STEP;
	}

	// WE NEED TO SCALE BECAUSE WE HAVE A VARIABLE TIMER
	delta_translation *= speed_multiplier_ * delta_time;

	// UPDATE THE TRANSFORMATION VECTOR FOR THIS NODE
	auto &T = get_node().get_transform();
	if (key_pressed_[KeyCode::eR])
	{
		distance_from_start *= speed_multiplier_ * delta_time;
		T.set_tranlsation(T.get_translation() + distance_from_start);
		distance_from_start = glm::vec3(0.0f, 0.0f, 0.0f);
	}
	else
	{
		T.set_tranlsation(T.get_translation() + delta_translation);
	}
	
	
// Assuming T is your transformation object
	if (get_node().get_rotate())
	{
		glm::quat cur = T.get_rotation();

		// Define an axis of rotation (y-axis in this case)
		glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);

		// Define the angle of rotation
		float rotationAngle = 0.0001f;        // Adjust the angle as needed

		// Create a quaternion for the rotation
		glm::quat rotationQuat = glm::angleAxis(rotationAngle, rotationAxis);

		// Combine the current rotation with the new rotation
		T.set_rotation(cur * rotationQuat);
	}
}

//void Player::reset_rotation()
//{
//	auto &T = get_node().get_transform();
//	T.set_rotation(glm::quat(0.0f, 0.0f, 0.0f, 1.0f));
//}

void Player::process_event(const Event &event)
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

}	// namespace W3D::sg