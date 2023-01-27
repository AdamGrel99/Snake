#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

// zmienne menu
enum game {MAIN, START, OPTION, INSTRUCTION};
game mode;
int menu = 0;
// zmienne opcje
int option = 0;
string tabSpeed[3] = {"SLOW", "MEDIUM", "FAST"};
string tabSize[3] = { "SMALL", "MEDIUM", "BIG" };
int typeSpeed = 2;		// wartoœcie domyœlne dla gry
int typeSize = 1;
// zmienne gry
int width = 25;     // ustawienia domyœlne dla medium
int height = 25;
int score;
enum direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
direction dir;
// zmienne wê¿a
int snakeX, snakeY;
int speed = 30;		// ustawienia domylne dla fast
int tailX[100], tailY[100], tailLength;
// zmienne owoca
int fruitX, fruitY;

void idzdoxy(int x, int y) {
	HANDLE hCon;
	COORD dwPos;

	dwPos.X = x;
	dwPos.Y = y;

	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon, dwPos);
}

void HideCursor() {
	::HANDLE hConsoleOut = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::CONSOLE_CURSOR_INFO hCCI;
	::GetConsoleCursorInfo(hConsoleOut, &hCCI);
	hCCI.bVisible = FALSE;
	::SetConsoleCursorInfo(hConsoleOut, &hCCI);
}

void game_Over() {
	tailLength = 0;
	score = 0;
	mode = MAIN;
}

void game_Setup() {
	mode = MAIN;
}

void game_Option() {
	system("cls");

	switch (option) {
	case 0:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); // zielony
		cout << ">> Speed : " << tabSpeed[typeSpeed] << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // domylny bia³y
		cout << "Size : " << endl;
		cout << "Return" << endl;
		break;
	case 1:
		cout << "Speed : " << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		cout << ">> Size : " << tabSize[typeSize] << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		cout << "Return" << endl;
		break;
	case 2:
		cout << "Speed : " << endl;
		cout << "Size : " << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		cout << ">> Return" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		break;
	}

	system("pause>0");

	if (GetAsyncKeyState(VK_RETURN)) {
		switch (option) {
		case 0:
			break;
		case 1:
			break;
		case 2:
			switch (typeSpeed) {
			case 0:
				speed = 100;
				break;
			case 1:
				speed = 70;
				break;
			case 2:
				speed = 30;
				break;
			}

			switch (typeSize) {
			case 0:
				width = 15;
				height = 15;
				break;
			case 1:
				width = 25;
				height = 25;
				break;
			case 2:
				width = 40;
				height = 25;
				break;
			}

			mode = MAIN;
			system("cls"); 
			break;
		}
	}

	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) {
		if (option == 0) {
			typeSpeed--;
		}
		else if (option == 1) {
			typeSize--;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) {
		if (option == 0) {
			typeSpeed++;
		}
		else if (option == 1) {
			typeSize++;
		}
	}
	else if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) {
		option++;
		Sleep(100);
	}
	else if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')) {
		option--;
		Sleep(100);
	}
	else if (GetAsyncKeyState(VK_ESCAPE)) {
		mode = MAIN;
	}

	if (option < 0) {
		option = 2;
	}
	else if (option > 2) {
		option = 0;
	}

	if (typeSpeed < 0) {
		typeSpeed = 2;
	}
	else if (typeSpeed > 2) {
		typeSpeed = 0;
	}

	if (typeSize < 0) {
		typeSize = 2;
	}
	else if (typeSize > 2) {
		typeSize = 0;
	}
}

void game_Instruction() {
	system("cls");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	cout << "*** Instruction Snake Game ***" << endl << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << "In the game of Snake, the player uses the arrow or 'WASD' keys to move a 'snake' around the board." << endl;
	cout << "As the snake finds food, it eats the food, and thereby grows larger." << endl;
	cout << "The game ends when the snake either moves off the screen or moves into itself." << endl;
	cout << "The goal is to make the snake as large as possible (the biggest score) before that happens." << endl;
	cout << "In Options you can change size of board and snake speed." << endl;
	cout << "You can go back with a ESC key in any window." << endl;

	system("pause>0");

	if (GetAsyncKeyState(VK_ESCAPE)) {
		mode = MAIN;
	}
}

