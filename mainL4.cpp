#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int*** createCube();
void normalAttack(int***);
void waveAttack(int***);
void expansiveAttack(int***);
void showShips(int***);
int countShips(int***);
void clearMemory(int***);
void setShips(int***);
int checkWinner(int***, int***);
void Gameplay(int*, int, int*, int, int***, int***);
void fillBoard(int***);


int main() {
    srand(time(NULL));
    cout<<"--- BATTLESHIP ---"<<endl<<endl;
    int*** P1 = createCube();
    int*** P2 = createCube();
    int ships_P1 = 15;
    int ships_P2 = 15;
    int waves_P1 = 3;
    int waves_P2 = 3;
    int ex_P1 = 3;
    int ex_P2 = 3;
    int winner = 0;
    
    fillBoard(P1);
    fillBoard(P2);

    setShips(P1);
    setShips(P2);

    while (winner == 0) {
        Gameplay(&waves_P1, waves_P1, &ex_P1, ex_P2, P1, P2);
        winner = checkWinner(P1, P2); // Si gana P1 --> 1
        Gameplay(&waves_P2, waves_P2, &ex_P2, ex_P2, P2, P1);
        winner = checkWinner(P1, P2); // Si gana P2 --> 2
    }
    if (winner == 1) {
        cout<<"¡Ha ganado el Jugador 1!"<<endl;
    } else if (winner == 2) {
        cout<<"¡Ha ganado el Jugador 2!"<<endl;
    }
    clearMemory(P1);
    clearMemory(P2);
    return 0;
}

int*** createCube() {
    int*** cube = new int**[12];
    for (int i = 0; i < 12; i++) {
        cube[i] = new int*[12];
    }

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            cube[i][j] = new int[12];
        }
    }
    return cube;
}

void clearMemory(int*** cube) {
	for(int i = 0;i < 13; i++){
		for(int j = 0; j < 3; j++){
			delete [] cube[i][j];
			cube[i][j] = NULL;
		}
	}

	for(int i = 0 ; i < 12 ;i++){
		delete[] cube[i];
		cube[i] = NULL;
	}
	delete[]cube;
}

void setShips(int*** board) {
    for (int i = 0; i < 15; i++) {
        int x = rand() % 11;
        int y = rand() % 11;
        int z = rand() % 11;
        while (board[x][y][z] != 0) {
            x = rand() % 11;
            y = rand() % 11;
            z = rand() % 11;
        }
        board[x][y][z] = 1;
    }
}

void fillBoard(int*** board) {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            for (int k = 0; k < 12; k++) {
                board[i][j][k] = 0;
            }
        }
    }
}

void showShips(int*** board) {
    for (int i = 0; i < 12; i++) {
         for (int j = 0; j < 12; j++) {
             for (int k = 0; k < 12; k++) {
                 if (board[i][j][k] == 1) {
                     cout<<"("<<i<<", "<<j<<", "<<k<<")"<<endl;
                 }
             }
         }
    }
}

int countShips(int*** board) {
    int cont = 0;
     for (int i = 0; i < 12; i++) {
          for (int j = 0; j < 12; j++) {
              for (int k = 0; k < 12; k++) {
                  if (board[i][j][k] == 1) {
                      cont = cont+1;
                  }
              }
          }
     }
     return cont;
}

void normalAttack(int*** board) {
    int x = 0;
    int y = 0;
    int z = 0;
    cout<<endl<<"Ingrese una coordenada x: ";
    cin>>x;
    while (x < 0 && x > 11) {
        cout<<"Ha ingresado una coordenada inválida."
        <<endl<<"Ingrese una nueva coordenada: ";
        cin>>x;
    }
    cout<<endl<<"Ingrese una coordenada y: ";
    cin>>y;
    while (y < 0 && y > 11) {
         cout<<"Ha ingresado una coordenada inválida."
         <<endl<<"Ingrese una nueva coordenada: ";
         cin>>y;
    }
    cout<<endl<<"Ingrese una coordenada z: ";
    cin>>z;
    while (z < 0 && z > 11) {
         cout<<"Ha ingresado una coordenada inválida."
         <<endl<<"Ingrese una nueva coordenada: ";
         cin>>z;
    }
    cout<<endl;
    if (board[x][y][z] == 1) {
        cout<<"Submarino en ("<<x<<", "<<y<<", "<<z<<") destruído."<<endl;
    } else {
        cout<<"Nada que destruir."<<endl;
    }
}

