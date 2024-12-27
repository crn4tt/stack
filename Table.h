#pragma once
#include <iostream>
#include <iomanip>
#include <optional>


template<typename T1, typename T2>


class Table{
private:
    std::string _title_col1;
    std::string _title_col2;
    size_t _table_size;
    std::optional<T1>* _col1;
    std::optional<T2>* _col2;
    size_t _count;
public:
    Table(std::string s1, std::string s2,size_t size=20){
        _title_col1 = s1;
        _title_col2 = s2;
        _table_size = size;
        _col1 = new std::optional<T1>[_table_size];
        _col2 = new std::optional<T2>[_table_size];
        _count =0;
    }

    size_t GetCount(){
        return _count;
    }

    void AppendRow(std::optional<T1> elem1, std::optional<T2> elem2){
        _col1[_count] = elem1;
        _col2[_count] = elem2;
        _count++;

    }

    std::optional<T2> operator[](const T1& elem){
        std::optional<T1> _elem(elem);
        for (int i = 0; i < _count; i++){
            if (_elem == _col1[i]){
                return _col2[i];
            }
        }
        return std::nullopt;
    }

    bool FindCol1(const T1& elem){
        for (int i = 0; i < _count; i++){
            if (_col1[i] == elem){
                return 1;
            }
        }
        return 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const Table& t){
        os << "|" << std::setw(5) << t._title_col1 << " | " <<std::setw(5) << t._title_col2 << "|" <<std::endl;
        for (size_t i = 0; i < 15; i++){
            std::cout << "-";
        }
        std::cout << std::endl;
        
        for(size_t i = 0; i < t._count; i++){
            if(t._col1[i] == std::nullopt){
                os << std::setw(5) << "no";
            }
            else
            os << std::setw(5) << t._col1[i].value();
            os << "|";
            if (t._col2[i] == std::nullopt){
                os << std::setw(5) << "no";
            }
            else
            os << std::setw(5) << t._col2[i].value();
            std::cout << std::endl;

        }
         for (size_t i = 0; i < 15; i++){
            std::cout << "-";
        }
        return os;
    }





    //в формуле нужно использовать таблицу приоритетов операций, и нужно(возвожно) сделать перегрузку [] для таблицы
};