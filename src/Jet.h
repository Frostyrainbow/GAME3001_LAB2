#pragma once
#ifndef __JET__
#define __JET__
#include "DisplayObject.h"
#include "TextureManager.h"

class Jet final : public DisplayObject
{
public:
	// constructor(s)
	Jet();

	// destructor
	~Jet();
	
	// life-cycle methods inherited from DisplayObject
	void draw() override;
	void update() override;
	void clean() override;

	//Getters
	float getRotation();
	glm::vec2 getOrientation();
	float getTurnRate();
	float getAccelerationRate();

	//Setters
	void setDestination(glm::vec2 destination);
	void setMaxSpeed(float speed);
	void setOrientation(glm::vec2 orientation);
	void setRotation(float angle);
	void setTurnRate(float rate);
	void setAccelerationRate(float rate);

private:

	glm::vec2 m_destination;
	glm::vec2 m_targetDirection;
	glm::vec2 m_orientation;
	float m_rotationAngle;
	float m_maxSpeed;
	float m_turnRate;
	float m_accelerationRate;

	// private function
	void m_Move();
};

#endif /* defined (__SPACE_SHIP__) */
