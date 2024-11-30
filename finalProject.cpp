#include <iostream>
#include <string>
#include <vector>
#include <limits> 
#include <thread>
#include <chrono>
#include <iomanip>
#include <cmath>
#include <cctype>
using namespace std;

class Design {
public:
  string greenText(){ return "\033[1;32m";}
  string purpleText(){return "\033[95m";}
  string redText(){return "\033[1;31m";}
  string whiteText() {return "\033[1;37m";}
  string resetColor(){return "\033[0m";};
  
  void printStylish(string mess) {
    string message = "✨ "+ mess +"✨";
    for (char c : message) {
    cout << c << flush; 
    this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << endl;
  }
  void coloredDesign() {
    for (int i = 0; i < 63; i++){
      if (i % 2 == 0) {
        cout << "\033[1;32m" << '-';
      }
      else {
        cout << "\033[95m" << '*';
      }
    }
    cout << "\033[0m" << endl;
  }
  void font(){
    cout  << purpleText() << "           ____          _   _ _  __" << endl;
    cout << "          |  _ \\   /\\   | \\ | | |/ /" << endl;
    cout << "          | |_) | /  \\  |  \\| | ' /" << endl;
    cout << "          |  _ < / /\\ \\ | . ` |  <" << endl;
    cout << "          | |_) / ____ \\| |\\  | . \\" << endl;
    cout << "          |____/_/    \\_\\_| \\_|_|\\_\\" << endl;
    cout << resetColor() << " " << endl;
  }
  void choiceTemp(string num, string messages){
    vector<string> longMess;

    longMess.push_back("| " + num + ".) " + messages);
    for (int i = 0; i <= (20 - messages.length()); i++){
      if(i == (20-messages.length())){
        longMess.push_back("|");
      } else {
        longMess.push_back(" ");
      }
    }

    cout << purpleText() << " _________________________" << resetColor() <<endl;
    for (string letters : longMess){ 
      cout << whiteText() << letters;
    }
    cout << resetColor() <<endl;
    cout << greenText() << " ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔" << resetColor() << endl;
  }
};
Design myDesign;

struct Account {
  string name;
  int id, pin;
  double balance;
};

class Bank {
private:
  vector<Account> accounts;
  int loginAccountIndex = -1;

