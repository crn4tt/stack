#pragma once
#include <string>
#include <iomanip>
#include <iostream>
#include <optional>

template <typename T1, typename T2>
class Table{
private:
    size_t _count;
    size_t _size;
    std :: optional<T1>* _col1;
    std :: optional<T2>* _col2;
    std :: string _title1;
    std :: string _title2;
public:
    Table(std :: string title1, std :: string title2, size_t size = 10){
        _title1 = title1;
        _title2 = title2;
        _count = 0;
        _size = size;
        _col1 = new std::optional<T1>[_size];
        _col2 = new std::optional<T2>[_size];
    }

    void AddRow(const std :: optional<T1> &elem1 = std :: nullopt, const std :: optional<T2> &elem2 = std :: nullopt){
        _col1[_count] = elem1;
        _col2[_count++] = elem2;
        if (_count == _size){
            _size *= 2;
            std :: optional<T1>* _colc1 = new std :: optional<T1>[_size];
            std :: optional<T2>* _colc2 = new std :: optional<T2>[_size];
            for (size_t i = 0; i < _size/2; i++){
                _colc1[i] = _col1[i];
                _colc2[i] = _col2[i];
            }
            delete [] _col1;
            delete [] _col2;
            _col1 = _colc1;
            _col2 = _colc2;
        }
    }
    
    size_t GetCount()const{return _count;}

    std::optional<T1> GetValcol1(size_t i)const{return _col1[i];}

    std::optional<T1> GetValcol2(size_t i)const{return _col2[i];}

    T2 GetValKey(T1 key)const{
        for (size_t i = 0; i < _count; i++){
            if (key == _col1[i]) return _col2[i].value();
        }
        return 0;
    }
    T1 GetValKey21(T2 key)const{
        for (size_t i = 0; i < _count; i++){
            if (key == _col1[i]) return _col2[i].value();
        }
        return 0;
    }
    friend std :: ostream& operator<<(std::ostream &os, const Table &table){
        size_t flag = 5;
        os << "+";
        for (size_t i = 0; i < flag * 2; i++){ if(i == flag) os <<"+"; os << "-";}
        os << "+\n";
        os << "|" << std :: setw(flag) << table._title1 << "|" << std :: setw(flag) << table._title2 << "|";
        os << "\n+";
        for (size_t i = 0; i < flag * 2; i++){ if(i == flag)os <<"+"; os << "-";}
        os << "+\n";
        for (size_t i = 0; i < table._count; i++){
            if (table._col1[i] == std::nullopt) os << "|" << std :: setw(flag) << "?";
            else os << "|" << std::setw(flag) << table._col1[i].value();
            os << "|";
            if (table._col2[i] == std::nullopt) os << std :: setw(flag) << "?";
            else os << std::setw(flag) << table._col2[i].value();
            os << "|\n";
        }
        os << "+";
        for (size_t i = 0; i < flag * 2; i++){ if(i == flag)os <<"+"; os << "-";}
        os << "+\n";
        return os;
    }

    ~Table(){
        delete [] _col1;
        delete [] _col2;
    }

};
