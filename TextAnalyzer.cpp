#include <iostream>
#include "MyIo.h"
using namespace std;
struct stTextInfo
{
	string text = "";
	short unsigned NumberOfWord = 0;
	short unsigned NumberOfChar = 0;
	short unsigned NumberOfUppercaseLetters = 0;
	short unsigned NumberOfLowerCaseLetters = 0;
	short unsigned NumberOfSpecialChar = 0;
	short unsigned UnknownCharsCount = 0;
	short unsigned NumberOfSpace = 0;
	string ReversText = "";
};
short unsigned NumberOfWord(string Text)
{
	short unsigned NumberOfWord = 0;
	for (int i = 0; i <= Text.length() - 1; i++)
	{
		if (Text[i] == ' ')
		{
			NumberOfWord++;
		}
	}
	return NumberOfWord;
}
short unsigned NumberOfChar(string Text)
{
	short unsigned NumberOfChar = 0;
	for (int i = 0; i <= Text.length() - 1; i++)
	{
		if (int(Text[i]) >=  32 && int(Text[i]) <= 255)
		{
			NumberOfChar++;
		}
	}
	return NumberOfChar;
}
short unsigned NumberOfUppercaseLetters(string Text)
{
	short unsigned NumberOfUppercaseLetters = 0;
	for (int i = 0; i <= Text.length() - 1; i++)
	{
		if (int(Text[i]) >= 65 && int(Text[i]) <= 90)
		{
			NumberOfUppercaseLetters++;
		}
	}
	return NumberOfUppercaseLetters;
}
short unsigned NumberOfLowerCaseLetters(string Text)
{
	short unsigned NumberOfLowerCaseLetters = 0;
	for (int i = 0; i <= Text.length() - 1; i++)
	{
		if (int(Text[i]) >= 97 && int(Text[i]) <= 122)
		{
			NumberOfLowerCaseLetters++;
		}
	}
	return NumberOfLowerCaseLetters;
}
short unsigned getSpecialCharsCount(string Text)
{
	short unsigned NumberOfSpecialChar = 0;
	for (int i = 0; i <= Text.length() - 1; i++)
	{
		if ((int(Text[i]) > 32 && int(Text[i]) <= 47)||
			(int(Text[i]) >= 58 && int(Text[i]) <= 64)||
			(int(Text[i]) >= 91 && int(Text[i]) <= 96)||
			(int(Text[i]) >= 123 && int(Text[i]) <= 126))
		{
			NumberOfSpecialChar++;
		}
	}
	return NumberOfSpecialChar;
}
short unsigned countUnknownChars(string Text)
{
	short unsigned UnknownCharsCount = 0;
	for (int i = 0; i <= Text.length() - 1; i++)
		{
		if (int(Text[i]) > 126 && int(Text[i]) < 32)
				UnknownCharsCount++;
		}
		return UnknownCharsCount;
} 
short unsigned NumberOfSpace(string Text)
{
	short unsigned NumberOfSpace = 0;
	for (int i = 0; i <= Text.length() - 1; i++)
	{
		if (Text[i] == ' ')
			NumberOfSpace++;
	}
	return NumberOfSpace;
}
string ReversText(string Text)
{
	string ReversText = "";
	for (int i = Text.length() - 1; i >= 0; i--)
	{
		ReversText += Text[i];
	}
	return ReversText;
}
stTextInfo FillInfo()
{
	stTextInfo TextInfo = {};
	TextInfo.text = Input::PrintMessageAndReadText("Please Enter Text Here");
	TextInfo.NumberOfWord = NumberOfWord(TextInfo.text);
	TextInfo.NumberOfChar = NumberOfChar(TextInfo.text);
	TextInfo.NumberOfUppercaseLetters = NumberOfUppercaseLetters(TextInfo.text);
	TextInfo.NumberOfLowerCaseLetters = NumberOfLowerCaseLetters(TextInfo.text);
	TextInfo.NumberOfSpecialChar = getSpecialCharsCount(TextInfo.text);
	TextInfo.UnknownCharsCount = countUnknownChars(TextInfo.text);
	TextInfo.NumberOfSpace = NumberOfSpace(TextInfo.text);
	TextInfo.ReversText = ReversText(TextInfo.text);
	return TextInfo;
}
void PrintInfo()
{
	stTextInfo TextInfo = {};
	TextInfo = FillInfo();
	cout << "Press any key to display information....";
	string S = "";
	getline(cin, S);
	Helpers::ResetScreen();
	printf("The word count is:%d\n", TextInfo.NumberOfWord);
	printf("The character count is:%d\n", TextInfo.NumberOfChar);
	printf("The uppercase letter count is:%d\n", TextInfo.NumberOfUppercaseLetters);
	printf("The lowercase letter count is:%d\n", TextInfo.NumberOfLowerCaseLetters);
	printf("The special character count is:%d\n", TextInfo.NumberOfSpecialChar);
	printf("The unknown character count is:%d\n", TextInfo.UnknownCharsCount);
	printf("The space count is:%d\n", TextInfo.NumberOfSpace);
	cout << "The reversed text is:\n\n" << TextInfo.ReversText << endl;
}
int main()
{
	PrintInfo();
}