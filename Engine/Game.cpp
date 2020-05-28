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
	surf_orig("bitmaps\\Dog_BMP_32_Bit_small.bmp"),
	//surf("bitmaps\\jump24_small.bmp"),
	//surf("bitmaps\\link90x90.bmp"),
    surfmat(surf,surf_orig),
	bitmapText(gfx)
	/*mf1(std::make_unique<MemeFighter>(MemeDwarf("Willy","bitmaps\\link90x90.bmp", CharacterLoads::Dwarf::Willy(), {10,100} , bitmapText))),
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
	gfx.DrawSprite(0, 600, surf_orig, SpriteEffect::Copy());
	
	std::string str1 = "Rank of composite matrix: ";
	str1.append(std::to_string(surfmat.curres));
	
	std::string str2 = "U (" + std::to_string(surfmat.UrowSize) + "," + std::to_string(surfmat.UcolSize) + "), ";
	str2 = str2 + "V (" + std::to_string(surfmat.VrowSize) + "," + std::to_string(surfmat.VcolSize) + ")";

	std::string str3 = "Each rank increase costs (" + std::to_string(surfmat.UcolSize) + " x " + std::to_string(surfmat.UcolSize) + ") pixels x 4 bytes / pixel = 5.4 kB";
	
	float memsize = surfmat.curres * (surfmat.UcolSize + surfmat.VrowSize) * 4 / 1000; // kB
	std::string str4 = "Compressed image size: " + std::to_string((int)memsize) + " kB" ;

	int rate = int((1.0f - memsize / 1805.328f) * 100.0f);
	std::string str5 = "Compression rate: " + std::to_string(rate) + "%";

	int i = 18;
	bitmapText.DrawString(10, 10, Colors::White, str1, BitmapText::Font::FixedSys8x14);
	bitmapText.DrawString(10, 10 + 1 * i, Colors::White, str2, BitmapText::Font::FixedSys8x14);
	bitmapText.DrawString(10, 10 + 2 * i, Colors::White, str3, BitmapText::Font::FixedSys8x14);
	bitmapText.DrawString(10, 10 + 3 * i, Colors::White, str4, BitmapText::Font::FixedSys8x14);
	bitmapText.DrawString(10, 10 + 4 * i, Colors::White, str5, BitmapText::Font::FixedSys8x14);

	std::string str6 = "Original file size: " + std::to_string(1805) + "kB";
	bitmapText.DrawString(10, 610, Colors::White, str6, BitmapText::Font::FixedSys8x14);
}


