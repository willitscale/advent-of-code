#define GRID_SIZE 1000

size_t countSurrounding(char g[GRID_SIZE][GRID_SIZE], size_t w, size_t h, size_t x, size_t y, char c);

size_t countSurrounding(char g[GRID_SIZE][GRID_SIZE], size_t w, size_t h, size_t x, size_t y, char c)
{
    return (g[x+1][y] == c) +
           (x > 0 && g[x-1][y] == c) +
           (g[x][y+1] == c) +
           (y > 0 && g[x][y-1] == c) +
           (g[x+1][y+1] == c) +
           (x > 0 && y > 0 && g[x-1][y-1] == c) +
           (y > 0 && g[x+1][y-1] == c) +
           (x > 0 && g[x-1][y+1] == c);
}
