#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

int firstDayOfYear, year;
bool leap;

void skip(int n){ for(int i=0; i<n; i++) cout << " ";}

void error(){
    system("cls");
    cout << "\nError. End procedure." << endl;
    exit(-1);
}

bool leapYear(int year){ return ((year%4==0) && (year%100 !=0))||(year%400==0);}

int monthDaysNumber(int m){
    if (m >= 1 && m <= 6) return 31;
    if (m >= 7 && m <= 11) return 30;
    if (m == 12){
        if (leap) return(30);
        return(29);
    }else{error();return 0;}
}

int getFirstDayOfYear(int year){
    int days = 0;
    int that_day = 6; // 1/1/1 was jom'eh
    if(year == 1) return 6;
    for(int i=1; i<=year; i++){
        if(leapYear(i)) days += 366;
        else days += 365;
    }
    int day = days%7;
    while(day > 0){
        if(that_day == 0) that_day = 0;
        else that_day++;
        day--;
    }
    that_day--;
    while(that_day>6 || that_day<0) that_day %= 7;
    return that_day;
}

void printMonthHeader(int m){
    string months[12] = {
        "------Farvardin-----", "-----Ordibehesht----", "-------Khordad------",
		"---------Tir--------", "-------Mordad-------", "------Shahrivar-----",
		"--------Mehr--------", "--------Aban--------", "--------Azar--------",
		"---------Dey--------", "-------Bahman-------", "-------Esfand-------"
	};
	skip(7);
    printf("~%d~\n",year);
    cout << " S  Y  D  S  C  P  \033[2;41;30mJ\033[0m" <<"\n";
    if(m >= 1 && m <= 12){
        cout << months[m-1] << endl;
    } else error();
}

void redPrint(int day){
    cout << "\033[2;41;30m";
    printf("%2d",day);
    cout << "\033[0m ";
}

bool checkToday(int day, int month){
    // ta'tilate rasmi taghvim hejri shamsi
    if(month==1){
        // norooz (1,2,3,4)
        // rooz J.E (12)
        // rooz tabi'at (13)
        if(day==1 || day==2 || day==3 || day==4 || day==12 || day==13){
            return true;
        }
    }
    // rehlate emam (14)
    // ghiam khoonin (15)
    if(month==3 && (day==14 || day==15)) return true;
    // piroozi enghelab eslami (22)
    if(month==11 && day==22) return true;
    // melli shodan san'at naft (29)
    if(month==12 && day==29) return true;
    return false;
}

int getFirstDayOfMonth(int month){
    if(month == 1) return firstDayOfYear;
    int firstDayOfMonth = firstDayOfYear;
    for(int i=2; i<=month; i++){
        int days = monthDaysNumber(i-1);
        firstDayOfMonth += (days%7);
    }
    while(firstDayOfMonth > 6){
        firstDayOfMonth = firstDayOfMonth%7;
    }
    return firstDayOfMonth;
}

void printMonthDays(int month){
    int day = 1;
    int weekDay = getFirstDayOfMonth(month);
    int temp = weekDay;
    while(temp != 0){cout << "   "; temp--;}
    int daysNumber = monthDaysNumber(month);
    while (day <= daysNumber){
        if (weekDay == 6){
            redPrint(day);
            cout << endl;
            weekDay = 0;
        } else {
            if(checkToday(day, month)) redPrint(day);
            else printf("%2d ",day);
            weekDay++;
        }
        day++;
    }
}

void printQuestion(){
    cout << "" << endl;
    cout << "                   _          _" << endl;
    cout << "__      _____  ___| | __   __| | __ _ _   _" << endl;
    cout << "\\ \\ /\\ / / _ \\/ _ \\ |/ /  / _` |/ _` | | | |" << endl;
    cout << " \\ V  V /  __/  __/   <  | (_| | (_| | |_| |" << endl;
    cout << "  \\_/\\_/ \\___|\\___|_|\\_\\  \\__,_|\\__,_|\\__, |" << endl;
    cout << "                                      |___/" << endl;
    cout << "" << endl;
    cout << "\n\t 0 => shanbeh" << endl;
    cout << "\t 1 => yek shanbeh" << endl;
    cout << "\t 2 => do shanbeh" << endl;
    cout << "\t 3 => se shanbeh" << endl;
    cout << "\t 4 => chahar shanbeh" << endl;
    cout << "\t 5 => panj shanbeh" << endl;
    cout << "\t 6 => jom'eh\n" << endl;
    cout << "\t10 => Automaticaly Calculate\n" << endl;
    cout << "Enter the start day: ";
}

