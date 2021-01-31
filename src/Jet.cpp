#include "Jet.h"
#include "Util.h"
#include "Game.h"

Jet::Jet():m_maxSpeed(10.0f)
{
	TextureManager::Instance()->load("../Assets/textures/jet.png", "jet");

	auto size = TextureManager::Instance()->getTextureSize("jet");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(JET);
	setOrientation(glm::vec2(0.0f, -1.0f));
	setRotation(0.0f);
	setAccelerationRate(10.0f);
	setTurnRate(10.0f);
}

Jet::~Jet()
= default;

void Jet::draw()
{
	TextureManager::Instance()->draw("jet", getTransform()->position.x, getTransform()->position.y, getRotation(), 255, true);
	Util::DrawLine(getTransform()->position, (getTransform()->position + m_orientation * 60.0f));
}

void Jet::update()
{
	m_Move();
}

void Jet::clean()
{

}

float Jet::getRotation()
{
	return m_rotationAngle;
}

glm::vec2 Jet::getOrientation()
{
	return m_orientation;
}

float Jet::getTurnRate()
{
	return m_turnRate;
}

float Jet::getAccelerationRate()
{
	return m_accelerationRate;
}

void Jet::setDestination(const glm::vec2 destination)
{
	m_destination = destination;
}

void Jet::setMaxSpeed(const float speed)
{
	m_maxSpeed = speed;
}

void Jet::setOrientation(const glm::vec2 orientation)
{
	m_orientation = orientation;
}

void Jet::setRotation(float angle)
{
	m_rotationAngle = angle;
	auto offset = -90.0f;
	auto angle_in_radians = (angle + offset) * Util::Deg2Rad;

	auto x = cos(angle_in_radians);
	auto y = sin(angle_in_radians);

	//convert the angle to a normalized vector and store it in orientation
	setOrientation(glm::vec2(x, y));
}

void Jet::setTurnRate(float rate)
{
	m_turnRate = rate;
}

void Jet::setAccelerationRate(float rate)
{
	m_accelerationRate = rate;
}

void Jet::m_Move()
{
	auto deltaTime = TheGame::Instance()->getDeltaTime();
	
	// direction with magnitude
	m_targetDirection = m_destination - getTransform()->position;
	// normalized direction
	m_targetDirection = Util::normalize(m_targetDirection);

	auto target_rotation = Util::signedAngle(getOrientation(), m_targetDirection);

	auto turn_sensitivity = 5.0f;

	if (abs(target_rotation) > turn_sensitivity)
	{
		if (target_rotation > 0.0f)
		{
			setRotation(getRotation() + getTurnRate());
		}
		else if (target_rotation < 0.0f)
		{
			setRotation(getRotation() - getTurnRate());
		}
	}

	getRigidBody()->acceleration = getOrientation() * getAccelerationRate();

	getRigidBody()->velocity += getOrientation() * (deltaTime)+0.5f * getRigidBody()->acceleration * (deltaTime);

	getRigidBody()->velocity = Util::clamp(getRigidBody()->velocity, m_maxSpeed);

	getTransform()->position += getRigidBody()->velocity;

}