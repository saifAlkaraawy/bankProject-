
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
const string ClientsFileName = "Clients.txt";
const string  usersFileName = "Users.txt";
void ShowMainMenue();
void backToTransactionMenue();
 void ShowManageUserMenue();
 void GoBackToManageUserMenue();
struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};
struct sUser
{
    string userName;
    string password;
    int premission = 0;
    bool deleteMark=false;


};
enum enMainMenueOptions
{
    eListClients = 1, eAddNewClient = 2,
    eDeleteClient = 3, eUpdateClient = 4,
    eFindClient = 5, eTranstion = 6, eManageUser = 7,
    eExit = 8
};
enum enTransactionMenue
{
    deposit = 1, withdraw = 2,
    TotalBalances = 3, MainMenue = 4,

};
enum enManageUserMenueOptions
{
    eListUser = 1, eAddNewUser = 2,
    eDeleteUser = 3, eUpdateUser = 4,
    eFindUser = 5,
    backToMainMenue = 6
};
struct sPremission {

    // 1 2 4 8 16 32 64 128 
    int  showListclient = 1, addNewClient = 2,
        deleteClient = 4,
        updateClient = 8
        , FindClient = 16,
        transtion = 32,
        manageuser = 64,
        allPremission = -1;

};


sUser currentUser;


vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord; // define a string variable  

    // use find() function to get the position of the delimiters  
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word   
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;

}
sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    sClient Client;
    vector<string> vClientData;
    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to double
    return Client;
}
string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}
bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
            vClients.push_back(Client);
        }

        MyFile.close();

    }
    return false;
}
sClient ReadNewClient()
{
    sClient Client;
    cout << "Enter Account Number? ";

    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter PinCode ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}
vector <sClient> LoadCleintsDataFromFile(string FileName)
{
    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(ClientsFileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}
void PrintClientRecordLine(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}
void ShowAllClientsScreen()
{
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";
}
bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{
    for (sClient C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }

    }
    return false;
}
sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;
    return Client;
}
bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    for (sClient& C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }

    }

    return false;
}
vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.  
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }

        }

        MyFile.close();
    }

    return vClients;
}
void AddDataLineToFile(string FileName, string  stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile<< stDataLine << endl;

        MyFile.close();
    }
}
void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}
void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
        //system("cls");
        cout << "Adding New Client:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}
bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);

            //Refresh Clients 
            vClients = LoadCleintsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}
bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveCleintsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}
string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;

}
void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}
void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);

}
void ShowAddNewClientsScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";

    AddNewClients();
}
void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";


}
void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}
void GoBackToMainMenue()
{
    system("pause");
    system("cls");
    ShowMainMenue();

}
short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 8]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}
short ReadtransactionMenueOption()
{
    cout << "Choose what do you want to do? [1 to 4]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}
int readAmount(string message)
{
    cout << message;
    int amount = 0;
    cin >> amount;
    return amount;

}
void depoistOpertion(vector <sClient>& vClients, string AccountNumber) {

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);


        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += readAmount("please enter deposit amount ?");
                break;
            }
        }



        cout << "\n\n deposit Successfully.";



    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";

    }

}
void showDepositScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    depoistOpertion(vClients, AccountNumber);
    SaveCleintsDataToFile(ClientsFileName, vClients);

}
void WithDrawOpertion(vector <sClient>& vClients, string AccountNumber) {

    sClient Client;

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);


        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                int amount = readAmount("please enter withdraw amount ?");

                if (C.AccountBalance >= amount) {

                    C.AccountBalance -= amount;
                    cout << "\n\n withdraw Successfully.";

                }
                else {

                    cout << "you can not withdraw more than " << C.AccountBalance;
                }
                break;
            }
        }







    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";

    }

}
void showWithdrawScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tWithDraw Screen";
    cout << "\n-----------------------------------\n";
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    WithDrawOpertion(vClients, AccountNumber);
    SaveCleintsDataToFile(ClientsFileName, vClients);


}
void ShowClientsBlancesScreen()
{
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    int totalBalance = 0;

    cout << "\n\t\t\t\t\Balances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";

    cout << "| " << left << setw(40) << "Client Name";

    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordLine(Client);
            totalBalance += Client.AccountBalance;
            cout << endl;
        }

    cout << "\n_______________________________________________________";

    cout << "_________________________________________\n" << endl;
    cout << "\t \t\t \t \t\t\t \t\t " << "Total Balance =" << totalBalance;
}
void TransactionOptoin(enTransactionMenue menue) {

    switch (menue)
    {
    case deposit:
        system("cls");
        showDepositScreen();
        backToTransactionMenue();
        break;
    case withdraw:
        system("cls");
        showWithdrawScreen();
        backToTransactionMenue();
        break;
    case TotalBalances:
        system("cls");
        ShowClientsBlancesScreen();
        backToTransactionMenue();
        break;
    case MainMenue:
        ShowMainMenue();
        break;
    }

}
void ShowTransctionMenue() {
    cout << "\n-----------------------------------\n";
    cout << "\tTransactions menue Screen";
    cout << "\n-----------------------------------\n";
    cout << "\t [1] Deposit" << endl;
    cout << "\t [2] withdraw" << endl;
    cout << "\t [3] Total Balances" << endl;
    cout << "\t [4] Main Menue" << endl;
    TransactionOptoin((enTransactionMenue)ReadtransactionMenueOption());
}
void backToTransactionMenue() {
    cout << "\n\nPress any key to go back toTransaction Menue...";
    system("pause>0");
    system("cls");
    ShowTransctionMenue();
}

void printAccessDainedScreen() {

    system("cls");
    cout << "--------------------------------------------\n";
    cout << "                   Access Dained               \n";
    cout << "--------------------------------------------\n";
    cout << " you don't have premission to enter this screen  ";


}
void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{     
    sPremission eachpremission;
    int premission = currentUser.premission;
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
    { 

    if ((premission == -1) || ((eachpremission.showListclient & premission) == eachpremission.showListclient)) {
        system("cls");
        ShowAllClientsScreen();
        GoBackToMainMenue();
    }else{
        printAccessDainedScreen();
            GoBackToMainMenue();
    }
        
        break;
    }
    case enMainMenueOptions::eAddNewClient:


        if ((premission == -1) || ((eachpremission.addNewClient & premission) == eachpremission.addNewClient)) {
            system("cls");
            ShowAddNewClientsScreen();
            GoBackToMainMenue();
        }
        else {
            printAccessDainedScreen();
            GoBackToMainMenue();
        }
      
        break;

    case enMainMenueOptions::eDeleteClient:
        if ((premission == -1) || ((eachpremission.deleteClient & premission) == eachpremission.deleteClient)) {
            system("cls");
            ShowDeleteClientScreen();
            GoBackToMainMenue();
        }
        else {
            printAccessDainedScreen();
            GoBackToMainMenue();
        }
      
        break;

    case enMainMenueOptions::eUpdateClient:

        if ((premission == -1) || ((eachpremission.updateClient & premission) == eachpremission.updateClient)) {
            system("cls");
            ShowUpdateClientScreen();
            GoBackToMainMenue();
        }
        else {
            printAccessDainedScreen();
            GoBackToMainMenue();
        }
  
        break;

    case enMainMenueOptions::eFindClient:
        if ((premission == -1) || ((eachpremission.FindClient & premission) == eachpremission.FindClient)) {
            system("cls");
            ShowFindClientScreen();
            GoBackToMainMenue();
        }
        else {
            printAccessDainedScreen();
            GoBackToMainMenue();
        }
     
        break;
    case enMainMenueOptions::eTranstion:
        if ((premission == -1) || ((eachpremission.transtion & premission) == eachpremission.transtion)) {
            system("cls");
            ShowTransctionMenue();
            GoBackToMainMenue();
        }
        else {
            printAccessDainedScreen();
            GoBackToMainMenue();
        }
  
        break;


    case enMainMenueOptions::eManageUser:
        if ((premission == -1) || ((eachpremission.manageuser & premission) == eachpremission.manageuser)) {
     
        system("cls");
        ShowManageUserMenue();
        ShowEndScreen();
        }
        else {
            printAccessDainedScreen();
            GoBackToMainMenue();
        }

        break;

    case enMainMenueOptions::eExit:
        system("cls");
        ShowEndScreen();
        break;
    }
}







