// تم الانتهاء بعد كتابة حوالي 10 ساعات وتم انهائه بتاريخ 2026/6/22  💪
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "MyIO.h"
using namespace std;

struct sClientsData
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string NumberPhone = "";
	double AccountBalance = 0;
	bool MarkForDelete = false;
	bool MarkForUpdate = false;

};

vector <string> SplitString(string line, string Delim)
{
	size_t pos;
	string word; 
	vector <string> vWords;
	while ((pos = line.find(Delim)) != string::npos)
	{
		word = line.substr(0,pos);
		vWords.push_back(word);
		line.erase(0, pos + Delim.length());
	}
	if (line != "")
	{
		vWords.push_back(line);
	}
	return vWords;
}

string ConvertRecordToLine(sClientsData info, string Dilem)
{
	string S1 = info.AccountNumber + Dilem;
	S1 += info.PinCode + Dilem;
	S1 += info.Name + Dilem;
	S1 += info.NumberPhone + Dilem;
	S1 += to_string(info.AccountBalance);
	return S1;
}

sClientsData ConvertLineToRecord(vector <string> &Data)
{
	sClientsData AccountInfo = {};
	if(Data.size() == 5)
	{
		AccountInfo.AccountNumber = Data[0];
		AccountInfo.PinCode = Data[1];
		AccountInfo.Name = Data[2];
		AccountInfo.NumberPhone = Data[3];
		AccountInfo.AccountBalance = stod(Data[4]);
	}
	return AccountInfo;
}

sClientsData FillDataForAccount()
{
	sClientsData info = {};
	cout << "Enter Account Number\n";
	getline(cin >> ws , info.AccountNumber);
	info.PinCode = Input::PrintMessageAndReadText("Enter Pin Code");
	info.Name = Input::PrintMessageAndReadText("Enter Name");
	info.NumberPhone = Input::PrintMessageAndReadText("Enter Number Phone");
	info.AccountBalance = Input::ReadNumber("Enter Account Balance");
	return info;
}

bool IsFind(string AccountNumber, vector <sClientsData>& ClientData, sClientsData& AccoundData)
{
	for (sClientsData& Temp : ClientData)
	{
		if (Temp.AccountNumber == AccountNumber)
		{
			AccoundData = Temp;
			return true;
		}
	}
	return false;
}

vector <string> LoadInfoFromFile(string FileName)
{
	vector <string> vData;
	fstream File;
	File.open(FileName, ios::in);
	if (File.is_open())
	{
		string Line;
		while (getline(File, Line))
		{
			if (Line != "")
			vData.push_back(Line);
		}
		File.close();
	}
	return vData;
}

void PrintTableHeader(vector <sClientsData> vClientData)
{
	if (vClientData.size() < 3)
	{
		cout << right << setw(50) << string(40, '-') << "Client List (" << vClientData.size() << ") client" << left << setw(45) << string(40, '-') << endl;
	}
	else
	{
		cout << right << setw(48) << string(40, '-') << "Client List (" << vClientData.size() << ") clients" << left << setw(45) << string(40, '-') << endl;
	}
	cout << string(120, '-') << "\n";
	cout << left
		<< "| " << setw(20) << "Account Number"
		<< "| " << setw(15) << "Pin Code"
		<< "| " << setw(30) << "Client Name"
		<< "| " << setw(20) << "Phone"
		<< "| " << fixed << setprecision(2) << "Balance" << "\n";
	cout << string(120, '-') << "\n";
}

void PrintClientRow(vector <sClientsData>& vClientData)
{
	for (sClientsData& client : vClientData)
	{
		cout << left
			<< "| " << setw(20) << client.AccountNumber
			<< "| " << setw(15) << client.PinCode
			<< "| " << setw(30) << client.Name
			<< "| " << setw(20) << client.NumberPhone
			<< "| " << fixed << setprecision(2) << client.AccountBalance << "\n";
	}
	cout << string(120, '-') << "\n";

}

void ClientList(vector <sClientsData> vClientData)
{
	PrintTableHeader(vClientData);
	PrintClientRow(vClientData);
}

void PrintClientsList(vector <string> info)
{
	vector <string> vClientData;
	vector <sClientsData> vData = {};
	sClientsData TempData = {};
	for (string &temp : info)
	{
		vClientData = SplitString(temp,"#//#");
		TempData = ConvertLineToRecord(vClientData);
		vData.push_back(TempData);
	}
	ClientList(vData);

}

bool AccountNumberExists(vector <string> InfoFromFile, string AccountNumber)
{
	vector <string> vInfoInLine;
	sClientsData info = {};
	vector <sClientsData> vClientsData;
	for (string temp : InfoFromFile)
	{
		vInfoInLine = SplitString(temp, "#//#");
		info = ConvertLineToRecord(vInfoInLine);
		if (info.AccountNumber == AccountNumber)
			return true;
	}		
	return false;
}

