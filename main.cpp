#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#define RESCON
#define CUSTOM

#include <ctime>
#include <SDL.h>
#include <SDL_ttf.h>
//#include "EnigmaSand2.h"
#include "EnigmaSandDefs.h"
#include "EnigmaSandParticle.h"


 SDL_Surface* viewer=nullptr;
 SDL_Surface* screen=nullptr;
 SDL_Surface* drawingsurface=nullptr;

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

    int pen_type=0;


    int resource_n=17;
    const char *resource_text []={
     "WALL", "FIRE", "WATER", "PLANT", "SAND", "SALT","WAX","OIL",
     "SPOUT", "METHANE", "NITRO", "NAPALM", "GUNPOWDER","C-4", "TORCH","CONCRETE","ERASER"
    };
    int resource_color []={
    WALL, FIRE, WATER, PLANT, SAND, SALT, CERA, OIL, SPOUT, METH, NITRO, NAPA,  GUNP,C4,TORCH, CONC, BLANK
    };
    const char *menu_text []={
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

     const char *menu_val_text [][7]={
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



int main(void){
    int eframe, bframe;
    int quitValue;

    if(SDL_Init(SDL_INIT_VIDEO)==-1){ fprintf(stderr, "Cannot init sdl video\n"); return 1;}
atexit(SDL_Quit);
    SDL_WM_SetCaption("EnigmaSand2", "EnigmaSand");


   #ifdef RESCON
    viewer = SDL_SetVideoMode(menu_values[9][menu_count[9]], sizheights[menu_count[9]], 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

    screen=SDL_CreateRGBSurface(SDL_HWSURFACE,menu_values[8][menu_count[8]], resheights[menu_count[8]], 32,
    viewer->format->Rmask,
    viewer->format->Gmask,
    viewer->format->Bmask,
    viewer->format->Amask);
    drawingsurface=screen;
   #else
 viewer = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
   screen=viewer;
   drawingsurface=screen;
   #endif


    TTF_Init();
    if(!(font=TTF_OpenFont("tahoma.ttf", 16))){ fprintf(stderr, "Cannot open ttf font file\n"); quitValue = 1; goto quit_no_font;}

    pmouseX=pmouseY=mouseX=mouseY=0;
    pmousePressed=mousePressed=false;
    quit=false;
    width=screen->w;
    height=screen->h;
    #ifdef RESCON
    sheight=height;
    #else
    sheight=height-80;
    #endif
    vwidth=viewer->w;
    vheight=viewer->h;
    mheight=vheight-80;
    srand((unsigned)time( nullptr ) );



    for(int i=0; i<1000; i++){
     particles[i]=(new Particle());
    }


    eframe=0, bframe=0;;


while(!quit){
    bframe=SDL_GetTicks();
processEvents();
processSand();
#ifdef RESCON
SDL_Rect destin;
destin.x=0;
destin.y=0;
destin.w=vwidth;
destin.h=mheight;

//SDL_BlitSurface(screen, &destin, viewer,nullptr);
drawingsurface=viewer;
if(width!=vwidth){
    int scaler=vwidth/width;
for(int i=0; i<width*height; i++){
    setColor(pixels(i));
    fillRect( (i%width)*scaler, (i/width)*scaler, scaler, scaler);
}
}else{
  SDL_BlitSurface(screen, &destin, viewer,nullptr);
}
drawingsurface=screen;
#endif

      if(SDL_MUSTLOCK(viewer)){
    SDL_UnlockSurface(viewer);
    SDL_UpdateRect(viewer, 0, 0, 0, 0);
    SDL_LockSurface(viewer);
      }else{
         SDL_UpdateRect(viewer, 0, 0, 0, 0);
      }

pmousePressed=mousePressed;
pmouseX=mouseX;
pmouseY=mouseY;
 eframe=SDL_GetTicks();
 if(capframe){while(eframe-bframe<(1000/targetrate)){ eframe=SDL_GetTicks();}}

}

      quitValue=0;
      TTF_CloseFont(font);
quit_no_font:
      SDL_FreeSurface(viewer);
      SDL_FreeSurface(screen);
      TTF_Quit();
      SDL_Quit();

      return quitValue;
}

void processEvents(void){
       SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                quit=true;
                break;
            case SDL_MOUSEBUTTONDOWN:
            mousePressed=true;
            break;
            case SDL_MOUSEBUTTONUP:
             mousePressed=false;
            break;
            case SDL_MOUSEMOTION:
            #ifdef RESCON
            if(event.button.y>mheight){
             mouseX=event.button.x;
             mouseY=event.button.y;}else{
                     int scaler=vwidth/width;
                mouseX=(event.button.x/scaler);
                mouseY=(event.button.y/scaler);
             }
             #else
                mouseX=event.button.x;
                mouseY=event.button.y;
            #endif
            break;
             case SDL_VIDEORESIZE:
             screen=SDL_SetVideoMode(event.resize.w, event.resize.h, 32,SDL_HWSURFACE|SDL_RESIZABLE);
             width=event.resize.w;
             height=event.resize.h;
             sheight=height-80;
             setColor(BLANK);
             fillRect(0, 0, width, height);
             break;
            } // end switch
                                if( event.type == SDL_KEYDOWN ) { //If enter was pressed
                    if( event.key.keysym.sym == SDLK_RETURN ) { //Switch cap
                    capframe = ( !capframe ); } }
        } // end of message processing

}

void processSand(void){
if(first){
    setColor(BLANK);
    fillRect(0, 0, width, height); printf("MADE IT");  drawMenu(); first=false;return;}

drawMenu();
if(pmousePressed&&mousePressed &&mouseY<sheight){
    setColor(resource_color[pen_type]);
drawLine(mouseX, mouseY, pmouseX, pmouseY, menu_values[0][menu_count[0]]);
}


	for(int i=0; i<menu_count[5]; i++){
#if 0
spigot(SAND, 4, 1, 15, 5*menu_values[1][menu_count[1]]);
spigot(WATER, 4, 2, 15, 5*menu_values[2][menu_count[2]]);
spigot(SALT, 4, 3, 15, 5*menu_values[3][menu_count[3]]);
spigot(OIL, 4, 4, 15, 5*menu_values[4][menu_count[4]]);
#endif

    setColor(WALL);
    drawLine(0, 0, 0, height, 1);
    drawLine(width, 0, width, height, 1);

    if( menu_count[6]==0){setColor(BLANK);}
drawLine(0, sheight, width, sheight,1);
    		for(int j=0; j<1000; j++){
			(*particles[j]).drawParticle();
        }

    update();

	}

}

void drawMenu(void){
    drawingsurface=viewer;
	  int location=0;
	setColor(0xff3c3c3c);
	//stroke(60F, 120F, 200F);
	fillRect(0, mheight, vwidth, vheight-mheight);

	for(int i=0; i<resource_n; i++){
	 //if(pen_type==resource_color[i]){noFill(); stroke(255); rect((location/5)*80, mheight+(location%5)*16, 80, 16);}
	 setColor(resource_color[i]);
	 drawString(resource_text[i], (int)((location/5)*80), mheight+(location%5)*16);
	 location++;
	}
	int xofset=(int)((location/5)*80)+80;
	location=0;
	for(int i=0; i<menu_n; i++){
	setColor(-128);
    drawString(menu_val_text[i][menu_count[i]], xofset+(location/5)*100, mheight+(location%5)*16);
	 location++;
	}

	if(overRect( 0, mheight, (((float)resource_n)/5+1)*80, 80, mouseX, mouseY)){
	  int index=(mouseX/80)*5+(mouseY-mheight)/16;
	  if(index<resource_n){
	  //if(index<resource_text.length && index>0){
	  setColor(BLANK);
	  fillRect( (index/5)*80,  mheight+(index%5)*16, 80, 16);  if(mousePressed){pen_type=index;}
	  setColor(255);
	  drawString(resource_text[index], (int)((index/5)*80), mheight+(index%5)*16);}
	}else if(mousePressed&&!pmousePressed){

	 int index=(int)(((mouseX-xofset)/90)*5)+(mouseY-mheight)/16;
	  if(overRect(xofset, mheight, (((float)menu_n)/5+1)*100, 80, mouseX, mouseY)){
	    if(index<menu_n)
	    menu_count[index]=(menu_count[index]+1)%(menu_max[index]);}

#ifdef RESCON
	    if(index==8 || index==9){resize();}
#endif
	 //if(!checkresource&&overRect(xofset+(location/5)*90, mheight+(location%5)*16, 90, 16,mouseX, mouseY)){
	 //if(mousePressed&&!pmousePressed){menu_count[i]=(menu_count[i]+1)%(menu_values[i].length);}}
	}
	setColor(0xffffffff); drawRect((pen_type/5)*80, mheight+(pen_type%5)*16, 80, 16);
	setColor(resource_color[pen_type]);
	drawString(resource_text[pen_type], (int)((pen_type/5)*80), mheight+(pen_type%5)*16);
	drawingsurface=screen;
	}

#ifdef RESCON
void resize(void){
    viewer = SDL_SetVideoMode(menu_values[9][menu_count[9]], sizheights[menu_count[9]], 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

    screen=SDL_CreateRGBSurface(SDL_HWSURFACE,menu_values[8][menu_count[8]], resheights[menu_count[8]], 32,
    viewer->format->Rmask,
    viewer->format->Gmask,
    viewer->format->Bmask,
    viewer->format->Amask);
    drawingsurface=screen;


    width=screen->w;
    height=screen->h;
    sheight=height;
    vwidth=viewer->w;
    vheight=viewer->h;
    mheight=vheight-80;
    setColor(BLANK);
    fillRect(0, 0, vwidth, vheight);
}
#endif


	void spigot(int type, int scount, int num, int hei, int wid){
setColor(type);
	 	int offset=(width/(scount+1))*num;
	for(int y=0; y<hei; y++){
	for(int x=0; x<wid; x++){
	  if( random(0.0F, 1.0F)<0.1F){
	    drawRect(offset+x, y, 1, 1);
	  }
	}
}
	}


void update(void){
	   for(int y=sheight; y>=0; y--){
		     if( (y&1)==1){
		  for(int x=1; x<width-1; x++){
		    //if(pixels[i]!=0){pixels[i+width]=pixels[i]; pixels[i]=0xff000000;}
		    if(pixels(y*width+x)==BLANK ){continue;}
		    pset(y*width+x);
		  }
		     }else{
		        for(int x=width-2; x>1; x--){
		    //if(pixels[i]!=0){pixels[i+width]=pixels[i]; pixels[i]=0xff000000;}
		    if(pixels(y*width+x)==BLANK){continue;}
		    pset(y*width+x);
		  }
		 }
	   }
}

void pset(int i){
    int loc=0;
    int loc2=0;
    switch(pixels(i)){
case (int)0xffeeddcc:return;
case (int)0xff808080:return;
case (int)0xff347606://nitro
    if(random(0.0F, 1.0F)<0.3F && (touching(i, FIRE))>-1){explosion(i); return;}
    if(random(0.0F, 1.0F)<0.2F && (touching(i, FIRE))>-1){pixels(i,FIRE);}
    if(fallingRule(i, true)){ return;}
    if(densityRule(i, OIL, 0.25F)){return;}
    if(densityRule(i, WATER, 0.25F)){return;}
    return;
case  (int)0xffeecc80://sand
	  if(fallingRule(i, true)){ return;}
	  if(densityRule(i, WATER, 0.25F)){return;}
	          	  if(densityRule(i, METH, 0.4F)){return;}
	  return;
	case  (int)0xff2020ff: //water
	  if( combineRule( i, SALT, SALTWATER, 0.25F)){return;}
	    if(densityRule(i, OIL, 0.25F)){return;}
	  if( fallingRule(i, true)){return;}
	          	  if(densityRule(i, METH, 0.4F)){return;}
	  return;
	case  -1://salt
	  if(fallingRule(i, true)){ return;}
	          	  if(densityRule(i, METH, 0.4F)){return;}
	  return;
	case (int)0xff804040://oil
	  if( random(0.0F, 1.0F)<0.30F &&(loc=touchingDirect(i, FIRE))!=-1){ doOilFire(i); return;}
	  if( fallingRule(i, true)){return;}
	          	  if(densityRule(i, METH, 0.4F)){return;}
	  return;
	case (int)0xff4080ff://salt water
	  if( fallingRule(i, true)){return;}
	  if(densityRule(i, WATER, 0.50F)){return;}
	          	  if(densityRule(i, METH, 0.4F)){return;}
	  return;
	case (int)0xff20cc20://plant
	  if( growRule(i, WATER, 0.50F)){return;}
	  return;
	case -49088://fire
	  if(random(0.0F, 1.0F)<0.2F && (loc=touching(i, PLANT))!=-1 ){pixels(loc,FIRE); return;}
	  if(random(0.0F, 1.0F)<0.01F && (loc=touchingDirect(i, CERA))!=-1 ){pixels(i,FIRE); pixels(loc,FIRE);
	  if( (loc2=below(max(i, loc), BLANK))!=-1){pixels(loc2,CERA2);}
	  return;}
	  if( random(0.0F, 1.0F)<0.4F &&( touching(i, PLANT)==-1 && touchingDirect(i, CERA)==-1) ){pixels(i,BLANK); return;}
	  if( random(0.0F, 1.0F)<0.8F &&(loc=touching(i, WATER))!=-1){pixels(loc,BLANK); pixels(i,BLANK);return;}
	  if( random(0.0F, 1.0F)<0.5F &&(loc=above(i, BLANK))>-1){ pixels(loc,FIRE);}
	  return;
	case (int)0xffeeddcd://falling cera
	   if( (loc=belowD(i, BLANK))!=-1){ change(i, loc);return;}else{pixels(i,CERA);}
	  return;
	case (int)0xff70a0ff://spout
	   doSpigot(i, WATER, 0.05F);
	  return;
	case (int)0xff8ba2a2://concrete
		  if(densityRule(i, WATER, 0.35F)){return;}
		  if(fallingRule3(i, true)){return;}else{
		  if((belowD(i, WALL)>-1 || adjacent(i, WALL)>-1) && random(0.0F, 1.0F)<0.1F){pixels(i,WALL);}
		  if(random(0.0F, 1.0F)<0.001){pixels(i,WALL);}
		  }
		 return;
    case (int)0xffe8a21e://napalm
		   if(random(0.0F, 1.0F)<0.25F && (touchingDirect(i, FIRE))>-1){doNapalm(i);}
		   if(fallingRule(i, true)){return;}//else{doNapalm(i);}
		           	  if(densityRule(i, METH, 0.4F)){return;}
		return;
	case (int)0xff9d866e://gunpowder
		  if(random(0.0F, 1.0F)<0.95F && (touchingDirect(i, FIRE))>-1){doGunpowder(i);return;}
		  if(fallingRule(i, true)){return;}
		          	  if(densityRule(i, METH, 0.4F)){return;}
		return;
	case (int)0xfffaf29c://C-4
		  if(random(0.0F, 1.0F)<0.6F && (touchingDirect(i, FIRE))>-1){doC4(i);}
		return;
    case (int)0xff090909://methane
		   if(random(0.0F, 1.0F)<0.25F && (touchingDirect(i, FIRE))>-1){doNapalm(i);}
        if(risingRule(i, true)){return;}

        return;
    case (int)0xfff54b0f://torch
  doSpigot2(i, FIRE, 0.25F);
  return;
    }
}

bool combineRule(int i, int comcolor, int resultcolor, float chance){
	 int loc=0; if( random(0.0F, 1.0F)<chance && ( (loc=below(i, comcolor))!=-1||(loc=adjacent(i, comcolor))!=-1||(loc=above(i, comcolor))!=-1 ) ){
	  pixels(i,BLANK);
	  pixels(loc,resultcolor); return true;
	 }
	 return false;
	}

bool growRule(int i, int comcolor, float chance){
	 int loc=0; if( random(0.0F, 1.0F)<chance &&( (loc=belowD(i, comcolor))!=-1||(loc=adjacent(i, comcolor))!=-1||(loc=aboveD(i, comcolor))!=-1 ) ){
	  pixels(loc,pixels(i)); return true;
	 }
	 return false;
	}

	bool risingRule(int i, bool adj){
		  (void)adj;

		  int loc=belowD(i, BLANK);

		   if( random(0.0F, 1.0F)<0.25F &&( (loc=aboveD(i, BLANK))!=-1||(loc=adjacent(i, BLANK))!=-1)){

		       change(i, loc);return true;
            }
		   //if( random(0.0F, 1.0F)<0.25F && (loc=adjacent(i, BLANK))!=-1){ change(i, loc);return true;}
		   return false;
}

bool fallingRule(int i, bool adj){
		  (void)adj;

		  int loc=belowD(i, BLANK);

		   if( random(0.0F, 1.0F)<0.95F &&( (loc=belowD(i, BLANK))!=-1||(loc=adjacent(i, BLANK))!=-1)){

		       change(i, loc);return true;
            }
		   //if( random(0.0F, 1.0F)<0.25F && (loc=adjacent(i, BLANK))!=-1){ change(i, loc);return true;}
		   return false;
}

bool fallingRule3(int i, bool adj){
	  (void)adj;

	  int loc=0;
	   if( random(0.0F, 1.0F)<0.95F &&( (loc=belowD(i, BLANK))!=-1||(loc=adjacent(i, BLANK))!=-1)){
	       change(i, loc);return true;}
	   if( random(0.0F, 1.0F)<0.95F && belowD(i, CONC)!=-1){return true;}
	   //if( random(0.0F, 1.0F)<0.25F && (loc=adjacent(i, BLANK))!=-1){ change(i, loc);return true;}
	   return false;
}


bool densityRule(int i, int comcolor, float chance){
	   int loc=0; if( random(0.0F, 1.0F)<chance && (loc=belowD(i, comcolor))!=-1){
	  pixels(loc,pixels(i));
	  pixels(i,comcolor); return true;
	 }
	 return false;
	}

void explosion(int i){
	 int j=0;
	 for(j=0; j<1000; j++){
	 if(!(*particles[j]).active){break;}
	 }
	 if(j==1000){return;}
	 doOilFire(i);
	 //ProjectileBehavior pb=new ProjectileBehavior();
	 //pb.initiate(i%width, int(i/width), FIRE_COLOR, int(random(2, 10)) );
	 (*particles[j]).initiate(i, 0);
	}


	void doNapalm(int i){
	 int j=0;
	 for(j=0; j<1000; j++){
	 if(!(*particles[j]).active){break;}
	 }
	 if(j==1000){return;}
	 (*particles[j]).initiate(i, 1);
	}

	void doC4(int i){
	   int j=0;
	 for(j=0; j<1000; j++){
	 if(!(*particles[j]).active){break;}
	 }
	 if(j==1000){doOilFire(i);return;}
	  (*particles[j]).initiate(i, 3);
	}

	void doOilFire2(int i, int avoid){
	 if(i-width>-1) {if(pixels(i-width)!=avoid || random(0.0F, 1.0F)<0.5F){ pixels(i-width,FIRE);}}
	 if( pixels(i+width)!=avoid|| random(0.0F, 1.0F)<0.5F){pixels(i+width,FIRE);}
	 if( pixels(i+1)!=avoid|| random(0.0F, 1.0F)<0.5F){pixels(i+1,FIRE);}
	  if( pixels(i-1)!=avoid|| random(0.0F, 1.0F)<0.5F){pixels(i-1,FIRE);}
	 pixels(i,FIRE);
	}

	void doGunpowder(int i){
	  bool fire=(random(0.0F, 1.0F)<0.4F);
	 if(i-width>-1){ if(fire){doOilFire2(i-width, GUNP);}else{pixels(i-width,GUNP);}}
	 if(fire){doOilFire2(i+width, GUNP );
	 doOilFire2(i+1, GUNP);
	 doOilFire2(i-1, GUNP);}else{ pixels(i+width,GUNP); pixels(i+1,GUNP); pixels(i-1,GUNP);}
	}

	void doOilFire(int i){
	 if(i-width>-1){ pixels(i-width,FIRE);}
	 pixels(i+width,FIRE);
	 pixels(i+1,FIRE);
	 pixels(i-1,FIRE);
	 pixels(i,FIRE);
	}


	void doSpigot(int i, int type, float rate){
	  if(random(0.0F, 1.0F)<rate){
	 if(i-width>-1 && pixels(i-width)==BLANK){ pixels(i-width,type);}
	 if(pixels(i+width)==BLANK)pixels(i+width,type);
	 if(pixels(i+1)==BLANK) pixels(i+1,type);
	 if(pixels(i-1)==BLANK) pixels(i-1,type);}
	}

void doSpigot2(int i, int type, float rate){
  if(random(0.0F, 1.0F)<rate){
 if(i-width>-1 ){ pixels(i-width,type);}
pixels(i+width,type);
 pixels(i+1,type);
pixels(i-1,type);}
}



	int touchingDirect(int i, int type){
	 int loc=0;
	 if( (loc=adjacent(i, type))!=-1 || (loc=below(i, type))!=-1 ||(loc=above(i, type))!=-1 ){return loc;}
	 return -1;
	}

	int touching(int i, int type){
	 int loc=0;
	 if( (loc=adjacent(i, type))!=-1 || (loc=belowD(i, type))!=-1 ||(loc=aboveD(i, type))!=-1 ){return loc;}
	 return -1;
	}

	int adjacent(int i, int type){
	  int loc=0;
	  if( pixels( loc=(i-1))==type &&pixels(loc=(i+1))==type){ return (random(0.0F, 1.0F)<0.5F?i-1:i+1);}
	  if(pixels(loc=(i-1))==type){return loc;}
	  if(pixels(loc=(i+1))==type){return loc;}
	  return -1;
	}

	int above(int i, int type){
	  int loc=0;
	if(i-width<0){if(type==BLANK){return i-width;}else{return -1;}}
	if(pixels(loc=(i-width))==type){return loc;}
	return -1;
	}

	int below(int i, int type){
	  int loc=0;
	if(i+width>sheight*width && type==BLANK){return i+width;}
	if(pixels(loc=(i+width))==type){return loc;}
	return -1;
	}

	int aboveD(int i, int type){
	  int loc=0;
	if(i-width-1<0){if(type==BLANK){return i-width;}else{return -1;}}
	if(pixels(loc=(i-width))==type || pixels(loc=(i-width-1))==type || pixels(loc=(i-width+1))==type){return loc;}
	return -1;
	}

	int belowD(int i, int type){
	  int loc=0;
	if(i+width>sheight*width && type==BLANK){return i+width;}
	if(pixels(loc=(i+width))==type || pixels(loc=(i+width-1))==type || pixels(loc=(i+width+1))==type){return loc;}
	return -1;
	}

	void change(int i, int loc){
		 if(i<sheight*width && i>0){
		  if(loc<sheight*width && loc>0){ int x=pixels(i); pixels(i, pixels(loc)); pixels(loc,x);}else{ pixels(i,BLANK);}
		 }else{
		   if(loc<sheight*width && loc>0){ pixels(loc,BLANK);}
		 };
	}

    int max(int i, int loc){
    if(loc>i){return loc;} return i;
    }

    int min(int i, int loc){
    if(loc<i){return loc;} return i;
    }

int pixels(int i){
Uint32 *pixels=(Uint32 *)screen->pixels;
return pixels[i];
}

void pixels(int i, int val){
Uint32 *pixels=(Uint32 *)screen->pixels;
pixels[i]=val;
}

	int compoundHor(int i, int search){
		 int count=0;
		  if(pixels(i)==search){count++;}
		  int j=0;
		  while( pixels(i+j)==search){ count++; j++; }
		  while( pixels(i-j)==search){ count++; j++; }
		  return count;
		}

		int compoundVer(int i, int search){
		 int count=0;
		  if(pixels(i)==search){count++;}
		  int j=0;
		  while( pixels(i+j*width)==search){ count++; if(i+j*width<sheight*width){break;}j++; }
		  while( pixels(i-j*width)==search){ count++; if(i-j*width>0){break;} j++; }
		  return count;
		}

		int floodSearch(int i, int search){
		searchcount=0;
		 compoundFull(i, search, ARBIT, 0.95F);
		 searchcount=0;
		 compoundFull(i, ARBIT, search, 1.0F);
		 return searchcount;
		}

		void compoundFull(int i, int search, int replace, float chance){
		  if(i<0 || i>sheight*width){return;}
		  if( pixels(i)!=search){return;}
		  if( random(0.0F, 1.0F)>chance)return;
		  if(searchcount>=128){return;}
		  pixels(i,replace);
		  searchcount++;

		compoundFull(i+1, search, replace, chance);
		compoundFull(i-1, search, replace, chance);
		compoundFull(i+width, search, replace, chance);
		compoundFull(i-width, search, replace, chance);
		}


	bool overRect(float f, float f1, float f2, float f3, float f4, float f5){
    return f4 >= f && f4 <= f + f2 && f5 >= f1 && f5 <= f1 + f3;
}

void fillRect(int x, int y, int w, int h){
            SDL_Rect rect;
 rect.x=x; rect.y=y; rect.w=w; rect.h=h;
            SDL_FillRect(drawingsurface, &rect, color);

}


void setColor(int co){
      SDL_PixelFormat *fmt=screen->format;
        color=co;
        sdlcolor.r=  ((co&fmt->Rmask)>> fmt->Rshift)<<fmt->Rloss;
        sdlcolor.g=  ((co&fmt->Gmask)>> fmt->Gshift)<<fmt->Gloss;
        sdlcolor.b=  ((co&fmt->Bmask)>> fmt->Bshift)<<fmt->Bloss;
}

void drawLine(int x0, int y0, int x1, int y1, int w){
        int dy = y1 - y0;
        int dx = x1 - x0;
        int stepx, stepy;

        if (dy < 0) { dy = -dy;  stepy = -1; } else { stepy = 1; }
        if (dx < 0) { dx = -dx;  stepx = -1; } else { stepx = 1; }
        dy <<= 1;
        dx <<= 1;

        //y0 *= width;
        //y1 *= width;
       fillCirc(x0, y0, w);
        if (dx > dy) {
            int fraction = dy - (dx >> 1);
            while (x0 != x1) {
                if (fraction >= 0) {
                    y0 += stepy;
                    fraction -= dx;
                }
                x0 += stepx;
                fraction += dy;
                       fillCirc(x0, y0, w);
            }
        } else {
            int fraction = dx - (dy >> 1);
            while (y0 != y1) {
                if (fraction >= 0) {
                    x0 += stepx;
                    fraction -= dy;
                }
                y0 += stepy;
                fraction += dx;
                       fillCirc(x0, y0, w);
            }
        }
}

void drawLine(int x1, int y1, int x2, int y2){
drawLine(x1, y1, x2, y2, 0);
}

  void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = nullptr ){
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

void drawRect(int x, int y, int w, int h){
    drawLine(x,y,x+w,y);
	drawLine(x,y+h,x+w,y+h);
	drawLine(x,y, x, y+h);
	drawLine(x+w, y, x+w, y+h);
}

void fillCirc(int xpos, int ypos, int radius){
	for (int x = ((xpos - radius - 1) < 0) ? 0 : (xpos - radius - 1); x <= xpos + radius && x < width; x++)
		for (int y = ((ypos - radius - 1) < 0) ? 0 : (ypos - radius - 1); y <= ypos + radius && y < height; y++)
		{
			if ((x-xpos)*(x-xpos) + (y-ypos)*(y-ypos) <= radius*radius) fillRect(x,y,1, 1);
		};
}


void drawString(const char* utf, int x, int y){
      SDL_Surface* message;

      message=TTF_RenderText_Solid(font, utf, sdlcolor);
      if(message==nullptr){ printf("image not created"); return;}
    apply_surface(x, y, message, drawingsurface);
          SDL_FreeSurface(message);
}

float random(float min, float max){
return (max-min)*((float)rand()/(RAND_MAX+1.0))+min;
}
