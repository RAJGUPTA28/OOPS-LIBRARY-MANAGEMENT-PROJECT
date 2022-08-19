#include <iostream>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>


using namespace std;

class Date
{
private:
    int dd;
    int mm;
    int yy;

    void adjustdate()
    {
        if (dd > 30)
        {
            dd -= 30;
            mm++;
        }
        if (mm > 12)
        {
            mm -= 12;
            yy++;
        }
    }

public:
    Date()
    {
        dd = 1;
        mm = 1;
        yy = 2022;
    }
    void setdate()
    {
        cout<<"Date ->"<<endl;
        cout << "Enter Day:";
        cin >> dd;
        cout << "Enter Month:";
        cin >> mm;
        cout << "Enter Year:";
        cin >> yy;
    }

    void setreturndate(Date temp)
    {
        dd = temp.dd + 15;
        mm = temp.yy;
        yy = temp.yy;
        adjustdate();
    }

    void showdate()
    {
        cout << dd << "-" << mm << "-" << yy;
    }
};

class BookData
{
public:
    char title[50];
    char author[35];
    int pages;
    char publisher[40];
    float price;
    int issuedrollNo;
    int status;
    Date issueDate;
    Date returnDate;

    BookData()
    {
        status = 0;
        issuedrollNo = 9999;
    }
};

class StudentData
{
public:
    int rollNo;
    char Name[35];
    char branch[35];
    char address[35];
    int status;
    char BookTitle[50];
    StudentData()
    {
        status = 0;
    }
};

class Book
{
public:
    void inputdetails();
    void modifydetails();
    void searchBook();
    void deleteBook();
    void showallbooks();
};

void Book::inputdetails()
{
    fstream myfile;
    myfile.open("BookStorageDataBase.dat", ios::out | ios::app | ios::binary);

    if (!myfile)
    {
        cout << "Unable to open File" << endl;
        return;
    }

    BookData b1;
    cout << "Enter title :";
    cin >> b1.title;
    cout << "Enter Author :";
    cin >> b1.author;
    cout << "Enter Publisher :";
    cin >> b1.publisher;
    cout << "Enter price :";
    cin >> b1.price;
    cout << "Enter pages :";
    cin >> b1.pages;

    myfile.write((char *)&b1, sizeof(BookData));
    cout<<"Book Added Sucessfully"<<endl;
    myfile.close();
    cin.get();
    cin.get();
}

void Book::modifydetails()
{
    fstream myfile;
    myfile.open("BookStorageDataBase.dat", ios::binary | ios::in | ios::out | ios::ate);
    if (!myfile)
    {
        cout << "Unable to open File" << endl;
        return;
    }

    myfile.seekg(0, ios::beg);

    BookData b1;
    char title[50];
    cout << "Enter Book title: ";
    cin >> title;

    while (myfile.read((char *)&b1, sizeof(BookData)))
    {
        if (strcmp(b1.title, title) == 0)
        {
            int pos = -1 * (sizeof(BookData));
            myfile.seekg(pos, ios::cur);

            cout << "Enter new title :";
            cin >> b1.title;
            cout << "Enter new Author :";
            cin >> b1.author;
            cout << "Enter new Publisher :";
            cin >> b1.publisher;
            cout << "Enter new price :";
            cin >> b1.price;
            cout << "Enter new pages :";
            cin >> b1.pages;

            myfile.write((char *)&b1, sizeof(BookData));
            myfile.close();
            cout << "Record Updated Sucessfully!" << endl;
            cin.get();
            cin.get();
            return;
        }
    }
    myfile.close();
    cout << "Book Not found" << endl;
    cin.get();
    cin.get();
}

