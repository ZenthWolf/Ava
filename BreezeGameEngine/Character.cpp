#include "Conflict.h"

Character::Character(const Vec<float>& pos, int hp, Keyboard& kbd)
	:Entity(pos, {0,0}, hp, Allegiance::Ava), sprite("Images//link90x90.bmp"), kbd(kbd)
{
	for (int i = 0; i < (int)Sequence::StandingLeft; i++)
	{
		animation.emplace_back(90, 90*i, 90, 90, 4, sprite, 0.16f);
	}

	for (int i = (int)Sequence::StandingLeft; i < (int)Sequence::Count; i++)
	{
		animation.emplace_back(0, 90 * (i-int(Sequence::StandingLeft)), 90, 90, 1, sprite, 0.16f);
	}
}

void Character::Draw(Graphics& gfx)
{
	if (!kbd.KeyIsPressed(VK_CONTROL))
	{
		if (vulnerable)
		{
			animation[(int)curSeq].Draw(Vec<int>(pos), gfx);
		}
		else
		{
			if (!flash)
			{
				animation[(int)curSeq].Draw(Vec<int>(pos), gfx);

				flash = !flash;
			}
			else
			{
				flash = !flash;
			}
		}
	}
	else
	{
		gfx.DrawRect(GetCollBox(), Colors::White);
	}
}

void Character::Draw(Graphics& gfx, Color sub) const
{
	animation[(int)curSeq].Draw(Vec<int>(pos), gfx, sub);
}

void Character::SetDir(const Vec<float>& dir)
{
	if (curAct == Action::Move)
	{
		if (dir.X > 0.0f)
		{
			curSeq = Sequence::WalkingRight;
		}
		else if (dir.X < 0.0f)
		{
			curSeq = Sequence::WalkingLeft;
		}
		else if (dir.Y > 0.0f)
		{
			curSeq = Sequence::WalkingDown;
		}
		else if (dir.Y < 0.0f)
		{
			curSeq = Sequence::WalkingUp;
		}
		else
		{
			if (curSeq == Sequence::WalkingRight)
			{
				curSeq = Sequence::StandingRight;
			}
			else if (curSeq == Sequence::WalkingLeft)
			{
				curSeq = Sequence::StandingLeft;
			}
			else if (curSeq == Sequence::WalkingDown)
			{
				curSeq = Sequence::StandingDown;
			}
			else if (curSeq == Sequence::WalkingUp)
			{
				curSeq = Sequence::StandingUp;
			}
		}
	}
}

Vec<float> Character::MakeAttack()
{
	if (curAct != Action::Attack)
	{
		Rect<float> edge = GetCollBox();
		Vec<float> pos0 = { 0.0f, 0.0f };

		if (curSeq == Sequence::StandingRight || curSeq == Sequence::WalkingRight)
		{
			curSeq = Sequence::StandingRight;
			pos0 = { edge.X1, (edge.Y0 + edge.Y1) / 2};
		}

		else if (curSeq == Sequence::StandingLeft || curSeq == Sequence::WalkingLeft)
		{
			curSeq = Sequence::StandingLeft;
			pos0 = { edge.X0, (edge.Y0 + edge.Y1) / 2 };
		}

		else if (curSeq == Sequence::StandingUp || curSeq == Sequence::WalkingUp)
		{
			curSeq = Sequence::StandingUp;
			pos0 = { (edge.X0 + edge.X1) / 2, edge.Y0 };
		}

		else if (curSeq == Sequence::StandingDown || curSeq == Sequence::WalkingDown)
		{
			curSeq = Sequence::StandingDown;
			pos0 = { (edge.X0 + edge.X1) / 2, edge.Y1 };
		}

		else
		{
			pos0 = { 10.0f, 10.0f };
		}

		return pos0;
	}
}

void Character::DVel(Vec<float> dv)
{
	vel += dv*speed;
}

void Character::AtkCooldown(float dt)
{
	atkCool = -dt;
}

void Character::Update(float const dt)
{
	VulnerableTimer(dt);

	switch (curAct)
	{
	
	case Action::Move:
	{
		SetDir(vel);
		pos += vel * dt;
		break;
	}

	case Action::Attack:
	{
		atkCool += dt;
		if (atkCool >= 0.0f)
		{
			ChangeAct(Action::Move);
		}
	}

	}

	animation[(int)curSeq].Update(dt);
}



Rect<float> Character::GetCollBox() const
{
	Vec<float> v0 = pos + Vec<float>(25.0f, 20.0f);
	Vec<float> v1 = pos + Vec<float>(65.0f, 70.0f);
	return Rect<float>( v0, v1 );
}

Character::Sequence Character::GetFacing() const
{
	return curSeq;
}

int Character::GetHealth() const
{
	return health;
}
