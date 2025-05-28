

 SDL_Surface* viewer=NULL;
 SDL_Surface* screen=NULL;
 SDL_Surface* drawingsurface=NULL;
SDL_Surface* message=NULL;

TTF_Font *font;
Uint16 mouseX, mouseY;
Uint16 pmouseX, pmouseY;
Uint16 width, height, sheight;
Uint16 vwidth, vheight, mheight;
bool mousePressed;
bool pmousePressed;
bool quit;
bool first=true;
bool rescon=false;
Uint32 color=0xff000000;
SDL_Color sdlcolor={0, 0, 0, 0};
int targetrate=1000;
bool capframe=true;
int searchcount=0;

void apply_surface(int x, int y,SDL_Surface* screen,SDL_Rect* clip);
bool overRect(float, float, float, float, float, float);
float random(float, float);
void drawMenu(void);
void spigot(int type, int scount, int num, int hei, int wid);
void update(void);
void pset(int i);
int pixels(int i);
void pixels(int, int);
bool combineRule(int, int, int , float);
bool growRule(int, int, float);
bool risingRule(int, bool);
bool fallingRule(int, bool);
bool fallingRule3(int, bool);
bool densityRule(int, int, float);
void doOilFire(int);
void doSpigot(int, int, float);
void doSpigot2(int, int, float);
int touchingDirect(int, int);
int touching(int, int);
int adjacent(int, int);
int above(int, int);
int below(int, int);
int aboveD(int, int);
int belowD(int, int);
void change(int, int);
int compoundHor(int i, int search);
int compoundVer(int i, int search);
int floodSearch(int, int);
void compoundFull(int i, int search, int replace, float chance);
void explosion(int);
void doNapalm(int);
void doC4(int);
void doGunpowder(int);
void doOilFire2(int, int);
int max(int, int);
int min(int, int);

void processEvents(void);
void processSand(void);
void resize(void);

//element definitions
    int SAND = 0xffeecc80;
    int WATER = 0xff2020ff;
    int FIRE = -49088;
    int WALL = 0xff808080;
    int PLANT = 0xff20cc20;
    int SPOUT = 0xff70a0ff;
    int TORCH = 0xfff54b0f;
    int WELL = 0xff3b1010;
    int NITRO = 0xff347606;
    int NAPA= 0xffe8a21e;
    int GUNP= 0xff9d866e;
    int CONC= 0xff8ba2a2;
    int C4= 0xfffaf29c;
    int ICE = 0xffb9d5ff;
    int CERA = 0xffeeddcc;
    int CERA2 = 0xffeeddcd;
    int OIL = 0xff804040;
    int SALTWATER = 0xff4080ff;
    int SALT = -1;
    int METH = 0xff090909;
    int BLANK=0xff000001;
    int FLASH=0xfffffafa;
    int ARBIT=0xff7853ce;
    int pen_type=0;


    int resource_n=17;
    char *resource_text []={
     "WALL", "FIRE", "WATER", "PLANT", "SAND", "SALT","WAX","OIL",
     "SPOUT", "METHANE", "NITRO", "NAPALM", "GUNPOWDER","C-4", "TORCH","CONCRETE","ERASER"
    };
    int resource_color []={
    WALL, FIRE, WATER, PLANT, SAND, SALT, CERA, OIL, SPOUT, METH, NITRO, NAPA,  GUNP,C4,TORCH, CONC, BLANK
    };
    char *menu_text []={
      "PEN-size: x", "SAND: x", "WATER: x", "SALT: x",
      "OIL: x", "Time: x",  "Ground On: ", "XavierSoft: "
    };

#ifdef RESCON
int menu_n=10;
#else
    int menu_n=8;
    #endif
    int menu_values [][7]={
     {1, 2, 4, 8, 16, 24, 32},
     {0, 1, 2, 3, 4, 5},
     {0, 1, 2, 3, 4, 5},
     {0, 1, 2, 3, 4, 5},
     {0, 1, 2, 3 ,4 , 5},
     {0, 1, 2, 3, 4},
     {0, 1},
     {0}
      #ifdef RESCON
      ,
     {320, 640},
     {640,1280},
     #endif
    };

    int resheights []={200, 400};
    int sizheights []={480, 880};

     char *menu_val_text [][7]={
     {"PEN-size: x1", "PEN-size: x2", "PEN-size: x4", "PEN-size: x8", "PEN-size: x16", "PEN-size: x24", "PEN-size: x32"},
     {"SAND: x0", "SAND: x1", "SAND: x2", "SAND: x3", "SAND: x4", "SAND: x5"},
     {"WATER: x0", "WATER: x1", "WATER: x2", "WATER: x3", "WATER: x4", "WATER: x5"},
     {"SALT: x0", "SALT: x1", "SALT: x2", "SALT: x3" ,"SALT: x4" , "SALT: x5"},
     {"OIL: x0", "OIL: x1", "OIL: x2", "OIL: x3", "OIL: x4", "OIL: x5"},
     {"Time: x0", "Time: x1", "Time: x2", "Time: x3", "Time: x4"},
     {"Ground off", "Ground on"},
     {"XavierSoft"}
          #ifdef RESCON
          ,
    {"Res: 320x160", "Res: 640x400"},
     {"Size: 640x480", "Size:1280x880"}
      #endif
    };


    int menu_count []={1, 1, 1, 1, 1, 1, 0, 0, 0, 0};
    int menu_max []={7, 6, 6, 6, 6, 5, 2, 1, 2, 2};



//utility methods
void setColor(int color);
void drawLine(int x1, int y1, int x2, int y2);
void drawLine(int x1, int y1, int x2, int y2, int w);
void drawRect(int x, int y, int w, int h);
void fillRect(int x, int y, int w, int h);
void fillCirc(int x, int y, int rad);
void drawString(char* utf, int x, int y);
