
#include "../include/state.h"

void loadSimulation(SimulationState *state){


  state->sun.texture = createTex(state->renderer, "files/images/sun.png");
  state->mercury.texture = createTex(state->renderer, "files/images/mercury.png");
  state->venus.texture = createTex(state->renderer, "files/images/venus.png");
  state->earth.texture = createTex(state->renderer, "files/images/earth.png");
  state->mars.texture = createTex(state->renderer, "files/images/mars.png");

  //Load Fonts
  state->text.size = 48;
  state->text.font = TTF_OpenFont("files/fonts/Crazy-Pixel.ttf", state->text.size);
  if(!state->text.font){
    printf("Cannot find font file!\n\n");
    SDL_Quit();
    exit(1);
  }

  //Inits Earth
  state->earth.distanceToGravPoolMeters = 1.496 * pow(10, 11);
  state->earth.speedToGravPool = 0;
  state->earth.mass = 5.972 * pow(10,24);
  state->earth.angle = PI/2;
  state->earth.AngularVelocityMetersPerSecond = 1.990986 * pow(10, -7);
  state->earth.radius = 10;
  state->earth.gravPool = &state->sun;
  state->earth.rotationAngle = 0;
  //Inits mercury
  state->mercury.distanceToGravPoolMeters = 5.7910 * pow(10, 10);
  state->mercury.speedToGravPool = 0;
  state->mercury.angle = -PI / 2;
  state->mercury.AngularVelocityMetersPerSecond = 8.26386956 * pow(10, -7);
  state->mercury.radius = 2;
  state->mercury.gravPool = &state->sun;
  state->mercury.rotationAngle = 0;
  //Inits venus
  state->venus.distanceToGravPoolMeters = 1.082 * pow(10, 11);
  state->venus.speedToGravPool = 0;
  state->venus.angle = -PI / 2;
  state->venus.AngularVelocityMetersPerSecond = 3.23209121 * pow(10, -7);
  state->venus.radius = 7;
  state->venus.gravPool = &state->sun;
  state->venus.rotationAngle = 0;
  //Inits mars
  state->mars.distanceToGravPoolMeters =  2.279 * pow(10, 11);
  state->mars.speedToGravPool = 0;
  state->mars.angle = -PI / 2;
  state->mars.AngularVelocityMetersPerSecond = 1.05854516 * pow(10, -7);
  state->mars.radius = 10;
  state->mars.gravPool = &state->sun;
  state->mars.rotationAngle = 0;
  //Inits Sun
  state->sun.x = 960/2;
  state->sun.mass = 1.98855*pow(10,30);
  state->sun.y = 540/2;
  state->sun.radius = 40;
  state->sun.massMultiplier = 1;
  state->sun.rotationAngle = 0;
  //state Vars
  state->COLLISION = 0;
  state->pixelsInOneEarthSunDistancePerPixel = 150;
  state->time = 0;
}
