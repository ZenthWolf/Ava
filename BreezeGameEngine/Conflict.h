#pragma once

#include "Vec.h"
#include "Rect.h"
#include "Graphics.h"
#include "Animation.h"
#include "Keyboard.h"
#include<vector>
#include<memory>
#include<random>

class Attack;
class Entity;

class Character;
class Enemy;

class SwordSrike;
class SwordStun;
class ArrowShot;

class BlobShot;

class Entity
{
public:
	virtual void OnHit(class Attack& attack) = 0;

	enum class Allegiance
	{
		Ava,
		Enemy,
		None
	};
	enum class Action
	{
		Stunned,
		Move,
		Attack,
		Jump
	};

	virtual void Update(float const dt) = 0;
	virtual void Draw(Graphics& gfx) = 0;
	void TakeDamage(float hp);
	void Stun(float duration = 2.0f);

	Vec<float> GetPos() const;
	Vec<float> GetVel() const;
	void Move(const Vec<float> dr);

	virtual void PushBox(Rect<float> wall);
	Allegiance GetAllegiance() const;
	Action GetAction() const;
	void ChangeAct(const Action newAct);

	virtual Rect<float> GetCollBox() const;
	bool IsVulnerable() const;
	bool IsStunned() const;
	virtual bool Cull();


protected:
	virtual ~Entity() = default;

	Entity(Vec<float> pos, Allegiance allegiance);
	Entity(Vec<float> pos, int health);
	Entity(Vec<float> pos, Vec<float> vel, int health, Allegiance allegiance);
	void VulnerableTimer(float dt);
	void StatusUpdate(float dt);

	Allegiance allegiance = Allegiance::None;
	Action curAct = Action::Move;
	int health;
	bool vulnerable = true;
	float invultime = 0.0f;
	bool stun = false;
	float stuntime = 0.0f;
	bool flash = false;
	bool cull = false;
	Vec<float> pos;
	Vec<float> vel = { 0.0f, 0.0f };
	Vec<float> collBoxSize = { 0.0f, 0.0f };
};

class Attack
{
public:
	virtual void Afflict(Character& targ) = 0;
	virtual void Afflict(Enemy& targ) = 0;

	Attack(const Vec<float> pos, Entity& source, const Color col = Colors::Red);

	virtual void Update(float dt);
	void Draw(Graphics& gfx) const;

	Rect<float> GetCollBox() const;
	Entity::Allegiance GetAllegiance() const;
	virtual bool Cull();

protected:
	Vec<float> pos;
	float vel = 0.0f;
	Vec<float> hitBoxSize;
	bool cull = false;
	Color col = Colors::Red;

	Entity& src;
};

class Character : public Entity
{
public:
	enum class Sequence
	{
		WalkingLeft,
		WalkingRight,
		WalkingUp,
		WalkingDown,
		StandingLeft,
		StandingRight,
		StandingUp,
		StandingDown,
		Count
	};

	Character(const Vec<float>& pos, Keyboard& kbd);
	void Draw(Graphics& gfx) override;
	void Draw(Graphics& gfx, Color sub) const;
	void Update(float const dt) override;
	Rect<float> GetCollBox() const override;
	Sequence GetFacing() const;

	void OnHit(class Attack& attack) override
	{
		attack.Afflict(*this);
	}
	Vec<float> MakeAttack();
	void DVel(Vec<float> dv);
	void AtkCooldown(float dt = 0.250f);

private:
	void SetDir(const Vec<float>& dir);

	Surface sprite;
	float atkCool = 0.0f;
	std::vector<Animation> animation;
	Sequence curSeq = Sequence::StandingDown;
	float speed = 120.0f;

	Keyboard& kbd;
};

class Enemy : public Entity
{
public:
	Enemy(const Vec<float> pos, const Vec<float> vel);

	void Update(const float dt) override;
	void Draw(Graphics& gfx) override;
	void OnHit(class Attack& attack) override
	{
		attack.Afflict(*this);
	}
	virtual void PushBox(Rect<float> wall) override;

	//This trash has to be handled better some other way, right?
	void fixpos(float dr);

	void BounceX();
	void BounceY();
	BlobShot BlobShot();

private:
	float aimTimer = 0.0f;

	Color col;
	float size;

	std::mt19937 rng;
	float atkTimer;
};

class SwordStrike : public Attack
{
public:
	SwordStrike(const Vec<float> pos0, Character& src)
		:Attack(pos0, src)
	{
		switch (src.GetFacing())
		{
		case Character::Sequence::StandingLeft:
		{
			hitBoxSize = { 50.0f, 10.0f };
			pos.X -= hitBoxSize.X;
			pos.Y -= hitBoxSize.Y / 2;
			break;
		}
		case Character::Sequence::StandingRight:
		{
			hitBoxSize = { 50.0f, 10.0f };
			pos.Y -= hitBoxSize.Y / 2;
			break;
		}
		case Character::Sequence::StandingUp:
		{
			hitBoxSize = { 10.0f, 50.0f };
			pos.X -= hitBoxSize.X / 2;
			pos.Y -= hitBoxSize.Y;
			break;
		}
		case Character::Sequence::StandingDown:
		{
			hitBoxSize = { 10.0f, 50.0f };
			pos.X -= hitBoxSize.X/2;
			break;
		}
		}
	}

