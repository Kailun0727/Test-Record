// Group_Assignment_Testing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <time.h>

using namespace std;

struct Question {
    char questionText[100];
    char answerA[100];
    char answerB[100];
    char answerC[100];
    char answerD[100];
    char actualAnswer;
};

struct Student
{
    string name;
    string examRefNum;
    string date;
    int count = 0;

};

struct Answer
{
    char answer;
};

int getMainChoice();

int getSubChoice();

void listQues(vector <Question> questions, int currentRecordNum);

void editQues(vector <Question>& questions, int num);

void addQues(vector <Question>& questions, int& currentRecordNum);

void deleteQuestion(vector <Question>& questions, int& currentRecordNum, int& index);

void saveQuestions(vector <Question> questions, int currentRecordNum);


Student startTest(vector<Question>& questions, int currentRecordNum);

void showResult(vector<Student> students, int countTest);

void processOption(vector <Question>& questions, int& currentRecordNum, int& index);

void readQuestion(vector <Question>& questions, int& currentRecordNumber);

//declare the size of questions array
const int QUESTION_SIZE = 100;
const int STUDENT_SIZE = 10;

int main()
{
    //variable declaration
    int mainChoice = 0, subChoice = 0, percentage = 0, currentRecordNum = 0, num = 0, index = 0, countTest = 0;

    //use vector to store questions and students
    vector <Question> questions;
    vector <Student> students;

    questions.resize(QUESTION_SIZE);//resize vector to 100
    students.resize(STUDENT_SIZE);//resize vector to 10

    readQuestion(questions, currentRecordNum);//read question from question.txt

    //use do while loop to get input from user
    do
    {
        //get the main choice from user
        mainChoice = getMainChoice();

        switch (mainChoice)
        {
            case 1:
                //process the option
                processOption(questions, currentRecordNum, index);

                break;


            case 2://start test
            {
                Student student;

                //create a file on desktop
                ofstream myFile("C:\\Users\\User\\Desktop\\student.txt");

                //store startTest into student

                students[countTest] = startTest(questions, currentRecordNum);

                countTest++;

                //write student detail to file
                for (int i = 0; i < countTest; i++)
                {
                    myFile << "Exam Reference Number:" << students[i].examRefNum << "\n" << "Name:" << students[i].name
                        << "\n" << "Date: " << students[i].date
                        << "\n" << "Total Correct:" << students[i].count << " / 10" << endl;
                    if (students[i].count >= 5)
                    {
                        myFile << "You Pass!" << endl;
                    }
                    else
                    {
                        myFile << "You Fail!" << endl;
                    }

                }


                //close file
                myFile.close();
                break;
            }
            case 3:
                //show historical result
                showResult(students, countTest);
                break;

            case 4:
                //exit the program
                break;


            default:
                cout << "Invalid Option!" << endl;
                break;
            }
    } while (mainChoice != 4);


    //save the question detail on desktop
    saveQuestions(questions, currentRecordNum); //save question back to question.txt
    return 0;

}


void processOption(vector <Question>& questions, int& currentRecordNum, int& index) {
    int subChoice = 0, num = 0;

    do
    {
        //get the sub choice from user
        subChoice = getSubChoice();

        //use another switch to process sub choice
        switch (subChoice)
        {
        case 1:
        {
            //use addQues function to add question into question array
            addQues(questions, currentRecordNum);
            //increase the current index number

            break;
        }

        case 2:
        {
            //prompt user to enter the number of question
            cout << "Enter the number of the question you want to edit:";
            cin >> num;
            editQues(questions, num);
            break;
        }
        case 3:
            //call delete function to delete question
            deleteQuestion(questions, currentRecordNum, index);
            break;

        case 4:
            //list all the question to user
            listQues(questions, currentRecordNum);
            break;

        case 5:
            //back to main menu
            break;

        default:
            cout << "Invalid Option!" << endl;
            break;
        }

    } while (subChoice != 5);//validate the sub choice
}

void showResult(vector<Student> students, int countTest) {

    string examRefNum;
    //display historical result
    cout << "Exam Reference Number should start with A follow by 5 integer values.\n" << endl;
    do
    {
        cout << "Enter your Exam Reference No:";
        cin >> examRefNum;
        cout << endl;

    } while (examRefNum[0] != 'A' || examRefNum.length() != 6);//validate exam reference num


    for (int i = 0; i <= countTest; i++)
    {
        //use loop to check the input of user , if exam reference number exists , show the results
        if (examRefNum == students[i].examRefNum)
        {
            cout << right << setw(30) << "Previous Test Result" << endl;
            cout << "-------------------------------------------" << endl;
            cout << "Exam Reference No :" << students[i].examRefNum << endl;
            cout << "Date :" << students[i].date << endl;
            cout << "Name :" << students[i].name << endl;
            cout << "Total Correct :" << students[i].count << " / 10" << endl;
            cout << endl;
        }
        else
        {
            cout << "Invalid exam reference number..." << endl;
            cout << endl;
            break;
        }
    }
}

