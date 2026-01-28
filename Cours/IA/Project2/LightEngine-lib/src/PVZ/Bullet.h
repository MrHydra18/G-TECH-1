#pragma once
#include "Entity.h"


class Bullet : public Entity
{
	void OnCollision(Entity* other) override;
	void OnInitialize() override;
};

