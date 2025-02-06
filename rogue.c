#include <ncurses.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <math.h>
// #include <cjson/cJSON.h>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_mixer.h>
#define track_1 "1.mp3"
#define track_2 "2.mp3"
#define track_3 "3.mp3"
#define MAX_SIZE 400
int all_treasures = 0;
int dificulty = 0;
int health_num = 100;


typedef struct prof
{
    char name[MAX_SIZE];
    char password[MAX_SIZE];
    char e_mail[MAX_SIZE];
    char map[4][MAX_SIZE][MAX_SIZE];
    char inventory[10][MAX_SIZE];
    int weapon;
    int weapon_num;
    int points;
    int gold_reserve;
    int experience;
    int health;
}profile;



typedef struct location
{
    int x;
    int y;
}location;

typedef struct rooms
{
    int show;
    int size_x;
    int size_y;
    int x_c;
    int y_c;
    char map[MAX_SIZE][MAX_SIZE];
    int numdoor;
    location door[MAX_SIZE];
    // location foods[MAX_SIZE];
}rooms;

typedef struct monster
{
    int monster_h;
    location monster;
    int damage;
}monsters;




typedef struct naghseh
{
    char naghseh[MAX_SIZE][MAX_SIZE];
    int show[MAX_SIZE][MAX_SIZE];
    int RoomNum;
    int MonsNum;
    rooms room[9];
}naghseh;
naghseh dungeons[5];
int stairs = 0;


void follow(int range , int x_p , int y_p , int* x_mp , int* y_mp , int* hurt)
{
    int ishurt = &hurt;
    int x_m = &x_mp;
    int y_m = &y_mp;
    int distance_x = abs(x_p - x_m);
    int distance_y = abs(y_p - y_m);
    if((distance_x != 1 || distance_y != 1) && (distance_x < range && distance_y < range))
    {
        if(abs(x_p - (x_m - 1)) <= distance_x && abs(x_p - (x_m - 1)) > 0)
        {
            x_m--;
        }
        else if(abs(x_p - (x_m + 1)) <= distance_x && abs(x_p - (x_m + 1)) > 0)
        {
            x_m++;
        }
        else if(abs(y_p - (y_m - 1)) <= distance_y && abs(y_p - (y_m - 1)) > 0)
        {
            y_m--;
        }
        else if(abs(y_p - (y_m + 1)) > 0)
        {
            y_m--;
        }
        ishurt = 0;
    }
    else if(distance_x == 1 && distance_y == 1)
    {
        if(abs(x_p - (x_m - 1)) <= distance_x)
        {
            x_m--;
        }
        else if(abs(x_p - (x_m + 1)) <= distance_x)
        {
            x_m++;
        }
        else if(abs(y_p - (y_m - 1)) <= distance_y)
        {
            y_m--;
        }
        else
        {
            y_m--;
        }
        ishurt = 1;
    }
}



int type_monster(char a)
{
    if(a == 'd')
    {
        return 1; // deamon
    }
    else if(a == 'b')
    {
        return 2; // fbm
    }
    else if(a == 'V')
    {
        return 3; //Giant
    }
    else if(a == 'S')
    {
        return 4; // snake
    }
    else if(a == 'U')
    {
        return 5; // undeed
    }
    return 0; // non.
}


int isfollower(char a)
{
    if(a == 'V')
    {
        return 1; //Giant
    }
    else if(a == 'S')
    {
        return 1; // snake
    }
    else if(a == 'U')
    {
        return 1; // undeed
    }
    return 0; // non.
}


int range_monster(char a)
{
    if(a == 'V')
    {
        return 5; //Giant
    }
    else if(a == 'S')
    {
        return MAX_SIZE; // snake
    }
    else if(a == 'U')
    {
        return 5; // undeed
    }
    return 0; // non.
}


int damage(char a)
{
    if(a == 'd')
    {
        return 5; // deamon
    }
    else if(a == 'b')
    {
        return 10; // fbm
    }
    else if(a == 'V')
    {
        return 15; //Giant
    }
    else if(a == 'S')
    {
        return 20; // snake
    }
    else if(a == 'U')
    {
        return 30; // undeed
    }
    return 0; // non.
}



char type(int a)
{
    if( a == 0 )
    {
        return 'd';
    }
    else if( a == 1 )
    {
        return 'b';
    }
    else if(a == 2)
    {
        return 'V';
    }
    else if(a==3)
    {
        return 'S';
    }
    else if(a==4)
    {
        return 'U';
    }
}



int health(int dificulty)
{
    if(dificulty == 0)
    {
        return 100;
    }
    else if(dificulty == 1)
    {
        return 500;
    }
    else if(dificulty == 2)
    {
        return 1000;
    }
}



int istreasure(char a)
{
    if( a == '$' )
    {
        return 1;
    }
    return 0;
}


int ismace(char a)
{
    if(a == 'M')
    {
        return 1;
    }
    return 0;
}


int iswand(char a)
{
    if(a == 'I')
    {
        return 1;
    }
    return 0;
}


int isdagger(char a)
{
    if(a == 'p')
    {
        return 1;
    }
    return 0;
}


int isarrow(char a)
{
    if(a == 'Y')
    {
        return 1;
    }
    return 0;
}



int issword(char a)
{
    if(a == 'P')
    {
        return 1;
    }
    return 0;
}



int istair(char a)
{
    if(a == '>')
    {
        return 1;
    }
    return 0;
}



int istrap(char a)
{
    if(a == '^' || a == 't')
    {
        return 1;
    }
    return 0;
}


int isdoor(char a)
{
    if(a == '+')
    {
        return 1;
    }
    return 0;
}


int iswall(char a)
{
    if(a == '|' || a == '-')
    {
        return 1;
    }
    return 0;
}


int isfood(char a)
{
    if(a == 'f')
    {
        return 1;
    }
    return 0;
}

int isgold(char a)
{
    if(a == 'G')
    {
        return 1;
    }
    return 0;
}

int ispillar(char a)
{
    if(a == '0')
    {
        return 1;
    }
    return 0;
}

int iswindow(char a)
{
    if(a == '=')
    {
        return 1;
    }
    return 0;
}


int iscorridor(char a)
{
    if(a == '#')
    {
        return 1;
    }
    return 0;
}

int isfloor(char a)
{
    if(a == '.')
    {
        return 1;
    }
    return 0;
}


int distance(int a , int b)
{
    return abs(a - b);
}


void SeedRand()
{
    srand(time(NULL));
}



int Random(int min , int max)
{
    int diff = max - min;
    return rand() % diff + min;
}



// void Seda_1()
// {
//     if(SDL_Init(SDL_INIT_AUDIO) < 0)
//     {
//         fprintf(stdscr , "SDL could not initialize! SDL_Error: %s\n" , SDL_GetError());
//         exit(1);
//     }

//     if(Mix_OpenAudio(44100 , MIX_DEFAULT_FORMAT , 2 , 2048) < 0)
//     {
//         fprintf(stdscr , "SDL could not initialize! SDL_Mixer Error: %s\n" , Mix_GetError());
//         exit(1);
//     }
// }


// void play_track(const char *file)
// {
//     Mix_Music *music = Mix_LoadMUS(file);
//     if(music == NULL)
//     {
//         fprintf(stdscr , "Failed to load music! SDL_Mixer Error: %s\n" , Mix_GetError());
//         exit(1);
//     }

//     if(Mix_PlayMusic(music , -1) < 0)
//     {
//         fprintf(stdscr , "Failed to play music! SDL_Mixer Error: %s\n" , Mix_GetError());
//         exit(1);
//     }
// }


// void stop()
// {
//     Mix_HaltMusic();
//     Mix_CloseAudio();
//     SDL_Quit();
// }

