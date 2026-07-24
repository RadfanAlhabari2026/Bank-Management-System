#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;
const string ClientFileName = "Clints.txt";
const string UserFileName = "Users.txt";
void ShowMainMenue();
void ShowManageUserMenue();
void ShowTransactionMenue();
int ReadPerission();
void Login();

enum enMianMenueOption
{
    eListClients = 1,
    eAddNewClient = 2,
    eDeleteClient = 3,
    eUpdateClient = 4,
    eFindClient = 5,
    eTransaction = 6,
    eManageUser = 7,
    eLogout = 8
}; //enum اختيار اي عمليه تريد


enum enTransactionMenueOptions
{
    eDposit = 1,
    eWithraw = 2,
    T_B = 3,
    MainMenue = 4
};


struct stClient
{
    string AccountNumber = "";
    string PinCode = "";
    string Name = "";
    string Phone = "";
    double AccountBalance;
    bool MarkDeletClient = false;
};

enum enMianMenuePermission
{
    eAll = -1,
    PListClients = 1,
    PAddNewClient = 2,
    PDeletClient = 4,
    PUpdateClient = 8,
    PFindClient = 16,
    PTransaction = 32,
    PManageUser = 64,
};


enum enMianMenueOptionUser
{
    eListUsers = 1,
    eAddNewUsers = 2,
    eDeleteUsers = 3,
    eUpdateUsers = 4,
    eFindUsers = 5,
    eMianMenue = 6,
};

struct stUser
{
    string UserName;
    string Password;
    int Permission;
    short NumberPermission = 0;

    bool MarkDeletUser = false;

};
stUser CurrentUser;
vector<string> SplitString(string S9, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord; // define a string variable // use fine() function to get the position
    while ((pos = S9.find(Delim)) != std::string::npos)
    {
        sWord = S9.substr(0, pos);
        if (sWord != "")
        {
            vString.push_back(sWord);
        } // erase() until positon and move to
        S9.erase(0, pos + Delim.length());
    }
    if (S9 != "")
    { // it print last word of the string
        vString.push_back(S9);
    }
    return vString;
}
short ReadManageMenueOption()
{
    short Opion;
    cout << "\nchoose what do you want to do ?[1to6]?";
    cin >> Opion;
    return Opion;

}

bool ReadChartrueOrFalse(string Maseege)
{
    char More;
    cout << Maseege;
    cin >> More;
    return (More == 'y' || More == 'Y');
}

void PrintClinetCard(stClient Client)
{

    cout << "\n\nThe following are the client dateils : ";
    cout << "\n-------------------------------------------\n";

    cout << "Account Number : " << Client.AccountNumber << endl;
    cout << "PinCode        : " << Client.PinCode << endl;
    cout << "Name           : " << Client.Name << endl;
    cout << "Phone          : " << Client.Phone << endl;
    cout << "Account Balance : " << Client.AccountBalance << endl;
    cout << "\n-------------------------------------------\n";
}

void ShowDataClientRecord(vector<stClient> vClient)
{
    for (stClient& C : vClient)
    {
        if (C.MarkDeletClient == true)
        {
            PrintClinetCard(C);
        }
    }
}

void PrintHeadScreen(string Massege)
{
    cout << "\n-------------------------------------------\n"
        << Massege << "\n-------------------------------------------\n";
}

void GoBackToMianMenue()
{

    cout << "\n\nPress any kay to go back to Main Menue...";
    system("pause>0");

    ShowMainMenue();
}

void PrintClinetRecourd(stClient ClientRecourd)
{
    cout << "| " << left << setw(15) << ClientRecourd.AccountNumber;
    cout << "| " << left << setw(10) << ClientRecourd.PinCode;
    cout << "| " << left << setw(30) << ClientRecourd.Name;
    cout << "| " << left << setw(12) << ClientRecourd.Phone;
    cout << "| " << left << setw(12) << ClientRecourd.AccountBalance;
}

