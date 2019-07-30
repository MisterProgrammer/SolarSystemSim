
#include "../include/state.h"
void render(SimulationState *state){
  //renders BackgroundColor
  SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 255);
  SDL_RenderClear(state->renderer);

  createText(state,"0                                                           3 X  Massa do Sol",230,1030,1,1);
  createText(state,"1Px=1,49^8km",5,50,1,1);
  createText(state,"distancia do centro",5,100,1,1);
  createText(state,"da Terra ao Sol Certa",5,150,1,1);
  createText(state,"Raio do sol e terra",700,50,1,1);
  createText(state,"c escala errada",700,100,1,1);
  createText(state,"(certa seria mrd)",700,150,1,1);

  SDL_RenderPlanet(state, &state->sun, 1.5);
  SDL_RenderPlanet(state, &state->mercury, 1.5);
  SDL_RenderPlanet(state, &state->venus, 1.5);
  SDL_RenderPlanet(state, &state->earth, 1.5);
  SDL_RenderPlanet(state, &state->mars, 1.5);


  //Renders the animated Progress Bar
  SDL_SetRenderDrawColor(state->renderer, 255, 255, 255, 255);
  SDL_Rect Progress_Bar = {960/2-410/2,500,300*(state->sun.massMultiplier/3),30};
  SDL_RenderFillRect(state->renderer, &Progress_Bar);

  if(state->COLLISION == 1){
    createText(state,"COLISAO",323,500,3,3);
  }

  SDL_RenderPresent(state->renderer);
}

void createText(SimulationState *state,char *str,int x,int y,int w,int h){
  ////////////// TEXT /////////////////
  SDL_Color white = {255,255,255,255};
  SDL_Surface *tmp = TTF_RenderText_Blended(state->text.font,str, white);
  state->text.label = SDL_CreateTextureFromSurface(state->renderer, tmp);
  state->text.w = tmp->w*w;
  state->text.h = tmp->h*h;
  SDL_FreeSurface(tmp);
  SDL_Rect textRect = {x,y/2-state->text.h/2,state->text.w,state->text.h};
  SDL_RenderCopy(state->renderer, state->text.label , NULL, &textRect);
  ////////////// TEXT /////////////////
}


void set_pixel(SDL_Renderer *rend, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
  SDL_SetRenderDrawColor(rend, r,g,b,a);
  SDL_RenderDrawPoint(rend, x, y);
}

/*USELESS FOR NOW
void fill_circle(SDL_Renderer *gRenderer, int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
  for (double dy = 1; dy <= radius; dy += 1.0)
  {
    double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
    SDL_SetRenderDrawColor(gRenderer, r, g, b, a);
    SDL_RenderDrawLine(gRenderer, cx - dx, cy + dy - radius, cx + dx, cy + dy - radius);
    SDL_RenderDrawLine(gRenderer, cx - dx, cy - dy + radius, cx + dx, cy - dy + radius);
  }
}*/

//Function to create a Texture without having the surface cum all over you
SDL_Texture *createTex(SDL_Renderer *renderer,char *file){
  SDL_Surface *image;
  SDL_Texture *tex;
  image = IMG_Load(file);
  if(image == NULL){
    printf("This file ain't it chief\n");
    SDL_Quit();
    exit(1);
  }

  tex = SDL_CreateTextureFromSurface(renderer, image);
  SDL_FreeSurface(image);
  return tex;
}

void SDL_RenderPlanet(SimulationState *state, Planet *planet,float scale){
  SDL_Rect planetRect = {planet->x-planet->radius*scale,planet->y-planet->radius*scale,planet->radius*scale*2,planet->radius*scale*2};
  SDL_RenderCopyEx(state->renderer, planet->texture, NULL, &planetRect,planet->rotationAngle,NULL,SDL_FLIP_NONE);
}
