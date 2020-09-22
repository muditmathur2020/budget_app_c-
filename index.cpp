#include <iostream>
#include <windows.h>
#include<conio.h>
#include <cstdlib>
#include <limits>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>
#include <cctype>
using namespace std;
double balance=0;
int ch=1;


struct MonthlyBudget {
	double housing;
	double utilites;
	double houseHold;
	double transportation;
	double food;
	double medical;
	double insurance;
	double entertainment;
	double clothinng;
	double misc;
};

struct MonthlyExpenses {
	double housingEx;
	double utilitesEx;
	double householdEx;
	double transportationEx;
	double foodEx;
	double medicalEx;
	double insuranceEx;
	double entertainmentEx;
	double clothinngEx;
	double miscEx;
};



int addmoney() {
	double abalance;
	cout<<"\n\n\n\n\n\n\n\n\n\t\tAmount to be added : ";
	cin>>abalance;
	cout<<"\n-----------------Adding "<<abalance<<" to your account-----------------"<<endl;
	balance+=abalance;
	cout<<"\n-----------------Balance successfully updated!-----------------"<<endl;
	cout<<"\nCurrent Balance is "<<balance<<endl<<endl<<endl;
	getch();
}

int deduct() {
	double adeduct;
	cout<<"Amount to be deducted : ";
	cin>>adeduct;
	if(adeduct<=balance) {
		cout<<"\n-----------------Deducting "<<adeduct<<" from your account-----------------"<<endl;
		balance-=adeduct;
		cout<<"\n-----------------Balance successfully updated!-----------------"<<endl;
		cout<<"\nCurrent balance is "<<balance<<endl<<endl<<endl;
		getch();
	} else
		cout<<"-----------------Insufficient Balance-----------------"<<endl<<endl;
	getch();
}



void getMonths(int& months) {
	cout<<"How many months would you like to have analyzed? ";
	cin>>months;

	while(cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(),'\n');
		cout << "Enter valid input ";
		cin >> months;
	}

}

void getMonthlyBudget(fstream& budgetFile, int months) {
	MonthlyBudget mb;
	int count = 1;

	budgetFile.open("budget.bin", ios::out|ios::binary);
	if(budgetFile.fail()) {
		cout<<"Could not find file: budget.bin \n";
		system("read");  //act as system("PAUSE")
	}

	try {
		do {
			cout<<"Enter your housing budget for month "<<count<<":\n";
			cin>>mb.housing;
			cout<<"Enter your utilities budget for month "<<count<<":\n";
			cin>>mb.utilites;
			cout<<"Enter your household expense budget for month "<<count<<":\n";
			cin>>mb.houseHold;
			cout<<"Enter your transportation budget for month "<<count<<":\n";
			cin>>mb.transportation;
			cout<<"Enter your food budget for month "<<count<<":\n";
			cin>>mb.food;
			cout<<"Enter your medical budget for month "<<count<<":\n";
			cin>>mb.medical;
			cout<<"Enter your insurance budget for month "<<count<<":\n";
			cin>>mb.insurance;
			cout<<"Enter your entertainment budget for month "<<count<<":\n";
			cin>>mb.entertainment;
			cout<<"Enter your clothing budget for month "<<count<<":\n";
			cin>>mb.clothinng;
			cout<<"Enter your Miscellaneous budget for month "<<count<<":\n";
			cin>>mb.misc;

			budgetFile.write(reinterpret_cast<char*>(&mb),sizeof(mb));
			count++;
			months --;
		} while(months != 0);
	}

	catch(...) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout<<"Error, invalid input entered.";
	}

	budgetFile.close();
}