string ConvertRecordToLine(stClient Clinet, string Separator = "#//#")
{
    string stClinetRecord = "";
    stClinetRecord += Clinet.AccountNumber + Separator;
    stClinetRecord += Clinet.PinCode + Separator;
    stClinetRecord += Clinet.Name + Separator;
    stClinetRecord += Clinet.Phone + Separator;
    stClinetRecord += to_string(Clinet.AccountBalance);
    return stClinetRecord;
} // Problem #46



stClient CounvertLineToRecord(string Line, string Separator = "#//#")
{
    stClient Client;
    vector<string> vClinetData;
    vClinetData = SplitString(Line, Separator);
    Client.AccountNumber = vClinetData[0];
    Client.PinCode = vClinetData[1];
    Client.Name = vClinetData[2];
    Client.Phone = vClinetData[3];
    Client.AccountBalance = stod(vClinetData[4]); // case string to double
    return Client;
}
vector<stClient> LoadClientDataFromFile(string FileName)
{ //تحميل البيانات من الملف وتخزينها في ملف
    fstream MyFileP;
    vector<stClient> vClients;
    MyFileP.open(FileName, ios::in);

    if (MyFileP.is_open())
    {
        string line;
        stClient Clinet;
        while (getline(MyFileP, line))
        {
            Clinet = CounvertLineToRecord(line);
            vClients.push_back(Clinet);
        }
        MyFileP.close();
    }
    return vClients;
}

short ReadMainMenueOption()
{ //داله الاختيار احد عناصر ال Screen
    short Number = 0;
    do
    {
        cout << "MianMenueOption what do you want to do? [1 to 6]?";
        cin >> Number;
    } while (Number < 1 || Number > 9);
    return Number;
}

enMianMenueOption CheckNumberScreenLest(enMianMenueOption MianMenueOption)
{ //التحقق من الرقم المختار من القايمه الريسيه وارجاعه
    switch (MianMenueOption)
    {
    case 1:
        return enMianMenueOption::eListClients;
        break;
    case 2:
        return enMianMenueOption::eAddNewClient;
        break;
    case 3:
        return enMianMenueOption::eDeleteClient;
        break;
    case 4:
        return enMianMenueOption::eUpdateClient;
        break;
    case 5:
        return enMianMenueOption::eFindClient;
        break;
    default:
        return enMianMenueOption::eLogout;
        break;
    }
}

stClient no(stClient Client)
{ //قرءاه Client
    cout << "Enter PinCode ? ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name ? ";
    getline(cin, Client.Name);
    cout << "Enter Phone ? ";
    getline(cin, Client.Phone);
    cout << "Enter Account Balance ? ";
    cin >> Client.AccountBalance;
    return Client;
}

bool CheckAccessPermission(enMianMenuePermission Permission) {

    if (CurrentUser.Permission == enMianMenuePermission::eAll)
        return true;

    if ((Permission & CurrentUser.Permission) == Permission)
        return true;
    else
        return false;

}
void ShowaccessDeniedMessage() {

    cout << "---------------------------------------------\n";
    cout << "Access Denied,\nYou dont Have Permission To Do this,\nPlease Conact Your admin.\n";

    cout << "---------------------------------------------\n";

}

void ShowAllClienstScreen()
{
    if (!CheckAccessPermission(enMianMenuePermission::PListClients)) {
        ShowaccessDeniedMessage();
        return;
    }
    vector<stClient> vClients = LoadClientDataFromFile(ClientFileName);
    cout << "\n\t\t\t\t\t Client List (" << vClients.size() << ") Client(s). ";
    cout << "\n__________________________________________________________";
    cout << "______________________________________________\n\n";
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code ";
    cout << "| " << left << setw(30) << "Client Name";
    cout << "| " << left << setw(12) << "Phone ";
    cout << "| " << left << setw(12) << "Balance ";
    cout << "\n__________________________________________________________";
    cout << "______________________________________________\n"
        << endl;

    if (vClients.size() == 0)

        cout << "\t\t\tNo Client Available In the System!";

    else
        for (stClient& C : vClients)
        {
            PrintClinetRecourd(C);
            cout << endl;
        }
    cout << "\n__________________________________________________________";
    cout << "______________________________________________\n\n";
}

