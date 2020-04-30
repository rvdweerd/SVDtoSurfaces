/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Graphics.h																			  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
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
#pragma once
#include "ChiliWin.h"
#include <d3d11.h>
#include <wrl.h>
#include "ChiliException.h"
#include "Colors.h"
#include "Surface.h"
#include "Rect.h"
//#include <assert.h>
#include <cassert>
#include <algorithm>
#include <cmath>

namespace PixelStep
{
	struct Pair
	{
		Pair(Vei2 a, Vei2 b)
			:
			activePos(a),
			targetPos(b)
		{
		}
		float GetDistance() const
		{
			return sqrt((activePos.x - targetPos.x)* (activePos.x - targetPos.x) + (activePos.y - targetPos.y)* (activePos.y - targetPos.y));
		}
		Vei2 MidPoint() const
		{
			return { int((activePos.x + targetPos.x) / 2) , int((activePos.y + targetPos.y) / 2) };
		}
		Vei2 TakeStep()
		{
			float phi = 0.0f;
			if (std::abs(targetPos.x - activePos.x) < 0.001f)
			{
				if ((targetPos.y - activePos.y) > 0)
				{
					phi = 3.14159f / 2;
				}
				else
				{
					phi = 3 / 2 * 3.14159f;
				}
			}
			else if ((targetPos.x - activePos.x) < 0)
			{
				phi = atan((targetPos.y - activePos.y) / (targetPos.x - activePos.x)) + 3.14159f;
			}
			else
			{
				phi = atan((targetPos.y - activePos.y) / (targetPos.x - activePos.x));
			}
			activePos.x += cos(phi);
			activePos.y += sin(phi);
			return { int(activePos.x), int(activePos.y) };
		}
		Vec2 activePos;
		Vec2 targetPos;
		
	};
}

class Graphics
{
public:
	class Exception : public ChiliException
	{
	public:
		Exception( HRESULT hr,const std::wstring& note,const wchar_t* file,unsigned int line );
		std::wstring GetErrorName() const;
		std::wstring GetErrorDescription() const;
		virtual std::wstring GetFullMessage() const override;
		virtual std::wstring GetExceptionType() const override;
	private:
		HRESULT hr;
	};
private:
	// vertex format for the framebuffer fullscreen textured quad
	struct FSQVertex
	{
		float x,y,z;		// position
		float u,v;			// texcoords
	};
public:
	Graphics( class HWNDKey& key );
	Graphics( const Graphics& ) = delete;
	Graphics& operator=( const Graphics& ) = delete;
	void EndFrame();
	void BeginFrame();
	void PutPixel( int x,int y,int r,int g,int b )
	{
		PutPixel( x,y,{ unsigned char( r ),unsigned char( g ),unsigned char( b ) } );
	}
	void PutPixel( int x,int y,Color c );
	const Color GetPixel(const int x, const int y) const;
	template<typename E>
	void DrawSprite(int x, int y, const Surface& s, E effect)
	{
		DrawSprite(x, y, s.GetRect(), s, effect);
	}
	template<typename E>
	void DrawSprite(int x, int y, const RectI& srcRect, const Surface& s, E effect)
	{
		DrawSprite(x, y, srcRect, GetScreenRect(), s, effect);
	}
	template<typename E>
	void DrawSprite(int x, int y, RectI srcRect, const RectI& clip, const Surface& s, E effect)
	{
		assert(clip.left >= 0);
		assert(clip.right <= ScreenWidth);
		assert(clip.top >= 0);
		assert(clip.bottom <= ScreenHeight);
		assert(srcRect.left >= 0);
		assert(srcRect.right <= s.GetWidth());
		assert(srcRect.top >= 0);
		assert(srcRect.bottom <= s.GetHeight());
		if (x < clip.left)
		{
			srcRect.left += clip.left - x;
			x = clip.left;
		}
		if (y < clip.top)
		{
			srcRect.top += clip.top - y;
			y = clip.top;
		}
		if (x + srcRect.GetWidth() > clip.right)
		{
			srcRect.right -= x + srcRect.GetWidth() - clip.right;
		}
		if (y + srcRect.GetHeight() > clip.bottom)
		{
			srcRect.bottom -= y + srcRect.GetHeight() - clip.bottom;
		}
		for (int sx = srcRect.left; sx < srcRect.right; sx++)
		{
			for (int sy = srcRect.top; sy < srcRect.bottom; sy++)
			{
				//PutPixel(x + sx - srcRect.left, y + sy - srcRect.top, s.GetPixel(sx, sy));
				effect(
					x + sx - srcRect.left, 
					y + sy - srcRect.top, 
					s.GetPixel(sx, sy), 
					*this
				);
			}
		}
	}
	void DrawLine(PixelStep::Pair pair, Color c)
	{
		//PixelStep::Pair pair(p1, p2);
		Vec2 p2 = pair.targetPos;
		Vei2 p;
		do
		{
			p = pair.TakeStep();
			PutPixel(p.x, p.y, c);
		} while ((p.x != int(p2.x)) && (p.y != int(p2.y)));
	}
	void DrawLine(Vei2 p1, Vei2 p2, Color c)
	{
		PixelStep::Pair pair(p1, p2);
		Vei2 p;
		do
		{
			p = pair.TakeStep();
			PutPixel(p.x, p.y, c);
		} while ((p.x != int(p2.x)) && (p.y != int(p2.y)));
	}
	void DrawLine(std::vector<Vei2> polygon, Color c)
	{
		polygon.emplace_back(polygon[0]);
		size_t n = polygon.size(); 
		for (size_t i = 0; i < n-size_t(1); i++)
		{
			DrawLine(polygon[i], polygon[i+size_t(1)], c);
		}
	}

	void DrawRect(RectI rect, RectI clip, Color c);
	void DrawRect(RectI rect, Color c);
	void DrawRectFilled(RectI rect, Color c);
	~Graphics();
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain>				pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>				pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			pImmediateContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				pSysBufferTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	pSysBufferTextureView;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>			pSamplerState;
	D3D11_MAPPED_SUBRESOURCE							mappedSysBufferTexture;
	Color*                                              pSysBuffer = nullptr;
public:
	static constexpr int ScreenWidth = 1800;
	static constexpr int ScreenHeight = 1600;
	static RectI GetScreenRect();
	
	
	
	
};