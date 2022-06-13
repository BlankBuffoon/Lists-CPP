#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <ctime>

using namespace std;



// Тип данных отвещающий за правильную работу функцуий
// Тип игрока
typedef enum playerType {playerT, dealerT} playerType;
// Текущий статус игры
typedef enum gameState { stop, play, playerLose, playerWin, nobodyWin, newgame } gameState;
// Статус игры по умолчанию 
gameState state = play;


// Функции
void checkGameState();
void endGame();



// Класс данных игроков
class playerObj {
private:
	string Name = "Player1"; // Имя игрока
	int Points = NULL; // Кол-во его очков
	int Bet = NULL; // Размер его ставки
	int Score = NULL; // Сумма карт в его руке
	playerType pt = playerT; // Тип игрока (диллер или игрок)

public:
	vector<int> Cards; // Массив с картами в руке

	// Метод установки типа игрока
	void setPlayerType(playerType a) {
		pt = a;
	}

	// Метод инициализации
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

	// Метод взятия карты
	void takeCard() {
		Cards.push_back(rand() % (11 - 3) + 2);
		calcScore();
		checkGameState();
	}

	// Метод высчитывания очков
	void calcScore() {
		Score = 0;
		for (int i = 0; i < Cards.size(); i++) {
			Score += Cards[i];
		}
	}

	// Метод изменения ставки
	void chandeBet(int a) {
		Bet = a;
	}

	// Метод добавления очков
	void addPoints(int a) {
		Points += a;
	}

	// Метод убавления очков
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



// Функция инициализации игры
void gameInit() {
	// Меняем статус игры
	state = play;
	// Указываем тип игрока
	dealer.setPlayerType(dealerT);
	// Инициализируем объект
	dealer.playerInit();
	// Указываем тип игрока
	player.setPlayerType(playerT);
	// Инициализируем объект
	player.playerInit();
}



// Функция очистки экрана и отрисовки его заново
void screenReload() {
	// Очистить консоль вывода
	system("cls");
	cout << "========================================================\n";
	cout << "\n\n\n\n\n\n\n\n";
	cout << "========================================================\n";
	cout << "\n\n\n\n\n";
	cout << "========================================================\n";
}



// Функция вывода информации
void printInfo() {
	// Инфо о игроке
	// Ставка и очки
	SetConsoleCursorPosition(hCon, { 1, 1 });
	cout << "BET: " << player.getBet() << "\tPoints: " << player.getPoints();
	
	// Карты игрока
	SetConsoleCursorPosition(hCon, { 1, 3 });
	cout << "Cards: ";

	// Выводим карты
	SetConsoleCursorPosition(hCon, { 1, 4 });
	for (int i = 0; i < player.Cards.size(); i++) {
		if (player.Cards[i] == 9) cout << "Q" << " ";
		else if (player.Cards[i] == 10) cout << "K" << " ";
		else if (player.Cards[i] == 11) cout << "A" << " ";
		else cout << player.Cards[i] << " ";
	}

	// Вывод имени и счета
	SetConsoleCursorPosition(hCon, { 1, 8 });
	cout << player.getName() << ": " << player.getScore();

	// Инфо о диллере
	SetConsoleCursorPosition(hCon, { 28, 8 });
	cout << dealer.getName() << ": " << dealer.getScore();

	// Карты диллера
	SetConsoleCursorPosition(hCon, { 28, 3 });
	cout << "Cards: ";

	// Выводим карты
	SetConsoleCursorPosition(hCon, { 28, 4 });
	for (int i = 0; i < dealer.Cards.size(); i++) {
		if (dealer.Cards[i] == 9) cout << "Q" << " ";
		else if (dealer.Cards[i] == 10) cout << "K" << " ";
		else if (dealer.Cards[i] == 11) cout << "A" << " ";
		else cout << dealer.Cards[i] << " ";
	}
}



// Функция ввывода меню консоли во время игры
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
	cout << "2 - Пас\n";
	SetConsoleCursorPosition(hCon, { 1, 13 });
	cout << "0 - Выйти\n";

