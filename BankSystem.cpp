#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

const string ClientFileName = "Clients.txt";

void ShowMainMenu();
void ShowTransactionsMenu();

enum enMainMenuOptions {
    eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, 
    eUpdateClient = 4, eFindClient = 5, eTransactions = 6, eExit = 7
};

enum enTransactionsMenuOptions {
    eDeposit = 1, eWithdraw = 2, eShowTotalBalances = 3, eMainPage = 4
};

struct sClient {
    string AccountNumber = "";
    string PinCode = "";
    string Name = "";
    string Phone = "";
    double AccountBalance = 0;
    bool MarkForDelete = false;
};

vector<string> SplitString(string Text, string Delimiter) {
    vector<string> vString;
    short pos = 0;
    string sWord;

    while ((pos = Text.find(Delimiter)) != std::string::npos) {
        sWord = Text.substr(0, pos);
        if (sWord != "") {
            vString.push_back(sWord);
        }
        Text.erase(0, pos + Delimiter.length());
    }

    if (Text != "") {
        vString.push_back(Text);
    }
    return vString;
}

bool ReadCharTrueOrFalse(string Message) {
    char Answer;
    cout << Message;
    cin >> Answer;
    return (Answer == 'y' || Answer == 'Y');
}

void PrintClientCard(sClient Client) {
    cout << "\n\nThe following are the client details : ";
    cout << "\n-------------------------------------------\n";
    cout << "Account Number  : " << Client.AccountNumber << endl;
    cout << "Pin Code        : " << Client.PinCode << endl;
    cout << "Name            : " << Client.Name << endl;
    cout << "Phone           : " << Client.Phone << endl;
    cout << "Account Balance : " << Client.AccountBalance << endl;
    cout << "\n-------------------------------------------\n";
}

void PrintScreenHeader(string Message) {
    cout << "\n-------------------------------------------\n" << Message << "\n-------------------------------------------\n";
}

void GoBackToMainMenu() {
    cout << "\n\nPress any key to go back to Main Menu...";
    system("pause>0");
    ShowMainMenu();
}

void GoBackToTransactionsMenu() {
    cout << "\n\nPress any key to go back to Transactions Menu...";
    system("pause>0");
    ShowTransactionsMenu();
}

void PrintClientRecordLine(sClient Client) {
    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(10) << Client.PinCode;
    cout << "| " << left << setw(30) << Client.Name;
    cout << "| " << left << setw(12) << Client.Phone;
    cout << "| " << left << setw(12) << Client.AccountBalance;
}

void PrintClientBalanceLine(sClient Client) {
    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(30) << Client.Name;
    cout << "| " << left << setw(12) << Client.AccountBalance;
}

string ConvertRecordToLine(sClient Client, string Separator = "#//#") {
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Separator;
    stClientRecord += Client.PinCode + Separator;
    stClientRecord += Client.Name + Separator;
    stClientRecord += Client.Phone + Separator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}

sClient ConvertLineToRecord(string Line, string Separator = "#//#") {
    sClient Client;
    vector<string> vClientData = SplitString(Line, Separator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);

    return Client;
}

vector<sClient> LoadClientDataFromFile(string FileName) {
    vector<sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open()) {
        string Line;
        sClient Client;
        while (getline(MyFile, Line)) {
            Client = ConvertLineToRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

short ReadMainMenuOption() {
    short Number = 0;
    do {
        cout << "Choose what do you want to do? [1 to 7]? ";
        cin >> Number;
    } while (Number < 1 || Number > 7);
    return Number;
}

short ReadTransactionsMenuOption() {
    short Number = 0;
    do {
        cout << "Choose what do you want to do? [1 to 4]? ";
        cin >> Number;
    } while (Number < 1 || Number > 4);
    return Number;
}

void ShowAllClientsScreen() {
    vector<sClient> vClients = LoadClientDataFromFile(ClientFileName);
    cout << "\n\t\t\t\t\t Client List (" << vClients.size() << ") Client(s). ";
    cout << "\n_______________________________________________________________________________________________________\n\n";
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code ";
    cout << "| " << left << setw(30) << "Client Name";
    cout << "| " << left << setw(12) << "Phone ";
    cout << "| " << left << setw(12) << "Balance ";
    cout << "\n_______________________________________________________________________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\tNo Clients Available In the System!";
    else {
        for (sClient &C : vClients) {
            PrintClientRecordLine(C);
            cout << endl;
        }
    }
    cout << "\n_______________________________________________________________________________________________________\n\n";
}

bool FindClientByAccountNumber(string AccountNumber, sClient &Client, const vector<sClient> &vClients) {
    for (const sClient &C : vClients) {
        if (C.AccountNumber == AccountNumber) {
            Client = C;
            return true;
        }
    }
    return false;
}

string ReadClientAccountNumber(string Message = "\nPlease enter Account Number? ") {
    string AccountNumber;
    cout << Message;
    cin >> AccountNumber;
    return AccountNumber;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName) {
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open()) {
        string Line;
        sClient Client;
        while (getline(MyFile, Line)) {
            Client = ConvertLineToRecord(Line);
            if (Client.AccountNumber == AccountNumber) {
                MyFile.close();
                return true;
            }
        }
        MyFile.close();
    }
    return false;
}

sClient ReadNewClient() {
    sClient Client;
    cout << "Enter Account Number? ";
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientFileName)) {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number: ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter Pin Code? ";
    getline(cin, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter Account Balance? ";
    cin >> Client.AccountBalance;

    return Client;
}

sClient ChangeClientRecord(string AccountNumber) {
    sClient Client;
    Client.AccountNumber = AccountNumber;
    cout << "Enter Pin Code? ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter Account Balance? ";
    cin >> Client.AccountBalance;
    return Client;
}

void AddDataLineToFile(string FileName, string Sline) {
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open()) {
        MyFile << Sline << endl;
        MyFile.close();
    }
}

