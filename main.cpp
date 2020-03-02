#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include<vector>
// Override base class with your custom functionality


class mazeMaker : public olc::PixelGameEngine
{
	struct gridPoint
	{
	public: 
		gridPoint(olc::vi2d inPos)
		{
			pos = inPos;
		}
		olc::vi2d pos;
		std::vector<bool> vecOpen = { false, false, false, false };
		void DrawGrid()
		{
			if (vecOpen[0])
				DrawLine(pos.x, pos.y, pos.x + 4, pos.y, olc::WHITE);

		}
	};
	struct maze
	{
		maze(int32_t width, int32_t height)
		{
			olc::vi2d temp;
			gridPoint* holder;
			//code to initialize
			for (int x = 0; x < width; x += 4)
			{
				for (int y = 0; y < height; y += 4)
				{
					temp.x = x;
					temp.y = y;
					holder = new gridPoint(temp);
					grid.push_back(holder);
				}
			}
			
		}

		std::vector<gridPoint*> grid;
		/*
		void drawGrid()
		{
			for (auto& a : grid)
			{
				if (a->vecOpen[0])
					DrawLine(a->pos.x, a->pos.y, (a->pos.x + 4), a->pos.y, olc::WHITE);
			}
		}
		*/
	};
	void reset()
	{

	}
public:
	mazeMaker()
	{
		sAppName = "mazeMaker";
	}
public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		if (ScreenHeight() % 4 != 0 || ScreenWidth() % 4 != 0)
			return false;
		else reset();
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		
		return true;
	}
};
int main()
{
	mazeMaker demo;
	if (demo.Construct(64, 64, 1, 1))
		demo.Start();
	return 0;
}