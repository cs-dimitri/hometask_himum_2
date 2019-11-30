#include <iostream>
#include <unordered_map>
#include <list>
#include <functional>
#include <fstream>

using namespace std;

template <class T>
class CacheManager
{
private:
    unsigned int _capacity;
    list<pair<T *, string> *> *_buffList;
    unordered_map<string, pair<T *, string> *> *_mapObj;
    ofstream myfile;

public:
    string className;
    CacheManager(int capacity)
    {
        this->_capacity = capacity;
        this->_buffList = new list<pair<T *, string> *>;
        this->_mapObj = new unordered_map<string, pair<T *, string> *>;
    }
    ~CacheManager()
    {
        delete this->_buffList;
        delete this->_mapObj;
    }

    void foreach (const function<void(T &)> func)
    {
        for (pair<T *, string> *mem : *(this->_buffList))
        {
            func(*mem->first);
        }
    }

    void insert(string key, T obj)
    {
        const string nameFile = obj.class_name + key;
        this->className = obj.class_name;
        ofstream file(nameFile, ios::out | ios::trunc | ios::binary);

        if (!file.is_open())
        {
            throw "File is not opened";
        }
        file.write((char *)&obj, sizeof(obj));

        if (this->_buffList->size() >= _capacity) // if capacity was overriden
        {
            string keyOfTail = _buffList->back()->second;
            this->_buffList->pop_back();
            this->_mapObj->erase(keyOfTail);
        }// if there is place for adding without LRU
        pair<T *, string> *pairToInsert = new pair<T *, string>(new T(), key);
        *pairToInsert->first = obj;

        this->_buffList->push_front(pairToInsert);

        this->_mapObj->insert({key, pairToInsert});
        file.close();
    }
    T get(string key) //////UPDATE
    {

        T *toReturn = new T();
        string keyFile;

        pair<T *, string> *pairInsert = new pair<T *, string>;
        string fromFile;

        if (_mapObj->count(key) == 0) // nothing in cashe
        {
            ifstream inFile;

            inFile.open(this->className + key, ios::in | ios::binary);

            if (inFile.is_open())
            {
                inFile.read((char *)toReturn, sizeof(*toReturn));

                this->_mapObj->erase(this->_buffList->back()->second);

                this->_buffList->pop_back();

                pairInsert->second = key;

                pairInsert->first = toReturn;
                this->_buffList->push_front(pairInsert);
                this->_mapObj->insert({key, pairInsert});
            }
            else // file was not opened
            {
                //cout << "File was not found" << endl;
                throw "File was not found";
            }
            inFile.close();
        }
        else // smt in cashe => need to update
        {
            pairInsert->first = _mapObj->at(key)->first;
            pairInsert->second = key;

            toReturn = this->_mapObj->at(key)->first; // getting

            // updating
            //this->_mapObj->at(key);
            this->_buffList->remove(_mapObj->at(key));

            this->_buffList->push_front(pairInsert);

            this->_mapObj->insert({key, pairInsert});
        }
        return *toReturn;
    }
};