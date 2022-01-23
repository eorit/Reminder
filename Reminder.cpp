/*
Для напоминания о приближающихся днях рождениях сотрудников (прошедших с последнего запуска, сегодня, в ближашую неделю, две), с подсчетом возраста,
перечень которых указанн в текстовом файле. 

made by Palatov A.M.
*/

/*
Требуются доработки:
*автозакрытие окна после 5-10 минут 
*Контролировать наличие данных в map'ах. Если пустые - окно не выводить, прерывать программу
*Вывести в строку с сегодняшней датой день недели
*Обработка данных при считывании из файла
*добавить функцию сортер- на входе строка из файла и мапы из пункта ниже
*При считывании формирование нескольких map –сегодня, пять дней(мб 7 ? ), 2 недели
*Убрать год рождения в выводе, оставить только день месяц
*Учет високосных лет при расчетах,
*Формулировки для 1 или нескольких сотрудников
* уйти от коунтера\считывать данный из файла пока есть
* сохранять последнюю дату запуска и при последующем запуске показывать прошедшие ДР с момента запуска
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



int get_counter() {  
    int COUNTER;
    std::ifstream counter_read;
    counter_read.open("counter");
    counter_read >> COUNTER;
    counter_read.close();
    return COUNTER;
}


void get_data(int* DAY, int* MOUNTH, int* YEAR, std::string sDATA) {  

    int DATA;
    int j = 0;
    for (int i = 0; i < 3; ++i) {
        DATA = 0;
        while (isdigit(sDATA[j])) {

            DATA = DATA * 10;
            DATA += (int(sDATA[j]) - 48);
            j++;
           
        }
        j++;
        if (i == 0) {
            *DAY = DATA;
        }
        else if (i == 1) {
            *MOUNTH = DATA;
        }
        else if (i == 2) {
            *YEAR = DATA;
        }
    } 
}

int MASK_MOUNTH = 100;
int MASK_YEAR = 10000;

int get_iData(int* DAY, int* MOUNTH, int* YEAR) {
 
    int DATA;
    DATA = ((*MOUNTH) * (MASK_MOUNTH)) + ((*YEAR) * (MASK_YEAR)) + *DAY;
    return DATA;
}



void read_birthday(std::map <int, std::string>* DATABASE, const int COUNTER, int* DAY, int* MOUNTH, int* YEAR) {
    int DATA;
    std::string sDATA;
    std::string FIRST_SECOND_NAME;
    std::ifstream data_read;
    data_read.open("DATA.txt");
    for (int i = 0; i < COUNTER; ++i) {
        data_read>>sDATA;
        get_data(DAY, MOUNTH, YEAR, sDATA);
        DATA = get_iData(DAY, MOUNTH, YEAR);
        std::getline(data_read, FIRST_SECOND_NAME);
        DATABASE->insert(make_pair(DATA, FIRST_SECOND_NAME));
    }
    data_read.close();
}



int get_current_day() {

    tm* local_time = NULL;
    time_t day = std::time(NULL);
    local_time = std::gmtime(&day);

    int DAY = local_time->tm_mday;
    return DAY;
}

int get_current_mounth() {

    tm* local_time = NULL;
    time_t day = std::time(NULL);
    local_time = std::gmtime(&day);

    int MOUNTH = (local_time->tm_mon) + 1;
    return MOUNTH;
}

int get_current_year() {

    tm* local_time = NULL;
    time_t day = std::time(NULL);
    local_time = std::gmtime(&day);
    int YEAR = (local_time->tm_year) + 1900;
    return YEAR;
}

int get_DATA2(int* DAY, int* MOUNTH, int* YEAR, int* DAYS) {
   
    int nDAY = *DAY + *DAYS;
    int nMOUNTH = *MOUNTH;
    int nYEAR = *YEAR;
    int DATA2;

    if (nDAY > 28) {
        if (nMOUNTH == 2) {
            nDAY -= 28;
            ++nMOUNTH;
        }
        if (nMOUNTH == 4 || nMOUNTH == 6 || nMOUNTH == 9 || nMOUNTH == 11) {
            nDAY -= 30;
            ++nMOUNTH;
        }

        else {
            nDAY -= 31;
            ++nMOUNTH;
        }

        if (nMOUNTH > 12) {
            nMOUNTH = nMOUNTH - 12;
            ++nYEAR;
        }
    }

   

    DATA2 = get_iData(&nDAY, &nMOUNTH, &nYEAR);
    
    return DATA2;
}



void print_two_weeks() {
    std::cout << "\n\n\nВ ближайшие 2 недели будут дни рождения у сотрудников:\n" << std::endl;
}

void print_mounth() {
    std::cout << "\n\n\nВ ближайшиий месяц будут дни рождения у сотрудников:\n" << std::endl;
}

void print_fdays() {
    std::cout << "\n\n\nВ ближайшие 5 дней будут дни рождения у сотрудников:\n" << std::endl;
}
void print_today() {
    std::cout << "\n\n\nСегодня день рождения у сотрудников:\n" << std::endl;
}


void print_case(int DAYS, int* d_case) {

    if (DAYS == 0 && *d_case == 1) {
        print_today();

    }
    if (DAYS == 5 && *d_case == 1) {
        print_fdays();
    }
    if (DAYS == 14 && *d_case == 1) {
        print_two_weeks();
    }
    if (DAYS == 30 && *d_case == 1) {
        print_mounth();
    }
    *d_case = 0;

}
void print_lists(std::map <int, std::string>* DATABASE, int* DATA, int* DATA2, int CUR_MOUNTH, int CUR_YEAR, int DAYS = 0) {
   
    int d_case = 1;
    int DAY;
    int MOUNTH;
    int YEAR;
   

    //==============================================
    std::map<int, std::string>::iterator it;
   

    for (it = DATABASE->begin(); it != DATABASE->end(); ++it) {
        
        DAY = ((*it).first) % 100;
        MOUNTH = ((*it).first / MASK_MOUNTH) % 100;
        YEAR = (*it).first / MASK_YEAR;
        int AGE = CUR_YEAR - YEAR;
        if (CUR_MOUNTH == 12 && MOUNTH == 1) {
            ++AGE;
        }

     

        if (((*it).first + AGE * MASK_YEAR >= *DATA) && ((*it).first + AGE * MASK_YEAR <= *DATA2)) {
            print_case(DAYS, &d_case);
            std::cout << DAY << "." << MOUNTH << "." << YEAR << " - " << (*it).second << std::endl;

        }
    }
   

    //=============================================

}





int main()
{
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


    std::map <int, std::string> DATABASE;

    int TEMP;
    int COUNTER;

    int DAY;
    int MOUNTH;
    int YEAR;
    int DATA;
    int DATA_NEXT_TWO_WEEK;
    int DATA_NEXT_MOUNTH;
    int DATA_FIVE_DAYS;


    int B_DAY;
    int B_MOUNTH;
    int B_YEAR;

    int INTERVAL_FIVE_DAYS = 5;
    int INTERVAL_TWO_WEEK = 14;
    int INTERVAL_NEXT_MOUNTH = 30;


    DAY = get_current_day();
    MOUNTH = get_current_mounth();
    YEAR = get_current_year();

    std::cout << "Сегодня: " << DAY << "." << MOUNTH << "." << YEAR << "\n" << std::endl;

    DATA = get_iData(&DAY, &MOUNTH, &YEAR);
    DATA_NEXT_TWO_WEEK = get_DATA2(&DAY, &MOUNTH, &YEAR, &INTERVAL_TWO_WEEK);
    DATA_NEXT_MOUNTH = get_DATA2(&DAY, &MOUNTH, &YEAR, &INTERVAL_NEXT_MOUNTH);
    DATA_FIVE_DAYS = get_DATA2(&DAY, &MOUNTH, &YEAR, &INTERVAL_FIVE_DAYS);

    COUNTER = get_counter();

    read_birthday(&DATABASE, COUNTER, &B_DAY, &B_MOUNTH, &B_YEAR);
 
    print_lists(&DATABASE, &DATA, &DATA, MOUNTH, YEAR);
   
    print_lists(&DATABASE, &DATA, &DATA_FIVE_DAYS, MOUNTH, YEAR, INTERVAL_FIVE_DAYS);
   
    print_lists(&DATABASE, &DATA, &DATA_NEXT_TWO_WEEK, MOUNTH, YEAR, INTERVAL_TWO_WEEK);
  
    print_lists(&DATABASE, &DATA, &DATA_NEXT_MOUNTH, MOUNTH, YEAR, INTERVAL_NEXT_MOUNTH);


    getchar();
    return 0;
}
