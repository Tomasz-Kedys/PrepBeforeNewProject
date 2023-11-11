#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include "Markup.h"

using namespace std;

string changeFormOFMonth(string monthWord){
    string monthNumber = "";

    vector <string> months = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    for(int i = 0; i < (int) months.size(); i++){
        if (monthWord == months[i]){
            return to_string(i+1);
        }
    }
    return monthNumber;
}

string getdaymonthyear(){

    string partOfDate = "";
    int partOfDateNumNum = 0;
    string dayOftheWeek = "", month = "", dayOfTheMonth = "", timeOfTheDay = "", year = "";

    time_t now = time (0);

    char* date_time = ctime (&now);

    string date = date_time;
    string date2 = "";
    date.erase(date.end()-1);
    date += " ";

    cout << date << endl << endl;

    for( int charPos = 0; charPos <= (int) date.length(); charPos++){
        if(date[charPos] != ' '){
            partOfDate += date[charPos];
        }else{
            partOfDateNumNum++;
            switch (partOfDateNumNum){
            case 1:
                dayOftheWeek = partOfDate;
                break;
            case 2:
                month = partOfDate;
                break;
            case 3:
                dayOfTheMonth = partOfDate;
                break;
            case 4:
                break;
            case 5:
                year = partOfDate;
                break;
            }
            partOfDate = "";
        }
    }
    cout << "The current date and time is:" << endl;
    cout << "Day of the month : " << dayOfTheMonth << endl;
    cout << "Month : " << month << endl;
    cout << "Year : " << year << endl;
    cout << "Day of the week : " << dayOftheWeek << endl;

    month = changeFormOFMonth(month);

    date2 = year +"/"+ month +"/"+ dayOfTheMonth;
    cout << endl << date2 << endl;
    system("pause");

    return date2;
}

void comparetwodates(){
    int day1, day2, month1, month2, year1, year2;
    int date1, date2;

    cout << "Give Date in format yyyy/mm/dd : ";
    cin >> year1;
    cin >> month1;
    cin >> day1;
    cin.sync();

    cout << year1 << month1 << day1 << endl;

    cout << "And another one : ";
    cin >> year2;
    cin >> month2;
    cin >> day2;
    cin.sync();

    cout << year2 << month2 << day2 << endl;

    //which is newer

    date1 = (year1 * 10000) + ( month1 * 100) + day1;
    date2 = (year2 * 10000) + ( month2 * 100) + day2;

    if(date1 > date2){
        cout << "Date " << date1 << " Date " << date2 << endl;
    }else if( date2 > date1 ){
        cout << "Date " << date2 << " Date " << date1 << endl;
    }else{
        cout << "Dates are the same" << endl;
    }
}

int getincome(){

    int income;

    cout << "How much money you got today?";
    cin >> income;

    return income;
}

void savetofile(int id, int income, string date){

    CMarkup xml;

    bool fileExists = xml.Load ( "incomes.xml" );

    if (!fileExists)
    {
        xml.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        xml.AddElem("Incomes");
    }

    xml.FindElem();
    xml.IntoElem();
    xml.AddElem("income");
    xml.IntoElem();
    xml.AddElem("Id", id);
    xml.AddElem("Date", date);
    xml.AddElem("Amount", income);
    xml.Save ("incomes.xml");
}

void readthefile(){

    string date2 = "", income2 = "";

    CMarkup xml;

    xml.Load ( "incomes.xml" );

    xml.FindElem();
    xml.IntoElem();
    while(xml.FindElem("income")){
        xml.IntoElem();
        xml.FindElem("Id");
        if(atoi(MCD_2PCSZ(xml.GetData()))==2){
            xml.FindElem("Date");
            date2 = xml.GetData();
            xml.FindElem("Amount");
            income2 = atoi(MCD_2PCSZ(xml.GetData()));
            cout << income2 << endl;
            cout <<  date2 << endl;
        }
        cout << "ataa" << endl;
        xml.OutOfElem();
    }
}

void weeeemonth(int month, int year){

    if((month==2) && ((year%400==0) || ((year%100!=0)&&(year%4==0)))){
        cout<<"Number of days is 29";
    }
    else if(month==2){
        cout<<"Number of days is 28";
    }
    else if(month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12){
        cout<<"Number of days is 31";
    }
    else if(month==4 || month==6 || month==9 || month==11){
        cout<<"Number of days is 30";
    }
    else cout<<"Invalid month";
}

int main() {

    savetofile(3,256,getdaymonthyear());

    return 0;
}