bool FindClientbyAccountNumber(string AccountNumber, stClient& Client, vector<stClient>& vClient)
{
    for (stClient& C : vClient)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

string ReadClientAccountNumber(string AccountNumber = "\nPlease enter AccountNumber?")
{
    cout << AccountNumber;
    cin >> AccountNumber;
    return AccountNumber;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
    vector<stClient> vCilents;

    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        stClient Clint;
        while (getline(MyFile, Line))
        {
            Clint = CounvertLineToRecord(Line);
            if (Clint.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
            vCilents.push_back(Clint);
        }
        MyFile.close();
    }
    return false;
}

stClient ReadNewClient()
{

    stClient Client;
    cout << "Enter Account Number ? ";
    getline(cin >> ws, Client.AccountNumber);
    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] aready exists,Enter another Account Number Client\n";

        getline(cin >> ws, Client.AccountNumber);
    }
    cout << "Enter PinCode ? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name ? ";
    getline(cin, Client.Name);

    cout << "Enter Phone ? ";
    getline(cin, Client.Phone);

    cout << "Enter Account Balance ? ";
    cin >> Client.AccountBalance;

    return Client;
}

void AddDataLineToFile(string FileName, string Sline) //تخزين كل من جديد عناصر Cliens In File
{
    fstream MyFileF;
    MyFileF.open(FileName, ios::out | ios::app);
    if (MyFileF.is_open())
    {

        MyFileF << Sline << endl;

        MyFileF.close();
    }
}

void AddNewClient()
{
    stClient Client;
    Client = ReadNewClient();

    AddDataLineToFile(ClientFileName, ConvertRecordToLine(Client));
}

void AddClients()
{

    do

    {
        cout << "Adding New Client:\n\n";
        AddNewClient();

    } while (ReadChartrueOrFalse("\nClient Adding Successfully, do you want add more Clients? Y/N? "));
}

void ShowAddClientsScreen()
{
    if (!CheckAccessPermission(enMianMenuePermission::PAddNewClient)) {
        ShowaccessDeniedMessage();
        return;
    }
    PrintHeadScreen("\tAdd New Client Screen");

    AddClients();
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<stClient>& vClients)
{

    for (stClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkDeletClient = true;
            return true;
        }
    }
    return false;
}

vector<stClient> SaveClientsDataToFile(string FileName, vector<stClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out); //overwrite
    string DataLine;
    if (MyFile.is_open())
    {
        for (stClient C : vClients)
        {
            if (C.MarkDeletClient == false)
            {
                // we only write record that are not marked for delete
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<stClient>& vClients)
{
    stClient Client;
    vClients = LoadClientDataFromFile(ClientFileName);
    if (FindClientbyAccountNumber(AccountNumber, Client, vClients))
    {
        PrintClinetCard(Client);
        if (ReadChartrueOrFalse("\nClient Adding Successfully, do you want Delet more Clients? Y/N? "))


        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveClientsDataToFile(ClientFileName, vClients);

            vClients = LoadClientDataFromFile(ClientFileName);
            cout << "\n\n Client Deleted Successfully. \n";
            return true;
        }
    }

    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is NOT Found! \n";
        return false;
    }
}

void ShowDeleteClientScreen()
{
    if (!CheckAccessPermission(enMianMenuePermission::PDeletClient)) {
        ShowaccessDeniedMessage();
        return;
    }

    PrintHeadScreen("\tDelete Client Screen");

    vector<stClient> vClients = LoadClientDataFromFile(ClientFileName);

    string AccountNumber = ReadClientAccountNumber();

    DeleteClientByAccountNumber(AccountNumber, vClients);
}

