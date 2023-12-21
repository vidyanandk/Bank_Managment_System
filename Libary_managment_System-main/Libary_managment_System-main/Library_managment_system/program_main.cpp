#include <iostream>  //for reading and writing on console
#include <fstream>   //for reading and writing from file
#include <string>    //for getline
#include <string.h>  //to read and write string
#include <conio.h>   //for getch
#include <stdlib.h>  //for exit
#include <windows.h> //for sleep used in password function
#include <ctime>
#include <stdio.h>

using namespace std;

// string student_rollNo;===use currentStudent instade....
int issueId;
bool isAvailable = false;
int checkID; // used when we are changing password...

// user class for login...
class user
{
public:
    int id;
    string password;
    int cato;
    user(){};
    user(int id, int pass)
    {
        this->id = id;
        password = pass;
    }
    void display()
    {
        cout << "User ID is:" << id << endl;
    }
};

// univeersal user.......
user currentUser;

// class for book
class book
{
    int id;
    char book_name[50];
    char author[50], status[10];

public:
    book()
    {
        // to store contents of file in it
    }
    book(int i, char c[], char a[], char s[])
    {
        id = i;
        strcpy(book_name, c);
        strcpy(author, a);
        strcpy(status, s);
    }
    void display(book &b)
    {
        cout << "Book id is " << b.id << "\n";
        cout << "Book name is " << b.book_name << "\n";
        cout << "Book author is " << b.author << "\n";
        cout << "Book status is " << b.status << "\n";
    }
    friend int search_book_Info(int);
    friend int modify_book_Record(book b);
    friend int delete_specific_book(int);
    friend int display_specific_book(int);
    friend void issueBook();
    friend void returnBook();
};

// used to search through id
int search_book_Info(int id)
{
    ifstream list("book_list.txt");
    int x = 3;
    string s; // buffer_string
    while (x--)
    {
        getline(list, s);
    }

    int check_id = 0;
    char name[24], auth[10], status[10];
    while (list)
    {
        list >> check_id >> name >> auth >> status;
        book b(check_id, name, auth, status);
        if (b.id == id)
        {
            if (status[0] == 'F')
            {
                isAvailable = true;
            }
            cout << "\nInformation..\n";
            b.display(b);
            x = -1;
            list.close();
            return 1;
        }
    }
    if (x != -1)
    {
        list.close();
        return 0;
    }
    list.close();
    return 0;
}

// add books
void add_specific_book()
{
    book b;

    int id;
    char book_name[50];
    char author[50];
    char status[10] = "Free";
    int n;
    cout << "Enter the number of books, you want to add: \n";
    cin >> n;
    ofstream fout("book_list.txt", ios::app);
    for (int i = 0; i < n; i++)
    {
        cout << "\nFor book " << i + 1 << "\n";
        cout << "\nEnter book id: ";
        cin >> id;
        cin.ignore(); // if we don't use this then while inputting book name and author only one thing will get printed.
        cout << "\nEnter book name: ";
        cin.getline(book_name, 50);
        cout << "\nEnter author of the book: ";
        cin.getline(author, 50);
        book b(id, book_name, author, status);

        fout << id << "\t\t\t" << book_name << "\t\t\t"
             << author << "\t\t\t" << status << endl;
    }
    fout.close();
}

// display books
void book_list_display()
{
    string s;
    ifstream list("book_list.txt");

    // read data from the file student
    getline(list, s);
    while (list)
    {
        cout << s;
        getline(list, s);
        cout << endl;
    }
    list.close();
}

