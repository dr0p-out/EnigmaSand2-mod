#ifndef EnigmaSandDefs_h
#define EnigmaSandDefs_h

#include <SDL.h>
#include <SDL_ttf.h>

extern SDL_Surface *viewer;
extern SDL_Surface *screen;
extern SDL_Surface *drawingsurface;

extern TTF_Font *font;
extern Uint16 mouseX, mouseY;
extern Uint16 pmouseX, pmouseY;
extern Uint16 width, height, sheight;
extern Uint16 vwidth, vheight, mheight;
extern bool mousePressed;
extern bool pmousePressed;
extern bool quit;
extern bool first;
extern bool rescon;
extern Uint32 color;
extern SDL_Color sdlcolor;
extern int targetrate;
extern bool capframe;
extern int searchcount;

void apply_surface(int x, int y, SDL_Surface *screen, SDL_Rect *clip);
bool overRect(float, float, float, float, float, float);
float random(float, float);
void drawMenu(void);
void spigot(int type, int scount, int num, int hei, int wid);
void update(void);
void pset(int i);
int pixels(int i);
void pixels(int, int);
bool combineRule(int, int, int, float);
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

// element definitions
const int SAND = 0xffeecc80;
const int WATER = 0xff2020ff;
const int FIRE = -49088;
const int WALL = 0xff808080;
const int PLANT = 0xff20cc20;
const int SPOUT = 0xff70a0ff;
const int TORCH = 0xfff54b0f;
const int WELL = 0xff3b1010;
const int NITRO = 0xff347606;
const int NAPA = 0xffe8a21e;
const int GUNP = 0xff9d866e;
const int CONC = 0xff8ba2a2;
const int C4 = 0xfffaf29c;
const int ICE = 0xffb9d5ff;
const int CERA = 0xffeeddcc;
const int CERA2 = 0xffeeddcd;
const int OIL = 0xff804040;
const int SALTWATER = 0xff4080ff;
const int SALT = -1;
const int METH = 0xff090909;
const int BLANK = 0xff000001;
const int FLASH = 0xfffffafa;
const int ARBIT = 0xff7853ce;

// utility methods
void setColor(int color);
void drawLine(int x1, int y1, int x2, int y2);
void drawLine(int x1, int y1, int x2, int y2, int w);
void drawRect(int x, int y, int w, int h);
void fillRect(int x, int y, int w, int h);
void fillCirc(int x, int y, int rad);
void drawString(const char *utf, int x, int y);

#endif
