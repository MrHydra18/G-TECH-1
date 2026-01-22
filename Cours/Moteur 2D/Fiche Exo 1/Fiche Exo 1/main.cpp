#include<iostream>
#include "StaticObject.h"
#include"BreakableObject.h"
#include"Mob.h"
#include "Player.h"

int main()
{
	StaticObject* patate = new StaticObject({ 32, 100 });
	BreakableObject* tomate = new BreakableObject({ 50, 50 }, 15, 15);
	tomate->TakeDamage(20);
	Mob* carrote = new Mob({ 100, 100 }, 20, 25, { 12, 15 });
	carrote->Move();
	Player* ananas = new Player({ 200, 200 }, 100, 100, { 10, 10 });
	ananas->Attack(carrote);



	return 0;
}