// update or modify book data
int modify_book_Record(book b)
{

    int state = search_book_Info(b.id);
    if (state == 1)
    {
        book rightBook;
        cout << "Enter right book ID: ";
        cin >> rightBook.id;

        cout << "Enter right book Name: ";
        cin >> rightBook.book_name;
        cout << "Enter right book author name: ";
        cin >> rightBook.author;
        cout << "Enter right book Status: ";
        cin >> rightBook.status;

        ofstream fout("book_new_list.txt");
        ifstream fin("book_list.txt");

        int x = 3, id_from_file;
        string s, name_of_book_from_file, author_from_file, status_from_file;
        while (x--)
        {
            getline(fin, s);
            fout << s << endl;
        }
        fin >> id_from_file >> name_of_book_from_file >>
            author_from_file >> status_from_file;
        while (fin)
        {

            if (id_from_file == b.id)
            {
                fout << rightBook.id << "\t\t\t" << rightBook.book_name << "\t\t\t"
                     << rightBook.author << "\t\t\t" << rightBook.status << endl;
            }
            else
            {
                fout << id_from_file << "\t\t\t" << name_of_book_from_file
                     << "\t\t\t" << author_from_file << "\t\t\t" << status_from_file << endl;
            }
            fin >> id_from_file >> name_of_book_from_file >>
                author_from_file >> status_from_file;
        }

        fout.close();
        fin.close();
        remove("book_list.txt");
        rename("book_new_list.txt", "book_list.txt");
        cout << "\nContent updated success\n";
    }
    else
    {
        cout << "\n Id not found";
    }
    return state;
}

// to delete any book
int delete_specific_book(int id)
{
    cout << "Enter book id\n";
    cin >> id;
    int state = search_book_Info(id);
    if (state == 1)
    {
        ofstream fout("book_new_list.txt");
        ifstream fin("book_list.txt");

        int x = 3, id_from_file;
        string s, name_of_book_from_file, author_from_file, status_from_file;
        while (x--)
        {
            getline(fin, s);
            fout << s << endl;
        }
        fin >> id_from_file >> name_of_book_from_file >>
            author_from_file >> status_from_file;
        while (fin)
        {

            if (id_from_file != id)
            {
                fout << id_from_file << "\t\t\t" << name_of_book_from_file << "\t\t\t"
                     << author_from_file << "\t\t\t" << status_from_file << endl;
            }
            fin >> id_from_file >> name_of_book_from_file >>
                author_from_file >> status_from_file;
        }

        fout.close();
        fin.close();
        remove("book_list.txt");
        rename("book_new_list.txt", "book_list.txt");
        cout << "\nBook deleted success...\n";
    }

    else
    {
        cout << "\n Id not found";
    }
    return state;
}

// display specific book
int display_specific_book(int id)
{
    cout << "Enter book id which you want to display: ";
    cin >> id;
    issueId = id;
    int state = search_book_Info(id);
    if (state == 1)
    {
        cout << "\nContent displayed success\n";
    }
    else
    {
        cout << "\nBook Id not found\n";
        exit(0);
    }
    return state;
}

// class to display student
class student : public user
{
    int rollNo;
    char name[30];

public:
    student()
    {
        // to store contents of file in it
    }
    student(int r)
    {
        rollNo = r;
    }
    student(int r, char n[])
    {
        rollNo = r;
        strcpy(name, n);
    }
    void display(student s)
    {
        cout << "Student's roll number is " << s.rollNo << "\n";
        cout << "Student's name is " << s.name << "\n\n";
    }
    friend int studentInfo(int);
    friend int modifyStudent(student s);
    friend int deleteStudent(int);
    int displayStudent(int);
    friend void password();
    friend void issueBook();
    friend void returnBook();
    friend void add_specific_student();
    friend void changePass();
};
// universal student...
student currentstudent;

// used to display data through roll number
int studentInfo(int rollNo)
{
    ifstream student_list("student_list.txt");
    int x = 2;
    string s; // buffer_string
    while (x--)
    {
        getline(student_list, s);
    }

    int roll = 0;
    char name[10];
    while (student_list)
    {
        student_list >> roll >> name;
        student s(roll, name);
        if (s.rollNo == rollNo)
        {
            cout << "\nInformation..\n";
            s.display(s);
            x = -1;
            student_list.close();
            return 1;
        }
    }
    if (x != -1)
    {
        student_list.close();
        return 0;
    }
    student_list.close();
    return 0;
}

