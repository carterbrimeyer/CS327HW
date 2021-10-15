#define sizeX       80
#define sizeY       21
#define minRoomX    4
#define minRoomY    3
#define minRoomNum  6
#define maxRoomX    10
#define maxRoomY    10
#define maxRoomNum  12

const char corridorTile = '#';
const char floorTile = '.';
const char rockTile = ' ';
const char upstairTile = '<';
const char downstairTile = '>';
const char playerTile = '@';

typedef struct {
    u_int8_t xLoc;
    u_int8_t yLoc;
    u_int8_t xSize;
    u_int8_t ySize;
    bool connected;
} room;

typedef struct {
    unsigned char icon;
} tile;

typedef struct {
    unsigned int xLoc;
    unsigned int yLoc;
} stair;
typedef struct {
    u_int16_t roomNum;
    room *rooms;
    tile **map;
    u_int8_t hardness[sizeY][sizeX];
    stair upStairs[1];
    u_int16_t numUpStair;
    stair downStairs[1];
    u_int16_t numDownStair;
}dungeon;

void printMap(dungeon d);

dungeon generateRooms(dungeon d);

int getRandInt(int lower, int upper);

dungeon generatePaths(dungeon d);

int roomIntersect(room a, room b);

dungeon generateRoomObj(dungeon d);

dungeon loadFromFile(dungeon d, char *path);

void saveToFile(dungeon d, char *path);