Student startTest(vector<Question>& questions, int currentRecordNum) {
    srand(time(0));
    Student student;
    int randomNum[10];

    Answer answers[10];
    int percentage = 0, i = 0, j = 0, temp = 0;


    //use array to store random number
    for (i = 0; i < 10; i++)
    {
        do
        {
            randomNum[i] = rand() % currentRecordNum;
            for (j = 0; j < i; j++)
            {
                if (randomNum[i] == randomNum[j]) {//if current number is same as previous number, loop again
                    break;
                }
            }
        } while (j != i);
    }


    cin.ignore();
    //validate the user input
    cout << "Exam Reference Number should start with A follow by 5 integer values.\n" << endl;
    do
    {
        cout << "Enter your Exam Reference No:";
        cin >> student.examRefNum;
        cout << endl;

    } while (student.examRefNum[0] != 'A' || student.examRefNum.length() != 6);


    //prompt user to enter date
    cout << "Date:";
    cin.ignore();
    getline(cin, student.date);

    cout << endl;

    //prompt user to enter name
    cout << "Name:";
    getline(cin, student.name);

    cout << "Start Test...." << endl;
    cout << "--------------------------------------" << endl;



    for (int i = 0; i < 10; i++)
    {
        temp = randomNum[0 + i];
        //read the question from array
        cout << (i + 1) << "->" << questions[temp].questionText << endl;
        cout << "a." << left << setw(30) << questions[temp].answerA << "b." << questions[temp].answerB << endl;
        cout << "c." << left << setw(30) << questions[temp].answerC << "d." << questions[temp].answerD << endl;
        cout << endl;


        do
        {
            cout << "The answer must be in A/B/C/D\n" << endl;
            cout << "Enter your answer:";
            //store user answer
            cin >> answers[i].answer;
            cout << endl;
        } while ((answers[i].answer != 'A') && (answers[i].answer != 'B') && (answers[i].answer != 'C') && (answers[i].answer != 'D'));
        //validate the user answer , answer must be in A , B , C ,D





        cout << endl;
        //if the user answers the question correctly , inrease count
        if (char(toupper(answers[i].answer)) == char(toupper(questions[temp].actualAnswer))) {
            student.count++;
        }
    }


    cout << endl;
    //display student detail
    cout << "Date:" << student.date << "\n" << endl;
    cout << "Name:" << student.name << "\n" << endl;
    cout << "Question" << endl;



    //show the user's answer and correct answer
    for (int i = 0; i < 10;i++)
    {
        temp = randomNum[0 + i];
        if (char(toupper(answers[i].answer)) == char(toupper(questions[temp].actualAnswer)))
        {
            cout << (i + 1) << ")" << setw(5) << char(toupper(answers[i].answer)) << endl;
        }
        else
        {
            cout << (i + 1) << ")" << setw(5) << char(toupper(answers[i].answer)) << " (" << char(toupper(questions[temp].actualAnswer)) << ")" << endl;
        }
    }


    //display result
    cout << endl;
    cout << "Total correct:" << student.count << endl;



    //calculate the percentage
    percentage = student.count * 10;
    cout << "Percentage:" << percentage << "%" << endl;

    //if percentage >= 50 , user pass , else user fail
    if (percentage >= 50 && percentage <= 100)
    {
        cout << "You Pass" << endl;
    }
    else
    {
        cout << "You Fail" << endl;
    }

    cout << endl;

    return student;
}

void readQuestion(vector <Question>& questions, int& currentRecordNumber)
{


    ifstream MyFile;
    MyFile.open("C:\\Users\\User\\Desktop\\question.txt");


    string text;


    while (!MyFile.eof())
    {
        getline(MyFile, text);
        strcpy_s(questions[currentRecordNumber].questionText, text.c_str());

        getline(MyFile, text);
        strcpy_s(questions[currentRecordNumber].answerA, text.c_str());

        getline(MyFile, text);
        strcpy_s(questions[currentRecordNumber].answerB, text.c_str());

        getline(MyFile, text);
        strcpy_s(questions[currentRecordNumber].answerC, text.c_str());

        getline(MyFile, text);
        strcpy_s(questions[currentRecordNumber].answerD, text.c_str());

        getline(MyFile, text);
        questions[currentRecordNumber].actualAnswer = text[0];


        currentRecordNumber++;
    }

    currentRecordNumber--;


    MyFile.close();
}

