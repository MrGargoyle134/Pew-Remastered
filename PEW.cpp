#include <iostream>

#include <cstdio>

#include <windows.h>

#include <string>

#include <ctime>

#include <sstream>

using namespace std;

string Oeuf[24 /*Voici l'oeuf!*/ ] {
  "                           ",
  "                           ",
  "                           ",
  "                           ",
  "                           ",
  "                           ",
  "                           ",
  "            ####           ",
  "          ##....##         ",
  "        ##........##       ",
  "        ##........##       ",
  "      ##............##     ",
  "      ##............##     ",
  "      ##............##     ",
  "        ##........##       ",
  "          ########         ",
  "                           ",
  "                           ",
  "                           ",
  "                           ",
  "                           ",
  "                           ",
  "                           ",
  "                           ",

};

string Interface[24 /*Voici l'interface!*/ ] {
  "+----------------------------------------+",
  "|      ACTIONS      |     EXPERIENCE     |",
  "|                   |                    |",
  "|     1.SNACKS      |                    |",
  "|     2.MEALS       |                    |",
  "|     3.PLAY        |                    |",
  "|     4.PUNISH      |           /1000    |", //6
  "|                   |                    |",
  "|     5.RESTART     |                    |",
  "|     6.EXIT        |                    |",
  "|                   |                    |",
  "|-------------------+--------------------|",
  "|                                        |", //12
  "|                                        |",
  "|----------------------------------------|",
  "| [..............................]<HUN>  |", //15
  "|                                        |",
  "|                                        |",
  "| [..............................]<HAP>  |", //18
  "|                                        |",
  "|                                        |",
  "| [..............................]<DIS>  |", //21
  "|                                        |",
  "+----------------------------------------+",

};

bool JeuEnCours = true, Jn = true;
int PlayGame = 0;

void color(int col /*Fonction pour ajouter de la couleur*/ ) {
  HANDLE hConsole;
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, col);
}

void ClearScreen( /*Effacer l'écran*/ ) {
  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  CONSOLE_SCREEN_BUFFER_INFO csbi;
  if (!GetConsoleScreenBufferInfo(hStdOut, & csbi)) return;
  DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;
  COORD homeCoords = {
    0,
    0
  };
  DWORD count;
  if (!FillConsoleOutputCharacter(hStdOut, ' ', cellCount, homeCoords, & count)) return;
  if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, & count)) return;

  SetConsoleCursorPosition(hStdOut, homeCoords);
}

void ResetPosition( /*Replacer le curseur*/ ) {
  SetConsoleCursorPosition
    (GetStdHandle(STD_OUTPUT_HANDLE), COORD {
      0,
      0
    });
}

void printc(string text, int coloration) {
  color(coloration);
  cout << text;
}
char pix = 219;

static const char* const kGameOverASCIIArtPart1 =
  "                  G)gggg   A)aa    M)mm mmm  E)eeeeee\n"
  "                G)       A)  aa  M)  mm  mm E)       \n"
  "               G)  ggg  A)    aa M)  mm  mm E)eeeee  \n"
  "               G)    gg A)aaaaaa M)  mm  mm E)       \n"
  "                G)   gg A)    aa M)      mm E)       \n"
  "                 G)ggg  A)    aa M)      mm E)eeeeee \n";

static const char* const kGameOverASCIIArtPart2 =
"                   O)oooo  V)    vv E)eeeeee R)rrrrr  \n "
"                  O)    oo V)    vv E)       R)    rr \n "
"                 O)    oo V)    vv E)eeeee  R)  rrr   \n "
"                 O)    oo  V)  vv  E)       R) rr     \n "
"                 O)    oo   V)vv   E)       R)   rr   \n "
"                  O)oooo     V)    E)eeeeee R)    rr  \n ";

void game_over()
{
    ClearScreen();
    cout << endl << endl << endl << endl;
   color(15); //White
    std::puts(kGameOverASCIIArtPart1);
    cout << endl << endl;
   color(12); //Red
    std::puts(kGameOverASCIIArtPart2);
     Beep(400, 1500);
    system("EXIT");
}


