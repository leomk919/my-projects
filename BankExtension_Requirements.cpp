// تم تعديل المشروع بتاريخ 2026/22/6 واستغرق حوالي 5 ساعات
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "MyIO.h"
using namespace std;

const string Delimiter = "#//#";

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
		word = line.substr(0, pos);
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

sClientsData ConvertLineToRecord(vector <string>& Data)
{
	sClientsData AccountInfo = {};
	if (Data.size() == 5)
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
	getline(cin >> ws, info.AccountNumber);
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

vector <sClientsData> ConvertToRecords(vector <string> InfoFormFile)
{
	vector <string> vInfo;
	sClientsData Data;
	vector <sClientsData> vClientData;
	for (string& Temp : InfoFormFile)
	{
		vInfo = SplitString(Temp, Delimiter);
		Data = ConvertLineToRecord(vInfo);
		vClientData.push_back(Data);
	}
	return vClientData;
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
	vector <sClientsData> vData = ConvertToRecords(info);
	ClientList(vData);
}

bool AccountNumberExists(vector <string> InfoFromFile, string AccountNumber)
{
	vector <string> vInfoInLine;
	sClientsData info = {};
	for (string temp : InfoFromFile)
	{
		vInfoInLine = SplitString(temp, Delimiter);
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
	} while (AccountNumberExists(info, TempData.AccountNumber));
	TempData.PinCode = Input::PrintMessageAndReadText("Enter Pin Code");
	TempData.Name = Input::PrintMessageAndReadText("Enter Name");
	TempData.NumberPhone = Input::PrintMessageAndReadText("Enter Number Phone");
	TempData.AccountBalance = Input::ReadNumber("Enter Account Balance");
	return TempData;
}

void AddNewClientToFile(string FileName, vector <string> info)
{
	fstream File;
	sClientsData NewInfoForNewAccount = AddNew(info);
	File.open(FileName, ios::app);
	if (File.is_open())
	{
		File << ConvertRecordToLine(NewInfoForNewAccount, Delimiter) << endl;
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

bool MarkForDelete(string AccountNumber, vector <sClientsData>& vClientData)
{
	for (sClientsData& Temp : vClientData)
	{
		if (Temp.AccountNumber == AccountNumber)
		{
			Temp.MarkForDelete = true;
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
			if (!Temp.MarkForDelete)
			{
				File << ConvertRecordToLine(Temp, Delimiter) << endl;
			}
		}
		File.close();
	}
}

void DeletAccountFromData(string FileName, vector <string>& infoFromFile, string AccountNumber)
{
	sClientsData S2 = {};
	vector <sClientsData> vDataClient = ConvertToRecords(infoFromFile);
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

void refreshAccountInfo(sClientsData& info)
{
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

void UpdateAccount(string FileName, vector <string>& infoFromFile, string AccountNumber)
{
	sClientsData S2 = {};
	vector <sClientsData> vDataClient = ConvertToRecords(infoFromFile);
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
	sClientsData S2 = {};
	vector <sClientsData> vDataClient = ConvertToRecords(infoFromFile);
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
	Helpers::ResetScreen();
	cout << string(36, '=') << endl;
	cout << "\t  Main Menu Screen" << endl;
	cout << string(36, '=') << endl;
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transacyions.\n";
	cout << "\t[7] Exit.\n";
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
}

void AddNewClientsScreen(string FileName, vector <string> infoFromFile)
{
	Helpers::ResetScreen();
	cout << string(36, '-') << endl;
	cout << "\tAdd New Clients Screen\n";
	cout << string(36, '-') << endl;;
	AddNewClients(FileName, infoFromFile);
	Pause();
}

void DeleteClientsScreen(string FileName, vector <string> infoFromFile)
{
	Helpers::ResetScreen();
	cout << string(36, '-') << endl;
	cout << "\tDelete Clients Screen\n";
	cout << string(36, '-') << endl;
	cout << "please enter account Number\n";
	string AccountNumber = "";
	getline(cin >> ws, AccountNumber);
	DeletAccountFromData(FileName, infoFromFile, AccountNumber);
	Pause();
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
}

enum enTransactionsMenuOption {deposit = 1, withdrow = 2, toltalBalance = 3, mainMenu = 4};

void PrintTransactionsMenuScreen()
{
	Helpers::ResetScreen();
	cout << string(36, '=') << endl;
	cout << "      Transactions Menu Screen" << endl;
	cout << string(36, '=') << endl;
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdrow.\n";
	cout << "\t[3] Toltal Balance.\n";
	cout << "\t[4] Main Menu.\n";
	cout << string(36, '=') << endl;
}

void ProcessClientDeposit(vector <sClientsData> &vClientData, string AccountNumber, int NumberOfDeposit)
{
	 for (sClientsData& Temp : vClientData)
	 {
		 if (AccountNumber == Temp.AccountNumber)
		 {
			 Temp.AccountBalance += NumberOfDeposit;
			 return;
		 }
	 }
}

void SaveClientsDataToFile(string FileName,vector <sClientsData>& vClientData)
 {
	 fstream File;
	 
	 File.open(FileName, ios::out);
	 if (File.is_open())
	 {
		 for (sClientsData &Temp : vClientData)
		 {
			 File << ConvertRecordToLine(Temp, Delimiter) << endl;
		 }
		 File.close();
	 }
 }

void Deposit(string FileName,vector <sClientsData> & vClientData, string AccountNumber,sClientsData Info)
 {
	int NumberOfDeposit;
	PrintInfoForAccount(Info);
	NumberOfDeposit = Input::ReadPositiveNumber("Enter the amount you want to deposit");
	char answer;
	cout << "Are  you sure want perform this transaction ? Y/N\n";
	cin >> answer;
	if (tolower(answer) == 'y')
	{
		ProcessClientDeposit(vClientData, AccountNumber, NumberOfDeposit);
		SaveClientsDataToFile(FileName, vClientData);
		cout << "Deposit completed successfully\n";
	}
	else 
	cout << "Transaction canceled successfully successfully\n";
 }

void ProcessClientWithdrow(vector <sClientsData> &vClientData, string AccountNumber, int NumberOfWithdrow)
{
	 for (sClientsData& Temp : vClientData)
	 {
		 if (AccountNumber == Temp.AccountNumber)
		 {
			 Temp.AccountBalance -= NumberOfWithdrow;
			 return;
		 }
	 }
}

void Withdrow(string FileName, vector <sClientsData>& vClientData, string AccountNumber, sClientsData Info)
 {
	int NumberOfWithdrow = 0;
	double Result = 0;
		 PrintInfoForAccount(Info);
		 do
		 {
			 NumberOfWithdrow = Input::ReadPositiveNumber("Enter the amount you want to Withdrow");
			 Result = Info.AccountBalance - NumberOfWithdrow;
			 if (Result < 0)
			 {
				 cout << "Insufficient funds\n.The maximum amount you can withdraw is [" << Info.AccountBalance << "].\n";
			 }
		 } while (Result < 0);
		 char answer;
		 cout << "Are  you sure want perform this transaction ? Y/N\n";
		 cin >> answer;
		 if (tolower(answer) == 'y')
		 {
			 ProcessClientWithdrow(vClientData, AccountNumber, NumberOfWithdrow);
			 SaveClientsDataToFile(FileName, vClientData);
				 cout << "Withdrawal completed successfully\n";
		 }
		 cout << "Transaction canceled successfully\n";
 }
 
double ToTalBalance(vector <sClientsData> ClientsData)
 {
	 double total = 0;
	 for (sClientsData &Temp : ClientsData)
	 {
		 total += Temp.AccountBalance;
	 }

	 return total;
 }

void DepositScreen(string FileName, vector <string>& InfoFormFile)
 {
	 Helpers::ResetScreen();
	 cout << string(36, '-') << endl;
	 cout << "\t   Deposit Screen\n";
	 cout << string(36, '-') << endl;
	 vector <sClientsData> ClientData = ConvertToRecords(InfoFormFile);
	 sClientsData S2;
	 bool AccountIsFind;
	 string AccountNumber = "";
	 do
	 {
		 cout << "Please enter Account Number\n";
		 getline(cin >> ws, AccountNumber);
		 AccountIsFind = IsFind(AccountNumber, ClientData,S2);
		 if (!AccountIsFind)
		 {
			  cout << "Client With Account Number (" + AccountNumber + ") is Not Found!\n";
		 }
	 } while (!AccountIsFind);
	 Deposit(FileName, ClientData, AccountNumber, S2);
	 Pause();

 } 

void WithdrowScreen(string FileName, vector <string>& InfoFormFile)
 {
	 Helpers::ResetScreen();
	 cout << string(36, '-') << endl;
	 cout << "\t   Withdrow Screen\n";
	 cout << string(36, '-') << endl;
	 vector <sClientsData> ClientData = ConvertToRecords(InfoFormFile);
	 sClientsData S2;
	 bool AccountIsFind;
	 string AccountNumber = "";
	 do
	 {
		 cout << "Please enter Account Number\n";
		 getline(cin >> ws, AccountNumber);
		 AccountIsFind = IsFind(AccountNumber, ClientData, S2);
		 if (!AccountIsFind)
		 {
			 cout << "Client With Account Number (" + AccountNumber + ") is Not Found!\n";
		 }
	 } while (!AccountIsFind);
	 cout << "Enter the amount you want to withdraw\n";
	 Withdrow(FileName, ClientData, AccountNumber, S2);
	 Pause();
 }

void PrintHeaderBalanceList(vector <sClientsData> vClientData)
 {
	 if (vClientData.size() < 3)
	 {
		 cout << right << setw(50) << string(40, '-') << "Balance List (" << vClientData.size() << ") client" << left << setw(45) << string(40, '-') << endl;
	 }
	 else
	 {
		 cout << right << setw(48) << string(40, '-') << "Client List (" << vClientData.size() << ") clients" << left << setw(45) << string(40, '-') << endl;
	 }
	 cout << string(120, '-') << "\n";
	 cout << left
		 << "| " << setw(35) << "Account Number"
		 << "| " << setw(50) << "Client Name"
		 << "| " << fixed << setprecision(2) << "Balance" << "\n";
	 cout << string(120, '-') << "\n";
 }

void PrintBalanceRow(vector <sClientsData>& vClientData, double Total)
 {
	 for (sClientsData& client : vClientData)
	 {
		 cout << left
			 << "| " << setw(35) << client.AccountNumber
			 << "| " << setw(50) << client.Name
			 << "| " << fixed << setprecision(2) << client.AccountBalance << "\n";
	 }
	 cout << string(120, '-') << "\n";
	 cout << "\t\t\t\t\t\t Total Balance = " << Total << endl;

 }

void PrintBalanceList(vector <sClientsData> vClientData, double Total)
{
	PrintHeaderBalanceList(vClientData);
	PrintBalanceRow(vClientData, Total);
}

void ToTalScreen(vector <string>& InfoFormFile)
 {
	vector <sClientsData> info = ConvertToRecords(InfoFormFile);
	 Helpers::ResetScreen();
	 double Total = ToTalBalance(info);
	 PrintBalanceList(info,Total);
	 Pause();
 }

enTransactionsMenuOption TransactionsScreen(string FileName)
{
	PrintTransactionsMenuScreen();
	short num = 0;
	do
	{
		cout << "Choose what do you want to do [1 to 4]?\n";
		cin >> num;
	} while (num < 0 || num > 4);
	enTransactionsMenuOption Option = (enTransactionsMenuOption) num;
	vector <string> InfoFormFile = LoadInfoFromFile (FileName);
	switch (Option)
	{
	case deposit :
	{
		DepositScreen(FileName, InfoFormFile);
		break;
	}
	case withdrow:
	{
		WithdrowScreen(FileName, InfoFormFile);
		break;
	}
	case toltalBalance:
	{
		ToTalScreen(InfoFormFile);
		break;
	}
	}
	return Option;
}

void Transactions(string FileName)
{
	enTransactionsMenuOption option;
	do
	{
		option = TransactionsScreen(FileName);
	} while (option != enTransactionsMenuOption::mainMenu);
}

enum enMainMenuOption
{
	ListClient = 1, AddNewClient = 2, DeleteClient = 3,
	UpDateClient = 4, FindClient = 5, Transaction = 6, Exit = 7
};

void EndScreen()
{
	Helpers::ResetScreen();
	cout << string(36, '-') << endl;
	cout << "\t  Program Ends :-)\n";
	cout << string(36, '-') << endl;
	system("pause>0");
}

enMainMenuOption Bank(string FileName)
{
	PrintMainMenuScreen();
	int num = 0;
	do
	{
		cout << "Choose what do you want to do [1 to 7]?\n";
		cin >> num;
	} while (num > 7 || num < 1);
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
	case Transaction:
	{
		Transactions(FileName);
		break;
	}
	case Exit:
		EndScreen();
	}
	return option;
}

void BankApp(string FileName)
{
	enMainMenuOption Option;
	do
	{
		Option = Bank(FileName);
	} while (Option != Exit);
}

int main()
{
	string const FileName = "MkFile.txt";
	BankApp(FileName);
}
