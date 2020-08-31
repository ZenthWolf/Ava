#include "Behavior.h"

Behavior::Behavior(Enemy& self, std::vector<std::unique_ptr<Attack>>& atk)
	:self(self), attack(atk), rng(std::random_device()())
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
	Rect<float> collBox = self.GetCollBox();

	if (collBox.Y0 <= 0.0f)
	{
		self.Move({ 0.0f, -collBox.Y0 });
		self.BounceY();
		self.BounceX();
	}

	else if (collBox.Y1 >= 600.0f)
	{
		self.Move({ 0.0f, 600.0f - collBox.Y1 });
		self.BounceY();
		self.BounceX();
	}

	else if (collBox.X0 <= 0.0f)
	{
		self.Move({ -collBox.X0, 0.0f });
		self.BounceX();
		self.BounceY();
	}

	else if (collBox.X1 >= 800.0f)
	{
		self.Move({ 800.0f - collBox.X1, 0.0f });
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
		attack.push_back(
			std::make_unique<BlobShot>(self.BlobShot())
		);
		self.ChangeAct(Entity::Action::Move);
	}
}