void game() {
  int Exp = 0;
  int color_of_the_interface = 15;
  color(7);
  ClearScreen();
  int a;
  int coli;
  char colic;

  /*Choisir la couleur de l'oeuf (cool, non?)
  La couleur:
  10 correspond au vert
  11 correspond au bleu
  12 correspond au rouge
  13 correspond au mauve/violet
  14 correspond au jaune
  15 correspond au blanc
  */

  srand(time(NULL));
  int ranA, ranB, ranC, ranD;
  int TabChoix = 0;
  string Couleurs[5] = {
    "|>Blue",
    "|>Red",
    "|>Yellow",
    "|>Purple",
    "|>Green",
  };
  while (!GetAsyncKeyState('A')) {
    color(7);
    ResetPosition();
    if (GetAsyncKeyState(VK_UP)) {
      if (TabChoix > 0) {
        TabChoix--;
      }
      Sleep(100);
    }
    if (GetAsyncKeyState(VK_DOWN)) {
      if (TabChoix < 4) {
        TabChoix++;
      }
      Sleep(100);
    }
    cout << endl;
    color(7);
    printf("+-");
    color(15);
    printf("[INPUT]");
    color(7);
    printf("+--------------------------------------------------------------------+\n");
    printf("|                                                                             |\n");
    color(7);
    printf("|                  ");
    color(159);
    printf("What's color do you want for your egg?");
    color(7);
    printf("                     |\n");

    if (TabChoix != 0) {
      printc(Couleurs[0], 11); color(7);  cout << "                                                                        |\n";
    } else {
      Beep(1000, 100);
      printc(Couleurs[0], 176); color(7); cout << "                                                                        |\n";
    }
    if (TabChoix != 1) {
      printc(Couleurs[1], 12); color(7);  cout << "                                                                         |\n";
    } else {
      printc(Couleurs[1], 192); color(7); cout << "                                                                         |\n";
    }
    if (TabChoix != 2) {
      printc(Couleurs[2], 14); color(7);  cout << "                                                                      |\n";
    } else {
      printc(Couleurs[2], 224); color(7); cout << "                                                                      |\n";
    }
    if (TabChoix != 3) {
      printc(Couleurs[3], 13); color(7);  cout << "                                                                      |\n";
    } else {
      printc(Couleurs[3], 208); color(7); cout << "                                                                      |\n";
    }
    if (TabChoix != 4) {
      printc(Couleurs[4], 10); color(7);  cout << "                                                                       |\n";
    } else {
      printc(Couleurs[4], 160); color(7); cout << "                                                                       |\n";
    }
    color(7);
    printf("+-----------------------------------------------------------------------------+\n");
    color(7);
    printf("+-");
    color(15);
    printf("[OUTPUT]");
    color(7);
    printf("+-------------------------------------------------------------------+\n");
    printf("|                                                                             |\n");
    color(7);
    printf("|                                ");
    color(159);
    printf("You choose: ");
    color(7);
    printf("                                 |\n");
    printf("|Press A to confirm ");
    printf("                                                          |\n");
    printf("+-----------------------------------------------------------------------------+\n");
  }
  switch (TabChoix) {
  case 0:
    colic = 'B';
    break;
  case 3:
    colic = 'P';
    break;
  case 4:
    colic = 'G';
    break;
  case 1:
    colic = 'R';
    break;
  case 2:
    colic = 'Y';
    break;
  }
  cout << endl;

  switch (colic) {
  case 'B':
    coli = 11;
    break;
  case 'R':
    coli = 12;
    break;
  case 'Y':
    coli = 14;
    break;
  case 'P':
    coli = 13;
    break;
  case 'G':
    coli = 10;
    break;
  }
  Beep(1000, 100);

  //Lancement du jeu
  int Hun = 0 /*/30*/ , Hap = 0 /*/30*/ , Dis = 0 /*/30*/ ; /**< Creation des statistiques de Pew :D */
  string Etat = "Adulte";
  string textInterface1 = "                                        ";
  string textInterface2 = "                                        ";
  string dpr = "/1000";

  ClearScreen();
  while (JeuEnCours) //Tant que le jeu est en cours:
  {
    Etat = "Oeuf";

    ranA = rand() % 4;
    ranB = rand() % 2;
    ranD = rand() % 35;
    string Hun_str, Hap_str, Dis_str;
    ResetPosition(); //On replace le curseur
    stringstream ss;
    ss << Exp;
    string str = ss.str();

    if (GetAsyncKeyState('3')) {
      Beep(1000, 100);
      PlayGame = 1;
    }

    if (PlayGame == 1) //Si on joue au jeu
    {
      color_of_the_interface = 11;
      /**
      Le jeu est très simple:
      Il faut juste deviner à quelle direction
      pense Pew
      **/
      ranC = rand() % 2;

      Interface[12] = "|Let's play! Guess the direction chosen  |";
      Interface[13] = "|by Pew. Press (R)IGHT or (L)EFT.        |";
      if (GetAsyncKeyState('R')) {
        if (ranC == 1) {
          //Gagné
          Interface[12] = "|You win!                                |";
          Interface[13] = "|                                        |";
          if (Hap + 4 < 30) {
            Hap += 4;
          }
          Exp += 40;
        } else if (ranC == 0) {
          if (Hap > 0) {
            Hap -= 1;
          }
          if (Hun > 0) {
            Hun -= 1;
          }
          if (Dis < 30) {
            Dis += 1;
          }
          Exp += 10;
          Interface[12] = "|You lose!                               |";
          Interface[13] = "|                                        |";
          //Perdu
        }
        Sleep(400);
        PlayGame = 0;
      } else if (GetAsyncKeyState('L')) {
        if (ranC == 0) {
          //Gagné
          if (Hap + 4 < 30) {
            Hap += 4;
          }
          Exp += 30;
          Interface[12] = "|You win!                                |";
          Interface[13] = "|                                        |";
        } else if (ranC == 1) {
          //perdu
          if (Hap > 0) {
            Hap -= 1;
          }
          if (Hun > 0) {
            Hun -= 1;
          }
          if (Dis < 30) {
            Dis += 1;
          }
          Exp += 10;
          Interface[12] = "|You lose!                               |";
          Interface[13] = "|                                        |";
        }
        Sleep(400);
        PlayGame = 0;
      }
    } else {
      color_of_the_interface = 15;
      textInterface1 = "                                        ";
      textInterface2 = "                                        ";
    Interface[12] = "|                                        |";
    Interface[13] = "|                                        |";
    }
    if (GetAsyncKeyState('1')) {
      Beep(1000, 100);
      if (Hap < 30 && Hun < 30) {
        Exp += 5;
        Hap++;
        if (ranA == 2) {
          Hun++;
        }
        Sleep(50);
      }
      if (Dis > 0) {
        Dis--;
      }
    }
    if (GetAsyncKeyState('2')) {
      Beep(1000, 100);
      if (Hun < 30) {
        Exp += 10;
        Hun++;
        Sleep(50);
      }
      if (ranA == 2) {
        if (Hap > 0) {
          Hap--;
        }
      }
    }

    if (GetAsyncKeyState('4')) {
      Beep(1000, 100);
      Exp += 15;
      if (Dis < 30) {
        Dis += 1;
        if (Hap > 0) {
          Hap--;
        }
        Sleep(150);
      }
    }

    if (GetAsyncKeyState('5')) {
      Beep(1000, 100);
      game();
    }
    if (GetAsyncKeyState('6')) {
      Beep(1000, 100);
      JeuEnCours = false;
    }

    for (int i = 0; i < Hun; i++) {
      Hun_str += pix;
    }
    for (int i = 0; i < 30 - Hun; i++) {
      Hun_str += ".";
    }

    Interface[15] = "| [" + Hun_str + "]<HUN>  |";

    for (int i = 0; i < Dis; i++) {
      Dis_str += pix;
    }
    for (int i = 0; i < 30 - Dis; i++) {
      Dis_str += ".";
    }

    Interface[21] = "| [" + Dis_str + "]<DIS>  |";

    for (int i = 0; i < Hap; i++) {
      Hap_str += pix;
    }
    for (int i = 0; i < 30 - Hap; i++) {
      Hap_str += ".";
    }

    Interface[18] = "| [" + Hap_str + "]<HAP>  |";

    if (ranD == 25) {
      if (Hun > 0) {
        Hun--;
      }
    }
    if(Jn)
    {
    if (Exp < 10) {
      Interface[6] = "|     4.PUNISH      |       " + str + dpr + "       |";
    } else if (Exp < 100) {
      Interface[6] = "|     4.PUNISH      |       " + str + dpr + "      |";
    } else if (Exp < 1000) {
      Interface[6] = "|     4.PUNISH      |       " + str + dpr + "     |";
    } else if (Exp < 10000){
      Interface[6] = "|     4.PUNISH      |       " + str + dpr + "    |";
    }
    }

    for (int a = 0; a < 24; a++) {
      for (int b = 0; b < Oeuf[a].size(); b++) {
        switch (Oeuf[a][b]) {
        case '#':
          color(15);
          break;
        case '.':
          color(coli);
          break;
        case 'o':
          color(coli);
          break;
        case 'O':
          color(12);
          break;
        case ',':
          color(7);
          break;

        }
        cout << Oeuf[a][b]; //Afficher l'oeuf
      }
      color(color_of_the_interface);
      cout << "          " << Interface[a] << endl;

    }

    if (Exp >= 1000 && Etat == "Oeuf") {
      Etat = "Sortie";
      dpr = "/2500";
    }

    if (Exp >= 2500 && Etat == "Sortie") {
      if (Hap >= 15) {
        Etat = "Bebe";
        dpr = "/3000";
      }
    }
    if (Exp >= 3000 && Etat == "Bebe") {
      if (Hun >= 20) {
        Etat = "Enfant";
        dpr = "/5000";
      }
    }

    if (Exp >= 5000 && Etat == "Enfant") {
      if (Dis >= 28) {
        Etat = "Ado";
        dpr = "/9500";
      }
    }
    if (Exp >= 9500 && Etat == "Ado") {
      if (Dis >= 20 && Hun >= 20 && Hap >= 20) {
        Etat = "Adulte";
      }
    }

    if (Etat != "Oeuf") {
      if (Hun <= 0) {
        JeuEnCours = 0;
        game_over();
      }
    }

    if (Etat == "Sortie") {
      Oeuf[0] = "                           ";
      Oeuf[1] = "                           ";
      Oeuf[2] = "                           ";
      Oeuf[3] = "                           ";
      Oeuf[4] = "                           ";
      Oeuf[5] = "                           ";
      Oeuf[6] = "                           ";
      Oeuf[7] = "            ####           ";
      Oeuf[8] = "          ##....##         ";
      Oeuf[9] = "        ##........##       ";
      Oeuf[10] = "        ##........##       ";
      Oeuf[11] = "      ##............##     ";
      Oeuf[12] = "      ##............##     ";
      Oeuf[13] = "      ##............##     ";
      Oeuf[14] = "        ##........##       ";
      Oeuf[15] = "          ########         ";
      Oeuf[16] = "         #        #        ";
      Oeuf[17] = "        #          #       ";
      Oeuf[18] = "        #          #       ";
      Oeuf[19] = "                           ";
      Oeuf[20] = "                           ";
      Oeuf[21] = "                           ";
      Oeuf[22] = "                           ";
      Oeuf[23] = "                           ";
    }
    if (Etat == "Bebe") {
      Oeuf[0] = "                           ";
      Oeuf[1] = "                           ";
      Oeuf[2] = "                           ";
      Oeuf[3] = "          ########         ";
      Oeuf[4] = "         #        #        ";
      Oeuf[5] = "         # o    o #        ";
      Oeuf[6] = "         #        #        ";
      Oeuf[7] = "         #  ####  #        ";
      Oeuf[8] = "         ###....###        ";
      Oeuf[9] = "        ##........##       ";
      Oeuf[10] = "        ##........##       ";
      Oeuf[11] = "      ##............##     ";
      Oeuf[12] = "  ######............###### ";
      Oeuf[13] = "      ##............##     ";
      Oeuf[14] = "        ##........##       ";
      Oeuf[15] = "          ########         ";
      Oeuf[16] = "         #        #        ";
      Oeuf[17] = "        #          #       ";
      Oeuf[18] = "        #          #       ";
      Oeuf[19] = "                           ";
      Oeuf[20] = "                           ";
      Oeuf[21] = "                           ";
      Oeuf[22] = "                           ";
      Oeuf[23] = "                           ";
    }
    if (Etat == "Enfant") {
      Oeuf[0] = "                           ";
      Oeuf[1] = "                           ";
      Oeuf[2] = "           ,,,,,,          ";
      Oeuf[3] = "          ########         ";
      Oeuf[4] = "         #        #        ";
      Oeuf[5] = "         # o    o #        ";
      Oeuf[6] = "         #   --   #        ";
      Oeuf[7] = "         #  ####  #        ";
      Oeuf[8] = "         ###....###        ";
      Oeuf[9] = "        ##........##       ";
      Oeuf[10] = "        ##........##       ";
      Oeuf[11] = "      ##............##     ";
      Oeuf[12] = "  ######............###### ";
      Oeuf[13] = "      ##............##     ";
      Oeuf[14] = "        ##........##       ";
      Oeuf[15] = "          ########         ";
      Oeuf[16] = "         #        #        ";
      Oeuf[17] = "        #          #       ";
      Oeuf[18] = "        #          #       ";
      Oeuf[19] = "       ##          ##      ";
      Oeuf[20] = "                           ";
      Oeuf[21] = "                           ";
      Oeuf[22] = "                           ";
      Oeuf[23] = "                           ";
    }

    if (Etat == "Ado") {
      Oeuf[0] = "                           ";
      Oeuf[1] = "                           ";
      Oeuf[2] = "           ,,,,,,          ";
      Oeuf[3] = "          ########         ";
      Oeuf[4] = "         # o    o #        ";
      Oeuf[5] = "        (#       O#)       ";
      Oeuf[6] = "         # O\\--/  #        ";
      Oeuf[7] = "         #  ####  #        ";
      Oeuf[8] = "         ###....###        ";
      Oeuf[9] = "        ##........##       ";
      Oeuf[10] = "        ##........##       ";
      Oeuf[11] = "      ##............##     ";
      Oeuf[12] = "  ######............###### ";
      Oeuf[13] = "      ##............##     ";
      Oeuf[14] = "        ##........##       ";
      Oeuf[15] = "          ########         ";
      Oeuf[16] = "         #        #        ";
      Oeuf[17] = "        #          #       ";
      Oeuf[18] = "        #          #       ";
      Oeuf[19] = "        #          #       ";
      Oeuf[20] = "      ###          ###     ";
      Oeuf[21] = "                           ";
      Oeuf[22] = "                           ";
      Oeuf[23] = "                           ";
    }

    if (Etat == "Adulte") {
      Oeuf[0] = "                           ";
      Oeuf[1] = "          ,,,,,,,,         ";
      Oeuf[2] = "          ########         ";
      Oeuf[3] = "         # \\    / #        ";
      Oeuf[4] = "         # o    o #        ";
      Oeuf[5] = "        (#        #)       ";
      Oeuf[6] = "         #;;\\--/;;#        ";
      Oeuf[7] = "         #;;####;;#        ";
      Oeuf[8] = "         ###....###        ";
      Oeuf[9] = "        ##........##       ";
      Oeuf[10] = "        ##........##       ";
      Oeuf[11] = "   #  ##............##  #  ";
      Oeuf[12] = "  ######............###### ";
      Oeuf[13] = "   #  ##............##  #  ";
      Oeuf[14] = "        ##........##       ";
      Oeuf[15] = "          ########         ";
      Oeuf[16] = "         #        #        ";
      Oeuf[17] = "        #          #       ";
      Oeuf[18] = "        #          #       ";
      Oeuf[19] = "        #          #       ";
      Oeuf[20] = "      ###          ###     ";
      Oeuf[21] = "                           ";
      Oeuf[22] = "                           ";
      Oeuf[23] = "                           ";
    }

    if (Exp >= 9500) {
            Jn = false;
      //Gagné!
      PlayGame = 0;
      Interface[0] =  "+----------------------------------------+";
      Interface[1] =  "|                                        |";
      Interface[2] =  "|                                        |";
      Interface[3] =  "| x   x xxxx x  x   x     x xxxx x    x  |";
      Interface[4] =  "|  x x  x  x x  x   x     x x  x xx   x  |";
      Interface[5] =  "|   x   x  x x  x   x     x x  x x x  x  |";
      Interface[6] =  "|   x   x  x x  x    x x x  x  x x  x x  |"; //6
      Interface[7] =  "|   x   x  x x  x     x x   x  x x   xx  |";
      Interface[8] =  "|   x   xxxx xxxx     x x   xxxx x    x  |";
      Interface[9] =  "|                                        |";
      Interface[10] = "|                                        |";
      Interface[11] = "|----------------------------------------|";
      Interface[12] = "|Nice work!                              |"; //12
      Interface[13] = "|                                        |";
      Interface[14] = "|----------------------------------------|";
      Interface[15] = "| [..............................]<HUN>  |"; //15
      Interface[16] = "|                                        |";
      Interface[17] = "|                                        |";
      Interface[18] = "| [..............................]<HAP>  |"; //18
      Interface[19] = "|                                        |";
      Interface[20] = "|                                        |";
      Interface[21] = "| [..............................]<DIS>  |"; //21
      Interface[22] = "|                                        |";
      Interface[23] = "+----------------------------------------+";
      system("PAUSE");
    }
   //Gerer les erreurs
   if(Hun > 30){system("EXIT");}
   if(Hap > 30){system("EXIT");}
   if(Dis > 30){system("EXIT");}

   if(Hun < 0) {system("EXIT");}
   if(Hap < 0) {system("EXIT");}
   if(Dis < 0) {system("EXIT");}

   if(Exp < 0) {system("EXIT");}
  }
}

void intro( /*Intro du jeu*/ ) {
  while (!GetAsyncKeyState(VK_SPACE)) {
    ResetPosition();
    color(156);
    cout << endl << "+------------------------------------------------------------------------------+\n";
    cout << endl << endl << endl << endl;
    color(7); //On centre le texte
    printf("                             --Welcome to PEW--\n\n");
    color(10);

    printf("                        PPPPPP  EEEEEEE WW       WW\n");
    color(11);
    printf("                        PP   PP EE      WW       WW\n");
    color(12);
    printf("                        PPPPPP  EEEEE   WW   W   WW\n");
    color(13);
    printf("                        PP      EE       WW WWW WW\n");
    color(14);
    printf("                        PP      EEEEEEE   WW   WW \n\n");
    color(15);

    printf("                             Remastered Edition\n\n");
    color(7);
    printf("                           PRESS SPACE to continue");
    cout << endl << endl << endl;
    color(156);
    cout << endl << "+------------------------------------------------------------------------------+\n";
  }
  game();

}

int main( /*Fonction principale*/ ) {
  SetConsoleTitle("PEW Remastered"); //Mettre un titre a la console
  ClearScreen();
  intro();
}