stClient ChangeClientRecord(string AccountNumber)
{
    stClient Client;
    Client.AccountNumber = AccountNumber;
    cout << "Enter PinCode ? ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name ? ";
    getline(cin, Client.Name);
    cout << "Enter Phone ? ";
    getline(cin, Client.Phone);
    cout << "Enter Account Balance ? ";
    cin >> Client.AccountBalance;

    return Client;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<stClient>& vClients)
{

    stClient Client;
    if (FindClientbyAccountNumber(AccountNumber, Client, vClients))
    {
        PrintClinetCard(Client);
        if (ReadChartrueOrFalse("\n Are you suer you want update this client ?Y/N? "))
        {
            for (stClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            vClients = SaveClientsDataToFile(ClientFileName, vClients);
            cout << "\n\nClient Update Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is NOT Found! \n";
        return false;
    }
}

void ShowUpdateClientScreen()
{
    if (!CheckAccessPermission(enMianMenuePermission::PUpdateClient)) {
        ShowaccessDeniedMessage();
        return;
    }
    PrintHeadScreen("\nUpdate Client Info Screen");
    vector<stClient> vClients = LoadClientDataFromFile(ClientFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowFindClientScreen()
{
    if (!CheckAccessPermission(enMianMenuePermission::PFindClient)) {
        ShowaccessDeniedMessage();
        return;
    }
    PrintHeadScreen("Find Client Screen");
    stClient Client;
    vector<stClient> vClients = LoadClientDataFromFile(ClientFileName);
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientbyAccountNumber(AccountNumber, Client, vClients))
    {
        PrintClinetCard(Client);
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is NOT Found! \n";
    }
}

short ReadTransactionsMenueOption()
{
    short Number = 0;
    cout << "Choose what do you want to do ?[1 to 4 ]?";
    cin >> Number;
    return Number;
}

void NumberDeposit(stClient Client, string AccountNumber, vector<stClient>& vClients)
{

    int Add_D_B = 0;

    PrintClinetCard(Client);
    cout << "\nPlease enter deposit amount?";
    cin >> Add_D_B;

    if (ReadChartrueOrFalse("\n Are you sure want prefrom this transaction ? Y/N? "))
    {
        //  AddDepositClient(AccountNumber, Add_D_B, vClients);
        SaveClientsDataToFile(ClientFileName, vClients);
        for (stClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                cout << "\nDan Successfully= " << C.AccountBalance << "\n";
                break;
            }
        }
    }
}

bool DepositBalanceToClientByAccountNumber(string& AccountNumber, double Amount, vector<stClient>& vClients)
{
    char Answer = 'n';

    cout << "\n\nAre you aure you want oerfrom this transaction? y/n ? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        for (stClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveClientsDataToFile(ClientFileName, vClients);
                cout << "\n\nDDone Successfully. New balance is:" << C.AccountBalance;
                return true;
            }
        }
        return false;
    }
}

