#include "reminder.h"
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
#include <tuple>


std::stringstream out_string_stream;

//получить текущий день
int get_current_day()
{

    //tm* local_time = NULL;
    time_t day = std::time(NULL);
    tm* local_time  = std::localtime(&day);
    int DAY = local_time->tm_mday;
    return DAY;
}

//получить текущий месяц
int get_current_month()
{
    time_t day = std::time(NULL);
    tm* local_time = std::localtime(&day);
    int MONTH = (local_time->tm_mon) + 1;
    return MONTH;
}

//получить текущий год
int get_current_year()
{

    time_t day = std::time(NULL);
    tm* local_time = std::localtime(&day);
    int YEAR = (local_time->tm_year) + 1900;
    return YEAR;
}

std::string get_current_day_of_week()
{

    time_t day = std::time(NULL);
    tm* local_time = std::localtime(&day);
    int WDAY = local_time->tm_wday;

    switch (WDAY)
    {
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


bool check_leap_year(int YEAR)
{
    if ((YEAR % 4 == 0) || (YEAR % 400 == 0))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void print_case(int DAYS);

//==============================================================================
//clas Date
//==============================================================================

Date& Date::operator ++()
{
    if (MONTH == 2)
    {
        if (check_leap_year(YEAR))
        {//  високосный
            if (DAY == 29)
            {
                ++MONTH;
                DAY = 1;
            }
            else
            {
                ++DAY;
            }
        }
        else
        {
            if (DAY == 28)
            {
                ++MONTH;
                DAY = 1;
            }
            else
            {
                ++DAY;
            }
        }
    }
    if (MONTH == 12)
    {
        if (DAY == 31)
        {
            MONTH = 1;
            DAY = 1;
            ++YEAR;
        }
        else
        {
            ++DAY;
        }
    }
    if (MONTH == 4 || MONTH == 6 || MONTH == 9 || MONTH == 11)
    {
        if (DAY == 30)
        {
            ++MONTH;
            DAY = 1;
        }
    }
    else {
        if (DAY == 31)
        {
            ++MONTH;
            DAY = 1;
        }
        else
        {
            ++DAY;
        }
    }
    return *this;
}



Date& Date::operator --()
{
    if (MONTH == 3)
    {
        if (check_leap_year(YEAR))
        {// проверка високосности года
            if (DAY == 1)
            {
                --MONTH;
                DAY = 29;
            }
            else
            {
                --DAY;
            }
        }
        else {
            if (DAY == 1)
            {
                --MONTH;
                DAY = 28;
            }
            else
            {
                --DAY;
            }
        }
    }
    if (MONTH == 1)
    {
        if (DAY == 1)
        {
            MONTH = 12;
            DAY = 31;
            --YEAR;
        }
        else
        {
            --DAY;
        }
    }
    if (MONTH == 5 || MONTH == 7 || MONTH == 10 || MONTH == 12)
    {
        if (DAY == 1)
        {
            --MONTH;
            DAY = 30;
        }
    }
    else
    {
        if (DAY == 1)
        {
            --MONTH;
            DAY = 31;
        }
        else
        {
            --DAY;
        }
    }
    return *this;
}

bool operator > (Date& first, Date& second)

{
    bool FLAG=0;
    int DAY_FIRST = first.get_day();
    int MONTH_FIRST = first.get_month();
    int YEAR_FIRST = first.get_year();

    int DAY_SECOND = second.get_day();
    int MONTH_SECOND = second.get_month();
    int YEAR_SECOND = second.get_year();
    if (YEAR_FIRST > YEAR_SECOND)
    {
        FLAG = 1;
        return FLAG;
    }
    else if (YEAR_FIRST == YEAR_SECOND)
    {
        if (MONTH_FIRST > MONTH_SECOND)
        {
            FLAG = 1;
            return FLAG;
        }
        else if (MONTH_FIRST == MONTH_SECOND)
        {
            if (DAY_FIRST > DAY_SECOND)
            {
                FLAG = 1;
                return FLAG;
            }
            else
            {
                return FLAG;
            }
        }
        else
        {
            return FLAG;
        }
    }
    else
    {
        return FLAG;
    }
}


bool operator == (Date& first, Date& second)
{

    int DAY_FIRST = first.get_day();
    int MONTH_FIRST = first.get_month();
    int YEAR_FIRST = first.get_year();

    int DAY_SECOND = second.get_day();
    int MONTH_SECOND = second.get_month();
    int YEAR_SECOND = second.get_year();

    if ((DAY_FIRST == DAY_SECOND) && (MONTH_FIRST == MONTH_SECOND) && (YEAR_FIRST == YEAR_SECOND))
    {
        return true;
    }
    else
    {
        return false;
    }
}


int Date::get_day()
{
    return DAY;
}

int Date::get_month()
{
    return MONTH;
}

int Date::get_year()
{
    return YEAR;
}

void Date::set_day(int _DAY)
{
    DAY = _DAY;
}

std::string Date::get_string_date()
{
    std::string sDAY= std::to_string(DAY);
    std::string sMONTH;
    std::string sYEAR;
    std::string sDATE;
    if (DAY < 10)
    {
        sDATE = "0" + std::to_string(DAY);
    }
    else
    {
        sDATE = std::to_string(DAY);
    }
    if (MONTH < 10)
    {
        sDATE = sDATE+ ".0" + std::to_string(MONTH);
    }
    else
    {
        sDATE = sDATE + "." + std::to_string(MONTH);
    }
    sDATE = sDATE + "." + std::to_string(YEAR)+"\n";
    return sDATE;
}


void Date::set_month(int _MOUNTH)
{
    MONTH = _MOUNTH;
}

void Date::set_year(int _YEAR)
{
    YEAR = _YEAR;
}

void Date::print_date()
{
    printf(" %02d.%02d.%4d \n", DAY, MONTH, YEAR);

}

void Date::erase()
{
    DAY=0;
    MONTH=0;
    YEAR=0;
}



//получение данных даты рождения из строки
void generate_date(Date* Date, std::string sDATE)
{
    int DATE;
    int j = 0;
    for (int i = 0; i < 3; ++i)
    {
        DATE = 0;
        while (isdigit(sDATE[j]))
        {
            DATE = DATE * 10;
            DATE += (int(sDATE[j]) - 48);
            j++;
        }
        j++;
        if (i == 0)
        {
            Date->set_day(DATE);
        }
        else if (i == 1)
        {
            Date->set_month(DATE);
        }
        else if (i == 2)
        {
            Date->set_year(DATE);
        }
    }
}

//преобразование даты в формат числа int
int get_iDate(Date* Date)
{
    int DATE;
    DATE = (Date->get_month() * MASK_MONTH) + (Date->get_year() * MASK_YEAR) + (Date->get_day() * (MASK_DAY));
    return DATE;
}




//==============================================================================
//class Sorted_Database
//==============================================================================

int Sorted_Database::get_calculated_last_date()
{

    int nDAY = ptrDate->get_day() + iLIMIT_DAYS;
    int nMONTH = ptrDate->get_month();
    int nYEAR = ptrDate->get_year();

    if (nMONTH == 2)
    {
        if (check_leap_year(nYEAR))
        {//  високосный
            if (nDAY > 29) {
                nDAY -= 29;
                ++nMONTH;
            }
        }
        else if (nDAY > 28)
        {
                nDAY -= 28;
                ++nMONTH;
        }
    }

    if (nMONTH == 12)
    {
        if (nDAY > 31)
        {
            nMONTH = 1;
            nDAY = nDAY - 31;
            ++nYEAR;
        }
    }
    if (nMONTH == 4 || nMONTH == 6 || nMONTH == 9 || nMONTH == 11)
    {
        if (nDAY > 30)
        {
            nDAY = nDAY - 30;
            ++nMONTH;
        }
    }
    else
    {
        if (nDAY > 31)
        {
            nDAY = nDAY - 31;
            ++nMONTH;
        }
    }

   Date Date2(nDAY, nMONTH, nYEAR);
   int temp = get_iDate(&Date2);
   return temp;
}

void Sorted_Database::set_iLimit_Days(int LIMIT_DAYS)
{
    iLIMIT_DAYS = LIMIT_DAYS;
}

void Sorted_Database::set_iDate_First(int DATE)
{
    iDATE_FIRST = DATE;
}

int Sorted_Database::get_iLimit_Days()
{
    return iLIMIT_DAYS;
}

int Sorted_Database::get_iDate_First()
{
    return iDATE_FIRST;
}

int Sorted_Database::get_iDate_Last()
{
    return iDATE_LAST;
}

void Sorted_Database::insert(std::string DATE, std::string DATA)
{
    Date Date_temp(0);
    generate_date(&Date_temp, DATE);
    iDATE_TEMP = get_iDate(&Date_temp);
    calculate_Age();
    mDATABASE.insert(make_pair(iDATE_TEMP, DATE + DATA + " - исполнится " + std::to_string(iAGE_TEMP)));
    iDATE_TEMP = 0;
}

void Sorted_Database::insert(int iDATE, std::string DATA)
{
    iDATE_TEMP = iDATE;
    calculate_Age();
    mDATABASE.insert(make_pair(iDATE_TEMP, DATA + " - исполнится " + std::to_string(iAGE_TEMP)));
    iDATE_TEMP = 0;
}



void Sorted_Database::calculate_Age ()
{

    int MONTH = iDATE_TEMP / MASK_MONTH;
    int YEAR= iDATE_TEMP % UNMASK_YEAR;
    iAGE_TEMP = ptrDate->get_year() - YEAR;
    if (ptrDate->get_month() == 12 && MONTH == 1)
    {
        ++iAGE_TEMP;
    }
}


bool Sorted_Database::empty()
{
    return mDATABASE.empty();
}

void Sorted_Database::print()
{
    if (!mDATABASE.empty())
    {
        print_case(get_iLimit_Days());
        std::multimap <int, std::string>::iterator it;
        for (it = mDATABASE.begin(); it != mDATABASE.end(); ++it)
        {
            printf(" %02d.%02d", ((*it).first % MASK_MONTH) / MASK_DAY, ((*it).first / MASK_MONTH));
            std::cout <<" - " << (*it).second << std::endl;
        }
    }
}


void Sorted_Database::out_string()
{
    if (!mDATABASE.empty())

    {
       // std::stringstream out_string_stream;
        out_string_stream<<get_case(get_iLimit_Days())<<"\n";
        //std::cout<<"out_string"<< get_case(get_iLimit_Days())<<"\n";
        std::multimap <int, std::string>::iterator it;
        for (it = mDATABASE.begin(); it != mDATABASE.end(); ++it)
        {

            out_string_stream.left;
            out_string_stream.width(2);
            out_string_stream<<((*it).first % MASK_MONTH) / MASK_DAY;
            out_string_stream.fill('0');
            out_string_stream<<".";
            out_string_stream.width(2);
            out_string_stream.left;
            out_string_stream<<((*it).first / MASK_MONTH);
            out_string_stream.fill('0');
            out_string_stream <<" - " << (*it).second<<"\n";

        }
    }
}



//==============================================================================
//class Sorted_Database_Previous
//==============================================================================

void Sorted_Database_Previous::insert(int iDATE, std::string DATA)
{
    iDATE_TEMP = iDATE;
    calculate_Age();
    mDATABASE.insert(make_pair(iDATE_TEMP, DATA + " - исполнилось " + std::to_string(iAGE_TEMP)));
    iDATE_TEMP = 0;
}



//=================================================================================


// чтение данных из файла
void read_datafile(std::multimap <int, std::string>* ROW_DATABASE)
{
    Date DateTemp(0);
    int DATE;
    std::string sDATE;
    std::string FIRST_SECOND_NAME;
    std::ifstream data_read;
    data_read.open("DATA.txt");
    if (!data_read.is_open())
    { // если файл не открыт
        std::cout << "Файл \"DATA.TXT\" не может быть открыт!" << std::endl;
    }
    else
    {
        while (!data_read.eof())
        {
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

void sorter(std::multimap <int, std::string>* DATABASE, Sorted_Database* SortedDatabase, std::multimap <int, std::string>::iterator* RANGE_FROM_DATE)
{ //искать от одного итератора до другого. второй итератор определяется в зависимости от передаваемого экземпляра класса от iDATE_LAST


    std::multimap <int, std::string>::iterator RANGE_TO_DATE;
    std::multimap <int, std::string>::iterator it;
    RANGE_TO_DATE = DATABASE->upper_bound(SortedDatabase->get_iDate_Last());
    for (*RANGE_FROM_DATE; *RANGE_FROM_DATE != RANGE_TO_DATE; ++(* RANGE_FROM_DATE))
    {
        SortedDatabase->insert((*RANGE_FROM_DATE)->first, (*RANGE_FROM_DATE)->second);
    }
}


//выборка (сортировка) из исходного map в map соответствующий прошедшему с последнего запуска интервалу дней
void sorter(std::multimap <int, std::string>* DATABASE, Sorted_Database_Previous* SortedDatabase, std::multimap <int, std::string>::iterator* RANGE_FROM_DATE)
{//искать от одного итератора до другого. второй итератор определяется в зависимости от передаваемого экземпляра класса от iDATE_LAST


    std::multimap <int, std::string>::iterator RANGE_TO_DATE;
    RANGE_TO_DATE = DATABASE-> upper_bound(SortedDatabase->get_iDate_Last());
    for (*RANGE_FROM_DATE; *RANGE_FROM_DATE != RANGE_TO_DATE; ++(*RANGE_FROM_DATE))
    {
        SortedDatabase->insert((*RANGE_FROM_DATE)->first, (*RANGE_FROM_DATE)->second);
    }
}




std::string get_message_two_weeks()
{
    return "\n\n\nВ ближайшие 2 недели будут дни рождения у сотрудников:\n";
}

std::string get_message_month()
{
    return "\n\n\nВ ближайшиий месяц будут дни рождения у сотрудников:\n";
}

std::string get_message_five_days()
{
    return "\n\n\nВ ближайшие 5 дней будут дни рождения у сотрудников:\n";
}

std::string get_message_today()
{
    return "\n\n\nСегодня день рождения у сотрудников:\n";
}

std::string get_message_past()
{
    return "\n\n\nЗа время с последнего запуска были дни рождения у сотрудников:\n";
}

std::string get_case(const int DAYS)
{

    switch (DAYS)
    {

    case 0:
        return get_message_today();


    case 5:
        return get_message_five_days();


    case 14:
        return get_message_two_weeks();


    case 30:
        return get_message_month();


    case -1:
        return get_message_past();

    }
}


void print_case(const int DAYS)
{

    std::cout<<get_case (DAYS)<<std::endl;
}



//определение итератора, соответствующего текущей дате
void find_iterator(std::multimap <int, std::string>* DATABASE, std::multimap <int, std::string>::iterator* it, Date* Date)
{
    int DATE = (get_iDate(Date)/UNMASK_YEAR)* UNMASK_YEAR;
    *it = DATABASE->upper_bound(DATE);
}


// чтение из файла даты последнего запуска
bool read_date_of_launch(Date* DateOfLastLaunch)
{
    std::string sDATE;
    std::ifstream date_read;

    date_read.open("DATE");
    if (!date_read.is_open())
    { // если файл не открыт
        date_read.close();
        //std::ofstream create_file("DATE");
        //create_file.close();
        return false;
    }
    else
    {
        while (!date_read.eof())
        {
            date_read >> sDATE;
            generate_date(DateOfLastLaunch, sDATE);
        }
        date_read.close();
        return true;
    }
}

// сохранение даты запуска в файл
void save_date_of_launch(Date * Date)
{
    std::ofstream record_to_file;
    record_to_file.open("DATE");
        if (!record_to_file.is_open())
        { // если файл не открыт
            std::cout << "Файл \"DATE\" не может быть открыт или создан!" << std::endl;
        }
        else {
            record_to_file << Date->get_string_date();
            record_to_file.close();
        }
    }

//проверка разницы дат
bool check_downtime(Date* Date_Today, Date* DateOfLastLaunch)
{

    if (*Date_Today > (++(*DateOfLastLaunch)))
    {
        return true;
    }
    else return false;
}
