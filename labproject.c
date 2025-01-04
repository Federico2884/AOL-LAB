#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define BOARD 100
#define MAX_NAME 50
#define SCORE_FILE "player_scores.txt"

// Structure for player data
typedef struct {
    char name[MAX_NAME];
    int position;
    int wins;
    int gamesPlayed;
} Player;

// Function declarations
void welcome();
int die();
bool winner(int position);
void playerturn(Player *player);
int snakeladder(int position, const char *playerName);
void initializePlayer(Player *player, const char *name);
void saveScore(Player *player);
void loadScore(Player *player);
void displayScoreboard();

int main() {
    welcome();
    
    printf("\n\tPress \"s\" to start\n");
    printf("\tPress \"l\" to leave\n");
    printf("\tPress \"v\" to view scoreboard\n\n");
    
    int ch;
    char opt = '\0';
    do {
        if (kbhit()) {
            ch = getch();
            opt = (char)ch;
        }
    } while (opt != 's' && opt != 'S' && opt != 'l' && opt != 'L' && opt != 'v' && opt != 'V');
    
    switch (opt) {
        case 'v':
        case 'V':
            displayScoreboard();
            break;
            
        case 's':
        case 'S': {
            srand((unsigned int)time(NULL));
            bool gameon = true;
            
            // Initialize players
            Player player1, player2;
            
            printf("Enter name for Player 1: ");
            scanf("%s", player1.name);
            printf("Enter name for Player 2: ");
            scanf("%s", player2.name);
            getchar(); // Clear buffer
            
            initializePlayer(&player1, player1.name);
            initializePlayer(&player2, player2.name);
            
            // Load existing scores
            loadScore(&player1);
            loadScore(&player2);
            
            printf("Open the image in the directory while playing for better experience\n\n");
            
            while(gameon) {
                playerturn(&player1);
                if (winner(player1.position)) {
                    printf("%s wins!\n", player1.name);
                    player1.wins++;
                    player1.gamesPlayed++;
                    player2.gamesPlayed++;
                    saveScore(&player1);
                    saveScore(&player2);
                    printf("Scores saved!\n");
                    gameon = false;
                    break;
                }
                
                playerturn(&player2);
                if (winner(player2.position)) {
                    printf("%s wins!\n", player2.name);
                    player2.wins++;
                    player1.gamesPlayed++;
                    player2.gamesPlayed++;
                    saveScore(&player1);
                    saveScore(&player2);
                    printf("Scores saved!\n");
                    gameon = false;
                    break;
                }
            }
            break;
        }
        case 'l':
        case 'L':
            printf("Goodbye, have a good time!\n");
            break;
    }
    
    return 0;
}

void welcome() {
    printf(" ____  _   _    _    _  _______   _        _    ____  ____  _____ ____  \n");
    printf("/ ___|| \\ | |  / \\  | |/ / ____| | |      / \\  |  _ \\|  _ \\| ____|  _ \\ \n");
    printf("\\___ \\|  \\| | / _ \\ | ' /|  _|   | |     / _ \\ | | | | | | |  _| | |_) |\n");
    printf(" ___) | |\\  |/ ___ \\| . \\| |___  | |___ / ___ \\| |_| | |_| | |___|  _ < \n");
    printf("|____/|_| \\_\\_/   \\_\\_|\\_\\_____| |_____/_/   \\_\\____/|____/|_____|_| \\_\\\n");
}

int die() {
    return (rand() % 6) + 1;
}

void initializePlayer(Player *player, const char *name) {
    strcpy(player->name, name);
    player->position = 0;
    player->wins = 0;
    player->gamesPlayed = 0;
}

void playerturn(Player *player) {
    printf("%s's turn. Press Enter to roll the dice...\n", player->name);
    getchar();
    int roll = die();
    printf("%s rolled a %d\n", player->name, roll);
    player->position += roll;
    
    player->position = snakeladder(player->position, player->name);
    
    if (player->position > BOARD) {
        player->position = BOARD - (player->position - BOARD);
    }
    
    printf("%s is now on square %d\n\n", player->name, player->position);
}

bool winner(int position) {
    return position == BOARD;
}