void getMonthlyExpenses(fstream& expenseFile, int months) {
	MonthlyExpenses me;
	int count = 1;


	expenseFile.open("expenses.bin", ios::out|ios::binary);
	if(expenseFile.fail()) {
		cout<<"Could not open expenses.bin \n";
		system("read");
	}
	try {
		do {
			cout<<"Enter your housing expenses for month "<<count<<":\n";
			cin>>me.housingEx;
			cout<<"Enter your utilities expenses for month "<<count<<":\n";
			cin>>me.utilitesEx;
			cout<<"Enter the cost of your house hold expenses for month "<<count<<":\n";
			cin>>me.householdEx;
			cout<<"Enter your transportation expenses for month "<<count<<":\n";
			cin>>me.transportationEx;
			cout<<"Enter your food expenses for month "<<count<<":\n";
			cin>>me.foodEx;
			cout<<"Enter your medical expenses for month "<<count<<":\n";
			cin>>me.medicalEx;
			cout<<"Enter your insurance expenses for month "<<count<<":\n";
			cin>>me.insuranceEx;
			cout<<"Enter your entertainment expenses for month "<<count<<":\n";
			cin>>me.entertainmentEx;
			cout<<"Enter your clothing expenses for month "<<count<<":\n";
			cin>>me.clothinngEx;
			cout<<"Enter your Miscellaneous expenses for month "<<count<<":\n";
			cin>>me.miscEx;

			expenseFile.write(reinterpret_cast<char*>(&me),sizeof(me));
			count++;
			months--;
		} while(months!=0);
	}

	catch(...) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout<<"Error, invalid input entered.";
	}
	system("cls");
	expenseFile.close();
}