// change the  librarian password
void lib_changePass()
{
    system("cls");
    cout << "Please Login Again...\n";
    int a = 0, i = 0, key = 0;
    do
    {
        user currentUser;
        int enterredID;
        string pwordIn;
        char c = ' ';
        cout << "\n\n        ::::::::::::::::::::::::::  LOGIN FORM  ::::::::::::::::::::::::::  ";
        cout << " \n                              ENTER USER ID:-";
        cin >> enterredID;
        if (checkID != enterredID)
        {
            cout << "\nBad credentials...";
            return;
        }
        cout << "                              ENTER OLD PASSWORD:-";
        while (i < 10)
        {
            c = getch();

            if (c == 13)
                break;
            else
                cout << "*";
            i++;
            pwordIn += c;
        }
        i = 0;

        ifstream lib_list("lib_list_pass.txt");
        ofstream lib_new_list("lib_new_list_pass.txt");
        lib_list >> currentUser.id >> currentUser.password;
        while (lib_list)
        {
            lib_list >> currentUser.id >> currentUser.password;
            if (enterredID == currentUser.id && pwordIn == currentUser.password)
            {
                key = 1;
                cout << endl;
                for (i = 0; i < 85; i++)
                {
                    cout << "*";
                }
                cout << "\n\nLOGIN IS SUCCESSFUL..!!!\n\n";
                for (i = 0; i < 85; i++)
                {
                    cout << "*";
                }
                cout << "\n                              ENTER NEW PASSWORD:- ";
                string new_password;
                i = 0;
                while (i < 10)
                {
                    c = getch();

                    if (c == 13)
                        break;
                    else
                        cout << "*";
                    i++;
                    new_password += c;
                }
                lib_new_list << currentUser.id << " " << new_password << endl;
                // lib_list >> currentUser.id >> currentUser.password;
                cout << "\n\n\n\t\t\t\tPress any key to continue...";
                getch();
            }
            else
            {
                lib_new_list << currentUser.id << " " << currentUser.password << endl;
            }
        }
        lib_list.close();
        lib_new_list.close();
        remove("lib_list_pass.txt");
        rename("lib_new_list_pass.txt", "lib_list_pass.txt");

        cout << "\n\n";
        if (key == 0)
        {
            cout << "               SORRY !!!!  LOGIN IS UNSUCESSFUL..!! PLEASE TRY AGAIN";
            a++;
            getch();
        }
        if (key == 1)
        {
            cout << "                PASSWORD CHANGED SUCESSFULLY..!!";
        }
    } while (a <= 3 && key == 0);
    if (a > 3)
    {
        cout << "\n Sorry you have entered the wrong user name or password many times!!!";
        getch();
    }
}

// student change pass
void student_changePass()
{
    system("cls");
    cout << "Please Login Again...\n";
    int a = 0, i = 0, key = 0;
    do
    {
        user currentUser;
        int enterredID;
        string pwordIn;
        char c = ' ';
        cout << "\n\n        ::::::::::::::::::::::::::  LOGIN FORM  ::::::::::::::::::::::::::  ";
        cout << " \n                              ENTER USER ID:-";
        cin >> enterredID;
        if (checkID != enterredID)
        {
            cout << "\nBad credentials...";
            return;
        }
        cout << "                              ENTER OLD PASSWORD:-";
        while (i < 10)
        {
            c = getch();

            if (c == 13)
                break;
            else
                cout << "*";
            i++;
            pwordIn += c;
        }
        i = 0;

        ifstream student_list("student_list_pass.txt");
        ofstream student_pass_list("student_new_list_pass.txt");
        student_list >> currentUser.id >> currentUser.password;
        while (student_list)
        {

            if (enterredID == currentUser.id && pwordIn == currentUser.password)
            {
                key = 1;
                cout << endl;
                for (i = 0; i < 85; i++)
                {
                    cout << "*";
                }
                cout << "\n\nLOGIN IS SUCCESSFUL!!!\n\n";
                for (i = 0; i < 85; i++)
                {
                    cout << "*";
                }
                cout << "\n                              ENTER NEW PASSWORD:- ";
                string new_password;
                i = 0;
                while (i < 10)
                {
                    c = getch();

                    if (c == 13)
                        break;
                    else
                        cout << "*";
                    i++;
                    new_password += c;
                }
                student_pass_list << currentUser.id << " " << new_password << endl;
            }
            else
            {
                student_pass_list << currentUser.id << " " << currentUser.password << endl;
            }
            student_list >> currentUser.id >> currentUser.password;
        }

        student_list.close();
        remove("student_list_pass.txt");

        student_pass_list.close();

        cout << "\n\n";
        if (key == 0)
        {
            cout << "               SORRY !!!!  LOGIN IS UNSUCESSFUL..!! PLEASE TRY AGAIN";
            a++;
            getch();
        }
        if (key == 1)
        {

            rename("student_new_list_pass.txt", "student_list_pass1.txt");
            cout << "                PASSWORD CHANGED SUCESSFULLY..!!";
        }
    } while (a <= 3 && key == 0);
    if (a > 3)
    {
        cout << "\n Sorry you have entered the wrong user name or password many times!!!";
        getch();
    }
}

