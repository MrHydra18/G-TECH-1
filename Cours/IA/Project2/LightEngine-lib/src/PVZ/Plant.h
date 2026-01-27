#pragma once
#include "Entity.h"
#include<iostream>


class Plant : public Entity
{
public:
	void OnCollision(Entity* other) override;
};