void ShowDepositScreen()
{
    PrintHeadScreen("eDposit Screen");
    stClient Client;
    vector<stClient> vClients = LoadClientDataFromFile(ClientFileName);
    string AccountNumber = ReadClientAccountNumber();

    while (!FindClientbyAccountNumber(AccountNumber, Client, vClients))
    {
        cout << "\nClient with [" << AccountNumber << "] dose not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }
    PrintClinetCard(Client);
    double Amount = 0;
    cout << "\nPlease enter deposit amount? ";
    cin >> Amount;

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
}

void GoBackToTransactionsMenue()
{

    cout << "\n\nPress any kay to go back to Transactions Menue...";
    system("pause>0");
    ShowTransactionMenue();
}

void PrintClinetRecordBalanceLine(stClient ClientRecourd)
{
    cout << "| " << left << setw(15) << ClientRecourd.AccountNumber;
    cout << "| " << left << setw(30) << ClientRecourd.Name;
    cout << "| " << left << setw(12) << ClientRecourd.AccountBalance;
}

void ShowTotalBalnces()
{

    vector<stClient> vClients = LoadClientDataFromFile(ClientFileName);
    cout << "\n\t\t\t\t\t Client List (" << vClients.size() << ") Client(s). ";
    cout << "\n__________________________________________________________";
    cout << "______________________________________________\n\n";
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(30) << "Client Name";
    cout << "| " << left << setw(12) << "Balance ";
    cout << "\n__________________________________________________________";
    cout << "______________________________________________\n"
        << endl;

    double TotalBalnces = 0;
    if (vClients.size() == 0)

        cout << "\t\t\tNo Client Available In the System!";

    else
        for (stClient Client : vClients)
        {
            PrintClinetRecordBalanceLine(Client);
            TotalBalnces += Client.AccountBalance;
            cout << endl;
        }
    cout << "\n__________________________________________________________";
    cout << "______________________________________________\n\n";
    cout << "\t\t\t\tTotal Balances = " << TotalBalnces;
}

void ShowWithDrawScreen()
{
    PrintHeadScreen("Withdrou Screen");
    stClient Client;
    vector<stClient> vClients = LoadClientDataFromFile(ClientFileName);
    string AccountNumber = ReadClientAccountNumber();

    while (!FindClientbyAccountNumber(AccountNumber, Client, vClients))
    {
        cout << "\nClient with [" << AccountNumber << "] dose not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }
    PrintClinetCard(Client);
    double Amount = 0;
    cout << "\nPlease enter withdraw amount? ";
    cin >> Amount;

    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Excode the balance,you can withdraw uo to :  " << Client.AccountBalance;

        cout << "\nPlease enter withdraw amount? ";
        cin >> Amount;
    }

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
}
void PreformTransactionsMenueOption(enTransactionMenueOptions TransactionOption)
{

    switch (TransactionOption)
    {
    case enTransactionMenueOptions::eDposit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenue();

        break;
    }
    case enTransactionMenueOptions::eWithraw:
    {
        system("cls");
        ShowWithDrawScreen();
        GoBackToTransactionsMenue();
    }
    break;

    case enTransactionMenueOptions::T_B:
    {
        system("cls");
        ShowTotalBalnces();
        GoBackToTransactionsMenue();
    }
    break;

    default:
    {
        ShowMainMenue();

        break;
    }
    }
}

void ShowTransactionMenue()
{
    if (!CheckAccessPermission(enMianMenuePermission::PTransaction)) {
        ShowaccessDeniedMessage();
        return;
    }
    system("cls");
    cout << "================================================\n";
    cout << "\t\t Main Menue Screen \n";
    cout << "================================================\n";
    cout << "\t[1] Deposit. \n";
    cout << "\t[2] Withdraw. \n";
    cout << "\t[3] Total Balance. \n";
    cout << "\t[4] Main Menue. \n";
    cout << "================================================\n";

    PreformTransactionsMenueOption(enTransactionMenueOptions(ReadTransactionsMenueOption()));
}

stUser CounvertLineToRecordUser(string Line, string Separator = "#//#")
{
    stUser User;
    vector<string> vClinetData;
    vClinetData = SplitString(Line, Separator);
    User.UserName = vClinetData[0];
    User.Password = vClinetData[1];
    User.Permission = stod(vClinetData[2]); // case string to double
    return User;
}

vector<stUser> LoadUserDataFromFile(string FileName)
{ //تحميل البيانات من الملف وتخزينها في ملف
    fstream MyFileP;
    vector<stUser> vUsers;
    MyFileP.open(FileName, ios::in);
    if (MyFileP.is_open())
    {
        string line;

        stUser User;
        while (getline(MyFileP, line))
        {
            if (line != "") {
                User = CounvertLineToRecordUser(line);
                vUsers.push_back(User);
            }
        }
        MyFileP.close();
    }
    return vUsers;
}

void PrintUserRecordLine(stUser UsertRecourd)
{
    cout << "| " << left << setw(15) << UsertRecourd.UserName;
    cout << "| " << left << setw(30) << UsertRecourd.Password;
    cout << "| " << left << setw(12) << UsertRecourd.Permission;
}

void ShowAllUsersScreen() {


    vector<stUser> vUsers = LoadUserDataFromFile(UserFileName);
    cout << "\n\t\t\t\t\t User List (" << vUsers.size() << ") User(s). ";
    cout << "\n__________________________________________________________";
    cout << "______________________________________________\n\n";
    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(30) << "Password";
    cout << "| " << left << setw(12) << "Parmission ";
    cout << "\n__________________________________________________________";
    cout << "______________________________________________\n"
        << endl;

    double TotalBalnces = 0;
    if (vUsers.size() == 0)

        cout << "\t\t\tNo Client Available In the System!";

    else
        for (stUser User : vUsers)
        {
            PrintUserRecordLine(User);

            cout << endl;
        }
    cout << "\n__________________________________________________________";
    cout << "______________________________________________\n\n";

}