void waveAttack(int*** board) {
    int opt = 0;
    cout<<"¿Qué plano desea atacar?"
    <<endl<<"1.- Plano XY"
    <<endl<<"2.- Plano YZ"
    <<endl<<"3.- Plano XZ"
    <<endl<<"Ingrese el número correspondiente a su opción: ";
    cin>>opt;
    while (opt <= 0 || opt > 3) {
        cout<<"Opción inválida. Por favor, ingrese un número entre 1 y 3: ";
        cin>>opt;
    }
    int atck = -1;
    if (opt == 1) { 
        cout<<endl<<"Ingrese el valor Z por atacar: ";
        cin>>atck;
        while (atck < 0 || atck >= 12) {
    	    cout<<"Coordenada inválida. Inténtelo de nuevo: ";
    	    cin>>atck;
        }
        for (int x = 0; x < 12; x++) {
            for (int y = 0; y < 12; y++) {
                if (board[x][y][atck] == 1) {
                    cout<<"Submarino en ("<<x<<", "<<y<<", "<<atck<<") destruído."<<endl; 
                } else {
                    cout<<"Nada que destruir."<<endl;
                }
            }
        }

    } else if (opt == 2) {
        cout<<endl<<"Ingrese el valor X por atacar: ";
        cin>>atck;
        while (atck <= 0 || atck >= 12) {
        	cout<<"Coordenada inválida. Inténtelo de nuevo: ";
	        cin>>atck;
        }
        for (int y = 0; y < 12; y++) {
            for (int z = 0; z < 12; z++) {
                 if (board[atck][y][z] == 1) {
                     cout<<"Submarino en ("<<atck<<", "<<y<<", "<<z<<") destruído."<<endl;
                 } else {
                     cout<<"Nada que destruir."<<endl;
                 }
             }
         }
    } else if (opt == 3) {
        cout<<endl<<"Ingrese el valor Y por atacar; ";
        cin>>atck;
        while (atck <= 0 || atck >= 12) {
    	    cout<<"Coordenada inválida. Inténtelo de nuevo: ";
	        cin>>atck;
        }
        for (int x = 0; x < 12; x++) {
            for (int z = 0; z < 12; z++) {
                 if (board[x][atck][z] == 1) {
                     cout<<"Submarino en ("<<x<<", "<<atck<<", "<<z<<") destruído."<<endl;
                 } else {
                     cout<<"Nada que destruir."<<endl;
                 }
             }
         }
    }
}

void expansiveAttack(int*** board) {
     int x = 0;
     int y = 0;
     int z = 0;
     cout<<endl<<"Ingrese una coordenada x: ";
     cin>>x;
     while (x < 0 && x > 11) {
         cout<<"Ha ingresado una coordenada inválida."
         <<endl<<"Ingrese una nueva coordenada: ";
         cin>>x;
     }
     cout<<endl<<"Ingrese una coordenada y: ";
     cin>>y;
     while (y < 0 && y > 11) {
          cout<<"Ha ingresado una coordenada inválida."
          <<endl<<"Ingrese una nueva coordenada: ";
          cin>>y;
     }
     cout<<endl<<"Ingrese una coordenada z: ";
     cin>>z;
     while (z < 0 && z > 11) {
          cout<<"Ha ingresado una coordenada inválida."
          <<endl<<"Ingrese una nueva coordenada: ";
          cin>>z;
     }
     cout<<endl;
    // Mirarlos como 3 layers diferentes 
}

void Gameplay(int* contW, int contw, int* contE, int conte, int*** board, int*** boardP2) {
    cout<<"------------ MAPA DE SUBMARINOS ------------"<<endl;
    showShips(board);
    cout<<endl<<"Submarinos por destruir: "<<countShips(boardP2);
    cout<<endl<<"------------ MENÚ DE ATAQUES ------------"<<endl;
    cout<<"1.- Ataque Normal"
        <<endl<<"2.- Ataque Wave"
        <<endl<<"3.- Ataque Expansive."
        <<endl<<"WAVES DISPONIBLES: "<<contw<<endl<<"EXPANSIVE DISPONIBLES: "<<conte
        <<endl<<"Ingrese el número del ataque que desea lanzar: ";
    int atck = 0;
    cin>>atck;
    if (atck == 1) {
        normalAttack(boardP2);
    } else if (atck == 2) {
        if (contW <= 0) {
            cout<<"No tiene ataques wave restantes. Preparando ataque normal...";
            normalAttack(boardP2);
        } else {
            contW = contW - 1;
            waveAttack(boardP2);
        }
    } else if (atck == 3) {
        if (contE <= 0) {
            cout<<"No tiene ataques expansive restantes. Preparando ataque normal...";
            normalAttack(boardP2);
        } else {
            contE = contE - 1;
            expansiveAttack(boardP2);
        }
    }
}

int checkWinner(int*** board, int*** board2) {
    int winner = 0;
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            for (int k = 0; k < 12; k++) {
                if (board2[i][j][k] == 1) {
                    winner = 0;
                    return winner;
                }
                if (board[i][j][k] == 1) {
                    winner = 0;
                    return winner;
                }
                if (board2[i][j][k] == 0) {
                    winner = 2;
                }
                if (board2[i][j][k] == 0) {
                    winner = 1;
                }
            }
        }
    }
    return winner;
}
