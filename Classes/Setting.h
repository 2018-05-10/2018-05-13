#pragma once
#include<cstdint>
#include<vector>
namespace Setting
{
	namespace Font
	{
		namespace Size
		{
			constexpr int name = 18;
			constexpr int chat = 24;
			constexpr int title = 60;
			constexpr int label = 40;
			constexpr int normal = 32;
			constexpr int light = 24;
			constexpr int result = 48;
		}
		namespace Type
		{
			constexpr char title[] = "fonts/Quicksand-Bold.ttf";
			constexpr char base[] = "fonts/OpenSans-Regular.ttf";
		};
	}
	namespace Map
	{
		constexpr char path[] = "Map/";
		static std::vector<const char *> list{
			"map1"
		};
		namespace TileSize
		{
			constexpr int height = 32;
			constexpr int width = 64;
		}
	}
	
}