//
// Created by maks on 19.01.18.
//

#include "GameObject.hpp"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}

GameObject::GameObject(GameObject const &rhs)
{
	*this = rhs;
}

GameObject& GameObject::operator=(GameObject const &src)
{
	this->type = src.type;
	this->hp = src.hp;
	this->shape = src.shape;
	this->shootSpeed = src.shootSpeed;
	this->actionDelimiter = src.actionDelimiter;
	return *this;
}

void GameObject::hit(int damage)
{
	hp -= damage;
}