void Book::searchBook()
{
    fstream myfile;
    myfile.open("BookStorageDataBase.dat", ios::binary | ios::in);
    if (!myfile)
    {
        cout << "Unable to open File" << endl;
        return;
    }
    myfile.seekg(0 , ios::beg);

    BookData b1;
    char title[50];
    cout << "Enter Book title: ";
    cin >> title;

    while (myfile.read((char *)&b1, sizeof(BookData)))
    {
        if (strcmp(b1.title, title) == 0)
        {
            cout << "\nBook Title : " << b1.title;
            cout << "\nBook author : " << b1.author << " Publisher : " << b1.publisher;
            cout << "\nPages : " << b1.pages << " Price : " << b1.price;
            if (b1.status)
            {
                cout << "\nIssued By (Roll No): " << b1.issuedrollNo;
                cout << "\nIssue Date : ";
                b1.issueDate.showdate();
                cout << "\nReturn Date : ";
                b1.returnDate.showdate();
            }
            else
            {
                cout << "\nIssue Status : NULL";
            }
            cin.get();
            cin.get();
            return;
        }
    }

    cout << "Book Not found" << endl;
    cin.get();
    cin.get();
}

void Book::deleteBook()
{
    fstream myfile;
    fstream mynewfile;
    myfile.open("BookStorageDataBase.dat", ios::binary | ios::in);
    mynewfile.open("tempDB.dat", ios::out | ios::binary);

    myfile.seekg(0 , ios::beg);

    char title[50];
    cin >> title;
    BookData b1;
    bool found = false;

    while (myfile.read((char *)&b1, sizeof(BookData)))
    {
        if (strcmp(b1.title, title) == 0)
        {
            found = true;
            continue;
        }

        mynewfile.write((char *)&b1, sizeof(BookData));
    }

    myfile.close();
    mynewfile.close();
    remove("BookStorageDataBase.dat");
    rename("temp.dat", "BookStorageDataBase.dat");

    if (found)
    {
        cout << "Book Record Removed SucessFully" << endl;
    }
    else
    {
        cout << "Book Not Found" << endl;
    }
    cin.get();
    cin.get();
    return;
}

void Book ::showallbooks()
{
    fstream myfile;
    myfile.open("BookStorageDataBase.dat", ios::binary | ios::in);
    if (!myfile)
    {
        cout << "Unable to open File" << endl;
        return;
    }
    myfile.seekg(0 , ios::beg);
    BookData b1;
    int choice = 1;

    while (myfile.read((char *)&b1, sizeof(BookData)) && choice)
    {
        cout << "\nBook Title : " << b1.title;
        cout << "\nBook author : " << b1.author << " Publisher : " << b1.publisher;
        cout << "\nPages : " << b1.pages << " Price : " << b1.price;
        if (b1.status)
        {
            cout << "\nIssued By (Roll No): " << b1.issuedrollNo;
            cout << "\nIssue Date : ";
            b1.issueDate.showdate();
            cout << "\nReturn Date : ";
            b1.returnDate.showdate();
        }
        else
        {
            cout << "\nIssue Status : NULL";
        }

        cout << "\nEnter (1/0) to view next Book or Exit : ";
        cin >> choice;
    }
    cin.get();
    cin.get();
    return;
}

class Student
{
public:
    void inputStudentdetails();
    void modifyStudentdetails();
    void searchStudent();
    void deleteStudent();
    void showallStudent();
};

void Student::inputStudentdetails()
{
    fstream fp;

    fp.open("StudentDatabase.dat", ios::binary | ios::out | ios::app);
    if (!fp)
    {
        cout << "Unable to open file" << endl;
        return;
    }

    StudentData s1;

    cout << "Enter Name :";
    cin >> s1.Name;
    cout << "Enter RollNo :";
    cin >> s1.rollNo;
    cout << "Enter Branch :";
    cin >> s1.branch;
    cout << "Enter address :";
    cin >> s1.address;

    cout << "Records added to Database" << endl;

    fp.write((char *)&s1, sizeof(StudentData));
    fp.close();

    cin.get();
    cin.get();
}