// add students
void add_specific_student()
{
    ofstream name_list("student_list.txt", ios::app);
    ofstream pass_list("student_list_pass.txt", ios::app);
    int rollNo;
    char name[30];
    int m;
    cout << "Enter the number of students you want to add: \n";
    cin >> m;
    // name_list << endl;
    // pass_list << endl;

    for (int i = 0; i < m; i++)
    {
        cout << "\nFor student: " << i + 1 << "\n";
        cout << "\nEnter student's roll number: ";
        cin >> rollNo;
        cin.ignore(); // if we don't use this then while inputting book name and author only one thing will get printed.
        cout << "\nEnter student's name: ";
        cin.getline(name, 30);
        student s(rollNo, name);

        name_list << s.rollNo << "\t\t" << s.name << endl;
        // name_list.ignore();
        pass_list << s.rollNo << "\t\t"
                  << "0000" << endl;
    }
    name_list.close();
    pass_list.close();
}

// display string...
int student::displayStudent(int rollNo)
{
    // cout << "Enter student roll number which you want to display: ";
    // cin >> rollNo;
    int state = studentInfo(rollNo);
    if (state == 1)
    {
        cout << "\nContent displayed success\n";
    }
    else
    {
        cout << "\nRoll Number not found\n";
        exit(0);
    }
    return state;
}
// modifytudent
int modifyStudent(student stu)
{
    int correctRoll;
    char correctName[10];
    string pass;
    int notUse;

    cout << "Enter the correct Roll Number: ";
    cin >> correctRoll;
    cout << "Enter the correct Name: ";
    cin >> correctName;

    student right_stu(correctRoll, correctName);
    cout << "Old ";
    int state = studentInfo(stu.rollNo);
    if (state == 1)
    {

        ifstream fin("student_list.txt");
        ofstream fout("new_student_list.txt");
        ifstream finPass("student_list_pass.txt");
        ofstream foutPass("new_student_list_pass.txt");

        string s;
        int x = 2;
        while (x--)
        {
            getline(fin, s);
            fout << s << endl;
        }
        int rollNumber_in_list;
        string name_in_list;
        fin >> rollNumber_in_list >> name_in_list;
        finPass >> notUse >> pass;
        while (fin)
        {

            if (stu.rollNo == rollNumber_in_list)
            {
                fout << right_stu.rollNo << "\t\t" << right_stu.name << endl;
                foutPass << right_stu.rollNo << "\t\t" << pass << endl;
            }
            else
            {
                fout << rollNumber_in_list << "\t\t" << name_in_list << endl;
                foutPass << rollNumber_in_list << "\t\t" << pass << endl;
            }
            fin >> rollNumber_in_list >> name_in_list;
            finPass >> notUse >> pass;
        }

        fout.close();
        fin.close();
        finPass.close();
        foutPass.close();
        remove("student_list.txt");
        remove("student_list_pass.txt");
        rename("new_student_list.txt", "student_list.txt");
        rename("new_student_list_pass.txt", "student_list_pass.txt");
        cout << "\nStudent Modifyed successfully....\n";
    }
    else
    {
        cout << "\nRoll Number not found\n";
    }
    return state;
}

