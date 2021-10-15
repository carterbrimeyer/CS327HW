
typedef struct {
    unsigned int xLoc;
    unsigned int yLoc;
    unsigned int xSize;
    unsigned int ySize;
    bool connected;
} room;

typedef struct {
    unsigned char icon;
    unsigned int hardness;
} tile;

void printMap();

void generateRooms();

int getRandInt(int lower, int upper);

void generatePaths(int roomNum, room rooms[roomNum]);

int roomIntersect(room a, room b);

void generateRoomObj(int roomNum, room rooms[roomNum]);

void buildPath(int ax, int ay, int bx, int by, int closeRoom, int roomNum, room rooms[roomNum]);
