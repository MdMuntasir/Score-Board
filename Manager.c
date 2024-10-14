#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <direct.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <windows.h>

int changed = 1;
bool error = false;
int match = 0;
int finished = 0;
int freehit = 0;
int saved = 1;

int runs = 0;
int wickets = 0;
int overs = 0, total_over=0;
int balls = 0;
char last_ball[5] = " ", team1[5] = "BAN", team2[5] = "IND", batting[5] = "BAN";
char bat1[20] = "Tamim", bat2[20] = "Liton", bowler[20] = "Bumrah";
char winner[5]="";
int run1 = 0, run2 = 0;
int innings = 1;
int target = 0;
int strike = 0;

int screen = 0;
char error_mssg[100] = "";
char db_path[100] = "";


bool windows = true;



//Checks the operating system
void opChecker(){
#ifdef _WIN32
    windows = true;
#else
    windows = false;
#endif
}




// Resets all variables
void reset(){
    runs = 0;
    wickets = 0;
    overs = 0;
    balls = 0;
    strike = 0;
    run1 = 0;
    run2 = 0;
    strcmp(batting,team1) == 0? strcpy(batting,team2) : strcpy(batting,team1);
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


void strUpper(char* str){
    for(int i=0; i<sizeof(str); i++){
        str[i] = toupper(str[i]);
    }
}


// Reads text from a file
char* fileReader(char* path){
    FILE *file = fopen(path,"r");
    char *content = (char *)malloc(20 * sizeof(char));
    fgets(content,20,file);
    fclose(file);
    return content;
}



// Returns the formated string from variable
char* TextFormat(){
    char *text = (char*)malloc(100 * sizeof(char));
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
    sprintf(tmp, "%d", finished);strcat(text,tmp);strcat(text,",");
    strcat(text,winner);strcat(text,",");

    return text;
}



// Saves the text into a file
void SaveFile(char* path, char* text){
    FILE *file = fopen(path, "w");

    if (file == NULL) {
        printf("File null");
        perror("Error opening file");
        saved = 0;
        return;
    }

    puts(text);

    fprintf(file,"%s",text);
    
    fclose(file);

}


// Get password input in an obsecure form
void getPassword(char* txt,char* password, int max_length) {
    int i = 0;
    char ch;

    printf("%s",txt);
    while (i < max_length - 1) { 
        ch = getch();
        if(ch == '\r')
            break;
        password[i++] = ch;
        // printf("*"); 
    }
    password[i] = '\0'; 
    printf("\n");
}


// Check if the score is valid
int validBallChecker(char *ball){
    if(strcmp(ball,"0") == 0 || strcmp(ball,"1") == 0 || strcmp(ball,"2") == 0 || strcmp(ball,"3") == 0 || strcmp(ball,"4") == 0 ||
    strcmp(ball,"5") == 0 || strcmp(ball,"6") == 0 || strcmp(ball,"N") == 0 || strcmp(ball,"N1") == 0 ||
    strcmp(ball,"N2") == 0 || strcmp(ball,"N3") == 0 || strcmp(ball,"N4") == 0 || strcmp(ball,"N5") == 0 ||
    strcmp(ball,"N6") == 0 || strcmp(ball,"Wd") == 0 || strcmp(ball,"Wd1") == 0 || strcmp(ball,"Wd2") == 0 ||
    strcmp(ball,"Wd3") == 0 || strcmp(ball,"Wd4") == 0 || strcmp(ball,"Lb1") == 0 || strcmp(ball,"Lb2") == 0 ||
    strcmp(ball,"Lb3") == 0 || strcmp(ball,"Lb4") == 0 || strcmp(ball,"RO") == 0 || strcmp(ball,"CO") == 0 ||
    strcmp(ball,"BO") == 0 || strcmp(ball,"OUT") == 0 || strcmp(ball,"LBW") == 0 )
    return 1;
    

    else
    return 0;
}


// Returns catagory of the score
char* scoreCategoryChecker(char* ball){
    if(strcmp(ball,"0") == 0 || strcmp(ball,"1") == 0 || strcmp(ball,"2") == 0 || strcmp(ball,"3") == 0 || 
    strcmp(ball,"4") == 0 || strcmp(ball,"5") == 0 || strcmp(ball,"6") == 0)
    return "R";

    else if(strcmp(ball,"RO") == 0 || strcmp(ball,"CO") == 0 ||strcmp(ball,"BO") == 0 
    || strcmp(ball,"OUT") == 0 || strcmp(ball,"LBW") == 0 )
    return "W";

    else if(strcmp(ball,"N") == 0 || strcmp(ball,"N1") == 0 ||strcmp(ball,"N2") == 0 || strcmp(ball,"N3") == 0 || 
    strcmp(ball,"N4") == 0 || strcmp(ball,"N5") == 0 || strcmp(ball,"N6") == 0 || 
    strcmp(ball,"Wd") == 0 || strcmp(ball,"Wd1") == 0 || strcmp(ball,"Wd2") == 0 || 
    strcmp(ball,"Wd3") == 0 || strcmp(ball,"Wd4") == 0 || strcmp(ball,"Lb1") == 0 || 
    strcmp(ball,"Lb2") == 0 || strcmp(ball,"Lb3") == 0 || strcmp(ball,"Lb4") == 0)
    return "E";

    else
    return "X";
}



void homeScreen(){
    
    int option;

    printf("Please log in to continue. \n1. Log In\n2. Register\nChoose an option: \n");
    scanf("%d",&option);
    if(error){
        printf("%s\n",error_mssg); error = !error;
    }

    if(option != 1 && option != 2){
        error = true;
        strcpy(error_mssg,"Choosed wrong option");
    }

    else {
        screen = option;
    }

    changed = 1;
    
}



void logScreen(){
    struct stat buffer;
    char username[50] = "dummy", password[50];

    if(error){
        int option;
        printf("%s\n",error_mssg); error = !error;
        printf("1. Go to homepage\n2. Continue to login\n");
        scanf("%d",&option);
        if(option-1){
            changed = 1;
        }
        else{
            screen = 0;
            changed = 1;
        }

    }

    else{
        printf("Log In\nEnter Username: ");getchar();
        fgets(username, 50, stdin);
        username[strlen(username)-1] = '\0';


        getPassword("Enter password: ",password,15);

        strcat(username,".txt");
        char* user = curdir();
        char file_dir[50];
        windows ? strcpy(file_dir,"\\Database\\Auth_Credential\\") : strcpy(file_dir,"/Database/Auth_Credential/");
        strcat(user,file_dir);strcat(user,username);

        bool user_found = stat(user, &buffer) == 0;

        if(user_found){
            char* pass = fileReader(user);
            if(strcmp(pass,password) == 0){
                strcpy(error_mssg,"Successfully logged in!!!");
                error = true;
                screen = 3;
            }
            else{
                strcpy(error_mssg,"Wrong Password");
                error = true;
            }
        }
        else{
            strcpy(error_mssg,"User not registered");
            error = true;
        }
    }
    changed = 1;
}




void regScreen(){
    struct stat buffer;
    char username[50]="", password[50], confirm_password[50];

    if(error){
        int option;
        printf("%s\n",error_mssg); error = !error;
        printf("1. Go to homepage\n2. Continue to Register\n");
        scanf("%d",&option);
        if(option-1){
            changed = 1;
        }
        else{
            screen = 0;
            changed = 1;
        }
    }

    else{

        printf("Sign Up\nEnter Username: "); getchar();
        fgets(username, 50, stdin);
        username[strlen(username)-1] = '\0';

        getPassword("Enter password: ",password,15);
        getPassword("Confirm password: ",confirm_password,15);


        strcat(username,".txt");
        char* user = curdir();
        char file_dir[50];
        windows ? strcpy(file_dir,"\\Database\\Auth_Credential\\") : strcpy(file_dir,"/Database/Auth_Credential/");
        strcat(user,file_dir);strcat(user,username);

        bool user_found = stat(user, &buffer) == 0;

        if(strcmp(confirm_password,password) != 0){
            strcpy(error_mssg,"Password didn't match"); error = true;
        }
        else if(strlen(password)<8 ){
            strcpy(error_mssg,"Weak password!. Password must contain at least 8 characters."); error = true;
        }
        else if(user_found){
            strcpy(error_mssg,"Username already exists. Try login or use different username."); error = true;
        }
        else{
            puts(user);
            FILE *file = fopen(user,"w");
            if(file == NULL)perror("Error opening: ");
            fprintf(file, "%s" ,password);
            fclose(file);
            strcpy(error_mssg,"Successfully created account. Now log in to your account."); error = true;
            screen = 1;
        }
    }
    changed = 1;
}



void setMatchScreen(){
    int  option;
    if(error){
        printf("%s\n",error_mssg); error = !error;
    }
    printf("Provide match information\nInsert name of teams in short form(ex: BAN , IND):\n");

    printf("Team 1: ");
    fgets(team1,5,stdin); 
    team1[strcspn(team1, "\n")] = '\0'; 

    printf("Team 2: ");
    fgets(team2,5,stdin); 
    team2[strcspn(team2, "\n")] = '\0'; 

    strUpper(team1); strUpper(team2);

    printf("Which team will bat first?\n1. %s\n2. %s\n",team1,team2);
    scanf("%d", &option); getchar();
    option-1 ? strcpy(batting,team2) : strcpy(batting,team1);
    

    printf("Total overs in one innings: ");
    scanf("%d",&total_over); getchar();

    printf("Enter 1st Batsman NickName: ");
    fgets(bat1,20,stdin); 
    bat1[strcspn(bat1, "\n")] = '\0';

    printf("Enter 2nd Batsman NickName: ");
    fgets(bat2,20,stdin); 
    bat2[strcspn(bat2, "\n")] = '\0';
    
    printf("Enter Bowler NickName: ");
    fgets(bowler,20,stdin); 
    bowler[strcspn(bowler, "\n")] = '\0'; 



    


    printf("\n%s vs %s\n%d Overs per Innings\nBatting: %s\nBatsman 1: %s\nBatsman 2: %s\nBowler : %s\n",team1,team2,total_over,batting,bat1,bat2,bowler);
    printf("Is the inforamtion correct?\n1. YES\n2. NO\n");
    scanf("%d",&option); getchar();

    if(!(option-1)){
        strcpy(error_mssg,"\tMatch Started");
        match = 1;
        screen = 4;
    }

    changed = 1;


}




void runningMatchScreen(){
    char score[5];

    if(error){
        printf("%s\n\n",error_mssg); error = !error;
    }

    innings-1 ? printf("2nd Innings Running\n") : printf("1st Innings Running\n");

    printf("Enter score in proper format for every ball. Proper score formats are,\n");
    printf("Runs: 0,1,2,3,4,5,6\n");
    printf("Wickets: RO,LBW,BO,CO,OUT\n");
    printf("Extras: N,N1,N2,N3,N4,N5,N6,\n        Wd,Wd1,Wd2,Wd3,Wd4,\n        Lb1,Lb2,Lb3,Lb4\n\n");
    printf("Enter score in this ball: ");
    fgets(score,5,stdin);
    score[strcspn(score,"\n")] = '\0';
    
    if(strlen(score) == 0){
        strcpy(error_mssg,"Wrong Input"); error = true;
    }

    else{
        score[0] = toupper(score[0]);
        int valid = validBallChecker(score);
        if(valid){
            balls++;
            char* category = scoreCategoryChecker(score);
            
            if(strcmp(category,"R") == 0){
                strcpy(last_ball,score);
                int scr = atoi(score);
                runs+=scr;
                if(strike)run2+=scr ; 
                else run1+=scr;

                if(scr % 2 != 0){
                    strike = !strike;
                }
                
                freehit = 0;
            }

            else if(strcmp(category,"W") == 0){
                if(!freehit){
                    wickets ++;
                    if(wickets < 10)
                    {
                        int opt;
                        printf("Wich batsman got out?\n1. %s\n2. %s\n",bat1,bat2);
                        scanf("%d",&opt); getchar();

                        printf("Enter new batsman nickname: ");
                        if(opt-1){
                            fgets(bat2,20,stdin);
                            bat2[strcspn(bat2, "\n")] = '\0';
                            run2 = 0;
                        }
                        else{
                            fgets(bat1,20,stdin);
                            bat1[strcspn(bat1, "\n")] = '\0';
                            run1 = 0;
                        }
                    }
                    else{
                        if(innings==1){
                            innings = 2;
                            target = runs+1;

                            printf("1st innings is over. Enter information for 2nd innings\n\n");

                            printf("Enter 1st Batsman NickName: ");
                            fgets(bat1,20,stdin); 
                            bat1[strcspn(bat1, "\n")] = '\0';

                            printf("Enter 2nd Batsman NickName: ");
                            fgets(bat2,20,stdin); 
                            bat2[strcspn(bat2, "\n")] = '\0';
                            
                            printf("Enter Bowler NickName: ");
                            fgets(bowler,20,stdin); 
                            bowler[strcspn(bowler, "\n")] = '\0'; 


                            reset();
                        }

                        else{
                            match = 0;
                            finished = 1;
                            if(runs < target-1){
                                strcmp(batting,team1) == 0 ? strcpy(winner,team2) : strcpy(winner,team1);
                            }
                            else{
                                strcpy(winner,"Draw");
                            }
                            
                            reset();
                            screen = 3;
                        }
                    }
                }
                else
                    freehit = 0;
                strcpy(last_ball,"W");
            }

            else if(strcmp(category,"E") == 0){
                if(score[0] == 'L'){
                    runs += atoi(&score[strlen(score)-1]);
                    freehit = 0;
                }
                else{
                    balls--;
                    runs++;
                    if(score[strlen(score)-1] != 'd' && score[strlen(score)-1] != 'N'){
                        runs += atoi(&score[strlen(score)-1]);
                        if(score[0]=='N') {
                            if(strike)
                                run2 += atoi(&score[strlen(score)-1]);
                            else
                                run1 += atoi(&score[strlen(score)-1]);
                        }
                    }
                    if(score[0]=='N'){
                        freehit = 1; 
                    }
                }

                strcpy(last_ball,score);
            }
            else{
                strcpy(error_mssg , "Wrong Input"); error = true;
                balls--;
            }


            if(innings == 2 && runs>target){
                match = 0;
                finished = 1;

                strcmp(batting,team2) == 0 ? strcpy(winner,team2) : strcpy(winner,team1);

                reset();
                screen = 3;
            }


            if(balls==6){
                overs++; balls = 0;
                if(overs == total_over){
                    if(innings==1){
                        innings = 2;
                        target = runs+1;

                        printf("1st innings is over. Enter information for 2nd innings\n\n");

                        printf("Enter 1st Batsman NickName: ");
                        fgets(bat1,20,stdin); 
                        bat1[strcspn(bat1, "\n")] = '\0';

                        printf("Enter 2nd Batsman NickName: ");
                        fgets(bat2,20,stdin); 
                        bat2[strcspn(bat2, "\n")] = '\0';
                        
                        printf("Enter Bowler NickName: ");
                        fgets(bowler,20,stdin); 
                        bowler[strcspn(bowler, "\n")] = '\0'; 


                        reset();
                    }

                    else{
                        match = 0;
                        finished = 1;
                        if(runs < target-1){
                            strcmp(batting,team1) == 0 ? strcpy(winner,team2) : strcpy(winner,team1);
                        }
                        else if(runs > target-1){
                            strcmp(batting,team2) == 0 ? strcpy(winner,team2) : strcpy(winner,team1);
                        }
                        else{
                            strcpy(winner,"Draw");
                        }
                        reset();

                        screen = 3;
                    }
                }
                else{
                    printf("For new over enter bowler's nickname: ");
                    fgets(bowler,20,stdin); 
                    bowler[strcspn(bowler, "\n")] = '\0'; 
                }
            }
            
        }

        else{
            strcpy(error_mssg,"Wrong Input"); error = true;
        }
    }
    

    SaveFile(db_path,TextFormat());
    changed = 1;
}




int main(){

    char* dir = curdir();
    char filepath[50];
    windows ? strcpy(filepath,"\\Database\\matchInfo.txt") : strcpy(filepath,"/Database/matchInfo.txt");
    strcat(dir,filepath);
    strcpy(db_path,dir);


    while(1){
        if(!saved){
            SaveFile(db_path,TextFormat());
        }
        
        if(saved && changed){
            changed = 0;
            clear_screen();

            switch(screen){
                case(0):
                homeScreen();
                break;

                case(1):
                logScreen();
                break;

                case(2):
                regScreen();
                break;

                case(3):
                setMatchScreen();
                break;

                case(4):
                runningMatchScreen();
                break;

                default:
                homeScreen();
                break;
            }

        }
    }
    
}