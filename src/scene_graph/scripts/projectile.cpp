#include "projectile.hpp"

namespace W3D::sg
{
const float Projectile::TRANSLATION_MOVE_STEP = 5.0f;
//glm::vec3   location;

W3D::sg::Projectile::Projectile(float x, float y, float z)
{
	start_location = glm::vec3(x, y, z);
	location       = glm::vec3(x, y, z);
}

W3D::sg::Projectile::Projectile(glm::vec3 vector)
{
	start_location = vector;
	location       = vector;
}

void W3D::sg::Projectile::update(float delta_time)
{
}

void W3D::sg::Projectile::process_event(const Event &event)
{
}
glm::vec3 Projectile::getLocation()
{
	return location;
}

}


