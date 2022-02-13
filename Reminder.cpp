/*
Для напоминания о приближающихся днях рождениях сотрудников (прошедших с последнего запуска, сегодня, в ближашую неделю, две), с подсчетом возраста,
перечень которых указанн в текстовом файле. 

made by Palatov A.M.
*/


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <string>
#include <ctime>
#include <clocale>
#include <windows.h>
#include <iomanip>
#include <thread>
//#include <tuple>
//#include <chrono>

/* todo
*Формулировки для 1 или нескольких сотрудников
*/

// маски для даты в формате десятичного числа int 
int MASK_MONTH = 1000000;
int MASK_YEAR = 1;
int UNMASK_YEAR = 10000;
int MASK_DAY = 10000;

//получить текущий день
int get_current_day() {

    //tm* local_time = NULL;
    time_t day = std::time(NULL);
    tm* local_time  = std::localtime(&day);
    int DAY = local_time->tm_mday;
    return DAY;
}

//получить текущий месяц
int get_current_month() {

    time_t day = std::time(NULL);
    tm* local_time = std::localtime(&day);
    int MONTH = (local_time->tm_mon) + 1;
    return MONTH;
}

//получить текущий год
int get_current_year() {

    time_t day = std::time(NULL);
    tm* local_time = std::localtime(&day);
    int YEAR = (local_time->tm_year) + 1900;
    return YEAR;
}

std::string get_current_day_of_week() {

    time_t day = std::time(NULL);
    tm* local_time = std::localtime(&day);
    //std::cout << day << " ";
    char* dt = ctime(&day);
    int WDAY = local_time->tm_wday;
   
    switch (WDAY){
        case 0:
            return "Воскресенье";
        case 1:
            return "Понедельник";
        case 2:
            return "Вторник";
        case 3:
            return "Среда";
        case 4:
            return "Четверг";
        case 5:
            return "Пятница";
        case 6:
            return "Суббота";
    };

}

void print_case(int DAYS);


class Date {
    int DAY;
    int MONTH;
    int YEAR;

public:
    Date() {
        DAY = get_current_day();
        MONTH = get_current_month();
        YEAR = get_current_year();
    };
    Date(int ZERO) {
        DAY = 0;
        MONTH =0;
        YEAR = 0;
    }
    Date(int _DAY, int _MONTH, int _YEAR) : DAY(_DAY), MONTH(_MONTH), YEAR(_YEAR) {
    };
    ~Date() {
    };

    int get_day();
    int get_month();
    int get_year();
    std::string get_string_date();
    void set_day(int _DAY);
    void set_month(int _MONTH);
    void set_year(int _YEAR);
    void print_date();
    void erase();
    Date& operator ++();
    Date& operator --();
    friend bool  operator > (Date& first, Date& second);
    friend bool  operator == (Date& first, Date& second);
};


Date& Date::operator ++() {
    if (MONTH == 2) {
        if ((YEAR % 4 == 0) || (YEAR % 400 == 0)) {//year  високосный
            if (DAY == 29) {
                ++MONTH;
                DAY = 1;
            }
            else {
                ++DAY;
            }
        }
        else {
            if (DAY == 28) {
                ++MONTH;
                DAY = 1;
            }
            else {
                ++DAY;
            }
        }
    }
    if (MONTH == 12) {
        if (DAY == 31) {
            MONTH = 1;
            DAY = 1;
            ++YEAR;
        }
        else {
            ++DAY;
        }
    }
    if (MONTH == 4 || MONTH == 6 || MONTH == 9 || MONTH == 11) {
        if (DAY == 30) {
            ++MONTH;
            DAY = 1;
        }
    }
    else {
        if (DAY == 31) {
            ++MONTH;
            DAY = 1;
        }
        else {
            ++DAY;
        }
    }
    return *this;
}



Date& Date::operator --() {
    if (MONTH == 3) {
        if ((YEAR % 4 == 0) || (YEAR % 400 == 0)) {// проверка високосности года
            if (DAY == 1) {
                --MONTH;
                DAY = 29;
            }
            else {
                --DAY;
            }
        }
        else {
            if (DAY == 1) {
                --MONTH;
                DAY = 28;
            }
            else {
                --DAY;
            }
        }
    }
    if (MONTH == 1) {
        if (DAY == 1) {
            MONTH = 12;
            DAY = 31;
            --YEAR;
        }
        else {
            --DAY;
        }
    }
    if (MONTH == 5 || MONTH == 7 || MONTH == 10 || MONTH == 12) {
        if (DAY == 1) {
            --MONTH;
            DAY = 30;
        }
    }
    else {
        if (DAY == 1) {
            --MONTH;
            DAY = 31;
        }
        else {
            --DAY;
        }
    }
    return *this;
}