sClientsData AddNew(vector <string> info)
{
	sClientsData TempData = {};
	
	int i = 0;
	do
	{
		if (i == 0)
			cout << "Enter Account Number\n";
		else
			cout << "Enter a different account number\n";
		i++;
		getline(cin >> ws, TempData.AccountNumber);
	} while(AccountNumberExists(info, TempData.AccountNumber));
	TempData.PinCode = Input::PrintMessageAndReadText("Enter Pin Code");
	TempData.Name = Input::PrintMessageAndReadText("Enter Name");
	TempData.NumberPhone = Input::PrintMessageAndReadText("Enter Number Phone");
	TempData.AccountBalance = Input::ReadNumber("Enter Account Balance");
	return TempData;
}

void AddNewClientToFile(string FileName,vector <string> info)
{
	fstream File;
	sClientsData NewInfoForNewAccount = AddNew(info);
	File.open(FileName, ios::app);
	if (File.is_open())
	{
		File << ConvertRecordToLine(NewInfoForNewAccount, "#//#") << endl;
		File.close();
	}
}

void AddNewClients(string FileName, vector <string> info)
{
	char answer = 'N';
	do
	{
		AddNewClientToFile(FileName, info);
		cout << "Client Added Successfully, Do you want to add more clients? Y/N\n";
		cin >> answer;
	} while (tolower(answer) == 'y');
	
}

void PrintInfoForAccount(sClientsData info)
{
	cout << string(30, '=') << endl;
	cout << "Account Number  : " << info.AccountNumber << endl;
	cout << "Pin Code        : " << info.PinCode << endl;
	cout << "Client Name     : " << info.Name << endl;
	cout << "Number Phone    : " << info.NumberPhone << endl;
	cout << "Account Balance : " << info.AccountBalance << endl;
	cout << string(30, '=') << endl;
}

