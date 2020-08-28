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

class Attack
{
public:
	//VConcrete Elements to be VisitedV
	virtual void Afflict(Character& targ) = 0;
	virtual void Afflict(Enemy& targ) = 0;
	//^Concrete Elements to be Visited^

	Attack(const Vec<float> pos, const Color col = Colors::Red);
	Attack()
	{
		pos = { 0,0 };
		hitBoxSize = { 0,0 };
	}

	virtual void Update(float dt);
	void Draw(Graphics& gfx) const;
	Rect<float> GetCollBox() const;

protected:
	Vec<float> pos;
	float vel = 0.0f;
	Vec<float> hitBoxSize;
	Color col = Colors::Red;
};

class Entity
{
public:
	//VAccept Visitors and Break EncapsulationV
	virtual void OnHit(class Attack& attack) = 0;

	void TakeDamage(float hp)
	{
		assert(hp >= 0);
		health -= hp;
		vulnerable = false;
		invultime = -0.5f;
		flash = true;
		if (health <= 0)
		{
			cull = true;
		}
	}

	void Stun(float duration = 2.0f)
	{
		if (!stun)
		{
			stun = true;
			stuntime = -duration;
		}
	}
	//^Accept Visitors and Break Encapsulation^

	enum class Allegiance
	{
		Ava,
		Enemy,
		None
	};
	virtual void Update(float const dt) = 0;
	virtual void Draw(Graphics& gfx) = 0;
	//virtual void OnHit(Entity& attacker, int atindex) = 0;

	Vec<float> GetPos() const;
	Vec<float> GetVel() const;
	void Move(const Vec<float> dr);

	virtual void PushBox(Rect<float> wall);
	Allegiance GetAllegiance() const;
	virtual Rect<float> GetCollBox() const;
	int GetAttackNum() const;
	bool IsVulnerable() const;
	virtual bool Cull();


protected:
	virtual ~Entity() = default;

	Entity(Vec<float> pos, Allegiance allegiance);
	Entity(Vec<float> pos, int health);
	Entity(Vec<float> pos, Vec<float> vel, int health, Allegiance allegiance);
	void VulnerableTimer(float dt);
	void StatusUpdate(float dt);

	Allegiance allegiance = Allegiance::None;
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
	std::vector<std::unique_ptr<class Attack>> attack;
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
private:
	enum class Action
	{
		Move,
		Attack,
		Jump
	};
public:
	Character(const Vec<float>& pos, Keyboard& kbd);
	void Draw(Graphics& gfx) override;
	void Draw(Graphics& gfx, Color sub) const;
	void SetDir(const Vec<float>& dir);
	bool GetSwing() const;
	void Update(float const dt) override;
	void Input(Keyboard::Event e);
	Rect<float> GetCollBox() const override;
	Rect<float> GetAttackBox(int atindex) const;
	Attack& GetAttack(int atindex) const;

	void OnHit(class Attack& attack) override
	{
		attack.Afflict(*this);
	}

private:
	void MakeAttack(int type = 0);
	void SetVel();

	Surface sprite;
	bool swingstate = false;
	float swingcool = 0.0f;
	std::vector<Animation> animation;
	Sequence curSeq = Sequence::StandingDown;
	Action curAct = Action::Move;
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

	enum class Action
	{
		Move,
		Aim,
		Stunned
	};

	Action GetState() const;

	void BounceX();
	void BounceY();
	void StateChange(const Action newstate);
	void BlobShot();

private:
	Action state = Action::Move;
	float aimTimer = 0.0f;

	Color col;
	float size;

	std::mt19937 rng;
	float atkTimer;
};

class SwordStrike : public Attack
{
public:
	SwordStrike(const Vec<float> pos0, const Character::Sequence dir0)
		:Attack(pos0)
	{
		switch (dir0)
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
};

class SwordStun : public Attack
{
public:
	SwordStun(const Vec<float> pos0, const Character::Sequence dir0)
		:Attack(pos0)
	{
		col = Colors::Green;

		switch (dir0)
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
};

class ArrowShot : public Attack
{
public:
	ArrowShot(const Vec<float> pos0, const Character::Sequence dir0)
		:Attack(pos0)
	{
		col = Color(200u, 70u, 0u);

		switch (dir0)
		{
		case Character::Sequence::StandingLeft:
		{
			hitBoxSize = { 10.0f, 5.0f };
			pos.X -= hitBoxSize.X;
			pos.Y -= hitBoxSize.Y / 2;
			dir = { -1, 0 };
			break;
		}
		case Character::Sequence::StandingRight:
		{
			hitBoxSize = { 10.0f, 5.0f };
			pos.Y -= hitBoxSize.Y / 2;
			dir = { 1, 0 };
			break;
		}
		case Character::Sequence::StandingUp:
		{
			hitBoxSize = { 5.0f, 10.0f };
			pos.X -= hitBoxSize.X / 2;
			pos.Y -= hitBoxSize.Y;
			dir = { 0, -1 };
			break;
		}
		case Character::Sequence::StandingDown:
		{
			hitBoxSize = { 5.0f, 10.0f };
			pos.X -= hitBoxSize.X/2;
			dir = { 0, 1 };
			break;
		}
		}
		vel = 120.0f;
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
private:
	Vec<float> dir;
};

class BlobShot : public Attack
{
public:
	BlobShot(const Vec<float> pos)
		:Attack(pos)
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
		}
	}

	void Afflict(Enemy& targ)
	{

	}

	void Update(float dt) override
	{
		pos += dir * vel * dt;
	}
private:
	float vel = 70.0f;
	Vec<float> dir;
};