	void Afflict(Character& targ)
	{

	}
	void Afflict(Enemy& targ)
	{
		if (targ.IsVulnerable())
		{
			targ.TakeDamage(2);
		}
	}

	void Update(float dt) override
	{
		if (!(src.GetAction() == Entity::Action::Attack))
		{
			cull = true;
		}
	}
};

class SwordStun : public Attack
{
public:
	SwordStun(const Vec<float> pos0, Character& src)
		:Attack(pos0, src)
	{
		col = Colors::Green;

		switch (src.GetFacing())
		{
		case Character::Sequence::StandingLeft:
		{
			hitBoxSize = { 50.0f, 10.0f };
			pos.X -= hitBoxSize.X;
			pos.Y -= hitBoxSize.Y / 2;
			break;
		}
		case Character::Sequence::StandingRight:
		{
			hitBoxSize = { 50.0f, 10.0f };
			pos.Y -= hitBoxSize.Y / 2;
			break;
		}
		case Character::Sequence::StandingUp:
		{
			hitBoxSize = { 10.0f, 50.0f };
			pos.X -= hitBoxSize.X / 2;
			pos.Y -= hitBoxSize.Y;
			break;
		}
		case Character::Sequence::StandingDown:
		{
			hitBoxSize = { 10.0f, 50.0f };
			pos.X -= hitBoxSize.X/2;
			break;
		}
		}
	}

	void Afflict(Character& targ)
	{

	}
	void Afflict(Enemy& targ)
	{

		if (targ.IsVulnerable())
		{
			targ.TakeDamage(1);
			targ.Stun();
		}
	}

	void Update(float dt) override
	{
		if (!(src.GetAction() == Entity::Action::Attack))
		{
			cull = true;
		}
	}
};

class ArrowShot : public Attack
{
public:
	ArrowShot(const Vec<float> pos0, Character& src)
		:Attack(pos0, src)
	{
		col = Color(200u, 70u, 0u);

		switch (src.GetFacing())
		{
		case Character::Sequence::StandingLeft:
		{
			hitBoxSize = { 15.0f, 5.0f };
			pos.X -= hitBoxSize.X;
			pos.Y -= hitBoxSize.Y / 2;
			dir = { -1, 0 };
			break;
		}
		case Character::Sequence::StandingRight:
		{
			hitBoxSize = { 15.0f, 5.0f };
			pos.Y -= hitBoxSize.Y / 2;
			dir = { 1, 0 };
			break;
		}
		case Character::Sequence::StandingUp:
		{
			hitBoxSize = { 5.0f, 15.0f };
			pos.X -= hitBoxSize.X / 2;
			pos.Y -= hitBoxSize.Y;
			dir = { 0, -1 };
			break;
		}
		case Character::Sequence::StandingDown:
		{
			hitBoxSize = { 5.0f, 15.0f };
			pos.X -= hitBoxSize.X/2;
			dir = { 0, 1 };
			break;
		}
		}
		vel = 150.0f;
	}

	void Afflict(Character& targ)
	{

	}
	void Afflict(Enemy& targ)
	{
		if (targ.IsVulnerable())
		{
			targ.TakeDamage(1);
		}
	}

	void Update(float dt) override
	{
		pos += dir * vel * dt;
	}

	bool Cull() override
	{
		Rect<float> box = GetCollBox();
		if (box.X0 > 800.0f || box.X1 < 0.0f || box.Y0 > 600.0f || box.Y1 < 0.0f)
		{
			cull = true;
		}

		return cull;
	}

private:
	Vec<float> dir;
};

class BlobShot : public Attack
{
public:
	BlobShot(const Vec<float> pos, Entity& src)
		:Attack(pos, src)
	{
		col = Color(50u, 140u, 255u);
		hitBoxSize = { 7.0f, 7.0f };

		auto rng = std::mt19937(std::random_device()());
		std::uniform_real_distribution<float> comp(-1.0f, 1.0f);
		dir = Vec<float>(comp(rng), comp(rng));
		dir = dir.Norm();
	}

	void Afflict(Character& targ)
	{
		if (targ.IsVulnerable())
		{
			targ.TakeDamage(2);
			cull = true;
		}
	}

	void Afflict(Enemy& targ)
	{

	}

	void Update(float dt) override
	{
		pos += dir * vel * dt;
	}
	
	bool Cull() override
	{
		Rect<float> box = GetCollBox();
		if (box.X0 > 800.0f || box.X1 < 0.0f || box.Y0 > 600.0f || box.Y1 < 0.0f)
		{
			cull = true;
		}

		return cull;
	}

private:
	float vel = 100.0f;
	Vec<float> dir;
};