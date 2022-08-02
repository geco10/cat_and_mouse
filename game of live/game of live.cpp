#include "simplesfml.hpp"
#include <cstdio>
#include <cmath>
#include <ctime>
using namespace sf;
int yh = 0, xh = 0;
int yb = 0, xb = 0;
int min = 1000;
char map[101][101]{
"#######################",
"#                     #",
"# ########## ###### ###",
"#                     #",
"#                     #",
"#                     #",
"#         @ ######    #",
"#           # b       #",
"#           #####     #",
"#                #    #",
"#                     #",
"#                     #",
"#                     #",
"#                     #",
"#                     #",
"#######################",
};//241 160 113
int n = 20, m = 23;
int len = 25;
bool moveX(bool er) {
    if (xb > xh && map[yb][xb - 1] != '#') {
        map[yb][xb] = ' ';
        map[yb][--xb] = 'b';
        return true;
    }
    if (xb < xh && map[yb][xb + 1] != '#') {
        map[yb][xb] = ' ';
        map[yb][++xb] = 'b';
        return true;
    }
    if (er) {
        if (map[yb][xb - 1] != '#') {
            map[yb][xb] = ' ';
            map[yb][--xb] = 'b';
            return true;
        }
        if (map[yb][xb + 1] != '#') {
            map[yb][xb] = ' ';
            map[yb][++xb] = 'b';
            return true;
        }
    }
    return false;
}
bool moveY(bool er) {
    if (yb > yh && map[yb - 1][xb] != '#') {
        map[yb][xb] = ' ';
        map[--yb][xb] = 'b';
        return true;
    }if (yb < yh && map[yb + 1][xb] != '#') {
        map[yb][xb] = ' ';
        map[++yb][xb] = 'b';
        return true;
    }
    if (er) {
        if (map[yb - 1][xb] != '#') {
            map[yb][xb] = ' ';
            map[--yb][xb] = 'b';
            return true;
        }if (map[yb + 1][xb] != '#') {
            map[yb][xb] = ' ';
            map[++yb][xb] = 'b';
            return true;
        }
    }
    return false;
}
void moveHero(char dih) {
    switch (dih)
    {
    case 'r':
        if (map[yh][xh + 1] != '#')
            xh++;
        break;
    case 'l':
        if (map[yh][xh - 1] != '#')
            xh--;
        break;
    case 'd':
        if (map[yh + 1][xh] != '#')
            yh++;
        break;
    case 'u':
        if (map[yh - 1][xh] != '#')
            yh--;
        break;
    default:
        puts("non command!");
        break;
    }
}
bool balanceX() {
    if (xh != xb) {
        if (!moveX(false)) {
            return moveY(true);
        }
        else return true;
    }
    return false;
}
bool balanceY() {
    if (yh != yb) {
        if (!moveY(false)) {
            return moveX(true);
        }
        else return true;
    }
    return false;
}
void calc(int y,int x,int dih) {
    if (dih == 15)return;
    if (y==yh &&x==xh&& dih<min) {
        min = dih;
    }
    else
        if (map[y][x]=='#'|| map[y][x] == '.') {
            return;
        }
        else {
            map[y][x] = '.';
            calc(y + 1, x, dih + 1);
            calc(y - 1, x, dih + 1);
            calc(y, x + 1, dih + 1);
            calc(y, x -1, dih + 1);
            map[y][x] = ' ';
        }
//    int r = rand() % 2;
//    if (r == 1) {
//        if (balanceX())return true;
//        return balanceY();
//    }
//    else {
//        if (balanceY())return true;
//        return balanceX();
//    }
}
int getLen(int y,int x){
    calc(y, x, 0);
    int t = min;
    min = 1000;
    return t;
}
char direction(){
  int min = 1000;
  char dir=' ';
  if (yh == yb && xh == xb) {
      return ' ';
  }
  int t=getLen(yb-1, xb);
  if (min > t)min = t, dir = 'u';
  t=getLen(yb + 1, xb);
  if (min > t)min = t, dir ='d';
  t=getLen(yb, xb + 1);
  if (min > t)min = t, dir = 'r';
  t=getLen(yb, xb - 1);
  if (min > t)min = t, dir = 'l';
  return dir;
}
bool moveBot() {
    switch (direction()) {
    case 'd':
        yb++;
        return true;
    case 'u':
        yb--;
        return true;
    case 'r':
        xb++;
        return true;
    case 'l':
        xb--;
        return true;
    default:
         return false;
    }
}
void drawMap(RenderWindow& window) {
    for (int i = 0; i < n - 4; i++) {
        for (int j = 0; j < m; ++j) {
            setFillColor(255, 255, 255);
            rectangle(window, len, len, j * len, i * len);
            if (map[i][j] == '#') {
                setFillColor(241, 160, 113);
                rectangle(window, len, len, j * len, i * len);
            }

        }
    }
    setFillColor(1, 255, 3);
    circle(window, len, xh * len, len * yh);
    setFillColor(255, 7, 6);
    circle(window, len, xb * len, yb * len);
}
int main() {
    srand(time(0));
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; j++) {
            {
                if (map[i][j] == '@')yh = i, xh = j;
                if (map[i][j] == 'b')xb=j,yb=i;
            }
        }
    }
    int count = 0;
    int c = 0;
    sf::RenderWindow window(sf::VideoMode(1256, 725), "SFML works!");
    window.setKeyRepeatEnabled(false);
    while (window.isOpen())
    {
        sf::Event event;
        char d = ' ';
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.key.code == sf::Keyboard::Up) {
                d = 'u';
            }
            else
                if (event.key.code == sf::Keyboard::Down) {
                    d = 'd';
                }
                else
                    if (event.key.code == sf::Keyboard::Right) {
                        d = 'r';
                    }
                     else
                        if (event.key.code == sf::Keyboard::Left) {
                            d = 'l';
                        }
        }
        setBackgroundColor(0, 0, 218);
        clear(window);
        if (count == 15) {
            int y = rand() % (n - 1) + 2;
            int x = rand() % (m - 1) + 2;
            if ((y!=yb||x!=xb)&& (y != yh||x!=xh)) {
                    map[y][x] = '#';
                count = 0;
            }
        }
        else {
            ++count;
        }
        if (c > 0)--c;
        else {
            if (moveBot() == false)c = 9, puts("coligen");
        }
        moveHero(d);
        drawMap(window);
        pause(250);
        window.display();
    }


    return 0;
}