  int findAccount(int id, int pin = -1){
    for(int i = 0; i < accounts.size(); i++){
      if(accounts[i].id == id && (pin == -1 || accounts[i].pin == pin)){
        return i;
      } 
    }
    return -1;
  }

public:
  int checkNum(string message);
  int randNum();
  void createAcc();
  void login();
  void loginMenu();
  void deposit();
  void withdraw();
  void viewBal();
  void moneyTransfer();
  bool isFourDigitNumber (const string & str);
};

void Bank::createAcc(){
  Account account;
  string userInp;
  myDesign.coloredDesign();
  cout << endl <<myDesign.purpleText() << setw(40)<< "Create New Account" << myDesign.resetColor() <<endl << endl;
  myDesign.coloredDesign();
  cout << myDesign.whiteText() << "Enter Your Name: " << myDesign.resetColor();
  cin.ignore();
  getline(cin, account.name);
  cout << myDesign.whiteText();
  account.id = randNum();
  for (const auto &acc : accounts){
    if(acc.id == account.id){
      account.id = randNum();
    } else {
      break;
    }
  }
  cout << "Your Account Number is: "<< account.id << endl;
  while (true) {
    cout << "Enter your 4-digit number: ";
    cin >> userInp;
    if (isFourDigitNumber(userInp)) {
      account.pin = stoi(userInp);
      break;
    } else {
      cout << myDesign.redText() << "Warning: The input is not a valid 4-digit number! Please enter a valid 4-digit number." << myDesign.resetColor()<< endl;
    }
  }
  account.balance = checkNum("Enter Initial Balance: ₱");
  cout << myDesign.resetColor();
 
  accounts.push_back(account);
  cout << myDesign.greenText() << "* Account Created!! * \n Please Wait......" << myDesign.resetColor() <<endl;
  this_thread::sleep_for(chrono::milliseconds(2000));
  system("clear");
}

void Bank::login(){
  int idNum, pin;
  myDesign.coloredDesign(); 
  cout << endl << myDesign.greenText()<<"|==========================|Log In|===========================|" << myDesign.resetColor()<< endl << endl;
  myDesign.coloredDesign();
  cout << myDesign.whiteText() <<"Enter your ID Number: ";
  cin >> idNum;
  cout << endl <<"Enter your PIN: ";
  cin >> pin;
  cout << myDesign.resetColor();
  loginAccountIndex = findAccount(idNum, pin);
  if(loginAccountIndex != -1){
    myDesign.printStylish("Logging In........");
    this_thread::sleep_for(chrono::milliseconds(2000)); 
    loginMenu();
  } else {
    cout << myDesign.redText() <<" |X|Invalid ID or PIN |X|" << myDesign.resetColor() << endl;
    this_thread::sleep_for(chrono::milliseconds(2000));
    system("clear");
  }
}

void Bank::loginMenu(){
  int userChoice;
  bool loggedOut = true;
  while (true && loginAccountIndex != -1) {
    myDesign.coloredDesign();
    myDesign.font();
    myDesign.coloredDesign();
    cout << myDesign.greenText() <<  "|======================|" << " Account Menu " << "|======================|" << endl;
    cout << setw(30) <<"   Welcome, " << accounts[loginAccountIndex].name << " !!"<< myDesign.resetColor() << endl;
    myDesign.choiceTemp("1", "Deposit");
    myDesign.choiceTemp("2", "Withdraw");
    myDesign.choiceTemp("3", "Money Transfer");
    myDesign.choiceTemp("4", "View Balance");
    myDesign.choiceTemp("5", "Log Out");
    userChoice = checkNum("Choose an option: ");
    switch (userChoice) {
    case 1:
      system("clear");
      deposit();
      break;
    case 2:
      system("clear");
      withdraw();
      break;
    case 3:
      system("clear");
      moneyTransfer();
      break;
    case 4:
      system("clear");
      viewBal();
    break;
    case 5:
      myDesign.printStylish("Logging Out...........");
      this_thread::sleep_for(chrono::milliseconds(2000));
      loginAccountIndex = -1;
      loggedOut = false;
      system("clear");
      break;
    default:
      cout << myDesign.redText() << ":X: Out Of Range :X:" << myDesign.resetColor();
      this_thread::sleep_for(chrono::milliseconds(2000));
      system("clear");
      break;
    }
  }
}

void Bank::deposit(){
  double depo;
  myDesign.coloredDesign();
  cout << endl << setw(35)<< "DEPOSIT"<< endl << endl;
  myDesign.coloredDesign();
  cout << endl << myDesign.whiteText() <<"Enter Amount to Deposit: ₱";
  cin >> depo;
  accounts[loginAccountIndex].balance += depo;
  cout << " * Deposit Successful!! *" << endl;
  cout << "Your Current Balance: ₱" << accounts[loginAccountIndex].balance << myDesign.resetColor()<< endl;
  myDesign.coloredDesign();
  this_thread::sleep_for(chrono::milliseconds(4000));
  system("clear");
}

void Bank::withdraw(){
  double withdrawal;
  myDesign.coloredDesign();
  cout << endl << setw(35) << "WITHDRAW" << endl << endl;
  myDesign.coloredDesign();
  cout << "Your current balance: "<< accounts[loginAccountIndex].balance << endl << endl;
  withdrawal = checkNum("Enter Amount to Withdraw: ₱");
  if(accounts[loginAccountIndex].balance >= withdrawal){
    accounts[loginAccountIndex].balance -= withdrawal;
    cout << "* Withdraw Successful!! *" << endl;
    this_thread::sleep_for(chrono::milliseconds(2000));
    system("clear");
  } else {
    cout << myDesign.redText() <<"You don't enough balance "<< myDesign.resetColor() << endl;
    this_thread::sleep_for(chrono::milliseconds(2000));
    system("clear");
  }
}

void Bank::viewBal(){
  myDesign.coloredDesign();
  cout << endl<< myDesign.whiteText() << setw(40)<< "Your Current Balance: ₱" <<myDesign.purpleText()<< fixed <<setprecision(2)<<accounts[loginAccountIndex].balance << myDesign.resetColor()<<endl << endl;
  myDesign.coloredDesign();
  this_thread::sleep_for(chrono::milliseconds(5000));
  system("clear");
}

void Bank::moneyTransfer(){
  int recipientID;
  double amount;
  recipientID = checkNum("Enter Recipient's Account ID: ");
  int recipientAcc = findAccount(recipientID);
  if(recipientAcc == -1){
    cout << myDesign.redText() << "Recipient Account Not Found." << myDesign.resetColor() <<  endl;
    this_thread::sleep_for(chrono::milliseconds(2000));
    return;
  }
  amount = checkNum("Enter Amount To Transfer: ");
  if(accounts[loginAccountIndex].balance >= amount){
    accounts[loginAccountIndex].balance -= amount;
    accounts[recipientAcc].balance += amount;
    cout << myDesign.whiteText() << "Money Transferred Successfully" << endl;
    cout << "Your current balance " << accounts[loginAccountIndex].balance << myDesign.resetColor() << endl;
    this_thread::sleep_for(chrono::milliseconds(2000));
    system("clear");
  } else {
    cout << myDesign.redText() <<"Insufficient Balance" << myDesign.resetColor() << endl;
    this_thread::sleep_for(chrono::milliseconds(2000));
    system("clear");
  }
}

int Bank::checkNum(string message){
  int userInputNum;
  while (true) {
    cout << myDesign.whiteText() << message << myDesign.resetColor();
    cin >> userInputNum;
    if(cin.fail()) {
       cin.clear();
       cin.ignore(numeric_limits<streamsize>::max(), '\n');
       cout << myDesign.redText() << "|X| Invalid Input |X| Try Again >> " << myDesign.resetColor();
    } else {
      break;
    }
  }
  return userInputNum;
}

bool Bank::isFourDigitNumber (const string & str) {
  if (str.length() == 4) {
    for (char c : str) {
      if (!isdigit(c)) {
        return false;
      }
    }
    return true;
  }
  return false;
}

int Bank::randNum(){
    srand((unsigned) time(NULL));
    int random = 100000 + (rand() % 999999);
    return random;
}

int main(){
  system("clear");
  Bank bankObj; 
  int first_choice;
  while (true) {
      system("clear");
      while (true) {
      myDesign.coloredDesign();
      myDesign.font();
      myDesign.coloredDesign();
      cout << endl;
      myDesign.choiceTemp("1", "Login");
      myDesign.choiceTemp("2", "Create Account");
      myDesign.choiceTemp("3", "Exit");
      cout << myDesign.whiteText() << "Choose an option: " << myDesign.resetColor();
      cin >> first_choice;
      if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << myDesign.redText() << "|X| Invalid Input |X|" << myDesign.resetColor() << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
        system("clear");
      }
      else {
        break;
      }
    }
    switch (first_choice) {
    case 1: 
      cout << endl;
      system("clear");
      bankObj.login();
      break;
    case 2:
      system("clear");
      bankObj.createAcc();
      break;
    case 3:
      system("clear");
      myDesign.printStylish("Thank You! For Trying our System");
      return 0;
    default:
      cout << myDesign.redText() << ":: Out Of Range ::" << myDesign.resetColor() << endl;
      this_thread::sleep_for(chrono::milliseconds(2000));
    }
  }
  return 0;
}