// delete any student data
int deleteStudent(int rollNo)
{
    cout << "Enter student's roll number\n";
    cin >> rollNo;
    int notUse;
    string pass;
    int state = studentInfo(rollNo);
    if (state == 1)
    {
        ofstream fout("new_student_list.txt");
        ifstream fin("student_list.txt");
        ifstream finPass("student_list_pass.txt");
        ofstream foutPass("new_student_list_pass.txt");

        string s;
        int x = 2;
        while (x--)
        {
            getline(fin, s);
            fout << s << endl;
        }
        student stu;
        int rollNumber_in_list;
        string name_in_list;
        fin >> rollNumber_in_list >> name_in_list;
        finPass >> notUse >> pass;
        while (fin)
        {
            if (rollNo != rollNumber_in_list)
            {
                fout << rollNumber_in_list << "\t\t" << name_in_list << endl;
                foutPass << rollNumber_in_list << "\t\t" << pass << endl;
            }
            fin >> rollNumber_in_list >> name_in_list;
            finPass >> notUse >> pass;
        }
        fout.close();
        fin.close();
        finPass.close();
        foutPass.close();
        remove("student_list.txt");
        remove("student_list_pass.txt");
        rename("new_student_list.txt", "student_list.txt");
        rename("new_student_list_pass.txt", "student_list_pass.txt");
        cout << "\nStudent deleted success\n";
    }
    else
    {
        cout << "\nRoll Number not found\n";
    }
    return state;
}

void issueBook()
{
    // issuebook i;
    int rollNo = currentstudent.rollNo;
    int id;
    currentstudent.displayStudent(rollNo);
    display_specific_book(id);
    if (!isAvailable)
    {
        cout << "Sorry...!! Book is not available.\n";
        return;
    }
    else
    {
        ifstream previous_list("book_list.txt");
        ofstream new_list("book_new_list.txt");
        int x = 3;
        string s; // buffer_string
        while (x--)
        {
            getline(previous_list, s);
            new_list << s << endl;
        }

        int check_id = 0;
        char name[24], auth[10], status[10];
        previous_list >> check_id >> name >> auth >> status;

        while (previous_list)
        {
            new_list << check_id << "\t\t\t" << name << "\t\t\t" << auth << "\t\t\t";
            book b(check_id, name, auth, status);
            if (b.id == issueId)
            {
                new_list << "Busy\n";
                // new_list << "Busy\t(" << student_rollNo << ")\n";
                // write...
            }
            else
            {
                new_list << status << "\n";
            }
            previous_list >> check_id >> name >> auth >> status;
        }
        previous_list.close();
        new_list.close();

        remove("trash.txt");
        char oldname[] = "book_new_list.txt";
        char oldfile[] = "book_list.txt";
        rename(oldfile, "trash.txt");
        remove("book_list");
        rename(oldname, "book_list.txt");
        cout << "Book sucessfully issued..\n";
    }
    time_t t = time(0); // get time now
    tm *now = localtime(&t);
    cout << "Date:- " << now->tm_mday << '-' << (now->tm_mon + 1) << '-' << (now->tm_year + 1900) << "\n";
}