//user part
sUser ConvertUserInfoToRecord(string Line, string Seperator = "#//#")
{
    sUser User;
    vector<string> vUserData;
    vUserData = SplitString(Line, Seperator);

    User.userName = vUserData[0];
    User.password = vUserData[1];
    User.premission = stoi(vUserData[2]);
    return User;
}
bool isUserExist(string  userName) {

    vector <sUser> users;



    fstream MyFile;
    MyFile.open(usersFileName, ios::out | ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        sUser user;

        while (getline(MyFile, Line))
        {
            user = ConvertUserInfoToRecord(Line);
            if (user.userName == userName)
            {

                    MyFile.close();
                    return true;
               

            }
        }

        MyFile.close();

    }
    return false;



}
sUser ReadNewUser()
{
    sUser User;
    sPremission givePremission;
    char give;
    cout << "Enter UserName? ";
    
    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, User.userName);

    while (isUserExist(User.userName))
    {
        cout << "\nClient with [" << User.userName << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, User.userName);
    }

    cout << "enter pasword : ";
    getline(cin >> ws, User.password);
    cout << "Did you give him all premission ? y or n ";
    cin >> give;

    if (tolower(give) == 'y') {
        User.premission = givePremission.allPremission;
    }
    else {
        cout << "Did you give him premission to show all Client ? y or n ";
        cin >> give;
        if (tolower(give) == 'y')
            User.premission = User.premission + givePremission.showListclient;

        cout << "Did you give him premission to add Client ? y or n ";
        cin >> give;
        if (tolower(give) == 'y')
            User.premission = User.premission + givePremission.addNewClient;

        cout << "Did you give him premission to delete Client ? y or n ";
        cin >> give;
        if (tolower(give) == 'y')
            User.premission = User.premission + givePremission.deleteClient;

        cout << "Did you give him premission to update Client ? y or n ";
        cin >> give;
        if (tolower(give) == 'y')
            User.premission = User.premission + givePremission.updateClient;


        cout << "Did you give him premission to find Client ? y or n ";
        cin >> give;
        if (tolower(give) == 'y')
            User.premission = User.premission + givePremission.FindClient;

        cout << "Did you give him premission to transtion   ? y or n ";
        cin >> give;
        if (tolower(give) == 'y')
            User.premission = User.premission + givePremission.transtion;

        cout << "Did you give him premission to Manage User? y or n ";
        cin >> give;
        if (tolower(give) == 'y')
            User.premission = User.premission + givePremission.manageuser;
    }

    return User;
}
string ConvertUserRecordToLine( sUser user, string Seperator = "#//#")
{

    string stUserRecord = "";
    stUserRecord +=user.userName + Seperator;
    stUserRecord += user.password + Seperator;
    stUserRecord +=to_string( user.premission) ;
    return stUserRecord;
}
void AddNewUser()
{
 sUser User;
 User = ReadNewUser();
    AddDataLineToFile(usersFileName, ConvertUserRecordToLine(User));
}
void AddNewUsers()
{
    char AddMore = 'Y';
    do
    {
        //system("cls");
        cout << "Adding New Client:\n\n";

        AddNewUser();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}
void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] tranction Menue.\n";
    cout << "\t[7] manage user.\n";
    cout << "\t[8] Exit.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}
