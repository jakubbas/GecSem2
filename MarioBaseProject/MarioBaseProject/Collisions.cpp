#include "Collisions.h"
#include "Character.h"

//initialises instance to nullptr
Collisions* Collisions::m_instance = nullptr;

Collisions::Collisions()
{

}

Collisions::~Collisions()
{
	m_instance = nullptr;
}

Collisions* Collisions::Instance()
{
	if (!m_instance)
	{
		m_instance = new Collisions;
	}

	return m_instance;
}

bool Collisions::Circle(Character* character1, Character* character2)
{
	//calculates vector that separates the two objects
	Vector2D vec = Vector2D((character1->GetPosition().x - character2->GetPosition().x), (character1->GetPosition().y - character2->GetPosition().y));
	//gets the length of the vector
	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	//gets collision radius of each character, and accumulates them.
	double combined_distance = (character1->GetCollisionRadius() + character2->GetCollisionRadius());

	return distance < combined_distance;
}
//bool Collisions::Box(Rect2D rect1, Rect2D rect2)
//{
//
//}