void GoBackToManageMenue()
{

    cout << "\n\nPress any kay to go back to Transactions Menue...";
    system("pause>0");
    ShowManageUserMenue();

}

bool UserExistsByUserName(string UserName, string FileName)
{
    vector<stUser> vUser;

    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        stUser User;
        while (getline(MyFile, Line))
        {
            if (Line != "") {
                User = CounvertLineToRecordUser(Line);
                if (User.UserName == UserName)
                {

                    MyFile.close();
                    return true;
                }
            }
            vUser.push_back(User);
        }
        MyFile.close();
    }
    return false;
}

int ReadPerission() {


    int Perissions = 0;
    if (ReadChartrueOrFalse("\nDo You wantgive full access? y/n? ")) {

        return -1;

    }

    else {
        cout << "\nDo You want to give access to :\n";

        if (ReadChartrueOrFalse("\nShow Client list? y/n? "))
            Perissions |= (enMianMenuePermission::PListClients);

        if (ReadChartrueOrFalse("\nAdd New Client? y/n? "))
            Perissions |= enMianMenuePermission::PAddNewClient;

        if (ReadChartrueOrFalse("\nDelete Client? y/n? "))
            Perissions |= enMianMenuePermission::PDeletClient;

        if (ReadChartrueOrFalse("\nUpdate Client? y/n? "))
            Perissions |= enMianMenuePermission::PUpdateClient;

        if (ReadChartrueOrFalse("\nFind Client? y/n? "))
            Perissions |= enMianMenuePermission::PFindClient;
        if (ReadChartrueOrFalse("\neTransaction? y/n? "))
            Perissions |= enMianMenuePermission::PTransaction;

        if (ReadChartrueOrFalse("\nManage User? y/n? "))
            Perissions |= enMianMenuePermission::PManageUser;
    }

    return (double)Perissions;
}

stUser ReadNewUser() {


    stUser User;
    cout << "Enter UserName  ? ";
    getline(cin >> ws, User.UserName);


    while (UserExistsByUserName(User.UserName, UserFileName))
    {
        cout << "\nClient with [" << User.UserName << "] aready exists,Enter another Username ?";

        getline(cin >> ws, User.UserName);
    }


    cout << "Enter Password ? ";
    getline(cin, User.Password);

    User.Permission = ReadPerission();

    return User;
}

string ConvertRecordToLineUser(stUser User, string Separator = "#//#")
{
    string stUserRecord = "";
    stUserRecord += User.UserName + Separator;
    stUserRecord += User.Password + Separator;

    stUserRecord += to_string(User.Permission);
    return stUserRecord;
} // Problem #46

void AddNewUser() {
    stUser User;


    User = ReadNewUser();



    AddDataLineToFile(UserFileName, ConvertRecordToLineUser(User));
}

void  AddUsers()
{

    do

    {
        cout << "Adding New User:\n\n";
        AddNewUser();

    } while (ReadChartrueOrFalse("\nUser Adding Successfully, do you want add more User? Y/N? "));
}

void ShowAddNewUsersScreen()
{
    PrintHeadScreen("\tAdd New User Screen");

    AddUsers();
}

bool FindUsertByUserName(string UserName, stUser& User, vector<stUser>& vUsers)
{
    for (stUser& U : vUsers)
    {
        if (U.UserName == UserName)
        {
            User = U;
            return true;
        }
    }
    return false;
}

void PrintUserCard(stUser User)
{

    cout << "\n\nThe following are the User dateils : ";
    cout << "\n-------------------------------------------\n";

    cout << "UserName    : " << User.UserName << endl;
    cout << "Password    : " << User.Password << endl;
    cout << "Permissions  : " << User.Permission << endl;
    cout << "\n-------------------------------------------\n";
}

