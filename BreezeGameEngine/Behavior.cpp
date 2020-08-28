#include "Behavior.h"

Behavior::Behavior(Enemy& self)
	:self(self), rng(std::random_device()())
{
}

void Behavior::Update(const float dt)
{
	self.Update(dt);  // Right now, for whatever I can't pull out!

	Enemy::Action state = self.GetState();

	switch (state)
	{

	case Enemy::Action::Move:
	{
		MoveUpdate(dt);
		break;
	}

	case Enemy::Action::Aim:
	{
		AimUpdate(dt);
		break;
	}

	case Enemy::Action::Stunned:
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
	Rect<float> collBox = self.GetCollBox();

	if (collBox.Y0 <= 0.0f)
	{
		self.Move({ 0.0f, -collBox.Y0 });
		self.BounceY();
	}

	else if (collBox.Y1 >= 600.0f)
	{
		self.Move({ 0.0f, 600.0f - collBox.Y1 });
		self.BounceY();
	}

	else if (collBox.X0 <= 0.0f)
	{
		self.Move({ -collBox.X0, 0.0f });
		self.BounceX();
	}

	else if (collBox.X1 >= 800.0f)
	{
		self.Move({ 800.0f - collBox.X1, 0.0f });
		self.BounceX();
	}
}

void Behavior::AttackTimer(const float dt)
{
	atkTimer += dt;
	if (atkTimer >= 0.0f)
	{
		self.StateChange(Enemy::Action::Aim);
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
		self.BlobShot();
		self.StateChange(Enemy::Action::Move);
	}
}

