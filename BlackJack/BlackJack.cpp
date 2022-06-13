#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <ctime>

using namespace std;

typedef enum playerType {playerT, dealerT} playerType;
typedef enum gameState { stop, play, playerLose, playerWin, nobodyWin, newgame } gameState;
gameState state = play;

void checkGameState();
void endGame();

class playerObj {
private:
	string Name = "blank";
	int Points = NULL;
	int Bet = NULL;
	int Score = NULL;
	playerType pt = playerT;

public:
	vector<int> Cards;

	void setPlayerType(playerType a) {
		pt = a;
	}

	void playerInit() {
		if (pt == playerT) {
			Name = "Player";
			Points = 1000;
			Bet = 100;
			Score = NULL;
		}
		if (pt == dealerT) {
			Name = "Dealer";
			Points = NULL;
			Bet = NULL;
			Score = NULL;
		}
	}

	void takeCard() {
		Cards.push_back(rand() % (11 - 3) + 2);
		calcScore();
		checkGameState();
	}

	void calcScore() {
		Score = 0;
		for (int i = 0; i < Cards.size(); i++) {
			Score += Cards[i];
		}
	}

	void chandeBet(int a) {
		Bet = a;
	}

	void addPoints(int a) {
		Points += a;
	}

	void removePoints(int a) {
		Points -= a;
	}

	string getName() {
		return Name;
	}

	int getPoints() {
		return Points;
	}

	int getBet() {
		return Bet;
	}

	int getScore() {
		return Score;
	}
};

playerObj dealer;
playerObj player;

HANDLE hCon;
COORD cPos;

void gameInit() {
	state = play;
	dealer.setPlayerType(dealerT);
	dealer.playerInit();
	player.setPlayerType(playerT);
	player.playerInit();
}

void screenReload() {
	system("cls");
	cout << "========================================================\n";
	cout << "\n\n\n\n\n\n\n\n";
	cout << "========================================================\n";
	cout << "\n\n\n\n\n";
	cout << "========================================================\n";
}

void printInfo() {
	// Инфо о игроке
	SetConsoleCursorPosition(hCon, { 1, 1 });
	cout << "BET: " << player.getBet() << "\tPoints: " << player.getPoints();
	
	SetConsoleCursorPosition(hCon, { 1, 3 });
	cout << "Cards: ";

	SetConsoleCursorPosition(hCon, { 1, 4 });
	for (int i = 0; i < player.Cards.size(); i++) {
		if (player.Cards[i] == 9) cout << "Q" << " ";
		else if (player.Cards[i] == 10) cout << "K" << " ";
		else if (player.Cards[i] == 11) cout << "A" << " ";
		else cout << player.Cards[i] << " ";
	}

	SetConsoleCursorPosition(hCon, { 1, 8 });
	cout << player.getName() << ": " << player.getScore();

	// Инфо о диллере
	SetConsoleCursorPosition(hCon, { 28, 8 });
	cout << dealer.getName() << ": " << dealer.getScore();

	SetConsoleCursorPosition(hCon, { 28, 3 });
	cout << "Cards: ";

	SetConsoleCursorPosition(hCon, { 28, 4 });
	for (int i = 0; i < dealer.Cards.size(); i++) {
		// Скрытие первой карты диллера до паса игнрока (в разработке)
		/*if (i == 0) {
			cout << "?" << " ";
		}
		else {
			if (dealer.Cards[i] == 9) cout << "Q" << " ";
			else if (dealer.Cards[i] == 10) cout << "K" << " ";
			else if (dealer.Cards[i] == 11) cout << "A" << " ";
			else cout << dealer.Cards[i] << " ";
		}*/
		if (dealer.Cards[i] == 9) cout << "Q" << " ";
		else if (dealer.Cards[i] == 10) cout << "K" << " ";
		else if (dealer.Cards[i] == 11) cout << "A" << " ";
		else cout << dealer.Cards[i] << " ";
	}
}

void gameConsolePrint() {
	SetConsoleCursorPosition(hCon, { 1, 10 });
	cout << "Console: ";
	if (state == play) cout << "идет игра..";
	if (state == playerLose) cout << "победа диллера..";
	if (state == playerWin) cout << "победа игрока..";
	if (state == nobodyWin) cout << "ничья... И такое бывает..";
	if (state == newgame) cout << "начинается новая игра..";
	SetConsoleCursorPosition(hCon, { 1, 11 });
	cout << "1 - Ещё!\n";
	SetConsoleCursorPosition(hCon, { 1, 12 });
	cout << "2 - Хватит!\n";
	SetConsoleCursorPosition(hCon, { 1, 13 });
	cout << "0 - Выйти\n";

	SetConsoleCursorPosition(hCon, { 1, 14 });
	cout << "-> ";
}

