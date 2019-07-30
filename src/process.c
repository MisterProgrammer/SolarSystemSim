
#include "../include/state.h"

void processEvents(SimulationState *state){
  state->time++;
  if(state->COLLISION == 1){
    SDL_Delay(4000);
    //Inits Earth
    state->earth.distanceToGravPoolMeters = 1.496 * pow(10, 11);
    state->earth.speedToGravPool = 0;
    state->earth.mass = 5.972 * pow(10,24);
    state->earth.angle = PI / 6;
    state->earth.AngularVelocityMetersPerSecond = 1.990986 * pow(10, -7);
    state->earth.radius = 10;
    state->earth.gravPool = &state->sun;
    //Inits mercury
    state->mercury.distanceToGravPoolMeters = 5.7910 * pow(10, 10);
    state->mercury.speedToGravPool = 0;
    state->mercury.angle = -PI / 2;
    state->mercury.AngularVelocityMetersPerSecond = 8.26386956 * pow(10, -7);
    state->mercury.radius = 2;
    state->mercury.gravPool = &state->sun;
    //Inits venus
    state->venus.distanceToGravPoolMeters = 1.082 * pow(10, 11);
    state->venus.speedToGravPool = 0;
    state->venus.angle = -PI / 2;
    state->venus.AngularVelocityMetersPerSecond = 3.23209121 * pow(10, -7);
    state->venus.radius = 7;
    state->venus.gravPool = &state->sun;
    //Inits mars
    state->mars.distanceToGravPoolMeters =  2.279 * pow(10, 11);
    state->mars.speedToGravPool = 0;
    state->mars.angle = -PI / 2;
    state->mars.AngularVelocityMetersPerSecond = 1.05854516 * pow(10, -7);
    state->mars.radius = 10;
    state->mars.gravPool = &state->sun;
    //Inits Sun
    state->sun.x = 960/2;
    state->sun.mass = 1.98855*pow(10,30);
    state->sun.y = 540/2;
    state->sun.radius = 40;
    state->sun.massMultiplier = 1;
    //state Vars
    state->COLLISION = 0;
    state->pixelsInOneEarthSunDistancePerPixel = 150;
  }

  state->numberOfCalculationsPerFrame = 1000;
  state->deltaT = 3600*24/ state->numberOfCalculationsPerFrame;
  SDL_Event event;
  //get filthy keyboard input *FILTHYYY*
  while(SDL_PollEvent(&event)){
    switch(event.type){

      case SDL_WINDOWEVENT_CLOSE:
      if(state->window){
        SDL_DestroyWindow(state->window);
        state->done = 1;
        break;
      }
      //press down key events
      case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
        state->done = 1;
        break;
        case SDLK_LEFT:
        if(state->sun.massMultiplier >= 0){
        state->sun.massMultiplier -= 0.05;
        state->sun.mass =  1.98855*pow(10,30)*state->sun.massMultiplier;
      }
        break;
        case SDLK_UP:
          state->pixelsInOneEarthSunDistancePerPixel += 10;
        break;
        case SDLK_DOWN:
          state->pixelsInOneEarthSunDistancePerPixel -= 10;

        break;
        case SDLK_RIGHT:
        if(state->sun.massMultiplier <= 3){
        state->sun.massMultiplier += 0.05;
        state->sun.mass = 1.98855*pow(10,30)*state->sun.massMultiplier;
        }
        break;
      }
      break;
      case SDL_QUIT:
      state->done = 1;
      break;
    }
  }

  for(int i=0;i<state->numberOfCalculationsPerFrame;i++){
    processPlanetPhysics(state,&state->earth, state->deltaT);
    processPlanetPhysics(state,&state->mercury, state->deltaT);
    processPlanetPhysics(state,&state->mars, state->deltaT);
    processPlanetPhysics(state,&state->venus, state->deltaT);
  }
  state->sun.rotationAngle += 12.72;
  state->mercury.rotationAngle += 6.1433447;
  state->venus.rotationAngle += 1.48148;
  state->earth.rotationAngle += 363.63;
  state->mars.rotationAngle += 349.5145;
  printf("%i\n", state->time);

  /*printf("earth:%i,%lf,%i,%i\n", state->earth.scaledDistanceToGravPoolPixels,state->earth.angle,state->earth.x,state->earth.y);
  printf("moon:%i,%lf,%i,%i\n", state->moon.scaledDistanceToGravPoolPixels,state->moon.angle,state->moon.x,state->moon.y);*/
  calculatePosOfPlanetFromAngAndRad(state, &state->mercury);
  calculatePosOfPlanetFromAngAndRad(state, &state->mars);
  calculatePosOfPlanetFromAngAndRad(state, &state->venus);
  calculatePosOfPlanetFromAngAndRad(state, &state->earth);

  if(dist(state->earth.x, state->earth.y, state->sun.x, state->sun.y) <(state->earth.radius + state->sun.radius)){
    state->COLLISION = 1;
  }

}



float calculateDistanceAcceleration(SimulationState *state,float distanceToGravPool,float angleSpeed, float massOfGravPool){
  state->gravConst = 6.67408 * pow(10, -11);
  return distanceToGravPool * pow(angleSpeed, 2) -
  (state->gravConst * massOfGravPool) / pow(distanceToGravPool, 2);
}

float calculateAngularAcceleration(float distanceToGravPool,float speedToGravPool,float angleSpeed){
  return -2.0 * angleSpeed * speedToGravPool / distanceToGravPool;
}

float eulerMethod(float currentValue, float deltaT, float derivative) {
  return currentValue + deltaT * derivative;
}


void processPlanetPhysics(SimulationState *state,Planet *planet,float deltaT){


  float distanceAcceleration = calculateDistanceAcceleration(state,planet->distanceToGravPoolMeters,planet->AngularVelocityMetersPerSecond,planet->gravPool->mass);

  planet->speedToGravPool = eulerMethod(planet->speedToGravPool,  deltaT, distanceAcceleration);

  planet->distanceToGravPoolMeters = eulerMethod(planet->distanceToGravPoolMeters,deltaT, planet->speedToGravPool);

  float angleAcceleration = calculateAngularAcceleration(planet->distanceToGravPoolMeters,planet->speedToGravPool,planet->AngularVelocityMetersPerSecond);

  planet->AngularVelocityMetersPerSecond = eulerMethod(planet->AngularVelocityMetersPerSecond,deltaT, angleAcceleration);

  planet->angle = eulerMethod(planet->angle,deltaT, planet->AngularVelocityMetersPerSecond);

}



void calculatePosOfPlanetFromAngAndRad(SimulationState *state,Planet *planet){


  state->scaleFactor = (1.496 * pow(10, 11))/ state->pixelsInOneEarthSunDistancePerPixel;

  planet->scaledDistanceToGravPoolPixels = (planet->distanceToGravPoolMeters /  state->scaleFactor);

  planet->x = planet->scaledDistanceToGravPoolPixels*cos(planet->angle)+planet->gravPool->x;
  planet->y = planet->scaledDistanceToGravPoolPixels*sin(planet->angle)+planet->gravPool->y;

}


int dist(int x,int y,int x2, int y2){
  int dist = sqrt(pow(x2-x,2)+pow(y2-y,2));
  return dist;
}