int menu(){
    int O;
    cout << "                 _ " << endl;
    cout << " _ __ ___   __ _(_)_ __    _ __ ___   ___ _ __  _   _" << endl;
    cout << "| '_ ` _ \\ / _` | | '_ \\  | '_ ` _ \\ / _ \\ '_ \\| | | |" << endl;
    cout << "| | | | | | (_| | | | | | | | | | | |  __/ | | | |_| |" << endl;
    cout << "|_| |_| |_|\\__,_|_|_| |_| |_| |_| |_|\\___|_| |_|\\__,_|" << endl;
    cout << "" << endl;
    cout << "\n\n\t 1 => Farvardin\n";
    cout << "\t 2 => Ordibehesht\n";
    cout << "\t 3 => Khordad\n";
    cout << "\t 4 => Tir\n";
    cout << "\t 5 => Mordad\n";
    cout << "\t 6 => Shahrivar\n";
    cout << "\t 7 => Mehr\n";
    cout << "\t 8 => Aban\n";
    cout << "\t 9 => Azar\n";
    cout << "\t10 => Dey\n";
    cout << "\t11 => Bahman\n";
    cout << "\t12 => Esfand\n";
    cout << "\t90 => All\n";
    cout << "\t99 => Reset Calendar\n";
    cout << "\t 0 => Exit\n\n";
    cout << "Choose your option: ";
    cin >> O;
    return O;
}

void resetCalendar(){
    system("cls");
    cout << "" << endl;
    cout << "     _             _                _" << endl;
    cout << "    | |   ___ __ _| | ___ _ __   __| | __ _ _ __" << endl;
    cout << " _  | |  / __/ _` | |/ _ \\ '_ \\ / _` |/ _` | '__|" << endl;
    cout << "| |_| | | (_| (_| | |  __/ | | | (_| | (_| | |" << endl;
    cout << " \\___/   \\___\\__,_|_|\\___|_| |_|\\__,_|\\__,_|_|" << endl;
    cout << "" << endl;
    cout << "\n\tEnter the year : ";
    cin >>year;
    leap = leapYear(year);
    system("cls");
    printQuestion();
    cin >> firstDayOfYear;
    if(firstDayOfYear == 10) firstDayOfYear = getFirstDayOfYear(year);
    if(!(firstDayOfYear >= 0 && firstDayOfYear <= 6)){error();}
}

void printWholeCalendar(int month){
    printMonthHeader(month);
    printMonthDays(month);
    cout << "\n\n\n";
}

void testing(){
    year = 1401;
    firstDayOfYear = 2;
    leap = leapYear(year);
    for(int i=1; i<=12; i++){
        int last = monthDaysNumber(i);
        int first = 1;
        int weekday = getFirstDayOfMonth(i);
        cout << "month: " << i << endl;
        while(first <= last){
            if(weekday==6){
                printf("\t%d: %d\n", first, weekday);
                weekday = 0;
            } else {
                printf("\t%d: %d\n", first, weekday);
                weekday++;
            }
            first++;
        }
    }
    cout << "DONE!\n";
    getch();
    exit(-1);
}

int main(){
    //testing();
    int option;
    resetCalendar();
    while(1){
        system("cls");
        option = menu();
        system("cls");

        if(option == 0) break;
        else if (option == 2334) testing();
        else if(option >= 1 && option <= 12) printWholeCalendar(option);
        else if(option == 99){
            resetCalendar();
            cout << "calendar reseted!";
            Sleep(1);
            continue;
        } else for(int i=1; i<=12; i++) printWholeCalendar(i);

        cout << "\n\nPress any key to continue..." << endl;
        getch();
    }
    cout << "\nPress any key to exit!";
    getch();
    return 0;
}