void getMonthlyReport(fstream& budgetFile, fstream& expenseFile, int months) {
	MonthlyBudget mb;
	MonthlyExpenses me;
	ofstream toFile;

	budgetFile.open("budget.bin", ios::in|ios::binary);
	if(budgetFile.fail()) {
		cout<<"Could not open budget.bin";
		system("read");
	}
	budgetFile.read(reinterpret_cast<char*>(&mb),sizeof(mb));

	expenseFile.open("expenses.bin", ios::in|ios::binary);
	if(expenseFile.fail()) {
		cout<<"Could not open expenses.bin (getMonthlyReport function)";
		system("read");
	}
	expenseFile.read(reinterpret_cast<char*>(&me),sizeof(me));

	while(  !expenseFile.eof() && !budgetFile.eof()  ) {
		//displaying info to screen
		cout<<fixed<<showpoint<<setprecision(2);
		cout<<"--------------------------------------------------------------------\n";
		cout<<left<<setw(14)<<"Category";
		cout<<right<<setw(11)<<"Budget";
		cout<<right<<setw(14)<<"Spent";
		cout<<right<<setw(19)<<"   Over(-)/Under \n";
		cout<<"--------------------------------------------------------------------\n";

		cout<<left<<setw(14)<<"Housing";
		cout<<right<<setw(11)<<mb.housing;
		cout<<right<<setw(14)<<me.housingEx;
		cout<<right<<setw(14)<<(mb.housing - me.housingEx)<<"\n";

		cout<<left<<setw(14)<<"Utilities";
		cout<<right<<setw(11)<<mb.utilites;
		cout<<right<<setw(14)<<me.utilitesEx;
		cout<<right<<setw(14)<<(mb.utilites - me.utilitesEx)<<"\n";

		cout<<left<<setw(14)<<"House Hold";
		cout<<right<<setw(11)<<mb.houseHold;
		cout<<right<<setw(14)<<me.householdEx;
		cout<<right<<setw(14)<<(mb.houseHold - me.householdEx)<<"\n";

		cout<<left<<setw(14)<<"Transportation";
		cout<<right<<setw(11)<<mb.transportation;
		cout<<right<<setw(14)<<me.transportationEx;
		cout<<right<<setw(14)<<(mb.transportation - me.transportationEx)<<"\n";

		cout<<left<<setw(14)<<"Food";
		cout<<right<<setw(11)<<mb.food;
		cout<<right<<setw(14)<<me.foodEx;
		cout<<right<<setw(14)<<(mb.food - me.foodEx)<<"\n";

		cout<<left<<setw(14)<<"Medical";
		cout<<right<<setw(11)<<mb.medical;
		cout<<right<<setw(14)<<me.medicalEx;
		cout<<right<<setw(14)<<(mb.medical - me.medicalEx)<<"\n";

		cout<<left<<setw(14)<<"Insurance";
		cout<<right<<setw(11)<<mb.insurance;
		cout<<right<<setw(14)<<me.insuranceEx;
		cout<<right<<setw(14)<<(mb.insurance - me.insuranceEx)<<"\n";

		cout<<left<<setw(14)<<"Entertainment";
		cout<<right<<setw(11)<<mb.entertainment;
		cout<<right<<setw(14)<<me.entertainmentEx;
		cout<<right<<setw(14)<<(mb.entertainment - me.entertainmentEx)<<"\n";

		cout<<left<<setw(14)<<"Clothing";
		cout<<right<<setw(11)<<mb.clothinng;
		cout<<right<<setw(14)<<me.clothinngEx;
		cout<<right<<setw(14)<<(mb.clothinng - me.clothinngEx)<<"\n";

		cout<<left<<setw(14)<<"Miscellaneous";
		cout<<right<<setw(11)<<mb.misc;
		cout<<right<<setw(14)<<me.miscEx;
		cout<<right<<setw(14)<<(mb.misc - me.miscEx)<<"\n";
		cout<<"For the month you are over(-)/under budget by Rs"<<
		    (mb.housing + mb.utilites + mb.houseHold + mb.transportation + mb.food +
		     mb.medical + mb.insurance + mb.entertainment + mb.clothinng + mb.misc)
		    -
		    (me.housingEx + me.utilitesEx + me.householdEx + me.transportationEx
		     + me.foodEx + me.medicalEx + me.insuranceEx + me.entertainmentEx +
		     me.clothinngEx + me.miscEx )<<"\n";

		//writing to text file
		toFile.open("results.txt",ios::app);
		toFile<<fixed<<showpoint<<setprecision(2);
		toFile<<"--------------------------------------------------------------------\n";
		toFile<<left<<setw(14)<<"Category";
		toFile<<right<<setw(11)<<"Budget";
		toFile<<right<<setw(14)<<"Spent";
		toFile<<right<<setw(19)<<"   Over(-)/Under \n";
		toFile<<"--------------------------------------------------------------------\n";

		toFile<<left<<setw(14)<<"Housing";
		toFile<<right<<setw(11)<<mb.housing;
		toFile<<right<<setw(14)<<me.housingEx;
		toFile<<right<<setw(14)<<(mb.housing - me.housingEx)<<"\n";

		toFile<<left<<setw(14)<<"Utilities";
		toFile<<right<<setw(11)<<mb.utilites;
		toFile<<right<<setw(14)<<me.utilitesEx;
		toFile<<right<<setw(14)<<(mb.utilites - me.utilitesEx)<<"\n";

		toFile<<left<<setw(14)<<"House Hold";
		toFile<<right<<setw(11)<<mb.houseHold;
		toFile<<right<<setw(14)<<me.householdEx;
		toFile<<right<<setw(14)<<(mb.houseHold - me.householdEx)<<"\n";

		toFile<<left<<setw(14)<<"Transportation";
		toFile<<right<<setw(11)<<mb.transportation;
		toFile<<right<<setw(14)<<me.transportationEx;
		toFile<<right<<setw(14)<<(mb.transportation - me.transportationEx)<<"\n";

		toFile<<left<<setw(14)<<"Food";
		toFile<<right<<setw(11)<<mb.food;
		toFile<<right<<setw(14)<<me.foodEx;
		toFile<<right<<setw(14)<<(mb.food - me.foodEx)<<"\n";

		toFile<<left<<setw(14)<<"Medical";
		toFile<<right<<setw(11)<<mb.medical;
		toFile<<right<<setw(14)<<me.medicalEx;
		toFile<<right<<setw(14)<<(mb.medical - me.medicalEx)<<"\n";

		toFile<<left<<setw(14)<<"Insurance";
		toFile<<right<<setw(11)<<mb.insurance;
		toFile<<right<<setw(14)<<me.insuranceEx;
		toFile<<right<<setw(14)<<(mb.insurance - me.insuranceEx)<<"\n";

		toFile<<left<<setw(14)<<"Entertainment";
		toFile<<right<<setw(11)<<mb.entertainment;
		toFile<<right<<setw(14)<<me.entertainmentEx;
		toFile<<right<<setw(14)<<(mb.entertainment - me.entertainmentEx)<<"\n";

		toFile<<left<<setw(14)<<"Clothing";
		toFile<<right<<setw(11)<<mb.clothinng;
		toFile<<right<<setw(14)<<me.clothinngEx;
		toFile<<right<<setw(14)<<(mb.clothinng - me.clothinngEx)<<"\n";

		toFile<<left<<setw(14)<<"Miscellaneous";
		toFile<<right<<setw(11)<<mb.misc;
		toFile<<right<<setw(14)<<me.miscEx;
		toFile<<right<<setw(14)<<(mb.misc - me.miscEx)<<"\n";
		toFile.close();

		expenseFile.read(reinterpret_cast<char*>(&me),sizeof(me));
		budgetFile.read(reinterpret_cast<char*>(&mb),sizeof(mb));
	}
	getch();
	budgetFile.close();
	expenseFile.close();
}