void saveQuestions(vector <Question> questions, int currentRecordIndex)
{
    //write to text file
    ofstream MyFile("C:\\Users\\User\\Desktop\\question.txt");

    //store questions detail inside text file
    for (int i = 0; i < currentRecordIndex; i++)
    {
        MyFile << questions[i].questionText << endl;
        MyFile << questions[i].answerA << endl;
        MyFile << questions[i].answerB << endl;
        MyFile << questions[i].answerC << endl;
        MyFile << questions[i].answerD << endl;
        MyFile << questions[i].actualAnswer << endl;
    }

    MyFile.close();


}

void deleteQuestion(vector <Question>& questions, int& currentRecordNum, int& index) {

    cin.ignore();
    cout << "Enter the number of question you want to delete:";
    cin >> index;


    cout << endl;

    for (int i = index - 1; i < (currentRecordNum - 1); i++)
    {
        questions[i] = questions[i + 1];//use the next question to reset the current question
    }


    cout << "Question deleted successfully...\n" << endl;

    //decrease the size of array
    currentRecordNum--;






}

int getMainChoice() {
    int choice = 0;

    //display the main menu
    cout << "\tIT Test System" << endl;
    cout << "\t  Main Menu" << endl;
    cout << endl;
    cout << "1.	Question Banks" << endl;
    cout << "2.	Start Test" << endl;
    cout << "3.	View Historical Results" << endl;
    cout << "4.	Exit" << endl;
    cout << endl;

    //get the input from user
    cout << "Enter Your Choice:";
    cin >> choice;
    cout << endl;
    return choice;
}

int getSubChoice() {
    int choice = 0;

    //display the main menu
    cout << "\tIT Test System" << endl;
    cout << "\tQuestion Banks" << endl;
    cout << endl;
    cout << "1.	Add Question" << endl;
    cout << "2.	Edit Question" << endl;
    cout << "3.	Delete Question" << endl;
    cout << "4.	View All Questions" << endl;
    cout << "5.	Return to the Main Menu" << endl;
    cout << endl;

    //get the input from user
    cout << "Enter Your Choice:";
    cin >> choice;
    cout << endl;
    return choice;

}

void editQues(vector <Question>& questions, int num) {
    Question q;
    //prompt user to enter the question
    cout << "Enter the new question:";
    cin.ignore();
    cin.getline(questions[num - 1].questionText, 80);



    cout << "Enter your Answer A:";
    cin.getline(questions[num - 1].answerA, 100);


    cout << "Enter your Answer B:";
    cin.getline(questions[num - 1].answerB, 100);


    cout << "Enter your Answer C:";
    cin.getline(questions[num - 1].answerC, 100);


    cout << "Enter your Answer D:";
    cin.getline(questions[num - 1].answerD, 100);

    cout << "Enter the actual answer:";
    cin >> questions[num - 1].actualAnswer;

    cout << endl;
    cout << "Successfully editing the current question!\n" << endl;



}

void listQues(vector <Question> questions, int currentRecordNum) {


    //display all question from array
    for (int i = 0; i < currentRecordNum; i++)
    {
        cout << (i + 1) << " -> " << questions[i].questionText << endl;
    }

    cout << endl;
}

void addQues(vector<Question>& questions, int& currentRecordNum) {



    //prompt user to enter questions detail
    cout << "Enter your question:";
    cin.ignore();
    cin.getline(questions[currentRecordNum].questionText, 100);

    cout << "Enter your Answer A:";
    cin.getline(questions[currentRecordNum].answerA, 100);

    cout << "Enter your Answer B:";
    cin.getline(questions[currentRecordNum].answerB, 100);

    cout << "Enter your Answer C:";
    cin.getline(questions[currentRecordNum].answerC, 100);

    cout << "Enter your Answer D:";
    cin.getline(questions[currentRecordNum].answerD, 100);

    cout << "Enter the actual answer:";
    cin >> questions[currentRecordNum].actualAnswer;


    currentRecordNum++;

    cout << endl;
    cout << "Successfully adding the question!\n" << endl;



}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
