#include "Conflict.h"

Attack::Attack(const Vec<float> pos, Entity& source, const Color col)
	:pos(pos), src(source), col(col)
{
	hitBoxSize = Vec<float>(0.0f, 0.0f);
}

void Attack::Update(float dt)
{
}

void Attack::Draw(Graphics& gfx) const
{
	gfx.DrawRect(GetCollBox(), col);
}

Rect<float> Attack::GetCollBox() const
{
	return Rect<float>(pos, pos + hitBoxSize);
}

Entity::Allegiance Attack::GetAllegiance() const
{
	return src.GetAllegiance();
}

bool Attack::Cull()
{
	return cull;
}
