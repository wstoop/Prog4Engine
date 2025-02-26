#include <SDL.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "InputManager.h"
bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_w:
                SDL_Log("W key pressed");
                break;
            case SDLK_a:
                SDL_Log("A key pressed");
                break;
            case SDLK_s:
                SDL_Log("S key pressed");
                break;
            case SDLK_d:
                SDL_Log("D key pressed");
                break;
            case SDLK_ESCAPE:
                SDL_Log("Escape key pressed");
                return false;  // Exit the loop if Escape is pressed
            default:
                SDL_Log("Other key pressed: %d", e.key.keysym.sym);
                break;
            }
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		// etc...
        ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}