void Student ::modifyStudentdetails()
{
    fstream fp;
    fp.open("StudentDatabase.dat", ios::binary | ios::in | ios::out | ios::ate);
    if (!fp)
    {
        cout << "Unable to open file" << endl;
        return;
    }

    fp.seekg(0, ios::beg);

    int roll;
    cout << "Enter Roll No. : ";
    cin >> roll;
    StudentData s1;
    while (fp.read((char *)&s1, sizeof(StudentData)))
    {
        if (s1.rollNo == roll)
        {
            int pos = -1 * sizeof(BookData);
            fp.seekg(pos, ios::cur);

            cout << "Enter Name :";
            cin >> s1.Name;
            cout << "Enter RollNo :";
            cin >> s1.rollNo;
            cout << "Enter Branch :";
            cin >> s1.branch;
            cout << "Enter address :";
            cin >> s1.address;

            fp.write((char *)&s1, sizeof(StudentData));
            cout << "Student Record Updated Sucessfully !" << endl;
            fp.close();

            cin.get();
            cin.get();
            return;
        }
    }
    fp.close();
    cout << "Record Not Found" << endl;
    cin.get();
    cin.get();
    return;
}

void Student::searchStudent()
{
    fstream fp;
    fp.open("StudentDatabase.dat", ios::binary | ios::in | ios::out | ios::ate);
    if (!fp)
    {
        cout << "Unable to open file" << endl;
        return;
    }

    int roll;
    cout << "Enter Roll No. : ";
    cin >> roll;
    fp.seekg(0, ios::beg);
    StudentData s1;
    while (fp.read((char *)&s1, sizeof(StudentData)))
    {
        if (s1.rollNo == roll)
        {

            cout << "Records Found" << endl;
            cout << "\nName :" << s1.Name << "\nRoll No : " << s1.rollNo << " Branch : " << s1.branch << endl;
            cout << "Address :" << s1.address << endl;
            if (s1.status == 1)
            {
                cout << "Book Issued : " << s1.BookTitle << endl;
            }
            else
            {
                cout << "No Books issued" << endl;
            }

            cin.get();
            cin.get();
            return;
        }
    }

    fp.close();
    cout << "Record Not Found" << endl;
    cin.get();
    cin.get();
    return;
}

void Student::showallStudent()
{
    fstream fp;
    fp.open("StudentDatabase.dat", ios::binary | ios::in | ios::out | ios::ate);
    if (!fp)
    {
        cout << "Unable to open file" << endl;
        return;
    }
    fp.seekg(0, ios::beg);
    int choice;
    cout << "Enter choice (0/1) : ";
    cin >> choice;

    StudentData s1;
    while (fp.read((char *)&s1, sizeof(StudentData)) && choice)
    {
        cout << "\nName :" << s1.Name << "\nRoll No : " << s1.rollNo << " Branch : " << s1.branch << endl;
        cout << "Address :" << s1.address << endl;
        if (s1.status == 1)
        {
            cout << "Book Issued : " << s1.BookTitle << endl;
        }
        else
        {
            cout << "No Books issued" << endl;
        }

        cout << "To view Next student Press choice (0/1) :";
        cin >> choice;
    }
    cin.get();
    cin.get();
    return;
}

void Student ::deleteStudent()
{
    fstream fp;
    fstream temp;
    fp.open("StudentDatabase.dat", ios::binary | ios::in | ios::out);
    temp.open("temp.dat", ios::binary | ios::in | ios::out);
    if (!fp)
    {
        cout << "Unable to open file" << endl;
        cin.get();
        cin.get();
        return;
    }
    StudentData s1;
    fp.seekg(0, ios::beg);
    bool found = false;
    int roll;
    cout << "Enter Roll No: ";
    cin >> roll;

    while (fp.read((char *)&s1, sizeof(StudentData)))
    {
        if (s1.rollNo == roll)
        {
            found = true;
            continue;
        }

        temp.write((char *)&s1, sizeof(StudentData));
    }

    fp.close();
    remove("StudentDatabase.dat");
    rename("temp.dat", "StudentDatabase.dat");
    temp.close();

    if (found)
    {
        cout << "Student Record Deleted" << endl;
    }
    else
    {
        cout << "Records Not Found" << endl;
    }
    cin.get();
    cin.get();
    return;
}

