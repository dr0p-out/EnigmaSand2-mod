#ifndef EnigmaSandParticle_h
#define EnigmaSandParticle_h

class Particle {
public:
  int type;
  int xpos, ypos;
  bool active;
  int strokecolor, fillcolor;
  int psize;
  int count;
  float xvel, yvel;

  Particle();

  void initiate(int i, int typ);

  void drawParticle();
};

extern Particle *particles[1000];

#endif
