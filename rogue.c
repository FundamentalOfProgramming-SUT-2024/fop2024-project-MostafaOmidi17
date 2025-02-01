#include <ncurses.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <math.h>
// #include <cjson/cJSON.h> 
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#define track_1 "1.mp3"
#define track_2 "2.mp3"
#define track_3 "3.mp3"
#define MAX_SIZE 400




typedef struct prof
{
    char name[MAX_SIZE];
    char password[MAX_SIZE];
    char e_mail[MAX_SIZE];
    char map[4][MAX_SIZE][MAX_SIZE];
    char inventory[10][MAX_SIZE];
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



typedef struct naghseh
{
    char naghseh[MAX_SIZE][MAX_SIZE];
    int show[MAX_SIZE][MAX_SIZE];
    int RoomNum;
    rooms room[9];
}naghseh;
naghseh dungeons[4];
int stairs = 0;



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



void generate_map(int row , int col , rooms Room[] , int RoomNum , char naghsheh[][MAX_SIZE] , int floor , location pelle[])
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

    for(int i = 0 ; i < RoomNum ; i++)
    {
        int x ;
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
                            naghsheh[j][i_1] = '-';
                            Room[i].map[j][i_1] = '-';
                        }
                    }
                    else
                    {
                        int pilar = Random(0,10);
                        if(pilar == 0 && pillar_count < 4 && j > y + 1 && j < room_hight + y - 1 && i_1 > x + 1 && i_1 < x + room_width - 1)
                        {
                            pillar_count++;
                            naghsheh[j][i_1] = '0';
                            Room[i].map[j][i_1] = '0';
                        }
                        else if(pilar == 1)
                        {
                            naghsheh[j][i_1] = '^';
                            Room[i].map[j][i_1] = '^';
                        }
                        else if(pilar == 2)
                        {
                            //food
                            naghsheh[j][i_1] = 'f';
                            Room[i].map[j][i_1] = 'f';
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
    // for(int i = 0 ; i < RoomNum ; i++)
    // {
    //     for(int j = 0 ; j < Room[i].numdoor ; j++)
    //     {
    //         int x_i = Room[i].door->x;
    //         int y_i = Room[i].door->y;
    //         if(naghsheh[y_i - 1][x_i] != '#' && naghsheh[y_i + 1][x_i] != '#' && naghsheh[y_i][x_i - 1] != '#' && naghsheh[y_i][x_i + 1] != '#')
    //         {
    //             if(naghsheh[y_i][x_i - 1] == '.' || naghsheh[y_i][x_i - 1] == '0' || naghsheh[y_i][x_i - 1] == '^')
    //             {
    //                 naghsheh[y_i][x_i] = '|';
    //             }
    //             else if(naghsheh[y_i][x_i + 1] == '.' || naghsheh[y_i][x_i + 1] == '0' || naghsheh[y_i][x_i + 1] == '^')
    //             {
    //                 naghsheh[y_i][x_i] = '|';
    //             }
    //             else if(naghsheh[y_i - 1][x_i] == '.' || naghsheh[y_i - 1][x_i] == '0' || naghsheh[y_i - 1][x_i] == '^')
    //             {
    //                 naghsheh[y_i][x_i] = '|';
    //             }
    //             else if(naghsheh[y_i + 1][x_i] == '.' || naghsheh[y_i + 1][x_i] == '0' || naghsheh[y_i + 1][x_i] == '^')
    //             {
    //                 naghsheh[y_i][x_i] = '|';
    //             }
    //         }
    //     }
    // }

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

void showcorridor(char map[MAX_SIZE][MAX_SIZE] , int show[MAX_SIZE][MAX_SIZE] , int x , int y)
{
    for(int i = y - 5; i < y + 5 ; i++)
    {
        for(int j = x - 5 ; j < x + 5 ; j++)
        {
            show[i][j] = 1;
        }
    }
}

void showtraps(char map[MAX_SIZE][MAX_SIZE] , int show[MAX_SIZE][MAX_SIZE], int x , int y)
{
    show[y][x] = 1;
    map[y][x] = 't';
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
                mvaddch(j , i , map[j][i]);
            else if(map[j][i] == '^' && show[j][i] == 1)
                mvaddch(j , i , '.');
            else
                mvaddch(j , i , ' ');
        }
    }
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


    wbkgd(menu_win , COLOR_PAIR(3));
    refresh();
    wrefresh(menu_win);
    keypad(menu_win , TRUE);
    char menu[5][100] = {"<new usr>" ,
                        "<login usr>" ,
                        "<guest mode>" ,
                        "<setting>" ,
                        "<scoreboard>"};
    int highlight = 0;
    int decision;
    noecho();
    while(1){
        for(int i = 0 ; i < 5 ; i++){
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
                    highlight = 4;
                }
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == 5){
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
                break;
            default:
                break;
            }
            if(game_decision == 10)
            {
                break;
            }
        }
        if(game_highlight == 0)
        {}
        else
        {}
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
        if(game_highlight == 0)
        {}
        else
        {}

    }
    else if(highlight == 2)
    {
        noecho();
        keypad(stdscr , TRUE);
        clear();
        bkgd(' ');
        rooms Room[4][9];
        location pelle[6];
        int RoomNum[4];
        for(int i = 0 ; i < 4 ; i++)
        {
            dungeons[i].RoomNum = Random(3 , 9);
        }
        generate_map(row , col , dungeons[0].room , dungeons[0].RoomNum , dungeons[0].naghseh , 1 , pelle);
        generate_corridor(dungeons[0].room , dungeons[0].RoomNum , dungeons[0].naghseh);
        generate_map(row , col , dungeons[1].room , dungeons[1].RoomNum , dungeons[1].naghseh , 2 , pelle);
        generate_corridor(dungeons[1].room , dungeons[1].RoomNum , dungeons[1].naghseh);
        generate_map(row , col , dungeons[2].room , dungeons[2].RoomNum , dungeons[2].naghseh , 3 , pelle);
        generate_corridor(dungeons[2].room , dungeons[2].RoomNum , dungeons[2].naghseh);
        generate_map(row , col , dungeons[3].room , dungeons[3].RoomNum , dungeons[3].naghseh , 4 , pelle);
        generate_corridor(dungeons[3].room , dungeons[3].RoomNum , dungeons[3].naghseh);

        profile guest;
        strcpy(guest.name , "guest-usr");
        copy_map(row , col , guest.map[0] , dungeons[0].naghseh);
        copy_map(row , col , guest.map[1] , dungeons[1].naghseh);
        copy_map(row , col , guest.map[2] , dungeons[2].naghseh);
        copy_map(row , col , guest.map[3] , dungeons[3].naghseh);
        guest.health = 100;
        guest.points = 0;
        guest.gold_reserve = 0;
        guest.weapon_num = 1;
        strcpy(guest.inventory[0] , "NO WEAPON");
        guest.experience = 1;

        char naghsheh[MAX_SIZE][MAX_SIZE];

        copy_map(row , col , naghsheh , dungeons[0].naghseh);
        int number = Random(0 , RoomNum[0] - 1);
        int y_loc;
        int x_loc;
        y_loc = spawn_py(dungeons[0].room[number]);
        x_loc = spawn_px(dungeons[0].room[number]);
        int floor = 0;
        dungeons[floor].naghseh[y_loc][x_loc] = '.';
        // naghsheh[y_loc][x_loc] = '.';
        attron(COLOR_PAIR(4));
        bkgd(COLOR_PAIR(4));
        // getch();
        init_show(dungeons[floor].show , row , col);
        showroom(dungeons[floor].room , dungeons[floor].naghseh , dungeons[floor].show , number);
        int out = 0;
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
            showcorridor(dungeons[floor].naghseh , dungeons[floor].show , x_loc , y_loc);
            print_map(row , col , dungeons[floor].naghseh , dungeons[floor].show);
            mvprintw(y_loc , x_loc , "@");
            mvprintw(0 , 0 , "your health is %d %d|" , guest.health , floor);
            mvprintw(0 , 20 , "your point is %d |" , guest.points);
            int kilid = getch();
            switch (kilid)
            {
            case KEY_UP:
                if(isfloor(dungeons[floor].naghseh[y_loc - 1][x_loc]) || iscorridor(dungeons[floor].naghseh[y_loc - 1][x_loc]) || isdoor(dungeons[floor].naghseh[y_loc - 1][x_loc]) || istrap(dungeons[floor].naghseh[y_loc - 1][x_loc]) || isfood(dungeons[floor].naghseh[y_loc - 1][x_loc]) || istair(dungeons[floor].naghseh[y_loc - 1][x_loc]))
                {
                    if(iswall(dungeons[floor].naghseh[y_loc - 1][x_loc]) || ispillar(dungeons[floor].naghseh[y_loc - 1][x_loc]) || iswindow(dungeons[floor].naghseh[y_loc - 1][x_loc]))
                    {
                        break;
                    }
                    else if(istrap(dungeons[floor].naghseh[y_loc][x_loc]))
                    {
                        if(guest.health >= 10)
                        {
                            showtraps(dungeons[0].naghseh , dungeons[0].show , x_loc , y_loc);
                            guest.health -= 10;
                        }
                        else
                            out = 2;
                    }
                    else if(dungeons[floor].naghseh[y_loc][x_loc] == 'f')
                    {
                        if(guest.health <= 90)
                        {
                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            guest.health+=10;
                        }
                    }
                    y_loc--;
                }
                break;
            case KEY_DOWN:
                if(isfloor(dungeons[floor].naghseh[y_loc + 1][x_loc]) || iscorridor(dungeons[floor].naghseh[y_loc + 1][x_loc]) || isdoor(dungeons[floor].naghseh[y_loc + 1][x_loc]) || istrap(dungeons[floor].naghseh[y_loc + 1][x_loc]) || isfood(dungeons[floor].naghseh[y_loc + 1][x_loc]) || istair(dungeons[floor].naghseh[y_loc + 1][x_loc]))
                {
                    if(dungeons[floor].naghseh[y_loc + 1][x_loc] == '-'|| dungeons[floor].naghseh[y_loc + 1][x_loc] == '0' || dungeons[floor].naghseh[y_loc + 1][x_loc] == '=')
                    {
                        break;
                    }
                    else if(istrap(dungeons[floor].naghseh[y_loc][x_loc]))
                    {
                        if(guest.health >= 10)
                        {
                            showtraps(dungeons[0].naghseh , dungeons[0].show , x_loc , y_loc);
                            guest.health -= 10;
                        }
                        else
                            out = 2;
                    }
                    else if(dungeons[floor].naghseh[y_loc][x_loc] == 'f')
                    {
                        if(guest.health <= 90)
                        {
                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            guest.health+=10;
                        }
                    }
                    y_loc++;
                }
                break;
            case KEY_LEFT:
                if(isfloor(dungeons[floor].naghseh[y_loc][x_loc - 1]) || iscorridor(dungeons[floor].naghseh[y_loc][x_loc - 1]) || isdoor(dungeons[floor].naghseh[y_loc][x_loc - 1]) || istrap(dungeons[floor].naghseh[y_loc][x_loc - 1]) || isfood(dungeons[floor].naghseh[y_loc][x_loc - 1]) || istair(dungeons[floor].naghseh[y_loc][x_loc - 1]))
                {
                    if(dungeons[floor].naghseh[y_loc][x_loc - 1] == '|'|| dungeons[floor].naghseh[y_loc][x_loc - 1] == '0' || dungeons[floor].naghseh[y_loc][x_loc - 1] == '=')
                    {
                        break;
                    }
                    else if(istrap(dungeons[floor].naghseh[y_loc][x_loc]))
                    {
                        if(guest.health >= 10)
                        {
                            showtraps(dungeons[0].naghseh , dungeons[0].show , x_loc , y_loc);
                            guest.health -= 10;
                        }
                        else
                            out = 2;
                    }
                    else if(dungeons[floor].naghseh[y_loc][x_loc] == 'f')
                    {
                        if(guest.health <= 90)
                        {
                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            guest.health+=10;
                        }
                    }
                    x_loc--;
                }
                break;
            case KEY_RIGHT:
                if(isfloor(dungeons[floor].naghseh[y_loc][x_loc + 1]) || iscorridor(dungeons[floor].naghseh[y_loc][x_loc + 1]) || isdoor(dungeons[floor].naghseh[y_loc][x_loc + 1]) || istrap(dungeons[floor].naghseh[y_loc][x_loc + 1]) || isfood(dungeons[floor].naghseh[y_loc][x_loc + 1]) || istair(dungeons[floor].naghseh[y_loc][x_loc + 1]))
                {
                    if(dungeons[floor].naghseh[y_loc][x_loc + 1] == '|'|| dungeons[floor].naghseh[y_loc][x_loc + 1] == '0' || dungeons[floor].naghseh[y_loc][x_loc + 1] == '=')
                    {
                        break;
                    }
                    else if(istrap(dungeons[floor].naghseh[y_loc][x_loc]))
                    {
                        if(guest.health >= 10)
                        {
                            showtraps(dungeons[0].naghseh , dungeons[0].show , x_loc , y_loc);
                            guest.health -= 10;
                        }
                        else
                            out = 2;
                    }
                    else if(dungeons[floor].naghseh[y_loc][x_loc] == 'f')
                    {
                        if(guest.health <= 90)
                        {
                            dungeons[floor].naghseh[y_loc][x_loc] = '.';
                            guest.health+=10;
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
                    clear();
                    print_map(row , col , dungeons[0].naghseh , dungeons[0].show);
                }
                else
                {
                    out = 1;
                }
                
                break;
            default:
                break;
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
        char setting_info[3][100] = {"music"};
        int info1_len = strlen(setting_info[0]);
        char Tracks[4][10] = {"Track 1" , "Track 2" , "Track 3" , "NO Music"};
        mvwprintw(setting_menu , 0 , col/2 - info1_len/2 , setting_info[0]);
        int highlight_s = 0;
        int decision_s;
        noecho();
        while(1){
            for(int i = 0 ; i < 4 ; i++){
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
                        highlight_s = 3;
                    }
                    break;
                case KEY_DOWN:
                    highlight_s++;
                    if(highlight_s == 4){
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
        
        // if(highlight_s == 0)
        // {
        //     if(music_1 == NULL)
        //     {
        //         music_1 = Mix_LoadMUS(track_1);
        //         Mix_PlayMusic(music_1 , -1);
        //     }
        //     else
        //     {
        //         Mix_HaltMusic();
        //         Mix_FreeMusic(music_1);
        //         music_1 = NULL;
        //         Mix_CloseAudio();
        //         music_1 = Mix_LoadMUS(track_1);
        //         Mix_PlayMusic(music_1 , -1);
        //     }
        // }
        // if(highlight_s == 1)
        // {
        //     if(music_1 == NULL)
        //     {
        //         music_1 = Mix_LoadMUS(track_2);
        //         Mix_PlayMusic(music_1 , -1);
        //     }
        //     else
        //     {
        //         Mix_HaltMusic();
        //         Mix_FreeMusic(music_1);
        //         music_1 = NULL;
        //         Mix_CloseAudio();
        //         music_1 = Mix_LoadMUS(track_2);
        //         Mix_PlayMusic(music_1 , -1);
        //     }
        // }
        // if(highlight_s == 2)
        // {
        //     if(music_1 == NULL)
        //     {
        //         music_1 = Mix_LoadMUS(track_3);
        //         Mix_PlayMusic(music_1 , -1);
        //     }
        //     else
        //     {
        //         Mix_HaltMusic();
        //         Mix_FreeMusic(music_1);
        //         music_1 = NULL;
        //         Mix_CloseAudio();
        //         music_1 = Mix_LoadMUS(track_3);
        //         Mix_PlayMusic(music_1 , -1);
        //     }
        // }
        // if(highlight_s == 3)
        // {
        //     if(music_1 != NULL)
        //     {
        //         Mix_HaltMusic();
        //         Mix_FreeMusic(music_1);
        //         music_1 = NULL;
        //         Mix_CloseAudio();
        //     }
        // }
    }
    else if(highlight == 4)
    {}
    // getchar();
    // SDL_Quit();
    endwin();
    return 0;
}