bool operator > (Date& first, Date& second) {
    bool FLAG=0;
    int DAY_FIRST = first.get_day();
    int MONTH_FIRST = first.get_month();
    int YEAR_FIRST = first.get_year();
    
    
    int DAY_SECOND = second.get_day();
    int MONTH_SECOND = second.get_month();
    int YEAR_SECOND = second.get_year();
    if (YEAR_FIRST > YEAR_SECOND) {
        FLAG = 1;
        return FLAG;
    }
    else if (YEAR_FIRST == YEAR_SECOND){
        if (MONTH_FIRST > MONTH_SECOND) {
            FLAG = 1;
            return FLAG;
        }
        else if (MONTH_FIRST == MONTH_SECOND) {
            if (DAY_FIRST > DAY_SECOND){
                FLAG = 1;
                return FLAG;
            }
            else {
                return FLAG;
            }
        }
        else {
            return FLAG;
        }
    }
    else {
        return FLAG;
    }
}

bool operator == (Date& first, Date& second) {
    
    int DAY_FIRST = first.get_day();
    int MONTH_FIRST = first.get_month();
    int YEAR_FIRST = first.get_year();

    int DAY_SECOND = second.get_day();
    int MONTH_SECOND = second.get_month();
    int YEAR_SECOND = second.get_year();
    
    if ((DAY_FIRST == DAY_SECOND) && (MONTH_FIRST == MONTH_SECOND) && (YEAR_FIRST == YEAR_SECOND)) {
        return true;
    }
    else {
        return false;
    }
}


int Date::get_day() {
    return DAY;
}

int Date::get_month() {
    return MONTH;
}

int Date::get_year() {
    return YEAR;
}

void Date::set_day(int _DAY) {
    DAY = _DAY;
}

std::string Date::get_string_date() {
    std::string sDAY= std::to_string(DAY);
    std::string sMONTH;
    std::string sYEAR;
    std::string sDATE;
    if (DAY < 10) {
        sDATE = "0" + std::to_string(DAY);
    }
    else {
        sDATE = std::to_string(DAY);
    }
    if (MONTH < 10) {
        sDATE = sDATE+ ".0" + std::to_string(MONTH);
    }
    else {
        sDATE = sDATE + "." + std::to_string(MONTH);
    }
    sDATE = sDATE + "." + std::to_string(YEAR);
    return sDATE;
}


void Date::set_month(int _MOUNTH){
    MONTH = _MOUNTH;
}

void Date::set_year(int _YEAR) {
    YEAR = _YEAR;
}

void Date::print_date() {
    printf(" %02d.%02d.%4d \n", DAY, MONTH, YEAR);
}

void Date::erase() {
    DAY=0;
    MONTH=0;
    YEAR=0;
}



//получение данных даты рождения из строки
void generate_date(Date* Date, std::string sDATE) {

  
    int DATE;
    int j = 0;
    for (int i = 0; i < 3; ++i) {
        DATE = 0;
        while (isdigit(sDATE[j])) {
            DATE = DATE * 10; 
            DATE += (int(sDATE[j]) - 48);
            j++;
        }
        j++;
        if (i == 0) {
            Date->set_day(DATE);
        }
        else if (i == 1) {
            Date->set_month(DATE);
        }
        else if (i == 2) {
            Date->set_year(DATE);
        }
    }
}

//преобразование даты в формат числа int
int get_iDate(Date* Date) {
   
    int DATE;
    DATE = (Date->get_month() * MASK_MONTH) + (Date->get_year() * MASK_YEAR) + (Date->get_day() * (MASK_DAY));
    return DATE;
}



class Sorted_Database {
protected:
    int get_calculated_last_date();

    std::multimap <int, std::string> mDATABASE;
    std::string sDATE_TEMP;
    Date* ptrDate;
    int iDATE_TEMP;
    int iAGE_TEMP;
    int iDATE_FIRST;
    int iLIMIT_DAYS;
    int iDATE_LAST;
    
    void calculate_Age();

public:
    
    Sorted_Database() {
        }


    Sorted_Database(Date* _Date, int _LIMIT_DAYS=0) : iLIMIT_DAYS(_LIMIT_DAYS) {   //класс дата же! // было int _iDate -> Date* _Date
        ptrDate = _Date;
        sDATE_TEMP = "";
        iDATE_TEMP = 0;
        iAGE_TEMP = 0;
        mDATABASE.clear();
        iDATE_FIRST= ptrDate->get_day()*MASK_DAY+ ptrDate->get_month()*MASK_MONTH + ptrDate->get_year()*MASK_YEAR;
        iDATE_LAST = get_calculated_last_date();
    }
 

