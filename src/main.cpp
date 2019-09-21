#include <SFML/Graphics.hpp>
#include <time.h>

//#include "config.h"
#include "InputHandler.h"
#include "Map.h"
#include "Enemy.h"
#include "Ship.h"

using namespace sf;

const int map_y = 200;
const int map_x = 400;

//int grid[M][N] = {0};
//
//void drop(int y,int x)
//{
//  if (grid[y][x]==0) grid[y][x]=-1;
//  if (grid[y-1][x]==0) drop(y-1,x);
//  if (grid[y+1][x]==0) drop(y+1,x);
//  if (grid[y][x-1]==0) drop(y,x-1);
//  if (grid[y][x+1]==0) drop(y,x+1);
//}

int main()
{
    Map map(map_x, map_y);
    InputHandler handler;
    Enemy* enemy1 = new Enemy(map_x, map_y);
    Enemy* enemy2 = new Enemy(map_x, map_y);
    Enemy* enemy3 = new Enemy(map_x, map_y);
    Enemy* enemy4 = new Enemy(map_x, map_y);
    ZetShip* zet_ship = new ZetShip();
    map.enemy.push_back(enemy1);
    map.enemy.push_back(enemy2);
    map.enemy.push_back(enemy3);
    map.enemy.push_back(enemy4);
    map.ship.push_back(zet_ship);

    srand(time(0));
	RenderWindow window(VideoMode(map.getMapHorizontalSize(), map.getMapverticalSize()), "");
	window.setFramerateLimit(60);

	//Texture t1,t2,t3;
	//t1.loadFromFile(RESOURCE_PATH + "images/tiles.png");
 //   t2.loadFromFile(RESOURCE_PATH + "images/gameover.png");
 //   t3.loadFromFile(RESOURCE_PATH + "images/enemy.png");

	//Sprite sTile(t1), sGameover(t2), sEnemy(t3);
	//sGameover.setPosition(100,100);
	//sEnemy.setOrigin(20,20);

	//int enemyCount = 4;

	bool Game=true;
	//int x=0, y=0, dx=0, dy=0;
    float timer=0, delay=0.04; 
    Clock clock;

    while (window.isOpen())
    {
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer+=time;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
			   
			if (e.type == Event::KeyPressed)
             if (e.key.code==Keyboard::Escape)
               {
                for (int i=1;i< map_y -1;i++)
	             for (int j=1;j< map_x -1;j++)
                   //grid[i][j]=0;

                //x=10;y=0;
                Game=true;
               }
		}

		if (!Game) continue;
        
        if (timer > delay)
        {
            handler.handleInput(zet_ship);
            Game = map.updateMap();
            timer = 0;

  //          int x_flag = 1;
  //          if (dx < 0) x_flag = -1;
  //          for (; dx != 0; x += x_flag, dx -= x_flag) {
  //              if (x < 0) {
  //                  x = 0;
  //                  dx += x_flag;
  //                  break;
  //              }
  //              if (x > N - 1) {
  //                  x = N - 1;
  //                  dx += x_flag;
  //                  break;
  //              }
  //              if (grid[y][x] == 2) Game = false;
  //              if (grid[y][x] == 0) grid[y][x] = 2;
  //              timer = 0;
  //          }

  //          int y_flag = 1;
  //          if (dy < 0) y_flag = -1;
  //          for (; dy != 0; y += y_flag, dy -= y_flag) {
  //              if (y < 0) {
  //                  y = 0;
  //                  dy += y_flag;
  //                  break;
  //              }
  //              if (y > M - 1) {
  //                  y = M - 1;
  //                  dy += y_flag;
  //                  break;
  //              }
  //              if (grid[y][x] == 2) Game = false;
  //              if (grid[y][x] == 0) grid[y][x] = 2;
  //              timer = 0;
  //          }

		//}

		//for (int i=0;i<enemyCount;i++) a[i].move();

		//if (grid[y][x]==1)
  //        {
  //         dx=dy=0;

  //         for (int i=0;i<enemyCount;i++)
  //              drop(a[i].y/ts, a[i].x/ts);

  //         for (int i=0;i<M;i++)
	 //	    for (int j=0;j<N;j++)
  //            if (grid[i][j]==-1) grid[i][j]=0;
  //            else grid[i][j]=1;
  //        }

  //      for (int i=0;i<enemyCount;i++)
  //         if  (grid[a[i].y/ts][a[i].x/ts]==2) Game=false;

  //    /////////draw//////////
  //    window.clear();

	 // for (int i=0;i<M;i++)
		//for (int j=0;j<N;j++)
		// {
  //          if (grid[i][j]==0) continue;
  //          if (grid[i][j]==1) sTile.setTextureRect(IntRect( 0,0,ts,ts));
  //          if (grid[i][j]==2) sTile.setTextureRect(IntRect(54,0,ts,ts));
		//	sTile.setPosition(j*ts,i*ts);
		//	window.draw(sTile);
		// }
        window.clear();
        map.drawMap(&window);
  //    sTile.setTextureRect(IntRect(36,0,ts,ts));
	 // sTile.setPosition(x*ts,y*ts);
	 // window.draw(sTile);

	  //sEnemy.rotate(10);
   //   for (int i=0;i<enemyCount;i++)
   //    {
	  //  sEnemy.setPosition(a[i].x,a[i].y);
	  //  window.draw(sEnemy);
        }

      //if (!Game) window.draw(sGameover);

 	  window.display();
	}

    return 0;
}
