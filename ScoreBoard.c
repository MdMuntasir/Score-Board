#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <direct.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int changed = 1;
int runs = 0;
int wickets = 0;
int overs = 0;
int balls = 0;
char last_ball[5] = "", team1[4] = "", team2[5] = "", batting[5] = "";




void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}




char* curdir(){
    static char cwd[1024];
    
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        return cwd;
    } else {
        perror("getcwd() error");
        return "Error";
    }
}




int reader(char* text){
    char data[8][5];
    char temp[5] = "";
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
        atoi(data[6]) == balls && strcmp(data[7], last_ball) == 0){
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

        return 1;
    }
}




void GetInfo(char* path){
    FILE *file;
    char* content;

    file = fopen(path,"r");
    
    fseek(file, 0, SEEK_END);
    
    long file_size = ftell(file);
    
    rewind(file);

    content = (char *)malloc(sizeof(char) * (file_size + 1));  
    
    if (content == NULL) {
        perror("Memory error");
        fclose(file);
    }

    fread(content, sizeof(char), file_size, file);

    content[file_size] = '\0';


    changed = reader(content);
    fclose(file);
    free(content);
}


int main(){
    struct stat buffer;
    char* db_dir = curdir();
    char db_path[] = "\\Database\\matchInfo.txt";
    strcat(db_dir,db_path);
    
    bool db_found = stat(db_dir, &buffer) == 0;

    if(db_found){
        while(1){
            GetInfo(db_dir);
            if(changed){
                clear_screen();
                printf("Team1: %s\nTeam2: %s\nBatting: %s\nRuns: %d\nWickets: %d\n%d over %d balls\nCurrent ball: %s\n",
                    team1, team2, batting, runs, wickets, overs, balls, last_ball);
                changed = 0;
            }
        }

    }

    else{
        perror("Databases Error");
    }


}