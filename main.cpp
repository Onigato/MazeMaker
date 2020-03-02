#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include<vector>
#include<ctime>
// Override base class with your custom functionality


class mazeMaker : public olc::PixelGameEngine
{
public: 
	struct gridPoint
	{
	public: 
		gridPoint(olc::vi2d inPos)
		{
			pos = inPos;
		}
		olc::vi2d pos;
		std::vector<bool> vecOpen = { true, false, false, false };
		void DrawGrid(mazeMaker *master)
		{
			if (!vecOpen[0])
				master->DrawLine(pos.x, pos.y, pos.x + 4, pos.y, olc::WHITE);
			if (!vecOpen[1])
				master->DrawLine(pos.x + 4, pos.y, pos.x + 4, pos.y + 4, olc::WHITE);
			if (!vecOpen[2])
				master->DrawLine(pos.x, pos.y + 4, pos.x + 4, pos.y + 4, olc::WHITE);
			if (!vecOpen[3])
				master->DrawLine(pos.x, pos.y, pos.x, pos.y + 4, olc::WHITE);
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
	};

	void reset()
	{
		delete mainMaze;
		mainMaze = new maze(ScreenWidth(), ScreenHeight());
		srand(std::time(NULL));
		currentPos.x = 0;
		currentPos.y = 0;
		prevPos = currentPos;
	}
	
	void makeConnection()
	{
		prevPos.x = currentPos.x;
		prevPos.y = currentPos.y;
		randDir = rand() % 4;
		std::cout << "rand is: " << randDir << std::endl;
		switch (randDir)
		{
		case 0:
			currentPos.y -= 4;
			break;
		case 1:
			currentPos.x += 4;
			break;
		case 2:
			currentPos.y += 4;
			break;
		case 3:
			currentPos.x -= 4;
			break;
		}
		if (currentPos.x < 0 || currentPos.y < 0  || currentPos.x > ScreenWidth() || currentPos.y > ScreenHeight())
		{
			currentPos.x = prevPos.x;
			currentPos.y = prevPos.y;
		}
	}
public:
	mazeMaker()
	{
		sAppName = "mazeMaker";
	}
public:
	maze* mainMaze = nullptr;
	float countTime = 0.0;
	float cycleTime = 0.5;//2 actions per second-ish
	olc::vi2d currentPos;
	olc::vi2d prevPos;
	int randDir;



	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		if (ScreenHeight() % 4 != 1 || ScreenWidth() % 4 != 1)
			return false;
		else reset();
		return true;
	}
	bool OnUserUpdate(float fElapsedTime) override
	{
		if (countTime > cycleTime)
		{
			makeConnection();
			countTime -= cycleTime;

			std::cout << "currentPos: " << currentPos.x << ", " << currentPos.y << std::endl;
		}

		Clear(olc::BLACK);
		for (auto& a : mainMaze->grid)
			a->DrawGrid(this);
		DrawRect(0, 0, ScreenWidth()-1, ScreenHeight()-1, olc::DARK_BLUE);
		FillRect(currentPos.x, currentPos.y, currentPos.x + 4, currentPos.y + 4, olc::DARK_RED);
		countTime += fElapsedTime;
		return true;
	}
};
int main()
{
	int numSquares = 10;
	mazeMaker demo;
	if (demo.Construct((numSquares * 4) + 1, (numSquares * 4) + 1, 4, 4))
		demo.Start();
	return 0;
}