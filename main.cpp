//
// Created by Daniela Stepanov on 11/16/19.
//
#include "ex2.h"
#include <iostream>
#include <string>

using namespace std;
// Testing Class
class Student
{
    int id;
    int value;
    const char *data;

public:
    static const string class_name; //every class will have a class static name called: class_name
    Student(int _key, int _value, const char *_data) : id(_key), value(_value), data(_data) {}
    Student(){}; //every class will have a default constructor
    void print()
    {
        cout << "Student Object: " << id << ", " << value << ", " << data << endl;
    };
    ~Student(){};
};
const string Student::class_name = "StudentClass";

using namespace std;
class Employee
{
    const char *name;

public:
    static const string class_name; //every class will have a class static name called: class_name
    Employee(const char *_name) : name(_name){};
    Employee(){}; //every class will have a default constructor
    void print()
    {
        cout << "Employee Object: " << name << endl;
    };
    ~Employee(){};
};
const string Employee::class_name = "EmployeeClass";

int main()
{
    CacheManager<Student> my_cache(3);
    try
    {
        my_cache.insert("0", Student(0, 22, "student1"));
        my_cache.insert("1", Student(1, 23, "student2"));
        my_cache.insert("2", Student(2, 25, "student3"));
        my_cache.insert("3", Student(3, 29, "student4"));
    }
    catch (const char *e)
    {
        cout << e << endl;
    }

    my_cache.foreach ([](Student &s) { s.print(); }); //prints all students in cache
    cout << "\n";

    try
    {
        Student return_obj = my_cache.get("0"); //not in cache but in filesystem
    }
    catch (const char *e)
    {
        cout << e << endl;
    }
    my_cache.foreach([](Student& s){s.print();}); //prints all students in cache
    cout<<"\n";

    try
    {
        auto return_obj2 = my_cache.get("1");
    }
    catch (const char *e)
    {
        cout << e << endl;
    }
    my_cache.foreach ([](Student &s) { s.print(); }); //prints all students in cache
    cout << "\n";
    try
    {
        auto return_obj3 = my_cache.get("2");
    }
    catch (const char *e)
    {
        cout << e << endl;
    }
    my_cache.foreach ([](Student &s) { s.print(); }); //prints all students in cache
    cout << "\n";

    try
    {
        auto return_obj4 = my_cache.get("3");
    }
    catch (const char *e)
    {
        cout << e << endl;
    }
    my_cache.foreach ([](Student &s) { s.print(); }); //prints all students in cache
    cout << "\n";

    CacheManager<Employee> my_2nd_cache(5);
    try
    {
        my_2nd_cache.insert("0", Employee("emp1"));
        my_2nd_cache.insert("1", Employee("emp2"));
        my_2nd_cache.insert("2", Employee("emp3"));
        my_2nd_cache.insert("3", Employee("emp4"));
    }
    catch (const char *e)
    {
        cout << e << endl;
    }
    my_2nd_cache.foreach ([](Employee &g) { g.print(); }); //prints all students in cache
    cout << "\n";
    try
    {
        auto emp3 = my_2nd_cache.get("2");
    }
    catch (const char *e)
    {
        cout << e << endl;
    }
    my_2nd_cache.foreach ([](Employee &g) { g.print(); }); //prints all students in cache
    cout << "\n";

    try
    {
        auto error_obj = my_cache.get("4");
    }
    catch (const char *e)
    {
        cout << e << endl;
    }
    my_2nd_cache.foreach ([](Employee &g) { g.print(); }); //prints all students in cache
    cout << "\n";

    try
    {
        my_2nd_cache.insert("emp_key", Employee("emp5"));
        my_2nd_cache.insert("hello", Employee("emp6"));
        my_2nd_cache.insert("bye", Employee("emp7"));
        my_2nd_cache.insert("some_key", Employee("emp8"));
    }
    catch (const char *e)
    {
        cout << e << endl;
    }
    my_2nd_cache.foreach ([](Employee &g) { g.print(); }); //prints all students in cache
    cout << "\n";

    try
    {
        auto emp1 = my_2nd_cache.get("0");
    }
    catch (const char *e)
    {
        cout << e << endl;
    }

    my_2nd_cache.foreach ([](Employee &g) { g.print(); }); //prints all students in cache
    cout << "\n";

    try
    {
        auto emp5 = my_2nd_cache.get("emp_key");
    }
    catch (const char *e)
    {
        cout << e << endl;
    }
    my_2nd_cache.foreach ([](Employee &g) { g.print(); }); //prints all students in cache
    cout << "\n";

    try
    {
        auto emp6 = my_2nd_cache.get("hello");
    }
    catch (const char *e)
    {
        cout << e << endl;
    }
    my_2nd_cache.foreach ([](Employee &g) { g.print(); }); //prints all students in cache
    cout << "\n";

    //*** ---- I will also perform a check that the files have indeed
    // been created in the same directory as the program-------------***
    return 0;
}