    ~Sorted_Database() {
        ptrDate = nullptr;
        mDATABASE.clear();
    }
    
    void set_sDate_temp(std::string DATE);

    void set_iLimit_Days(int LIMIT_DAYS);

    void set_iDate_First(int DATE);

    int get_iLimit_Days();

    int get_iDate_First();

    int get_iDate_Last();

    void insert(std::string DATE, std::string DATA);
    
    void insert(int iDATE, std::string DATA);

    bool empty();

    void print();

};

int Sorted_Database:: get_calculated_last_date() {

   int nDAY = ptrDate->get_day() + iLIMIT_DAYS;
   int nMONTH = ptrDate->get_month();
   int nYEAR = ptrDate->get_year();

   if (nDAY > 28) {
       if (nMONTH == 2) {
           nDAY -= 28;
           ++nMONTH;
       }
       if (nMONTH == 4 || nMONTH == 6 || nMONTH == 9 || nMONTH == 11) {
           nDAY -= 30;
           ++nMONTH;
       }

       else {
           nDAY -= 31;
           ++nMONTH;
       }

       if (nMONTH > 12) {
           nMONTH = nMONTH - 12;
           ++nYEAR;
       }
   }

 
   Date Date2(nDAY, nMONTH, nYEAR);
   int temp = get_iDate(&Date2);
   return temp;
}

void Sorted_Database::set_iLimit_Days(int LIMIT_DAYS) {
    iLIMIT_DAYS = LIMIT_DAYS;
}

void Sorted_Database::set_iDate_First(int DATE) {
    iDATE_FIRST = DATE;
}

int Sorted_Database::get_iLimit_Days() {
    return iLIMIT_DAYS;
}

int Sorted_Database::get_iDate_First() {
    return iDATE_FIRST;
}

int Sorted_Database::get_iDate_Last() {
    return iDATE_LAST;
}

void Sorted_Database::insert(std::string DATE, std::string DATA) {
    Date Date_temp(0);
    generate_date(&Date_temp, DATE); 
    iDATE_TEMP = get_iDate(&Date_temp);
    mDATABASE.insert(make_pair(iDATE_TEMP, DATE + DATA + " - исполнится " + std::to_string(iAGE_TEMP)));
    iDATE_TEMP = 0;
}

void Sorted_Database::insert(int iDATE, std::string DATA) {
    iDATE_TEMP = iDATE;
    calculate_Age();
    mDATABASE.insert(make_pair(iDATE_TEMP, DATA + " - исполнится " + std::to_string(iAGE_TEMP)));
    iDATE_TEMP = 0;
}


void Sorted_Database::calculate_Age () {

    int MONTH = (iDATE_TEMP % MASK_DAY )/ MASK_MONTH;
    int YEAR= iDATE_TEMP % UNMASK_YEAR;
    iAGE_TEMP = ptrDate->get_year() - YEAR;
    if (ptrDate->get_month() == 12 && MONTH == 1) {
        ++iAGE_TEMP;
    }
}


bool Sorted_Database::empty() {
    return mDATABASE.empty();
}

void Sorted_Database::print() {
    if (!mDATABASE.empty()) {
        print_case(get_iLimit_Days());
        std::multimap <int, std::string>::iterator it;
        for (it = mDATABASE.begin(); it != mDATABASE.end(); ++it) {
            printf(" %02d.%02d", ((*it).first % MASK_MONTH) / MASK_DAY, ((*it).first / MASK_MONTH));
            std::cout <<" - " << (*it).second << std::endl;
        }
    }
}



class Sorted_Database_Previous :public Sorted_Database {
    Date ptrDate_Yesterday;

public:
    Sorted_Database_Previous() {}

    Sorted_Database_Previous(Date* _Date_previous, Date _Date_today) {
        ptrDate = _Date_previous;
        ptrDate_Yesterday = --(_Date_today);
        sDATE_TEMP = "";
        iDATE_TEMP = 0;
        iAGE_TEMP = 0;
        mDATABASE.clear();
        iLIMIT_DAYS = -1;
        iDATE_FIRST = ptrDate->get_day() * MASK_DAY + ptrDate->get_month() * MASK_MONTH + ptrDate->get_year() * MASK_YEAR;
        iDATE_LAST = ptrDate_Yesterday.get_day() * MASK_DAY + ptrDate_Yesterday.get_month() * MASK_MONTH + ptrDate_Yesterday.get_year() * MASK_YEAR;
    }

