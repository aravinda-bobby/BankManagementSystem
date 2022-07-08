//                                            Bank Management System

/*   Features
    1-> Create Accounts
    2-> View Customers List
    3-> Update information of existing account
    4-> Check the details of an existing account
    5-> Transactions
        5.1-> Withdrawing money
        5.2-> Depositing money
    6-> Close Existing accounts
    7-> Exit
*/

#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<fstream>
#include<conio.h>
#include<iomanip>

using namespace std;

class account
{
private:
    int acc_no;
    char name[50];
    int saving;
    char acc_type;

public:
    void create_acc();               //get data from user
    void show_acc();                 //get account number
    void modify();                   //modify account details
    void dep(int num);                 //deposit money 
    void draw(int num);                //withdraw money
    char ret_type();                 //return type of account
    int ret_saving();               //return savings
    int acc_no_return();
};

int account::acc_no_return(){
    return acc_no;
}


void account::create_acc(){

    cout<<"Enter the account number: "<<endl;
    cin>>acc_no;
    cout<<"Enter the name: "<<endl;
    cin.ignore();
    cin.getline(name,50);
    cout<<"Enter the Initial amount: "<<endl;
    cin>>saving;
    cout<<"Enter the type of account[C/S]: "<<endl;
    cin>>acc_type;
    acc_type = toupper(acc_type);
}

void account::show_acc(){

    cout<<"Account Number"<<setw(10)<<"Name"<<setw(10)<<"Savings"<<setw(20)<<"Account Type"<<endl;
    cout<<acc_no<<setw(20)<<name<<setw(10)<<saving<<setw(20)<<acc_type<<endl;
    
}

void account::modify(){
    
    cout<<"Enter the modified name: "<<endl;
    cin.ignore();
    cin.getline(name,50);
    cout<<"Enter the type of account[C/S]: "<<endl;
    cin>>acc_type;
    acc_type = toupper(acc_type);
    return;

}

void account::dep(int money){

    this->saving = this->saving + money;
    cout<<"\nMoney has been successfully deposited"<<endl;
    return;

}

void account::draw(int money){
    if(this->saving >= money){
    this->saving = (this->saving - money);
    cout<<"\nMoney has been successfully drawn\n"<<endl;
    }else{
        cout<<"Insufficient Balance\n";
    }

    return;
}

int account::ret_saving(){
    
    return saving;

}

char account::ret_type(){
    
    return acc_type;

}

//function used
//----------INTRO FUNCTION------------------//
void intro(){

    cout<<"\n\n\tBank Management System";
    cout<<"by -> P Ranga Aravinda Swamy";

}

//----------To write into file--------------//
void write_account(){
    account ac;
    ofstream file;
    file.open("account.dat",ios::binary|ios::app);
    ac.create_acc();
    file.write((char*)&ac,sizeof(account));
    file.close();
}

//-------------To perform Transactions--------//
void deposit_money(int num,int option){
    account ac;
    fstream file;
    bool flag = false;
    file.open("account.dat",ios::binary|ios::in|ios::out);
    if(!file){
        cout<<"File could not be opened...Press any key to continue";
        return;
    }

    while(file.read((char*)&ac,sizeof(account))){
        if(ac.acc_no_return() == num){
            flag = true;
            if(option == 1){
                int money;
                cout<<"\n\nEnter the amount to be deposited: ";
                cin.ignore();
                cin>>money;
                ac.dep(money);
                
            }

            if(option == 2){
                int money;
                cout<<"\n\nEnter the amount to be drawn: ";
                cin.ignore();
                cin>>money;
                ac.draw(money);


            }

            int pos = sizeof(account);
            file.seekp(-pos,ios::cur);
            file.write((char*)&ac,sizeof(ac));
        }
    }
    file.close();
    return;

}