bool MarkForDelete(string AccountNumber, vector <sClientsData> &vClientData)
{
	for (sClientsData &Temp : vClientData)
	{
		if (Temp.AccountNumber == AccountNumber)
		{
			Temp.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

void SaveInfoFromFile(string FileName, vector <sClientsData> &DataClient)
{
	fstream File;
	File.open(FileName, ios::out);
	if (File.is_open())
	{
		for (sClientsData &Temp : DataClient)
		{
			if (!Temp.MarkForDelete)
			{
				File << ConvertRecordToLine(Temp, "#//#") << endl;
			}
		}
		File.close();
	}
}

void DeletAccountFromData(string FileName,vector <string> &infoFromFile, string AccountNumber)
{
	vector <string> info;
	sClientsData S = {}, S2 = {};
	vector <sClientsData> vDataClient;
	for (string &Temp : infoFromFile)
	{
		info = SplitString(Temp, "#//#");
		S = ConvertLineToRecord(info);
		vDataClient.push_back(S);
	}
	if (IsFind(AccountNumber, vDataClient, S2))
	{
		PrintInfoForAccount(S2);
		cout << "Are you sure you want delete this client ? Y/N\n";
		char answer;
		cin >> answer;
		if (toupper(answer) == 'Y')
		{
			MarkForDelete(AccountNumber, vDataClient);
			SaveInfoFromFile(FileName, vDataClient);
			cout << "Client Delete Successfully.";
		}
	}
	else
		cout << "Client With Account Number (" + AccountNumber + ") is Not Found!\n";
}

void refreshAccountInfo(sClientsData &info)
{
	info.AccountNumber = info.AccountNumber;
	cout << "Enter Pin Code\n";
	getline(cin >> ws, info.PinCode);
	info.Name = Input::PrintMessageAndReadText("Enter Name");
	info.NumberPhone = Input::PrintMessageAndReadText("Enter Number Phone");
	info.AccountBalance = Input::ReadNumber("Enter Account Balance");

}

bool MarkForUpdate(string AccountNumber, vector <sClientsData>& vClientData)
{
	for (sClientsData& Temp : vClientData)
	{
		if (Temp.AccountNumber == AccountNumber)
		{
			Temp.MarkForUpdate = true;
			return true;
		}
	}
	return false;
}

void SaveInfoFromFile(string FileName, vector <sClientsData>& DataClient)
{
	fstream File;
	File.open(FileName, ios::out);
	if (File.is_open())
	{
		for (sClientsData& Temp : DataClient)
		{
			if (Temp.MarkForUpdate)
				  refreshAccountInfo(Temp);
			File << ConvertRecordToLine(Temp, "#//#") << endl;
		}
		File.close();
	}
}

void UpdateAccount(string FileName, vector <string>& infoFromFile, string AccountNumber)
{
	vector <string> info;
	sClientsData S = {}, S2 = {};
	vector <sClientsData> vDataClient;
	for (string& Temp : infoFromFile)
	{
		info = SplitString(Temp, "#//#");
		S = ConvertLineToRecord(info);
		vDataClient.push_back(S);
	}
	if (IsFind(AccountNumber, vDataClient, S2))
	{
		PrintInfoForAccount(S2);
		char answer = 'a';
		cout << "\nAre you sure you want update this client ? Y/N\n";
		cin >> answer;
		if (tolower(answer) == 'y')
		{
			MarkForUpdate(AccountNumber, vDataClient);
			SaveInfoFromFile(FileName, vDataClient);
			cout << "Client Update Successfully.";
		}
	}
	else
		cout << "Client With Account Number (" + AccountNumber + ") is Not Found!\n";
}

void PrintClientDataByAccountNumber(vector <string> infoFromFile, string AccountNumber)
{
	vector <string> info;
	sClientsData S = {}, S2 = {};
	vector <sClientsData> vDataClient;
	for (string& Temp : infoFromFile)
	{
		info = SplitString(Temp, "#//#");
		S = ConvertLineToRecord(info);
		vDataClient.push_back(S);
	}
	if (IsFind(AccountNumber, vDataClient, S2))
	{
		PrintInfoForAccount(S2);
	}
	else
	{
		cout << "Account number (" + AccountNumber + ") does not exist!";
	}
}

void PrintMainMenuScreen()
{
	cout << string(36, '=') << endl;
	cout << "\t  Main Menu Sreen" << endl;
	cout << string(36, '=') << endl;
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Exit.\n";
	cout << string(36, '=') << endl;

}

void Pause()
{
	cout << "\n\nPress any key to go back to main Menue...";
	system("pause>0");
}

void ClientListScreen(vector <string> infoFromFile)
{
	Helpers::ResetScreen();
	PrintClientsList(infoFromFile);
	Pause();
	Helpers::ResetScreen();
}

void AddNewClientsScreen(string FileName,vector <string> infoFromFile)
{
	Helpers::ResetScreen();
	cout << string(36, '-') << endl;
	cout << "\tAdd New Clients Screen\n";
	cout << string(36, '-') << endl;;
	AddNewClients(FileName, infoFromFile);
	Pause();
	Helpers::ResetScreen();
}

void DeleteClientsScreen(string FileName,vector <string> infoFromFile)
{
	Helpers::ResetScreen();
	cout << string(36, '-') << endl;
	cout << "\tDelete Clients Screen\n";
	cout << string(36, '-') << endl;
	cout << "please enter account Number\n";
	string AccountNumber = "";
	getline(cin >> ws, AccountNumber);
	DeletAccountFromData(FileName,infoFromFile, AccountNumber);
	Pause();
	Helpers::ResetScreen();
}

void UpdateClientsInfoScreen(string FileName, vector <string> infoFromFile)
{
	Helpers::ResetScreen();
	cout << string(36, '-') << endl;
	cout << "    Update Clients Info Screen\n";
	cout << string(36, '-') << endl;
	cout << "please enter account Number\n";
	string AccountNumber = "";
	getline(cin >> ws, AccountNumber);
	UpdateAccount(FileName, infoFromFile, AccountNumber);
	Pause();
	Helpers::ResetScreen();
}

void FindClientScreen(string FileName, vector <string> infoFromFile)
{
	Helpers::ResetScreen();
	cout << string(36, '-') << endl;
	cout << "\tFind Client Screen\n";
	cout << string(36, '-') << endl;
	string AccountNumber = "";
	cout << "please enter account Number\n";
	getline(cin >> ws, AccountNumber);
	PrintClientDataByAccountNumber(infoFromFile, AccountNumber);
	Pause();
	Helpers::ResetScreen();
}

enum enMainMenuOption
{
	ListClient = 1, AddNewClient = 2, DeleteClient = 3,
	UpDateClient = 4, FindClient = 5, Exit = 6
};

void EndScreen()
{
	Helpers::ResetScreen();
	cout << string(36, '-') << endl;
	cout << "\t  Program Ends :-)\n";
	cout << string(36, '-') << endl;
	system("pause>0");
}

int Bank(string FileName)
{
	PrintMainMenuScreen();
	int num = 0;
	do
	{
		cout << "Choose what do you want to do [1 to 6]?\n";
		cin >> num;
	} while (num > 6 || num < 1);
	enMainMenuOption option = enMainMenuOption(num);
	vector <string> infoFromFile = LoadInfoFromFile(FileName);
	switch (option)
	{
	case ListClient:
	{
		ClientListScreen(infoFromFile);
		break;
	}
	case AddNewClient:
	{
		AddNewClientsScreen(FileName, infoFromFile);
		break;
	}
	case DeleteClient:
	{
		DeleteClientsScreen(FileName, infoFromFile);
		break;
	}
	case UpDateClient:
	{
		UpdateClientsInfoScreen(FileName, infoFromFile);
		break;
	}
	case FindClient:
	{
	
		FindClientScreen(FileName, infoFromFile);
		break;
	}
	case Exit :
		EndScreen();
	}
	return num;
}

void BankApp(string FileName)
{
	int num = 0;
	do
	{
		num = Bank(FileName);
	} while (num >= 1 && num < 6);
}

int main()
{
	BankApp("MkFile.txt"); 
}
