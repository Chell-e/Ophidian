#include "main.h"

static void capFrameRate(long* then, float* remainder);

int main(int argc, char* argv[])
{
	srand(time(NULL));
	long then;
	float remainder;

	// Allocate memory for the App struct
	memset(&app, 0, sizeof(App));
	app.textureTail = &app.textureHead;

	// Initialize SDL and open a window
	initSDL();
	// On application exit, call cleanup function
	atexit(cleanup);

	then = SDL_GetTicks();
	remainder = 0;

	// Initialize GameScene or any first scene you want here
	GameScene *scene = new GameScene();
	
	// Framework code
	// Pass in your initialized variable here
	Scene::setActiveScene(scene);
	
	// Main game loop
	while (true)
	{
		prepareScene();
		doInput();

		Scene::getActiveScene()->update();
		Scene::getActiveScene()->draw();

		presentScene();

		capFrameRate(&then, &remainder);
	}
	// Delete your instantiated scene here
	delete scene;

	//return 0;

    int grid_cell_size = 36;
    int grid_width = 29;
    int grid_height = 23;

    // + 1 so that the last grid lines fit in the screen.
    int window_width = (grid_width * grid_cell_size) + 1;
    int window_height = (grid_height * grid_cell_size) + 1;

    // Dark theme.
    SDL_Color grid_line_color = { 44, 44, 44, 255 }; // Dark grey

    // Light Theme.
    // SDL_Color grid_background = {233, 233, 233, 255}; // Barely white
    // SDL_Color grid_line_color = {200, 200, 200, 255}; // Very light grey
    // SDL_Color grid_cursor_ghost_color = {200, 200, 200, 255};
    // SDL_Color grid_cursor_color = {160, 160, 160, 255}; // Grey

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Initialize SDL: %s",
            SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window* window;
    SDL_Renderer* renderer;
    if (SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window,
        &renderer) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "Create window and renderer: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_SetWindowTitle(window, "SDL Grid");
   
        // Draw grid lines.
        SDL_SetRenderDrawColor(renderer, grid_line_color.r, grid_line_color.g,
            grid_line_color.b, grid_line_color.a);

        for (int x = 0; x < 1 + grid_width * grid_cell_size;
            x += grid_cell_size) {
            SDL_RenderDrawLine(renderer, x, 0, x, window_height);
        }

        for (int y = 0; y < 1 + grid_height * grid_cell_size;
            y += grid_cell_size) {
            SDL_RenderDrawLine(renderer, 0, y, window_width, y);
        }

        SDL_RenderPresent(renderer);
        return 0;
}

static void capFrameRate(long* then, float* remainder)
{
	long wait, frameTime;

	wait = 16 + *remainder;

	*remainder -= (int)*remainder;

	frameTime = SDL_GetTicks() - *then;

	wait -= frameTime;

	if (wait < 1)
	{
		wait = 1;
	}

	SDL_Delay(wait);

	*remainder += 0.667;

	*then = SDL_GetTicks();
}