    ~Sorted_Database_Previous() {
        ptrDate = nullptr;
        mDATABASE.clear();
    }
    
    void insert(int iDATE, std::string DATA);
   
};

void Sorted_Database_Previous::insert(int iDATE, std::string DATA) {
    iDATE_TEMP = iDATE;
    calculate_Age();
    mDATABASE.insert(make_pair(iDATE_TEMP, DATA + " - исполнилось " + std::to_string(iAGE_TEMP)));
    iDATE_TEMP = 0;
}




// чтение даннаых из файла 
void read_datafile(std::multimap <int, std::string>* ROW_DATABASE) { //old read_birthday
    Date DateTemp(0);
    int DATE;
    std::string sDATE;
    std::string FIRST_SECOND_NAME;
    std::ifstream data_read;
    data_read.open("DATA.txt");
    if (!data_read.is_open()) { // если файл не открыт
        std::cout << "Файл \"DATA.TXT\" не может быть открыт!" << std::endl;
    }
    else {
        while (!data_read.eof()) {
            data_read >> sDATE;
            //std::cout<< sDATE;
            generate_date(&DateTemp, sDATE);
            DATE = get_iDate(&DateTemp)/MASK_YEAR; 
            //std::cout<< DATA<<std::endl;
            std::getline(data_read, FIRST_SECOND_NAME);
            //std::cout<< FIRST_SECOND_NAME<<std::endl;
            ROW_DATABASE->insert(make_pair(DATE, FIRST_SECOND_NAME));
            DateTemp.erase();
            DATE = 0;
        }
        
        data_read.close();
    }
}



//выборка (сортировка) из исходного map в map соответствующий заданному интервалу дней 
void sorter(std::multimap <int, std::string>* DATABASE, Sorted_Database* SortedDatabase, std::multimap <int, std::string>::iterator* RANGE_FROM_DATE) { //искать от одного итератора до другого. второй итератор определяется в зависимости от передаваемого экземпляра класса от iDATE_LAST //нужна перегрузка для наследика сотртердата

    std::multimap <int, std::string>::iterator RANGE_TO_DATE;
    std::multimap <int, std::string>::iterator it;
    RANGE_TO_DATE = DATABASE->lower_bound(SortedDatabase->get_iDate_Last());
    for (*RANGE_FROM_DATE; *RANGE_FROM_DATE != RANGE_TO_DATE; ++(* RANGE_FROM_DATE)) {
        SortedDatabase->insert((*RANGE_FROM_DATE)->first, (*RANGE_FROM_DATE)->second);
    }
}
//выборка (сортировка) из исходного map в map соответствующий прошедшему с последнего запуска интервалу дней
void sorter(std::multimap <int, std::string>* DATABASE, Sorted_Database_Previous* SortedDatabase, std::multimap <int, std::string>::iterator* RANGE_FROM_DATE) {//искать от одного итератора до другого. второй итератор определяется в зависимости от передаваемого экземпляра класса от iDATE_LAST //нужна перегрузка для наследика сотртердата

    std::multimap <int, std::string>::iterator RANGE_TO_DATE;
    RANGE_TO_DATE = DATABASE->lower_bound(SortedDatabase->get_iDate_Last());
    for (*RANGE_FROM_DATE; *RANGE_FROM_DATE != RANGE_TO_DATE; ++(*RANGE_FROM_DATE)) {
        SortedDatabase->insert((*RANGE_FROM_DATE)->first, (*RANGE_FROM_DATE)->second);
    }
}



void print_message_two_weeks() {
    std::cout << "\n\n\n В ближайшие 2 недели будут дни рождения у сотрудников:\n" << std::endl;
}

void print_message_month() {
    std::cout << "\n\n\n В ближайшиий месяц будут дни рождения у сотрудников:\n" << std::endl;
}

void print_message_five_days() {
    std::cout << "\n\n\n В ближайшие 5 дней будут дни рождения у сотрудников:\n" << std::endl;
}

void print_message_today() {
    std::cout << "\n\n\n Сегодня день рождения у сотрудников:\n" << std::endl;
}

void print_message_past() {
    std::cout << "\n\n\n За время Вашего отсутствия были дни рождения у сотрудников:\n" << std::endl;
}

void print_case(int DAYS) {

    switch (DAYS) {

    case 0:
        print_message_today();
        break;

    case 5:
        print_message_five_days();
        break;

    case 14:
        print_message_two_weeks();
        break;

    case 30:
        print_message_month();
        break;

    case -1:
        print_message_past();
        break;
    }
}

