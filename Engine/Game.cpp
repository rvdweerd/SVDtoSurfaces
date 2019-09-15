/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	surf("bitmaps\\link90x90.bmp"),
	willy(surf),
	bitmapText(gfx),
	soundHit(L"sounds\\hit.wav")
{	
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	float dt = ft.Mark();
	
	willy.SetDirection({ 0,0 });
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		willy.SetDirection({ 1,0 });
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		willy.SetDirection({ -1,0 });
	}
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		willy.SetDirection({ 0,-1 });
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		willy.SetDirection({ 0,1 });
	}
	/**if (wnd.kbd.KeyIsPressed(0x51))
	{
		willy.ActivateEffect();
		soundHit.Play();
	} */
	while (!wnd.kbd.KeyIsEmpty())
	{
		const Keyboard::Event e = wnd.kbd.ReadKey();
		if ( e.GetCode() == VK_SPACE )
		{
			if (e.IsRelease())
			{
				willy.SetSpeedFactor(1);
			}
			else if (e.IsPress())
			{
				willy.SetSpeedFactor(2);
			}
		}
		if (e.GetCode() == 0x51 && e.IsPress() )
		{
			willy.ActivateEffect();
			soundHit.Play();
		}
	}

	
	willy.Update(dt);
}

void Game::ComposeFrame()
{
	//bitmapText.DrawChar(100, 100, Colors::Red, 'A', BitmapText::Font::Consolas13x24 );
	bitmapText.DrawString(100, 130, Colors::White, "Fun Times", BitmapText::Font::Consolas13x24);
	//bitmapText.DrawString(wnd.mouse.GetPosX(),wnd.mouse.GetPosY(), Colors::Blue, "Weeeeee", BitmapText::Font::FixedSys16x28);
	gfx.DrawRectFilled({ {100,250},100,80 }, Colors::Blue);
	gfx.DrawRectFilled({ {240,250},100,80 }, Colors::Red);
	gfx.DrawRectFilled({ {380,250},100,80 }, Colors::Yellow);
	gfx.DrawRectFilled({ {520,250},100,80 }, Colors::Green);
	gfx.DrawRectFilled({ {660,250},100,80 }, Colors::LightGray);
	willy.Draw(gfx);

}