	SetConsoleCursorPosition(hCon, { 1, 14 });
	cout << "-> ";
}



// Главная функция игры
void game() {
	int choice;

	SetConsoleCursorPosition(hCon, { 1, 10 });
	cout << "Console: \n";

	Sleep(1000);
	SetConsoleCursorPosition(hCon, { 1, 11 });
	cout << "Раздаю карты...\n";

	// Взяли карты
	dealer.takeCard();
	player.takeCard();

	// Заново отрисовали интерфейс
	screenReload();
	printInfo();

	// Взяли карты
	dealer.takeCard();
	player.takeCard();

	// Заново отрисовали интерфейс
	screenReload();
	printInfo();

	do
	{
		// Отрисовываем меню консоли во врмея игры
		gameConsolePrint();
		cin >> choice;
		if (choice == 0) return;
		// Если игрок выбрал взять карту
		if (choice == 1) {
			// Перезагружаем интерфейс
			screenReload();
			printInfo();
			gameConsolePrint();
			// Берем карту
			player.takeCard();
		}
		// Если выбрал остановиться
		if (choice == 2) {
			// Меняем статус игры
			state = stop;
			// Перезагружаем интерфейс
			screenReload();
			printInfo();
			gameConsolePrint();
			// Проверяем статус игры
			checkGameState();
		}
	} while (state == play);

	// Если игра была остановлена
	if (state != play) {
		checkGameState();
		endGame();
	}
}



// Проферяем статус игры
void checkGameState() {
	screenReload();
	printInfo();

	// Получаем очки
	int dealerScore = dealer.getScore();
	int playerScore = player.getScore();

	// Если у игрока перебор
	if (playerScore > 21 && state == stop) {
		state = playerLose;
		return;
	}

	// Если у диллера перебор
	else if (playerScore <= 21 && dealerScore > 21 && state == stop) {
		state = playerWin;
		return;
	}

	// Если у игрока нет перебора, то
	else if (state == stop) {
		// Диллер добирает
		if (dealerScore < playerScore) {
			dealer.takeCard();
			return;
		}

		// Диллер побеждает
		if (dealerScore > playerScore) {
			state = playerLose;
			return;
		}

		// Ничья
		if (dealerScore == playerScore) {
			state = nobodyWin;
			return;
		}
	}
}



// Функция завешения игры
void endGame() {
	// Получаем ставку игрока
	int playerBet = player.getBet();

	// Добавляем очки при победе
	if (state == playerWin) {
		player.addPoints(playerBet);
	}

	// Отнимаем очки при поражении
	if (state == playerLose) {
		player.removePoints(playerBet);
	}

	// Задержка чтобы можно было посмотреть карты перед завершением игры
	Sleep(4000);
	// Очищаем массивы с картами игроков
	player.Cards.clear();
	dealer.Cards.clear();
}



// Функция изменения ставки игрока
void changebet() {
	// Очищаем и отрисовываем экран и инфо
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
		Sleep(2000);
	}
	else {
		screenReload();
		printInfo();
		SetConsoleCursorPosition(hCon, { 1, 10 });
		cout << "Console: ";
		cout << "Ставка была изменена!";
		player.chandeBet(bet);
		Sleep(2000);
	}
}



int main()	
{
	// Кодировки и настройки
	// Русские символы в консоли
	setlocale(0, "");
	// Привязываем hCon к нашему окну вывода
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	// Настраиваем рандом
	srand(time(NULL));

	// Удаление курсора с экрана
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hCon, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hCon, &structCursorInfo);

	// Инициализируем игру
	gameInit();

	int choice;

	// Menu
	do
	{
		// Очищаем экран и отрисовываем его
		screenReload();
		// Выводи информацию на экран
		printInfo();

		SetConsoleCursorPosition(hCon, { 1, 10 });
		cout << "Console: ";
		if (state == play) cout << "идет игра..";
		if (state == playerLose) cout << "победа диллера..";
		if (state == playerWin) cout << "победа игрока..";
		if (state == nobodyWin) cout << "ничья... И такое бывает..";
		if (state == newgame) cout << "начинается новая игра..";
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