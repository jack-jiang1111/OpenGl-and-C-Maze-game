

#include <stdio.h>
#include <ctype.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
// so this parse file will obtain all info and seal into seperate class
// Players (contain start and goal, all doors and keys)
// Walls
using namespace std;
class Door {
public:
    char door;
    char key;
    int doorx;
    int doory;
    float keyx;
    float keyy;
    float keyz;

    bool open;
    bool have_key;
    float r;
    float g;
    float b;
    Door()
    {
        have_key = false;
        open = false;
        keyz = 0;
        r = (float)rand() / RAND_MAX;
        g = (float)rand() / RAND_MAX;
        b = (float)rand() / RAND_MAX;
    }
};
int width = 5;
int height = 5;
class Player {
public:
    int Playerx = 0;
    int Playery = 0;
    int startx = 0;
    int starty = 0;
    int goalx = 0;
    int goaly = 0;
    bool goal = false;
    vector<Door> doors;
};
class Wall {
public:
    int x;
    int y;
    Wall(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};

vector<Wall> walls;
Player player;
void parseMapFile(std::string fileName){
  //TODO: Override the default values with new data from the file "fileName"
    // open the file containing the scene description
    std::ifstream input(fileName.c_str());
    // check for errors in opening the file
    if (input.fail()) {
        std::cout << "Can't open file '" << fileName << "'" << std::endl;
        return;
    }

    // determine the file size (this is optional -- feel free to delete the 6 lines below)
    std::streampos begin, end;
    begin = input.tellg();
    input.seekg(0, std::ios::end);
    end = input.tellg();
    std::cout << "File '" << fileName << "' is: " << (end - begin) << " bytes long.\n\n";
    input.seekg(0, std::ios::beg);


    //Loop through reading each line
    input >> width >> height;
    std::string line;
    int ycor = height-1;
    int xcor = -1;
    while (input >> line) { //Read first word in the line (i.e., the command type)
        xcor = -1;
        while (line != "")
        {
            xcor++;
            if (line[0] == '0') { // nothing
                line = line.substr(1);
                continue;
            }
            else if (line[0] == 'W') // wall
            {
                Wall newWall(xcor, ycor);
                walls.push_back(newWall);
                line = line.substr(1);
                continue;
            }
            else if (line[0] == 'G') // Goal
            {
                player.goalx = xcor;
                player.goaly = ycor;
                line = line.substr(1);
                continue;
            }
            else if (line[0] == 'S') //Start
            {
                player.Playerx = xcor;
                player.Playery = ycor;
                player.startx = xcor;
                player.starty = ycor;
                line = line.substr(1);
                continue;
            }
            else if (line[0] == 'a' || line[0] == 'b'|| line[0] == 'c'|| line[0] == 'd'|| line[0] == 'e') // key
            {
                char keyletter = line[0];
                bool find = false;
                for (int i = 0; i < player.doors.size(); i++) // find existing door
                {
                    if (player.doors[i].door == toupper(keyletter))
                    {
                        find = true;
                        player.doors[i].key = keyletter;
                        player.doors[i].keyx = xcor;
                        player.doors[i].keyy = ycor;
                    }
                }
                if (!find) // create a new pair
                {
                    Door newdoor;
                    newdoor.keyx = xcor;
                    newdoor.keyy = ycor;
                    newdoor.key = keyletter;
                    player.doors.push_back(newdoor);
                }
                line = line.substr(1);
                continue;
            }
            else if (line[0] == 'A' || line[0] == 'B' || line[0] == 'C' || line[0] == 'D' || line[0] == 'E') // door
            {
                char doorletter = line[0];
                bool find = false;
                for (int i = 0; i < player.doors.size(); i++) // find existing key
                {
                    if (player.doors[i].key == tolower(doorletter))
                    {
                        find = true;
                        player.doors[i].door = doorletter;
                        player.doors[i].doorx = xcor;
                        player.doors[i].doory = ycor;
                    }
                }
                if (!find) // create a new pair
                {
                    Door newdoor;
                    newdoor.doorx = xcor;
                    newdoor.doory = ycor;
                    newdoor.door = doorletter;
                    player.doors.push_back(newdoor);
                }
                line = line.substr(1);
                continue;
            }
            else {
                std::cout << "Unknown char " << line[0] << std::endl;
                line = line.substr(1);
                continue;
                
            }
            
        }
        ycor--;
    }


    // these two are the walls around the map
    for (int i = 0; i < width; i++)
    {
        Wall newWall(i, -1);
        walls.push_back(newWall);
        Wall newWalls(i, width);
        walls.push_back(newWalls);
    }
    for (int i = 0; i < height; i++)
    {
        Wall newWall(-1, i);
        walls.push_back(newWall);
        Wall newWalls(height,i);
        walls.push_back(newWalls);
    }
}
/*
int main(int argc, char* argv[])
{
    parseMapFile(argv[1]);
    for (int i = 0; i < walls.size(); i++)
    {
        cout << "wall " << walls[i].x << " " << walls[i].y << endl;
    }
    cout << "player " << player.Playerx << " " << player.Playery << endl;
    cout << "goal " << player.goalx << " " << player.goaly << endl;
    for (int i = 0; i < player.doors.size(); i++)
    {
        cout << "door " << player.doors[i].door << " " << player.doors[i].key << " " << player.doors[i].doorx << " " << player.doors[i].doory << endl;
        cout<< "key "<< player.doors[i].door << " " << player.doors[i].key << " " << player.doors[i].keyx << " " << player.doors[i].keyy << endl;
    }
    return 0;
}
#endif
*/