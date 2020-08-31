#include "Conflict.h"

Enemy::Enemy(const Vec<float> pos, const Vec<float> vel)
	:Entity(pos, vel, 3, Allegiance::Enemy), col(Colors::Cyan), size(15),
	rng(std::random_device()())
{
	fixpos(float(size));
	collBoxSize = { size*2 -1 , size*2 -1 };
	size -= 1;

	std::uniform_real_distribution<float> timer(4.0f, 7.0f);
	atkTimer = -timer(rng);
}

void Enemy::fixpos(float dr)
{
	pos = pos - Vec<float>(dr, dr);
}

void Enemy::Update(const float dt)
{
	VulnerableTimer(dt);

	for (int i = 0; i < attack.size(); i++)
	{
		attack[i]->Update(dt);
	}
}

void Enemy::Draw(Graphics& gfx)
{
	if (vulnerable)
	{
		gfx.DrawCirc(pos + Vec<float>(float(size), float(size)), size + 1, col);
	}
	else
	{
		if (!flash)
		{
			gfx.DrawCirc(pos + Vec<float>(float(size), float(size)), size + 1, col);
		}
		else
		{
			gfx.DrawCirc(pos + Vec<float>(float(size), float(size)), size + 1, Colors::Red);
		}

		flash = !flash;
	}
	for (int i = 3; i < 9; i++)
	{
		gfx.PutPixel(pos.X + i + size, pos.Y + size - i + 1, Colors::Black);
		gfx.PutPixel(pos.X - i + size, pos.Y + size - i + 1, Colors::Black);
	}

	for (int i = 0; i < attack.size(); i++)
	{
		attack[i]->Draw(gfx);
	}
}

void Enemy::PushBox(Rect<float> wall)
{
	float Deviance[4] = { 0.0f }; //0-4 Left, Up, Right, Down
	float MinDev = 0.0f;

	Rect<float> entcoll = GetCollBox();

	float UpDeviance = entcoll.Y1 - wall.Y0;
	if (UpDeviance > 0.0f)
	{
		MinDev = UpDeviance;
	}
	float LeftDeviance = entcoll.X1 - wall.X0;
	if (LeftDeviance > 0.0f)
	{
		if (MinDev == 0.0f || LeftDeviance < MinDev)
		{
			MinDev = LeftDeviance;
		}
	}
	float DownDeviance = wall.Y1 - entcoll.Y0;
	if (DownDeviance > 0.0f)
	{
		if (MinDev == 0.0f || DownDeviance < MinDev)
		{
			MinDev = DownDeviance;
		}
	}
	float RightDeviance = wall.X1 - entcoll.X0;
	if (RightDeviance > 0.0f)
	{
		if (MinDev == 0.0f || RightDeviance < MinDev)
		{
			MinDev = RightDeviance;
		}
	}

	if (MinDev == UpDeviance)
	{
		pos.Y = round(pos.Y - UpDeviance);
		BounceY();
		BounceX();
	}
	else if (MinDev == LeftDeviance)
	{
		pos.X = round(pos.X - LeftDeviance);
		BounceX();
		BounceY();
	}
	else if (MinDev == DownDeviance)
	{
		pos.Y = round(pos.Y + DownDeviance);
		BounceY();
		BounceX();
	}
	else if (MinDev == RightDeviance)
	{
		pos.X = round(pos.X + RightDeviance);
		BounceX();
		BounceY();
	}
	else
	{
		//There probably should be an error or something here...
	}
}

Enemy::Action Enemy::GetState() const
{
	return state;
}

void Enemy::StateChange(const Action newstate)
{
	state = newstate;
}

void Enemy::BounceX()
{
	vel.X = -vel.X;
}

void Enemy::BounceY()
{
	vel.Y = -vel.Y;
}

BlobShot Enemy::BlobShot()
{
	return class BlobShot(pos);
}
