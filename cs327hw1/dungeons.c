#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "dungeons.h"


const char corridorTile = '#';
const char floorTile = '.';
const char rockTile = ' ';
const char upstairTile = '<';
const char downstairTile = '>';
const int sizeX = 79, sizeY = 20;
const int minRoomX = 4, minRoomY = 3, minRoomNum = 6;
const int maxRoomX = 10, maxRoomY = 10, maxRoomNum = 12;


tile **map;


int main(int argc, char *argv[])
{
    int i, j;
    srand(time(NULL));
    map = malloc(sizeX * sizeY * sizeof(tile));
    for(i = 0; i < sizeY; i++)
    {
        map[i] = malloc(sizeX * sizeof(tile));
    }
    for(i = 0; i < sizeY; i++)
    {
        for(j = 0; j < sizeX; j++)
        {
            map[i][j].icon = rockTile;
            map[i][j].hardness = getRandInt(1, 100);
        }
    }


    generateRooms();

    printMap();



    free(map);
    return 0;
}
void printMap()
{
    int i, j;
    for(i = 0; i <= sizeX + 1; i++)
    {
        printf("-");
    }
    printf("\n");
    for(i = 0; i < sizeY; i++)
    {
        printf("|");
        for(j = 0; j < sizeX; j++)
        {
            printf("%c", map[i][j].icon);
        }
        printf("|\n");
    }
    for(i = 0; i <= sizeX + 1; i++)
    {
        printf("-");
    }
    printf("\n");
}
void generateRooms()
{
    int j, currRooms = 0;
    int roomNum = getRandInt(minRoomNum, maxRoomNum);
    bool isOpen;
    room rooms[roomNum];
    for(currRooms = 0; currRooms < roomNum;)
    {
        isOpen = true;
        room genRoom;
        genRoom.xSize = getRandInt(minRoomX, maxRoomX);
        genRoom.ySize = getRandInt(minRoomY, maxRoomY);
        genRoom.xLoc = getRandInt(1, sizeX - genRoom.xSize - 1);
        genRoom.yLoc = getRandInt(1, sizeY - genRoom.ySize - 1);
        genRoom.connected = false;
        for(j = 0; j < currRooms; j++)
        {
            if(roomIntersect(genRoom, rooms[j]))
            {
                isOpen = false;
            }
        }
        if(isOpen)
        {
            rooms[currRooms] = genRoom;
            currRooms++;
            int u, o;
            for(u = genRoom.yLoc; u < genRoom.yLoc + genRoom.ySize; u++)
            {
                for(o = genRoom.xLoc; o < genRoom.xLoc + genRoom.xSize; o++)
                {
                    map[u][o].icon = floorTile;
                }
            }
        }
    }

    generatePaths(roomNum, rooms);
    generateRoomObj(roomNum, rooms);
}
void generatePaths(int roomNum, room rooms[roomNum])
{
    int i, j, closeRoom, lowest, ax, ay, bx, by, extraPathNum, extraStart, extraEnd, temp;

    for(i = 0; i < roomNum; i++)
    {
        lowest = 1000;
        ax = rooms[i].xLoc + (rooms[i].xSize/2);
        ay = rooms[i].yLoc + (rooms[i].ySize/2);
        for(j = 0; j < roomNum; j++)
        {
            if(j != i)
            {
                bx = rooms[j].xLoc + (rooms[j].xSize/2);
                by = rooms[j].yLoc + (rooms[j].ySize/2);
                temp = sqrt(((bx - ax)*(bx - ax) + (by - ay)*(by - ay)));
                if(temp < lowest && rooms[j].connected == false)
                {
                    lowest = temp;
                    closeRoom = j;
                }
            }
        }
        rooms[i].connected = true;
        bx = rooms[closeRoom].xLoc + (rooms[closeRoom].xSize/2);
        by = rooms[closeRoom].yLoc + (rooms[closeRoom].ySize/2);
        buildPath(ax, ay, bx, by, closeRoom, roomNum, rooms);
    }
    extraPathNum = getRandInt(1, 3);
    for(i = 0; i < extraPathNum; i++)
    {
        extraStart = getRandInt(0, roomNum - 1);
        extraEnd = getRandInt(0, roomNum - 1);
        while(extraStart == extraEnd)
        {
            extraEnd = getRandInt(0, roomNum - 1);
        }
        int axu = rooms[extraStart].xLoc + (rooms[extraStart].xSize/2);
        int ayu = rooms[extraStart].yLoc + (rooms[extraStart].ySize/2);
        int bxu = rooms[extraEnd].xLoc + (rooms[extraEnd].xSize/2);
        int byu = rooms[extraEnd].yLoc + (rooms[extraEnd].ySize/2);
        buildPath(axu, ayu, bxu, byu, extraEnd, roomNum, rooms);
    }

}
void generateRoomObj(int roomNum, room rooms[roomNum])
{
    int downNum = getRandInt(0, roomNum - 1);
    int upNum = getRandInt(0, roomNum - 1);
    while(upNum == downNum)
    {
        upNum = getRandInt(0, roomNum - 1);
    }
    int xStair = getRandInt(1, (rooms[downNum].xSize) - 2);
    int yStair = getRandInt(1, (rooms[downNum].ySize) - 2);
    map[rooms[downNum].yLoc + yStair][rooms[downNum].xLoc + xStair].icon = downstairTile;
    xStair = getRandInt(1, (rooms[upNum].xSize) - 2);
    yStair = getRandInt(1, (rooms[upNum].ySize) - 2);
    map[rooms[upNum].yLoc + yStair][rooms[upNum].xLoc + xStair].icon = upstairTile;
}
void buildPath(int ax, int ay, int bx, int by, int closeRoom, int roomNum, room rooms[roomNum])
{
    int xDirect;
    int yDirect;
    int currX, currY;
    bool atRoom;
    xDirect = ax <= bx ? 1 : -1; // Determines which direction, +/- the x and y values need to go to get closer to target
    yDirect = ay <= by ? 1 : -1;
    atRoom = false;
    currX = ax;
    currY = ay;
    while(!atRoom)
        {
            if(map[currY][currX].icon != floorTile && map[currY][currX].icon != corridorTile)
            {
                map[currY][currX].icon = corridorTile;
                if(currX == bx)
                {
                    currY = currY + yDirect;
                }
                else if(currY == by)
                {
                    currX = currX + (xDirect);
                }
                else if(sqrt(((bx - currX + xDirect)*(bx - currX + xDirect) + (by - currY)*(by - currY))) < sqrt(((bx - currX)*(bx - currX) + (by - currY + yDirect)*(by - currY + yDirect))) )
                {
                    currY = currY + yDirect;
                }
                else
                {
                    if(map[currY][currX + xDirect].hardness < map[currY + yDirect][currX].hardness)
                    {
                        currX = currX + (xDirect);
                    }
                    else
                    {
                        currY = currY + yDirect;
                    }

                }
                if(currY > 3 && currY < sizeY - 3) // Bridges corridors over the Y axis if only 1 tile between
                {
                    if((map[currY + 2][currX].icon == corridorTile || map[currY + 2][currX].icon == floorTile) && map[currY + 1][currX].icon != floorTile && map[currY + 1][currX].hardness < 25)
                    {
                        //if(!(map[currY + 2][currX + 1].icon = corridorTile) && (map[currY + 2][currX - 1].icon = corridorTile))
                            map[currY + 1][currX].icon = corridorTile;
                    }
                    if((map[currY - 2][currX].icon == corridorTile || map[currY - 2][currX].icon == floorTile) && map[currY - 1][currX].icon != floorTile && map[currY - 1][currX].hardness < 25)
                    {
                        //if(!(map[currY - 2][currX + 1].icon = corridorTile) && (map[currY - 2][currX - 1].icon = corridorTile))
                            map[currY - 1][currX].icon = corridorTile;
                    }
                }
                if(currX > 3 && currX < sizeX - 3) //Bridges corridors over the X axis if only 1 tile between
                {
                    if(map[currY][currX + 2].icon == corridorTile && map[currY][currX].icon == corridorTile && map[currY + 2][currX].icon == corridorTile)
                    if((map[currY][currX + 2].icon == corridorTile || map[currY][currX + 2].icon == floorTile) && map[currY][currX + 1].icon != floorTile && map[currY][currX + 1].hardness < 25)
                    {
                        //if(!(map[currY + 1][currX + 2].icon = corridorTile) && (map[currY - 1][currX + 2].icon = corridorTile))
                            map[currY][currX + 1].icon = corridorTile;
                    }
                    if((map[currY][currX - 2].icon == corridorTile || map[currY][currX - 2].icon == floorTile) && map[currY][currX - 1].icon != floorTile && map[currY][currX - 1].hardness < 25)
                    {
                        //if(!(map[currY + 1][currX - 2].icon = corridorTile) && (map[currY - 1][currX - 2].icon = corridorTile))
                            map[currY][currX - 1].icon = corridorTile;
                    }
                }
            }
            else
            {
                if(((currX > rooms[closeRoom].xLoc && currX < rooms[closeRoom].xLoc + rooms[closeRoom].xSize) && (currY > rooms[closeRoom].yLoc && currY < rooms[closeRoom].yLoc + rooms[closeRoom].ySize)))
                {
                    atRoom = true;
                }
                else
                {
                    if(currX == bx)
                    {
                        currY = currY + yDirect;
                    }
                    else if(currY == by)
                    {
                        currX = currX + (xDirect);
                    }
                    else if(currX + bx*(xDirect) <= currY + by*(yDirect))
                    {
                        currY = currY + yDirect;
                    }
                    else
                    {
                        currX = currX + (xDirect);
                    }
                }
            }
        }
}
int getRandInt(int lower, int upper)
{
    return (rand() % (upper - lower + 1)) + lower;

}
int roomIntersect(room a, room b) //Includes size 1 spacing around room.
{
    if(((a.xLoc - 1 < b.xLoc && a.xLoc - 1 + a.xSize + 1 > b.xLoc + b.xSize) || (a.yLoc - 1 < b.yLoc && a.yLoc - 1 + a.ySize + 1 > b.yLoc + b.ySize))
        || ((b.xLoc < a.xLoc - 1 && b.xLoc + b.xSize > a.xLoc - 1 + a.xSize) || (b.yLoc < a.yLoc - 1 && b.yLoc + b.ySize > a.yLoc - 1 + a.ySize)) //return true if the room passes through the entirety of another room
        || ((a.xLoc - 1 >= b.xLoc && a.xLoc - 1 <= b.xLoc + b.xSize) && (a.yLoc - 1 >= b.yLoc && a.yLoc - 1 <= b.yLoc + b.ySize)) // Check A corners in B
        || ((a.xLoc - 1 + a.xSize + 1 >= b.xLoc && a.xLoc - 1 + a.xSize + 1 <= b.xLoc + b.xSize) && (a.yLoc - 1 >= b.yLoc && a.yLoc - 1 <= b.yLoc + b.ySize))
        || ((a.xLoc - 1 >= b.xLoc && a.xLoc - 1 <= b.xLoc + b.xSize) && (a.yLoc - 1 + a.ySize + 1 >= b.yLoc && a.yLoc - 1 + a.ySize + 1 <= b.yLoc + b.ySize))
        || ((a.xLoc - 1 + a.xSize + 1 >= b.xLoc && a.xLoc - 1 + a.xSize + 1 <= b.xLoc + b.xSize) && (a.yLoc - 1 + a.ySize + 1 >= b.yLoc && a.yLoc - 1 + a.ySize + 1 <= b.yLoc + b.ySize))
        || ((b.xLoc >= a.xLoc - 1 && b.xLoc <= a.xLoc - 1 + a.xSize) && (b.yLoc >= a.yLoc - 1 && b.yLoc <= a.yLoc - 1 + a.ySize)) // Check B corners in A
        || ((b.xLoc + b.xSize >= a.xLoc - 1 && b.xLoc + b.xSize <= a.xLoc - 1 + a.xSize) && (b.yLoc >= a.yLoc - 1 && b.yLoc <= a.yLoc - 1 + a.ySize))
        || ((b.xLoc >= a.xLoc - 1 && b.xLoc <= a.xLoc - 1 + a.xSize) && (b.yLoc + b.ySize >= a.yLoc - 1 && b.yLoc + b.ySize <= a.yLoc - 1 + a.ySize))
        || ((b.xLoc + b.xSize >= a.xLoc - 1 && b.xLoc + b.xSize <= a.xLoc - 1 + a.xSize) && (b.yLoc + b.ySize >= a.yLoc - 1 && b.yLoc + b.ySize <= a.yLoc - 1 + a.ySize)))
        return true;
    return false;
}
