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
	bitmapText(gfx)
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
	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		willy.SetSpeedFactor(2);
	} 
	else
	{
		willy.SetSpeedFactor(1);
	}
	willy.Update(dt);
}

void Game::ComposeFrame()
{
	willy.Draw(gfx);
	bitmapText.DrawChar(100, 100, Colors::Red, 'A', BitmapText::Font::Consolas13x24 );
	bitmapText.DrawString(100, 130, Colors::White, "Rogier is briljant!! ;-) Consolas", BitmapText::Font::Consolas13x24);
	bitmapText.DrawString(wnd.mouse.GetPosX(),wnd.mouse.GetPosY(), Colors::Blue, "Rogier is briljant!! ;-) FixedSys", BitmapText::Font::FixedSys16x28);
}