void AddNewClient() {
    sClient Client = ReadNewClient();
    AddDataLineToFile(ClientFileName, ConvertRecordToLine(Client));
}

void AddClients() {
    do {
        system("cls");
        PrintScreenHeader("\tAdd New Client Screen");
        AddNewClient();
    } while (ReadCharTrueOrFalse("\nClient Added Successfully, do you want to add more Clients? Y/N? "));
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient> &vClients) {
    for (sClient &C : vClients) {
        if (C.AccountNumber == AccountNumber) {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

vector<sClient> SaveClientsDataToFile(string FileName, const vector<sClient> &vClients) {
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    if (MyFile.is_open()) {
        for (const sClient &C : vClients) {
            if (!C.MarkForDelete) {
                MyFile << ConvertRecordToLine(C) << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient> &vClients) {
    sClient Client;
    if (FindClientByAccountNumber(AccountNumber, Client, vClients)) {
        PrintClientCard(Client);
        
        if (ReadCharTrueOrFalse("\nAre you sure you want to delete this client? Y/N? ")) {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveClientsDataToFile(ClientFileName, vClients);
            vClients = LoadClientDataFromFile(ClientFileName);
            cout << "\n\nClient Deleted Successfully.\n";
            return true;
        }
    } else {
        cout << "\nClient with Account Number (" << AccountNumber << ") is NOT Found!\n";
    }
    return false;
}

void ShowDeleteClientScreen() {
    PrintScreenHeader("\tDelete Client Screen");
    vector<sClient> vClients = LoadClientDataFromFile(ClientFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient> &vClients) {
    sClient Client;
    if (FindClientByAccountNumber(AccountNumber, Client, vClients)) {
        PrintClientCard(Client);
        if (ReadCharTrueOrFalse("\nAre you sure you want to update this client? Y/N? ")) {
            for (sClient &C : vClients) {
                if (C.AccountNumber == AccountNumber) {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveClientsDataToFile(ClientFileName, vClients);
            cout << "\n\nClient Updated Successfully.";
            return true;
        }
    } else {
        cout << "\nClient with Account Number (" << AccountNumber << ") is NOT Found!\n";
    }
    return false;
}

void ShowUpdateClientScreen() {
    PrintScreenHeader("\tUpdate Client Info Screen");
    vector<sClient> vClients = LoadClientDataFromFile(ClientFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowFindClientScreen() {
    PrintScreenHeader("\tFind Client Screen");
    sClient Client;
    vector<sClient> vClients = LoadClientDataFromFile(ClientFileName);
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, Client, vClients)) {
        PrintClientCard(Client);
    } else {
        cout << "\nClient with Account Number (" << AccountNumber << ") is NOT Found!\n";
    }
}

bool UpdateClientBalance(string AccountNumber, double Amount, vector<sClient> &vClients) {
    for (sClient &C : vClients) {
        if (C.AccountNumber == AccountNumber) {
            C.AccountBalance += Amount;
            return true;
        }
    }
    return false;
}

void DepositClientByAccountNumber(string AccountNumber, vector<sClient> &vClients) {
    sClient Client;
    double Amount = 0;
    if (FindClientByAccountNumber(AccountNumber, Client, vClients)) {
        PrintClientCard(Client);
        cout << "\nPlease enter deposit amount? ";
        cin >> Amount;

        if (ReadCharTrueOrFalse("\nAre you sure you want to perform this transaction? Y/N? ")) {
            UpdateClientBalance(AccountNumber, Amount, vClients);
            SaveClientsDataToFile(ClientFileName, vClients);
            
            FindClientByAccountNumber(AccountNumber, Client, vClients);
            cout << "\nDone Successfully. New Balance = " << Client.AccountBalance << "\n";
        }
    } else {
        cout << "\nClient with Account Number (" << AccountNumber << ") is NOT Found!\n";
    }
}

void WithdrawClientByAccountNumber(string AccountNumber, vector<sClient> &vClients) {
    sClient Client;
    double Amount = 0;
    if (FindClientByAccountNumber(AccountNumber, Client, vClients)) {
        PrintClientCard(Client);
        cout << "\nPlease enter withdraw amount? ";
        cin >> Amount;

        while (Amount > Client.AccountBalance) {
            cout << "\nAmount Exceeds the balance, you can withdraw up to: " << Client.AccountBalance << endl;
            cout << "Please enter withdraw amount? ";
            cin >> Amount;
        }

        if (ReadCharTrueOrFalse("\nAre you sure you want to perform this transaction? Y/N? ")) {
            UpdateClientBalance(AccountNumber, Amount * -1, vClients);
            SaveClientsDataToFile(ClientFileName, vClients);
            
            FindClientByAccountNumber(AccountNumber, Client, vClients);
            cout << "\nDone Successfully. New Balance = " << Client.AccountBalance << "\n";
        }
    } else {
        cout << "\nClient with Account Number (" << AccountNumber << ") is NOT Found!\n";
    }
}

void ShowDepositScreen() {
    PrintScreenHeader("\tDeposit Screen");
    vector<sClient> vClients = LoadClientDataFromFile(ClientFileName);
    string AccountNumber = ReadClientAccountNumber();
    DepositClientByAccountNumber(AccountNumber, vClients);
}

void ShowWithdrawScreen() {
    PrintScreenHeader("\tWithdraw Screen");
    vector<sClient> vClients = LoadClientDataFromFile(ClientFileName);
    string AccountNumber = ReadClientAccountNumber();
    WithdrawClientByAccountNumber(AccountNumber, vClients);
}

void ShowTotalBalancesScreen() {
    vector<sClient> vClients = LoadClientDataFromFile(ClientFileName);
    double TotalBalances = 0;

    cout << "\n\t\t\t\t\t Balances List (" << vClients.size() << ") Client(s). ";
    cout << "\n_______________________________________________________________________________________________________\n\n";
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(30) << "Client Name";
    cout << "| " << left << setw(12) << "Balance ";
    cout << "\n_______________________________________________________________________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\tNo Clients Available In the System!";
    else {
        for (sClient &C : vClients) {
            PrintClientBalanceLine(C);
            TotalBalances += C.AccountBalance;
            cout << endl;
        }
    }
    cout << "\n_______________________________________________________________________________________________________\n\n";
    cout << "\t\t\t\t\t Total Balances = " << TotalBalances << endl;
}

void PerformTransactionsMenuOption(enTransactionsMenuOptions TransactionOption) {
    switch (TransactionOption) {
    case enTransactionsMenuOptions::eDeposit:
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenu();
        break;
    case enTransactionsMenuOptions::eWithdraw:
        system("cls");
        ShowWithdrawScreen();
        GoBackToTransactionsMenu();
        break;
    case enTransactionsMenuOptions::eShowTotalBalances:
        system("cls");
        ShowTotalBalancesScreen();
        GoBackToTransactionsMenu();
        break;
    default:
        ShowMainMenu();
        break;
    }
}

void ShowTransactionsMenu() {
    system("cls");
    cout << "================================================\n";
    cout << "\t\t Transactions Menu Screen \n";
    cout << "================================================\n";
    cout << "\t[1] Deposit. \n";
    cout << "\t[2] Withdraw. \n";
    cout << "\t[3] Total Balances. \n";
    cout << "\t[4] Main Menu. \n";
    cout << "================================================\n";
    PerformTransactionsMenuOption((enTransactionsMenuOptions)ReadTransactionsMenuOption());
}

void PerformMainMenuOption(enMainMenuOptions MainMenuOption) {
    switch (MainMenuOption) {
    case enMainMenuOptions::eListClients:
        system("cls");
        ShowAllClientsScreen();
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::eAddNewClient:
        system("cls");
        AddClients();
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::eDeleteClient:
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::eUpdateClient:
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::eFindClient:
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::eTransactions:
        system("cls");
        ShowTransactionsMenu();
        break;
    default:
        system("cls");
        PrintScreenHeader("\tProgram Ends :-)");
        break;
    }
}

void ShowMainMenu() {
    system("cls");
    cout << "================================================\n";
    cout << "\t\t Main Menu Screen \n";
    cout << "================================================\n";
    cout << "\t[1] Show Client List. \n";
    cout << "\t[2] Add New Client. \n";
    cout << "\t[3] Delete Client. \n";
    cout << "\t[4] Update Client Info. \n";
    cout << "\t[5] Find Client. \n";
    cout << "\t[6] Transactions. \n";
    cout << "\t[7] Exit. \n";
    cout << "================================================\n";
    PerformMainMenuOption((enMainMenuOptions)ReadMainMenuOption());
}

int main() {
    ShowMainMenu();
    return 0;
}
