#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


int match = 0;
int runs = 0;
int wickets = 0;
int overs = 0;
int balls = 0;
char last_ball[5] = "", team1[5] = "", team2[5] = "", batting[5] = "";
char bat1[20] = "", bat2[20] = "", bowler[20] = "";
int run1 = 4, run2 = 1;
int innings = 1;
int target = 0;
int strike = 0;



char* TextFormat(){
    char *text = (char*)malloc(50 * sizeof(char));
    char tmp[20];
    strcpy(text,team1);strcat(text,",");
    strcat(text,team2); strcat(text,",");
    strcat(text,batting);strcat(text,",");
    sprintf(tmp, "%d", runs);strcat(text,tmp);strcat(text,",");
    sprintf(tmp, "%d", wickets);strcat(text,tmp);strcat(text,",");
    sprintf(tmp, "%d", overs);strcat(text,tmp);strcat(text,",");
    sprintf(tmp, "%d", balls);strcat(text,tmp);strcat(text,",");
    strcat(text,last_ball);strcat(text,",");
    strcat(text,bat1);strcat(text,",");
    sprintf(tmp, "%d", run1);strcat(text,tmp);strcat(text,",");
    strcat(text,bat2);strcat(text,",");
    sprintf(tmp, "%d", run2);strcat(text,tmp);strcat(text,",");
    sprintf(tmp, "%d", strike);strcat(text,tmp);strcat(text,",");
    strcat(text,bowler);strcat(text,",");
    sprintf(tmp, "%d", innings);strcat(text,tmp);strcat(text,",");
    sprintf(tmp, "%d", target);strcat(text,tmp);strcat(text,",");
    sprintf(tmp, "%d", match);strcat(text,tmp);strcat(text,",");
    printf("%s",text);
    return text;
}



int main(){
    char mssg[50];
    
    puts(TextFormat());
}