#pragma once
#include "Entity.h"
#include<iostream>


class Zombi : public Entity
{
public:
	void OnCollision(Entity* other) override;
};

