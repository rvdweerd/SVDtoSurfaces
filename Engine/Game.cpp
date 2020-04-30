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
	//surf("bitmaps\\dib32.bmp"),
	surf("bitmaps\\Dog_BMP_32_Bit_small.bmp"),
	//surf("bitmaps\\link90x90.bmp"),
    surfmat(surf)
	/*bitmapText(gfx),
	mf1(std::make_unique<MemeFighter>(MemeDwarf("Willy","bitmaps\\link90x90.bmp", CharacterLoads::Dwarf::Willy(), {10,100} , bitmapText))),
	mf2(std::make_unique<MemeFighter>(MemeHuman("Laura","bitmaps\\laura.bmp", CharacterLoads::Human::Laura(), {10,200}, bitmapText))),
	mf3(std::make_unique<MemeFighter>(MemeHuman("Umisan","bitmaps\\umisan.bmp", CharacterLoads::Human::Umisan(), {10,400}, bitmapText))),
	soundHit(L"sounds\\hit.wav")*/
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

	while (!wnd.kbd.KeyIsEmpty())
	{
		// get an event from the queue
		const Keyboard::Event e = wnd.kbd.ReadKey();
		// check if it is a release event
		if (e.IsRelease())
		{
			// check if the event was for the space key
			if (e.GetCode() == 'Q')
			{
				surfmat.IncreaseResolution(surf);
			}
		}
	}
}


void Game::ComposeFrame()
{
	
	gfx.DrawSprite(0, 0, surf, SpriteEffect::Copy());
	

}


