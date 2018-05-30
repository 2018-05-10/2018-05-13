#include "Soldier.h"

Soldier::Soldier() {}

Soldier::~Soldier() {}

int Soldier::GetAttack()
{
	return _attack;
}

void Soldier::Attack(Entity* target)
{
	if (target == NULL)
	{
		return;
	}
	target->Hit(_attack);
}

bool Soldier::init()
{
	return true;
}