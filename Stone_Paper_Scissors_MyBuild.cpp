#include <iostream>
using namespace std;
enum enGameChoice {Stone = 1, Paper = 2, Scissors = 3};
enum enWinnerName {Player = 1, Computer = 2, Draw = 3};
struct stRoundInfo 
{
	short RoundNumber;
	enGameChoice PlayerChoies;
	enGameChoice ComputerChoies;
	enWinnerName Winner;
	string WinnerName;
};
struct stGameInfo 
{
	short NumberRound;
	short PlayerWonTimes;
	short ComputerWonTimes;
	short DrawTimes;
	enWinnerName Winner;
	string WinnerName;
};
int RandomNumber(int from, int to)
{
	int num = rand() % (to - from + 1) + from;
	return num;
}
string NameWinner(enWinnerName winnerName)
{
	string arrWinnerName[3] = { "Player", "Computer", "Draw" };
	return arrWinnerName[winnerName - 1];
}
enWinnerName RoundWinner(stRoundInfo RoundInfo)
{
	if (RoundInfo.ComputerChoies == RoundInfo.PlayerChoies)
		return Draw;
	switch (RoundInfo.PlayerChoies)
	{
	case Stone:
		if (RoundInfo.ComputerChoies == Paper)
			return Computer;
		break;
	case Paper:
		if (RoundInfo.ComputerChoies == Scissors)
			return Computer;
		break;
	case Scissors:
		if (RoundInfo.ComputerChoies == Stone)
			return Computer;
		break;
	}
	return Player;
}
string ChoiceName(enGameChoice GameChoice)
{
	string arrGameChoice[3] = {"Stone", "Paper" , "Scissors"};
	return arrGameChoice[GameChoice - 1];
}
void SetWinnerScreenColor(enWinnerName WinnerName)
{
	switch (WinnerName)
	{
	case Player:
		system("color 2F");
		break;
	case Computer :
		system("color 4F");
		cout << "\a";
		break;
	default:
		system("color 6F");
	}
}
void PrintRoundInfo(stRoundInfo RoundInfo)
{
	cout << "-----------------------------[Round " << RoundInfo.RoundNumber << "] --------------------------\n\n";
	cout << "Player Choies   :" << ChoiceName(RoundInfo.PlayerChoies) << endl;
	cout << "Computer Choies :" << ChoiceName(RoundInfo.ComputerChoies) << endl;
	cout << "Round Winner    :" << RoundInfo.WinnerName << endl;
	cout << "------------------------------------------------------------------\n\n";
	SetWinnerScreenColor(RoundInfo.Winner);
}
enWinnerName NameWinnerInGame(stGameInfo GameInfo)
{
	if (GameInfo.ComputerWonTimes < GameInfo.PlayerWonTimes)
		return Player;
	else if (GameInfo.ComputerWonTimes > GameInfo.PlayerWonTimes)
		return Computer;
	else return Draw;
}
stGameInfo FillGameInfo (short NumberRound, short PlayerWonTimes, short ComputerWonTimes, short DrawTimes)
{
	stGameInfo GameInfo;
	GameInfo.NumberRound = NumberRound;
	GameInfo.PlayerWonTimes = PlayerWonTimes;
	GameInfo.ComputerWonTimes = ComputerWonTimes;
	GameInfo.DrawTimes = DrawTimes;
	GameInfo.Winner = NameWinnerInGame(GameInfo);
	GameInfo.WinnerName = NameWinner(GameInfo.Winner);
	return GameInfo;
}
enGameChoice ReadPlayerChoice(short NumberRound)
{
	short num;
	cout << "Round [" << NumberRound << "] begins :\n";
	cout << "Your Choies : [1]: Stone, [2]: Paper, [3]: Scissors?\n";
	cin >> num;
	cout << "\n";
	return enGameChoice(num);
}
enGameChoice GetComputerOption()
{
	return enGameChoice(RandomNumber(1, 3));
}
stGameInfo PlayGame(short NumberRound)
{
	stRoundInfo RoundInfo;
	short PlayerWonTimes = 0, ComputerWonTimes = 0, DrawTimes = 0;
	for (int i = 1; i <= NumberRound; i++)
	{
		RoundInfo.PlayerChoies = ReadPlayerChoice(i);
		RoundInfo.ComputerChoies = GetComputerOption();
		RoundInfo.RoundNumber = i;
		RoundInfo.Winner = RoundWinner(RoundInfo);
		RoundInfo.WinnerName = NameWinner(RoundInfo.Winner);
		PrintRoundInfo(RoundInfo);
		if (RoundInfo.Winner == Player)
			PlayerWonTimes++;
		else if (RoundInfo.Winner == Computer)
			ComputerWonTimes++;
		else DrawTimes++;
	}
	return FillGameInfo(NumberRound, PlayerWonTimes, ComputerWonTimes, DrawTimes);
}
string Taps(short NumberOfTaps)
{
	string tap = "";
	for (int i = 1; i <= NumberOfTaps; i++)
	{
		tap += "\t";
	}
	return tap;
}
void PrintGameOver()
{
	cout << Taps(3) << "----------------------------------------------------------\n\n";
	cout << Taps(5) << "      +++ Game Over +++ " << Taps(3) << "\n\n";
	cout << Taps(3) << "----------------------------------------------------------\n\n";
}
void PrintResultGame(stGameInfo GameInfo)
{
	cout << Taps(3) << "----------------------[Game  Result]----------------------\n\n";
	cout << Taps(3) << "Game Round :" << GameInfo.NumberRound << endl;
	cout << Taps(3) << "Player won Times:" << GameInfo.PlayerWonTimes << endl;
	cout << Taps(3) << "Computer won Times:" << GameInfo.ComputerWonTimes << endl;
	cout << Taps(3) << "Draw Times :" << GameInfo.DrawTimes << endl;
	cout << Taps(3) << "Final Winner :" << GameInfo.WinnerName << endl;
	cout << Taps(3) << "----------------------------------------------------------\n\n";
}
short ReadNumberOfRounds()
{
	short num = 0;
	do
	{
		cout << "How Many Rounds 1 to 10 ?\n";
		cin >> num;
	} while (num > 10 || num < 1);
	return num;
}
void ResetScreen()
{
	system("cls");
	system("color 0F");
}
void StartPlay()
{
	char PlayMore;
	do
	{
		ResetScreen();
		stGameInfo GameInfo = PlayGame(ReadNumberOfRounds());
		PrintGameOver();
		PrintResultGame(GameInfo);
		cout << Taps(3) << "do you want to play agin ? Y/N ";
		cin >> PlayMore;
	} while (PlayMore == 'Y' || PlayMore == 'y');
}
int main()
{
	srand((unsigned)time(NULL));
	StartPlay();
}