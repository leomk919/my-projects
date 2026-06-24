// The code was written by me on 2026/6/1, rewritten once, and modified only once.
#include <iostream>
#include <string>
using namespace std;
enum enLevelQuestions { Easy = 1, Med = 2, Hard = 3, MixLevel = 4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, Mix = 5 };
struct stRoundInfo
{
	int num1 = 0;
	int num2 = 0;
	char OpType;
	int userAnswer = 0;
	int RightAnswer = 0;
};
struct stGameInfo
{
	short NumberOfQuestion = 0;
	enLevelQuestions LevelQuestions;
	string NameLevel = "";
	enOperationType OperationType;
	string NameOperation = "";
	short NumberOfCorrectAnswer = 0;
	short NumberOfIncorrectAnswer = 0;
};
int RandomNumber(int from, int to)
{
	int num = rand() % (to - from + 1) + from;
	return num;
}
int ReadNumber()
{
	int num;
	cin >> num;
	return num;
}
enLevelQuestions ReadLevelQuestions()
{
	short num = 0;
	do
	{
		cout << "Please Enter Question Level [1]: Easy, [2]: Mid, [3]: Hard, [4]: Mix\n";
		cin >> num;
	} while (num > 4 || num < 0);
	return enLevelQuestions(num);
}
string NameLevel(enLevelQuestions LevelQuestions)
{
	string NameLevel[4] = { "Easy", "Med", "Hard", "Mix" };
	return NameLevel[LevelQuestions - 1];
}
enOperationType ReadOperationType()
{
	short num;
	do
	{
		cout << "Enter Opreation type [1]: Add, [2]: Sud, [3]: Mul, [4]: Div, [5]: Mix\n";
		cin >> num;
	} while (num > 5 || num < 0);
	return (enOperationType)num;
}
string NameOpreation(enOperationType OperationType)
{
	string NameOpreation[5] = { "Add", "Sub", "Mul", "Div", "Mix" };
	return NameOpreation[OperationType - 1];
}
stRoundInfo Fill2NumberRandomly(enLevelQuestions LevelQuestions)
{
	stRoundInfo RoundInfo;
	if (LevelQuestions == MixLevel)
	{
		LevelQuestions = enLevelQuestions(RandomNumber(1, 3));
	}
	switch (LevelQuestions)
	{
	case Easy:
		RoundInfo.num1 = RandomNumber(1, 10);
		RoundInfo.num2 = RandomNumber(1, 10);
		break;
	case Med:
		RoundInfo.num1 = RandomNumber(10, 50);
		RoundInfo.num2 = RandomNumber(10, 50);
		break;
	case Hard:
		RoundInfo.num1 = RandomNumber(50, 100);
		RoundInfo.num2 = RandomNumber(50, 100);
		break;
	}
	return RoundInfo;
}
stRoundInfo RightAnswer(stRoundInfo RoundInfo, enOperationType OperationType)
{
	if (OperationType == Mix)
	{
		OperationType = enOperationType(RandomNumber(1, 4));
	}
	switch (OperationType)
	{
	case Add:
		RoundInfo.RightAnswer = RoundInfo.num1 + RoundInfo.num2;
		RoundInfo.OpType = '+';
		break;
	case Sub:
		RoundInfo.RightAnswer = RoundInfo.num1 - RoundInfo.num2;
		RoundInfo.OpType = '-';
		break;
	case Mul:
		RoundInfo.RightAnswer = RoundInfo.num1 * RoundInfo.num2;
		RoundInfo.OpType = '*';
		break;
	case Div:
		RoundInfo.RightAnswer = RoundInfo.num1 / RoundInfo.num2;
		RoundInfo.OpType = '/';
		break;
	}
	return RoundInfo;
}
bool IsUserAnswerCorrect(stRoundInfo RoundInfo)
{
	return (RoundInfo.RightAnswer == RoundInfo.userAnswer);
}
void ScreenColor(bool IsCorrect)
{
	if (IsCorrect)
		system("color 2F");
	else
	{
		system("color 4F");
		cout << "\a";
	}
}
void ResetScreen()
{
	system("cls");
	system("color 0F");
}
stRoundInfo PrintRoundInfo(stRoundInfo RoundInfo)
{
	cout << "\n" << RoundInfo.num1 << endl << RoundInfo.num2 << "  " << RoundInfo.OpType << endl;
	cout << "-----------------------------------------------\n";
	cin >> RoundInfo.userAnswer;
	cout << endl;
	return RoundInfo;
}
void PrintGameInfo(stGameInfo GameInfo)
{
	cout << "\n-----------------------------------------------\n";
	if (GameInfo.NumberOfCorrectAnswer >= GameInfo.NumberOfIncorrectAnswer)
	{
		cout << "\t    Final Results Is Pass\n";
		ScreenColor(true);
	}
	else
	{
		cout << "\t    Final Results Is Fail\n";
		ScreenColor(false);
	}
	cout << "-----------------------------------------------\n";
	cout << "Number Of Questions :" << GameInfo.NumberOfQuestion << endl;
	cout << "Questions Level     :" << GameInfo.NameLevel << endl;
	cout << "Operation Type      :" << GameInfo.NameOperation << endl;
	cout << "Number Of Right Answer :" << GameInfo.NumberOfCorrectAnswer << endl;
	cout << "Number Of Wrong Answer :" << GameInfo.NumberOfIncorrectAnswer << endl;
	cout << "-----------------------------------------------\n";
}
void PlayMathGAme()
{
	string text;
	bool IsCorrect = {};
	stGameInfo GameInfo;
	cout << "Please Enter a Number Of Question\n";
	GameInfo.NumberOfQuestion = ReadNumber();
	GameInfo.LevelQuestions = ReadLevelQuestions();
	GameInfo.NameLevel = NameLevel(GameInfo.LevelQuestions);
	GameInfo.OperationType = ReadOperationType();
	GameInfo.NameOperation = NameOpreation(GameInfo.OperationType);
	for (int i = 1; i <= GameInfo.NumberOfQuestion; i++)
	{
		stRoundInfo RoundInfo = {};
		RoundInfo = Fill2NumberRandomly(GameInfo.LevelQuestions);
		RoundInfo = RightAnswer(RoundInfo, GameInfo.OperationType);
		cout << "Question [" << i << "/" << GameInfo.NumberOfQuestion << "]:\n";
		RoundInfo = PrintRoundInfo(RoundInfo);
		IsCorrect = IsUserAnswerCorrect(RoundInfo);
		ScreenColor(IsCorrect);
		if (IsCorrect)
		{
			cout << "Correct Answer\n\n";
			GameInfo.NumberOfCorrectAnswer++;
		}
		else
		{
			cout << "Incorrect Answer\n\n";
			cout << "The Correct Answer is :" << RoundInfo.RightAnswer << endl;

			GameInfo.NumberOfIncorrectAnswer++;
		}

	}
	cout << "To see the game results, please press Enter .....";
	cin.ignore();
	getline(cin, text);
	PrintGameInfo(GameInfo);
}
void StartGame()
{
	char addMore = 'n';
	do
	{
		PlayMathGAme();
		cout << "do you want to Play Again? Y/N\n";
		cin >> addMore;
		ResetScreen();
	} while (addMore == 'Y' || addMore == 'y');
}
int main()
{
	srand((unsigned)time(NULL));
	StartGame();
}