#include "Heads.h"

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
	if (this->GetPlayer() != target->GetPlayer())
	{
		target->Hit(_attack);
	}
}

void Soldier::ForcedAttack(Entity* target)       //ǿ�ƹ�������ν������������ϰ�����A+����Ҽ�
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

void Soldier::Die()     
{
	_pSoldierManager->DestroySoldier(this);
}