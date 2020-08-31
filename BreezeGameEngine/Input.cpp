#include "Input.h"

Input::Input(Character& ava, std::vector<std::unique_ptr<class Attack>>& atk, 
			 Keyboard& kbd)
	:Ava(ava), attack(atk), kbd(kbd)
{
}

bool Input::HasInput() const
{
	return !kbd.KeyIsEmpty();
}

void Input::ReadInput()
{
	while (!kbd.KeyIsEmpty())
	{
		const Keyboard::Event e = kbd.ReadKey();

		if (e.IsPress())
		{
			switch (e.GetCode())
			{
			case ' ':
			{
				if (Ava.GetAction() != Character::Action::Attack)
				{
					attack.push_back(
						std::make_unique<SwordStrike>(Ava.MakeAttack(), Ava.GetFacing())
					);
				}
				break;
			}
			
			case 'Z':
			{
				if (Ava.GetAction() != Character::Action::Attack)
				{
					attack.push_back(
						std::make_unique<SwordStun>(Ava.MakeAttack(), Ava.GetFacing())
					);
				}
				break;
			}
			case 'X':
			{
				if (Ava.GetAction() != Character::Action::Attack)
				{
					attack.push_back(
						std::make_unique<ArrowShot>(Ava.MakeAttack(), Ava.GetFacing())
					);
				}
				break;
			}
			
			case VK_LEFT:
			{
				Ava.DVel({ -1.0f, 0.0f });
				break;
			}
			case VK_UP:
			{
				Ava.DVel({ 0.0f, -1.0f });
				break;
			}
			case VK_RIGHT:
			{
				Ava.DVel({ 1.0f, 0.0f });
				break;
			}
			case VK_DOWN:
			{
				Ava.DVel({ 0.0f, 1.0f });
				break;
			}
			}
		}
		else if (e.IsRelease())
		{
			switch (e.GetCode())
			{
			case VK_LEFT:
			{
				Ava.DVel({ 1.0f, 0.0f });
				break;
			}
			case VK_UP:
			{
				Ava.DVel({ 0.0f, 1.0f });
				break;
			}
			case VK_RIGHT:
			{
				Ava.DVel({ -1.0f, 0.0f });
				break;
			}
			case VK_DOWN:
			{
				Ava.DVel({ 0.0f, -1.0f });
				break;
			}
			}
		}
	}
}