void game() {
	int choice;

	

	SetConsoleCursorPosition(hCon, { 1, 10 });
	cout << "Console: \n";

	if (player.getBet() > player.getPoints()) {
		SetConsoleCursorPosition(hCon, { 1, 11 });
		cout << "Вы не можете столько поставить\n";
		return;
	}

	SetConsoleCursorPosition(hCon, { 1, 11 });
	cout << "Раздаю карты...\n";

	dealer.takeCard();
	player.takeCard();

	screenReload();
	printInfo();

	dealer.takeCard();
	player.takeCard();

	screenReload();
	printInfo();

	do
	{
		gameConsolePrint();
		cin >> choice;
		if (choice == 0) return;
		if (choice == 1) {
			screenReload();
			printInfo();
			gameConsolePrint();
			player.takeCard();
		}
		if (choice == 2) {
			state = stop;
			screenReload();
			printInfo();
			gameConsolePrint();
			checkGameState();
		}
	} while (state == play);

	if (state != play) {
		checkGameState();
		endGame();
	}
	if (state == newgame) {
		return;
	}
}

void dealerAI() {
	screenReload();
	printInfo();
	int dealerScore = dealer.getScore();
	int playerScore = player.getScore();

	if (dealerScore < playerScore) {
		dealer.takeCard();
	}
}

void checkGameState() {
	screenReload();
	printInfo();
	int dealerScore = dealer.getScore();
	int playerScore = player.getScore();

	if (playerScore > 21 && state == stop) {
		state = playerLose;
		//endGame();
		return;
	}

	else if (playerScore <= 21 && dealerScore > 21 && state == stop) {
		state = playerWin;
		//endGame();
		return;
	}

	else if (state == stop) {
		if (dealerScore < playerScore) {
			dealer.takeCard();
			return;
		}

		if (dealerScore > playerScore) {
			state = playerLose;
			//endGame;
			return;
		}

		if (dealerScore == playerScore) {
			state = nobodyWin;
			//endGame;
			return;
		}
	}

	//else if (state != play) dealerAI();
}

void endGame() {
	int playerBet = player.getBet();
	if (state == playerWin) {
		player.addPoints(playerBet);
	}

	if (state == playerLose) {
		player.removePoints(playerBet);
	}

	player.Cards.clear();
	dealer.Cards.clear();
}

void changebet() {
	screenReload();
	printInfo();
	int bet;
	SetConsoleCursorPosition(hCon, { 1, 10 });
	cout << "Console: ";
	cout << "На какое число вы хотите изменить ставку?";

	SetConsoleCursorPosition(hCon, { 1, 14 });
	cout << "-> ";
	cin >> bet;

	if (bet > player.getPoints()) {
		screenReload();
		printInfo();
		SetConsoleCursorPosition(hCon, { 1, 10 });
		cout << "Console: ";
		cout << "Вы не можете поставить больше чем у вас есть!";
	}
	else {
		screenReload();
		printInfo();
		SetConsoleCursorPosition(hCon, { 1, 10 });
		cout << "Console: ";
		cout << "Ставка была изменена!";
		player.chandeBet(bet);
	}
}

int main()	
{
	// Кодировки и настройки
	SetConsoleOutputCP(1251);
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(NULL));

	// Удаление курсора с экрана
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hCon, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hCon, &structCursorInfo);

	gameInit();
	int choice;

	// Menu
	do
	{
		screenReload();
		printInfo();

		//SetConsoleCursorPosition(hCon, { 1, 10 });
		//cout << "Console: ";
		/*if (state == play) cout << "идет игра..";
		if (state == playerLose) cout << "победа диллера..";
		if (state == playerWin) cout << "победа игрока..";
		if (state == nobodyWin) cout << "ничья... И такое бывает..";
		if (state == newgame) cout << "начинается новая игра..";*/
		SetConsoleCursorPosition(hCon, { 1, 11 });
		cout << "1 - Играть\n";
		SetConsoleCursorPosition(hCon, { 1, 12 });
		cout << "2 - Изменить ставку\n";
		SetConsoleCursorPosition(hCon, { 1, 13 });
		cout << "0 - Выйти\n";

		SetConsoleCursorPosition(hCon, { 1, 14 });
		cout << "-> ";
		cin >> choice;

		if (choice < 0 && choice > 2) {
		}

		if (choice == 1) {
			state = play;
			game();
		}
		if (choice == 2) changebet();
	} while (choice != 0);
}