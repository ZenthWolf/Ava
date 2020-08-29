#include "Input.h"

Input::Input(Character& ava, Keyboard& kbd)
	:Ava(ava), kbd(kbd)
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
				Ava.MakeAttack();
				break;
			}
			case 'Z':
			{
				Ava.MakeAttack(1);
				break;
			}
			case 'X':
			{
				Ava.MakeAttack(2);
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
