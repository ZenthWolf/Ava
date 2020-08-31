#include "Conflict.h"

Character::Character(const Vec<float>& pos, Keyboard& kbd)
	:Entity(pos, Allegiance::Ava), sprite("Images//link90x90.bmp"), kbd(kbd)
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
		animation[(int)curSeq].Draw(Vec<int>(pos), gfx);

		for (int i = 0; i < attack.size(); i++)
		{
			attack[i]->Draw(gfx);
		}
	}
	else
	{
		gfx.DrawRect(GetCollBox(), Colors::White);
		for (int i = 0; i < attack.size(); i++)
		{
			attack[i]->Draw(gfx);
		}
	}
}

void Character::Draw(Graphics& gfx, Color sub) const
{
	animation[(int)curSeq].Draw(Vec<int>(pos), gfx, sub);

	for (int i = 0; i < attack.size(); i++)
	{
		attack[i]->Draw(gfx);
	}
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
		swingstate = true;
		curAct = Action::Attack;

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

		swingcool = 0.0f;
	}
}

void Character::DVel(Vec<float> dv)
{
	vel += dv*speed;
}

void Character::Update(float const dt)
{
	if (curAct == Action::Move)
	{
		SetDir(vel);
		pos += vel * dt;
	}

	for (int i = 0; i < attack.size(); i++)
	{
		attack[i]->Update(dt);
	}

	if (swingstate)
	{
		swingcool += dt;
		if (swingcool >= 0.25f)
		{
			swingstate = false;
			curAct = Action::Move;
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

Character::Action Character::GetAction() const
{
	return curAct;
}

Character::Sequence Character::GetFacing() const
{
	return curSeq;
}

Rect<float> Character::GetAttackBox(int atindex) const
{
	if (atindex < attack.size())
	{
		return attack[atindex]->GetCollBox();
	}
	else
	{
		return Rect<float>(0.0f, 0.0f, 0.0f, 0.0f);
	}
}

Attack& Character::GetAttack(int atindex) const
{
	return *attack[atindex];
}