class MainMenu
{
public:
    void Homepagemenu();
    void BookMenu();
    void StudentMenu();
    void IssueBook();
    void ReturnBook();
};

void MainMenu::Homepagemenu()
{
    cout << "#################### MAIN MENU ####################" << endl;
    cout << "1. Student Menu \n2. Book Menu \n3. IssueBook \n4. Return Book \n5. Exit" << endl;
}

void MainMenu::BookMenu()
{
    cout << "#################### BOOK MENU ####################" << endl;
    cout << "1. ADD New Book \n2. Update Book Details \n3. Search Book \n4. Delete Book \n5. Show all Books" << endl;
}

void MainMenu::StudentMenu()
{
    cout << "#################### BOOK MENU ####################" << endl;
    cout << "1. ADD New Student \n2. Update Student Details \n3. Search Student \n4. Delete Student Entry\n5. Show All Students " << endl;
}

void MainMenu::IssueBook()
{
    fstream st, bk;
    st.open("StudentDatabase.dat", ios::binary | ios::ate | ios::in | ios::out);
    bk.open("BookStorageDataBase.dat", ios::binary | ios::in | ios::out | ios::ate);
    if (!st || !bk)
    {
        cout << "Unable to open file" << endl;
        return;
    }

    st.seekg(0, ios::beg);
    bk.seekg(0, ios::beg);

    int roll;
    bool sfound = false;
    StudentData s1;

    cout << "Enter Roll No. to Issue Book :";
    cin >> roll;

    while (st.read((char *)&s1, sizeof(StudentData)))
    {
        if (s1.rollNo == roll)
        {
            sfound = true;
            int pos = -1 * sizeof(StudentData);
            st.seekg(pos, ios::cur);
            break;
        }
    }

    if (!sfound)
    {
        cout << "Student Not Found" << endl;
        cin.get();
        cin.get();
        st.close();
        bk.close();
        return;
    }

    char title[40];
    bool bfound = false;
    BookData b1;
    cout << "Enter Book Title to Issue : ";
    cin >> title;

    while (bk.read((char *)&b1, sizeof(BookData)))
    {
        if (strcmp(b1.title, title) == 0)
        {
            bfound = true;
            int pos = -1 * sizeof(BookData);
            bk.seekg(pos, ios::cur);
            break;
        }
    }

    if (!bfound)
    {
        cout << "Book Not Found" << endl;
        cin.get();
        cin.get();
        st.close();
        bk.close();
        return;
    }

    if (s1.status != 1 && b1.status != 1)
    {
        strcpy(s1.BookTitle, title);
        s1.status = 1;
        b1.status = 1;
        b1.issuedrollNo = s1.rollNo;
        b1.issueDate.setdate();
        b1.returnDate.setreturndate(b1.issueDate);

        st.write((char *)&s1, sizeof(StudentData));
        bk.write((char *)&b1, sizeof(BookData));

        cout << "Book issued SucessFully" << endl;
        cin.get();
        cin.get();
        st.close();
        bk.close();
    }
    else
    {
        if (s1.status == 1)
        {
            cout << "Student Already Issued Book (Account Full) !" << endl;
            cin.get();
            cin.get();
            st.close();
            bk.close();
            return;
        }
        else
        {
            cout << "Book already Issued" << endl;
            cin.get();
            cin.get();
            st.close();
            bk.close();
            return;
        }
    }
}