bool MarkUserForDeleteByUserName(string UserName, vector<stUser>& vUsers)
{

    for (stUser& U : vUsers)
    {
        if (U.UserName == UserName)
        {
            U.MarkDeletUser = true;
            return true;
        }
    }
    return false;
}

vector<stUser> SaveUserDataToFile(string FileName, vector<stUser> vUsers)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out); //overwrite
    string DataLine;
    if (MyFile.is_open())
    {
        for (stUser U : vUsers)
        {
            if (U.MarkDeletUser == false)
            {
                // we only write record that are not marked for delete
                DataLine = ConvertRecordToLineUser(U);

                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vUsers;
}

bool DeletUserByUserName(string UserName, vector<stUser>& vUsers) {
    stUser User;
    vUsers = LoadUserDataFromFile(UserFileName);
    if (FindUsertByUserName(UserName, User, vUsers))
    {
        PrintUserCard(User);

        if (ReadChartrueOrFalse("\nAre you sure want delet this User ? Y/N? "))


        {
            MarkUserForDeleteByUserName(UserName, vUsers);


            SaveUserDataToFile(UserFileName, vUsers);


            vUsers = LoadUserDataFromFile(UserFileName);
            cout << "\n\n User Deleted Successfully. \n";
            return true;
        }
    }
    // void ShowDeleteClientScreen()

    else
    {
        cout << "\nClient with Account Number (" << UserName << ") is NOT Found! \n";
        return false;
    }
}

string ReadUserName(string UserName = "\nPlease enter UserName?")
{
    cout << UserName;
    cin >> UserName;
    return UserName;
}

void ShowDeletUsersScreen() {

    PrintHeadScreen("\tDelete User Menue");

    vector <stUser> vUsers;
    vUsers = LoadUserDataFromFile(UserFileName);

    string UserName = ReadUserName();
    DeletUserByUserName(UserName, vUsers);
}

stUser ChangeUserRecord(string UserName)
{
    stUser User;
    User.UserName = UserName;
    cout << "Enter Password ? ";
    getline(cin >> ws, User.Password);
    User.Permission = ReadPerission();


    return User;
}

bool UpdateUserByUserName(string UserName, vector<stUser>& vUsers)
{
    vUsers = LoadUserDataFromFile(UserFileName);

    stUser User;

    if (FindUsertByUserName(UserName, User, vUsers))
    {

        PrintUserCard(User);
        if (ReadChartrueOrFalse("\n Are you suer you want update this User ?Y/N? \n"))
        {
            for (stUser& U : vUsers)
            {
                if (U.UserName == UserName)
                {


                    U = ChangeUserRecord(UserName);

                    break;
                }
            }

            vUsers = SaveUserDataToFile(UserFileName, vUsers);
            cout << "\n\nClient Update Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << UserName << ") is NOT Found! \n";
        return false;
    }

}
void ShowUpdateUsersScreen() {
    PrintHeadScreen("\nUpdate User Screen");
    vector<stUser> vUsers;
    string UserName = ReadUserName();
    UpdateUserByUserName(UserName, vUsers);
}

void ShowFindUsersScreen()
{
    PrintHeadScreen("Find User Screen");
    stUser User;
    vector<stUser> vUsers = LoadUserDataFromFile(UserFileName);
    string UserName = ReadUserName();
    if (FindUsertByUserName(UserName, User, vUsers))
    {
        PrintUserCard(User);
    }
    else
    {
        cout << "\nClient with Account Number (" << UserName << ") is NOT Found! \n";
    }
}

void PerformManageUserMenueOption(enMianMenueOptionUser MenueOptionUser) {

    switch (MenueOptionUser)
    {
        {


    case enMianMenueOptionUser::eListUsers:
        system("cls");
        ShowAllUsersScreen();
        GoBackToManageMenue();

        break;
        }
        {case enMianMenueOptionUser::eAddNewUsers:
            system("cls");
            ShowAddNewUsersScreen();
            GoBackToManageMenue();

            break;
        } {
        case enMianMenueOptionUser::eDeleteUsers:
            system("cls");
            ShowDeletUsersScreen();
            GoBackToManageMenue();

            break;}

        {  case enMianMenueOptionUser::eUpdateUsers:
            system("cls");
            ShowUpdateUsersScreen();
            GoBackToManageMenue();
            break;}


    case enMianMenueOptionUser::eFindUsers: {
        system("cls");
        ShowFindUsersScreen();
        GoBackToManageMenue();
        break;}




    default: {

        ShowMainMenue();

        break;}
    }
}
void ShowManageUserMenue() {

    if (!CheckAccessPermission(enMianMenuePermission::PManageUser)) {
        ShowaccessDeniedMessage();
        return;
    }
    system("cls");
    cout << "================================================\n";
    cout << "\t\t Manage Users Menue Screen \n";
    cout << "================================================\n";
    cout << "\t[1] Lest Users. \n";
    cout << "\t[2] Add New User. \n";
    cout << "\t[3] Delete Users. \n";
    cout << "\t[4] Update User. \n";
    cout << "\t[5] Find User. \n";
    cout << "\t[6] Mian Menue. \n";
    cout << "================================================\n";
    PerformManageUserMenueOption((enMianMenueOptionUser)ReadManageMenueOption());

}

bool FindUsertByUserNameAndPassword(string UserName, string Password, stUser& User)
{
    vector<stUser> vUsers = LoadUserDataFromFile(UserFileName);
    for (stUser& U : vUsers)
    {
        if (U.UserName == UserName && U.Password == Password)
        {
            User = U;
            return true;
        }
    }
    return false;
}


void PerformMainMenueOption(enMianMenueOption MianMenueOption)
{
    vector<stClient> vClients;
    vClients = LoadClientDataFromFile(ClientFileName);

    switch (MianMenueOption)
    {
        {

    case enMianMenueOption::eListClients:
        system("cls");
        ShowAllClienstScreen();
        GoBackToMianMenue();
        break;
        }

    case enMianMenueOption::eAddNewClient:
        system("cls");
        ShowAddClientsScreen();
        GoBackToMianMenue();
        break;

    case enMianMenueOption::eDeleteClient:
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMianMenue();
        break;

    case enMianMenueOption::eUpdateClient:
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMianMenue();
        break;

    case enMianMenueOption::eFindClient:
        system("cls");
        ShowFindClientScreen();
        GoBackToMianMenue();
        break;

    case enMianMenueOption::eTransaction:
        system("cls");
        ShowTransactionMenue();
        GoBackToMianMenue();
        break;


    case enMianMenueOption::eManageUser:
        system("cls");
        ShowManageUserMenue();
        GoBackToMianMenue();
        break;

    default:
        system("cls");
        Login();
        break;
    }
}

void ShowMainMenue()
{


    system("cls");
    cout << "================================================\n";
    cout << "\t\t Main Menue Screen \n";
    cout << "================================================\n";
    cout << "\t[1] Show Client Lest. \n";
    cout << "\t[2] Add New Client. \n";
    cout << "\t[3] Delete Client. \n";
    cout << "\t[4] Update Client Info. \n";
    cout << "\t[5] Find Client. \n";
    cout << "\t[6] Transaction. \n";
    cout << "\t[7] Manage User. \n";
    cout << "\t[8] Logout. \n";


    cout << "================================================\n";
    PerformMainMenueOption((enMianMenueOption)ReadMainMenueOption());
}

bool LoadUserInFo(string Username, string Password) {

    if (FindUsertByUserNameAndPassword(Username, Password, CurrentUser))
        return true;
    else
        return false;
}

void Login() {
    bool Loginfaild = false;

    string Username, Password;
    do
    {
        system("cls");

        PrintHeadScreen("Login Screen");
        if (Loginfaild) {
            cout << "Invlaid Username/Password!\n";
        }
        cout << "Enter Username? ";
        cin >> Username;

        cout << "Enter Password? ";
        cin >> Password;

        Loginfaild = !LoadUserInFo(Username, Password);

    } while (Loginfaild);
    ShowMainMenue();
}

int main()
{
    
    Login();

    return 0;
}
