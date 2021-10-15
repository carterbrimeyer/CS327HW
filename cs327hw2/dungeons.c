#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <endian.h>
#include "dungeons.h"
#include <errno.h>

int playerXLoc, playerYLoc;


int main(int argc, char *argv[])
{
    dungeon d;
    char *path = strcat(getenv("HOME"), "/.rlg327/dungeon/testdungeon.rlg327");
    int i, j;
    srand(time(NULL));
    d.map = malloc(sizeX * sizeY * sizeof(tile));
    for(i = 0; i < sizeY; i++)
    {
        d.map[i] = malloc(sizeX * sizeof(tile));
    }

    for(i = 0; i < sizeY; i++)
    {
        for(j = 0; j < sizeX; j++)
        {
            d.map[i][j].icon = rockTile;
            d.hardness[i][j] = (int8_t) getRandInt(1, 255);
        }
    }
    if(argc > 1 && strcmp(argv[1], "--load") == 0) {
        d = loadFromFile(d, path);
        printMap(d);

    }
    else if(argc > 1 && strcmp(argv[1], "--save") == 0)
    {
        d = generateRooms(d);
        saveToFile(d, path);
        printMap(d);
    }
    else
    {
        d = generateRooms(d);
        printMap(d);
    }

    free(d.rooms);
    free(d.map);
    return 0;
}
void printMap(dungeon d)
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
            printf("%c", d.map[i][j].icon);
        }
        printf("|\n");
    }
    for(i = 0; i <= sizeX + 1; i++)
    {
        printf("-");
    }
    printf("\n");
}
dungeon generateRooms(dungeon d)
{
    int j, currRooms;
    d.roomNum = getRandInt(minRoomNum, maxRoomNum);
   d.rooms= malloc(d.roomNum * sizeof(room));
    bool isOpen;
    for(currRooms= 0; currRooms < d.roomNum;)
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
            if(roomIntersect(genRoom,d.rooms[j]))
            {
                isOpen = false;
            }
        }
        if(isOpen)
        {
           d.rooms[currRooms] = genRoom;
            currRooms++;
            int u, o;
            for(u = genRoom.yLoc; u < genRoom.yLoc + genRoom.ySize; u++)
            {
                for(o = genRoom.xLoc; o < genRoom.xLoc + genRoom.xSize; o++)
                {
                    d.map[u][o].icon = floorTile;
                    d.hardness[u][o] = 0;
                }
            }
        }
    }

    d = generatePaths(d);
    d = generateRoomObj(d);
    return d;
}
dungeon generatePaths(dungeon d)
{
    int i, j, closeRoom, lowest, ax, ay, bx, by;
    int xDirect;
    int yDirect;
    int currX, currY;
    bool atRoom;
    for(i = 0; i < d.roomNum; i++)
    {
        lowest = 1000;
        ax =d.rooms[i].xLoc + (d.rooms[i].xSize/2);
        ay =d.rooms[i].yLoc + (d.rooms[i].ySize/2);
        for(j = 0; j < d.roomNum; j++)
        {
            if(j != i)
            {
                bx =d.rooms[j].xLoc + (d.rooms[j].xSize/2);
                by =d.rooms[j].yLoc + (d.rooms[j].ySize/2);
                int temp = sqrt(((bx - ax)*(bx - ax) + (by - ay)*(by - ay)));
                if(temp < lowest &&d.rooms[j].connected == false)
                {
                    lowest = temp;
                    closeRoom = j;
                }
            }
        }
       d.rooms[i].connected = true;
        bx =d.rooms[closeRoom].xLoc + (d.rooms[closeRoom].xSize/2);
        by =d.rooms[closeRoom].yLoc + (d.rooms[closeRoom].ySize/2);
        xDirect = ax <= bx ? 1 : -1; // Determines which direction, +/- the x and y values need to go to get closer to target
        yDirect = ay <= by ? 1 : -1;
        atRoom = false;
        currX = ax;
        currY = ay;
        while(!atRoom)
        {
            if(d.map[currY][currX].icon != floorTile && d.map[currY][currX].icon != corridorTile)
            {
                d.map[currY][currX].icon = corridorTile;
                d.hardness[currY][currX] = 0;
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
                if(currY > 3 && currY < sizeY - 3) // Bridges corridors over the Y axis if only 1 tile between
                {
                    if((d.map[currY + 2][currX].icon == corridorTile || d.map[currY + 2][currX].icon == floorTile) && d.map[currY + 1][currX].icon != floorTile && d.hardness[currY + 1][currX] < 25)
                    {
                        d.map[currY + 1][currX].icon = corridorTile;
                        d.hardness[currY + 1][currX] = 0;
                    }
                    if((d.map[currY - 2][currX].icon == corridorTile || d.map[currY - 2][currX].icon == floorTile) && d.map[currY - 1][currX].icon != floorTile && d.hardness[currY - 1][currX] < 25)
                    {
                        d.map[currY - 1][currX].icon = corridorTile;
                        d.hardness[currY - 1][currX] = 0;
                    }
                }
                if(currX > 3 && currX < sizeX - 3) //Bridges corridors over the X axis if only 1 tile between
                {
                    if((d.map[currY][currX + 2].icon == corridorTile || d.map[currY][currX + 2].icon == floorTile) && d.map[currY][currX + 1].icon != floorTile && d.hardness[currY][currX + 1] < 25)
                    {
                        d.map[currY][currX + 1].icon = corridorTile;
                        d.hardness[currY][currX + 1] = 0;
                    }
                    if((d.map[currY][currX - 2].icon == corridorTile || d.map[currY][currX - 2].icon == floorTile) && d.map[currY][currX - 1].icon != floorTile && d.hardness[currY][currX - 1] < 25)
                    {
                        d.map[currY][currX - 1].icon = corridorTile;
                        d.hardness[currY][currX - 1] = 0;
                    }
                }
            }
            else
            {
                if(((currX >d.rooms[closeRoom].xLoc && currX <d.rooms[closeRoom].xLoc +d.rooms[closeRoom].xSize) && (currY >d.rooms[closeRoom].yLoc && currY <d.rooms[closeRoom].yLoc +d.rooms[closeRoom].ySize)))
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
    return d;
}
dungeon generateRoomObj(dungeon d)
{
    playerXLoc =d.rooms[0].xLoc + 1;
    playerYLoc =d.rooms[0].yLoc + 1;
    d.map[playerYLoc][playerXLoc].icon = playerTile;

    d.numUpStair = 1;
    d.numDownStair = 1;
    int downNum = getRandInt(0, d.roomNum - 1);
    int upNum = getRandInt(0, d.roomNum - 1);
    while(upNum == downNum)
    {
        upNum = 0;
        upNum = getRandInt(0, d.roomNum - 1);
    }
    int xStair = getRandInt(1, (d.rooms[downNum].xSize) - 2);
    int yStair = getRandInt(1, (d.rooms[downNum].ySize) - 2);
    d.map[d.rooms[downNum].yLoc + yStair][d.rooms[downNum].xLoc + xStair].icon = downstairTile;
    d.downStairs[0].xLoc = d.rooms[downNum].xLoc + xStair;
    d.downStairs[0].yLoc = d.rooms[downNum].yLoc + yStair;
    xStair = getRandInt(1, (d.rooms[upNum].xSize) - 2);
    yStair = getRandInt(1, (d.rooms[upNum].ySize) - 2);
    d.map[d.rooms[upNum].yLoc + yStair][d.rooms[upNum].xLoc + xStair].icon = upstairTile;
    d.upStairs[0].xLoc = d.rooms[upNum].xLoc + xStair;
    d.upStairs[0].yLoc = d.rooms[upNum].yLoc + yStair;
    return d;
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
dungeon loadFromFile(dungeon d, char *path)
{

    int i, j, k;
    //Endian Start

    //printf("%s", path);
    FILE *f = fopen(path, "r");
    if(f != NULL)
    {
        unsigned char semantic[13];
        semantic[12] = '\0';
        fread(semantic, 1, 12, f);

        unsigned int version;
        fread(&version, 4, 1, f);

        unsigned int size;
        fread(&size, 4, 1, f);
        //printf("size: %d, %d", size, version);
        int8_t playerLoc[2];
        fread(playerLoc, 1, 2, f);
        playerXLoc = playerLoc[0];
        playerYLoc = playerLoc[1];
        fread(d.hardness, 1, sizeX * sizeY, f);

        fread(&d.roomNum, 2, 1, f);
        d.roomNum = be16toh(d.roomNum);

        d.rooms= malloc(d.roomNum * sizeof(room));
        for (int j = 0; j < d.roomNum; j ++) {
            fread(&d.rooms[j].xLoc, 1, 1, f);
            fread(&d.rooms[j].yLoc, 1, 1, f);
            fread(&d.rooms[j].xSize, 1, 1, f);
            fread(&d.rooms[j].ySize, 1, 1, f);
            //printf("Room %d: %d, %d, %d, %d\n", j, d.rooms[j].xLoc, d.rooms[j].yLoc, d.rooms[j].xSize, d.rooms[j].ySize);
        }
        fread(&d.numUpStair, 2, 1, f);
        d.numUpStair = be16toh(d.numUpStair);

        int8_t uLocations[2 * d.numUpStair];//add numUpStair *
        fread(uLocations, 1, d.numUpStair * 2, f);

        fread(&d.numDownStair, 2, 1, f);
        d.numDownStair = be16toh(d.numDownStair);


        int8_t dLocations[2 * d.numDownStair]; //add numDownStair *
        fread(dLocations, 1, d.numDownStair * 2, f);
        fclose(f);
        for(i = 1; i < sizeY; i++)
        {
            for(j = 1; j < sizeX; j++)
            {
                if(d.hardness[i][j] == 0)
                {
                    d.map[i][j].icon = corridorTile;
                }
                else
                {
                    d.map[i][j].icon = rockTile;
                }
            }
        }
        for(k = 0; k < d.roomNum; k++) {
            for (i =d.rooms[k].yLoc; i <d.rooms[k].yLoc +d.rooms[k].ySize; i++) {
                for (j =d.rooms[k].xLoc; j <d.rooms[k].xLoc +d.rooms[k].xSize; j++) {
                    d.map[i][j].icon = floorTile;
                }
            }
        }
        //printf("numUpStair: %d\nnumDwnStair: %d\n", d.numUpStair, d.numDownStair);
        for(i = 0; i < d.numUpStair*2; i += 2)
        {
            //printf("up: %d, %d\n", uLocations[i], uLocations[i + 1]);
            d.map[uLocations[i + 1]][uLocations[i]].icon = upstairTile;
        }
        for(i = 0; i < d.numDownStair*2; i += 2)
        {
            //printf("down: %d, %d\n", dLocations[i], dLocations[i + 1]);
            d.map[dLocations[i + 1]][dLocations[i]].icon = downstairTile;
        }

        d.map[playerYLoc][playerXLoc].icon = playerTile;
    }

    return d;
}
void saveToFile(dungeon d, char *path)
{
    //printf("stair nuums: %d, %d", d.numUpStair, d.numDownStair);
    int i, j;

    FILE *fh = fopen (path, "w");
    if (fh != NULL) {
        unsigned char semantic[] = "RLG327-S2021";
        fwrite (semantic, 1, 12, fh);
        unsigned int version = 0;
        fwrite (&version, 4, 1, fh);
        unsigned int size = 1704 + (d.roomNum * 4) + (d.numUpStair * 2) + (d.numDownStair *2);
        fwrite (&size, 4, 1, fh);

        fwrite (&playerXLoc, 1, 1, fh);

        fwrite(&playerYLoc, 1, 1, fh);

        fwrite(d.hardness, 1, sizeX * sizeY, fh);
        u_int16_t temp = be16toh(d.roomNum);;
        fwrite(&temp, 2, 1, fh);
        for(i = 0; i < d.roomNum; i++) {
            fwrite(&d.rooms[i].xLoc, 1, 1, fh);
            fwrite(&d.rooms[i].yLoc, 1, 1, fh);
            fwrite(&d.rooms[i].xSize, 1, 1, fh);
            fwrite(&d.rooms[i].ySize, 1, 1, fh);
            //printf("Room %d: %d, %d, %d, %d\n", i, d.rooms[i].xLoc,d.rooms[i].yLoc,d.rooms[i].xSize,d.rooms[i].ySize);
        }
        temp = be16toh(d.numUpStair);
        fwrite(&temp, 2, 1, fh);

        j = 0;
        for(i = 0; i < d.numUpStair * 2; i += 2)
        {
            fwrite(&d.upStairs[j].xLoc, 1, 1, fh);
            fwrite(&d.upStairs[j].yLoc, 1, 1, fh);
            //printf("up: %d, %d\n", d.upStairs[j].xLoc, d.upStairs[j].yLoc);
            j++;
        }
        temp = be16toh(d.numDownStair);
        fwrite(&temp, 2, 1, fh);

        j = 0;
        for(i = 0; i < d.numDownStair * 2; i += 2)
        {
            fwrite(&d.downStairs[j].xLoc, 1, 1, fh);
            fwrite(&d.downStairs[j].yLoc, 1, 1, fh);
            //printf("dwn: %d, %d\n", d.downStairs[j].xLoc, d.downStairs[j].yLoc);
            j++;
        }

        fclose (fh);
    }
}