void returnBook()
{
    // issuebook i;
    int book_id;
    cout << "Enter book id\n";
    cin >> book_id;
    // i.roll = student_rollNo;
    currentstudent.displayStudent(currentstudent.rollNo);
    //////////////////////
    ifstream previous_list("book_list.txt");
    ofstream new_list("book_new_list.txt");
    int x = 3;
    string s; // buffer_string
    while (x--)
    {
        getline(previous_list, s);
        new_list << s << endl;
    }

    int check_id = 0;
    char name[24], auth[10], status[10];
    previous_list >> check_id >> name >> auth >> status;

    while (previous_list)
    {
        new_list << check_id << "\t\t\t" << name << "\t\t\t" << auth << "\t\t\t";
        book b(check_id, name, auth, status);
        if (b.id == book_id)
        {
            new_list << "Free\n";
            // new_list << "Busy\t(" << student_rollNo << ")\n";
            // write...
        }
        else
        {
            new_list << status << "\n";
        }
        previous_list >> check_id >> name >> auth >> status;
    }
    previous_list.close();
    new_list.close();

    remove("trash.txt");
    char oldname[] = "book_new_list.txt";
    char oldfile[] = "book_list.txt";
    rename(oldfile, "trash.txt");
    remove("book_list");
    rename(oldname, "book_list.txt");
    cout << "Book sucessfully returned..\n";

    /////////////////////
}

void studentMenu()
{
    char c;
    int id;
    cout << "--------------------------------------------------WELCOME TO STUDENT'S SECTION----------------------------------------------\n";
    do
    {

        int y;
        cout << "\nChoose any one option:\n";
        cout << "======================\n\n";
        cout << "1 = Display books \n2 = Display Specific Book \n3 = Issue books \n4 = Returning of books \n5 = Exit\n";

        cin >> y;
        switch (y)
        {
        case 1:
            book_list_display();
            break;
        case 2:
            display_specific_book(id);
            break;
        case 3:
            issueBook();
            break;
        case 4:
            returnBook();
            break;
        case 5:
            //     student_changePass();
            //     break;

            // case 6:
            exit(0);
            break;
        default:
            cout << "You enter wrong choice. Please select any other\n";
            break;
        }
        cout << "\nDo you want to continue? Press (y/Y) to continue\n";
        c = getche();
    } while (c == 'y' || c == 'Y');
}

// display student...(function overloading)
void displayStudent()
{
    int rollNo;
    char name[30];

    int x = 2;
    string s;
    ifstream student_list("student_list.txt");
    while (student_list)
    {
        getline(student_list, s);
        cout << s << endl;
    }

    // // student_list >> rollNo >> name;

    // while (student_list)
    // {
    //     student_list >> rollNo >> name;
    //     student stu(rollNo, name);
    //     stu.display(stu);
    // }
    // student_list.close();
}

// specific student...(function overloading...)
void displayStudent(int rollFind)
{
    int rollNo;
    char name[30];

    int x = 2, key = 0;
    string s;
    ifstream student_list("student_list.txt");
    while (x--)
    {
        getline(student_list, s);
    }

    // student_list >> rollNo >> name;

    while (student_list)
    {
        student_list >> rollNo >> name;
        student stu(rollNo, name);
        if (rollNo == rollFind)
        {
            stu.display(stu);
            key++;
            break;
        }
    }
    if (key == 0)
    {
        cout << "Enetered roll number does not exist. \n";
    }
    student_list.close();
}

