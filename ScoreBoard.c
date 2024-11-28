#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <direct.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <windows.h>

int changed = 1;
int match = 0, finished = 0;

int runs = 0;
int wickets = 0;
int overs = 0;
int balls = 0;
char ball_array[20][5];
int over_index = 0;
char last_ball[5] = "", team1[5] = "", team2[5] = "", batting[5] = "";
char bat1[20] = "", bat2[20] = "", bowler[20] = "";
char winner[5] = "";
int run1 = 4, run2 = 1;
int innings = 1;
int target = 0;
int strike = 0;
float rr = 0;

bool windows = true;



//Checks the operating system
void opChecker(){
#ifdef _WIN32
    windows = true;
#else
    windows = false;
#endif
}



//Clears the over 
void clear_over(){
    for(int i=0; i<=over_index; i++){
        strcpy(ball_array[i],"");
    }
    over_index = 0;
}



// Clears the screen 
void clear_screen(){
    windows ? system("cls") : system("clear");
}



// Returns current directory path
char* curdir(){
    static char cwd[1024];
    
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        return cwd;
    } else {
        perror("getcwd() error");
        return "Error";
    }
}



// Retrive data from the text and save in the variables
int reader(char* text){
    char data[20][20];
    char temp[20] = "";
    int c = 0;
    int temp_idx = 0;

    
    int size = strlen(text);

    for(int i=0; i<size; i++){
        if(text[i] == ','){
            temp[temp_idx] = '\0';
            strcpy(data[c], temp);
            c++;
            temp_idx = 0;
        }
        else{
            temp[temp_idx++] = text[i];
        }
    }


    if(strcmp(data[0], team1) == 0 && strcmp(data[1], team2) == 0 && strcmp(data[2], batting) == 0 &&
        atoi(data[3]) == runs && atoi(data[4]) == wickets && atoi(data[5]) == overs && 
        atoi(data[6]) == balls && strcmp(data[7], last_ball) == 0 && strcmp(data[8], bat1) == 0
        && atoi(data[9]) == run1 && strcmp(data[10], bat2) == 0 && atoi(data[11]) == run2 &&
        atoi(data[12]) == strike && strcmp(bowler, data[13]) == 0 && atoi(data[14]) == innings 
        && atoi(data[15]) == target && match == atoi(data[16]) && finished == atoi(data[17]) && strcmp(winner, data[18]) == 0){
        return 0;
    }


    else{
        
        strcpy(team1, data[0]);
        strcpy(team2, data[1]);
        strcpy(batting,data[2]);
        runs = atoi(data[3]);
        wickets = atoi(data[4]);
        overs = atoi(data[5]);
        balls = atoi(data[6]);
        strcpy(last_ball, data[7]);
        strcpy(bat1, data[8]);
        run1 = atoi(data[9]);
        strcpy(bat2, data[10]);
        run2 = atoi(data[11]);
        strike = atoi(data[12]);
        strcpy(bowler, data[13]);
        innings = atoi(data[14]);
        target = atoi(data[15]);
        match = atoi(data[16]);
        finished = atoi(data[17]);
        strcpy(winner,data[18]);

        return 1;
    }
}



// Reads the database text file and retrive data 
void GetInfo(char* path){
    FILE *file = fopen(path,"r");
    char content[100];

    fgets(content, sizeof(content), file);
    
    if (content == NULL) {
        perror("Memory error");
        fclose(file);
    }

    else{

        changed = reader(content);
        fclose(file);
    }

}



