#ifndef REMINDER_H
#define REMINDER_H


//#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <string>
#include <ctime>
#include <clocale>
#include <windows.h>
#include <iomanip>
#include <thread>
#include <tuple>

//static std::string OUT_STRING=" ";
extern std::stringstream out_string_stream;


// маски для даты в формате десятичного числа int
const int MASK_MONTH = 1000000;
const int MASK_YEAR = 1;
const int UNMASK_YEAR = 10000;
const int MASK_DAY = 10000;




//получить текущий день
int get_current_day();

//получить текущий месяц
int get_current_month();

//получить текущий год
int get_current_year();

std::string get_current_day_of_week();

bool check_leap_year(int YEAR);

void print_case(int DAYS);

//==============================================================
class Date
{
    int DAY;
    int MONTH;
    int YEAR;

public:
    Date()
    {
        DAY = get_current_day();
        MONTH = get_current_month();
        YEAR = get_current_year();
    }

    Date(int ZERO)
    {
        DAY = 0;
        MONTH =0;
        YEAR = 0;
    }

    Date(int _DAY, int _MONTH, int _YEAR) : DAY(_DAY), MONTH(_MONTH), YEAR(_YEAR)
    {}

    ~Date()
    {}

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


bool operator > (Date& first, Date& second);
bool operator == (Date& first, Date& second);


//получение данных даты рождения из строки
void generate_date(Date* Date, std::string sDATE);

//преобразование даты в формат числа int
int get_iDate(Date* Date);

//======================================================

class Sorted_Database
{
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

    Sorted_Database()
    {}


    Sorted_Database(Date* _Date, int _LIMIT_DAYS=0) : iLIMIT_DAYS(_LIMIT_DAYS)
    {
        ptrDate = _Date;
        sDATE_TEMP = "";
        iDATE_TEMP = 0;
        iAGE_TEMP = 0;
        mDATABASE.clear();
        iDATE_FIRST= ptrDate->get_day()*MASK_DAY+ ptrDate->get_month()*MASK_MONTH + ptrDate->get_year()*MASK_YEAR;
        iDATE_LAST = get_calculated_last_date();
    }


    ~Sorted_Database()
    {
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

    void out_string();

};

//=========================================================

class Sorted_Database_Previous :public Sorted_Database
{
    Date ptrDate_Yesterday;

public:
    Sorted_Database_Previous() =delete;

    Sorted_Database_Previous(Date* _Date_previous, Date _Date_today)
    {
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

    ~Sorted_Database_Previous()
    {
        ptrDate = nullptr;
        mDATABASE.clear();
    }

    void insert(int iDATE, std::string DATA);

};



// чтение даннаых из файла
void read_datafile(std::multimap <int, std::string>* ROW_DATABASE);


//выборка (сортировка) из исходного map в map соответствующий заданному интервалу дней
void sorter(std::multimap <int, std::string>* DATABASE, Sorted_Database* SortedDatabase, std::multimap <int, std::string>::iterator* RANGE_FROM_DATE); //искать от одного итератора до другого. второй итератор определяется в зависимости от передаваемого экземпляра класса от iDATE_LAST
  //нужна перегрузка для наследика сотртердата


//выборка (сортировка) из исходного map в map соответствующий прошедшему с последнего запуска интервалу дней
void sorter(std::multimap <int, std::string>* DATABASE, Sorted_Database_Previous* SortedDatabase, std::multimap <int, std::string>::iterator* RANGE_FROM_DATE); //искать от одного итератора до другого. второй итератор определяется в зависимости от передаваемого экземпляра класса от iDATE_LAST
 //нужна перегрузка для наследика сотртердата


std::string get_message_two_weeks();

std::string get_message_month();

std::string get_message_five_days();

std::string get_message_today();

std::string get_message_past();

std::string get_case(const int DAYS);

void print_case(const int DAYS);

//определение итератора, соответствующего текущей дате
void find_iterator(std::multimap <int, std::string>* DATABASE, std::multimap <int, std::string>::iterator* it, Date* Date);


// чтение из файла даты последнего запуска
bool read_date_of_launch(Date* DateOfLastLaunch);

// сохранение даты запуска в файл
void save_date_of_launch(Date * Date);

//проверка разницы дат
bool check_downtime(Date* Date_Today, Date* DateOfLastLaunch);


#endif // REMAINDER_H
