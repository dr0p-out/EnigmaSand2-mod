#include "math.h"

#define M_PI       3.14159265358979323846

class Particle {
    public:
	int type;
	int xpos, ypos;
	bool active;
	int strokecolor, fillcolor;
	int psize;
	int count;
	float xvel, yvel;

	 Particle(){type=0;
	 active=false;
	 xpos=0;
	 ypos=0;
	 strokecolor=0;
	 fillcolor=0;
	 psize=0;
	 count=0;
	 xvel=0;
	 yvel=0;}

	 void initiate(int i, int typ){
	   type=typ;
	   xpos=i%width;
	   ypos=i/width;
	   active=true;
	   count=0;
	   float vel=0;
	   float ang=0;
    switch(type){
	    case 0:
	            strokecolor=FIRE; fillcolor=FIRE;
	      vel=5.0F+random(0.0F, 10.0F);
	      ang=random(0.0F, (float)(2*M_PI));
	      xvel=(float)(vel*cos(ang));
	      yvel=(float)(vel*sin(ang));
	      psize=(int)(1+random(1.0F, 8.0F));
	    break;
	    case 1:
	        strokecolor=FIRE; fillcolor=FIRE;
	        psize=(int)( min(compoundHor(i, pixels(i)), compoundVer(i, pixels(i)))*random(4.0F, 8.0F) );
	        xvel=0; yvel=0;
	    break;
	    case 2:
	            strokecolor=FIRE; fillcolor=FIRE;
	        psize=(int)( min(compoundHor(i, pixels(i)), compoundVer(i, pixels(i)))*random(4.0F, 16.0F) );
	        xvel=0; yvel=0;
	        type=1;
	    break;
	    case 3:
	            strokecolor=FIRE; fillcolor=FIRE;
	            int count=floodSearch(i, C4);
	            if(count>64){ count/=random(6.0F, 12.0F);}else{count*=random(1.0F, 3.0F);}
	        psize=(int)( count);
	        xvel=0; yvel=0;

	    break;
	   }
	 }

	 void drawParticle(){
	   if(active){
	     xpos+=xvel;
	     ypos+=yvel;
	     //stroke(strokecolor);
	     setColor(fillcolor);



	   count++;
	   switch(type){
	    case 0:
	       drawLine((int)(xpos-xvel), (int)(ypos-yvel), xpos, ypos, psize);
	       if(count%15==0){yvel+=(4.9*(count/15));}
	       if(count%5==0)psize/=1.5;
	     break;
	     case 1:

	       //ellipseMode(CENTER);
	       fillCirc(xpos, ypos, psize/2);
	       if(count%5==0)psize/=2;
	     break;
	     case 3:
	    	 fillCirc(xpos, ypos, psize/2);
	       if(count%3==0)psize/=3;
	     break;
	   }

	   if(psize==0){active=false;}
	   }
	 }

	};


Particle *particles[1000];