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
#include "CharacterLoads.h"
#include "MemeFighter.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	bitmapText(gfx),
	mf1(new MemeDwarf("Willy","bitmaps\\link90x90.bmp", CharacterLoads::Dwarf::Willy(), {10,100} , bitmapText)),
	mf2(new MemeHuman("Laura","bitmaps\\laura.bmp", CharacterLoads::Human::Laura(), {10,200}, bitmapText)),
	mf3(new MemeHuman("Umisan","bitmaps\\umisan.bmp", CharacterLoads::Human::Umisan(), {10,400}, bitmapText)),
	//attributes(100,bitmapText),
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
	//MOVE CONTROL
	float dt = ft.Mark();
	mf1->character->SetDirection(Vec2{ 0,0 });
	{
		if (wnd.kbd.KeyIsPressed(0x44)) mf1->character->SetDirection({ 1,0 });
		if (wnd.kbd.KeyIsPressed(0x41)) mf1->character->SetDirection({ -1,0 });
		if (wnd.kbd.KeyIsPressed(0x57)) mf1->character->SetDirection({ 0,-1 });
		if (wnd.kbd.KeyIsPressed(0x53)) mf1->character->SetDirection({ 0,1 });
	}
	mf2->character->SetDirection(Vec2{ 0,0 });
	{
		if (wnd.kbd.KeyIsPressed(VK_RIGHT)) mf2->character->SetDirection({ 1,0 });
		if (wnd.kbd.KeyIsPressed(VK_LEFT )) mf2->character->SetDirection({ -1,0 });
		if (wnd.kbd.KeyIsPressed(VK_UP   )) mf2->character->SetDirection({ 0,-1 });
		if (wnd.kbd.KeyIsPressed(VK_DOWN )) mf2->character->SetDirection({ 0,1 });
	}
	mf3->character->SetDirection(Vec2{ 0,0 });
	{
		if (wnd.kbd.KeyIsPressed(0x44)) mf3->character->SetDirection({ 1,0 });
		if (wnd.kbd.KeyIsPressed(0x41)) mf3->character->SetDirection({ -1,0 });
		if (wnd.kbd.KeyIsPressed(0x57)) mf3->character->SetDirection({ 0,-1 });
		if (wnd.kbd.KeyIsPressed(0x53)) mf3->character->SetDirection({ 0,1 });
	}

	//SPECIAL EFFECTS
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
			mf1->character->TakeDamage(1);
			if (e.IsRelease())
			{
				mf1->character->SetSpeedFactor(1);
			}
			else if (e.IsPress())
			{
				mf1->character->SetSpeedFactor(2);
			}
		}
		if (e.GetCode() == 0x51 && e.IsPress() )
		{
			mf1->character->ActivateHit();
			mf1->character->TakeDamage(10);
			soundHit.Play();
		}
	}

	//STATUS UPDATING
	mf1->character->Update(dt);
	mf2->character->Update(dt);
	mf3->character->Update(dt);
}

void Game::ComposeFrame()
{
	bitmapText.DrawString(100, 130, Colors::White, "Fun Times", BitmapText::Font::Consolas13x24);
	//bitmapText.DrawString(wnd.mouse.GetPosX(),wnd.mouse.GetPosY(), Colors::Blue, "Weeeeee", BitmapText::Font::FixedSys16x28);
	gfx.DrawRectFilled({ {200,250},50,125 }, Colors::Blue);
	gfx.DrawRectFilled({ {300,250},50,125 }, Colors::Red);
	gfx.DrawRectFilled({ {400,250},50,125 }, Colors::Yellow);
	gfx.DrawRectFilled({ {500,250},50,125 }, Colors::Green);
	gfx.DrawRectFilled({ {600,250},50,125 }, Colors::LightGray);
	mf1->character->Draw(gfx);
	mf2->character->Draw(gfx);
	mf3->character->Draw(gfx);
	//attributes.Draw(gfx);
	//attributes.TakeDamage(1);

}


