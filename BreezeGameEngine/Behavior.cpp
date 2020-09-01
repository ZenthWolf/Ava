#include "Behavior.h"

Behavior::Behavior(Enemy& self, Room& room)
	:self(self), room(room), rng(std::random_device()())
{
	std::uniform_real_distribution<float> timer(0.0f, 3.0f);
	atkTimer = -timer(rng);
}

void Behavior::Update(const float dt)
{
	self.Update(dt);

	Entity::Action curAct = self.GetAction();

	switch (curAct)
	{

	case Entity::Action::Move:
	{
		if (!self.IsStunned())
		{
			MoveUpdate(dt);
		}
		break;
	}

	case Entity::Action::Attack:
	{
		if (!self.IsStunned())
		{
			AimUpdate(dt);
		}
		break;
	}

	case Entity::Action::KnockBack:
	{
		RecoilUpdate(dt);
		break;
	}

	case Entity::Action::Stunned:
	{
		break;
	}

	}
}

bool Behavior::Cull() const
{
	return self.Cull();
}

void Behavior::MoveUpdate(const float dt)
{
	AttackTimer(dt);

	self.Move(self.GetVel() * dt);
	WallHit(WallCheck());
}

Entity::Facing Behavior::WallCheck()
{
	Rect<float> collBox = self.GetCollBox();

	if (collBox.Y0 < 0.0f)
	{
		self.Move({ 0.0f, -collBox.Y0 });
		return Entity::Facing::Up;
	}

	else if (collBox.Y1 > 600.0f)
	{
		self.Move({ 0.0f, 600.0f - collBox.Y1 });
		return Entity::Facing::Down;
	}

	else if (collBox.X0 < 0.0f)
	{
		self.Move({ -collBox.X0, 0.0f });
		return Entity::Facing::Left;
	}

	else if (collBox.X1 > 800.0f)
	{
		self.Move({ 800.0f - collBox.X1, 0.0f });
		return Entity::Facing::Right;
	}
	else
	{
		return Entity::Facing::None;
	}
}

void Behavior::WallHit(Entity::Facing wall)
{
	if (!(wall == Entity::Facing::None))
	{
		self.BounceX();
		self.BounceY();
	}
}

void Behavior::AttackTimer(const float dt)
{
	atkTimer += dt;
	if (atkTimer >= 0.0f)
	{
		self.ChangeAct(Entity::Action::Attack);
		std::uniform_real_distribution<float> timer(1.0f, 3.0f);
		atkTimer = -timer(rng);
		aimTimer = -0.3f;
	}
}

void Behavior::AimUpdate(const float dt)
{
	aimTimer += dt;
	if (aimTimer >= 0.0f)
	{
		room.attack.push_back(
			std::make_unique<BlobShot>(self.BlobShot(room.Ava))
		);
		self.ChangeAct(Entity::Action::Move);
	}
}

void Behavior::RecoilUpdate(const float dt)
{
	self.Recoil(dt);
	WallCheck();
}