void GoBackToManageUserMenue()
{
    system("pause");
    system("cls");
    ShowManageUserMenue();

}
vector <sUser> LoadUsersDataFromFile()
{
    vector <sUser> vUsers;
    fstream MyFile;
    MyFile.open(usersFileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        sUser user;

        while (getline(MyFile, Line))
        {
            user = ConvertUserInfoToRecord(Line);

            vUsers.push_back(user);

        }
        MyFile.close();
    }
    return vUsers;
}
bool checkUser(string  userName, string Password) {

    vector <sUser> users;



    fstream MyFile;
    MyFile.open(usersFileName,  ios::out | ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        sUser user;

        while (getline(MyFile, Line))
        {
            user = ConvertUserInfoToRecord(Line);
            if (user.userName == userName)
            {
                if (user.password == Password) {
                    MyFile.close();
                    currentUser =user;
                    return true;
                }
               
            }
        }

        MyFile.close();

    }
    return false;



}
short ReadManageUserMenueOption()
{
    cout << "Choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;

    return  Choice;
}
void PrintClientRecordLine(sUser User)
{
    cout << "| " << setw(15) << left << User.userName;
    cout << "| " << setw(10) << left << User.password;
    cout << "| " << setw(40) << left << User.premission;

}
 void showAllUsers() {

    vector <sUser> vUsers = LoadUsersDataFromFile();

    cout << "\n\t\t\t\tUser List (" << vUsers.size() << ") User(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "username";
    cout << "| " << left << setw(10) << "Password ";
    cout << "| " << left << setw(40) << "premission";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;


   
        for (sUser  &user : vUsers)
        {

            PrintClientRecordLine(user);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;


}



 //delete user
 string ReadUserName()
 {
     string userNAme = "";

     cout << "\nPlease enter userNAme? ";
     cin >> userNAme;
     return userNAme;

 }
 bool FindUsertByUserName(string UserName, vector <sUser> vUsers, sUser &User)
 {
     for (sUser C : vUsers)
     {

         if (C.userName == UserName)
         {
             User = C;
             return true;
         }

     }
     return false;
 }
 void PrintUserCard(sUser user)
 {
     cout << "\nThe following are the user details:\n";
     cout << "-----------------------------------";
     cout << "\n user name: " << user.userName;
     cout << "\npassword: " << user.password;
     cout << "\npremission: " << user.premission;

     cout << "\n-----------------------------------\n";
 }
 bool MarkUsertForDeleteByUserName(string UserName, vector <sUser>& vUsers)
 {

     for (sUser& C : vUsers)
     {

         if (C.userName == UserName)
         {
             C.deleteMark = true;
             return true;
         }

     }

     return false;
 }
 vector <sUser> SaveUsersDataToFile(string FileName, vector <sUser> vUsers)
 {
     fstream MyFile;
     MyFile.open(FileName, ios::out);//overwrite

     string DataLine;

     if (MyFile.is_open())
     {
         for (sUser C : vUsers)
         {

             if (C.deleteMark == false)
             {
                 //we only write records that are not marked for delete.  
                 DataLine = ConvertUserRecordToLine(C);
                 MyFile << DataLine << endl;
             }

         }

         MyFile.close();
     }

     return vUsers;
 }
 bool DeleteUsertByUserName(string Username, vector <sUser>& vUsers)
 {
     sUser user;
     string Answer = "n";

     if (FindUsertByUserName(Username, vUsers, user))
     {

         PrintUserCard(user);

         cout << "\n\nAre you sure you want delete this user? y/n ? ";
         cin >> Answer;
         if (Answer == "y" || Answer == "Y")
         {
             MarkUsertForDeleteByUserName(Username, vUsers);

             SaveUsersDataToFile(usersFileName, vUsers);

             //Refresh Clients 
             vUsers = LoadUsersDataFromFile();

             cout << "\n\nClient Deleted Successfully.";
             return true;
         }

     }
     else
     {
         cout << "\n user with username (" << Username << ") is Not Found!";
         return false;
     }
 }
 void ShowDeleteUserScreen()
 {
     cout << "\n-----------------------------------\n";
     cout << "\tDelete Client Screen";
     cout << "\n-----------------------------------\n";

     vector <sUser> vUsers = LoadUsersDataFromFile();
     string userName = ReadUserName();
     DeleteUsertByUserName(userName, vUsers);
 }


 //update User
 bool UpdateUserByUserName(string userName, vector <sUser>& vUsers)
 {

     sUser user;
     char Answer = 'n';

     if (FindUsertByUserName(userName, vUsers, user))
     {

         PrintUserCard(user);
         cout << "\n\nAre you sure you want update this user? y/n ? ";
         cin >> Answer;
         if (Answer == 'y' || Answer == 'Y')
         {
             for (sUser& C : vUsers)
             {
                 if (C.userName == userName)
                 {
                     C = ReadNewUser();
                     break;
                 }
             }

             SaveUsersDataToFile(usersFileName, vUsers);

             cout << "\n\nClient Updated Successfully.";
             return true;
         }

     }
     else
     {
         cout << "\n user with userName (" << userName << ") is Not Found!";
         return false;
     }
 }
 void ShowUpdateUserScreen()
 {
     cout << "\n-----------------------------------\n";
     cout << "\tUpdate user Info Screen";
     cout << "\n-----------------------------------\n";

     vector <sUser> vUsers = LoadUsersDataFromFile();
     string UserName = ReadUserName();
     UpdateUserByUserName(UserName, vUsers);

 }



 //find user
 void ShowFindUsertScreen()
 {
     cout << "\n-----------------------------------\n";
     cout << "\tFind User Screen";
     cout << "\n-----------------------------------\n";

     vector <sUser> vUsers = LoadUsersDataFromFile();
     sUser user;
     string userName = ReadUserName();
     if (FindUsertByUserName(userName, vUsers, user))
         PrintUserCard(user);
     else
         cout << "\n user with userName [" << userName << "] is not found!";


 }

void performManageUserOption(enManageUserMenueOptions option) {



    switch (option)
    {
    case eListUser:
        system("cls");
        showAllUsers();
        GoBackToManageUserMenue();

        break;
    case eAddNewUser:
        system("cls");
        AddNewUsers();
        GoBackToManageUserMenue();
        break;
    case eDeleteUser:
        system("cls");
        ShowDeleteUserScreen();
        GoBackToManageUserMenue();
        break;
    case eUpdateUser:
        system("cls");
        ShowUpdateUserScreen();
        GoBackToManageUserMenue();
        break;
    case eFindUser:
        system("cls");
        ShowFindUsertScreen();
        GoBackToManageUserMenue();
        break;
    case backToMainMenue:
        ShowMainMenue();


        break;
    default:
        system("cls");
            ShowMainMenue();
        break;
    }

}
void ShowManageUserMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\Manage User Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete users.\n";
    cout << "\t[4] Update User .\n";
    cout << "\t[5] Find Yser.\n";
    cout << "\t[6] back to main menue.\n";
    cout << "===========================================\n";
    performManageUserOption((enManageUserMenueOptions)ReadManageUserMenueOption());


}



void login() {
    string username;
    string password;
 

    bool oneTime = false;
    do {
        system("cls");
        cout << "---------------------" << "login screen" << "----------------------------" << endl;
        if (oneTime)
            cout << "invalide password or username" << endl;

        cout << "enter usename :";
        cin >> username;
        cout << "enter password :";
        cin >> password;

        oneTime = true;



    } while (!checkUser(username, password));



    ShowMainMenue();



}
int main()
{
    login();
        system("pause>0");
    return 0;
}