void describeProgram();
void getMonths(int& months);
void getMonthlyBudget(fstream& budgetFile, int months);
void getMonthlyExpenses(fstream& expenseFile, int months);
void getMonthlyReport(fstream& budgetFile, fstream& expenseFile, int months);



void cat() {
	int months = 1;
	fstream budgetFile, expenseFile;

	getMonths(months);
	getMonthlyBudget(budgetFile, months);
	getMonthlyExpenses(expenseFile, months);
	getMonthlyReport(budgetFile, expenseFile, months);
}

void menu() {
	system("cls");
	cout<<"\n\n\n\n\n\t\tChoose from one of the followings:-\n\n";
	cout<<"\t\t1.Add money\n"<<endl;
	cout<<"\t\t2.Deduct money\n"<<endl;
	cout<<"\t\t3.Show Balance\n"<<endl;
	cout<<"\t\t4.Plan your Budget\n"<<endl;
	cout<<"\t\t0.Exit\n"<<endl;
	cout<<"\n\n\t\tEnter your choice: ";
	cin>>ch;
	cout<<"\n";
	switch(ch) {
		case 1:
			system("cls");
			addmoney();
			break;
		case 2:
			system("cls");
			deduct();
			break;
		case 3:
			system("cls");
			cout<<"\n\n\n\n\n\n\n\n\n\t\tAvailable Balance is "<<balance<<endl<<endl<<endl;
			getch();
			break;
		case 4:
			system("cls");
			cat();
			break;
		case 0:
			system("cls");
			cout<<"\n\n\n\n\n\n\n\n\n\t\tThank You For Using MAC Savify :) "<<endl<<endl<<endl;
			getch();
			break;
		default:
			system("cls");
			cout<<"\n\n\n\n\n\n\n\n\n\t\tEnter a valid choice!"<<endl;
			getch();
	}
}





int main() {
	system("Color 7c");

	cout<<"\n\n\n\n\n\n\n\n\n\t\tWELCOME TO THE BEST MONEY MANAGEMENT SOFTWARE"<<"\n\n\t\t\t    M.A.C Savify v3.0"<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tCopyright @ M.A.C Savify 2020\n\n"<<endl;
	getch();
	system("cls");
	while(ch) {
		menu();
	}

	return 0;
}