void main_Menu() {
	system("cls");
		
	switch (menu) {
	case 0:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); // zielony
		cout << ">> Play the Game" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // domylny bia³y
		cout << "Option" << endl;
		cout << "Instruction" << endl;
		cout << "End Game" << endl;
		break;
	case 1:
		cout << "Play the Game" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		cout << ">> Option" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		cout << "Instruction" << endl;
		cout << "End Game" << endl;
		break;
	case 2:
		cout << "Play the Game" << endl;
		cout << "Option" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		cout << ">> Instruction" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		cout << "End Game" << endl;
		break;
	case 3:
		cout << "Play the Game" << endl;
		cout << "Option" << endl;
		cout << "Instruction" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		cout << ">> End Game" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		break;
	}
	
	system("pause>0");

	if (GetAsyncKeyState(VK_RETURN)) {
		switch (menu) {
		case 0:
			mode = START;
			system("cls");
			break;
		case 1:
			mode = OPTION;
			system("cls");
			break;
		case 2:
			mode = INSTRUCTION;
			system("cls");
			break;
		case 3:
			system("cls");   // czyœci konsole
			exit(0);
			break;
		}
	}

	// naprawia b³¹d wynikaj¹cy z naciœniêcie 'wasd' przed nacisnieciem play the game (dir = stop)
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A') || GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) {
		dir = STOP;
	}
	else if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) {
		dir = STOP;
		menu++;
		Sleep(100);
	}
	else if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')) {
		dir = STOP;
		menu--;
		Sleep(100);
	}
	else if (GetAsyncKeyState(VK_ESCAPE)) {
		system("cls");
		exit(0);
	}

	if (menu < 0) {
		menu = 3;
	}
	else if (menu > 3) {
		menu = 0;
	}
}

void normal_Setup() {
	dir = STOP;
	snakeX = width / 2;
	snakeY = height / 2;
	do {
		fruitX = rand() % width + 1;
		fruitY = rand() % height;
	} while (fruitX == snakeX && fruitY == snakeY);
	score = 0;
}

void game_Draw() {
	idzdoxy(0, 0); // wraca na pocz¹tek w tym uk³adzie wspó³rzêdnych bez czyszczenie tablicy. Zastêpuje system("cls");

	for (int i = 0; i < width + 2; i++) {
		cout << "*";
	}
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width + 2; j++) {
			if (j == 0 || j == width + 1) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				cout << "*";
			}
			else if (i == snakeY && j == snakeX) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				cout << "0";
			}
			else if (i == fruitY && j == fruitX) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);  // czerwony
				cout << "F";
			}
			else {
				bool tail = false;
				for (int k = 0; k < tailLength; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); 
						cout << "o";
						tail = true;
					}
				}
				if (!tail) {
					cout << " ";
				}
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		cout << "*";
	}
	cout << endl << "Score: " << score << endl;
}

void game_Input_InnaWersja() {
	if (_kbhit()) {							// sprawdza naciœniêcie klawisza
		switch (_getch()) {
		case 'a':
			if (dir != RIGHT) {				// uniemo¿liwia gwa³towne zawracanie wê¿a
				dir = LEFT;
			}
			break;
		case 'w':
			if (dir != DOWN) {
				dir = UP;
			}
			break;
		case 's':
			if (dir != UP) {
				dir = DOWN;
			}
			break;
		case 'd':
			if (dir != LEFT) {
				dir = RIGHT;
			}
			break;
		case 'q':
			mode = MAIN;
			break;
		}
	}
}

void game_Input() {
	if ((GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A')) && dir != RIGHT) {
		dir = LEFT;
	} 
	else if ((GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D')) && dir != LEFT) {
		dir = RIGHT;
	}
	else if ((GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S')) && dir != UP) {
		dir = DOWN;
	}
	else if ((GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W')) && dir != DOWN) {
		dir = UP;
	}
	else if (GetAsyncKeyState(VK_ESCAPE)) {
		mode = MAIN;
	}
}

void game_Logic() {
	// cia³o wê¿a
	int firstpositionX, firstpositionY;
	int secondpositionX, secondpositionY;
	firstpositionX = tailX[0];
	firstpositionY = tailY[0];
	tailX[0] = snakeX;
	tailY[0] = snakeY;
	for (int i = 1; i < tailLength; i++) {
		secondpositionX = tailX[i];
		secondpositionY = tailY[i];
		tailX[i] = firstpositionX;
		tailY[i] = firstpositionY;
		firstpositionX = secondpositionX;
		firstpositionY = secondpositionY;
		while (tailX[i] == fruitX && tailY[i] == fruitY) {
			fruitX = rand() % width + 1;
			fruitY = rand() % height;
		}
	}
	// Ruch wê¿a
	switch (dir) {
	case LEFT:
		snakeX --;
		break;
	case UP:
		snakeY --;
		break;
	case DOWN:
		snakeY ++;
		break;
	case RIGHT:
		snakeX ++;
		break;
	}
	// Gdy w¹¿ uderza w plansze i w samego siebie
	if (snakeX > width || snakeX == 0 || snakeY > height - 1 || snakeY == -1) {
		game_Over();
	}

	for (int i = 0; i < tailLength; i++) {
		if (snakeX == tailX[i] && snakeY == tailY[i]) {
			game_Over();
		}
	}

	// Gdy w¹¿ zjada owoc
	if (snakeX == fruitX && snakeY == fruitY) {
		fruitX = rand() % width + 1;
		fruitY = rand() % height;
		score += 10;
		tailLength++;
	}
}

void startGame() {
	game_Setup();
	HideCursor();
	while (true) {
		if (mode == MAIN) {
			main_Menu();
		}
		else if (mode == OPTION) {
			game_Option();
		}
		else if (mode == INSTRUCTION) {
			game_Instruction();
		}
		else {
			normal_Setup();
			while (mode == START) {
				game_Draw();
				game_Input();
				game_Logic();
				Sleep(speed);
			}
		}
	}
}