void MainMenu::ReturnBook()
{
    fstream st, bk;
    st.open("StudentDatabase.dat", ios::binary | ios::ate | ios::in | ios::out);
    bk.open("BookStorageDataBase.dat", ios::binary | ios::in | ios::out | ios::ate);
    if (!st || !bk)
    {
        cout << "Unable to open file" << endl;
        return;
    }

    st.seekg(0, ios::beg);
    bk.seekg(0, ios::beg);

    int roll;
    bool sfound = false;
    StudentData s1;

    cout << "Enter Roll No. to return Book :";
    cin >> roll;

    while (st.read((char *)&s1, sizeof(StudentData)))
    {
        if (s1.rollNo == roll)
        {
            sfound = true;
            int pos = -1 * sizeof(StudentData);
            st.seekg(pos, ios::cur);
            break;
        }
    }

    if (!sfound)
    {
        cout << "Student Not Found" << endl;
        cin.get();
        cin.get();
        st.close();
        bk.close();
        return;
    }

    char title[40];
    bool bfound = false;
    BookData b1;
    cout << "Enter Book Title to return : ";
    cin >> title;

    while (bk.read((char *)&b1, sizeof(BookData)))
    {
        if (strcmp(b1.title, title) == 0)
        {
            bfound = true;
            int pos = -1 * sizeof(BookData);
            bk.seekg(pos, ios::cur);
            break;
        }
    }

    if (!bfound)
    {
        cout << "Book Not Found" << endl;
        cin.get();
        cin.get();
        st.close();
        bk.close();
        return;
    }

    if (s1.status == 1 && b1.status == 1)
    {

        s1.status = 0;
        b1.status = 1;
        b1.issuedrollNo = -9999;
        st.write((char *)&s1, sizeof(StudentData));
        bk.write((char *)&b1, sizeof(BookData));

        cout << "Book Returned SucessFully" << endl;
        cin.get();
        cin.get();
        st.close();
        bk.close();
    }
    else
    {
        if (s1.status == 0)
        {
            cout << "Student has No Book (Account empty) !" << endl;
            cin.get();
            cin.get();
            st.close();
            bk.close();
            return;
        }
        else
        {
            cout << "Book not Issued" << endl;
            cin.get();
            cin.get();
            st.close();
            bk.close();
            return;
        }
    }
}

main()
{
    int exit = 0;
    char choice[3];
    MainMenu menu;
    while (!exit)
    {   system("CLS");
        menu.Homepagemenu();
        cout << "Enter Your choice : ";
        cin >> choice;

        switch (atoi(choice))
        {
        case 1:
        {
            system("CLS");
            menu.StudentMenu();
            cout << "Enter Your choice : ";
            cin >> choice;
            Student s1;

            switch (atoi(choice))
            {
            case 1:
            {
                s1.inputStudentdetails();
            }
            break;
            case 2:
            {
                s1.modifyStudentdetails();
            }
            break;
            case 3:
            {
                s1.searchStudent();
            }
            break;
            case 4:
            {
                s1.deleteStudent();
            }
            break;
            case 5:
            {
                s1.showallStudent();
            }
            break;

            case 6:
                break;
            default:
            {
                cout << "Invalid Input !" << endl;
            }
            break;
            }
        }
        break;

        case 2:
        {
            system("CLS");
            menu.BookMenu();
            cout << "Enter Your choice : ";
            cin >> choice;
            Book b1;
            switch (atoi(choice))
            {
            case 1:
            {
                b1.inputdetails();
            }
            break;
            case 2:
            {
                b1.modifydetails();
            }
            break;
            case 3:
            {
                b1.searchBook();
            }
            break;
            case 4:
            {
                b1.deleteBook();
            }
            break;
            case 5:
            {
                b1.showallbooks();
            }
            case 6:
                break;

            default:
            {
                cout << "Invalid Input !" << endl;
            }
            break;
            }
        }
        break;
        case 3:
        {
            menu.IssueBook();
        }
        break;
        case 4:
        {
            menu.ReturnBook();
        }
        break;
        case 5:
            exit = 1;
        default:
        {
            cout << "Enter a valid Choice : ";
            cin >> choice;
        }
        break;
        }
    }

    return 0;
}