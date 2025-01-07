#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_SIZE 400
char naghsheh[MAX_SIZE][MAX_SIZE];


typedef struct prof{
    char name[MAX_SIZE];
    char password[MAX_SIZE];
    char e_mail[MAX_SIZE];
    int points;
    int gold_reserve;
    int experience;
}profile;



struct location
{
    int x;
    int y;
};






void SeedRand()
{
    srand(time(NULL));
}



int Random(int min , int max)
{
    int diff = max - min;
    return rand() % diff + min;
}





int is_char(char a){
    if((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z')){
        return 1;
    }
    return 0;
}



void welcome_to_the_rouge(){
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



void generate_map(int row , int col)
{
    int RoomNum = Random(3 , 9);
    for (int i = 0; i < row; i++)
    {
        for(int j = 0 ; j < col ; j++)
        {
            naghsheh[i][j] = ' ';
        }
    }


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
            int door_count = 0;
            int pillar_count = 0;
            for(int i_1 = x ; i_1 < x + room_width ; i_1++)
            {
                for(int j = y ; j < y + room_hight ; j++)
                {
                    if(i_1 == x && j == y || i_1 == x + room_width - 1 && j == y || i_1 == x && j == y + room_hight - 1 || i_1 == x + room_width - 1 && j == y + room_hight - 1)
                    {
                        naghsheh[j][i_1] = ' ';
                    }
                    else if(i_1 == x || i_1 == x + room_width - 1)
                    {
                        int door = Random(0,x+room_width-1);
                        int window = Random(0,100);
                        if(door > (50) * (x+room_width-1) / 100 && door_count < 2 && j <= y + room_hight - 3 || (i_1 == x + room_width - 3 && j == y + room_hight - 3 && door_count == 0))
                        {
                            door_count++;
                            naghsheh[j][i_1] = '+';
                        }
                        else if(window > 80 && j <= y + room_hight - 3 )
                        {
                            naghsheh[j][i_1] = '=';
                        }
                        else
                        {
                            naghsheh[j][i_1] = '|';
                        }
                    }
                    else if(j == y || j == y + room_hight - 1)
                    {
                        int door = Random(0,x+room_width-1);
                        int window = Random(0,100);
                        if(door > (50) * (x+room_width-1) / 100 && door_count < 2 && j <= y + room_hight - 3 || (i_1 == x + room_width - 3 && j == y + room_hight - 3 && door_count == 0))
                        {
                            door_count++;
                            naghsheh[j][i_1] = '+';
                        }
                        else if(window > 80 && j <= y + room_hight - 3 )
                        {
                            naghsheh[j][i_1] = '=';
                        }
                        else
                        {
                            naghsheh[j][i_1] = '-';
                        }
                    }
                    else
                    {
                        int pilar = Random(0,2);
                        if(pilar && pillar_count < 4 && j > y + 1 && j < room_hight + y - 1 && i_1 > x + 1 && i_1 < x + room_width - 1)
                        {
                            pillar_count++;
                            naghsheh[j][i_1] = '0';
                        }
                        else
                        {
                            naghsheh[j][i_1] = '.';

                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            mvaddch(j , i , naghsheh[j][i]);
        }
        
    }
    

}


void print_map(int row , int col , char naghsheh[row][col])
{
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            mvaddch(j , i , naghsheh[j][i]);
        }
        
    }
}


void game(){}


int main(){

    initscr();


    SeedRand();
    if(has_colors())
    {
        start_color();
    }


    
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

    }
    else if(highlight == 2)
    {
        noecho();
        keypad(stdscr , TRUE);
        clear();
        bkgd(' ');
        generate_map(row , col);
        // generate_corridor();
        spawn_p();
        int y_loc = row / 2;
        int x_loc = col/ 2;
        while(1)
        {
            refresh();
            mvprintw(y_loc , x_loc , "o");
            int kilid = getch();
            switch (kilid)
            {
            case KEY_UP:
                if(naghsheh[y_loc][x_loc] == '.')
                {
                    if(naghsheh[y_loc - 1][x_loc] == '-'|| naghsheh[y_loc - 1][x_loc] == '0')
                    {
                        break;
                    }
                    else
                    {
                        mvprintw(y_loc , x_loc , ".");
                        y_loc--;
                    }
                }
                break;
            case KEY_DOWN:
                if(naghsheh[y_loc][x_loc] == '.')
                {
                    if(naghsheh[y_loc + 1][x_loc] == '-'|| naghsheh[y_loc + 1][x_loc] == '0')
                    {
                        break;
                    }
                    else
                    {
                        mvprintw(y_loc , x_loc , ".");
                        y_loc++;
                    }
                }
                break;
            case KEY_LEFT:
                if(naghsheh[y_loc][x_loc - 1] == '.')
                {
                    if(naghsheh[y_loc][x_loc - 1] == '|'|| naghsheh[y_loc][x_loc - 1] == '0')
                    {
                        break;
                    }
                    else
                    {
                        mvprintw(y_loc , x_loc , ".");
                        x_loc--;
                    }
                }
                break;
            case KEY_RIGHT:
                if(naghsheh[y_loc][x_loc + 1] == '.')
                {
                    if(naghsheh[y_loc][x_loc + 1] == '|'|| naghsheh[y_loc][x_loc+1] == '0')
                    {
                        break;
                    }
                    else
                    {
                        mvprintw(y_loc , x_loc , ".");
                        x_loc++;
                    }
                }
                break;
            default:
                break;
            }
            
        }
        getch();
        // wgetch(game_win);
        //wall "| & _"
        //floor "."
        //door "+"
        //corridor "#"
        //pillar "O"
        //window "="

    }
    else if(highlight == 3)
    {

    }
    else if(highlight == 4)
    {}


    
    endwin();
    return 0;
}