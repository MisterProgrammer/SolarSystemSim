
#include "../include/state.h"


int main(int argc, char *argv[]) {
  SimulationState state;
  state.done = 0;
  SDL_Init(SDL_INIT_VIDEO);

  state.window = SDL_CreateWindow("Solar System", 1920/4, 1080/4, 960, 540, SDL_WINDOW_SHOWN);
  state.renderer = SDL_CreateRenderer(state.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  TTF_Init();
  loadSimulation(&state);

  while(!state.done){
    processEvents(&state);
    render(&state);
  }

  SDL_DestroyTexture(state.mercury.texture);
  SDL_DestroyTexture(state.venus.texture);
  SDL_DestroyTexture(state.earth.texture);
  SDL_DestroyTexture(state.mars.texture);
  SDL_DestroyTexture(state.text.label);
  state.text.label = NULL;
  SDL_DestroyRenderer(state.renderer);
  SDL_DestroyWindow(state.window);
  TTF_Quit();
  SDL_Quit();
  return 0;
}
