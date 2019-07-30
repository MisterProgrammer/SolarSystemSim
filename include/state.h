#ifndef STATE_H
#define STATE_H
#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#define PI 3.14159265358979323846

typedef struct Planet_{
  double distanceToGravPoolMeters;
  int scaledDistanceToGravPoolPixels;
  double speedToGravPool;
  float angle;
  double AngularVelocityMetersPerSecond;
  double mass;
  float massMultiplier;
  struct Planet_ *gravPool;
  float rotationAngle;
  SDL_Texture *texture;
  float radius;
  int x;
  int y;
}Planet;

typedef struct Text_{
  TTF_Font *font;
  int size;
  SDL_Texture *label;
  int w,h;
}Text;


typedef struct SimulationState_{
  int done;
  SDL_Window *window;
  SDL_Renderer *renderer;
  Planet sun;
  Planet earth;
  Planet mars;
  Planet mercury;
  Planet venus;
  int pixelsInOneEarthSunDistancePerPixel;
  float scaleFactor;
  Text text;
  int COLLISION;
  double gravConst;
  int numberOfCalculationsPerFrame;
  int deltaT;
  int time;
}SimulationState;


void render(SimulationState *state);
void fill_circle(SDL_Renderer *gRenderer, int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void set_pixel(SDL_Renderer *rend, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
void createText(SimulationState *state,char *str,int x,int y,int w,int h);
void processEvents(SimulationState *state);
void processPlanetPhysics(SimulationState *state,Planet *planet,float deltaT);
float eulerMethod(float currentValue, float deltaT, float derivative);
float calculateDistanceAcceleration(SimulationState *state,float distanceToGravPool,float angleSpeed, float massOfGravPool);
float calculateAngularAcceleration(float distanceToGravPool,float speedToGravPool,float angleSpeed);
int dist(int x,int y,int x2, int y2);
void calculatePosOfPlanetFromAngAndRad(SimulationState *state,Planet *planet);
void loadSimulation(SimulationState *state);
SDL_Texture *createTex(SDL_Renderer *renderer,char *file);
void SDL_RenderPlanet(SimulationState *state, Planet *planet,float scale);

#endif