//определение итератора, соответствующего текущей дате
void find_iterator(std::multimap <int, std::string>* DATABASE, std::multimap <int, std::string>::iterator* it, Date* Date) {
    int DATE = (get_iDate(Date)/UNMASK_YEAR)* UNMASK_YEAR;
    *it = DATABASE->upper_bound(DATE);
}


// чтение из файла даты последнего запуска
void read_date_of_launch(Date* DateOfLastLaunch) {
    std::string sDATE;
    std::ifstream date_read;
    date_read.open("DATE");
    while (!date_read.eof()) {
       date_read >> sDATE;
       generate_date(DateOfLastLaunch, sDATE);
    }
    date_read.close();
}

/// сохранение даты запуска в файл
void save_date_of_launch(Date * Date) {         
    std::ofstream record_to_file;
    record_to_file.open("DATE");
        if (!record_to_file.is_open()) { // если файл не открыт
            std::cout << "Файл \"DATE\" не может быть открыт или создан!" << std::endl; // сообщить об этом
        }
        else {
            record_to_file << Date->get_string_date();
            record_to_file.close();
        }
    }

//проверка разницы дат
bool check_downtime(Date* Date_Today, Date* DateOfLastLaunch) {
        
    if (Date_Today > (++DateOfLastLaunch)) {
        return true;
    }
    else return false;
}


int main()
{
    //настройки консоли-язык, шрифт
        
    //WideCharToMultiByte (CP_UTF8, WC_NO_BEST_FIT_CHARS, pszWideSource, nWideLength, pszByteSource, nByteLegth, NULL, NULL);
    setlocale(LC_ALL, "Russian");
    //SetConsoleCP(CP_UTF8);
    //SetConsoleOutputCP(CP_UTF8);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(fontInfo);
    GetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);
    wcscpy(fontInfo.FaceName, L"Lucida Console");
    fontInfo.dwFontSize.Y = 16;
    SetCurrentConsoleFontEx(hConsole, TRUE, &fontInfo);

    //значнеия для диапазонов дней      
    int INTERVAL_FIVE_DAYS = 5;
    int INTERVAL_TWO_WEEK = 14;
    int INTERVAL_NEXT_MOUNTH = 30;

    //инициализация экземпляров класса
    Date Date_today;
    Date Date_previous(0);

    //инициализация переменной для всех данных
    std::multimap <int, std::string> dbTEMP;
    
    //чтение даннных из файла
    read_datafile(&dbTEMP);
    //чтение даты последенего запуска
    read_date_of_launch(&Date_previous);

    //инициализация экземпляров класса для хранение данных необходимого жиапазона дней
    Sorted_Database Database_next_five_days(&Date_today, INTERVAL_FIVE_DAYS);
    Sorted_Database Database_next_two_week(&Date_today, INTERVAL_TWO_WEEK);
    Sorted_Database Database_today(&Date_today);
    Sorted_Database_Previous Database_past(&Date_previous, Date_today);
    
    //инициализация итератора для определения положения текущей даты в "массиве" данных
    std::multimap <int, std::string>::iterator begin;
    
    //определение положения текущей даты в "массиве" данных
    find_iterator(&dbTEMP, &begin, &Date_today);
    
    //формированиие "массивов" данных заданного диапазона
    sorter(&dbTEMP, &Database_today, &begin);

    sorter(&dbTEMP, &Database_next_five_days, &begin);

    sorter(&dbTEMP, &Database_next_two_week, &begin);

    
    //формирование "массива" данных нужного диапазона для прошедшего после предыдущего включения диапазона
    if (check_downtime(&Date_today, &Date_previous)) {
        find_iterator(&dbTEMP, &begin, &Date_previous);
        sorter(&dbTEMP, &Database_past, &begin);
    }

    //сохранение текущей даты запуска 
    save_date_of_launch(&Date_today);

    //проверка условия вывода-если массивы не пусты и сегодня программа еще не запускалась
    if ((!Database_today.empty() || !Database_next_five_days.empty() || !Database_next_two_week.empty() || !Database_past.empty()) && !(Date_today==Date_previous)) {
        
        std::cout << "\n Сегодня: ";
               
        std::cout << get_current_day_of_week() << " - " ;
        
        Date_today.print_date();
        
        Database_past.print();
        
        Database_today.print();
        
        Database_next_five_days.print();
        
        Database_next_two_week.print();
        
        std::this_thread::sleep_for(std::chrono::minutes(10));
    }
      
    return 0;
}
