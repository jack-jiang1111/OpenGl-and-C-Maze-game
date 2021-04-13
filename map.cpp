#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
float way3_2 = 0.5;
float way3_1 = 0.6;
float way3_0 = 0.33;

float way2_1 = 0.5;
float way2_0 = 0.5;

float way1_0 = 0.75;
float half = 0.5;
int width;
int height;
float rand01() {
	return rand() / (float)RAND_MAX;
}
class block
{
public:
	int x;
	int y;
	string type;
	block(int x, int y, string type)
	{
		this->x = x;
		this->y = y;
		this->type = type;
	}
};
std::vector<block> blocks;
std::vector<block> allzeors;
bool spawn_walls(int x, int y)
{
	for (int i = 0; i < allzeors.size(); i++)
	{
		if (allzeors[i].x == x && allzeors[i].y == y)
		{
			return false;
		}
	}
	return true;
}
void spawn_keys(int x, int y)
{

}
void generate_map(int width, int height, int keys)
{
	
	char map[width][height];
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			map[i][j] = '0';
			
		}
	}
	int startx = rand() % width;
	int starty = rand() % height;
	cout << startx << " " << starty << endl;
	map[startx][starty] = 'S';
	block init1(startx, starty+1, "up");
	block init2(startx, starty-1, "down");
	block init3(startx-1, starty, "left");
	block init4(startx+1, starty, "right");

	blocks.push_back(init1);
	blocks.push_back(init2);
	blocks.push_back(init3);
	blocks.push_back(init4);
	block init(startx, starty, "center");
	allzeors.push_back(init);
	allzeors.push_back(init1);
	allzeors.push_back(init2);
	allzeors.push_back(init3);
	allzeors.push_back(init4);

	while (blocks.size() > 1)
	{
		//cout << blocks.size();
		if (map[blocks[0].x][blocks[0].y] == 'W'|| map[blocks[0].x][blocks[0].y] == 'S') // this was cause by first way's sub way piror than second way, so that sub way occupy second way as wall 
		{
			
			blocks.erase(blocks.begin()); // erase first element
			continue;
		}

		int x = blocks[0].x;
		int y = blocks[0].y;
		if (blocks[0].type == "up")
		{
			//cout << blocks.size();
			int x1 = blocks[0].x;
			int y1 = blocks[0].y+1;
			bool block1 = false;

			int x2 = blocks[0].x - 1;
			int y2 = blocks[0].y;
			bool block2 = false;

			int x3 = blocks[0].x + 1;
			int y3 = blocks[0].y;
			bool block3 = false;

			int ava_block = 0;
			if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height &&map[x1][y1]=='0')
			{
				block1 = true;
				ava_block++;
			}
			if (x2 >= 0 && x2 < width && y2 >= 0 && y2 < height && map[x2][y2] =='0')
			{
				block2 = true;
				ava_block++;
			}
			if (x3 >= 0 && x3 < width && y3 >= 0 && y3 < height && map[x3][y3] =='0')
			{
				block3 = true;
				ava_block++;
			}
			
			if (ava_block == 0) // no avaliable block
			{
				//cout << blocks.size();
				blocks.erase(blocks.begin()); // erase first element
				continue;
			}
			
			if (block1) // if the upper block is avaliable
			{
				if (ava_block == 1) // only one block avaliable, which one?->block1
				{
					if (rand01() <= way1_0) // save it
					{
						// block 1 become 0
						map[x1][y1] = '0';
						block upper(x1, y1, "up");
						blocks.push_back(upper);allzeors.push_back(upper);
					}
					else // block it
					{
						if (spawn_walls(x1, y1))
						{
							map[x1][y1] = 'W';
						}
						
					}
				}
				else if (ava_block == 2)
				{
					if (block2) // 1,2 ava
					{
						if (rand01() <= way2_1) // +1 both 1 and 2 ava
						{
							block upper(x1, y1, "up");
							blocks.push_back(upper);allzeors.push_back(upper);
							block left(x2, y2, "left");
							blocks.push_back(left);allzeors.push_back(left);
							// 1,2 become 0
						}
						else 
						{
							if (rand01() <= way2_0) // 0: one of 1 and 2 ava
							{
								if (rand01() >= 0.5)
								{
									block upper(x1, y1, "up");
									blocks.push_back(upper);allzeors.push_back(upper);
									if (spawn_walls(x2, y2))
									{
										map[x2][y2] = 'W';
									}
									// 1 become 0, 2 become W
								}
								else
								{
									block left(x2, y2, "left");
									blocks.push_back(left);allzeors.push_back(left);
										if (spawn_walls(x1, y1))
										{
											map[x1][y1] = 'W';
										}
									// 2 become 0, 1 become W
								}
							}
							else // -1 both 1 and 2 block
							{
								if (spawn_walls(x1, y1))
								{
									map[x1][y1] = 'W';
								}
								if (spawn_walls(x2, y2))
								{
									map[x2][y2] = 'W';
								}
							}
						}
					}
					else // 1,3 ava
					{
						if (rand01() >= 0.5) // +1 both 1 and 3 ava
						{
							block upper(x1, y1, "up");
							blocks.push_back(upper);allzeors.push_back(upper);
							block right(x3, y3, "right");
							blocks.push_back(right);allzeors.push_back(right);
							// 1,3 become 0
						}
						else
						{
							if (rand01() >= 0.5) // 0: one of 1 and 3 ava
							{
								if (rand01() >= 0.5)
								{
									block upper(x1, y1, "up");
									blocks.push_back(upper);allzeors.push_back(upper);
									if (spawn_walls(x3, y3))
									{
										map[x3][y3] = 'W';
									}
									
									// 1 become 0, 3 become W
								}
								else
								{
									block right(x3, y3, "right");
									blocks.push_back(right);allzeors.push_back(right);
									if (spawn_walls(x1, y1))
									{
										map[x1][y1] = 'W';
									}
									
									// 3 become 0, 1 become W
								}
							}
							else // -1 both 1 and 2 block
							{
								if (spawn_walls(x1, y1))
								{
									map[x1][y1] = 'W';
								}
								if (spawn_walls(x2, y2))
								{
									map[x2][y2] = 'W';
								}
								
							}
						}
					}
				}
				else if (ava_block == 3)
				{
					if (rand01() <= way3_2) // +2 block 0 way
					{
						block upper(x1, y1, "up");
						blocks.push_back(upper);allzeors.push_back(upper);
						block left(x2, y2, "left");
						blocks.push_back(left);allzeors.push_back(left);
						block right(x3, y3, "right");
						blocks.push_back(right);allzeors.push_back(right);
						// 1,2,3 become 0
					}
					else if(rand01()<=way3_1) // +1 random block one way
					{
						if (rand01() <= 0.33) // block 1
						{
							block left(x2, y2, "left");
							blocks.push_back(left);allzeors.push_back(left);
							block right(x3, y3, "right");
							blocks.push_back(right);allzeors.push_back(right);
							if (spawn_walls(x1, y1))
							{
								map[x1][y1] = 'W';
							}
							
							// 2,3 become 0
						}
						else if (rand01() <= 0.5) // block 2
						{
							block upper(x1, y1, "up");
							blocks.push_back(upper);allzeors.push_back(upper);
							block right(x3, y3, "right");
							blocks.push_back(right);allzeors.push_back(right);
							if (spawn_walls(x2, y2))
							{
								map[x2][y2] = 'W';
							}
			
							// 1,3 become 0
						}
						else // block 3
						{
							block upper(x1, y1, "up");
							blocks.push_back(upper);allzeors.push_back(upper);
							block left(x2, y2, "left");
							blocks.push_back(left);allzeors.push_back(left);
							
							if (spawn_walls(x3, y3))
							{
								map[x3][y3] = 'W';
							}
							// 1,2 become 0
						}
					}
					else if(rand01()<=way3_0) // -1  block all ways
					{
						if (spawn_walls(x1, y1))
						{
							map[x1][y1] = 'W';
						}
						if (spawn_walls(x2, y2))
						{
							map[x2][y2] = 'W';
						}
						if (spawn_walls(x3, y3))
						{
							map[x3][y3] = 'W';
						}
					}
					else // 0  block two ways
					{
						if (rand01() <= 0.33) // leave 1
						{
							block upper(x1, y1, "up");
							blocks.push_back(upper);allzeors.push_back(upper);
								
							if (spawn_walls(x2, y2))
							{
								map[x2][y2] = 'W';
							}
							if (spawn_walls(x3, y3))
							{
								map[x3][y3] = 'W';
							}
							// 1 become 0
						}
						else if (rand01() <= 0.5) // leave 2
						{
							block left(x2, y2, "left");
							blocks.push_back(left);allzeors.push_back(left);
								if (spawn_walls(x1, y1))
								{
									map[x1][y1] = 'W';
								}
							
							if (spawn_walls(x3, y3))
							{
								map[x3][y3] = 'W';
							}
							// 2 become 0
						}
						else // leave 3
						{
							block right(x3, y3, "right");
							blocks.push_back(right);allzeors.push_back(right);
								if (spawn_walls(x1, y1))
								{
									map[x1][y1] = 'W';
								}
							if (spawn_walls(x2, y2))
							{
								map[x2][y2] = 'W';
							}
							
							// 3 become 0
						}
					}
				}
			}
			else if (block2) //left block is avaliable, upper block is not avaliable
			{
				if (ava_block == 1) // only one block avaliable, block 2 avaliable 
				{
					if (rand01() <= way1_0) // save it
					{
						// block 2 become 0
						map[x2][y2] = '0';
						block left(x2, y2, "left");
						blocks.push_back(left);allzeors.push_back(left);
					}
					else // block it
					{
						
						if (spawn_walls(x2, y2))
						{
							map[x2][y2] = 'W';
						}
						
					}
				}
				else // two block avaliable, which is 2 and 3
				{
					if (rand01() <= way2_1) // +1 both 2 and 3 ava
					{
						block right(x3, y3, "right");
						blocks.push_back(right);allzeors.push_back(right);
						block left(x2, y2, "left");
						blocks.push_back(left);allzeors.push_back(left);
						// 2,3 become 0
					}
					else
					{
						if (rand01() <= way2_0) // 0: one of 2 and 3 ava
						{
							if (rand01() >= 0.5)
							{
								block right(x3, y3, "right");
								blocks.push_back(right);allzeors.push_back(right);
								
								if (spawn_walls(x2, y2))
								{
									map[x2][y2] = 'W';
								}
								
								// 3 become 0, 2 become W, 1 is not avaliable
							}
							else
							{
								block left(x2, y2, "left");
								blocks.push_back(left);allzeors.push_back(left);
									
								if (spawn_walls(x3, y3))
								{
									map[x3][y3] = 'W';
								}
								// 2 become 0, 3 become W, 1 is not avaliable
							}
						}
						else // -1 both 1 and 2 block
						{
							if (spawn_walls(x1, y1))
							{
								map[x1][y1] = 'W';
							}
							if (spawn_walls(x2, y2))
							{
								map[x2][y2] = 'W';
							}
							
						}
					}
					
				}
			}
			else { // only block 3 is avaliable 
				if (rand01() <= way1_0) // save it
				{
					// block 3 become 0
					map[x3][y3] = '0';
					block right(x3, y3, "right");
					blocks.push_back(right);allzeors.push_back(right);
				}
				else // block it
				{
					
					if (spawn_walls(x3, y3))
					{
						map[x3][y3] = 'W';
					}
				}
			}
			blocks.erase(blocks.begin()); // erase first element
		}
		else if (blocks[0].type == "down")
		{
		
			// block 1 down
			int x1 = blocks[0].x;
			int y1 = blocks[0].y - 1;
			bool block1 = false;
			// block 2 left
			int x2 = blocks[0].x - 1;
			int y2 = blocks[0].y;
			bool block2 = false;
			// block 3 right
			int x3 = blocks[0].x + 1;
			int y3 = blocks[0].y;
			bool block3 = false;

			int ava_block = 0;
			if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height && map[x1][y1] =='0')
			{
				block1 = true;
				ava_block++;
			}
			if (x2 >= 0 && x2 < width && y2 >= 0 && y2 < height && map[x2][y2] =='0')
			{
				block2 = true;
				ava_block++;
			}
			if (x3 >= 0 && x3 < width && y3 >= 0 && y3 < height && map[x3][y3] =='0')
			{
				block3 = true;
				ava_block++;
			}

			if (ava_block == 0) // no avaliable block
			{
				blocks.erase(blocks.begin()); // erase first element
				continue;
			}
			if (block1) // if the below block is avaliable
			{
				if (ava_block == 1) // only one block avaliable, which one?->block1
				{
					if (rand01() <= way1_0) // save it
					{
						// block 1 become 0
						map[x1][y1] = '0';
						block below(x1, y1, "down");
						blocks.push_back(below);allzeors.push_back(below);
					}
					else // block it
					{
						if (spawn_walls(x1, y1))
						{
							map[x1][y1] = 'W';
						}
						
					}
				}
				else if (ava_block == 2)
				{
					if (block2) // 1,2 ava
					{
						if (rand01() <= way2_1) // +1 both 1 and 2 ava
						{
							block below(x1, y1, "down");
							blocks.push_back(below);allzeors.push_back(below);
							block left(x2, y2, "left");
							blocks.push_back(left);allzeors.push_back(left);
							// 1,2 become 0
						}
						else
						{
							if (rand01() <= way2_0) // 0: one of 1 and 2 ava
							{
								if (rand01() >= 0.5)
								{
									block below(x1, y1, "down");
									blocks.push_back(below);allzeors.push_back(below);
									
									if (spawn_walls(x2, y2))
									{
										map[x2][y2] = 'W';
									}
									
									// 1 become 0, 2 become W
								}
								else
								{
									block left(x2, y2, "left");
									blocks.push_back(left);allzeors.push_back(left);
										if (spawn_walls(x1, y1))
										{
											map[x1][y1] = 'W';
										}
									
									// 2 become 0, 1 become W
								}
							}
							else // -1 both 1 and 2 block
							{
								if (spawn_walls(x1, y1))
								{
									map[x1][y1] = 'W';
								}
								if (spawn_walls(x2, y2))
								{
									map[x2][y2] = 'W';
								}
								
							}
						}
					}
					else // 1,3 ava
					{
						if (rand01() <= way2_1) // +1 both 1 and 3 ava
						{
							block below(x1, y1, "down");
							blocks.push_back(below);allzeors.push_back(below);
							block right(x3, y3, "right");
							blocks.push_back(right);allzeors.push_back(right);
							// 1,3 become 0
						}
						else
						{
							if (rand01() <= way2_0) // 0: one of 1 and 3 ava
							{
								if (rand01() >= 0.5)
								{
									block below(x1, y1, "down");
									blocks.push_back(below);allzeors.push_back(below);
									
									if (spawn_walls(x3, y3))
									{
										map[x3][y3] = 'W';
									}
									// 1 become 0, 3 become W
								}
								else
								{
									block right(x3, y3, "right");
									blocks.push_back(right);allzeors.push_back(right);
										if (spawn_walls(x1, y1))
										{
											map[x1][y1] = 'W';
										}
									
									// 3 become 0, 1 become W
								}
							}
							else // -1 both 1 and 2 block
							{
								if (spawn_walls(x1, y1))
								{
									map[x1][y1] = 'W';
								}
								if (spawn_walls(x2, y2))
								{
									map[x2][y2] = 'W';
								}
								
							}
						}
					}
				}
				else if (ava_block == 3)
				{
					if (rand01() <=way3_2) // +2 block 0 way
					{
						block below(x1, y1, "down");
						blocks.push_back(below);allzeors.push_back(below);
						block left(x2, y2, "left");
						blocks.push_back(left);allzeors.push_back(left);
						block right(x3, y3, "right");
						blocks.push_back(right);allzeors.push_back(right);
						// 1,2,3 become 0
					}
					else if (rand01() <= way3_1) // +1 random block one way
					{
						if (rand01() <= 0.33) // block 1
						{
							block left(x2, y2, "left");
							blocks.push_back(left);allzeors.push_back(left);
							block right(x3, y3, "right");
							blocks.push_back(right);allzeors.push_back(right);
							if (spawn_walls(x1, y1))
							{
								map[x1][y1] = 'W';
							}
							
							// 2,3 become 0
						}
						else if (rand01() <= 0.5) // block 2
						{
							block below(x1, y1, "down");
							blocks.push_back(below);allzeors.push_back(below);
							block right(x3, y3, "right");
							blocks.push_back(right);allzeors.push_back(right);
							
							if (spawn_walls(x2, y2))
							{
								map[x2][y2] = 'W';
							}
							
							// 1,3 become 0
						}
						else // block 3
						{
							block below(x1, y1, "down");
							blocks.push_back(below);allzeors.push_back(below);
							block left(x2, y2, "left");
							blocks.push_back(left);allzeors.push_back(left);
							
							if (spawn_walls(x3, y3))
							{
								map[x3][y3] = 'W';
							}
							// 1,2 become 0
						}
					}
					else if (rand01() <= way3_0) // -1  block all ways
					{
						if (spawn_walls(x1, y1))
						{
							map[x1][y1] = 'W';
						}
						if (spawn_walls(x2, y2))
						{
							map[x2][y2] = 'W';
						}
						if (spawn_walls(x3, y3))
						{
							map[x3][y3] = 'W';
						}
					}
					else // 0  block two ways
					{
						if (rand01() <= 0.33) // leave 1
						{
							block below(x1, y1, "down");
							blocks.push_back(below);allzeors.push_back(below);
								
							if (spawn_walls(x2, y2))
							{
								map[x2][y2] = 'W';
							}
							if (spawn_walls(x3, y3))
							{
								map[x3][y3] = 'W';
							}
							// 1 become 0
						}
						else if (rand01() <= 0.5) // leave 2
						{
							block left(x2, y2, "left");
							blocks.push_back(left);allzeors.push_back(left);
								if (spawn_walls(x1, y1))
								{
									map[x1][y1] = 'W';
								}
							
							if (spawn_walls(x3, y3))
							{
								map[x3][y3] = 'W';
							}
							// 2 become 0
						}
						else // leave 3
						{
							block right(x3, y3, "right");
							blocks.push_back(right);allzeors.push_back(right);
								if (spawn_walls(x1, y1))
								{
									map[x1][y1] = 'W';
								}
							if (spawn_walls(x2, y2))
							{
								map[x2][y2] = 'W';
							}
							
							// 3 become 0
						}
					}
				}
			}
			else if (block2) //left block is avaliable, below block is not avaliable
			{
				if (ava_block == 1) // only one block avaliable, block 2 avaliable 
				{
					if (rand01() <= way1_0) // save it
					{
						// block 2 become 0
						map[x2][y2] = '0';
						block left(x2, y2, "left");
						blocks.push_back(left);allzeors.push_back(left);
					}
					else // block it
					{
						
						if (spawn_walls(x2, y2))
						{
							map[x2][y2] = 'W';
						}
						
					}
				}
				else // two block avaliable, which is 2 and 3
				{
					if (rand01() <= way2_1) // +1 both 2 and 3 ava
					{
						block right(x3, y3, "right");
						blocks.push_back(right);allzeors.push_back(right);
						block left(x2, y2, "left");
						blocks.push_back(left);allzeors.push_back(left);
						// 2,3 become 0
					}
					else
					{
						if (rand01() <=way2_0) // 0: one of 2 and 3 ava
						{
							if (rand01() >= 0.5)
							{
								block right(x3, y3, "right");
								blocks.push_back(right);allzeors.push_back(right);
								
								if (spawn_walls(x2, y2))
								{
									map[x2][y2] = 'W';
								}
								
								// 3 become 0, 2 become W, 1 is not avaliable
							}
							else
							{
								block left(x2, y2, "left");
								blocks.push_back(left);allzeors.push_back(left);
									
								if (spawn_walls(x3, y3))
								{
									map[x3][y3] = 'W';
								}
								// 2 become 0, 3 become W, 1 is not avaliable
							}
						}
						else // -1 both 1 and 2 block
						{
							if (spawn_walls(x1, y1))
							{
								map[x1][y1] = 'W';
							}
							if (spawn_walls(x2, y2))
							{
								map[x2][y2] = 'W';
							}
							
						}
					}

				}
			}
			else { // only block 3 is avaliable 
				if (rand01() <=way1_0) // save it
				{
					// block 3 become 0
					map[x3][y3] = '0';
					block right(x3, y3, "right");
					blocks.push_back(right);allzeors.push_back(right);
				}
				else // block it
				{
					
					if (spawn_walls(x3, y3))
					{
						map[x3][y3] = 'W';
					}
				}
			}
			blocks.erase(blocks.begin()); // erase first element

		}
		else if (blocks[0].type == "left")
		{
			// block 2 left
			int x2 = blocks[0].x-1;
			int y2 = blocks[0].y;
			bool block2 = false;
			// block 3 down
			int x3 = blocks[0].x;
			int y3 = blocks[0].y-1;
			bool block3 = false;
			// block 1 up
			int x1 = blocks[0].x;
			int y1 = blocks[0].y+1;
			bool block1 = false;
			int ava_block = 0;
			if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height && map[x1][y1] =='0')
			{
				block1 = true;
				ava_block++;
			}
			if (x2 >= 0 && x2 < width && y2 >= 0 && y2 < height && map[x2][y2] =='0')
			{
				block2 = true;
				ava_block++;
			}
			if (x3 >= 0 && x3 < width && y3 >= 0 && y3 < height && map[x3][y3] =='0')
			{
				block3 = true;
				ava_block++;
			}
			if (ava_block == 0) // no avaliable block
			{
				blocks.erase(blocks.begin()); // erase first element
				continue;
			}

			if (block1) // if the upper block is avaliable
			{
				if (ava_block == 1) // only one block avaliable, which one?->block1
				{
					if (rand01() <= way1_0) // save it
					{
						// block 1 become 0
						map[x1][y1] = '0';
						block upper(x1, y1, "up");
						blocks.push_back(upper);allzeors.push_back(upper);
					}
					else // block it
					{
						if (spawn_walls(x1, y1))
						{
							map[x1][y1] = 'W';
						}
						
					}
				}
				else if (ava_block == 2)
				{
					if (block2) // 1,2 ava
					{
						if (rand01() <= way2_1) // +1 both 1 and 2 ava
						{
							block upper(x1, y1, "up");
							blocks.push_back(upper);allzeors.push_back(upper);
							block left(x2, y2, "left");
							blocks.push_back(left);allzeors.push_back(left);
							// 1,2 become 0
						}
						else
						{
							if (rand01() <= way2_0) // 0: one of 1 and 2 ava
							{
								if (rand01() >= 0.5)
								{
									block upper(x1, y1, "up");
									blocks.push_back(upper);allzeors.push_back(upper);
									
									if (spawn_walls(x2, y2))
									{
										map[x2][y2] = 'W';
									}
									
									// 1 become 0, 2 become W
								}
								else
								{
									block left(x2, y2, "left");
									blocks.push_back(left);allzeors.push_back(left);
										if (spawn_walls(x1, y1))
										{
											map[x1][y1] = 'W';
										}
									
									// 2 become 0, 1 become W
								}
							}
							else // -1 both 1 and 2 block
							{
								if (spawn_walls(x1, y1))
								{
									map[x1][y1] = 'W';
								}
								if (spawn_walls(x2, y2))
								{
									map[x2][y2] = 'W';
								}
							
							}
						}
					}
					else // 1,3 ava
					{
						if (rand01() >= 0.5) // +1 both 1 and 3 ava
						{
							block upper(x1, y1, "up");
							blocks.push_back(upper);allzeors.push_back(upper);
							block down(x3, y3, "down");
							blocks.push_back(down);
							// 1,3 become 0
						}
						else
						{
							if (rand01() >= 0.5) // 0: one of 1 and 3 ava
							{
								if (rand01() >= 0.5)
								{
									block upper(x1, y1, "up");
									blocks.push_back(upper);allzeors.push_back(upper);
									
									if (spawn_walls(x3, y3))
									{
										map[x3][y3] = 'W';
									}
									// 1 become 0, 3 become W
								}
								else
								{
									block down(x3, y3, "down");
									blocks.push_back(down);
										if (spawn_walls(x1, y1))
										{
											map[x1][y1] = 'W';
										}
									
									// 3 become 0, 1 become W
								}
							}
							else // -1 both 1 and 2 block
							{
								if (spawn_walls(x1, y1))
								{
									map[x1][y1] = 'W';
								}
								if (spawn_walls(x2, y2))
								{
									map[x2][y2] = 'W';
								}
								
							}
						}
					}
				}
				else if (ava_block == 3)
				{
					if (rand01() <= way3_2) // +2 block 0 way
					{
						block upper(x1, y1, "up");
						blocks.push_back(upper);allzeors.push_back(upper);
						block left(x2, y2, "left");
						blocks.push_back(left);allzeors.push_back(left);
						block down(x3, y3, "down");
						blocks.push_back(down);
						// 1,2,3 become 0
					}
					else if (rand01() <= way3_1) // +1 random block one way
					{
						if (rand01() <= 0.33) // block 1
						{
							block left(x2, y2, "left");
							blocks.push_back(left);allzeors.push_back(left);
							block down(x3, y3, "down");
							blocks.push_back(down);
							if (spawn_walls(x1, y1))
							{
								map[x1][y1] = 'W';
							}
							
							// 2,3 become 0
						}
						else if (rand01() <= 0.5) // block 2
						{
							block upper(x1, y1, "up");
							blocks.push_back(upper);allzeors.push_back(upper);
							block down(x3, y3, "down");
							blocks.push_back(down);
							
							if (spawn_walls(x2, y2))
							{
								map[x2][y2] = 'W';
							}
						
							// 1,3 become 0
						}
						else // block 3
						{
							block upper(x1, y1, "up");
							blocks.push_back(upper);allzeors.push_back(upper);
							block left(x2, y2, "left");
							blocks.push_back(left);allzeors.push_back(left);
							
							if (spawn_walls(x3, y3))
							{
								map[x3][y3] = 'W';
							}
							// 1,2 become 0
						}
					}
					else if (rand01() <= way3_0) // -1  block all ways
					{
						if (spawn_walls(x1, y1))
						{
							map[x1][y1] = 'W';
						}
						if (spawn_walls(x2, y2))
						{
							map[x2][y2] = 'W';
						}
						if (spawn_walls(x3, y3))
						{
							map[x3][y3] = 'W';
						}
					}
					else // 0  block two ways
					{
						if (rand01() <= 0.33) // leave 1
						{
							block upper(x1, y1, "up");
							blocks.push_back(upper);allzeors.push_back(upper);
							
							if (spawn_walls(x2, y2))
							{
								map[x2][y2] = 'W';
							}
							if (spawn_walls(x3, y3))
							{
								map[x3][y3] = 'W';
							}
							// 1 become 0
						}
						else if (rand01() <= 0.5) // leave 2
						{
							block left(x2, y2, "left");
							blocks.push_back(left);allzeors.push_back(left);
								if (spawn_walls(x1, y1))
								{
									map[x1][y1] = 'W';
								}
							
							if (spawn_walls(x3, y3))
							{
								map[x3][y3] = 'W';
							}
							// 2 become 0
						}
						else // leave 3
						{
							block down(x3, y3, "down");
							blocks.push_back(down);
								if (spawn_walls(x1, y1))
								{
									map[x1][y1] = 'W';
								}
							if (spawn_walls(x2, y2))
							{
								map[x2][y2] = 'W';
							}
							
							// 3 become 0
						}
					}
				}
			}
			else if (block2) //left block is avaliable, upper block is not avaliable
			{
				if (ava_block == 1) // only one block avaliable, block 2 avaliable 
				{
					if (rand01() <= way1_0) // save it
					{
						// block 2 become 0
						map[x2][y2] = '0';
						block left(x2, y2, "left");
						blocks.push_back(left);allzeors.push_back(left);
					}
					else // block it
					{
						
						if (spawn_walls(x2, y2))
						{
							map[x2][y2] = 'W';
						}
						
					}
				}
				else // two block avaliable, which is 2 and 3
				{
					if (rand01() <= way2_1) // +1 both 2 and 3 ava
					{
						block down(x3, y3, "down");
						blocks.push_back(down);
						block left(x2, y2, "left");
						blocks.push_back(left);allzeors.push_back(left);
						// 2,3 become 0
					}
					else
					{
						if (rand01() <= way2_0) // 0: one of 2 and 3 ava
						{
							if (rand01() >= 0.5)
							{
								block down(x3, y3, "down");
								blocks.push_back(down);
								
								if (spawn_walls(x2, y2))
								{
									map[x2][y2] = 'W';
								}
								
								// 3 become 0, 2 become W, 1 is not avaliable
							}
							else
							{
								block left(x2, y2, "left");
								blocks.push_back(left);allzeors.push_back(left);
									
								if (spawn_walls(x3, y3))
								{
									map[x3][y3] = 'W';
								}
								// 2 become 0, 3 become W, 1 is not avaliable
							}
						}
						else // -1 both 1 and 2 block
						{
							if (spawn_walls(x1, y1))
							{
								map[x1][y1] = 'W';
							}
							if (spawn_walls(x2, y2))
							{
								map[x2][y2] = 'W';
							}
							
						}
					}

				}
			}
			else { // only block 3 is avaliable 
				if (rand01() <= way1_0) // save it
				{
					// block 3 become 0
					map[x3][y3] = '0';
					block down(x3, y3, "down");
					blocks.push_back(down);
				}
				else // block it
				{
					
					if (spawn_walls(x3, y3))
					{
						map[x3][y3] = 'W';
					}
				}
			}
			blocks.erase(blocks.begin()); // erase first element


		}
		else if (blocks[0].type == "right")
		{
			// block 2 right
			int x2 = blocks[0].x+1;
			int y2 = blocks[0].y;
			bool block2 = false;
			// block 3 down
			int x3 = blocks[0].x;
			int y3 = blocks[0].y-1;
			bool block3 = false;
			// block 1 up
			int x1 = blocks[0].x;
			int y1 = blocks[0].y+1;
			bool block1 = false;
			//cout << "h";
			int ava_block = 0;
			if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height && map[x1][y1] =='0')
			{
				block1 = true;
				ava_block++;
			}
			if (x2 >= 0 && x2 < width && y2 >= 0 && y2 < height && map[x2][y2] =='0')
			{
				block2 = true;
				ava_block++;
			}
			if (x3 >= 0 && x3 < width && y3 >= 0 && y3 < height && map[x3][y3] =='0')
			{
				block3 = true;
				ava_block++;
			}
			if (ava_block == 0) // no avaliable block
			{
				//cout << "h";
				blocks.erase(blocks.begin()); // erase first element
				continue;
			}
			if (block1) // if the upper block is avaliable
			{
				if (ava_block == 1) // only one block avaliable, which one?->block1
				{
					if (rand01() <= way1_0) // save it
					{
						// block 1 become 0
						map[x1][y1] = '0';
						block upper(x1, y1, "up");
						blocks.push_back(upper);allzeors.push_back(upper);
					}
					else // block it
					{
						if (spawn_walls(x1, y1))
						{
							map[x1][y1] = 'W';
						}
						
					}
				}
				else if (ava_block == 2)
				{
					if (block2) // 1,2 ava
					{
						if (rand01() <= way2_1) // +1 both 1 and 2 ava
						{
							block upper(x1, y1, "up");
							blocks.push_back(upper);allzeors.push_back(upper);
							block right(x2, y2, "right");
							blocks.push_back(right);allzeors.push_back(right);
							// 1,2 become 0
						}
						else
						{
							if (rand01() <= way2_0) // 0: one of 1 and 2 ava
							{
								if (rand01() >= 0.5)
								{
									block upper(x1, y1, "up");
									blocks.push_back(upper);allzeors.push_back(upper);
									
									if (spawn_walls(x2, y2))
									{
										map[x2][y2] = 'W';
									}
									
									// 1 become 0, 2 become W
								}
								else
								{
									block right(x2, y2, "right");
									blocks.push_back(right);allzeors.push_back(right);
										if (spawn_walls(x1, y1))
										{
											map[x1][y1] = 'W';
										}
									
									// 2 become 0, 1 become W
								}
							}
							else // -1 both 1 and 2 block
							{
								if (spawn_walls(x1, y1))
								{
									map[x1][y1] = 'W';
								}
								if (spawn_walls(x2, y2))
								{
									map[x2][y2] = 'W';
								}
								
							}
						}
					}
					else // 1,3 ava
					{
						if (rand01() >= 0.5) // +1 both 1 and 3 ava
						{
							block upper(x1, y1, "up");
							blocks.push_back(upper);allzeors.push_back(upper);
							block down(x3, y3, "down");
							blocks.push_back(down);
							// 1,3 become 0
						}
						else
						{
							if (rand01() >= 0.5) // 0: one of 1 and 3 ava
							{
								if (rand01() >= 0.5)
								{
									block upper(x1, y1, "up");
									blocks.push_back(upper);allzeors.push_back(upper);
									
									if (spawn_walls(x3, y3))
									{
										map[x3][y3] = 'W';
									}
									// 1 become 0, 3 become W
								}
								else
								{
									block down(x3, y3, "down");
									blocks.push_back(down);
										if (spawn_walls(x1, y1))
										{
											map[x1][y1] = 'W';
										}
									
									// 3 become 0, 1 become W
								}
							}
							else // -1 both 1 and 2 block
							{
								if (spawn_walls(x1, y1))
								{
									map[x1][y1] = 'W';
								}
								if (spawn_walls(x2, y2))
								{
									map[x2][y2] = 'W';
								}
								
							}
						}
					}
				}
				else if (ava_block == 3)
				{
					if (rand01() <= way3_2) // +2 block 0 way
					{
						block upper(x1, y1, "up");
						blocks.push_back(upper);allzeors.push_back(upper);
						block right(x2, y2, "right");
						blocks.push_back(right);allzeors.push_back(right);
						block down(x3, y3, "down");
						blocks.push_back(down);
						// 1,2,3 become 0
					}
					else if (rand01() <= way3_1) // +1 random block one way
					{
						if (rand01() <= 0.33) // block 1
						{
							block right(x2, y2, "right");
							blocks.push_back(right);allzeors.push_back(right);
							block down(x3, y3, "down");
							blocks.push_back(down);
							if (spawn_walls(x1, y1))
							{
								map[x1][y1] = 'W';
							}
							
							// 2,3 become 0
						}
						else if (rand01() <= 0.5) // block 2
						{
							block upper(x1, y1, "up");
							blocks.push_back(upper);allzeors.push_back(upper);
							block down(x3, y3, "down");
							blocks.push_back(down);
							
							if (spawn_walls(x2, y2))
							{
								map[x2][y2] = 'W';
							}
							
							// 1,3 become 0
						}
						else // block 3
						{
							block upper(x1, y1, "up");
							blocks.push_back(upper);allzeors.push_back(upper);
							block right(x2, y2, "right");
							blocks.push_back(right);allzeors.push_back(right);
							
							if (spawn_walls(x3, y3))
							{
								map[x3][y3] = 'W';
							}
							// 1,2 become 0
						}
					}
					else if (rand01() <= way3_0) // -1  block all ways
					{
						if (spawn_walls(x1, y1))
						{
							map[x1][y1] = 'W';
						}
						if (spawn_walls(x2, y2))
						{
							map[x2][y2] = 'W';
						}
						if (spawn_walls(x3, y3))
						{
							map[x3][y3] = 'W';
						}
					}
					else // 0  block two ways
					{
						if (rand01() <= 0.33) // leave 1
						{
							block upper(x1, y1, "up");
							blocks.push_back(upper);allzeors.push_back(upper);
								
							if (spawn_walls(x2, y2))
							{
								map[x2][y2] = 'W';
							}
							if (spawn_walls(x3, y3))
							{
								map[x3][y3] = 'W';
							}
							// 1 become 0
						}
						else if (rand01() <= 0.5) // leave 2
						{
							block right(x2, y2, "right");
							blocks.push_back(right);allzeors.push_back(right);
								if (spawn_walls(x1, y1))
								{
									map[x1][y1] = 'W';
								}
							
							if (spawn_walls(x3, y3))
							{
								map[x3][y3] = 'W';
							}
							// 2 become 0
						}
						else // leave 3
						{
							block down(x3, y3, "down");
							blocks.push_back(down);
								if (spawn_walls(x1, y1))
								{
									map[x1][y1] = 'W';
								}
							if (spawn_walls(x2, y2))
							{
								map[x2][y2] = 'W';
							}
							
							// 3 become 0
						}
					}
				}
			}
			else if (block2) //right block is avaliable, upper block is not avaliable
			{
				if (ava_block == 1) // only one block avaliable, block 2 avaliable 
				{
					if (rand01() <= way1_0) // save it
					{
						// block 2 become 0
						map[x2][y2] = '0';
						block right(x2, y2, "right");
						blocks.push_back(right);allzeors.push_back(right);
					}
					else // block it
					{
						if (spawn_walls(x2, y2))
						{
							map[x2][y2] = 'W';
						}
					}
				}
				else // two block avaliable, which is 2 and 3
				{
					if (rand01() <= way2_1) // +1 both 2 and 3 ava
					{
						block down(x3, y3, "down");
						blocks.push_back(down);
						block right(x2, y2, "right");
						blocks.push_back(right);allzeors.push_back(right);
						// 2,3 become 0
					}
					else
					{
						if (rand01() <= way2_0) // 0: one of 2 and 3 ava
						{
							if (rand01() >= 0.5)
							{
								block down(x3, y3, "down");
								blocks.push_back(down);
								
								if (spawn_walls(x2, y2))
								{
									map[x2][y2] = 'W';
								}
								
								// 3 become 0, 2 become W, 1 is not avaliable
							}
							else
							{
								block right(x2, y2, "right");
								blocks.push_back(right);allzeors.push_back(right);
									
								if (spawn_walls(x3, y3))
								{
									map[x3][y3] = 'W';
								}
								// 2 become 0, 3 become W, 1 is not avaliable
							}
						}
						else // -1 both 1 and 2 block
						{
							if (spawn_walls(x1, y1))
							{
								map[x1][y1] = 'W';
							}
							if (spawn_walls(x2, y2))
							{
								map[x2][y2] = 'W';
							}
							
						}
					}

				}
			}
			else { // only block 3 is avaliable 
				if (rand01() <= way1_0) // save it
				{
					// block 3 become 0
					map[x3][y3] = '0';
					block down(x3, y3, "down");
					blocks.push_back(down);
				}
				else // block it
				{
					
					if (spawn_walls(x3, y3))
					{
						map[x3][y3] = 'W';
					}
				}
			}
			blocks.erase(blocks.begin()); // erase first element
		}
		map[x][y] = '0';
		for (int j = height - 1; j >= 0; j--)
		{
			for (int i = 0; i <width; i++)
			{

				cout << map[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl << endl;
	}
	map[blocks[0].x][blocks[0].y] = 'G';
	for (int j = height - 1; j >= 0; j--)
	{
		for (int i = 0; i < width; i++)
		{

			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
}

int main()
{
	generate_map(5, 5, 0);
	return 0;
}