int snakeladder(int position, const char *playerName) {
    // Ladders
    if(position == 1) {
        printf("%s climbed a ladder from 1 to 38!\n", playerName);
        return 38;
    }
    if(position == 4) {
        printf("%s climbed a ladder from 4 to 14!\n", playerName);
        return 14;
    }
    if(position == 9) {
        printf("%s climbed a ladder from 9 to 31!\n", playerName);
        return 31;
    }
    if(position == 21) {
        printf("%s climbed a ladder from 21 to 42!\n", playerName);
        return 42;
    }
    if(position == 28) {
        printf("%s climbed a ladder from 28 to 84!\n", playerName);
        return 84;
    }
    if(position == 51) {
        printf("%s climbed a ladder from 51 to 67!\n", playerName);
        return 67;
    }
    if(position == 80) {
        printf("%s climbed a ladder from 80 to 99!\n", playerName);
        return 99;
    }
    if(position == 72) {
        printf("%s climbed a ladder from 72 to 91!\n", playerName);
        return 91;
    }

    // Snakes
    if(position == 98) {
        printf("%s eaten by snake! sliding from 98 to 79!\n", playerName);
        return 79;
    }
    if(position == 94) {
        printf("%s eaten by snake! sliding from 94 to 75!\n", playerName);
        return 75;
    }
    if(position == 93) {
        printf("%s eaten by snake! sliding from 93 to 73!\n", playerName);
        return 73;
    }
    if(position == 87) {
        printf("%s eaten by snake! sliding from 87 to 36!\n", playerName);
        return 36;
    }
    if(position == 64) {
        printf("%s eaten by snake! sliding from 64 to 60!\n", playerName);
        return 60;
    }
    if(position == 62) {
        printf("%s eaten by snake! sliding from 62 to 19!\n", playerName);
        return 19;
    }
    if(position == 54) {
        printf("%s eaten by snake! sliding from 54 to 34!\n", playerName);
        return 34;
    }
    if(position == 17) {
        printf("%s eaten by snake! sliding from 17 to 7!\n", playerName);
        return 7;
    }

    return position;
}

void saveScore(Player *player) {
    FILE *temp = fopen("temp.txt", "w");
    FILE *fp = fopen(SCORE_FILE, "r");
    bool found = false;
    
    char name[MAX_NAME];
    int wins, games;
    
    // Copy existing scores to temp file, updating the player's score
    if (fp != NULL) {
        while (fscanf(fp, "%s %d %d", name, &wins, &games) != EOF) {
            if (strcmp(name, player->name) == 0) {
                fprintf(temp, "%s %d %d\n", player->name, player->wins, player->gamesPlayed);
                found = true;
            } else {
                fprintf(temp, "%s %d %d\n", name, wins, games);
            }
        }
        fclose(fp);
    }
    
    // Add new player if not found
    if (!found) {
        fprintf(temp, "%s %d %d\n", player->name, player->wins, player->gamesPlayed);
    }
    
    fclose(temp);
    
    // Replace original file with temp file
    remove(SCORE_FILE);
    rename("temp.txt", SCORE_FILE);
}

void loadScore(Player *player) {
    FILE *fp = fopen(SCORE_FILE, "r");
    if (fp == NULL) {
        return; // File doesn't exist yet
    }
    
    char name[MAX_NAME];
    int wins, games;
    
    while (fscanf(fp, "%s %d %d", name, &wins, &games) != EOF) {
        if (strcmp(name, player->name) == 0) {
            player->wins = wins;
            player->gamesPlayed = games;
            break;
        }
    }
    
    fclose(fp);
}

void displayScoreboard() {
    FILE *fp = fopen(SCORE_FILE, "r");
    if (fp == NULL) {
        printf("No scores recorded yet!\n");
        return;
    }
    
    printf("\n=== SCOREBOARD ===\n");
    printf("Player Name\tWins\tGames Played\tWin Rate\n");
    printf("------------------------------------------------\n");
    
    char name[MAX_NAME];
    int wins, games;
    
    while (fscanf(fp, "%s %d %d", name, &wins, &games) != EOF) {
        double winRate = games > 0 ? ((double)wins / games) * 100 : 0;
        printf("%-12s\t%d\t%d\t\t%.1f%%\n", name, wins, games, winRate);
    }
    
    fclose(fp);
}