//--------------Read specific records from the file-----------//
void display_sp(int num){

    account ac;
    bool flag = false;
    ifstream file;
    file.open("account.dat",ios::binary);
    if(!file){                                                           //if the file doesn't open properly.
        cout<<"File could not be opened...Press any key to continue";
        return;
    }
    cout<<"\n\nAccount Details\n\n";
    while(file.read((char*)&ac,sizeof(account))){
        if(ac.acc_no_return() == num){
            ac.show_acc();
            flag = true;
        }
    }
    file.close();
    if(flag == false){
        cout<<"\n\nAccount Number doesn't exist."<<endl;
    }
    return;
}

//--------------Display all accounts-------------------------//
void display_all(){
    account ac;
    ifstream file;
    file.open("account.dat",ios::binary|ios::in);
    if(!file){
        cout<<"File could not be opened...Press any key to continue";
        return;
    }

    while(file.read(((char*)&ac),sizeof(account))){
        ac.show_acc();
    }
    file.close();
    return;
}

//--------------Delete an Account----------------------------//
void delete_account(int num){

    account ac;
    bool flag = false;
    ifstream file;
    ofstream file_n;
    file.open("account.dat",ios::binary|ios::in);
    file_n.open("temp.dat",ios::binary|ios::out);
    if(!file){
        cout<<"file couldn't be opened...Press any key to continue";
        return;
    }

    while(!file.eof()){
        file.read((char*)&ac,sizeof(account));
        if(ac.acc_no_return() != num){
            file_n.write((char*)&ac,sizeof(account));
            flag = true;
        }
    }
    file.close();
    file_n.close();
    remove("account.dat");
    rename("temp.dat","account.dat");
    if(!flag){
        cout<<"Account has been successfully deleted";
    }else{
        cout<<"Account number is invalid";
    }

}

//---------------Modify Existing Account---------------------//
void modify_account(int num){

    account ac;
    fstream file;
    bool flag = false;
    file.open("account.dat",ios::binary|ios::in|ios::out);
    if(!file){
        cout<<"file couldn't be opened...Press any key to continue";
        return;
    }

    while(!file.eof() && flag == false){
        file.read((char*)&ac,sizeof(account));
        if(ac.acc_no_return() == num){
            flag = true;
            ac.show_acc();
            cout<<"\n\nEnter the new details of the account\n";
            ac.modify();
            //move the pointer to current position -1
            int pos = sizeof(ac);
            file.seekp(-pos,ios::cur);
            //write the object into account.dat
            file.write((char*)&ac,sizeof(account));
        }
    }
    file.close();
    
}



int main(){
    char ch;
    int num;
    intro();
    cout<<"enter to continue";
    getch();
    do{
        system("cls");
        cout<<"\n\n\nMain Menu"<<endl;
        cout<<"\n\n\t1->New Account";
        cout<<"\n\n\t2->Deposit Amount";
        cout<<"\n\n\t3->Withdraw Amount";
        cout<<"\n\n\t4->Balance Enquiry";
        cout<<"\n\n\t5->All Account Holder List";
        cout<<"\n\n\t6->Close An Account";
        cout<<"\n\n\t7->Modify Amount";
        cout<<"\n\n\t8->Exit";
        cout<<"\n\n\tSelect your option";
        cout<<endl<<endl;
        cin>>ch;
        system("cls");
        switch(ch){
            case '1':
                write_account();
                break;
            case '2':
                cout<<"\n\nEnter the Account Number : ";
                cin>>num;
                deposit_money(num,1);
                break;
            case '3':
                cout<<"\n\nEnter the Account Number : ";
                cin>>num;
                deposit_money(num,2);
                break;
            case '4':
                cout<<"\n\nEnter The account No. : ";
                cin>>num;
                display_sp(num);
                break;
            case '5':
                display_all();
                break;
            case '6':
                cout<<"\n\nEnter The account No. : "; 
                cin>>num;
                delete_account(num);
                break;
            case '7':
                cout<<"\n\nEnter The account No. : "; 
                cin>>num;
                modify_account(num);
                break;
            case '8':
                cout<<"\n\nThanks for using bank managemnt system";
                break;
            default :cout<<"Invalid Input";
            getch();
        }
        cout<<"\n\n\tPress any key to continue"<<endl;
        getch();
        
                
    }while(ch != '8');

    return 0;
}
