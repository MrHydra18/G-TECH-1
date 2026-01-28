#pragma once
#include "Entity.h"
#include<iostream>


class Zombie : public Entity
{
public:
	void OnCollision(Entity* other) override;
	void OnInitialize() override;
};

