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
	surf("bitmaps\\link90x90.bmp"),
	bitmapText(gfx),
	mf1(new MemeDwarf("Willy","bitmaps\\link90x90.bmp", CharacterLoads::Dwarf::Willy(), {10,100} , bitmapText)),
	mf2(new MemeHuman("Laura","bitmaps\\laura.bmp", CharacterLoads::Human::Laura(), {10,200}, bitmapText)),
	mf3(new MemeHuman("Umisan","bitmaps\\umisan.bmp", CharacterLoads::Human::Umisan(), {10,400}, bitmapText)),
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
		if (wnd.kbd.KeyIsPressed(0x4C)) mf3->character->SetDirection({ 1,0 });
		if (wnd.kbd.KeyIsPressed(0x4A)) mf3->character->SetDirection({ -1,0 });
		if (wnd.kbd.KeyIsPressed(0x49)) mf3->character->SetDirection({ 0,-1 });
		if (wnd.kbd.KeyIsPressed(0x4B)) mf3->character->SetDirection({ 0,1 });
	}

	//SPECIAL EFFECTS
	//if (wnd.kbd.KeyIsPressed(0x51))
	//{
	//	willy.ActivateEffect();
	//	soundHit.Play();
	//} 
	/*
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
	*/
	//STATUS UPDATING
	mf1->character->Update(dt);
	mf2->character->Update(dt);
	mf3->character->Update(dt);
	
	/*if (wnd.kbd.KeyIsPressed(VK_HOME))
	{
		surf.Scale(1.002f);
	}
	if (wnd.kbd.KeyIsPressed(VK_END))
	{
		surf.Scale(0.998f);
		//mf1->character->
	}*/
	while (!wnd.kbd.KeyIsEmpty())
	{
		const Keyboard::Event e = wnd.kbd.ReadKey();
		if (e.GetCode() == VK_HOME && e.IsPress())
		{
			mf3->character->Scale(2.0f);
			//surf.Scale(2.0f);
		}
		if (e.GetCode() == VK_END && e.IsPress())
		{
			mf3->character->Scale(0.5f); 
			//surf.Scale(0.5f);
		}
		if (e.GetCode() == VK_SPACE)
		{
			mf1->character->TakeDamage(10);
			if (e.IsRelease())
			{
				mf1->character->SetSpeedFactor(1);
			}
			else if (e.IsPress())
			{
				mf1->character->SetSpeedFactor(2);
			}
		}
		if (e.GetCode() == 0x51 && e.IsPress())
		{
			mf1->character->ActivateHit();
			mf1->character->TakeDamage(10);
			soundHit.Play();
		}
	}
}

Vei2 Intersection(Vei2 p1, Vei2 p2, Vei2 p3, Vei2 p4)
{
	//bring to base
	//Vei2 p1_orig = p1;
	p2 -= p1;
	p3 -= p1;
	p4 -= p1;
	//p1 -= p1;


	float y0 = float(-p4.x * p3.y + p3.x * p4.y) / float(p3.x - p4.x);
	float alpha = float(p3.y - p4.y) / float(p3.x - p4.x);
	float x_ = float(y0 * p2.x) / float(p2.y - alpha * p2.x);
	float y_ = float(y0 * p2.y) / float(p2.y - alpha * p2.x);



	return ( Vei2{ int(x_) , int(y_) } + p1 );
}

void Game::ComposeFrame()
{
	//bitmapText.DrawString(100, 130, Colors::White, "Fun Times (small font)", BitmapText::Font::FixedSys8x14);
	//bitmapText.DrawString(100, 100, Colors::White, "Fun Times (large font)", BitmapText::Font::FixedSys16x28);

	//bitmapText.DrawString(wnd.mouse.GetPosX(),wnd.mouse.GetPosY(), Colors::Blue, "Weeeeee", BitmapText::Font::FixedSys16x28);
	//gfx.DrawRectFilled({ {200,250},50,125 }, Colors::Blue);
	//gfx.DrawRectFilled({ {300,250},50,125 }, Colors::Red);
	//gfx.DrawRectFilled({ {400,250},50,125 }, Colors::Yellow);
	//gfx.DrawRectFilled({ {500,250},50,125 }, Colors::Green);
	//gfx.DrawRectFilled({ {600,250},50,125 }, Colors::LightGray);
	//mf1->character->Draw(gfx);
	//mf2->character->Draw(gfx);
	//mf3->character->Draw(gfx);
	//attributes.Draw(gfx);
	//attributes.TakeDamage(1);
	//gfx.DrawLine(p1, Vei2(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()), Colors::Magenta);
	//gfx.DrawSprite(10, 10, surf, SpriteEffect::Copy());

	/*
	auto p1 = mf1->character->GetPersonalSpace().GetCenter();
	auto p2 = mf2->character->GetPersonalSpace().GetCenter();
	auto p3 = mf3->character->GetPersonalSpace().GetCenter();
	PixelStep::Pair pair1(p1, p2);
	PixelStep::Pair pair2(p1, p3);
	PixelStep::Pair pair3(p2, p3);
	gfx.DrawLine(pair1, Colors::Red);
	gfx.DrawLine(pair2, Colors::Red);
	gfx.DrawLine(pair3, Colors::Red);
	Vei2 middle1 = pair1.MidPoint();
	Vei2 middle2 = pair2.MidPoint();
	Vei2 middle3 = pair3.MidPoint();
	bitmapText.DrawString(middle1.x, middle1.y, Colors::Magenta, std::to_string(pair1.GetDistance()), BitmapText::Font::FixedSys8x14);
	bitmapText.DrawString(middle2.x, middle2.y, Colors::Magenta, std::to_string(pair2.GetDistance()), BitmapText::Font::FixedSys8x14);
	bitmapText.DrawString(middle3.x, middle3.y, Colors::Magenta, std::to_string(pair3.GetDistance()), BitmapText::Font::FixedSys8x14);
	*/
	Vei2 p1(10, 20);
	Vei2 p2(wnd.mouse.GetPosX(), wnd.mouse.GetPosY());
	Vei2 p3(30, 80);
	Vei2 p4(140, 10);
	PixelStep::Pair pair1(p1, p2);
	PixelStep::Pair pair2(p3, p4);
	gfx.DrawLine(pair1, Colors::Red);
	gfx.DrawLine(pair2, Colors::Red);
	Vei2 q = Intersection(p1, p2, p3, p4);
	gfx.DrawLine(p1, q, Colors::White);
	gfx.DrawLine(p3, q, Colors::White);
}