void librarianMenu()
{
    char c;
    cout << "----------------------------------------------WELCOME TO LIBRARIAN'S SECTION--------------------------------------------\n";
    do
    {
        int id = 0;
        char book_name[50];
        char author[50];
        int rollNo = 0;
        char name[30];
        cout << "\nChoose any one option\n";
        cout << "1 = Display all students  \n2 = Display specific student  \n3 = Modify student  \n4 = Delete student  ";
        cout << "\n5 = Modify Book  \n6 = Delete Book \n7 = Add Book  \n8 = Add student \n";
        cout << "9 = Display specific Book\n10 = Display All Books\n11 = Exit\n";
        int z;
        cin >> z;
        switch (z)
        {
        case 1:
            displayStudent();
            break;
        case 2:
            cout << "Enter student roll number which you want to display: ";
            cin >> rollNo;
            displayStudent(rollNo);
            break;
        case 3:
        {
            int rollNo;
            char name[30];
            cout << "\nEnter student's OLD roll number: ";
            cin >> rollNo;
            student s(rollNo, name);
            modifyStudent(s);
        }
        break;
        case 4:
            deleteStudent(rollNo);
            break;
        case 5:
        {
            int id;
            char book_name[50];
            char author[50], status[10];
            cout << "Enter older book id: ";
            cin >> id;
            book b(id, book_name, author, status);

            modify_book_Record(b);
        }
        break;

        case 6:
            delete_specific_book(id);
            break;
        case 7:

            add_specific_book();
            break;
        case 8:

            add_specific_student();
            break;
        case 9:

            display_specific_book(id);
            break;
        case 10:

            book_list_display();
            break;
        case 11:

            //     lib_changePass();
            //     break;
            // case 12:

            exit(0);
            break;
        default:

            cout << "You entered wrong choice. Please select any other option\n";
            break;
        }

        cout << "Do you want to continue? Press (y/Y) to continue \n";

        c = getche();

    } while (c == 'y' || c == 'Y');
}

void password()
{
    int a = 0, i = 0, key = 0;
    char c = ' ';

    do
    {
        int enterredID;
        string pwordIn;
        cout << "\n\n        ::::::::::::::::::::::::::  LOGIN FORM  ::::::::::::::::::::::::::  ";
        cout << " \n                              ENTER USER ID:-";
        cin >> enterredID;
        cout << "                              ENTER PASSWORD:-";
        while (i < 10)
        {
            c = getch();

            if (c == 13)
                break;
            else
                cout << "*";
            i++;
            pwordIn += c;
        }
        i = 0;
        ifstream lib_list("lib_list_pass.txt");

        while (lib_list)
        {
            lib_list >> currentUser.id >> currentUser.password;
            if (enterredID == currentUser.id && pwordIn == currentUser.password)
            {
                // student_rollNo = currentUser.id;
                key++;
                cout << endl;
                for (i = 0; i < 85; i++)
                {
                    cout << "*";
                }
                cout << "\n\nLOGIN IS SUCCESSFUL!!!\n\n";
                for (i = 0; i < 85; i++)
                {
                    cout << "*";
                }
                cout << "\n\n LOADING PLEASE WAIT...";
                for (i = 0; i < 4; i++)
                {
                    cout << ".";
                    Sleep(450);
                }
                cout << "\n\n\n\t\t\t\tPress any key to continue...";
                checkID = enterredID;
                getch();
                system("cls");

                librarianMenu();

                return;
            }
        }
        lib_list.close();
        // if not a librarian...
        ifstream student_list("student_list_pass.txt");
        if (key != 1)
        {
            while (student_list)
            {
                student_list >> currentUser.id >> currentUser.password;
                if (enterredID == currentUser.id && pwordIn == currentUser.password)
                {
                    currentstudent.rollNo = currentUser.id;

                    key++;
                    cout << endl;
                    for (i = 0; i < 85; i++)
                    {
                        cout << "*";
                    }
                    cout << "\n\nLOGIN IS SUCCESSFUL!!!\n\n";
                    for (i = 0; i < 85; i++)
                    {
                        cout << "*";
                    }
                    cout << "\n\n LOADING PLEASE WAIT...";
                    for (i = 0; i < 4; i++)
                    {
                        cout << ".";
                        Sleep(450);
                    }
                    cout << "\n\n\n\t\t\t\tPress any key to continue...";
                    checkID = enterredID;
                    getch();
                    system("cls");
                    studentMenu();
                    break;
                }
            }
        }
        student_list.close();

        cout << "\n\n";
        if (key == 0)
        {
            cout << "               SORRY !!!!  LOGIN IS UNSUCESSFUL!! PLEASE TRY AGAIN";
            a++;
            getch();
        }
    } while (a <= 3 && key == 0);
    if (a > 3)
    {
        cout << "\n Sorry you have entered the wrong user name or password many times!!!";
        getch();
        exit(0);
    }
    system("cls");
}

int main()
{
    password();
    return 0;
}