//Prints output to consol
void ScoreBoard(){
    int width = 60, height = 15;
    int idx = 0;

    for(int i=1; i<=height; i++){
        if(i%2!=0 && i!=7){
            for(int j=1; j<=width; j++){
                printf("-");
            }
        }
        else{
            for(int j=1; j<=width; j++){
                if(j==1 || j==width){
                    printf("|");
                }
                else{
                    if(i==2){
                        int t = ceil(width*.4);
                        if(j==t){
                            printf("%s  vs  %s",team1,team2);
                            j+=11;
                        }
                        else{
                            printf(" ");
                        }
                    }
                    
                    else if(i==4){
                        if(j==ceil(width*.15)){
                            innings == 1?
                            printf("1st Innings"):
                            printf("2nd Innings");
                            j+=10;
                        }
                        
                        else if(j==width/2){
                            printf("|");
                        }
                        
                        else if(innings==2 && j==width*.6){
                            printf("Target:    %d",target);
                            char tmp[5];
                            sprintf(tmp, "%d", target);
                            int s = strlen(tmp) + 10;
                            j+=s;
                        }
                        
                        else
                        printf(" ");
                    }
                    
                    else if(i==6){
                        if(j==ceil(width*.2)){
                            printf("%s",batting);
                            j+=2;
                        }
                        
                        else if(j==width/2){
                            printf("|");
                        }
                        else{
                            j>width/2?
                            printf(" "):
                            printf("_");
                        }
                    }
                    
                    else if(i==7){
                        if(j==ceil(width*.1)){
                            char tmp[5];
                            sprintf(tmp, "%d", runs);
                            printf("Runs:  %d",runs);
                            int s = 6 + strlen(tmp);
                            j+=s;
                        }
                        
                        else if(j==width/2){
                            printf("|");
                        }
                        
                        else if(j==width*.6){
                            printf("Run Rate:    %.1f",rr);
                            char tmp[5];
                            sprintf(tmp, "%.1f", rr);
                            
                            int s = strlen(tmp) + 12;
                            j+=s;
                        }
                        
                        else
                        printf(" ");
                    }
                    
                    else if(i==8){
                        if(j==ceil(width*.1)){
                            char tmp[5];
                            sprintf(tmp, "%d", wickets);
                            printf("Wickets:  %d",wickets);
                            int s = 9 + strlen(tmp);
                            j+=s;
                        }
                        
                        else if(j==width/2){
                            printf("|");
                        }
                        else
                        printf(" ");
                    }
                    
                    else if(i==10){
                        if(j==ceil(width*.15)){
                            char tmp[5];int x=4;
                            sprintf(tmp, "%d", run1);
                            if(!strike){
                                printf("*");
                                x=5;
                            }
                            printf("%s  -  %d",bat1,run1);
                            int s = x + strlen(bat1) + strlen(tmp);
                            j+=s;
                        }
                        
                        else if(j==width/2){
                            printf("|");
                        }
                        
                        else if(j==width*.65){
                            char tmp[5];int x=4;
                            sprintf(tmp, "%d", run2);
                            if(strike){
                                printf("*");
                                x=5;
                            }
                            printf("%s  -  %d",bat2,run2);
                            int s = x + strlen(bat2) + strlen(tmp);
                            j+=s;
                        }
                        
                        else
                        printf(" ");
                    }
                    
                    else if(i==12){
                        if(j==ceil(width*.15)){
                            char tmp[5];
                            sprintf(tmp, "%d", overs);
                            printf("Overs :  %d.%d",overs, balls);
                            int s = 10 + strlen(tmp);
                            j+=s;
                        }
                        
                        else if(j==width/2){
                            printf("|");
                        }
                        
                        else if(j==width*.6){
                            printf("Bowler :  %s",bowler);
                            int s = 9 + strlen(bowler);
                            j+=s;
                        }
                        
                        else
                        printf(" ");
                    }
                    
                    else if(i==14){
                        if(j==ceil(width*.07)){
                            printf("%s",last_ball);
                            int s = strlen(last_ball)-1;
                            j+=s;
                        }
                        
                        else if(j == width*.15){
                            printf("|");
                        }
                        
                        else if(j > width*.2 && j<width ){
                            if(idx<over_index){
                                printf(" %s ",ball_array[idx++]);
                                j+=strlen(ball_array[idx-1])+1;
                            }

                            else
                                printf(" ");
                        }
                        else
                        printf(" ");
                    }
                    
                    else{
                        printf(" ");
                    }
                }
            }
        }
        printf("\n");
    }
}



int main(){
    opChecker();
    struct stat buffer;
    char* db_dir = curdir();
    char db_path[50];
    windows ? strcpy(db_path,"\\Database\\matchInfo.txt") : strcpy(db_path,"/Database/matchInfo.txt");
    strcat(db_dir,db_path);
    
    bool db_found = stat(db_dir, &buffer) == 0;

    if(db_found){
        while(1){
            GetInfo(db_dir);

            if(changed){
                clear_screen();

                if(runs!=0 || overs!=0 || balls!=0){
                    rr = runs!=0 && overs==0 && balls==0?
                    runs : 
                    runs*1.0/(overs + balls*1.0/6);
                }

                if(balls==1){
                    clear_over();
                }
                strcpy(ball_array[over_index++],last_ball);

                if(match)
                    ScoreBoard();
                else if(finished)
                    strcmp(winner,"Draw") != 0 ? printf("________%s Won The Match________", winner) : printf("________Match Draw________");
                else
                    printf("No Match Started Yet");
                changed = 0;
            }
        }

    }

    else{
        perror("Databases Error");
    }


}