void connect(int x_i , int y_i , int x_f , int y_f , char naghsheh[][MAX_SIZE])
{
    int distance_x = x_f - x_i;
    int distance_y = y_f - y_i;
    if(distance_x > 0 && distance_y > 0)
    {
        while(distance_x > 0 || distance_y > 0)
        {
            int choose = Random(0,2);
            if(!choose)
            {
                if(distance_x - 1 >= 0)
                {
                    x_i++;
                    distance_x--;
                    if(naghsheh[y_i][x_i] == ' ')
                    {
                        naghsheh[y_i][x_i] = '#';
                    }
                    else if(naghsheh[y_i][x_i] == '-' || naghsheh[y_i][x_i] == '|' || naghsheh[y_i][x_i] == '=')
                    {
                        naghsheh[y_i][x_i] = '+';
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            else
            {
                if(distance_y - 1 >= 0)
                {
                    y_i++;
                    distance_y--;
                    if(naghsheh[y_i][x_i] == ' ')
                    {
                        naghsheh[y_i][x_i] = '#';
                    }
                    else if(naghsheh[y_i][x_i] == '-' || naghsheh[y_i][x_i] == '|' || naghsheh[y_i][x_i] == '=')
                    {
                        naghsheh[y_i][x_i] = '+';
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
    }
    else if(distance_x > 0 && distance_y < 0)
    {
        while(distance_x > 0 || distance_y < 0)
        {
            int choose = Random(0,2);
            if(!choose)
            {
                if(distance_x - 1 >= 0)
                {
                    x_i++;
                    distance_x--;
                    if(naghsheh[y_i][x_i] == ' ')
                    {
                        naghsheh[y_i][x_i] = '#';
                    }
                    else if(naghsheh[y_i][x_i] == '-' || naghsheh[y_i][x_i] == '|' || naghsheh[y_i][x_i] == '=')
                    {
                        naghsheh[y_i][x_i] = '+';
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            else
            {
                if(distance_y + 1 <= 0)
                {
                    y_i--;
                    distance_y++;
                    if(naghsheh[y_i][x_i] == ' ')
                    {
                        naghsheh[y_i][x_i] = '#';
                    }
                    else if(naghsheh[y_i][x_i] == '-' || naghsheh[y_i][x_i] == '|' || naghsheh[y_i][x_i] == '=')
                    {
                        naghsheh[y_i][x_i] = '+';
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
    }
    else if(distance_x < 0 && distance_y > 0)
    {
        while(distance_x < 0 || distance_y > 0)
        {
            int choose = Random(0,2);
            if(!choose)
            {
                if(distance_x + 1 <= 0)
                {
                    x_i--;
                    distance_x++;
                    if(naghsheh[y_i][x_i] == ' ')
                    {
                        naghsheh[y_i][x_i] = '#';
                    }
                    else if(naghsheh[y_i][x_i] == '-' || naghsheh[y_i][x_i] == '|' || naghsheh[y_i][x_i] == '=')
                    {
                        naghsheh[y_i][x_i] = '+';
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            else
            {
                if(distance_y - 1 >= 0)
                {
                    y_i++;
                    distance_y--;
                    if(naghsheh[y_i][x_i] == ' ')
                    {
                        naghsheh[y_i][x_i] = '#';
                    }
                    else if(naghsheh[y_i][x_i] == '-' || naghsheh[y_i][x_i] == '|' || naghsheh[y_i][x_i] == '=')
                    {
                        naghsheh[y_i][x_i] = '+';
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
    }
    else
    {
        while(distance_x < 0 || distance_y < 0)
        {
            int choose = Random(0,2);
            if(!choose)
            {
                if(distance_x + 1 <= 0)
                {
                    x_i--;
                    distance_x++;
                    if(naghsheh[y_i][x_i] == ' ')
                    {
                        naghsheh[y_i][x_i] = '#';
                    }
                    else if(naghsheh[y_i][x_i] == '-' || naghsheh[y_i][x_i] == '|' || naghsheh[y_i][x_i] == '=')
                    {
                        naghsheh[y_i][x_i] = '+';
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            else
            {
                if(distance_y + 1 <= 0)
                {
                    y_i--;
                    distance_y++;
                    if(naghsheh[y_i][x_i] == ' ')
                    {
                        naghsheh[y_i][x_i] = '#';
                    }
                    else if(naghsheh[y_i][x_i] == '-' || naghsheh[y_i][x_i] == '|' || naghsheh[y_i][x_i] == '=')
                    {
                        naghsheh[y_i][x_i] = '+';
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
    }
}



int is_char(char a)
{
    if((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z')){
        return 1;
    }
    return 0;
}




void welcome_to_the_rouge()
{
    char welcome[100] = "Welcome to the Rogue!";
    char *p = welcome;
    int len_1 = strlen(welcome);
    int row_1 , col_1;
    getmaxyx(stdscr , row_1 , col_1);
    attron(COLOR_PAIR(1));
    bkgd('.');
    move(0,col_1/2 - len_1/2);
    while(*p){
        addch(*p);
        refresh();
        p++;
        napms(100); // adding delay function.
    }
    napms(500);
    getmaxyx(stdscr , row_1 , col_1);
    move(row_1/2 - 1,col_1/2 - 26/2);
    printw("Press any key to continue!");
    getch();
    attroff(COLOR_PAIR(1));
    refresh();
}



void generate_map(int row , int col , rooms Room[] , int RoomNum , char naghsheh[][MAX_SIZE] , int floor , location pelle[] , location beast[])
{
    for (int i = 0; i < row; i++)
    {
        for(int j = 0 ; j < col ; j++)
        {
            naghsheh[i][j] = ' ';
        }
    }
    int stairs_num;
    if(floor == 1 || floor == 4)
    {
        stairs_num = 1;
    }
    else
    {
        stairs_num = 2;
    }
    int stairs_cnt = 0;

    int beast_num = 4;
    int beast_cnt = 0;



    int weapon_type = Random(0,5);
    char weapon;
    int weapon_cnt = 0;
    switch (weapon_type)
    {
    case 0:
        weapon = 'M';
        break;
    case 1:
        weapon = 'I';
        break;
    case 2:
        weapon = 'p';
        break;
    case 3:
        weapon = 'Y';
        break;
    case 4:
        weapon = 'P';
        break;
    default:
        break;
    }


    int treasure_cnt = 0;


    int points = Random(0 , 7);
    int gold_cnt = 0;


    for(int i = 0 ; i < RoomNum ; i++)
    {
        int x;
        int y;
        int room_width;
        int room_hight;
        room_width = Random(6 , 10);
        room_hight = Random(6 , 10);
        //making sure that our rooms doesnt get out of the map.
        x =  Random(room_width + 1 , col - room_width - 1);
        y = Random(room_hight + 1 , row - room_hight - 1);
        
        
        int count = 0;
        //checking if there is any full place in random room or not.
        for(int i = y - 1; i < y + room_hight + 1 ; i++ )
        {
            for(int j = x - 1 ; j < x + room_width + 1 ; j++)
            {
                if(naghsheh[i][j] != ' ')
                {
                    count = 1;
                    i = y + room_hight + 1;
                    break;
                }
            }
        }
        if(count == 1)
        {
            i--;
        }
        else
        {
            Room[i].size_x = room_width;
            Room[i].size_y = room_hight;
            Room[i].x_c = x;
            Room[i].y_c = y;
            int door_count = 0;
            int pillar_count = 0;
            for(int i_1 = x ; i_1 < x + room_width ; i_1++)
            {
                for(int j = y ; j < y + room_hight ; j++)
                {
                    if(i_1 == x && j == y || i_1 == x + room_width - 1 && j == y || i_1 == x && j == y + room_hight - 1 || i_1 == x + room_width - 1 && j == y + room_hight - 1)
                    {
                        naghsheh[j][i_1] = ' ';
                        Room[i].map[j][i_1] = ' ';
                    }
                    else if(i_1 == x || i_1 == x + room_width - 1)
                    {
                        int door = Random(0,x+room_width-1);
                        int window = Random(0,100);
                        if(door > (50) * (x+room_width-1) / 100 && door_count < 2 && j <= y + room_hight - 3 || (i_1 == x + room_width - 3 && j == y + room_hight - 3 && door_count == 0))
                        {
                            (Room[i].door[door_count]).x = i_1;
                            (Room[i].door[door_count]).y = j;
                            door_count++;
                            naghsheh[j][i_1] = '+';
                            Room[i].map[j][i_1] = '+';
                        }
                        else
                        {
                            naghsheh[j][i_1] = '|';
                            Room[i].map[j][i_1] = '|';
                        }
                    }
                    else if(j == y || j == y + room_hight - 1)
                    {
                        int door = Random(0,x+room_width-1);
                        int window = Random(0,100);
                        if(door > (50) * (x+room_width-1) / 100 && door_count < 2 && j <= y + room_hight - 3 || (i_1 == x + room_width - 3 && j == y + room_hight - 3 && door_count == 0))
                        {
                            (Room[i].door[door_count]).x = i_1;
                            (Room[i].door[door_count]).y = j;
                            door_count++;
                            naghsheh[j][i_1] = '+';
                            Room[i].map[j][i_1] = '+';
                        }
                        else if(window > 80 && j <= y + room_hight - 3 )
                        {
                            naghsheh[j][i_1] = '=';
                            Room[i].map[j][i_1] = '=';
                        }
                        else
                        {
                            if (treasure_cnt < 1 && floor == 4)
                            {
                                naghsheh[j][i_1] = '$';
                                Room[i].map[j][i_1] = '$';
                                treasure_cnt++;
                            }
                            else
                            {
                                naghsheh[j][i_1] = '-';
                                Room[i].map[j][i_1] = '-';
                            }
                        }
                    }
                    else
                    {
                        int pilar = Random(0,10);
                        int randgold = Random(0,10);
                        if(pilar == 0 && pillar_count < 4 && j > y + 1 && j < room_hight + y - 1 && i_1 > x + 1 && i_1 < x + room_width - 1)
                        {
                            pillar_count++;
                            naghsheh[j][i_1] = '0';
                            Room[i].map[j][i_1] = '0';
                        }
                        else if(pilar == 1)
                        {
                            int randomize = Random(0,10);
                            if (randomize > 7 && beast_cnt < beast_num)
                            {
                                int tip = Random(0,5);
                                naghsheh[j][i_1] = type(tip);
                                Room[i].map[j][i_1] = type(tip);
                                beast[beast_cnt].x = i_1;
                                beast[beast_cnt].y = j;
                                beast_cnt++;
                            }
                            else
                            {                            
                                naghsheh[j][i_1] = '^';
                                Room[i].map[j][i_1] = '^';
                            }
                        }
                        else if(pilar == 2)
                        {
                            //food & gold
                            if(randgold > 5)
                            {
                                naghsheh[j][i_1] = 'f';
                                Room[i].map[j][i_1] = 'f';
                            }
                            else
                            {
                                naghsheh[j][i_1] = 'G';
                                Room[i].map[j][i_1] = 'G';
                            }
                        }
                        else
                        {
                            if(stairs_cnt < stairs_num)
                            {
                                naghsheh[j][i_1] = '>';
                                Room[i].map[j][i_1] = '>';
                                pelle[stairs].x = i_1;
                                pelle[stairs].y = j;
                                stairs++;
                                stairs_cnt++;
                            }
                            else if(weapon_cnt < 1)
                            {
                                naghsheh[j][i_1] = weapon;
                                Room[i].map[j][i_1] = weapon;
                                weapon_cnt++;
                            }
                            else
                            {
                                naghsheh[j][i_1] = '.';
                                Room[i].map[j][i_1] = '.';
                            }
                        }
                    }
                }
                Room[i].numdoor = door_count;
            }
        }
    }
    for(int i = 0 ; i < RoomNum ; i++)
    {
        int x = Room[i].x_c;
        int y = Room[i].y_c;
        int sx = Room[i].size_x;
        int sy = Room[i].size_y;
        for(int j = x - 1 ; j < x + sx ; j++)
        {
            for(int k = y - 1 ; k < y + sy ; k++)
            {
                if(j == x - 1 || j == x + sx - 1)
                {
                    if(naghsheh[k][j] == '+')
                    {
                        if(naghsheh[k+1][j]!='#' && naghsheh[k-1][j] != '#' && naghsheh[k][j+1]!='#' && naghsheh[k][j-1]!='#')
                        {
                            naghsheh[k][j] = '|';
                            Room[i].map[k][j] = '|';
                        }
                    }
                }
                else if(k == y  - 1 || k == y + sy - 1 )
                {
                    if(naghsheh[k][j] == '+')
                    {
                        if(naghsheh[k+1][j] != '#' && naghsheh[k-1][j] != '#' && naghsheh[k][j+1] != '#' && naghsheh[k][j-1] != '#')
                        {
                            naghsheh[k][j] = '-';
                            Room[i].map[k][j] = '-';
                        }
                    }
                }
            }
        }
    }

}




void generate_treasure_room(int row , int col , char naghsheh[][MAX_SIZE])
{

    for (int i = 3; i < row ; i++)
    {
        for(int j = 0 ; j < col  ; j++)
        {
            int random = Random(0,10);
            int randgold = Random(0,10);
            if(random > 5)
            {
                if(randgold > 5)
                    naghsheh[j][i] = '.';
                else
                {
                    naghsheh[j][i] = 'G';
                    all_treasures++;
                }
            }
            else
            {
                naghsheh[j][i] = '^';
            }
        }
    }
}


void generate_corridor(rooms Room[] , int RoomNum , char naghsheh[][MAX_SIZE])
{
    for(int i = 0 ; i < RoomNum ; i++)
    {
        for(int j = 0 ; j < Room[i].numdoor ; j++)
        {
            int Rand_connect = Random(0,RoomNum - 1);
            int x_i = Room[i].door->x;
            int y_i = Room[i].door->y;
            location init = {x_i , y_i};
            int x_f = Room[Rand_connect].door->x;
            int y_f = Room[Rand_connect].door->y;
            location finish = {x_f , y_f};
            connect(init.x , init.y , finish.x , finish.y , naghsheh);
        }
    }
}


int spawn_px(rooms Room)
{
    return Random(Room.x_c + 1 , Room.size_x + Room.x_c - 1);
}

int spawn_py(rooms Room)
{
    return Random(Room.y_c + 1 , Room.size_y + Room.y_c - 1);
}




void copy_map(int row , int col , char naghsheh[][MAX_SIZE] , char dungen[][MAX_SIZE])
{
    for(int i = 0 ; i < col ; i++)
    {
        for(int j = 0 ; j < row ; j++)
        {
            naghsheh[j][i] = dungen[j][i];
        }
    }
}


void init_show(int show[MAX_SIZE][MAX_SIZE] , int row , int col)
{
    for(int i = 0 ; i < row ; i++)
    {
        for(int j = 0 ; j < col ; j++)
        {
            show[i][j] = 0;
        }
    }
}


void showroom(rooms room[] , char map[MAX_SIZE][MAX_SIZE] , int show[MAX_SIZE][MAX_SIZE] , int roomNum)
{
    int y = room[roomNum].y_c;
    int x = room[roomNum].x_c;
    int size_y = room[roomNum].size_y;
    int size_x = room[roomNum].size_x;
    for(int i = y ; i < y + size_y ; i++)
    {
        for(int j = x ; j < x + size_x ; j++)
        {
            if(istrap(map[i][j]))
                show[i][j] = 0;
            else
                show[i][j] = 1;
        }
    }
}

void showcorridor(char map[MAX_SIZE][MAX_SIZE] , int show[MAX_SIZE][MAX_SIZE] , int x , int y , int num)
{
    for(int i = y - num; i < y + num ; i++)
    {
        for(int j = x - num ; j < x + num ; j++)
        {
            show[i][j] = 1;
        }
    }
}

void showtraps(char map[MAX_SIZE][MAX_SIZE] , int show[MAX_SIZE][MAX_SIZE], int x , int y)
{
    if(istrap(map[y][x]))
    {
        show[y][x] = 1;
        map[y][x] = 't';
    }
}


void init_map(int row , int col , char map[MAX_SIZE][MAX_SIZE])
{
    clear();
    move(0,0);
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            map[j][i] = ' ';
        }
    }
}


void print_map(int row , int col , char map[MAX_SIZE][MAX_SIZE] , int show[MAX_SIZE][MAX_SIZE])
{
    clear();
    move(0,0);
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            if(show[j][i] == 1 && map[j][i] != '^')
                if(istreasure(map[j][i]))
                {
                    attron(COLOR_PAIR(6));
                    mvaddch(j , i , map[j][i]);
                    attroff(COLOR_PAIR(6));
                }
                else
                    mvaddch(j , i , map[j][i]);
            else if(map[j][i] == '^' && show[j][i] == 1)
                mvaddch(j , i , '.');
            else
                mvaddch(j , i , ' ');
        }
    }
}

void print_map_1(int row , int col , char map[MAX_SIZE][MAX_SIZE] , int show[MAX_SIZE][MAX_SIZE])
{
    clear();
    move(0,0);
    for (int i = 0; i < row; i++)
    {
        mvprintw(i , 0 , map[i]);
    }
}

void print(int row , int col , char map[MAX_SIZE][MAX_SIZE] , int show[MAX_SIZE][MAX_SIZE])
{
    clear();
    move(0,0);
    for (int i = 0; i < row + 10; i++)
    {
        for(int j = 0 ; j < col + 11 ; j++)
            mvaddch(i , j , map[i][j]);
    }
}

void draw_scoreboard(WINDOW *win, char name[MAX_SIZE][MAX_SIZE] , int score[MAX_SIZE], int num_players) {
    // Clear the window
    werase(win);
    wrefresh(win);

    // Print the title
    mvwprintw(win, 1, 10, "SCOREBOARD");

    // Print the column headers
    mvwprintw(win, 3, 2, "Rank");
    mvwprintw(win, 3, 10, "Player Name");
    mvwprintw(win, 3, 30, "Score");

    // Print the players' information
    for (int i = 0; i < num_players; i++) {
        if( i == 0 )
        {
            mvwprintw(win, 5 + i, 2, "%d", i + 1);
            mvwprintw(win, 5 + i, 10, "%s", name[i]);
            mvwprintw(win, 5 + i, 30, "%d       he is the goat!!!", score[i]);
        }
        else if( i == 1 )
        {
            mvwprintw(win, 5 + i, 2, "%d", i + 1);
            mvwprintw(win, 5 + i, 10, "%s", name[i]);
            mvwprintw(win, 5 + i, 30, "%d       My Man :)", score[i]);
        }
        else if( i == 3 )
        {
            mvwprintw(win, 5 + i, 2, "%d", i + 1);
            mvwprintw(win, 5 + i, 10, "%s", name[i]);
            mvwprintw(win, 5 + i, 30, "%d       My Man :)", score[i]);
        }
        else
        {
            mvwprintw(win, 5 + i, 2, "%d", i + 1);
            mvwprintw(win, 5 + i, 10, "%s", name[i]);
            mvwprintw(win, 5 + i, 30, "%d", score[i]);
        }
    }
    wprintw(win , "\n\n\n");
    wprintw(win , "type anything to exit!");

    // Refresh the window to show the updates
    wrefresh(win);
}


void game(){}



int main()
{



    // if(SDL_Init(SDL_INIT_AUDIO) < 0)
    // {
    //     printf("SDL couldnt initialize Eror: %s" , SDL_GetError());
    // }
    // if(Mix_OpenAudio(44100 , MIX_DEFAULT_FORMAT , 2 , 2048) < 0)
    // {
    //     printf("Error: %s" , Mix_GetError());
    // }
    setlocale(LC_ALL , "");
    initscr();
    curs_set(0);

    SeedRand();
    if(has_colors())
    {
        start_color();
    }

    // Mix_Music* music_1;
    // music_1 = NULL;
    
    init_pair(1 , COLOR_RED , COLOR_WHITE);
    init_pair(2 , COLOR_RED , COLOR_YELLOW);
    init_pair(3 , COLOR_CYAN , COLOR_BLUE);
    init_pair(4 , COLOR_GREEN , COLOR_BLACK);
    init_pair(5 , COLOR_GREEN , COLOR_YELLOW);
    init_pair(6 , COLOR_YELLOW , COLOR_BLACK);
    int row , col;
    getmaxyx(stdscr , row , col);
    // welcome_to_the_rouge();
    

    //file handling;

    //new window for menu:
    WINDOW* menu_win = newwin(row , col , 0 , 0);
    box(menu_win , 0 , 0);
    if(!has_colors()){
        addstr("SORRY :(\n");
        refresh();
        getch();
        endwin();
        return 0;
    }

    if(start_color() != OK){
        addstr("SORRY :(\n");
        refresh();
        getch();
        endwin();
        return 0;
    }
    int exit = 0;
    while(1)
    {
        if(exit == 1)
        {
            break;
        }
        clear();
        box(menu_win , 0 , 0);
        wbkgd(menu_win , COLOR_PAIR(4));
        refresh();
        wrefresh(menu_win);
        keypad(menu_win , TRUE);
        char menu[6][100] = {"<new usr>" ,
                            "<login usr>" ,
                            "<guest mode>" ,
                            "<setting>" ,
                            "<scoreboard>" ,
                            "<load last game>"};
        int highlight = 0;
        int decision;
        noecho();
        while(1){
            for(int i = 0 ; i < 6 ; i++){
                int len = strlen(menu[i]);
                if(i == highlight){
                    wattron(menu_win , A_REVERSE);
                }
                mvwprintw(menu_win , i + row/2 - 4 , col/2 - len/2 , menu[i]);
                wattroff(menu_win , A_REVERSE);
            }
            decision = wgetch(menu_win);
            switch(decision){
                case KEY_UP:
                    highlight--;
                    if(highlight == -1){
                        highlight = 5;
                    }
                    break;
                case KEY_DOWN:
                    highlight++;
                    if(highlight == 6){
                        highlight = 0;
                    }
                    break;
                default:
                    break;
            }
            if(decision == 10){
                break;
            }
        }




        if(highlight == 0)
        {
            WINDOW* new_usr_win = newwin(row , col , 0 , 0);
            box(new_usr_win , 0 , 0);
            refresh();
            wrefresh(new_usr_win);
            wbkgd(new_usr_win , COLOR_PAIR(3));
            char usr_in[3][100] = {"usr-name:" , "password:" , "e-mail:"};
            int usr_len_0 = strlen(usr_in[0]);
            int usr_len_1 = strlen(usr_in[1]);
            int usr_len_2 = strlen(usr_in[2]);
            int choose;
            int complete = 0;
            char message[3][100] = {"Please fill your usr-name (maximum usr/pass/e-mail size is 100):" ,
                                    "Please fill your password (maximum usr/pass/e-mail size is 100):" ,
                                    "Please fill your e-mail (maximum usr/pass/e-mail size is 100):"};
            int message_len[3] = {strlen(message[0]) , strlen(message[1]) , strlen(message[2])};
            for(int i = 0 ; i < 3 ; i++){
                int len = strlen(usr_in[i]);
                mvwprintw(new_usr_win , 4*(i+1) + 1 , 2 , usr_in[i]);
            }
            profile user;
            char input[3][MAX_SIZE];
            FILE * fptr_usr;
            FILE * fptr_all_names_append;
            char temp[100];
            fptr_all_names_append = fopen("all-names.txt" , "a");
            keypad(new_usr_win , TRUE);
            while(complete < 3){
                mvwprintw(new_usr_win , 2 , col/2 - message_len[complete] /2 , message[complete]);
                switch(complete){
                    case 0:
                        echo();
                        wmove(new_usr_win , 5 , usr_len_0 + 2);
                        // wgetnstr(new_usr_win , user.name , MAX_SIZE - 1);
                        wscanw(new_usr_win , " %s", user.name);
                        FILE * fptr_all_names;
                        fptr_all_names = fopen("all-names.txt" , "r");
                        char user_check[MAX_SIZE];
                        int checker = 0;
                        noecho();
                        int key = wgetch(new_usr_win);
                        while (1)
                        {
                            int a = fscanf(fptr_all_names , " %s" , user_check);
                            if(a == -1){
                                break;
                            }
                            if(strcmp(user_check , user.name) == 0){
                                checker = 1;
                                break;
                            }
                        }
                        if(checker == 1){
                            mvwprintw(new_usr_win , 3 , col/2 - 25 /2 , "choose another user-name!");
                            mvwprintw(new_usr_win , 5 , usr_len_0 + 2 , "                                                                          ");
                            wmove(new_usr_win , 5 , usr_len_0 + 2);
                            break;
                        }else{
                            fprintf(fptr_all_names_append , "%s\n" , user.name);
                            fclose(fptr_all_names_append);
                            char temp[100];
                            strcpy(temp ,user.name);
                            strcat(temp , ".txt");
                            fptr_usr = fopen(temp , "w");
                            mvwprintw(new_usr_win , 2 , col/2 - message_len[complete] /2 , "                                                               ");
                            complete++;
                            break;
                        }
                    case 1:
                        noecho();
                        wmove(new_usr_win , 9 , usr_len_1 + 2);
                        wgetnstr(new_usr_win , user.password , MAX_SIZE - 1);
                        int check = strlen(user.password);
                        if(check < 7){
                            mvwprintw(new_usr_win , 3 , col/2 - 30 /2 , "Password len is smaller than 7");
                            break;
                        }
                        fprintf(fptr_usr , "%s\n" , user.password);
                        mvwprintw(new_usr_win , 3 , col/2 - 30 /2 , "                              ");
                        mvwprintw(new_usr_win , 2 , col/2 - message_len[complete] /2 , "                                                               ");
                        complete++;
                        break;
                    case 2:
                        echo();
                        wmove(new_usr_win , 13 , usr_len_2 + 2);
                        wgetnstr(new_usr_win , user.e_mail , MAX_SIZE - 1);
                        int len_e_mail = strlen(user.e_mail);
                        int check_adsign = 0;
                        int check_dot = 0;
                        int asghar = 0;
                        int point_ad_sign;
                        int point_dot;
                        for(int i = 0 ; i < len_e_mail ; i++){
                            if(user.e_mail[i] == '@' && check_adsign < 2){
                                asghar = 1;
                                check_adsign++;
                                point_ad_sign = i;
                            }else if(user.e_mail[i] == '.' && asghar == 1 && check_dot < 2 && i > point_ad_sign + 1 && is_char(user.e_mail[i+1])){
                                check_dot++;
                            }
                        }
                        if(check_dot == 0 || check_adsign == 0){
                            mvwprintw(new_usr_win , 3 , col/2 - 30 /2 , "e-mail is not valid!");
                            break;
                        }
                        fprintf(fptr_usr , "%s\n" , user.e_mail);
                        mvwprintw(new_usr_win , 3 , col/2 - 30 /2 , "                    ");
                        complete++;
                        noecho();
                        break;
                }
                noecho();
                wrefresh(new_usr_win);
            }
            noecho();
            clear();
            WINDOW * game_menu = newwin(row , col , 0 , 0);
            box(game_menu , 0 , 0);
            keypad(game_menu , TRUE);
            refresh();
            wrefresh(game_menu);
            wbkgd(game_menu , COLOR_PAIR(3));
            char game_option[2][MAX_SIZE] = { "<new game>" ,
                                            "<load last game>"};
            int game_highlight = 0;
            int game_decision;
            while(1)
            {
                for(int i = 0 ; i < 1 ; i++)
                {
                    int game_len = strlen(game_option[i]);
                    if(i == game_highlight)
                    {
                        wattron(game_menu , A_REVERSE);
                    }
                    mvwprintw(game_menu , i + row/2 - 4 , col/2 - game_len/2 , game_option[i]);
                    wattroff(game_menu , A_REVERSE);
                }
                game_decision = wgetch(game_menu);
                switch (game_decision)
                {
                case KEY_UP:
                    game_highlight--;
                    if(game_highlight == -1)
                    {
                        game_highlight = 0;
                    }
                    break;
                case KEY_DOWN:
                    game_highlight++;
                    if(game_highlight == 1)
                    {
                        game_highlight = 0;
                    }
                    break;
                default:
                    break;
                }
                if(game_decision == 10)
                {
                    break;
                }
            }
            char file_1[MAX_SIZE] = "map-1-";
            char file_2[MAX_SIZE] = "map-2-";
            char file_3[MAX_SIZE] = "map-3-";
            char file_4[MAX_SIZE] = "map-4-";
            char file_5[MAX_SIZE] = "treasure-";
            char file_6[MAX_SIZE] = "show-1-";
            char file_7[MAX_SIZE] = "show-2-";
            char file_8[MAX_SIZE] = "show-3-";
            char file_9[MAX_SIZE] = "show-4-";
            char file_10[MAX_SIZE] = "show-";
            char file_11[MAX_SIZE] = "usr-games-";
            char file_12[MAX_SIZE] = "usr-points-";
            strcat(file_1 , user.name);
            strcat(file_1 , ".txt");
            strcat(file_2 , user.name);
            strcat(file_2 , ".txt");
            strcat(file_3 , user.name);
            strcat(file_3 , ".txt");
            strcat(file_4 , user.name);
            strcat(file_4 , ".txt");
            strcat(file_5 , user.name);
            strcat(file_5 , ".txt");
            strcat(file_6 , user.name);
            strcat(file_6 , ".txt");
            strcat(file_7 , user.name);
            strcat(file_7 , ".txt");
            strcat(file_8 , user.name);
            strcat(file_8 , ".txt");
            strcat(file_9 , user.name);
            strcat(file_9 , ".txt");
            strcat(file_10 , user.name);
            strcat(file_10 , ".txt");
            strcat(file_11 , user.name);
            strcat(file_11 , ".txt");
            strcat(file_12 , user.name);
            strcat(file_12 , ".txt");
            if(game_highlight == 0)
            {
                noecho();
                keypad(stdscr , TRUE);
                clear();
                bkgd(' ');
                int out = 0;
                int finish = 0;
                while (1)
                {
                    if(out == 2 || out == 1)
                    {
                        clear();
                        WINDOW * option_menu = newwin(row , col , 0 , 0);
                        box(option_menu , 0 , 0);
                        keypad(option_menu , TRUE);
                        refresh();
                        wrefresh(option_menu);
                        wbkgd(option_menu , COLOR_PAIR(4));
                        char options[2][MAX_SIZE] = { "<new game>" ,
                                                        "<exit>"};
                        int highlight_option = 0;
                        int decision_option;
                        wattron(option_menu , COLOR_PAIR(6));
                        if(out == 2)
                            mvwprintw(option_menu , 0 , col/2 - 8/2 , "YOU LOST");
                        else if(out == 1)
                        {
                            mvwprintw(option_menu , 0 , col/2 - 7/2 , "YOU WON");
                        }
                        wattroff(option_menu , COLOR_PAIR(6));
                        while(1)
                        {
                            for(int i = 0 ; i < 2 ; i++)
                            {
                                int game_len = strlen(options[i]);
                                if(i == highlight_option)
                                {
                                    wattron(option_menu , A_REVERSE);
                                }
                                mvwprintw(option_menu , i + row/2 - 4 , col/2 - game_len/2 , options[i]);
                                wattroff(option_menu , A_REVERSE);
                            }
                            decision_option = wgetch(option_menu);
                            switch (decision_option)
                            {
                            case KEY_UP:
                                highlight_option--;
                                if(highlight_option == -1)
                                {
                                    highlight_option = 1;
                                }
                                break;
                            case KEY_DOWN:
                                highlight_option++;
                                if(highlight_option == 2)
                                {
                                    highlight_option = 0;
                                }
                            default:
                                break;
                            }
                            if(decision_option == 10)
                            {
                                break;
                            }
                        }
                        if(highlight_option == 1)
                        {
                            exit = 1;
                            break;
                        }
                        else
                        {
                            out = 0;
                        }
                    }
                    
                    rooms Room[4][9];
                    location pelle[6];
                    location beasts[5][4];
                    int RoomNum[4];
                    for(int i = 0 ; i < 4 ; i++)
                    {
                        dungeons[i].RoomNum = Random(3 , 9);
                    }
                    generate_map(row , col , dungeons[0].room , dungeons[0].RoomNum , dungeons[0].naghseh , 1 , pelle , beasts[1]);
                    generate_corridor(dungeons[0].room , dungeons[0].RoomNum , dungeons[0].naghseh);
                    generate_map(row , col , dungeons[1].room , dungeons[1].RoomNum , dungeons[1].naghseh , 2 , pelle , beasts[2]);
                    generate_corridor(dungeons[1].room , dungeons[1].RoomNum , dungeons[1].naghseh);
                    generate_map(row , col , dungeons[2].room , dungeons[2].RoomNum , dungeons[2].naghseh , 3 , pelle , beasts[3]);
                    generate_corridor(dungeons[2].room , dungeons[2].RoomNum , dungeons[2].naghseh);
                    generate_map(row , col , dungeons[3].room , dungeons[3].RoomNum , dungeons[3].naghseh , 4 , pelle , beasts[4]);
                    generate_corridor(dungeons[3].room , dungeons[3].RoomNum , dungeons[3].naghseh);
                    generate_treasure_room(row , col  , dungeons[4].naghseh );
                    remove(file_1);
                    remove(file_2);
                    remove(file_3);
                    remove(file_4);
                    remove(file_5);
                    remove(file_6);
                    remove(file_7);
                    remove(file_8);
                    remove(file_9);
                    remove(file_10);
                    remove(file_11);
                    profile guest;
                    strcpy(guest.name , "guest-usr");
                    user.gold_reserve = 0;
                    
                    guest.health = health_num;
                    guest.points = 0;
                    guest.gold_reserve = 0;
                    guest.weapon_num = 1;
                    strcpy(guest.inventory[0] , "NO WEAPON");
                    guest.experience = 1;
                    int number = Random(0 , RoomNum[0] - 1);
                    int y_loc;
                    int x_loc;
                    y_loc = spawn_py(dungeons[0].room[number]);
                    x_loc = spawn_px(dungeons[0].room[number]);
                    int floor = 0;
                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                    attron(COLOR_PAIR(4));
                    bkgd(COLOR_PAIR(4));
                    int move = 0;
                    init_show(dungeons[floor].show , row , col);
                    showroom(dungeons[floor].room , dungeons[floor].naghseh , dungeons[floor].show , number);
                    while(1)
                    {
                        
                        clear();
                        if(out == 1)
                        {
                            break;
                        }
                        if(out == 2)
                        {
                            break;
                        }
                        refresh();
                        move++;
                        if(move%4 == 0)
                            guest.health--;
                        showcorridor(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc , 5);
                        for(int k = 0 ; k < 4 ; k++)
                        {
                            if (isfollower(dungeons[floor].naghseh[beasts[floor][k].y][beasts[floor][k].x]))
                            {
                                int range = range_monster(dungeons[floor].naghseh[beasts[floor][k].y][beasts[floor][k].x]);
                                int hurt = 0;
                                int x_m = beasts[floor][k].x;
                                int y_m = beasts[floor][k].y;
                                char temp = dungeons[floor].naghseh[beasts[floor][k].y][beasts[floor][k].x];
                                dungeons[floor].naghseh[beasts[floor][k].y][beasts[floor][k].x] = '.';
                                int distance_x = abs(x_loc - x_m);
                                int distance_y = abs(y_loc - y_m);
                                if((distance_x != 1 || distance_y != 1) && (distance_x < range && distance_y < range))
                                {
                                    if(abs(x_loc - (x_m - 1)) <= distance_x &&
                                    (!iswall(dungeons[floor].naghseh[y_m][x_m - 1]) && !iswindow(dungeons[floor].naghseh[y_m][x_m - 1]) && !isdoor(dungeons[floor].naghseh[y_m][x_m - 1]) && !ispillar(dungeons[floor].naghseh[y_m][x_m - 1])) && 
                                    abs(x_loc - (x_m - 1)) > 0)
                                    {
                                        x_m--;
                                        beasts[floor][k].x = x_m;
                                    }
                                    else if(abs(x_loc - (x_m + 1)) <= distance_x && 
                                    (!iswall(dungeons[floor].naghseh[y_m][x_m + 1]) && !iswindow(dungeons[floor].naghseh[y_m][x_m + 1]) && !isdoor(dungeons[floor].naghseh[y_m][x_m + 1]) && !ispillar(dungeons[floor].naghseh[y_m][x_m + 1])) && 
                                    abs(x_loc - (x_m + 1)) > 0)
                                    {
                                        x_m++;
                                        beasts[floor][k].x = x_m;
                                    }
                                    else if(abs(y_loc - (y_m - 1)) <= distance_y && 
                                    (!iswall(dungeons[floor].naghseh[y_m - 1][x_m]) && !iswindow(dungeons[floor].naghseh[y_m - 1][x_m]) && !isdoor(dungeons[floor].naghseh[y_m - 1][x_m]) && !ispillar(dungeons[floor].naghseh[y_m - 1][x_m])) && 
                                    abs(y_loc - (y_m - 1)) > 0)
                                    {
                                        y_m--;
                                        beasts[floor][k].y = y_m;
                                    }
                                    else if(abs(y_loc - (y_m + 1)) > 0 && 
                                    (!iswall(dungeons[floor].naghseh[y_m + 1][x_m]) && !iswindow(dungeons[floor].naghseh[y_m + 1][x_m]) && !isdoor(dungeons[floor].naghseh[y_m + 1][x_m]) && !ispillar(dungeons[floor].naghseh[y_m + 1][x_m])))
                                    {
                                        y_m++;
                                        beasts[floor][k].y = y_m;
                                    }
                                    hurt = 0;
                                }
                                else if(distance_x == 1 && distance_y == 1)
                                {
                                    hurt = 1;
                                }
                                dungeons[floor].naghseh[beasts[floor][k].y][beasts[floor][k].x] = temp;
                                if(hurt)
                                {
                                    int asib = damage(temp);
                                    if(guest.health - asib >= 0)
                                    {
                                        guest.health-=asib;
                                        mvprintw(0,40 , "You got hit by a monster!");
                                    }
                                    else
                                    {
                                        out = 2;
                                        continue;
                                    }
                                }
                            }
                        }
                        print_map(row , col , dungeons[floor].naghseh , dungeons[floor].show);
                        mvprintw(y_loc , x_loc , "@");
                        mvprintw(0 , 0 , "your health is %d |" , guest.health , floor);
                        mvprintw(0 , 20 , "your point is %d |" , guest.points);
                        int kilid = getch();
                        switch (kilid)
                        {
                        case KEY_UP:
                            if(isfloor(dungeons[floor].naghseh[y_loc - 1][x_loc]) ||
                               iscorridor(dungeons[floor].naghseh[y_loc - 1][x_loc]) ||
                               isdoor(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               istrap(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               isfood(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               istair(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               isgold(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               ismace(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               isdagger(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               iswand(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               isarrow(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               issword(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               istreasure(dungeons[floor].naghseh[y_loc - 1][x_loc]))
                            {
                                if(iswall(dungeons[floor].naghseh[y_loc - 1][x_loc]) || ispillar(dungeons[floor].naghseh[y_loc - 1][x_loc]) || iswindow(dungeons[floor].naghseh[y_loc - 1][x_loc]))
                                {
                                    break;
                                }
                                else if(istrap(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.health - 10 >= 0)
                                    {
                                        showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc);
                                        guest.health -= 10;
                                    }
                                    else
                                        out = 2;
                                }
                                else if(dungeons[floor].naghseh[y_loc][x_loc] == 'f')
                                {
                                    if(guest.health + 10 <= health_num)
                                    {
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        guest.health+=10;
                                    }
                                }
                                else if(dungeons[floor].naghseh[y_loc][x_loc] == 'G')
                                {
                                    guest.points++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(ismace(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Mace (M)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(iswand(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Magic Wand (I)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(isdagger(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Dagger (p)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(isarrow(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Arrow (Y)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(issword(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Sword (P)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                y_loc--;
                            }
                            break;
                        case KEY_DOWN:
                            if(isfloor(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            iscorridor(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            isdoor(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            istrap(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            isfood(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            istair(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            isgold(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            ismace(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            isdagger(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            iswand(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            isarrow(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            issword(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            istreasure(dungeons[floor].naghseh[y_loc + 1][x_loc]))
                            {
                                if(dungeons[floor].naghseh[y_loc + 1][x_loc] == '-'|| dungeons[floor].naghseh[y_loc + 1][x_loc] == '0' || dungeons[floor].naghseh[y_loc + 1][x_loc] == '=')
                                {
                                    break;
                                }
                                else if(istrap(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.health - 10 >= 0)
                                    {
                                        showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc);
                                        guest.health -= 10;
                                    }
                                    else
                                        out = 2;
                                }
                                else if(dungeons[floor].naghseh[y_loc][x_loc] == 'f')
                                {
                                    if(guest.health + 10 <= health_num)
                                    {
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        guest.health+=10;
                                    }
                                }
                                else if(dungeons[floor].naghseh[y_loc][x_loc] == 'G')
                                {
                                    guest.points++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(ismace(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Mace (M)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(iswand(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Magic Wand (I)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(isdagger(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Dagger (p)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(isarrow(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Arrow (Y)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(issword(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Sword (P)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                y_loc++;
                            }
                            break;
                        case KEY_LEFT:
                            if(isfloor(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            iscorridor(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            isdoor(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            istrap(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            isfood(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            istair(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            isgold(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            ismace(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            isdagger(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            iswand(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            isarrow(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            issword(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            istreasure(dungeons[floor].naghseh[y_loc][x_loc - 1]))
                            {
                                if(dungeons[floor].naghseh[y_loc][x_loc - 1] == '|'|| dungeons[floor].naghseh[y_loc][x_loc - 1] == '0' || dungeons[floor].naghseh[y_loc][x_loc - 1] == '=')
                                {
                                    break;
                                }
                                else if(istrap(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.health - 10 >= 0)
                                    {
                                        showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc);
                                        guest.health -= 10;
                                    }
                                    else
                                        out = 2;
                                }
                                else if(dungeons[floor].naghseh[y_loc][x_loc] == 'f')
                                {
                                    if(guest.health + 10 <= health_num)
                                    {
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        guest.health+=10;
                                    }
                                }
                                else if(dungeons[floor].naghseh[y_loc][x_loc] == 'G')
                                {
                                    guest.points++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(ismace(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Mace (M)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(iswand(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Magic Wand (I)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(isdagger(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Dagger (p)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(isarrow(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Arrow (Y)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(issword(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Sword (P)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                x_loc--;
                            }
                            break;
                        case KEY_RIGHT:
                            if(isfloor(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            iscorridor(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            isdoor(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            istrap(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            isfood(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            istair(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            isgold(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            ismace(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            isdagger(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            iswand(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            isarrow(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            issword(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            istreasure(dungeons[floor].naghseh[y_loc][x_loc + 1]))
                            {
                                if(dungeons[floor].naghseh[y_loc][x_loc + 1] == '|'|| dungeons[floor].naghseh[y_loc][x_loc + 1] == '0' || dungeons[floor].naghseh[y_loc][x_loc + 1] == '=')
                                {
                                    break;
                                }
                                else if(istrap(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.health - 10 >= 0)
                                    {
                                        showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc);
                                        guest.health -= 10;
                                    }
                                    else
                                        out = 2;
                                }
                                else if(dungeons[floor].naghseh[y_loc][x_loc] == 'f')
                                {
                                    if(guest.health + 10 <= health_num)
                                    {
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        guest.health+=10;
                                    }
                                }
                                else if(dungeons[floor].naghseh[y_loc][x_loc] == 'G')
                                {
                                    guest.points++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(ismace(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Mace (M)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(iswand(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Magic Wand (I)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(isdagger(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Dagger (p)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(isarrow(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Arrow (Y)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(issword(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Sword (P)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                x_loc++;
                            }
                            break;
                        
                        case '>':
                            if(istair(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                switch (floor)
                                {
                                case 0:
                                    if(pelle[0].x == x_loc && pelle[0].y == y_loc)
                                    {
                                        floor++;
                                        y_loc = pelle[1].y;
                                        x_loc = pelle[1].x;
                                    }
                                    break;
                                case 1:
                                    if(pelle[1].x == x_loc && pelle[1].y == y_loc)
                                    {
                                        floor--;
                                        y_loc = pelle[0].y;
                                        x_loc = pelle[0].x;
                                    }
                                    else if(pelle[2].x == x_loc && pelle[2].y == y_loc)
                                    {
                                        floor++;
                                        y_loc = pelle[3].y;
                                        x_loc = pelle[3].x;
                                    }
                                    break;
                                case 2:
                                    if(pelle[3].x == x_loc && pelle[3].y == y_loc)
                                    {
                                        floor--;
                                        y_loc = pelle[2].y;
                                        x_loc = pelle[2].x;
                                    }
                                    else if(pelle[4].x == x_loc && pelle[4].y == y_loc)
                                    {
                                        floor++;
                                        y_loc = pelle[5].y;
                                        x_loc = pelle[5].x;
                                    }
                                    break;
                                case 3:
                                    if(pelle[5].x == x_loc && pelle[5].y == y_loc)
                                    {
                                        floor--;
                                        y_loc = pelle[4].y;
                                        x_loc = pelle[4].x;
                                    }
                                    break;
                                default:
                                    break;
                                }
                            }
                            else if(istreasure(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                x_loc = 10;
                                y_loc = 10;
                                floor++;
                                out = 1;
                                guest.points+=100;
                            }
                            break;
                        case 'i':
                            WINDOW* inventory = newwin(row , col , 0 , 0);
                            box(inventory , 0 , 0);
                            refresh();
                            keypad(inventory , TRUE);
                            wrefresh(inventory);
                            wbkgd(inventory , COLOR_PAIR(4));
                            int inventory_highlight = 0;
                            int inventory_decision;
                            while(1)
                            {
                                for(int i = 0 ; i < guest.weapon_num ; i++)
                                {
                                    int item_len = strlen(guest.inventory[i]);
                                    if(i == inventory_highlight)
                                    {
                                        wattron(inventory , A_REVERSE);
                                    }
                                    mvwprintw(inventory , i + 1 , col/2 - item_len/2 , guest.inventory[i]);
                                    wattroff(inventory , A_REVERSE);
                                }
                                inventory_decision = wgetch(inventory);
                                switch (inventory_decision)
                                {
                                case KEY_UP:
                                    inventory_highlight--;
                                    if(inventory_highlight == -1)
                                    {
                                        inventory_highlight = guest.weapon_num - 1;
                                    }
                                    break;
                                case KEY_DOWN:
                                    inventory_highlight++;
                                    if(inventory_highlight == guest.weapon_num)
                                    {
                                        inventory_highlight = 0;
                                    }
                                    break;
                                default:
                                    break;
                                }
                                if(inventory_decision == 10)
                                {
                                    break;
                                }
                                
                            
                                if(inventory_highlight == 0)
                                {
                                    if(strcmp(guest.inventory[inventory_highlight] , "Mace (M)") == 0)
                                    {
                                        guest.weapon = 5;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Dagger (p)") == 0)
                                    {
                                        guest.weapon = 12;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Magic Wand (I)") == 0)
                                    {
                                        guest.weapon = 15;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Arrow (Y)") == 0)
                                    {
                                        guest.weapon = 5;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Sword (P)") == 0)
                                    {
                                        guest.weapon = 10;
                                    }
                                }
                                else if(inventory_highlight == 1)
                                {
                                    if(strcmp(guest.inventory[inventory_highlight] , "Mace (M)") == 0)
                                    {
                                        guest.weapon = 5;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Dagger (p)") == 0)
                                    {
                                        guest.weapon = 12;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Magic Wand (I)") == 0)
                                    {
                                        guest.weapon = 15;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Arrow (Y)") == 0)
                                    {
                                        guest.weapon = 5;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Sword (P)") == 0)
                                    {
                                        guest.weapon = 10;
                                    }
                                }
                                else if(inventory_highlight == 2)
                                {
                                    if(strcmp(guest.inventory[inventory_highlight] , "Mace (M)") == 0)
                                    {
                                        guest.weapon = 5;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Dagger (p)") == 0)
                                    {
                                        guest.weapon = 12;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Magic Wand (I)") == 0)
                                    {
                                        guest.weapon = 15;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Arrow (Y)") == 0)
                                    {
                                        guest.weapon = 5;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Sword (P)") == 0)
                                    {
                                        guest.weapon = 10;
                                    }
                                }
                                else if(inventory_highlight == 3)
                                {
                                    if(strcmp(guest.inventory[inventory_highlight] , "Mace (M)") == 0)
                                    {
                                        guest.weapon = 5;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Dagger (p)") == 0)
                                    {
                                        guest.weapon = 12;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Magic Wand (I)") == 0)
                                    {
                                        guest.weapon = 15;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Arrow (Y)") == 0)
                                    {
                                        guest.weapon = 5;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Sword (P)") == 0)
                                    {
                                        guest.weapon = 10;
                                    }
                                }
                                else if(inventory_highlight == 4)
                                {
                                    if(strcmp(guest.inventory[inventory_highlight] , "Mace (M)") == 0)
                                    {
                                        guest.weapon = 5;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Dagger (p)") == 0)
                                    {
                                        guest.weapon = 12;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Magic Wand (I)") == 0)
                                    {
                                        guest.weapon = 15;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Arrow (Y)") == 0)
                                    {
                                        guest.weapon = 5;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Sword (P)") == 0)
                                    {
                                        guest.weapon = 10;
                                    }
                                }
                            }
                            break;
                        case 's':
                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc + 1 , y_loc + 1);
                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc - 1 , y_loc - 1);
                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc - 1 , y_loc);
                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc + 1 , y_loc);
                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc - 1);
                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc + 1);
                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc - 1 , y_loc + 1);
                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc + 1 , y_loc - 1);
                            break;
                        case 'w':
                            if(ismace(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(strcmp(guest.inventory[1] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[1] , "Mace (M)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[2] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[2] , "Mace (M)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[3] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[3] , "Mace (M)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[4] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[4] , "Mace (M)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[5] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[5] , "Mace (M)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else
                                {
                                    char weap;
                                    if(strcmp(guest.inventory[5] , "Mace (M)") == 0)
                                    {
                                        weap = 'M';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Dagger (p)") == 0)
                                    {
                                        weap = 'p';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Magic Wand (I)") == 0)
                                    {
                                        weap = 'I';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Arrow (Y)") == 0)
                                    {
                                        weap = 'Y';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Sword (P)") == 0)
                                    {
                                        weap = 'P';
                                    }
                                    dungeons[floor].naghseh[y_loc][x_loc] = weap;
                                    strcpy(guest.inventory[5] , "Mace (M)");
                                }
                            }
                            else if(iswand(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(strcmp(guest.inventory[1] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[1] , "Magic Wand (I)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[2] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[2] , "Magic Wand (I)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[3] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[3] , "Magic Wand (I)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[4] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[4] , "Magic Wand (I)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[5] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[5] , "Magic Wand (I)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else
                                {
                                    char weap;
                                    if(strcmp(guest.inventory[5] , "Mace (M)") == 0)
                                    {
                                        weap = 'M';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Dagger (p)") == 0)
                                    {
                                        weap = 'p';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Magic Wand (I)") == 0)
                                    {
                                        weap = 'I';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Arrow (Y)") == 0)
                                    {
                                        weap = 'Y';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Sword (P)") == 0)
                                    {
                                        weap = 'P';
                                    }
                                    dungeons[floor].naghseh[y_loc][x_loc] = weap;
                                    strcpy(guest.inventory[5] , "Magic Wand (I)");
                                }
                            }
                            else if(isdagger(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(strcmp(guest.inventory[1] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[1] , "Dagger (p)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[2] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[2] , "Dagger (p)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[3] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[3] , "Dagger (p)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[4] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[4] , "Dagger (p)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[5] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[5] , "Dagger (p)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else
                                {
                                    char weap;
                                    if(strcmp(guest.inventory[5] , "Mace (M)") == 0)
                                    {
                                        weap = 'M';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Dagger (p)") == 0)
                                    {
                                        weap = 'p';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Magic Wand (I)") == 0)
                                    {
                                        weap = 'I';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Arrow (Y)") == 0)
                                    {
                                        weap = 'Y';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Sword (P)") == 0)
                                    {
                                        weap = 'P';
                                    }
                                    dungeons[floor].naghseh[y_loc][x_loc] = weap;
                                    strcpy(guest.inventory[5] , "Dagger (p)");
                                }
                            }
                            else if(isarrow(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(strcmp(guest.inventory[1] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[1] , "Arrow (Y)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[2] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[2] , "Arrow (Y)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[3] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[3] , "Arrow (Y)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[4] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[4] , "Arrow (Y)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[5] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[5] , "Arrow (Y)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else
                                {
                                    char weap;
                                    if(strcmp(guest.inventory[5] , "Mace (M)") == 0)
                                    {
                                        weap = 'M';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Dagger (p)") == 0)
                                    {
                                        weap = 'p';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Magic Wand (I)") == 0)
                                    {
                                        weap = 'I';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Arrow (Y)") == 0)
                                    {
                                        weap = 'Y';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Sword (P)") == 0)
                                    {
                                        weap = 'P';
                                    }
                                    dungeons[floor].naghseh[y_loc][x_loc] = weap;
                                    strcpy(guest.inventory[5] , "Arrow (Y)");
                                }
                            }
                            else if(issword(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(strcmp(guest.inventory[1] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[1] , "Sword (P)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[2] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[2] , "Sword (P)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[3] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[3] , "Sword (P)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[4] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[4] , "Sword (P)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[5] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[5] , "Sword (P)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else
                                {
                                    char weap;
                                    if(strcmp(guest.inventory[5] , "Mace (M)") == 0)
                                    {
                                        weap = 'M';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Dagger (p)") == 0)
                                    {
                                        weap = 'p';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Magic Wand (I)") == 0)
                                    {
                                        weap = 'I';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Arrow (Y)") == 0)
                                    {
                                        weap = 'Y';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Sword (P)") == 0)
                                    {
                                        weap = 'P';
                                    }
                                    dungeons[floor].naghseh[y_loc][x_loc] = weap;
                                    strcpy(guest.inventory[5] , "Sword (P)");
                                }
                            }
                            break;
                        case 'S':
                            WINDOW* setting = newwin(row , col , 0 , 0);
                            box(setting , 0 , 0);
                            refresh();
                            keypad(setting , TRUE);
                            wrefresh(setting);
                            wbkgd(setting , COLOR_PAIR(4));
                            char setting_option[2][MAX_SIZE] = {"SAVE" , "EXIT"};
                            int setting_highlight = 0;
                            int setting_decision;
                            while (1)
                            {
                                for(int i = 0 ; i < 2 ; i++)
                                {
                                    int setting_len = strlen(setting_option[i]);
                                    if(i == setting_highlight)
                                    {
                                        wattron(setting , A_REVERSE);
                                    }
                                    mvwprintw(setting , i + row/2 - 4 , col/2 - setting_len/2 , setting_option[i]);
                                    wattroff(setting , A_REVERSE);
                                }
                                setting_decision = wgetch(setting);
                                switch (setting_decision)
                                {
                                case KEY_UP:
                                    setting_highlight--;
                                    if(setting_highlight == -1)
                                    {
                                        setting_highlight = 1;
                                    }
                                    break;
                                case KEY_DOWN:
                                    setting_highlight++;
                                    if(setting_highlight == 2)
                                    {
                                        setting_highlight = 0;
                                    }
                                    break;
                                default:
                                    break;
                                }
                                if(setting_decision == 10)
                                {
                                    break;
                                }
                            }
                            if(setting_highlight == 0)
                                {
                                    FILE * map_1 = fopen(file_1 , "w");
                                    FILE * map_2 = fopen(file_2 , "w");
                                    FILE * map_3 = fopen(file_3 , "w");
                                    FILE * map_4 = fopen(file_4 , "w");
                                    FILE * treasure_map = fopen(file_5 , "w");
                                    FILE * show_1 = fopen(file_6 , "w");
                                    FILE * show_2 = fopen(file_7 , "w");
                                    FILE * show_3 = fopen(file_8 , "w");
                                    FILE * show_4 = fopen(file_9 , "w");
                                    FILE * show_treasure = fopen(file_10 , "w");
                                    FILE * guestfile = fopen(file_11 , "w");
                                    FILE * points = fopen(file_12 , "w");
                                    fprintf(points , "%d" , user.gold_reserve + guest.points);
                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        fprintf(map_1 ,"%s\n"  , dungeons[0].naghseh[i]);
                                    }
                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        fprintf(map_2 ,"%s\n"  , dungeons[1].naghseh[i]);
                                    }
                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        fprintf(map_3 ,"%s\n"  , dungeons[2].naghseh[i]);
                                    }
                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        fprintf(map_4 ,"%s\n"  , dungeons[3].naghseh[i]);
                                    }
                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        fprintf(treasure_map ,"%s\n"  , dungeons[4].naghseh[i]);
                                    }

                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        for(int j = 0 ; j < col ; j++)
                                        {
                                            fprintf(show_1 , "%d " , dungeons[0].show[i][j]);
                                        }
                                        fprintf(show_1 , "\n");
                                    }

                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        for(int j = 0 ; j < col ; j++)
                                        {
                                            fprintf(show_2 , "%d " , dungeons[0].show[i][j]);
                                        }
                                        fprintf(show_2 , "\n");
                                    }

                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        for(int j = 0 ; j < col ; j++)
                                        {
                                            fprintf(show_3 , "%d " , dungeons[0].show[i][j]);
                                        }
                                        fprintf(show_3 , "\n");
                                    }

                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        for(int j = 0 ; j < col ; j++)
                                        {
                                            fprintf(show_4 , "%d " , dungeons[0].show[i][j]);
                                        }
                                        fprintf(show_4 , "\n");
                                    }

                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        for(int j = 0 ; j < col ; j++)
                                        {
                                            fprintf(show_treasure , "%d " , dungeons[0].show[i][j]);
                                        }
                                        fprintf(show_treasure , "\n");
                                    }
                                    fprintf(guestfile , "%d\n" , guest.health);
                                    fprintf(guestfile , "%d\n" , guest.points);
                                    fprintf(guestfile , "%d\n" , guest.experience);
                                    fprintf(guestfile , "%d\n" , y_loc);
                                    fprintf(guestfile , "%d\n" , x_loc);
                                    fprintf(guestfile , "%d\n" , floor);
                                    fprintf(guestfile , "%d\n" , pelle[0].x);
                                    fprintf(guestfile , "%d\n" , pelle[0].y);
                                    fprintf(guestfile , "%d\n" , pelle[1].x);
                                    fprintf(guestfile , "%d\n" , pelle[1].y);
                                    fprintf(guestfile , "%d\n" , pelle[2].x);
                                    fprintf(guestfile , "%d\n" , pelle[2].y);
                                    fprintf(guestfile , "%d\n" , pelle[3].x);
                                    fprintf(guestfile , "%d\n" , pelle[3].y);
                                    fprintf(guestfile , "%d\n" , pelle[4].x);
                                    fprintf(guestfile , "%d\n" , pelle[4].y);
                                    fprintf(guestfile , "%d\n" , pelle[5].x);
                                    fprintf(guestfile , "%d\n" , pelle[5].y);
                                    fprintf(guestfile , "%d\n" , guest.weapon);
                                    for(int i = 0 ; i < 5 ; i++)
                                    {
                                        for(int j = 0 ; j < 4 ; j++)
                                            fprintf(guestfile , "%d %d" , beasts[i][j].x , beasts[i][j].y);
                                        fprintf(guestfile , "\n");
                                    }
                                    for(int i = 0 ; i < 10 ; i++)
                                    {
                                        fprintf(guestfile , "%s\n" , guest.inventory[i]);
                                    }
                                    clear();
                                    out = 1;
                                }
                            else
                            {
                                out = 2;
                            }
                            
                            break;
                        default:
                            break;
                        }
                        
                    }
                }

            }


        }
        else if(highlight == 1)
        {
            WINDOW* new_usr_win = newwin(row , col , 0 , 0);
            box(new_usr_win , 0 , 0);
            refresh();
            wrefresh(new_usr_win);
            wbkgd(new_usr_win , COLOR_PAIR(3));
            char usr_in[3][100] = {"usr-name:" , "password:" , "e-mail:"};
            int usr_len_0 = strlen(usr_in[0]);
            int usr_len_1 = strlen(usr_in[1]);
            int usr_len_2 = strlen(usr_in[2]);
            int choose;
            int complete = 0;
            char message[3][100] = {"Please fill your usr-name (maximum usr/pass/e-mail size is 100):" ,
                                    "Please fill your password if you forgot it fill your e-mail (maximum usr/pass/e-mail size is 100):" ,
                                    "Please fill your e-mail (maximum usr/pass/e-mail size is 100):"};
            int message_len[3] = {strlen(message[0]) , strlen(message[1]) , strlen(message[2])};
            for(int i = 0 ; i < 3 ; i++){
                int len = strlen(usr_in[i]);
                mvwprintw(new_usr_win , 4*(i+1) + 1 , 2 , usr_in[i]);
            }
            profile user;
            char input[3][MAX_SIZE];
            FILE * fptr_usr;
            keypad(new_usr_win , TRUE);
            char File[100];
            char check_data[2][100];
            while(complete < 3){
                mvwprintw(new_usr_win , 2 , col/2 - message_len[complete] /2 , message[complete]);
                switch(complete){
                    case 0:
                        echo();
                        wmove(new_usr_win , 5 , usr_len_0 + 2);
                        wscanw(new_usr_win , " %s", user.name);
                        FILE * fptr_all_names;
                        fptr_all_names = fopen("all-names.txt" , "r");
                        char user_check[MAX_SIZE];
                        int checker = 0;
                        noecho();
                        int key = wgetch(new_usr_win);
                        while (1)
                        {
                            fscanf(fptr_all_names , " %s" , user_check);
                            if(strcmp(user_check , user.name) == 0){
                                checker = 1;
                                break;
                            }
                        }
                        if(checker == 1){
                            strcpy(File ,user.name);
                            strcat(File , ".txt");
                            complete++;
                            break;
                        }else{
                            mvwprintw(new_usr_win , 3 , col/2 - 24 /2 , "user name doesnt exists!");
                            mvwprintw(new_usr_win , 5 , usr_len_0 + 2 , "                                                                          ");
                            wmove(new_usr_win , 5 , usr_len_0 + 2);
                            break;
                        }
                    case 1:
                        noecho();
                        wmove(new_usr_win , 9 , usr_len_1 + 2);
                        wgetnstr(new_usr_win , user.password , MAX_SIZE - 1);
                        int check = strlen(user.password);
                        fptr_usr = fopen(File , "r");
                        int a = 0;
                        int k = 0;
                        while(a != -1){
                            a = fscanf(fptr_usr , " %s" , check_data[k]);
                            k++;
                        }
                        if(strcmp(check_data[0] , user.password) == 0){
                            complete = 3;
                            break;
                        }
                        mvwprintw(new_usr_win , 3 , col/2 - 30 /2 , "                              ");
                        mvwprintw(new_usr_win , 2 , col/2 - message_len[complete] /2 , "                                                               ");
                        complete++;
                        break;
                    case 2:
                        echo();
                        wmove(new_usr_win , 13 , usr_len_2 + 2);
                        wgetnstr(new_usr_win , user.e_mail , MAX_SIZE - 1);
                        int len_e_mail = strlen(user.e_mail);
                        int check_adsign = 0;
                        int check_dot = 0;
                        int asghar = 0;
                        int point_ad_sign;
                        int point_dot;
                        if(strcmp(check_data[1] , user.e_mail) != 0){
                            mvwprintw(new_usr_win , 3 , col/2 - 30 /2 , "e-mail is not wrong!");
                            break;
                        }
                        mvwprintw(new_usr_win , 3 , col/2 - 30 /2 , "                    ");
                        complete++;
                        noecho();
                        break;
                }
                noecho();
                wrefresh(new_usr_win);
            }
            noecho();
            clear();
            WINDOW * game_menu = newwin(row , col , 0 , 0);
            box(game_menu , 0 , 0);
            keypad(game_menu , TRUE);
            refresh();
            wrefresh(game_menu);
            wbkgd(game_menu , COLOR_PAIR(3));
            char game_option[2][MAX_SIZE] = { "<new game>" ,
                                            "<load last game>"};
            int game_highlight = 0;
            int game_decision;
            while(1)
            {
                for(int i = 0 ; i < 2 ; i++)
                {
                    int game_len = strlen(game_option[i]);
                    if(i == game_highlight)
                    {
                        wattron(game_menu , A_REVERSE);
                    }
                    mvwprintw(game_menu , i + row/2 - 4 , col/2 - game_len/2 , game_option[i]);
                    wattroff(game_menu , A_REVERSE);
                }
                game_decision = wgetch(game_menu);
                switch (game_decision)
                {
                case KEY_UP:
                    game_highlight--;
                    if(game_highlight == -1)
                    {
                        game_highlight = 1;
                    }
                    break;
                case KEY_DOWN:
                    game_highlight++;
                    if(game_highlight == 2)
                    {
                        game_highlight = 0;
                    }
                default:
                    break;
                }
                if(game_decision == 10)
                {
                    break;
                }
            }
            char file_1[MAX_SIZE] = "map-1-";
            char file_2[MAX_SIZE] = "map-2-";
            char file_3[MAX_SIZE] = "map-3-";
            char file_4[MAX_SIZE] = "map-4-";
            char file_5[MAX_SIZE] = "treasure-";
            char file_6[MAX_SIZE] = "show-1-";
            char file_7[MAX_SIZE] = "show-2-";
            char file_8[MAX_SIZE] = "show-3-";
            char file_9[MAX_SIZE] = "show-4-";
            char file_10[MAX_SIZE] = "show-";
            char file_11[MAX_SIZE] = "usr-games-";
            char file_12[MAX_SIZE] = "usr-points-";
            strcat(file_1 , user.name);
            strcat(file_1 , ".txt");
            strcat(file_2 , user.name);
            strcat(file_2 , ".txt");
            strcat(file_3 , user.name);
            strcat(file_3 , ".txt");
            strcat(file_4 , user.name);
            strcat(file_4 , ".txt");
            strcat(file_5 , user.name);
            strcat(file_5 , ".txt");
            strcat(file_6 , user.name);
            strcat(file_6 , ".txt");
            strcat(file_7 , user.name);
            strcat(file_7 , ".txt");
            strcat(file_8 , user.name);
            strcat(file_8 , ".txt");
            strcat(file_9 , user.name);
            strcat(file_9 , ".txt");
            strcat(file_10 , user.name);
            strcat(file_10 , ".txt");
            strcat(file_11 , user.name);
            strcat(file_11 , ".txt");
            strcat(file_12 , user.name);
            strcat(file_12 , ".txt");
            if(game_highlight == 0)
            {
                noecho();
                keypad(stdscr , TRUE);
                clear();
                bkgd(' ');
                int out = 0;
                int finish = 0;
                while (1)
                {
                    if(out == 2 || out == 1)
                    {
                        clear();
                        WINDOW * option_menu = newwin(row , col , 0 , 0);
                        box(option_menu , 0 , 0);
                        keypad(option_menu , TRUE);
                        refresh();
                        wrefresh(option_menu);
                        wbkgd(option_menu , COLOR_PAIR(4));
                        char options[2][MAX_SIZE] = { "<new game>" ,
                                                        "<exit>"};
                        int highlight_option = 0;
                        int decision_option;
                        wattron(option_menu , COLOR_PAIR(6));
                        if(out == 2)
                            mvwprintw(option_menu , 0 , col/2 - 8/2 , "YOU LOST");
                        else if(out == 1)
                        {
                            mvwprintw(option_menu , 0 , col/2 - 7/2 , "YOU WON");
                        }
                        wattroff(option_menu , COLOR_PAIR(6));
                        while(1)
                        {
                            for(int i = 0 ; i < 2 ; i++)
                            {
                                int game_len = strlen(options[i]);
                                if(i == highlight_option)
                                {
                                    wattron(option_menu , A_REVERSE);
                                }
                                mvwprintw(option_menu , i + row/2 - 4 , col/2 - game_len/2 , options[i]);
                                wattroff(option_menu , A_REVERSE);
                            }
                            decision_option = wgetch(option_menu);
                            switch (decision_option)
                            {
                            case KEY_UP:
                                highlight_option--;
                                if(highlight_option == -1)
                                {
                                    highlight_option = 1;
                                }
                                break;
                            case KEY_DOWN:
                                highlight_option++;
                                if(highlight_option == 2)
                                {
                                    highlight_option = 0;
                                }
                            default:
                                break;
                            }
                            if(decision_option == 10)
                            {
                                break;
                            }
                        }
                        if(highlight_option == 1)
                        {
                            exit = 1;
                            break;
                        }
                        else
                        {
                            out = 0;
                        }
                    }
                    
                    rooms Room[4][9];
                    location pelle[6];
                    location beasts[5][4];
                    int RoomNum[4];
                    for(int i = 0 ; i < 4 ; i++)
                    {
                        dungeons[i].RoomNum = Random(3 , 9);
                    }
                    generate_map(row , col , dungeons[0].room , dungeons[0].RoomNum , dungeons[0].naghseh , 1 , pelle , beasts[0]);
                    generate_corridor(dungeons[0].room , dungeons[0].RoomNum , dungeons[0].naghseh);
                    generate_map(row , col , dungeons[1].room , dungeons[1].RoomNum , dungeons[1].naghseh , 2 , pelle , beasts[1]);
                    generate_corridor(dungeons[1].room , dungeons[1].RoomNum , dungeons[1].naghseh);
                    generate_map(row , col , dungeons[2].room , dungeons[2].RoomNum , dungeons[2].naghseh , 3 , pelle , beasts[2]);
                    generate_corridor(dungeons[2].room , dungeons[2].RoomNum , dungeons[2].naghseh);
                    generate_map(row , col , dungeons[3].room , dungeons[3].RoomNum , dungeons[3].naghseh , 4 , pelle , beasts[3]);
                    generate_corridor(dungeons[3].room , dungeons[3].RoomNum , dungeons[3].naghseh);
                    generate_treasure_room(row , col  , dungeons[4].naghseh );
                    remove(file_1);
                    remove(file_2);
                    remove(file_3);
                    remove(file_4);
                    remove(file_5);
                    remove(file_6);
                    remove(file_7);
                    remove(file_8);
                    remove(file_9);
                    remove(file_10);
                    remove(file_11);
                    profile guest;
                    strcpy(guest.name , "guest-usr");
                    FILE * temp = fopen(file_12 , "r");
                    if(temp != NULL)
                        fscanf(temp , "%d" , &user.gold_reserve);
                    else
                        user.gold_reserve = 0;
                    remove(file_12);
                    
                    guest.health = health_num;
                    guest.points = 0;
                    guest.gold_reserve = 0;
                    guest.weapon_num = 1;
                    strcpy(guest.inventory[0] , "NO WEAPON");
                    guest.experience = 1;
                    int number = Random(0 , RoomNum[0] - 1);
                    int y_loc;
                    int x_loc;
                    y_loc = spawn_py(dungeons[0].room[number]);
                    x_loc = spawn_px(dungeons[0].room[number]);
                    int floor = 0;
                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                    attron(COLOR_PAIR(4));
                    bkgd(COLOR_PAIR(4));
                    init_show(dungeons[floor].show , row , col);
                    int move = 0;
                    showroom(dungeons[floor].room , dungeons[floor].naghseh , dungeons[floor].show , number);
                    while(1)
                    {
                        
                        clear();
                        if(out == 1)
                        {
                            break;
                        }
                        if(out == 2)
                        {
                            break;
                        }
                        refresh();
                        move++;
                        if(move%4 == 0)
                            guest.health--;
                        showcorridor(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc , 5);
                        for(int k = 0 ; k < 4 ; k++)
                        {
                            if (isfollower(dungeons[floor].naghseh[beasts[floor][k].y][beasts[floor][k].x]))
                            {
                                int range = range_monster(dungeons[floor].naghseh[beasts[floor][k].y][beasts[floor][k].x]);
                                int hurt = 0;
                                int x_m = beasts[floor][k].x;
                                int y_m = beasts[floor][k].y;
                                char temp = dungeons[floor].naghseh[beasts[floor][k].y][beasts[floor][k].x];
                                dungeons[floor].naghseh[beasts[floor][k].y][beasts[floor][k].x] = '.';
                                int distance_x = abs(x_loc - x_m);
                                int distance_y = abs(y_loc - y_m);
                                if((distance_x != 1 || distance_y != 1) && (distance_x < range && distance_y < range))
                                {
                                    if(abs(x_loc - (x_m - 1)) <= distance_x &&
                                    (!iswall(dungeons[floor].naghseh[y_m][x_m - 1]) && !iswindow(dungeons[floor].naghseh[y_m][x_m - 1]) && !isdoor(dungeons[floor].naghseh[y_m][x_m - 1]) && !ispillar(dungeons[floor].naghseh[y_m][x_m - 1])) && 
                                    abs(x_loc - (x_m - 1)) > 0)
                                    {
                                        x_m--;
                                        beasts[floor][k].x = x_m;
                                    }
                                    else if(abs(x_loc - (x_m + 1)) <= distance_x && 
                                    (!iswall(dungeons[floor].naghseh[y_m][x_m + 1]) && !iswindow(dungeons[floor].naghseh[y_m][x_m + 1]) && !isdoor(dungeons[floor].naghseh[y_m][x_m + 1]) && !ispillar(dungeons[floor].naghseh[y_m][x_m + 1])) && 
                                    abs(x_loc - (x_m + 1)) > 0)
                                    {
                                        x_m++;
                                        beasts[floor][k].x = x_m;
                                    }
                                    else if(abs(y_loc - (y_m - 1)) <= distance_y && 
                                    (!iswall(dungeons[floor].naghseh[y_m - 1][x_m]) && !iswindow(dungeons[floor].naghseh[y_m - 1][x_m]) && !isdoor(dungeons[floor].naghseh[y_m - 1][x_m]) && !ispillar(dungeons[floor].naghseh[y_m - 1][x_m])) && 
                                    abs(y_loc - (y_m - 1)) > 0)
                                    {
                                        y_m--;
                                        beasts[floor][k].y = y_m;
                                    }
                                    else if(abs(y_loc - (y_m + 1)) > 0 && 
                                    (!iswall(dungeons[floor].naghseh[y_m + 1][x_m]) && !iswindow(dungeons[floor].naghseh[y_m + 1][x_m]) && !isdoor(dungeons[floor].naghseh[y_m + 1][x_m]) && !ispillar(dungeons[floor].naghseh[y_m + 1][x_m])))
                                    {
                                        y_m++;
                                        beasts[floor][k].y = y_m;
                                    }
                                    hurt = 0;
                                }
                                else if(distance_x == 1 && distance_y == 1)
                                {
                                    hurt = 1;
                                }
                                dungeons[floor].naghseh[beasts[floor][k].y][beasts[floor][k].x] = temp;
                                if(hurt)
                                {
                                    int asib = damage(temp);
                                    if(guest.health - asib >= 0)
                                    {
                                        guest.health-=asib;
                                        mvprintw(0,40 , "You got hit by a monster!");
                                    }
                                    else
                                    {
                                        out = 2;
                                        continue;
                                    }
                                }
                            }
                        }
                        print_map(row , col , dungeons[floor].naghseh , dungeons[floor].show);
                        mvprintw(y_loc , x_loc , "@");
                        mvprintw(0 , 0 , "your health is %d |" , guest.health , floor);
                        mvprintw(0 , 20 , "your point is %d |" , guest.points);
                        int kilid = getch();
                        switch (kilid)
                        {
                        case KEY_UP:
                            if(isfloor(dungeons[floor].naghseh[y_loc - 1][x_loc]) ||
                               iscorridor(dungeons[floor].naghseh[y_loc - 1][x_loc]) ||
                               isdoor(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               istrap(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               isfood(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               istair(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               isgold(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               ismace(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               isdagger(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               iswand(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               isarrow(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               issword(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               istreasure(dungeons[floor].naghseh[y_loc - 1][x_loc]))
                            {
                                if(iswall(dungeons[floor].naghseh[y_loc - 1][x_loc]) || ispillar(dungeons[floor].naghseh[y_loc - 1][x_loc]) || iswindow(dungeons[floor].naghseh[y_loc - 1][x_loc]))
                                {
                                    break;
                                }
                                else if(istrap(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.health - 10 >= 0)
                                    {
                                        showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc);
                                        guest.health -= 10;
                                    }
                                    else
                                        out = 2;
                                }
                                else if(dungeons[floor].naghseh[y_loc][x_loc] == 'f')
                                {
                                    if(guest.health + 10 <= health_num)
                                    {
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        guest.health+=10;
                                    }
                                }
                                else if(dungeons[floor].naghseh[y_loc][x_loc] == 'G')
                                {
                                    guest.points++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(ismace(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Mace (M)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(iswand(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Magic Wand (I)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(isdagger(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Dagger (p)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(isarrow(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Arrow (Y)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(issword(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Sword (P)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                y_loc--;
                            }
                            break;
                        case KEY_DOWN:
                            if(isfloor(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            iscorridor(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            isdoor(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            istrap(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            isfood(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            istair(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            isgold(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            ismace(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            isdagger(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            iswand(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            isarrow(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            issword(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            istreasure(dungeons[floor].naghseh[y_loc + 1][x_loc]))
                            {
                                if(dungeons[floor].naghseh[y_loc + 1][x_loc] == '-'|| dungeons[floor].naghseh[y_loc + 1][x_loc] == '0' || dungeons[floor].naghseh[y_loc + 1][x_loc] == '=')
                                {
                                    break;
                                }
                                else if(istrap(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.health - 10 >= 0)
                                    {
                                        showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc);
                                        guest.health -= 10;
                                    }
                                    else
                                        out = 2;
                                }
                                else if(dungeons[floor].naghseh[y_loc][x_loc] == 'f')
                                {
                                    if(guest.health + 10 <= health_num)
                                    {
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        guest.health+=10;
                                    }
                                }
                                else if(dungeons[floor].naghseh[y_loc][x_loc] == 'G')
                                {
                                    guest.points++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(ismace(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Mace (M)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(iswand(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Magic Wand (I)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(isdagger(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Dagger (p)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(isarrow(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Arrow (Y)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(issword(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Sword (P)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                y_loc++;
                            }
                            break;
                        case KEY_LEFT:
                            if(isfloor(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            iscorridor(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            isdoor(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            istrap(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            isfood(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            istair(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            isgold(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            ismace(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            isdagger(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            iswand(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            isarrow(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            issword(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            istreasure(dungeons[floor].naghseh[y_loc][x_loc - 1]))
                            {
                                if(dungeons[floor].naghseh[y_loc][x_loc - 1] == '|'|| dungeons[floor].naghseh[y_loc][x_loc - 1] == '0' || dungeons[floor].naghseh[y_loc][x_loc - 1] == '=')
                                {
                                    break;
                                }
                                else if(istrap(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.health - 10 >= 0)
                                    {
                                        showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc);
                                        guest.health -= 10;
                                    }
                                    else
                                        out = 2;
                                }
                                else if(dungeons[floor].naghseh[y_loc][x_loc] == 'f')
                                {
                                    if(guest.health + 10 <= health_num)
                                    {
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        guest.health+=10;
                                    }
                                }
                                else if(dungeons[floor].naghseh[y_loc][x_loc] == 'G')
                                {
                                    guest.points++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(ismace(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Mace (M)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(iswand(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Magic Wand (I)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(isdagger(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Dagger (p)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(isarrow(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Arrow (Y)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(issword(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Sword (P)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                x_loc--;
                            }
                            break;
                        case KEY_RIGHT:
                            if(isfloor(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            iscorridor(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            isdoor(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            istrap(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            isfood(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            istair(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            isgold(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            ismace(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            isdagger(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            iswand(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            isarrow(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            issword(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            istreasure(dungeons[floor].naghseh[y_loc][x_loc + 1]))
                            {
                                if(dungeons[floor].naghseh[y_loc][x_loc + 1] == '|'|| dungeons[floor].naghseh[y_loc][x_loc + 1] == '0' || dungeons[floor].naghseh[y_loc][x_loc + 1] == '=')
                                {
                                    break;
                                }
                                else if(istrap(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.health - 10 >= 0)
                                    {
                                        showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc);
                                        guest.health -= 10;
                                    }
                                    else
                                        out = 2;
                                }
                                else if(dungeons[floor].naghseh[y_loc][x_loc] == 'f')
                                {
                                    if(guest.health + 10 <= health_num)
                                    {
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        guest.health+=10;
                                    }
                                }
                                else if(dungeons[floor].naghseh[y_loc][x_loc] == 'G')
                                {
                                    guest.points++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(ismace(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Mace (M)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(iswand(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Magic Wand (I)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(isdagger(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Dagger (p)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(isarrow(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Arrow (Y)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(issword(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Sword (P)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                x_loc++;
                            }
                            break;
                        
                        case '>':
                            if(istair(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                switch (floor)
                                {
                                case 0:
                                    if(pelle[0].x == x_loc && pelle[0].y == y_loc)
                                    {
                                        floor++;
                                        y_loc = pelle[1].y;
                                        x_loc = pelle[1].x;
                                    }
                                    break;
                                case 1:
                                    if(pelle[1].x == x_loc && pelle[1].y == y_loc)
                                    {
                                        floor--;
                                        y_loc = pelle[0].y;
                                        x_loc = pelle[0].x;
                                    }
                                    else if(pelle[2].x == x_loc && pelle[2].y == y_loc)
                                    {
                                        floor++;
                                        y_loc = pelle[3].y;
                                        x_loc = pelle[3].x;
                                    }
                                    break;
                                case 2:
                                    if(pelle[3].x == x_loc && pelle[3].y == y_loc)
                                    {
                                        floor--;
                                        y_loc = pelle[2].y;
                                        x_loc = pelle[2].x;
                                    }
                                    else if(pelle[4].x == x_loc && pelle[4].y == y_loc)
                                    {
                                        floor++;
                                        y_loc = pelle[5].y;
                                        x_loc = pelle[5].x;
                                    }
                                    break;
                                case 3:
                                    if(pelle[5].x == x_loc && pelle[5].y == y_loc)
                                    {
                                        floor--;
                                        y_loc = pelle[4].y;
                                        x_loc = pelle[4].x;
                                    }
                                    break;
                                default:
                                    break;
                                }
                            }
                            else if(istreasure(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                x_loc = 10;
                                y_loc = 10;
                                floor++;
                                out = 1;
                                guest.points += 100;
                            }
                            break;
                        case 'i':
                            WINDOW* inventory = newwin(row , col , 0 , 0);
                            box(inventory , 0 , 0);
                            refresh();
                            keypad(inventory , TRUE);
                            wrefresh(inventory);
                            wbkgd(inventory , COLOR_PAIR(4));
                            int inventory_highlight = 0;
                            int inventory_decision;
                            while(1)
                            {
                                for(int i = 0 ; i < guest.weapon_num ; i++)
                                {
                                    int item_len = strlen(guest.inventory[i]);
                                    if(i == inventory_highlight)
                                    {
                                        wattron(inventory , A_REVERSE);
                                    }
                                    mvwprintw(inventory , i + 1 , col/2 - item_len/2 , guest.inventory[i]);
                                    wattroff(inventory , A_REVERSE);
                                }
                                inventory_decision = wgetch(inventory);
                                switch (inventory_decision)
                                {
                                case KEY_UP:
                                    inventory_highlight--;
                                    if(inventory_highlight == -1)
                                    {
                                        inventory_highlight = guest.weapon_num - 1;
                                    }
                                    break;
                                case KEY_DOWN:
                                    inventory_highlight++;
                                    if(inventory_highlight == guest.weapon_num)
                                    {
                                        inventory_highlight = 0;
                                    }
                                    break;
                                default:
                                    break;
                                }
                                if(inventory_decision == 10)
                                {
                                    break;
                                }
                                if(inventory_highlight == 0)
                                {
                                    if(strcmp(guest.inventory[inventory_highlight] , "Mace (M)") == 0)
                                    {
                                        guest.weapon = 5;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Dagger (p)") == 0)
                                    {
                                        guest.weapon = 12;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Magic Wand (I)") == 0)
                                    {
                                        guest.weapon = 15;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Arrow (Y)") == 0)
                                    {
                                        guest.weapon = 5;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Sword (P)") == 0)
                                    {
                                        guest.weapon = 10;
                                    }
                                }
                                else if(inventory_highlight == 1)
                                {
                                    if(strcmp(guest.inventory[inventory_highlight] , "Mace (M)") == 0)
                                    {
                                        guest.weapon = 5;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Dagger (p)") == 0)
                                    {
                                        guest.weapon = 12;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Magic Wand (I)") == 0)
                                    {
                                        guest.weapon = 15;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Arrow (Y)") == 0)
                                    {
                                        guest.weapon = 5;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Sword (P)") == 0)
                                    {
                                        guest.weapon = 10;
                                    }
                                }
                                else if(inventory_highlight == 2)
                                {
                                    if(strcmp(guest.inventory[inventory_highlight] , "Mace (M)") == 0)
                                    {
                                        guest.weapon = 5;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Dagger (p)") == 0)
                                    {
                                        guest.weapon = 12;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Magic Wand (I)") == 0)
                                    {
                                        guest.weapon = 15;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Arrow (Y)") == 0)
                                    {
                                        guest.weapon = 5;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Sword (P)") == 0)
                                    {
                                        guest.weapon = 10;
                                    }
                                }
                                else if(inventory_highlight == 3)
                                {
                                    if(strcmp(guest.inventory[inventory_highlight] , "Mace (M)") == 0)
                                    {
                                        guest.weapon = 5;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Dagger (p)") == 0)
                                    {
                                        guest.weapon = 12;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Magic Wand (I)") == 0)
                                    {
                                        guest.weapon = 15;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Arrow (Y)") == 0)
                                    {
                                        guest.weapon = 5;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Sword (P)") == 0)
                                    {
                                        guest.weapon = 10;
                                    }
                                }
                                else if(inventory_highlight == 4)
                                {
                                    if(strcmp(guest.inventory[inventory_highlight] , "Mace (M)") == 0)
                                    {
                                        guest.weapon = 5;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Dagger (p)") == 0)
                                    {
                                        guest.weapon = 12;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Magic Wand (I)") == 0)
                                    {
                                        guest.weapon = 15;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Arrow (Y)") == 0)
                                    {
                                        guest.weapon = 5;
                                    }
                                    else if(strcmp(guest.inventory[inventory_highlight] , "Sword (P)") == 0)
                                    {
                                        guest.weapon = 10;
                                    }
                                }
                            }
                            break;
                        case 's':
                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc + 1 , y_loc + 1);
                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc - 1 , y_loc - 1);
                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc - 1 , y_loc);
                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc + 1 , y_loc);
                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc - 1);
                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc + 1);
                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc - 1 , y_loc + 1);
                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc + 1 , y_loc - 1);
                            break;
                        case 'w':
                            if(ismace(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(strcmp(guest.inventory[1] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[1] , "Mace (M)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[2] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[2] , "Mace (M)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[3] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[3] , "Mace (M)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[4] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[4] , "Mace (M)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[5] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[5] , "Mace (M)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else
                                {
                                    char weap;
                                    if(strcmp(guest.inventory[5] , "Mace (M)") == 0)
                                    {
                                        weap = 'M';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Dagger (p)") == 0)
                                    {
                                        weap = 'p';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Magic Wand (I)") == 0)
                                    {
                                        weap = 'I';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Arrow (Y)") == 0)
                                    {
                                        weap = 'Y';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Sword (P)") == 0)
                                    {
                                        weap = 'P';
                                    }
                                    dungeons[floor].naghseh[y_loc][x_loc] = weap;
                                    strcpy(guest.inventory[5] , "Mace (M)");
                                }
                            }
                            else if(iswand(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(strcmp(guest.inventory[1] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[1] , "Magic Wand (I)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[2] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[2] , "Magic Wand (I)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[3] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[3] , "Magic Wand (I)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[4] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[4] , "Magic Wand (I)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[5] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[5] , "Magic Wand (I)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else
                                {
                                    char weap;
                                    if(strcmp(guest.inventory[5] , "Mace (M)") == 0)
                                    {
                                        weap = 'M';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Dagger (p)") == 0)
                                    {
                                        weap = 'p';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Magic Wand (I)") == 0)
                                    {
                                        weap = 'I';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Arrow (Y)") == 0)
                                    {
                                        weap = 'Y';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Sword (P)") == 0)
                                    {
                                        weap = 'P';
                                    }
                                    dungeons[floor].naghseh[y_loc][x_loc] = weap;
                                    strcpy(guest.inventory[5] , "Magic Wand (I)");
                                }
                            }
                            else if(isdagger(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(strcmp(guest.inventory[1] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[1] , "Dagger (p)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[2] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[2] , "Dagger (p)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[3] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[3] , "Dagger (p)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[4] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[4] , "Dagger (p)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[5] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[5] , "Dagger (p)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else
                                {
                                    char weap;
                                    if(strcmp(guest.inventory[5] , "Mace (M)") == 0)
                                    {
                                        weap = 'M';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Dagger (p)") == 0)
                                    {
                                        weap = 'p';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Magic Wand (I)") == 0)
                                    {
                                        weap = 'I';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Arrow (Y)") == 0)
                                    {
                                        weap = 'Y';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Sword (P)") == 0)
                                    {
                                        weap = 'P';
                                    }
                                    dungeons[floor].naghseh[y_loc][x_loc] = weap;
                                    strcpy(guest.inventory[5] , "Dagger (p)");
                                }
                            }
                            else if(isarrow(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(strcmp(guest.inventory[1] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[1] , "Arrow (Y)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[2] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[2] , "Arrow (Y)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[3] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[3] , "Arrow (Y)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[4] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[4] , "Arrow (Y)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[5] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[5] , "Arrow (Y)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else
                                {
                                    char weap;
                                    if(strcmp(guest.inventory[5] , "Mace (M)") == 0)
                                    {
                                        weap = 'M';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Dagger (p)") == 0)
                                    {
                                        weap = 'p';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Magic Wand (I)") == 0)
                                    {
                                        weap = 'I';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Arrow (Y)") == 0)
                                    {
                                        weap = 'Y';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Sword (P)") == 0)
                                    {
                                        weap = 'P';
                                    }
                                    dungeons[floor].naghseh[y_loc][x_loc] = weap;
                                    strcpy(guest.inventory[5] , "Arrow (Y)");
                                }
                            }
                            else if(issword(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(strcmp(guest.inventory[1] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[1] , "Sword (P)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[2] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[2] , "Sword (P)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[3] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[3] , "Sword (P)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[4] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[4] , "Sword (P)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(strcmp(guest.inventory[5] , "NO WEAPON"))
                                {
                                    strcpy(guest.inventory[5] , "Sword (P)");
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else
                                {
                                    char weap;
                                    if(strcmp(guest.inventory[5] , "Mace (M)") == 0)
                                    {
                                        weap = 'M';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Dagger (p)") == 0)
                                    {
                                        weap = 'p';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Magic Wand (I)") == 0)
                                    {
                                        weap = 'I';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Arrow (Y)") == 0)
                                    {
                                        weap = 'Y';
                                    }
                                    else if(strcmp(guest.inventory[5] , "Sword (P)") == 0)
                                    {
                                        weap = 'P';
                                    }
                                    dungeons[floor].naghseh[y_loc][x_loc] = weap;
                                    strcpy(guest.inventory[5] , "Sword (P)");
                                }
                            }
                            break;
                        case 'S':
                            WINDOW* setting = newwin(row , col , 0 , 0);
                            box(setting , 0 , 0);
                            refresh();
                            keypad(setting , TRUE);
                            wrefresh(setting);
                            wbkgd(setting , COLOR_PAIR(4));
                            char setting_option[2][MAX_SIZE] = {"SAVE" , "EXIT"};
                            int setting_highlight = 0;
                            int setting_decision;
                            while (1)
                            {
                                for(int i = 0 ; i < 2 ; i++)
                                {
                                    int setting_len = strlen(setting_option[i]);
                                    if(i == setting_highlight)
                                    {
                                        wattron(setting , A_REVERSE);
                                    }
                                    mvwprintw(setting , i + row/2 - 4 , col/2 - setting_len/2 , setting_option[i]);
                                    wattroff(setting , A_REVERSE);
                                }
                                setting_decision = wgetch(setting);
                                switch (setting_decision)
                                {
                                case KEY_UP:
                                    setting_highlight--;
                                    if(setting_highlight == -1)
                                    {
                                        setting_highlight = 1;
                                    }
                                    break;
                                case KEY_DOWN:
                                    setting_highlight++;
                                    if(setting_highlight == 2)
                                    {
                                        setting_highlight = 0;
                                    }
                                    break;
                                default:
                                    break;
                                }
                                if(setting_decision == 10)
                                {
                                    break;
                                }
                            }
                            if(setting_highlight == 0)
                                {
                                    FILE * map_1 = fopen(file_1 , "w");
                                    FILE * map_2 = fopen(file_2 , "w");
                                    FILE * map_3 = fopen(file_3 , "w");
                                    FILE * map_4 = fopen(file_4 , "w");
                                    FILE * treasure_map = fopen(file_5 , "w");
                                    FILE * show_1 = fopen(file_6 , "w");
                                    FILE * show_2 = fopen(file_7 , "w");
                                    FILE * show_3 = fopen(file_8 , "w");
                                    FILE * show_4 = fopen(file_9 , "w");
                                    FILE * show_treasure = fopen(file_10 , "w");
                                    FILE * guestfile = fopen(file_11 , "w");
                                    user.gold_reserve += guest.points;
                                    FILE * points_write = fopen(file_12 , "w");
                                    fprintf(points_write , "%d" , user.gold_reserve);
                                    fclose(points_write);
                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        fprintf(map_1 ,"%s\n"  , dungeons[0].naghseh[i]);
                                    }
                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        fprintf(map_2 ,"%s\n"  , dungeons[1].naghseh[i]);
                                    }
                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        fprintf(map_3 ,"%s\n"  , dungeons[2].naghseh[i]);
                                    }
                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        fprintf(map_4 ,"%s\n"  , dungeons[3].naghseh[i]);
                                    }
                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        fprintf(treasure_map ,"%s\n"  , dungeons[4].naghseh[i]);
                                    }

                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        for(int j = 0 ; j < col ; j++)
                                        {
                                            fprintf(show_1 , "%d " , dungeons[0].show[i][j]);
                                        }
                                        fprintf(show_1 , "\n");
                                    }

                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        for(int j = 0 ; j < col ; j++)
                                        {
                                            fprintf(show_2 , "%d " , dungeons[0].show[i][j]);
                                        }
                                        fprintf(show_2 , "\n");
                                    }

                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        for(int j = 0 ; j < col ; j++)
                                        {
                                            fprintf(show_3 , "%d " , dungeons[0].show[i][j]);
                                        }
                                        fprintf(show_3 , "\n");
                                    }

                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        for(int j = 0 ; j < col ; j++)
                                        {
                                            fprintf(show_4 , "%d " , dungeons[0].show[i][j]);
                                        }
                                        fprintf(show_4 , "\n");
                                    }

                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        for(int j = 0 ; j < col ; j++)
                                        {
                                            fprintf(show_treasure , "%d " , dungeons[0].show[i][j]);
                                        }
                                        fprintf(show_treasure , "\n");
                                    }
                                    fprintf(guestfile , "%d\n" , guest.health);
                                    fprintf(guestfile , "%d\n" , guest.points);
                                    fprintf(guestfile , "%d\n" , guest.experience);
                                    fprintf(guestfile , "%d\n" , y_loc);
                                    fprintf(guestfile , "%d\n" , x_loc);
                                    fprintf(guestfile , "%d\n" , floor);
                                    fprintf(guestfile , "%d\n" , pelle[0].x);
                                    fprintf(guestfile , "%d\n" , pelle[0].y);
                                    fprintf(guestfile , "%d\n" , pelle[1].x);
                                    fprintf(guestfile , "%d\n" , pelle[1].y);
                                    fprintf(guestfile , "%d\n" , pelle[2].x);
                                    fprintf(guestfile , "%d\n" , pelle[2].y);
                                    fprintf(guestfile , "%d\n" , pelle[3].x);
                                    fprintf(guestfile , "%d\n" , pelle[3].y);
                                    fprintf(guestfile , "%d\n" , pelle[4].x);
                                    fprintf(guestfile , "%d\n" , pelle[4].y);
                                    fprintf(guestfile , "%d\n" , pelle[5].x);
                                    fprintf(guestfile , "%d\n" , pelle[5].y);
                                    fprintf(guestfile , "%d\n" , guest.weapon);
                                    for(int i = 0 ; i < 5 ; i++)
                                    {
                                        for(int j = 0 ; j < 4 ; j++)
                                            fprintf(guestfile , "%d %d" , beasts[i][j].x , beasts[i][j].y);
                                        fprintf(guestfile , "\n");
                                    }
                                    for(int i = 0 ; i < 10 ; i++)
                                    {
                                        fprintf(guestfile , "%s\n" , guest.inventory[i]);
                                    }
                                    clear();
                                    out = 1;
                                }
                            else
                            {
                                out = 2;
                            }
                            
                            break;
                        default:
                            break;
                        }
                        
                    }
                }

            }
            else
            {
                clear();
                FILE * map_1 = fopen(file_1 , "r");
                FILE * map_2 = fopen(file_2 , "r");
                FILE * map_3 = fopen(file_3 , "r");
                FILE * map_4 = fopen(file_4 , "r");
                FILE * treasure_map = fopen(file_5 , "r");
                FILE * show_1 = fopen(file_6 , "r");
                FILE * show_2 = fopen(file_7 , "r");
                FILE * show_3 = fopen(file_8 , "r");
                FILE * show_4 = fopen(file_9 , "r");
                FILE * show_treasure = fopen(file_10 , "r");
                FILE * guestfile = fopen(file_11 , "r"); 
                FILE * usr_point = fopen(file_12 , "r");
                if(usr_point != NULL)
                {
                    fscanf(usr_point , "%d" , &user.gold_reserve);
                }
                else
                {
                    user.gold_reserve = 0;
                }
                if(guestfile != NULL)
                {
                    int index_1 = 0;
                    while (fgets(dungeons[0].naghseh[index_1] , MAX_SIZE, map_1) != NULL && index_1 < row)
                    {
                        dungeons[0].naghseh[index_1][strcspn(dungeons[0].naghseh[index_1] , "\n")] = '\0';
                        index_1++;
                    }
                    int index_2 = 0;
                    while (fgets(dungeons[1].naghseh[index_2] , MAX_SIZE , map_2) != NULL && index_2 < row)
                    {
                        dungeons[1].naghseh[index_2][strcspn(dungeons[1].naghseh[index_2] , "\n")] = '\0';
                        index_2++;
                    }
                    int index_3 = 0;
                    while (fgets(dungeons[2].naghseh[index_3] , MAX_SIZE , map_3) != NULL && index_3 < row)
                    {
                        dungeons[2].naghseh[index_3][strcspn(dungeons[0].naghseh[index_3] , "\n")] = '\0';
                        index_3++;
                    }
                    int index_4 = 0;
                    while (fgets(dungeons[3].naghseh[index_4] , MAX_SIZE , map_4) != NULL && index_4 < row)
                    {
                        dungeons[3].naghseh[index_4][strcspn(dungeons[3].naghseh[index_4] , "\n")] = '\0';
                        index_4++;
                    }

                    int index_5 = 0;
                    while (fgets(dungeons[4].naghseh[index_5] , MAX_SIZE , treasure_map) != NULL && index_5 < row)
                    {
                        dungeons[4].naghseh[index_5][strcspn(dungeons[4].naghseh[index_5] , "\n")] = '\0';
                        index_5++;
                    }

                    for(int i = 0 ; i < row ; i++)
                    {
                        for(int j = 0 ; j < col ; j++)
                        {
                            fscanf(show_1 , "%d" , &dungeons[0].show[i][j]);
                        }
                    }
                    for(int i = 0 ; i < row ; i++)
                    {
                        for(int j = 0 ; j < col ; j++)
                        {
                            fscanf(show_2 , "%d" , &dungeons[1].show[i][j]);
                        }
                    }
                    for(int i = 0 ; i < row ; i++)
                    {
                        for(int j = 0 ; j < col ; j++)
                        {
                            fscanf(show_3 , "%d" , &dungeons[2].show[i][j]);
                        }
                    }
                    for(int i = 0 ; i < row ; i++)
                    {
                        for(int j = 0 ; j < col ; j++)
                        {
                            fscanf(show_4 , "%d" , &dungeons[3].show[i][j]);
                        }
                    }
                    for(int i = 0 ; i < row ; i++)
                    {
                        for(int j = 0 ; j < col ; j++)
                        {
                            fscanf(show_treasure , "%d" , &dungeons[4].show[i][j]);
                        }
                    }
                    profile guest;
                    location pelle[6];
                    location beasts[5][4];
                    int x_loc , y_loc , floor;
                    strcpy(guest.name , "guest-usr");
                    fscanf(guestfile , "%d" ,&guest.health);
                    fscanf(guestfile , "%d" , &guest.points);
                    fscanf(guestfile , "%d" , &guest.experience);
                    fscanf(guestfile , "%d" , &y_loc);
                    fscanf(guestfile , "%d" , &x_loc);
                    fscanf(guestfile , "%d" , &floor);
                    fscanf(guestfile , "%d" , &pelle[0].x);
                    fscanf(guestfile , "%d" , &pelle[0].y);
                    fscanf(guestfile , "%d" , &pelle[1].x);
                    fscanf(guestfile , "%d" , &pelle[1].y);
                    fscanf(guestfile , "%d" , &pelle[2].x);
                    fscanf(guestfile , "%d" , &pelle[2].y);
                    fscanf(guestfile , "%d" , &pelle[3].x);
                    fscanf(guestfile , "%d" , &pelle[3].y);
                    fscanf(guestfile , "%d" , &pelle[4].x);
                    fscanf(guestfile , "%d" , &pelle[4].y);
                    fscanf(guestfile , "%d" , &pelle[5].x);
                    fscanf(guestfile , "%d" , &pelle[5].y);
                    fscanf(guestfile , "%d" , &guest.weapon);
                    for(int i = 0 ; i < 5 ; i++)
                    {
                        for(int j = 0 ; j < 4 ; j++)
                        {
                            fscanf(guestfile , "%d" , &beasts[i][j].x);
                            fscanf(guestfile , "%d" , &beasts[i][j].x);
                        }
                    }
                    int index = 0;
                    while (index < 10)
                    {
                        int a = fscanf(guestfile , " %s" , guest.inventory[index]);
                        if(a == -1)
                        {
                            break;
                        }
                        index++;
                    }
                    guest.weapon_num = index - 1;
                    int out = 0;
                    int finish = 0;
                    keypad(stdscr , TRUE);
                    while (1)
                    {
                        if(out == 2 || out == 1)
                        {
                            clear();
                            WINDOW * option_menu = newwin(row , col , 0 , 0);
                            box(option_menu , 0 , 0);
                            keypad(option_menu , TRUE);
                            refresh();
                            wrefresh(option_menu);
                            wbkgd(option_menu , COLOR_PAIR(4));
                            char options[2][MAX_SIZE] = { "<new game>" ,
                                                            "<exit>"};
                            int highlight_option = 0;
                            int decision_option;
                            wattron(option_menu , COLOR_PAIR(6));
                            if(out == 2)
                                mvwprintw(option_menu , 0 , col/2 - 8/2 , "YOU LOST");
                            else if(out == 1)
                            {
                                mvwprintw(option_menu , 0 , col/2 - 7/2 , "YOU WON");
                            }
                            wattroff(option_menu , COLOR_PAIR(6));
                            while(1)
                            {
                                for(int i = 0 ; i < 2 ; i++)
                                {
                                    int game_len = strlen(options[i]);
                                    if(i == highlight_option)
                                    {
                                        wattron(option_menu , A_REVERSE);
                                    }
                                    mvwprintw(option_menu , i + row/2 - 4 , col/2 - game_len/2 , options[i]);
                                    wattroff(option_menu , A_REVERSE);
                                }
                                decision_option = wgetch(option_menu);
                                switch (decision_option)
                                {
                                case KEY_UP:
                                    highlight_option--;
                                    if(highlight_option == -1)
                                    {
                                        highlight_option = 1;
                                    }
                                    break;
                                case KEY_DOWN:
                                    highlight_option++;
                                    if(highlight_option == 2)
                                    {
                                        highlight_option = 0;
                                    }
                                default:
                                    break;
                                }
                                if(decision_option == 10)
                                {
                                    break;
                                }
                            }
                            if(highlight_option == 1)
                            {
                                exit = 1;
                                break;
                            }
                            else
                            {
                                out = 0;
                            }
                        }
                        int move = 0;
                        while(1)
                        {
                            
                            clear();
                            if(out == 1)
                            {
                                break;
                            }
                            if(out == 2)
                            {
                                break;
                            }
                            refresh();
                            move++;
                            if(move%4==0)
                                guest.health--;
                            showcorridor(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc , 5);
                            for(int k = 0 ; k < 4 ; k++)
                            {
                                if (isfollower(dungeons[floor].naghseh[beasts[floor][k].y][beasts[floor][k].x]))
                                {
                                    int range = range_monster(dungeons[floor].naghseh[beasts[floor][k].y][beasts[floor][k].x]);
                                    int hurt = 0;
                                    int x_m = beasts[floor][k].x;
                                    int y_m = beasts[floor][k].y;
                                    char temp = dungeons[floor].naghseh[beasts[floor][k].y][beasts[floor][k].x];
                                    dungeons[floor].naghseh[beasts[floor][k].y][beasts[floor][k].x] = '.';
                                    int distance_x = abs(x_loc - x_m);
                                    int distance_y = abs(y_loc - y_m);
                                    if((distance_x != 1 || distance_y != 1) && (distance_x < range && distance_y < range))
                                    {
                                        if(abs(x_loc - (x_m - 1)) <= distance_x &&
                                        (!iswall(dungeons[floor].naghseh[y_m][x_m - 1]) && !iswindow(dungeons[floor].naghseh[y_m][x_m - 1]) && !isdoor(dungeons[floor].naghseh[y_m][x_m - 1]) && !ispillar(dungeons[floor].naghseh[y_m][x_m - 1])) && 
                                        abs(x_loc - (x_m - 1)) > 0)
                                        {
                                            x_m--;
                                            beasts[floor][k].x = x_m;
                                        }
                                        else if(abs(x_loc - (x_m + 1)) <= distance_x && 
                                        (!iswall(dungeons[floor].naghseh[y_m][x_m + 1]) && !iswindow(dungeons[floor].naghseh[y_m][x_m + 1]) && !isdoor(dungeons[floor].naghseh[y_m][x_m + 1]) && !ispillar(dungeons[floor].naghseh[y_m][x_m + 1])) && 
                                        abs(x_loc - (x_m + 1)) > 0)
                                        {
                                            x_m++;
                                            beasts[floor][k].x = x_m;
                                        }
                                        else if(abs(y_loc - (y_m - 1)) <= distance_y && 
                                        (!iswall(dungeons[floor].naghseh[y_m - 1][x_m]) && !iswindow(dungeons[floor].naghseh[y_m - 1][x_m]) && !isdoor(dungeons[floor].naghseh[y_m - 1][x_m]) && !ispillar(dungeons[floor].naghseh[y_m - 1][x_m])) && 
                                        abs(y_loc - (y_m - 1)) > 0)
                                        {
                                            y_m--;
                                            beasts[floor][k].y = y_m;
                                        }
                                        else if(abs(y_loc - (y_m + 1)) > 0 && 
                                        (!iswall(dungeons[floor].naghseh[y_m + 1][x_m]) && !iswindow(dungeons[floor].naghseh[y_m + 1][x_m]) && !isdoor(dungeons[floor].naghseh[y_m + 1][x_m]) && !ispillar(dungeons[floor].naghseh[y_m + 1][x_m])))
                                        {
                                            y_m++;
                                            beasts[floor][k].y = y_m;
                                        }
                                        hurt = 0;
                                    }
                                    else if(distance_x == 1 && distance_y == 1)
                                    {
                                        hurt = 1;
                                    }
                                    dungeons[floor].naghseh[beasts[floor][k].y][beasts[floor][k].x] = temp;
                                    if(hurt)
                                    {
                                        int asib = damage(temp);
                                        if(guest.health - asib >= 0)
                                        {
                                            guest.health-=asib;
                                            mvprintw(0,40 , "You got hit by a monster!");
                                        }
                                        else
                                        {
                                            out = 2;
                                            continue;
                                        }
                                    }
                                }
                            }
                            move(0,0);
                            attron(COLOR_PAIR(4));
                            // mvprintw(10,0,dungeons[floor].naghseh[10]);
                            // getch();
                            print_map(row , col , dungeons[floor].naghseh , dungeons[floor].show);
                            mvprintw(y_loc , x_loc , "@");
                            mvprintw(0 , 0 , "your health is %d %d|" , y_loc , x_loc);
                            mvprintw(0 , 20 , "your point is %d |" , guest.points);
                            int kilid = getch();
                            switch (kilid)
                            {
                            case KEY_UP:
                                if(isfloor(dungeons[floor].naghseh[y_loc - 1][x_loc]) ||
                               iscorridor(dungeons[floor].naghseh[y_loc - 1][x_loc]) ||
                               isdoor(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               istrap(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               isfood(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               istair(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               isgold(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               ismace(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               isdagger(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               iswand(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               isarrow(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               issword(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                               istreasure(dungeons[floor].naghseh[y_loc - 1][x_loc]))
                                {
                                    if(iswall(dungeons[floor].naghseh[y_loc - 1][x_loc]) || ispillar(dungeons[floor].naghseh[y_loc - 1][x_loc]) || iswindow(dungeons[floor].naghseh[y_loc - 1][x_loc]))
                                    {
                                        break;
                                    }
                                    else if(istrap(dungeons[floor].naghseh[y_loc][x_loc]))
                                    {
                                        if(guest.health - 10 >= 0)
                                        {
                                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc);
                                            guest.health -= 10;
                                        }
                                        else
                                            out = 2;
                                    }
                                    else if(dungeons[floor].naghseh[y_loc][x_loc] == 'f')
                                    {
                                        if(guest.health + 10 <= health_num)
                                        {
                                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                            guest.health+=10;
                                        }
                                    }
                                    else if(dungeons[floor].naghseh[y_loc][x_loc] == 'G')
                                    {
                                        guest.points++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else if(ismace(dungeons[floor].naghseh[y_loc][x_loc]))
                                    {
                                        if(guest.weapon_num < 5)
                                        {
                                            strcpy(guest.inventory[guest.weapon_num] , "Mace (M)");
                                            guest.weapon_num++;
                                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        }
                                    }
                                    else if(iswand(dungeons[floor].naghseh[y_loc][x_loc]))
                                    {
                                        if(guest.weapon_num < 5)
                                        {
                                            strcpy(guest.inventory[guest.weapon_num] , "Magic Wand (I)");
                                            guest.weapon_num++;
                                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        }
                                    }
                                    else if(isdagger(dungeons[floor].naghseh[y_loc][x_loc]))
                                    {
                                        if(guest.weapon_num < 5)
                                        {
                                            strcpy(guest.inventory[guest.weapon_num] , "Dagger (p)");
                                            guest.weapon_num++;
                                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        }
                                    }
                                    else if(isarrow(dungeons[floor].naghseh[y_loc][x_loc]))
                                    {
                                        if(guest.weapon_num < 5)
                                        {
                                            strcpy(guest.inventory[guest.weapon_num] , "Arrow (Y)");
                                            guest.weapon_num++;
                                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        }
                                    }
                                    else if(issword(dungeons[floor].naghseh[y_loc][x_loc]))
                                    {
                                        if(guest.weapon_num < 5)
                                        {
                                            strcpy(guest.inventory[guest.weapon_num] , "Sword (P)");
                                            guest.weapon_num++;
                                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        }
                                    }
                                    y_loc--;
                                }
                                break;
                            case KEY_DOWN:
                                if(isfloor(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                                iscorridor(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                                isdoor(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                                istrap(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                                isfood(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                                istair(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                                isgold(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                                ismace(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                                isdagger(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                                iswand(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                                isarrow(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                                issword(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                                istreasure(dungeons[floor].naghseh[y_loc + 1][x_loc]))
                                {
                                    if(dungeons[floor].naghseh[y_loc + 1][x_loc] == '-'|| dungeons[floor].naghseh[y_loc + 1][x_loc] == '0' || dungeons[floor].naghseh[y_loc + 1][x_loc] == '=')
                                    {
                                        break;
                                    }
                                    else if(istrap(dungeons[floor].naghseh[y_loc][x_loc]))
                                    {
                                        if(guest.health - 10 >= 0)
                                        {
                                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc);
                                            guest.health -= 10;
                                        }
                                        else
                                            out = 2;
                                    }
                                    else if(dungeons[floor].naghseh[y_loc][x_loc] == 'f')
                                    {
                                        if(guest.health + 10 <= health_num)
                                        {
                                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                            guest.health+=10;
                                        }
                                    }
                                    else if(dungeons[floor].naghseh[y_loc][x_loc] == 'G')
                                    {
                                        guest.points++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else if(ismace(dungeons[floor].naghseh[y_loc][x_loc]))
                                    {
                                        if(guest.weapon_num < 5)
                                        {
                                            strcpy(guest.inventory[guest.weapon_num] , "Mace (M)");
                                            guest.weapon_num++;
                                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        }
                                    }
                                    else if(iswand(dungeons[floor].naghseh[y_loc][x_loc]))
                                    {
                                        if(guest.weapon_num < 5)
                                        {
                                            strcpy(guest.inventory[guest.weapon_num] , "Magic Wand (I)");
                                            guest.weapon_num++;
                                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        }
                                    }
                                    else if(isdagger(dungeons[floor].naghseh[y_loc][x_loc]))
                                    {
                                        if(guest.weapon_num < 5)
                                        {
                                            strcpy(guest.inventory[guest.weapon_num] , "Dagger (p)");
                                            guest.weapon_num++;
                                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        }
                                    }
                                    else if(isarrow(dungeons[floor].naghseh[y_loc][x_loc]))
                                    {
                                        if(guest.weapon_num < 5)
                                        {
                                            strcpy(guest.inventory[guest.weapon_num] , "Arrow (Y)");
                                            guest.weapon_num++;
                                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        }
                                    }
                                    else if(issword(dungeons[floor].naghseh[y_loc][x_loc]))
                                    {
                                        if(guest.weapon_num < 5)
                                        {
                                            strcpy(guest.inventory[guest.weapon_num] , "Sword (P)");
                                            guest.weapon_num++;
                                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        }
                                    }
                                    y_loc++;
                                }
                                break;
                            case KEY_LEFT:
                                if(isfloor(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                                iscorridor(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                                isdoor(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                                istrap(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                                isfood(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                                istair(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                                isgold(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                                ismace(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                                isdagger(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                                iswand(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                                isarrow(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                                issword(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                                istreasure(dungeons[floor].naghseh[y_loc][x_loc - 1]))
                                {
                                    if(dungeons[floor].naghseh[y_loc][x_loc - 1] == '|'|| dungeons[floor].naghseh[y_loc][x_loc - 1] == '0' || dungeons[floor].naghseh[y_loc][x_loc - 1] == '=')
                                    {
                                        break;
                                    }
                                    else if(istrap(dungeons[floor].naghseh[y_loc][x_loc]))
                                    {
                                        if(guest.health - 10 >= 0)
                                        {
                                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc);
                                            guest.health -= 10;
                                        }
                                        else
                                            out = 2;
                                    }
                                    else if(dungeons[floor].naghseh[y_loc][x_loc] == 'f')
                                    {
                                        if(guest.health + 10 <= health_num)
                                        {
                                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                            guest.health+=10;
                                        }
                                    }
                                    else if(dungeons[floor].naghseh[y_loc][x_loc] == 'G')
                                    {
                                        guest.points++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else if(ismace(dungeons[floor].naghseh[y_loc][x_loc]))
                                    {
                                        if(guest.weapon_num < 5)
                                        {
                                            strcpy(guest.inventory[guest.weapon_num] , "Mace (M)");
                                            guest.weapon_num++;
                                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        }
                                    }
                                    else if(iswand(dungeons[floor].naghseh[y_loc][x_loc]))
                                    {
                                        if(guest.weapon_num < 5)
                                        {
                                            strcpy(guest.inventory[guest.weapon_num] , "Magic Wand (I)");
                                            guest.weapon_num++;
                                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        }
                                    }
                                    else if(isdagger(dungeons[floor].naghseh[y_loc][x_loc]))
                                    {
                                        if(guest.weapon_num < 5)
                                        {
                                            strcpy(guest.inventory[guest.weapon_num] , "Dagger (p)");
                                            guest.weapon_num++;
                                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        }
                                    }
                                    else if(isarrow(dungeons[floor].naghseh[y_loc][x_loc]))
                                    {
                                        if(guest.weapon_num < 5)
                                        {
                                            strcpy(guest.inventory[guest.weapon_num] , "Arrow (Y)");
                                            guest.weapon_num++;
                                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        }
                                    }
                                    else if(issword(dungeons[floor].naghseh[y_loc][x_loc]))
                                    {
                                        if(guest.weapon_num < 5)
                                        {
                                            strcpy(guest.inventory[guest.weapon_num] , "Sword (P)");
                                            guest.weapon_num++;
                                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        }
                                    }
                                    x_loc--;
                                }
                                break;
                            case KEY_RIGHT:
                                if(isfloor(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                                iscorridor(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                                isdoor(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                                istrap(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                                isfood(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                                istair(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                                isgold(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                                ismace(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                                isdagger(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                                iswand(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                                isarrow(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                                issword(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                                istreasure(dungeons[floor].naghseh[y_loc][x_loc + 1]))
                                {
                                    if(dungeons[floor].naghseh[y_loc][x_loc + 1] == '|'|| dungeons[floor].naghseh[y_loc][x_loc + 1] == '0' || dungeons[floor].naghseh[y_loc][x_loc + 1] == '=')
                                    {
                                        break;
                                    }
                                    else if(istrap(dungeons[floor].naghseh[y_loc][x_loc]))
                                    {
                                        if(guest.health - 10 >= 0)
                                        {
                                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc);
                                            guest.health -= 10;
                                        }
                                        else
                                            out = 2;
                                    }
                                    else if(dungeons[floor].naghseh[y_loc][x_loc] == 'f')
                                    {
                                        if(guest.health + 10 <= health_num)
                                        {
                                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                            guest.health+=10;
                                        }
                                    }
                                    else if(dungeons[floor].naghseh[y_loc][x_loc] == 'G')
                                    {
                                        guest.points++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else if(ismace(dungeons[floor].naghseh[y_loc][x_loc]))
                                    {
                                        if(guest.weapon_num < 5)
                                        {
                                            strcpy(guest.inventory[guest.weapon_num] , "Mace (M)");
                                            guest.weapon_num++;
                                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        }
                                    }
                                    else if(iswand(dungeons[floor].naghseh[y_loc][x_loc]))
                                    {
                                        if(guest.weapon_num < 5)
                                        {
                                            strcpy(guest.inventory[guest.weapon_num] , "Magic Wand (I)");
                                            guest.weapon_num++;
                                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        }
                                    }
                                    else if(isdagger(dungeons[floor].naghseh[y_loc][x_loc]))
                                    {
                                        if(guest.weapon_num < 5)
                                        {
                                            strcpy(guest.inventory[guest.weapon_num] , "Dagger (p)");
                                            guest.weapon_num++;
                                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        }
                                    }
                                    else if(isarrow(dungeons[floor].naghseh[y_loc][x_loc]))
                                    {
                                        if(guest.weapon_num < 5)
                                        {
                                            strcpy(guest.inventory[guest.weapon_num] , "Arrow (Y)");
                                            guest.weapon_num++;
                                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        }
                                    }
                                    else if(issword(dungeons[floor].naghseh[y_loc][x_loc]))
                                    {
                                        if(guest.weapon_num < 5)
                                        {
                                            strcpy(guest.inventory[guest.weapon_num] , "Sword (P)");
                                            guest.weapon_num++;
                                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        }
                                    }
                                    x_loc++;
                                }
                                break;
                            
                            case '>':
                                if(istair(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    switch (floor)
                                    {
                                    case 0:
                                        if(pelle[0].x == x_loc && pelle[0].y == y_loc)
                                        {
                                            floor++;
                                            y_loc = pelle[1].y;
                                            x_loc = pelle[1].x;
                                        }
                                        break;
                                    case 1:
                                        if(pelle[1].x == x_loc && pelle[1].y == y_loc)
                                        {
                                            floor--;
                                            y_loc = pelle[0].y;
                                            x_loc = pelle[0].x;
                                        }
                                        else if(pelle[2].x == x_loc && pelle[2].y == y_loc)
                                        {
                                            floor++;
                                            y_loc = pelle[3].y;
                                            x_loc = pelle[3].x;
                                        }
                                        break;
                                    case 2:
                                        if(pelle[3].x == x_loc && pelle[3].y == y_loc)
                                        {
                                            floor--;
                                            y_loc = pelle[2].y;
                                            x_loc = pelle[2].x;
                                        }
                                        else if(pelle[4].x == x_loc && pelle[4].y == y_loc)
                                        {
                                            floor++;
                                            y_loc = pelle[5].y;
                                            x_loc = pelle[5].x;
                                        }
                                        break;
                                    case 3:
                                        if(pelle[5].x == x_loc && pelle[5].y == y_loc)
                                        {
                                            floor--;
                                            y_loc = pelle[4].y;
                                            x_loc = pelle[4].x;
                                        }
                                        break;
                                    default:
                                        break;
                                    }
                                }
                                else if(istreasure(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    x_loc = 10;
                                    y_loc = 10;
                                    floor++;
                                    out = 1;
                                    guest.points += 100;
                                }
                                break;
                            case 'i':
                                WINDOW* inventory = newwin(row , col , 0 , 0);
                                box(inventory , 0 , 0);
                                refresh();
                                keypad(inventory , TRUE);
                                wrefresh(inventory);
                                wbkgd(inventory , COLOR_PAIR(4));
                                int inventory_highlight = 0;
                                int inventory_decision;
                                while(1)
                                {
                                    for(int i = 0 ; i < guest.weapon_num ; i++)
                                    {
                                        int item_len = strlen(guest.inventory[i]);
                                        if(i == inventory_highlight)
                                        {
                                            wattron(inventory , A_REVERSE);
                                        }
                                        mvwprintw(inventory , i + 1 , col/2 - item_len/2 , guest.inventory[i]);
                                        wattroff(inventory , A_REVERSE);
                                    }
                                    inventory_decision = wgetch(inventory);
                                    switch (inventory_decision)
                                    {
                                    case KEY_UP:
                                        inventory_highlight--;
                                        if(inventory_highlight == -1)
                                        {
                                            inventory_highlight = guest.weapon_num - 1;
                                        }
                                        break;
                                    case KEY_DOWN:
                                        inventory_highlight++;
                                        if(inventory_highlight == guest.weapon_num)
                                        {
                                            inventory_highlight = 0;
                                        }
                                        break;
                                    default:
                                        break;
                                    }
                                    if(inventory_decision == 10)
                                    {
                                        break;
                                    }
                                    if(inventory_highlight == 0)
                                    {
                                        if(strcmp(guest.inventory[inventory_highlight] , "Mace (M)") == 0)
                                        {
                                            guest.weapon = 5;
                                        }
                                        else if(strcmp(guest.inventory[inventory_highlight] , "Dagger (p)") == 0)
                                        {
                                            guest.weapon = 12;
                                        }
                                        else if(strcmp(guest.inventory[inventory_highlight] , "Magic Wand (I)") == 0)
                                        {
                                            guest.weapon = 15;
                                        }
                                        else if(strcmp(guest.inventory[inventory_highlight] , "Arrow (Y)") == 0)
                                        {
                                            guest.weapon = 5;
                                        }
                                        else if(strcmp(guest.inventory[inventory_highlight] , "Sword (P)") == 0)
                                        {
                                            guest.weapon = 10;
                                        }
                                    }
                                    else if(inventory_highlight == 1)
                                    {
                                        if(strcmp(guest.inventory[inventory_highlight] , "Mace (M)") == 0)
                                        {
                                            guest.weapon = 5;
                                        }
                                        else if(strcmp(guest.inventory[inventory_highlight] , "Dagger (p)") == 0)
                                        {
                                            guest.weapon = 12;
                                        }
                                        else if(strcmp(guest.inventory[inventory_highlight] , "Magic Wand (I)") == 0)
                                        {
                                            guest.weapon = 15;
                                        }
                                        else if(strcmp(guest.inventory[inventory_highlight] , "Arrow (Y)") == 0)
                                        {
                                            guest.weapon = 5;
                                        }
                                        else if(strcmp(guest.inventory[inventory_highlight] , "Sword (P)") == 0)
                                        {
                                            guest.weapon = 10;
                                        }
                                    }
                                    else if(inventory_highlight == 2)
                                    {
                                        if(strcmp(guest.inventory[inventory_highlight] , "Mace (M)") == 0)
                                        {
                                            guest.weapon = 5;
                                        }
                                        else if(strcmp(guest.inventory[inventory_highlight] , "Dagger (p)") == 0)
                                        {
                                            guest.weapon = 12;
                                        }
                                        else if(strcmp(guest.inventory[inventory_highlight] , "Magic Wand (I)") == 0)
                                        {
                                            guest.weapon = 15;
                                        }
                                        else if(strcmp(guest.inventory[inventory_highlight] , "Arrow (Y)") == 0)
                                        {
                                            guest.weapon = 5;
                                        }
                                        else if(strcmp(guest.inventory[inventory_highlight] , "Sword (P)") == 0)
                                        {
                                            guest.weapon = 10;
                                        }
                                    }
                                    else if(inventory_highlight == 3)
                                    {
                                        if(strcmp(guest.inventory[inventory_highlight] , "Mace (M)") == 0)
                                        {
                                            guest.weapon = 5;
                                        }
                                        else if(strcmp(guest.inventory[inventory_highlight] , "Dagger (p)") == 0)
                                        {
                                            guest.weapon = 12;
                                        }
                                        else if(strcmp(guest.inventory[inventory_highlight] , "Magic Wand (I)") == 0)
                                        {
                                            guest.weapon = 15;
                                        }
                                        else if(strcmp(guest.inventory[inventory_highlight] , "Arrow (Y)") == 0)
                                        {
                                            guest.weapon = 5;
                                        }
                                        else if(strcmp(guest.inventory[inventory_highlight] , "Sword (P)") == 0)
                                        {
                                            guest.weapon = 10;
                                        }
                                    }
                                    else if(inventory_highlight == 4)
                                    {
                                        if(strcmp(guest.inventory[inventory_highlight] , "Mace (M)") == 0)
                                        {
                                            guest.weapon = 5;
                                        }
                                        else if(strcmp(guest.inventory[inventory_highlight] , "Dagger (p)") == 0)
                                        {
                                            guest.weapon = 12;
                                        }
                                        else if(strcmp(guest.inventory[inventory_highlight] , "Magic Wand (I)") == 0)
                                        {
                                            guest.weapon = 15;
                                        }
                                        else if(strcmp(guest.inventory[inventory_highlight] , "Arrow (Y)") == 0)
                                        {
                                            guest.weapon = 5;
                                        }
                                        else if(strcmp(guest.inventory[inventory_highlight] , "Sword (P)") == 0)
                                        {
                                            guest.weapon = 10;
                                        }
                                    }
                                }
                                break;
                            case 's':
                                showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc + 1 , y_loc + 1);
                                showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc - 1 , y_loc - 1);
                                showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc - 1 , y_loc);
                                showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc + 1 , y_loc);
                                showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc - 1);
                                showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc + 1);
                                showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc - 1 , y_loc + 1);
                                showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc + 1 , y_loc - 1);
                                break;
                            case 'w':
                                if(ismace(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(strcmp(guest.inventory[1] , "NO WEAPON"))
                                    {
                                        strcpy(guest.inventory[1] , "Mace (M)");
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else if(strcmp(guest.inventory[2] , "NO WEAPON"))
                                    {
                                        strcpy(guest.inventory[2] , "Mace (M)");
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else if(strcmp(guest.inventory[3] , "NO WEAPON"))
                                    {
                                        strcpy(guest.inventory[3] , "Mace (M)");
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else if(strcmp(guest.inventory[4] , "NO WEAPON"))
                                    {
                                        strcpy(guest.inventory[4] , "Mace (M)");
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else if(strcmp(guest.inventory[5] , "NO WEAPON"))
                                    {
                                        strcpy(guest.inventory[5] , "Mace (M)");
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else
                                    {
                                        char weap;
                                        if(strcmp(guest.inventory[5] , "Mace (M)") == 0)
                                        {
                                            weap = 'M';
                                        }
                                        else if(strcmp(guest.inventory[5] , "Dagger (p)") == 0)
                                        {
                                            weap = 'p';
                                        }
                                        else if(strcmp(guest.inventory[5] , "Magic Wand (I)") == 0)
                                        {
                                            weap = 'I';
                                        }
                                        else if(strcmp(guest.inventory[5] , "Arrow (Y)") == 0)
                                        {
                                            weap = 'Y';
                                        }
                                        else if(strcmp(guest.inventory[5] , "Sword (P)") == 0)
                                        {
                                            weap = 'P';
                                        }
                                        dungeons[floor].naghseh[y_loc][x_loc] = weap;
                                        strcpy(guest.inventory[5] , "Mace (M)");
                                    }
                                }
                                else if(iswand(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(strcmp(guest.inventory[1] , "NO WEAPON"))
                                    {
                                        strcpy(guest.inventory[1] , "Magic Wand (I)");
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else if(strcmp(guest.inventory[2] , "NO WEAPON"))
                                    {
                                        strcpy(guest.inventory[2] , "Magic Wand (I)");
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else if(strcmp(guest.inventory[3] , "NO WEAPON"))
                                    {
                                        strcpy(guest.inventory[3] , "Magic Wand (I)");
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else if(strcmp(guest.inventory[4] , "NO WEAPON"))
                                    {
                                        strcpy(guest.inventory[4] , "Magic Wand (I)");
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else if(strcmp(guest.inventory[5] , "NO WEAPON"))
                                    {
                                        strcpy(guest.inventory[5] , "Magic Wand (I)");
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else
                                    {
                                        char weap;
                                        if(strcmp(guest.inventory[5] , "Mace (M)") == 0)
                                        {
                                            weap = 'M';
                                        }
                                        else if(strcmp(guest.inventory[5] , "Dagger (p)") == 0)
                                        {
                                            weap = 'p';
                                        }
                                        else if(strcmp(guest.inventory[5] , "Magic Wand (I)") == 0)
                                        {
                                            weap = 'I';
                                        }
                                        else if(strcmp(guest.inventory[5] , "Arrow (Y)") == 0)
                                        {
                                            weap = 'Y';
                                        }
                                        else if(strcmp(guest.inventory[5] , "Sword (P)") == 0)
                                        {
                                            weap = 'P';
                                        }
                                        dungeons[floor].naghseh[y_loc][x_loc] = weap;
                                        strcpy(guest.inventory[5] , "Magic Wand (I)");
                                    }
                                }
                                else if(isdagger(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(strcmp(guest.inventory[1] , "NO WEAPON"))
                                    {
                                        strcpy(guest.inventory[1] , "Dagger (p)");
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else if(strcmp(guest.inventory[2] , "NO WEAPON"))
                                    {
                                        strcpy(guest.inventory[2] , "Dagger (p)");
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else if(strcmp(guest.inventory[3] , "NO WEAPON"))
                                    {
                                        strcpy(guest.inventory[3] , "Dagger (p)");
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else if(strcmp(guest.inventory[4] , "NO WEAPON"))
                                    {
                                        strcpy(guest.inventory[4] , "Dagger (p)");
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else if(strcmp(guest.inventory[5] , "NO WEAPON"))
                                    {
                                        strcpy(guest.inventory[5] , "Dagger (p)");
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else
                                    {
                                        char weap;
                                        if(strcmp(guest.inventory[5] , "Mace (M)") == 0)
                                        {
                                            weap = 'M';
                                        }
                                        else if(strcmp(guest.inventory[5] , "Dagger (p)") == 0)
                                        {
                                            weap = 'p';
                                        }
                                        else if(strcmp(guest.inventory[5] , "Magic Wand (I)") == 0)
                                        {
                                            weap = 'I';
                                        }
                                        else if(strcmp(guest.inventory[5] , "Arrow (Y)") == 0)
                                        {
                                            weap = 'Y';
                                        }
                                        else if(strcmp(guest.inventory[5] , "Sword (P)") == 0)
                                        {
                                            weap = 'P';
                                        }
                                        dungeons[floor].naghseh[y_loc][x_loc] = weap;
                                        strcpy(guest.inventory[5] , "Dagger (p)");
                                    }
                                }
                                else if(isarrow(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(strcmp(guest.inventory[1] , "NO WEAPON"))
                                    {
                                        strcpy(guest.inventory[1] , "Arrow (Y)");
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else if(strcmp(guest.inventory[2] , "NO WEAPON"))
                                    {
                                        strcpy(guest.inventory[2] , "Arrow (Y)");
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else if(strcmp(guest.inventory[3] , "NO WEAPON"))
                                    {
                                        strcpy(guest.inventory[3] , "Arrow (Y)");
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else if(strcmp(guest.inventory[4] , "NO WEAPON"))
                                    {
                                        strcpy(guest.inventory[4] , "Arrow (Y)");
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else if(strcmp(guest.inventory[5] , "NO WEAPON"))
                                    {
                                        strcpy(guest.inventory[5] , "Arrow (Y)");
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else
                                    {
                                        char weap;
                                        if(strcmp(guest.inventory[5] , "Mace (M)") == 0)
                                        {
                                            weap = 'M';
                                        }
                                        else if(strcmp(guest.inventory[5] , "Dagger (p)") == 0)
                                        {
                                            weap = 'p';
                                        }
                                        else if(strcmp(guest.inventory[5] , "Magic Wand (I)") == 0)
                                        {
                                            weap = 'I';
                                        }
                                        else if(strcmp(guest.inventory[5] , "Arrow (Y)") == 0)
                                        {
                                            weap = 'Y';
                                        }
                                        else if(strcmp(guest.inventory[5] , "Sword (P)") == 0)
                                        {
                                            weap = 'P';
                                        }
                                        dungeons[floor].naghseh[y_loc][x_loc] = weap;
                                        strcpy(guest.inventory[5] , "Arrow (Y)");
                                    }
                                }
                                else if(issword(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(strcmp(guest.inventory[1] , "NO WEAPON"))
                                    {
                                        strcpy(guest.inventory[1] , "Sword (P)");
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else if(strcmp(guest.inventory[2] , "NO WEAPON"))
                                    {
                                        strcpy(guest.inventory[2] , "Sword (P)");
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else if(strcmp(guest.inventory[3] , "NO WEAPON"))
                                    {
                                        strcpy(guest.inventory[3] , "Sword (P)");
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else if(strcmp(guest.inventory[4] , "NO WEAPON"))
                                    {
                                        strcpy(guest.inventory[4] , "Sword (P)");
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else if(strcmp(guest.inventory[5] , "NO WEAPON"))
                                    {
                                        strcpy(guest.inventory[5] , "Sword (P)");
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                    else
                                    {
                                        char weap;
                                        if(strcmp(guest.inventory[5] , "Mace (M)") == 0)
                                        {
                                            weap = 'M';
                                        }
                                        else if(strcmp(guest.inventory[5] , "Dagger (p)") == 0)
                                        {
                                            weap = 'p';
                                        }
                                        else if(strcmp(guest.inventory[5] , "Magic Wand (I)") == 0)
                                        {
                                            weap = 'I';
                                        }
                                        else if(strcmp(guest.inventory[5] , "Arrow (Y)") == 0)
                                        {
                                            weap = 'Y';
                                        }
                                        else if(strcmp(guest.inventory[5] , "Sword (P)") == 0)
                                        {
                                            weap = 'P';
                                        }
                                        dungeons[floor].naghseh[y_loc][x_loc] = weap;
                                        strcpy(guest.inventory[5] , "Sword (P)");
                                    }
                                }
                                break;
                            case 'S':
                                WINDOW* setting = newwin(row , col , 0 , 0);
                                box(setting , 0 , 0);
                                refresh();
                                keypad(setting , TRUE);
                                wrefresh(setting);
                                wbkgd(setting , COLOR_PAIR(4));
                                char setting_option[2][MAX_SIZE] = {"SAVE" , "EXIT"};
                                int setting_highlight = 0;
                                int setting_decision;
                                while (1)
                                {
                                    for(int i = 0 ; i < 2 ; i++)
                                    {
                                        int setting_len = strlen(setting_option[i]);
                                        if(i == setting_highlight)
                                        {
                                            wattron(setting , A_REVERSE);
                                        }
                                        mvwprintw(setting , i + row/2 - 4 , col/2 - setting_len/2 , setting_option[i]);
                                        wattroff(setting , A_REVERSE);
                                    }
                                    setting_decision = wgetch(setting);
                                    switch (setting_decision)
                                    {
                                    case KEY_UP:
                                        setting_highlight--;
                                        if(setting_highlight == -1)
                                        {
                                            setting_highlight = 1;
                                        }
                                        break;
                                    case KEY_DOWN:
                                        setting_highlight++;
                                        if(setting_highlight == 2)
                                        {
                                            setting_highlight = 0;
                                        }
                                        break;
                                    default:
                                        break;
                                    }
                                    if(setting_decision == 10)
                                    {
                                        break;
                                    }
                                }
                                if(setting_highlight == 0)
                                {
                                    FILE * map_1 = fopen(file_1 , "w");
                                    FILE * map_2 = fopen(file_2 , "w");
                                    FILE * map_3 = fopen(file_3 , "w");
                                    FILE * map_4 = fopen(file_4 , "w");
                                    FILE * treasure_map = fopen(file_5 , "w");
                                    FILE * show_1 = fopen(file_6 , "w");
                                    FILE * show_2 = fopen(file_7 , "w");
                                    FILE * show_3 = fopen(file_8 , "w");
                                    FILE * show_4 = fopen(file_9 , "w");
                                    FILE * show_treasure = fopen(file_10 , "w");
                                    FILE * guestfile = fopen(file_11 , "w");
                                    FILE * points = fopen(file_12 , "w");
                                    fprintf(points , "%d" , user.gold_reserve + guest.points);
                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        fprintf(map_1 ,"%s\n"  , dungeons[0].naghseh[i]);
                                    }
                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        fprintf(map_2 ,"%s\n"  , dungeons[1].naghseh[i]);
                                    }
                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        fprintf(map_3 ,"%s\n"  , dungeons[2].naghseh[i]);
                                    }
                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        fprintf(map_4 ,"%s\n"  , dungeons[3].naghseh[i]);
                                    }
                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        fprintf(treasure_map ,"%s\n"  , dungeons[4].naghseh[i]);
                                    }

                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        for(int j = 0 ; j < col ; j++)
                                        {
                                            fprintf(show_1 , "%d " , dungeons[0].show[i][j]);
                                        }
                                        fprintf(show_1 , "\n");
                                    }

                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        for(int j = 0 ; j < col ; j++)
                                        {
                                            fprintf(show_2 , "%d " , dungeons[0].show[i][j]);
                                        }
                                        fprintf(show_2 , "\n");
                                    }

                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        for(int j = 0 ; j < col ; j++)
                                        {
                                            fprintf(show_3 , "%d " , dungeons[0].show[i][j]);
                                        }
                                        fprintf(show_3 , "\n");
                                    }

                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        for(int j = 0 ; j < col ; j++)
                                        {
                                            fprintf(show_4 , "%d " , dungeons[0].show[i][j]);
                                        }
                                        fprintf(show_4 , "\n");
                                    }

                                    for(int i = 0 ; i < row ; i++)
                                    {
                                        for(int j = 0 ; j < col ; j++)
                                        {
                                            fprintf(show_treasure , "%d " , dungeons[0].show[i][j]);
                                        }
                                        fprintf(show_treasure , "\n");
                                    }
                                    fprintf(guestfile , "%d\n" , guest.health);
                                    fprintf(guestfile , "%d\n" , guest.points);
                                    fprintf(guestfile , "%d\n" , guest.experience);
                                    fprintf(guestfile , "%d\n" , y_loc);
                                    fprintf(guestfile , "%d\n" , x_loc);
                                    fprintf(guestfile , "%d\n" , floor);
                                    fprintf(guestfile , "%d\n" , pelle[0].x);
                                    fprintf(guestfile , "%d\n" , pelle[0].y);
                                    fprintf(guestfile , "%d\n" , pelle[1].x);
                                    fprintf(guestfile , "%d\n" , pelle[1].y);
                                    fprintf(guestfile , "%d\n" , pelle[2].x);
                                    fprintf(guestfile , "%d\n" , pelle[2].y);
                                    fprintf(guestfile , "%d\n" , pelle[3].x);
                                    fprintf(guestfile , "%d\n" , pelle[3].y);
                                    fprintf(guestfile , "%d\n" , pelle[4].x);
                                    fprintf(guestfile , "%d\n" , pelle[4].y);
                                    fprintf(guestfile , "%d\n" , pelle[5].x);
                                    fprintf(guestfile , "%d\n" , pelle[5].y);
                                    fprintf(guestfile , "%d\n" , guest.weapon);
                                    for(int i = 0 ; i < 5 ; i++)
                                    {
                                        for(int j = 0 ; j < 4 ; j++)
                                            fprintf(guestfile , "%d %d" , beasts[i][j].x , beasts[i][j].y);
                                        fprintf(guestfile , "\n");
                                    }
                                    for(int i = 0 ; i < 10 ; i++)
                                    {
                                        fprintf(guestfile , "%s\n" , guest.inventory[i]);
                                    }
                                    clear();
                                    out = 1;
                                }
                                else
                                {
                                    out = 2;
                                }
                                
                                break;
                            default:
                                break;
                            }
                            
                        }
                    }

                    

                    
                }
            }



        }
        else if(highlight == 2)
        {
            noecho();
            keypad(stdscr , TRUE);
            clear();
            bkgd(' ');
            int out = 0;
            int finish = 0;
            while (1)
            {
                if(out == 2 || out == 1)
                {
                    clear();
                    WINDOW * option_menu = newwin(row , col , 0 , 0);
                    box(option_menu , 0 , 0);
                    keypad(option_menu , TRUE);
                    refresh();
                    wrefresh(option_menu);
                    wbkgd(option_menu , COLOR_PAIR(4));
                    char options[2][MAX_SIZE] = { "<new game>" ,
                                                    "<exit>"};
                    int highlight_option = 0;
                    int decision_option;
                    wattron(option_menu , COLOR_PAIR(6));
                    if(out == 2)
                        mvwprintw(option_menu , 0 , col/2 - 8/2 , "YOU LOST");
                    else if(out == 1)
                    {
                        mvwprintw(option_menu , 0 , col/2 - 7/2 , "YOU WON");
                    }
                    wattroff(option_menu , COLOR_PAIR(6));
                    while(1)
                    {
                        for(int i = 0 ; i < 2 ; i++)
                        {
                            int game_len = strlen(options[i]);
                            if(i == highlight_option)
                            {
                                wattron(option_menu , A_REVERSE);
                            }
                            mvwprintw(option_menu , i + row/2 - 4 , col/2 - game_len/2 , options[i]);
                            wattroff(option_menu , A_REVERSE);
                        }
                        decision_option = wgetch(option_menu);
                        switch (decision_option)
                        {
                        case KEY_UP:
                            highlight_option--;
                            if(highlight_option == -1)
                            {
                                highlight_option = 1;
                            }
                            break;
                        case KEY_DOWN:
                            highlight_option++;
                            if(highlight_option == 2)
                            {
                                highlight_option = 0;
                            }
                        default:
                            break;
                        }
                        if(decision_option == 10)
                        {
                            break;
                        }
                    }
                    if(highlight_option == 1)
                    {
                        exit = 1;
                        break;
                    }
                    else
                    {
                        out = 0;
                    }
                }
                
                rooms Room[4][9];
                location pelle[6];
                location beasts[5][4];
                int RoomNum[4];
                for(int i = 0 ; i < 4 ; i++)
                {
                    dungeons[i].RoomNum = Random(3 , 9);
                }
                generate_map(row , col , dungeons[0].room , dungeons[0].RoomNum , dungeons[0].naghseh , 1 , pelle , beasts[0]);
                generate_corridor(dungeons[0].room , dungeons[0].RoomNum , dungeons[0].naghseh);
                generate_map(row , col , dungeons[1].room , dungeons[1].RoomNum , dungeons[1].naghseh , 2 , pelle , beasts[1]);
                generate_corridor(dungeons[1].room , dungeons[1].RoomNum , dungeons[1].naghseh);
                generate_map(row , col , dungeons[2].room , dungeons[2].RoomNum , dungeons[2].naghseh , 3 , pelle , beasts[2]);
                generate_corridor(dungeons[2].room , dungeons[2].RoomNum , dungeons[2].naghseh);
                generate_map(row , col , dungeons[3].room , dungeons[3].RoomNum , dungeons[3].naghseh , 4 , pelle , beasts[3]);
                generate_corridor(dungeons[3].room , dungeons[3].RoomNum , dungeons[3].naghseh);
                generate_treasure_room(row , col  , dungeons[4].naghseh );
                remove("map-1-defualt.txt");
                remove("map-2-defualt.txt");
                remove("map-3-defualt.txt");
                remove("map-4-defualt.txt");
                remove("treasure-defualt.txt");
                remove("show-1-defualt.txt");
                remove("show-2-defualt.txt");
                remove("show-3-defualt.txt");
                remove("show-4-defualt.txt");
                remove("show-defualt.txt");
                remove("defualt.txt");
                profile guest;
                strcpy(guest.name , "guest-usr");
                
                guest.health = health_num;
                guest.points = 0;
                guest.gold_reserve = 0;
                guest.weapon = 5;
                guest.weapon_num = 1;
                strcpy(guest.inventory[0] , "NO WEAPON");
                guest.experience = 1;
                int number = Random(0 , RoomNum[0] - 1);
                int y_loc;
                int x_loc;
                y_loc = spawn_py(dungeons[0].room[number]);
                x_loc = spawn_px(dungeons[0].room[number]);
                int floor = 0;
                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                attron(COLOR_PAIR(4));
                bkgd(COLOR_PAIR(4));
                int move = 0;
                init_show(dungeons[floor].show , row , col);
                showroom(dungeons[floor].room , dungeons[floor].naghseh , dungeons[floor].show , number);
                while(1)
                {
                    
                    clear();
                    if(out == 1)
                    {
                        break;
                    }
                    if(out == 2)
                    {
                        break;
                    }
                    refresh();
                    move++;
                    if(move%4 == 0)
                        guest.health--;
                    showcorridor(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc , 5);
                    for(int k = 0 ; k < 4 ; k++)
                    {
                        if (isfollower(dungeons[floor].naghseh[beasts[floor][k].y][beasts[floor][k].x]))
                        {
                            int range = range_monster(dungeons[floor].naghseh[beasts[floor][k].y][beasts[floor][k].x]);
                            int hurt = 0;
                            int x_m = beasts[floor][k].x;
                            int y_m = beasts[floor][k].y;
                            char temp = dungeons[floor].naghseh[beasts[floor][k].y][beasts[floor][k].x];
                            dungeons[floor].naghseh[beasts[floor][k].y][beasts[floor][k].x] = '.';
                            int distance_x = abs(x_loc - x_m);
                            int distance_y = abs(y_loc - y_m);
                            if((distance_x != 1 || distance_y != 1) && (distance_x < range && distance_y < range))
                            {
                                if(abs(x_loc - (x_m - 1)) <= distance_x &&
                                (!iswall(dungeons[floor].naghseh[y_m][x_m - 1]) && !iswindow(dungeons[floor].naghseh[y_m][x_m - 1]) && !isdoor(dungeons[floor].naghseh[y_m][x_m - 1]) && !ispillar(dungeons[floor].naghseh[y_m][x_m - 1])) && 
                                abs(x_loc - (x_m - 1)) > 0)
                                {
                                    x_m--;
                                    beasts[floor][k].x = x_m;
                                }
                                else if(abs(x_loc - (x_m + 1)) <= distance_x && 
                                (!iswall(dungeons[floor].naghseh[y_m][x_m + 1]) && !iswindow(dungeons[floor].naghseh[y_m][x_m + 1]) && !isdoor(dungeons[floor].naghseh[y_m][x_m + 1]) && !ispillar(dungeons[floor].naghseh[y_m][x_m + 1])) && 
                                abs(x_loc - (x_m + 1)) > 0)
                                {
                                    x_m++;
                                    beasts[floor][k].x = x_m;
                                }
                                else if(abs(y_loc - (y_m - 1)) <= distance_y && 
                                (!iswall(dungeons[floor].naghseh[y_m - 1][x_m]) && !iswindow(dungeons[floor].naghseh[y_m - 1][x_m]) && !isdoor(dungeons[floor].naghseh[y_m - 1][x_m]) && !ispillar(dungeons[floor].naghseh[y_m - 1][x_m])) && 
                                abs(y_loc - (y_m - 1)) > 0)
                                {
                                    y_m--;
                                    beasts[floor][k].y = y_m;
                                }
                                else if(abs(y_loc - (y_m + 1)) > 0 && 
                                (!iswall(dungeons[floor].naghseh[y_m + 1][x_m]) && !iswindow(dungeons[floor].naghseh[y_m + 1][x_m]) && !isdoor(dungeons[floor].naghseh[y_m + 1][x_m]) && !ispillar(dungeons[floor].naghseh[y_m + 1][x_m])))
                                {
                                    y_m++;
                                    beasts[floor][k].y = y_m;
                                }
                                hurt = 0;
                            }
                            else if(distance_x == 1 && distance_y == 1)
                            {
                                hurt = 1;
                            }
                            dungeons[floor].naghseh[beasts[floor][k].y][beasts[floor][k].x] = temp;
                            if(hurt)
                            {
                                int asib = damage(temp);
                                if(guest.health - asib >= 0)
                                {
                                    guest.health-=asib;
                                    mvprintw(0,40 , "You got hit by a monster!");
                                }
                                else
                                {
                                    out = 2;
                                    continue;
                                }
                            }
                        }
                    }
                    print_map(row , col , dungeons[floor].naghseh , dungeons[floor].show);
                    mvprintw(y_loc , x_loc , "@");
                    mvprintw(0 , 0 , "your health is %d %d|" , guest.health , floor);
                    mvprintw(0 , 20 , "your point is %d |" , guest.points);
                    int kilid = getch();
                    switch (kilid)
                    {
                    case KEY_UP:
                        if(isfloor(dungeons[floor].naghseh[y_loc - 1][x_loc]) ||
                        iscorridor(dungeons[floor].naghseh[y_loc - 1][x_loc]) ||
                        isdoor(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                        istrap(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                        isfood(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                        istair(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                        isgold(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                        ismace(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                        isdagger(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                        iswand(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                        isarrow(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                        issword(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                        istreasure(dungeons[floor].naghseh[y_loc - 1][x_loc]))
                        {
                            if(iswall(dungeons[floor].naghseh[y_loc - 1][x_loc]) || ispillar(dungeons[floor].naghseh[y_loc - 1][x_loc]) || iswindow(dungeons[floor].naghseh[y_loc - 1][x_loc]))
                            {
                                break;
                            }
                            else if(istrap(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(guest.health - 10 >= 0)
                                {
                                    showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc);
                                    guest.health -= 10;
                                }
                                else
                                    out = 2;
                            }
                            else if(dungeons[floor].naghseh[y_loc][x_loc] == 'f')
                            {
                                if(guest.health + 10 <= health_num)
                                {
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    guest.health+=10;
                                }
                            }
                            else if(dungeons[floor].naghseh[y_loc][x_loc] == 'G')
                            {
                                guest.points++;
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else if(ismace(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(guest.weapon_num < 5)
                                {
                                    strcpy(guest.inventory[guest.weapon_num] , "Mace (M)");
                                    guest.weapon_num++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                            }
                            else if(iswand(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(guest.weapon_num < 5)
                                {
                                    strcpy(guest.inventory[guest.weapon_num] , "Magic Wand (I)");
                                    guest.weapon_num++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                            }
                            else if(isdagger(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(guest.weapon_num < 5)
                                {
                                    strcpy(guest.inventory[guest.weapon_num] , "Dagger (p)");
                                    guest.weapon_num++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                            }
                            else if(isarrow(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(guest.weapon_num < 5)
                                {
                                    strcpy(guest.inventory[guest.weapon_num] , "Arrow (Y)");
                                    guest.weapon_num++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                            }
                            else if(issword(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(guest.weapon_num < 5)
                                {
                                    strcpy(guest.inventory[guest.weapon_num] , "Sword (P)");
                                    guest.weapon_num++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                            }
                            y_loc--;
                        }
                        break;
                    case KEY_DOWN:
                        if(isfloor(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                        iscorridor(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                        isdoor(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                        istrap(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                        isfood(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                        istair(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                        isgold(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                        ismace(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                        isdagger(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                        iswand(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                        isarrow(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                        issword(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                        istreasure(dungeons[floor].naghseh[y_loc + 1][x_loc]))
                        {
                            if(dungeons[floor].naghseh[y_loc + 1][x_loc] == '-'|| dungeons[floor].naghseh[y_loc + 1][x_loc] == '0' || dungeons[floor].naghseh[y_loc + 1][x_loc] == '=')
                            {
                                break;
                            }
                            else if(istrap(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(guest.health - 10 >= 0)
                                {
                                    showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc);
                                    guest.health -= 10;
                                }
                                else
                                    out = 2;
                            }
                            else if(dungeons[floor].naghseh[y_loc][x_loc] == 'f')
                            {
                                if(guest.health + 10 <= health_num)
                                {
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    guest.health+=10;
                                }
                            }
                            else if(dungeons[floor].naghseh[y_loc][x_loc] == 'G')
                            {
                                guest.points++;
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else if(ismace(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(guest.weapon_num < 5)
                                {
                                    strcpy(guest.inventory[guest.weapon_num] , "Mace (M)");
                                    guest.weapon_num++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                            }
                            else if(iswand(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(guest.weapon_num < 5)
                                {
                                    strcpy(guest.inventory[guest.weapon_num] , "Magic Wand (I)");
                                    guest.weapon_num++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                            }
                            else if(isdagger(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(guest.weapon_num < 5)
                                {
                                    strcpy(guest.inventory[guest.weapon_num] , "Dagger (p)");
                                    guest.weapon_num++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                            }
                            else if(isarrow(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(guest.weapon_num < 5)
                                {
                                    strcpy(guest.inventory[guest.weapon_num] , "Arrow (Y)");
                                    guest.weapon_num++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                            }
                            else if(issword(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(guest.weapon_num < 5)
                                {
                                    strcpy(guest.inventory[guest.weapon_num] , "Sword (P)");
                                    guest.weapon_num++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                            }
                            y_loc++;
                        }
                        break;
                    case KEY_LEFT:
                        if(isfloor(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                        iscorridor(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                        isdoor(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                        istrap(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                        isfood(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                        istair(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                        isgold(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                        ismace(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                        isdagger(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                        iswand(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                        isarrow(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                        issword(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                        istreasure(dungeons[floor].naghseh[y_loc][x_loc - 1]))
                        {
                            if(dungeons[floor].naghseh[y_loc][x_loc - 1] == '|'|| dungeons[floor].naghseh[y_loc][x_loc - 1] == '0' || dungeons[floor].naghseh[y_loc][x_loc - 1] == '=')
                            {
                                break;
                            }
                            else if(istrap(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(guest.health - 10 >= 0)
                                {
                                    showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc);
                                    guest.health -= 10;
                                }
                                else
                                    out = 2;
                            }
                            else if(dungeons[floor].naghseh[y_loc][x_loc] == 'f')
                            {
                                if(guest.health + 10 <= health_num)
                                {
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    guest.health+=10;
                                }
                            }
                            else if(dungeons[floor].naghseh[y_loc][x_loc] == 'G')
                            {
                                guest.points++;
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else if(ismace(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(guest.weapon_num < 5)
                                {
                                    strcpy(guest.inventory[guest.weapon_num] , "Mace (M)");
                                    guest.weapon_num++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                            }
                            else if(iswand(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(guest.weapon_num < 5)
                                {
                                    strcpy(guest.inventory[guest.weapon_num] , "Magic Wand (I)");
                                    guest.weapon_num++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                            }
                            else if(isdagger(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(guest.weapon_num < 5)
                                {
                                    strcpy(guest.inventory[guest.weapon_num] , "Dagger (p)");
                                    guest.weapon_num++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                            }
                            else if(isarrow(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(guest.weapon_num < 5)
                                {
                                    strcpy(guest.inventory[guest.weapon_num] , "Arrow (Y)");
                                    guest.weapon_num++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                            }
                            else if(issword(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(guest.weapon_num < 5)
                                {
                                    strcpy(guest.inventory[guest.weapon_num] , "Sword (P)");
                                    guest.weapon_num++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                            }
                            x_loc--;
                        }
                        break;
                    case KEY_RIGHT:
                        if(isfloor(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                        iscorridor(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                        isdoor(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                        istrap(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                        isfood(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                        istair(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                        isgold(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                        ismace(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                        isdagger(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                        iswand(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                        isarrow(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                        issword(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                        istreasure(dungeons[floor].naghseh[y_loc][x_loc + 1]))
                        {
                            if(dungeons[floor].naghseh[y_loc][x_loc + 1] == '|'|| dungeons[floor].naghseh[y_loc][x_loc + 1] == '0' || dungeons[floor].naghseh[y_loc][x_loc + 1] == '=')
                            {
                                break;
                            }
                            else if(istrap(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(guest.health - 10 >= 0)
                                {
                                    showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc);
                                    guest.health -= 10;
                                }
                                else
                                    out = 2;
                            }
                            else if(dungeons[floor].naghseh[y_loc][x_loc] == 'f')
                            {
                                if(guest.health + 10 <= health_num)
                                {
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    guest.health+=10;
                                }
                            }
                            else if(dungeons[floor].naghseh[y_loc][x_loc] == 'G')
                            {
                                guest.points++;
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else if(ismace(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(guest.weapon_num < 5)
                                {
                                    strcpy(guest.inventory[guest.weapon_num] , "Mace (M)");
                                    guest.weapon_num++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                            }
                            else if(iswand(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(guest.weapon_num < 5)
                                {
                                    strcpy(guest.inventory[guest.weapon_num] , "Magic Wand (I)");
                                    guest.weapon_num++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                            }
                            else if(isdagger(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(guest.weapon_num < 5)
                                {
                                    strcpy(guest.inventory[guest.weapon_num] , "Dagger (p)");
                                    guest.weapon_num++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                            }
                            else if(isarrow(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(guest.weapon_num < 5)
                                {
                                    strcpy(guest.inventory[guest.weapon_num] , "Arrow (Y)");
                                    guest.weapon_num++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                            }
                            else if(issword(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                if(guest.weapon_num < 5)
                                {
                                    strcpy(guest.inventory[guest.weapon_num] , "Sword (P)");
                                    guest.weapon_num++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                            }
                            x_loc++;
                        }
                        break;
                    
                    case '>':
                        if(istair(dungeons[floor].naghseh[y_loc][x_loc]))
                        {
                            switch (floor)
                            {
                            case 0:
                                if(pelle[0].x == x_loc && pelle[0].y == y_loc)
                                {
                                    floor++;
                                    y_loc = pelle[1].y;
                                    x_loc = pelle[1].x;
                                }
                                break;
                            case 1:
                                if(pelle[1].x == x_loc && pelle[1].y == y_loc)
                                {
                                    floor--;
                                    y_loc = pelle[0].y;
                                    x_loc = pelle[0].x;
                                }
                                else if(pelle[2].x == x_loc && pelle[2].y == y_loc)
                                {
                                    floor++;
                                    y_loc = pelle[3].y;
                                    x_loc = pelle[3].x;
                                }
                                break;
                            case 2:
                                if(pelle[3].x == x_loc && pelle[3].y == y_loc)
                                {
                                    floor--;
                                    y_loc = pelle[2].y;
                                    x_loc = pelle[2].x;
                                }
                                else if(pelle[4].x == x_loc && pelle[4].y == y_loc)
                                {
                                    floor++;
                                    y_loc = pelle[5].y;
                                    x_loc = pelle[5].x;
                                }
                                break;
                            case 3:
                                if(pelle[5].x == x_loc && pelle[5].y == y_loc)
                                {
                                    floor--;
                                    y_loc = pelle[4].y;
                                    x_loc = pelle[4].x;
                                }
                                break;
                            default:
                                break;
                            }
                        }
                        else if(istreasure(dungeons[floor].naghseh[y_loc][x_loc]))
                        {
                            x_loc = 10;
                            y_loc = 10;
                            floor++;
                            out = 1;
                            guest.points+=100;
                        }
                        break;
                    case 'i':
                        WINDOW* inventory = newwin(row , col , 0 , 0);
                        box(inventory , 0 , 0);
                        refresh();
                        keypad(inventory , TRUE);
                        wrefresh(inventory);
                        wbkgd(inventory , COLOR_PAIR(4));
                        int inventory_highlight = 0;
                        int inventory_decision;
                        while(1)
                        {
                            for(int i = 0 ; i < guest.weapon_num ; i++)
                            {
                                int item_len = strlen(guest.inventory[i]);
                                if(i == inventory_highlight)
                                {
                                    wattron(inventory , A_REVERSE);
                                }
                                mvwprintw(inventory , i + 1 , col/2 - item_len/2 , guest.inventory[i]);
                                wattroff(inventory , A_REVERSE);
                            }
                            inventory_decision = wgetch(inventory);
                            switch (inventory_decision)
                            {
                            case KEY_UP:
                                inventory_highlight--;
                                if(inventory_highlight == -1)
                                {
                                    inventory_highlight = guest.weapon_num - 1;
                                }
                                break;
                            case KEY_DOWN:
                                inventory_highlight++;
                                if(inventory_highlight == guest.weapon_num)
                                {
                                    inventory_highlight = 0;
                                }
                                break;
                            default:
                                break;
                            }
                            if(inventory_decision == 10)
                            {
                                break;
                            }
                            if(inventory_highlight == 0)
                            {
                                if(strcmp(guest.inventory[inventory_highlight] , "Mace (M)") == 0)
                                {
                                    guest.weapon = 5;
                                }
                                else if(strcmp(guest.inventory[inventory_highlight] , "Dagger (p)") == 0)
                                {
                                    guest.weapon = 12;
                                }
                                else if(strcmp(guest.inventory[inventory_highlight] , "Magic Wand (I)") == 0)
                                {
                                    guest.weapon = 15;
                                }
                                else if(strcmp(guest.inventory[inventory_highlight] , "Arrow (Y)") == 0)
                                {
                                    guest.weapon = 5;
                                }
                                else if(strcmp(guest.inventory[inventory_highlight] , "Sword (P)") == 0)
                                {
                                    guest.weapon = 10;
                                }
                            }
                            else if(inventory_highlight == 1)
                            {
                                if(strcmp(guest.inventory[inventory_highlight] , "Mace (M)") == 0)
                                {
                                    guest.weapon = 5;
                                }
                                else if(strcmp(guest.inventory[inventory_highlight] , "Dagger (p)") == 0)
                                {
                                    guest.weapon = 12;
                                }
                                else if(strcmp(guest.inventory[inventory_highlight] , "Magic Wand (I)") == 0)
                                {
                                    guest.weapon = 15;
                                }
                                else if(strcmp(guest.inventory[inventory_highlight] , "Arrow (Y)") == 0)
                                {
                                    guest.weapon = 5;
                                }
                                else if(strcmp(guest.inventory[inventory_highlight] , "Sword (P)") == 0)
                                {
                                    guest.weapon = 10;
                                }
                            }
                            else if(inventory_highlight == 2)
                            {
                                if(strcmp(guest.inventory[inventory_highlight] , "Mace (M)") == 0)
                                {
                                    guest.weapon = 5;
                                }
                                else if(strcmp(guest.inventory[inventory_highlight] , "Dagger (p)") == 0)
                                {
                                    guest.weapon = 12;
                                }
                                else if(strcmp(guest.inventory[inventory_highlight] , "Magic Wand (I)") == 0)
                                {
                                    guest.weapon = 15;
                                }
                                else if(strcmp(guest.inventory[inventory_highlight] , "Arrow (Y)") == 0)
                                {
                                    guest.weapon = 5;
                                }
                                else if(strcmp(guest.inventory[inventory_highlight] , "Sword (P)") == 0)
                                {
                                    guest.weapon = 10;
                                }
                            }
                            else if(inventory_highlight == 3)
                            {
                                if(strcmp(guest.inventory[inventory_highlight] , "Mace (M)") == 0)
                                {
                                    guest.weapon = 5;
                                }
                                else if(strcmp(guest.inventory[inventory_highlight] , "Dagger (p)") == 0)
                                {
                                    guest.weapon = 12;
                                }
                                else if(strcmp(guest.inventory[inventory_highlight] , "Magic Wand (I)") == 0)
                                {
                                    guest.weapon = 15;
                                }
                                else if(strcmp(guest.inventory[inventory_highlight] , "Arrow (Y)") == 0)
                                {
                                    guest.weapon = 5;
                                }
                                else if(strcmp(guest.inventory[inventory_highlight] , "Sword (P)") == 0)
                                {
                                    guest.weapon = 10;
                                }
                            }
                            else if(inventory_highlight == 4)
                            {
                                if(strcmp(guest.inventory[inventory_highlight] , "Mace (M)") == 0)
                                {
                                    guest.weapon = 5;
                                }
                                else if(strcmp(guest.inventory[inventory_highlight] , "Dagger (p)") == 0)
                                {
                                    guest.weapon = 12;
                                }
                                else if(strcmp(guest.inventory[inventory_highlight] , "Magic Wand (I)") == 0)
                                {
                                    guest.weapon = 15;
                                }
                                else if(strcmp(guest.inventory[inventory_highlight] , "Arrow (Y)") == 0)
                                {
                                    guest.weapon = 5;
                                }
                                else if(strcmp(guest.inventory[inventory_highlight] , "Sword (P)") == 0)
                                {
                                    guest.weapon = 10;
                                }
                            }
                        }
                        break;
                    case 's':
                        showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc + 1 , y_loc + 1);
                        showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc - 1 , y_loc - 1);
                        showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc - 1 , y_loc);
                        showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc + 1 , y_loc);
                        showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc - 1);
                        showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc + 1);
                        showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc - 1 , y_loc + 1);
                        showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc + 1 , y_loc - 1);
                        break;
                    case 'w':
                        if(ismace(dungeons[floor].naghseh[y_loc][x_loc]))
                        {
                            if(strcmp(guest.inventory[1] , "NO WEAPON"))
                            {
                                strcpy(guest.inventory[1] , "Mace (M)");
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else if(strcmp(guest.inventory[2] , "NO WEAPON"))
                            {
                                strcpy(guest.inventory[2] , "Mace (M)");
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else if(strcmp(guest.inventory[3] , "NO WEAPON"))
                            {
                                strcpy(guest.inventory[3] , "Mace (M)");
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else if(strcmp(guest.inventory[4] , "NO WEAPON"))
                            {
                                strcpy(guest.inventory[4] , "Mace (M)");
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else if(strcmp(guest.inventory[5] , "NO WEAPON"))
                            {
                                strcpy(guest.inventory[5] , "Mace (M)");
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else
                            {
                                char weap;
                                if(strcmp(guest.inventory[5] , "Mace (M)") == 0)
                                {
                                    weap = 'M';
                                }
                                else if(strcmp(guest.inventory[5] , "Dagger (p)") == 0)
                                {
                                    weap = 'p';
                                }
                                else if(strcmp(guest.inventory[5] , "Magic Wand (I)") == 0)
                                {
                                    weap = 'I';
                                }
                                else if(strcmp(guest.inventory[5] , "Arrow (Y)") == 0)
                                {
                                    weap = 'Y';
                                }
                                else if(strcmp(guest.inventory[5] , "Sword (P)") == 0)
                                {
                                    weap = 'P';
                                }
                                dungeons[floor].naghseh[y_loc][x_loc] = weap;
                                strcpy(guest.inventory[5] , "Mace (M)");
                            }
                        }
                        else if(iswand(dungeons[floor].naghseh[y_loc][x_loc]))
                        {
                            if(strcmp(guest.inventory[1] , "NO WEAPON"))
                            {
                                strcpy(guest.inventory[1] , "Magic Wand (I)");
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else if(strcmp(guest.inventory[2] , "NO WEAPON"))
                            {
                                strcpy(guest.inventory[2] , "Magic Wand (I)");
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else if(strcmp(guest.inventory[3] , "NO WEAPON"))
                            {
                                strcpy(guest.inventory[3] , "Magic Wand (I)");
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else if(strcmp(guest.inventory[4] , "NO WEAPON"))
                            {
                                strcpy(guest.inventory[4] , "Magic Wand (I)");
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else if(strcmp(guest.inventory[5] , "NO WEAPON"))
                            {
                                strcpy(guest.inventory[5] , "Magic Wand (I)");
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else
                            {
                                char weap;
                                if(strcmp(guest.inventory[5] , "Mace (M)") == 0)
                                {
                                    weap = 'M';
                                }
                                else if(strcmp(guest.inventory[5] , "Dagger (p)") == 0)
                                {
                                    weap = 'p';
                                }
                                else if(strcmp(guest.inventory[5] , "Magic Wand (I)") == 0)
                                {
                                    weap = 'I';
                                }
                                else if(strcmp(guest.inventory[5] , "Arrow (Y)") == 0)
                                {
                                    weap = 'Y';
                                }
                                else if(strcmp(guest.inventory[5] , "Sword (P)") == 0)
                                {
                                    weap = 'P';
                                }
                                dungeons[floor].naghseh[y_loc][x_loc] = weap;
                                strcpy(guest.inventory[5] , "Magic Wand (I)");
                            }
                        }
                        else if(isdagger(dungeons[floor].naghseh[y_loc][x_loc]))
                        {
                            if(strcmp(guest.inventory[1] , "NO WEAPON"))
                            {
                                strcpy(guest.inventory[1] , "Dagger (p)");
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else if(strcmp(guest.inventory[2] , "NO WEAPON"))
                            {
                                strcpy(guest.inventory[2] , "Dagger (p)");
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else if(strcmp(guest.inventory[3] , "NO WEAPON"))
                            {
                                strcpy(guest.inventory[3] , "Dagger (p)");
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else if(strcmp(guest.inventory[4] , "NO WEAPON"))
                            {
                                strcpy(guest.inventory[4] , "Dagger (p)");
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else if(strcmp(guest.inventory[5] , "NO WEAPON"))
                            {
                                strcpy(guest.inventory[5] , "Dagger (p)");
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else
                            {
                                char weap;
                                if(strcmp(guest.inventory[5] , "Mace (M)") == 0)
                                {
                                    weap = 'M';
                                }
                                else if(strcmp(guest.inventory[5] , "Dagger (p)") == 0)
                                {
                                    weap = 'p';
                                }
                                else if(strcmp(guest.inventory[5] , "Magic Wand (I)") == 0)
                                {
                                    weap = 'I';
                                }
                                else if(strcmp(guest.inventory[5] , "Arrow (Y)") == 0)
                                {
                                    weap = 'Y';
                                }
                                else if(strcmp(guest.inventory[5] , "Sword (P)") == 0)
                                {
                                    weap = 'P';
                                }
                                dungeons[floor].naghseh[y_loc][x_loc] = weap;
                                strcpy(guest.inventory[5] , "Dagger (p)");
                            }
                        }
                        else if(isarrow(dungeons[floor].naghseh[y_loc][x_loc]))
                        {
                            if(strcmp(guest.inventory[1] , "NO WEAPON"))
                            {
                                strcpy(guest.inventory[1] , "Arrow (Y)");
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else if(strcmp(guest.inventory[2] , "NO WEAPON"))
                            {
                                strcpy(guest.inventory[2] , "Arrow (Y)");
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else if(strcmp(guest.inventory[3] , "NO WEAPON"))
                            {
                                strcpy(guest.inventory[3] , "Arrow (Y)");
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else if(strcmp(guest.inventory[4] , "NO WEAPON"))
                            {
                                strcpy(guest.inventory[4] , "Arrow (Y)");
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else if(strcmp(guest.inventory[5] , "NO WEAPON"))
                            {
                                strcpy(guest.inventory[5] , "Arrow (Y)");
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else
                            {
                                char weap;
                                if(strcmp(guest.inventory[5] , "Mace (M)") == 0)
                                {
                                    weap = 'M';
                                }
                                else if(strcmp(guest.inventory[5] , "Dagger (p)") == 0)
                                {
                                    weap = 'p';
                                }
                                else if(strcmp(guest.inventory[5] , "Magic Wand (I)") == 0)
                                {
                                    weap = 'I';
                                }
                                else if(strcmp(guest.inventory[5] , "Arrow (Y)") == 0)
                                {
                                    weap = 'Y';
                                }
                                else if(strcmp(guest.inventory[5] , "Sword (P)") == 0)
                                {
                                    weap = 'P';
                                }
                                dungeons[floor].naghseh[y_loc][x_loc] = weap;
                                strcpy(guest.inventory[5] , "Arrow (Y)");
                            }
                        }
                        else if(issword(dungeons[floor].naghseh[y_loc][x_loc]))
                        {
                            if(strcmp(guest.inventory[1] , "NO WEAPON"))
                            {
                                strcpy(guest.inventory[1] , "Sword (P)");
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else if(strcmp(guest.inventory[2] , "NO WEAPON"))
                            {
                                strcpy(guest.inventory[2] , "Sword (P)");
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else if(strcmp(guest.inventory[3] , "NO WEAPON"))
                            {
                                strcpy(guest.inventory[3] , "Sword (P)");
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else if(strcmp(guest.inventory[4] , "NO WEAPON"))
                            {
                                strcpy(guest.inventory[4] , "Sword (P)");
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else if(strcmp(guest.inventory[5] , "NO WEAPON"))
                            {
                                strcpy(guest.inventory[5] , "Sword (P)");
                                dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            }
                            else
                            {
                                char weap;
                                if(strcmp(guest.inventory[5] , "Mace (M)") == 0)
                                {
                                    weap = 'M';
                                }
                                else if(strcmp(guest.inventory[5] , "Dagger (p)") == 0)
                                {
                                    weap = 'p';
                                }
                                else if(strcmp(guest.inventory[5] , "Magic Wand (I)") == 0)
                                {
                                    weap = 'I';
                                }
                                else if(strcmp(guest.inventory[5] , "Arrow (Y)") == 0)
                                {
                                    weap = 'Y';
                                }
                                else if(strcmp(guest.inventory[5] , "Sword (P)") == 0)
                                {
                                    weap = 'P';
                                }
                                dungeons[floor].naghseh[y_loc][x_loc] = weap;
                                strcpy(guest.inventory[5] , "Sword (P)");
                            }
                        }
                        break;
                    case 'S':
                        WINDOW* setting = newwin(row , col , 0 , 0);
                        box(setting , 0 , 0);
                        refresh();
                        keypad(setting , TRUE);
                        wrefresh(setting);
                        wbkgd(setting , COLOR_PAIR(4));
                        char setting_option[2][MAX_SIZE] = {"SAVE" , "EXIT"};
                        int setting_highlight = 0;
                        int setting_decision;
                        while (1)
                        {
                            for(int i = 0 ; i < 2 ; i++)
                            {
                                int setting_len = strlen(setting_option[i]);
                                if(i == setting_highlight)
                                {
                                    wattron(setting , A_REVERSE);
                                }
                                mvwprintw(setting , i + row/2 - 4 , col/2 - setting_len/2 , setting_option[i]);
                                wattroff(setting , A_REVERSE);
                            }
                            setting_decision = wgetch(setting);
                            switch (setting_decision)
                            {
                            case KEY_UP:
                                setting_highlight--;
                                if(setting_highlight == -1)
                                {
                                    setting_highlight = 1;
                                }
                                break;
                            case KEY_DOWN:
                                setting_highlight++;
                                if(setting_highlight == 2)
                                {
                                    setting_highlight = 0;
                                }
                                break;
                            default:
                                break;
                            }
                            if(setting_decision == 10)
                            {
                                break;
                            }
                        }
                        if(setting_highlight == 0)
                        {
                            FILE * map_1 = fopen("map-1-defualt.txt" , "w");
                            FILE * map_2 = fopen("map-2-defualt.txt" , "w");
                            FILE * map_3 = fopen("map-3-defualt.txt" , "w");
                            FILE * map_4 = fopen("map-4-defualt.txt" , "w");
                            FILE * treasure_map = fopen("treasure-defualt.txt" , "w");
                            FILE * show_1 = fopen("show-1-defualt.txt" , "w");
                            FILE * show_2 = fopen("show-2-defualt.txt" , "w");
                            FILE * show_3 = fopen("show-3-defualt.txt" , "w");
                            FILE * show_4 = fopen("show-4-defualt.txt" , "w");
                            FILE * show_treasure = fopen("show-defualt.txt" , "w");
                            FILE * guestfile = fopen("defualt.txt" , "a");
                            for(int i = 0 ; i < row ; i++)
                            {
                                fprintf(map_1 ,"%s\n"  , dungeons[0].naghseh[i]);
                            }
                            for(int i = 0 ; i < row ; i++)
                            {
                                fprintf(map_2 ,"%s\n"  , dungeons[1].naghseh[i]);
                            }
                            for(int i = 0 ; i < row ; i++)
                            {
                                fprintf(map_3 ,"%s\n"  , dungeons[2].naghseh[i]);
                            }
                            for(int i = 0 ; i < row ; i++)
                            {
                                fprintf(map_4 ,"%s\n"  , dungeons[3].naghseh[i]);
                            }
                            for(int i = 0 ; i < row ; i++)
                            {
                                fprintf(treasure_map ,"%s\n"  , dungeons[4].naghseh[i]);
                            }

                            for(int i = 0 ; i < row ; i++)
                            {
                                for(int j = 0 ; j < col ; j++)
                                {
                                    fprintf(show_1 , "%d " , dungeons[0].show[i][j]);
                                }
                                fprintf(show_1 , "\n");
                            }

                            for(int i = 0 ; i < row ; i++)
                            {
                                for(int j = 0 ; j < col ; j++)
                                {
                                    fprintf(show_2 , "%d " , dungeons[0].show[i][j]);
                                }
                                fprintf(show_2 , "\n");
                            }

                            for(int i = 0 ; i < row ; i++)
                            {
                                for(int j = 0 ; j < col ; j++)
                                {
                                    fprintf(show_3 , "%d " , dungeons[0].show[i][j]);
                                }
                                fprintf(show_3 , "\n");
                            }

                            for(int i = 0 ; i < row ; i++)
                            {
                                for(int j = 0 ; j < col ; j++)
                                {
                                    fprintf(show_4 , "%d " , dungeons[0].show[i][j]);
                                }
                                fprintf(show_4 , "\n");
                            }

                            for(int i = 0 ; i < row ; i++)
                            {
                                for(int j = 0 ; j < col ; j++)
                                {
                                    fprintf(show_treasure , "%d " , dungeons[0].show[i][j]);
                                }
                                fprintf(show_treasure , "\n");
                            }
                            fprintf(guestfile , "%d\n" , guest.health);
                            fprintf(guestfile , "%d\n" , guest.points);
                            fprintf(guestfile , "%d\n" , guest.experience);
                            fprintf(guestfile , "%d\n" , y_loc);
                            fprintf(guestfile , "%d\n" , x_loc);
                            fprintf(guestfile , "%d\n" , floor);
                            fprintf(guestfile , "%d\n" , pelle[0].x);
                            fprintf(guestfile , "%d\n" , pelle[0].y);
                            fprintf(guestfile , "%d\n" , pelle[1].x);
                            fprintf(guestfile , "%d\n" , pelle[1].y);
                            fprintf(guestfile , "%d\n" , pelle[2].x);
                            fprintf(guestfile , "%d\n" , pelle[2].y);
                            fprintf(guestfile , "%d\n" , pelle[3].x);
                            fprintf(guestfile , "%d\n" , pelle[3].y);
                            fprintf(guestfile , "%d\n" , pelle[4].x);
                            fprintf(guestfile , "%d\n" , pelle[4].y);
                            fprintf(guestfile , "%d\n" , pelle[5].x);
                            fprintf(guestfile , "%d\n" , pelle[5].y);
                            fprintf(guestfile , "%d\n" , guest.weapon);
                            for(int i = 0 ; i < 5 ; i++)
                            {
                                for(int j = 0 ; j < 4 ; j++)
                                    fprintf(guestfile , "%d %d" , beasts[i][j].x , beasts[i][j].y);
                                fprintf(guestfile , "\n");
                            }
                            for(int i = 0 ; i < 10 ; i++)
                            {
                                fprintf(guestfile , "%s\n" , guest.inventory[i]);
                            }
                            clear();
                            out = 1;
                        }
                        else
                        {
                            out = 2;
                        }
                        
                        break;
                    default:
                        break;
                    }
                    
                }
            }

        }
        else if(highlight == 3)
        {
            WINDOW* setting_menu = newwin(row , col , 0 , 0);
            box(setting_menu,0,0);
            refresh();
            wrefresh(setting_menu);
            wbkgd(setting_menu , COLOR_PAIR(4));
            char setting_info[3][100] = {"dificulty"};
            int info1_len = strlen(setting_info[0]);
            char Tracks[3][10] = {"HARD-CORE" , "MEDIUM" , "EASY" };
            mvwprintw(setting_menu , 0 , col/2 - info1_len/2 , setting_info[0]);
            int highlight_s = 0;
            int decision_s;
            noecho();
            while(1){
                for(int i = 0 ; i < 3 ; i++){
                    int len = strlen(Tracks[i]);
                    if(i == highlight_s){
                        wattron(menu_win , A_REVERSE);
                    }
                    mvwprintw(menu_win , i + row/2 - 4 , col/2 - len/2 , Tracks[i]);
                    wattroff(menu_win , A_REVERSE);
                }
                decision_s = wgetch(menu_win);
                switch(decision_s){
                    case KEY_UP:
                        highlight_s--;
                        if(highlight_s == -1){
                            highlight_s = 2;
                        }
                        break;
                    case KEY_DOWN:
                        highlight_s++;
                        if(highlight_s == 3){
                            highlight_s = 0;
                        }
                        break;
                    default:
                        break;
                }
                if(decision_s == 10){
                    break;
                }
            }
            
            if(highlight_s == 0)
            {
                dificulty = 0;
                health_num = health(dificulty); 
            }
            if(highlight_s == 1)
            {
                dificulty = 1;
                health_num = health(dificulty); 
            }
            if(highlight_s == 2)
            {
                dificulty = 2;
                health_num = health(dificulty); 
            }
            // if(highlight_s == 3)
            // {
            //     stop();
            // }
        }
        else if(highlight == 4)
        {
            // clear();
            FILE * file = fopen("all-names.txt" , "r");
            char name[MAX_SIZE][MAX_SIZE];
            char final_names[MAX_SIZE][MAX_SIZE];
            char names[MAX_SIZE][MAX_SIZE];
            char file_names[MAX_SIZE][MAX_SIZE];
            int score_arr[MAX_SIZE];
            int i = 0;
            if(file == NULL)
            {
                endwin();
                printf("No player exists\n");
                return 1;
            }
            int l = 0;
            while (fscanf(file , "%s" , names[i]) == 1 && i < MAX_SIZE)
            {
                strcpy(file_names[i] , "usr-points-");
                strcpy(name[i] , names[i]);
                strcat(names[i] , ".txt");
                strcat(file_names[i] , names[i]);
                FILE * points = fopen(file_names[i] , "r");
                if(points != NULL)
                {
                    fscanf(points , "%d" , &score_arr[l]);
                    strcpy(final_names[l] , name[i]);
                    fclose(points);
                    l++;
                }
                i++;
            }

            // // sorting.
            for(int j = 0 ; j < l ; j++)
            {
                for(int k = j + 1 ; k < l ; k++)
                {
                    if(score_arr[j] < score_arr[k])
                    {
                        int temp = score_arr[k];
                        char temp_1[MAX_SIZE];
                        strcpy(temp_1 , final_names[k]);
                        score_arr[k] = score_arr[j];
                        score_arr[j] = temp;
                        strcpy(final_names[k] , final_names[j]);
                        strcpy(final_names[j] , temp_1);
                    }
                }
            }
            int height = row, width = col;
            WINDOW *scoreboard_win = newwin(height, width, 0, 0);
            int num = 10;
            if(l < 10)
            {
                num = l;
            }
            draw_scoreboard(scoreboard_win , final_names , score_arr , num);
            getch();


            
        }
        else if(highlight == 5)
        {
            clear();
            FILE * map_1 = fopen("map-1-defualt.txt" , "r");
            FILE * map_2 = fopen("map-2-defualt.txt" , "r");
            FILE * map_3 = fopen("map-3-defualt.txt" , "r");
            FILE * map_4 = fopen("map-4-defualt.txt" , "r");
            FILE * treasure_map = fopen("treasure-defualt.txt" , "r");
            FILE * show_1 = fopen("show-1-defualt.txt" , "r");
            FILE * show_2 = fopen("show-2-defualt.txt" , "r");
            FILE * show_3 = fopen("show-3-defualt.txt" , "r");
            FILE * show_4 = fopen("show-4-defualt.txt" , "r");
            FILE * show_treasure = fopen("show-defualt.txt" , "r");
            FILE * guestfile = fopen("defualt.txt" , "r");
            if(guestfile != NULL)
            {
                int index_1 = 0;
                while (fgets(dungeons[0].naghseh[index_1] , MAX_SIZE, map_1) != NULL && index_1 < row)
                {
                    dungeons[0].naghseh[index_1][strcspn(dungeons[0].naghseh[index_1] , "\n")] = '\0';
                    index_1++;
                }
                int index_2 = 0;
                while (fgets(dungeons[1].naghseh[index_2] , MAX_SIZE , map_2) != NULL && index_2 < row)
                {
                    dungeons[1].naghseh[index_2][strcspn(dungeons[1].naghseh[index_2] , "\n")] = '\0';
                    index_2++;
                }
                int index_3 = 0;
                while (fgets(dungeons[2].naghseh[index_3] , MAX_SIZE , map_3) != NULL && index_3 < row)
                {
                    dungeons[2].naghseh[index_3][strcspn(dungeons[0].naghseh[index_3] , "\n")] = '\0';
                    index_3++;
                }
                int index_4 = 0;
                while (fgets(dungeons[3].naghseh[index_4] , MAX_SIZE , map_4) != NULL && index_4 < row)
                {
                    dungeons[3].naghseh[index_4][strcspn(dungeons[3].naghseh[index_4] , "\n")] = '\0';
                    index_4++;
                }

                int index_5 = 0;
                while (fgets(dungeons[4].naghseh[index_5] , MAX_SIZE , treasure_map) != NULL && index_5 < row)
                {
                    dungeons[4].naghseh[index_5][strcspn(dungeons[4].naghseh[index_5] , "\n")] = '\0';
                    index_5++;
                }

                for(int i = 0 ; i < row ; i++)
                {
                    for(int j = 0 ; j < col ; j++)
                    {
                        fscanf(show_1 , "%d" , &dungeons[0].show[i][j]);
                    }
                }
                for(int i = 0 ; i < row ; i++)
                {
                    for(int j = 0 ; j < col ; j++)
                    {
                        fscanf(show_2 , "%d" , &dungeons[1].show[i][j]);
                    }
                }
                for(int i = 0 ; i < row ; i++)
                {
                    for(int j = 0 ; j < col ; j++)
                    {
                        fscanf(show_3 , "%d" , &dungeons[2].show[i][j]);
                    }
                }
                for(int i = 0 ; i < row ; i++)
                {
                    for(int j = 0 ; j < col ; j++)
                    {
                        fscanf(show_4 , "%d" , &dungeons[3].show[i][j]);
                    }
                }
                for(int i = 0 ; i < row ; i++)
                {
                    for(int j = 0 ; j < col ; j++)
                    {
                        fscanf(show_treasure , "%d" , &dungeons[4].show[i][j]);
                    }
                }
                profile guest;
                location pelle[6];
                location beasts[5][4];
                int x_loc , y_loc , floor;
                strcpy(guest.name , "guest-usr");
                fscanf(guestfile , "%d" ,&guest.health);
                fscanf(guestfile , "%d" , &guest.points);
                fscanf(guestfile , "%d" , &guest.experience);
                fscanf(guestfile , "%d" , &y_loc);
                fscanf(guestfile , "%d" , &x_loc);
                fscanf(guestfile , "%d" , &floor);
                fscanf(guestfile , "%d" , &pelle[0].x);
                fscanf(guestfile , "%d" , &pelle[0].y);
                fscanf(guestfile , "%d" , &pelle[1].x);
                fscanf(guestfile , "%d" , &pelle[1].y);
                fscanf(guestfile , "%d" , &pelle[2].x);
                fscanf(guestfile , "%d" , &pelle[2].y);
                fscanf(guestfile , "%d" , &pelle[3].x);
                fscanf(guestfile , "%d" , &pelle[3].y);
                fscanf(guestfile , "%d" , &pelle[4].x);
                fscanf(guestfile , "%d" , &pelle[4].y);
                fscanf(guestfile , "%d" , &pelle[5].x);
                fscanf(guestfile , "%d" , &pelle[5].y);
                fscanf(guestfile , "%d" , &guest.weapon);
                for(int i = 0 ; i < 5 ; i++)
                {
                    for(int j = 0 ; j < 4 ; j++)
                    {
                        fscanf(guestfile , "%d" , &beasts[i][j].x);
                        fscanf(guestfile , "%d" , &beasts[i][j].x);
                    }
                }
                int index = 0;
                while (index < 10)
                {
                    int a = fscanf(guestfile , " %s" , guest.inventory[index]);
                    if(a == -1)
                    {
                        break;
                    }
                    index++;
                }
                guest.weapon_num = index - 1;
                int out = 0;
                int finish = 0;
                keypad(stdscr , TRUE);
                while (1)
                {
                    if(out == 2 || out == 1)
                    {
                        clear();
                        WINDOW * option_menu = newwin(row , col , 0 , 0);
                        box(option_menu , 0 , 0);
                        keypad(option_menu , TRUE);
                        refresh();
                        wrefresh(option_menu);
                        wbkgd(option_menu , COLOR_PAIR(4));
                        char options[2][MAX_SIZE] = { "<new game>" ,
                                                        "<exit>"};
                        int highlight_option = 0;
                        int decision_option;
                        wattron(option_menu , COLOR_PAIR(6));
                        if(out == 2)
                            mvwprintw(option_menu , 0 , col/2 - 8/2 , "YOU LOST");
                        else if(out == 1)
                        {
                            mvwprintw(option_menu , 0 , col/2 - 7/2 , "YOU WON");
                        }
                        wattroff(option_menu , COLOR_PAIR(6));
                        while(1)
                        {
                            for(int i = 0 ; i < 2 ; i++)
                            {
                                int game_len = strlen(options[i]);
                                if(i == highlight_option)
                                {
                                    wattron(option_menu , A_REVERSE);
                                }
                                mvwprintw(option_menu , i + row/2 - 4 , col/2 - game_len/2 , options[i]);
                                wattroff(option_menu , A_REVERSE);
                            }
                            decision_option = wgetch(option_menu);
                            switch (decision_option)
                            {
                            case KEY_UP:
                                highlight_option--;
                                if(highlight_option == -1)
                                {
                                    highlight_option = 1;
                                }
                                break;
                            case KEY_DOWN:
                                highlight_option++;
                                if(highlight_option == 2)
                                {
                                    highlight_option = 0;
                                }
                            default:
                                break;
                            }
                            if(decision_option == 10)
                            {
                                break;
                            }
                        }
                        if(highlight_option == 1)
                        {
                            exit = 1;
                            break;
                        }
                        else
                        {
                            out = 0;
                        }
                    }
                    int move = 0;
                    while(1)
                    {
                        
                        clear();
                        if(out == 1)
                        {
                            break;
                        }
                        if(out == 2)
                        {
                            break;
                        }
                        refresh();
                        move++;
                        if(move%4 == 0)
                            guest.health--;
                        showcorridor(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc , 5);
                        for(int k = 0 ; k < 4 ; k++)
                        {
                            if (isfollower(dungeons[floor].naghseh[beasts[floor][k].y][beasts[floor][k].x]))
                            {
                                int range = range_monster(dungeons[floor].naghseh[beasts[floor][k].y][beasts[floor][k].x]);
                                int hurt = 0;
                                int x_m = beasts[floor][k].x;
                                int y_m = beasts[floor][k].y;
                                char temp = dungeons[floor].naghseh[beasts[floor][k].y][beasts[floor][k].x];
                                dungeons[floor].naghseh[beasts[floor][k].y][beasts[floor][k].x] = '.';
                                int distance_x = abs(x_loc - x_m);
                                int distance_y = abs(y_loc - y_m);
                                if((distance_x != 1 || distance_y != 1) && (distance_x < range && distance_y < range))
                                {
                                    if(abs(x_loc - (x_m - 1)) <= distance_x &&
                                    (!iswall(dungeons[floor].naghseh[y_m][x_m - 1]) && !iswindow(dungeons[floor].naghseh[y_m][x_m - 1]) && !isdoor(dungeons[floor].naghseh[y_m][x_m - 1]) && !ispillar(dungeons[floor].naghseh[y_m][x_m - 1])) && 
                                    abs(x_loc - (x_m - 1)) > 0)
                                    {
                                        x_m--;
                                        beasts[floor][k].x = x_m;
                                    }
                                    else if(abs(x_loc - (x_m + 1)) <= distance_x && 
                                    (!iswall(dungeons[floor].naghseh[y_m][x_m + 1]) && !iswindow(dungeons[floor].naghseh[y_m][x_m + 1]) && !isdoor(dungeons[floor].naghseh[y_m][x_m + 1]) && !ispillar(dungeons[floor].naghseh[y_m][x_m + 1])) && 
                                    abs(x_loc - (x_m + 1)) > 0)
                                    {
                                        x_m++;
                                        beasts[floor][k].x = x_m;
                                    }
                                    else if(abs(y_loc - (y_m - 1)) <= distance_y && 
                                    (!iswall(dungeons[floor].naghseh[y_m - 1][x_m]) && !iswindow(dungeons[floor].naghseh[y_m - 1][x_m]) && !isdoor(dungeons[floor].naghseh[y_m - 1][x_m]) && !ispillar(dungeons[floor].naghseh[y_m - 1][x_m])) && 
                                    abs(y_loc - (y_m - 1)) > 0)
                                    {
                                        y_m--;
                                        beasts[floor][k].y = y_m;
                                    }
                                    else if(abs(y_loc - (y_m + 1)) > 0 && 
                                    (!iswall(dungeons[floor].naghseh[y_m + 1][x_m]) && !iswindow(dungeons[floor].naghseh[y_m + 1][x_m]) && !isdoor(dungeons[floor].naghseh[y_m + 1][x_m]) && !ispillar(dungeons[floor].naghseh[y_m + 1][x_m])))
                                    {
                                        y_m++;
                                        beasts[floor][k].y = y_m;
                                    }
                                    hurt = 0;
                                }
                                else if(distance_x == 1 && distance_y == 1)
                                {
                                    hurt = 1;
                                }
                                dungeons[floor].naghseh[beasts[floor][k].y][beasts[floor][k].x] = temp;
                                if(hurt)
                                {
                                    int asib = damage(temp);
                                    if(guest.health - asib >= 0)
                                    {
                                        guest.health-=asib;
                                        mvprintw(0,40 , "You got hit by a monster!");
                                    }
                                    else
                                    {
                                        out = 2;
                                        continue;
                                    }
                                }
                            }
                        }
                        attron(COLOR_PAIR(4));
                        // mvprintw(10,0,dungeons[floor].naghseh[10]);
                        // getch();
                        print_map(row , col , dungeons[floor].naghseh , dungeons[floor].show);
                        mvprintw(y_loc , x_loc , "@");
                        mvprintw(0 , 0 , "your health is %d %d|" , y_loc , x_loc);
                        mvprintw(0 , 20 , "your point is %d |" , guest.points);
                        int kilid = getch();
                        switch (kilid)
                        {
                        case KEY_UP:
                            if(isfloor(dungeons[floor].naghseh[y_loc - 1][x_loc]) ||
                            iscorridor(dungeons[floor].naghseh[y_loc - 1][x_loc]) ||
                            isdoor(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                            istrap(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                            isfood(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                            istair(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                            isgold(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                            ismace(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                            isdagger(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                            iswand(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                            isarrow(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                            issword(dungeons[floor].naghseh[y_loc - 1][x_loc]) || 
                            istreasure(dungeons[floor].naghseh[y_loc - 1][x_loc]))
                            {
                                if(iswall(dungeons[floor].naghseh[y_loc - 1][x_loc]) || ispillar(dungeons[floor].naghseh[y_loc - 1][x_loc]) || iswindow(dungeons[floor].naghseh[y_loc - 1][x_loc]))
                                {
                                    break;
                                }
                                else if(istrap(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.health - 10 >= 0)
                                    {
                                        showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc);
                                        guest.health -= 10;
                                    }
                                    else
                                        out = 2;
                                }
                                else if(dungeons[floor].naghseh[y_loc][x_loc] == 'f')
                                {
                                    if(guest.health + 10 <= health_num)
                                    {
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        guest.health+=10;
                                    }
                                }
                                else if(dungeons[floor].naghseh[y_loc][x_loc] == 'G')
                                {
                                    guest.points++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(ismace(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Mace (M)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(iswand(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Magic Wand (I)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(isdagger(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Dagger (p)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(isarrow(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Arrow (Y)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(issword(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Sword (P)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                y_loc--;
                            }
                            break;
                        case KEY_DOWN:
                            if(isfloor(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            iscorridor(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            isdoor(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            istrap(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            isfood(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            istair(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            isgold(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            ismace(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            isdagger(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            iswand(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            isarrow(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            issword(dungeons[floor].naghseh[y_loc + 1][x_loc]) || 
                            istreasure(dungeons[floor].naghseh[y_loc + 1][x_loc]))
                            {
                                if(dungeons[floor].naghseh[y_loc + 1][x_loc] == '-'|| dungeons[floor].naghseh[y_loc + 1][x_loc] == '0' || dungeons[floor].naghseh[y_loc + 1][x_loc] == '=')
                                {
                                    break;
                                }
                                else if(istrap(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.health - 10 >= 0)
                                    {
                                        showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc);
                                        guest.health -= 10;
                                    }
                                    else
                                        out = 2;
                                }
                                else if(dungeons[floor].naghseh[y_loc][x_loc] == 'f')
                                {
                                    if(guest.health + 10 <= health_num)
                                    {
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        guest.health+=10;
                                    }
                                }
                                else if(dungeons[floor].naghseh[y_loc][x_loc] == 'G')
                                {
                                    guest.points++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(ismace(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Mace (M)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(iswand(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Magic Wand (I)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(isdagger(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Dagger (p)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(isarrow(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Arrow (Y)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(issword(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Sword (P)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                y_loc++;
                            }
                            break;
                        case KEY_LEFT:
                            if(isfloor(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            iscorridor(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            isdoor(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            istrap(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            isfood(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            istair(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            isgold(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            ismace(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            isdagger(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            iswand(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            isarrow(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            issword(dungeons[floor].naghseh[y_loc][x_loc - 1]) || 
                            istreasure(dungeons[floor].naghseh[y_loc][x_loc - 1]))
                            {
                                if(dungeons[floor].naghseh[y_loc][x_loc - 1] == '|'|| dungeons[floor].naghseh[y_loc][x_loc - 1] == '0' || dungeons[floor].naghseh[y_loc][x_loc - 1] == '=')
                                {
                                    break;
                                }
                                else if(istrap(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.health - 10 >= 0)
                                    {
                                        showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc);
                                        guest.health -= 10;
                                    }
                                    else
                                        out = 2;
                                }
                                else if(dungeons[floor].naghseh[y_loc][x_loc] == 'f')
                                {
                                    if(guest.health + 10 <= health_num)
                                    {
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        guest.health+=10;
                                    }
                                }
                                else if(dungeons[floor].naghseh[y_loc][x_loc] == 'G')
                                {
                                    guest.points++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(ismace(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Mace (M)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(iswand(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Magic Wand (I)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(isdagger(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Dagger (p)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(isarrow(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Arrow (Y)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(issword(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Sword (P)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                x_loc--;
                            }
                            break;
                        case KEY_RIGHT:
                            if(isfloor(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            iscorridor(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            isdoor(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            istrap(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            isfood(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            istair(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            isgold(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            ismace(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            isdagger(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            iswand(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            isarrow(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            issword(dungeons[floor].naghseh[y_loc][x_loc + 1]) || 
                            istreasure(dungeons[floor].naghseh[y_loc][x_loc + 1]))
                            {
                                if(dungeons[floor].naghseh[y_loc][x_loc + 1] == '|'|| dungeons[floor].naghseh[y_loc][x_loc + 1] == '0' || dungeons[floor].naghseh[y_loc][x_loc + 1] == '=')
                                {
                                    break;
                                }
                                else if(istrap(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.health - 10 >= 0)
                                    {
                                        showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc);
                                        guest.health -= 10;
                                    }
                                    else
                                        out = 2;
                                }
                                else if(dungeons[floor].naghseh[y_loc][x_loc] == 'f')
                                {
                                    if(guest.health + 10 <= health_num)
                                    {
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                        guest.health+=10;
                                    }
                                }
                                else if(dungeons[floor].naghseh[y_loc][x_loc] == 'G')
                                {
                                    guest.points++;
                                    dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                }
                                else if(ismace(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Mace (M)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(iswand(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Magic Wand (I)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(isdagger(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Dagger (p)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(isarrow(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Arrow (Y)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                else if(issword(dungeons[floor].naghseh[y_loc][x_loc]))
                                {
                                    if(guest.weapon_num < 5)
                                    {
                                        strcpy(guest.inventory[guest.weapon_num] , "Sword (P)");
                                        guest.weapon_num++;
                                        dungeons[floor].naghseh[y_loc][x_loc] = '.';
                                    }
                                }
                                x_loc++;
                            }
                            break;
                        
                        case '>':
                            if(istair(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                switch (floor)
                                {
                                case 0:
                                    if(pelle[0].x == x_loc && pelle[0].y == y_loc)
                                    {
                                        floor++;
                                        y_loc = pelle[1].y;
                                        x_loc = pelle[1].x;
                                    }
                                    break;
                                case 1:
                                    if(pelle[1].x == x_loc && pelle[1].y == y_loc)
                                    {
                                        floor--;
                                        y_loc = pelle[0].y;
                                        x_loc = pelle[0].x;
                                    }
                                    else if(pelle[2].x == x_loc && pelle[2].y == y_loc)
                                    {
                                        floor++;
                                        y_loc = pelle[3].y;
                                        x_loc = pelle[3].x;
                                    }
                                    break;
                                case 2:
                                    if(pelle[3].x == x_loc && pelle[3].y == y_loc)
                                    {
                                        floor--;
                                        y_loc = pelle[2].y;
                                        x_loc = pelle[2].x;
                                    }
                                    else if(pelle[4].x == x_loc && pelle[4].y == y_loc)
                                    {
                                        floor++;
                                        y_loc = pelle[5].y;
                                        x_loc = pelle[5].x;
                                    }
                                    break;
                                case 3:
                                    if(pelle[5].x == x_loc && pelle[5].y == y_loc)
                                    {
                                        floor--;
                                        y_loc = pelle[4].y;
                                        x_loc = pelle[4].x;
                                    }
                                    break;
                                default:
                                    break;
                                }
                            }
                            else if(istreasure(dungeons[floor].naghseh[y_loc][x_loc]))
                            {
                                x_loc = 10;
                                y_loc = 10;
                                floor++;
                                out = 1;
                                guest.points+=100;
                            }
                            break;
                        case 'i':
                            WINDOW* inventory = newwin(row , col , 0 , 0);
                            box(inventory , 0 , 0);
                            refresh();
                            keypad(inventory , TRUE);
                            wrefresh(inventory);
                            wbkgd(inventory , COLOR_PAIR(4));
                            int inventory_highlight = 0;
                            int inventory_decision;
                            while(1)
                            {
                                for(int i = 0 ; i < guest.weapon_num ; i++)
                                {
                                    int item_len = strlen(guest.inventory[i]);
                                    if(i == inventory_highlight)
                                    {
                                        wattron(inventory , A_REVERSE);
                                    }
                                    mvwprintw(inventory , i + 1 , col/2 - item_len/2 , guest.inventory[i]);
                                    wattroff(inventory , A_REVERSE);
                                }
                                inventory_decision = wgetch(inventory);
                                switch (inventory_decision)
                                {
                                case KEY_UP:
                                    inventory_highlight--;
                                    if(inventory_highlight == -1)
                                    {
                                        inventory_highlight = guest.weapon_num - 1;
                                    }
                                    break;
                                case KEY_DOWN:
                                    inventory_highlight++;
                                    if(inventory_highlight == guest.weapon_num)
                                    {
                                        inventory_highlight = 0;
                                    }
                                    break;
                                default:
                                    break;
                                }
                                if(inventory_decision == 10)
                                {
                                    break;
                                }
                            }
                            break;
                        case 's':
                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc + 1 , y_loc + 1);
                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc - 1 , y_loc - 1);
                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc - 1 , y_loc);
                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc + 1 , y_loc);
                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc - 1);
                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc + 1);
                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc - 1 , y_loc + 1);
                            showtraps(dungeons[floor].naghseh , dungeons[floor].show , x_loc + 1 , y_loc - 1);
                            break;
                        case 'S':
                            WINDOW* setting = newwin(row , col , 0 , 0);
                            box(setting , 0 , 0);
                            refresh();
                            keypad(setting , TRUE);
                            wrefresh(setting);
                            wbkgd(setting , COLOR_PAIR(4));
                            char setting_option[2][MAX_SIZE] = {"SAVE" , "EXIT"};
                            int setting_highlight = 0;
                            int setting_decision;
                            while (1)
                            {
                                for(int i = 0 ; i < 2 ; i++)
                                {
                                    int setting_len = strlen(setting_option[i]);
                                    if(i == setting_highlight)
                                    {
                                        wattron(setting , A_REVERSE);
                                    }
                                    mvwprintw(setting , i + row/2 - 4 , col/2 - setting_len/2 , setting_option[i]);
                                    wattroff(setting , A_REVERSE);
                                }
                                setting_decision = wgetch(setting);
                                switch (setting_decision)
                                {
                                case KEY_UP:
                                    setting_highlight--;
                                    if(setting_highlight == -1)
                                    {
                                        setting_highlight = 1;
                                    }
                                    break;
                                case KEY_DOWN:
                                    setting_highlight++;
                                    if(setting_highlight == 2)
                                    {
                                        setting_highlight = 0;
                                    }
                                    break;
                                default:
                                    break;
                                }
                                if(setting_decision == 10)
                                {
                                    break;
                                }
                            }
                            if(setting_highlight == 0)
                            {
                                FILE * map_1 = fopen("map-1-defualt.txt" , "w");
                                FILE * map_2 = fopen("map-2-defualt.txt" , "w");
                                FILE * map_3 = fopen("map-3-defualt.txt" , "w");
                                FILE * map_4 = fopen("map-4-defualt.txt" , "w");
                                FILE * treasure_map = fopen("treasure-defualt.txt" , "w");
                                FILE * show_1 = fopen("show-1-defualt.txt" , "w");
                                FILE * show_2 = fopen("show-2-defualt.txt" , "w");
                                FILE * show_3 = fopen("show-3-defualt.txt" , "w");
                                FILE * show_4 = fopen("show-4-defualt.txt" , "w");
                                FILE * show_treasure = fopen("show-defualt.txt" , "w");
                                FILE * guestfile = fopen("defualt.txt" , "w");
                                for(int i = 0 ; i < row ; i++)
                                {
                                    fprintf(map_1 ,"%s\n"  , dungeons[0].naghseh[i]);
                                }
                                for(int i = 0 ; i < row ; i++)
                                {
                                    fprintf(map_2 ,"%s\n"  , dungeons[1].naghseh[i]);
                                }
                                for(int i = 0 ; i < row ; i++)
                                {
                                    fprintf(map_3 ,"%s\n"  , dungeons[2].naghseh[i]);
                                }
                                for(int i = 0 ; i < row ; i++)
                                {
                                    fprintf(map_4 ,"%s\n"  , dungeons[3].naghseh[i]);
                                }
                                for(int i = 0 ; i < row ; i++)
                                {
                                    fprintf(treasure_map ,"%s\n"  , dungeons[4].naghseh[i]);
                                }

                                for(int i = 0 ; i < row ; i++)
                                {
                                    for(int j = 0 ; j < col ; j++)
                                    {
                                        fprintf(show_1 , "%d " , dungeons[0].show[i][j]);
                                    }
                                    fprintf(show_1 , "\n");
                                }

                                for(int i = 0 ; i < row ; i++)
                                {
                                    for(int j = 0 ; j < col ; j++)
                                    {
                                        fprintf(show_2 , "%d " , dungeons[0].show[i][j]);
                                    }
                                    fprintf(show_2 , "\n");
                                }

                                for(int i = 0 ; i < row ; i++)
                                {
                                    for(int j = 0 ; j < col ; j++)
                                    {
                                        fprintf(show_3 , "%d " , dungeons[0].show[i][j]);
                                    }
                                    fprintf(show_3 , "\n");
                                }

                                for(int i = 0 ; i < row ; i++)
                                {
                                    for(int j = 0 ; j < col ; j++)
                                    {
                                        fprintf(show_4 , "%d " , dungeons[0].show[i][j]);
                                    }
                                    fprintf(show_4 , "\n");
                                }

                                for(int i = 0 ; i < row ; i++)
                                {
                                    for(int j = 0 ; j < col ; j++)
                                    {
                                        fprintf(show_treasure , "%d " , dungeons[0].show[i][j]);
                                    }
                                    fprintf(show_treasure , "\n");
                                }
                                fprintf(guestfile , "%d\n" , guest.health);
                                fprintf(guestfile , "%d\n" , guest.points);
                                fprintf(guestfile , "%d\n" , guest.experience);
                                fprintf(guestfile , "%d\n" , y_loc);
                                fprintf(guestfile , "%d\n" , x_loc);
                                fprintf(guestfile , "%d\n" , floor);
                                fprintf(guestfile , "%d\n" , pelle[0].x);
                                fprintf(guestfile , "%d\n" , pelle[0].y);
                                fprintf(guestfile , "%d\n" , pelle[1].x);
                                fprintf(guestfile , "%d\n" , pelle[1].y);
                                fprintf(guestfile , "%d\n" , pelle[2].x);
                                fprintf(guestfile , "%d\n" , pelle[2].y);
                                fprintf(guestfile , "%d\n" , pelle[3].x);
                                fprintf(guestfile , "%d\n" , pelle[3].y);
                                fprintf(guestfile , "%d\n" , pelle[4].x);
                                fprintf(guestfile , "%d\n" , pelle[4].y);
                                fprintf(guestfile , "%d\n" , pelle[5].x);
                                fprintf(guestfile , "%d\n" , pelle[5].y);
                                for(int i = 0 ; i < 10 ; i++)
                                {
                                    fprintf(guestfile , "%s\n" , guest.inventory[i]);
                                }
                                clear();
                                out = 1;
                            }
                            else
                            {
                                out = 2;
                            }
                            
                            break;
                        default:
                            break;
                        }
                        
                    }
                }

                

                
            }
        }
    }
    endwin();
    return 0;
}