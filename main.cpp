#include <iostream>
#include <string>
using namespace std;

class Question {
private:
    string question;
    string option1, option2, option3, option4;
    int correctOption;

public:
    void setData(string q, string o1, string o2, string o3,
                 string o4, int correct) {
        question = q;
        option1 = o1;
        option2 = o2;
        option3 = o3;
        option4 = o4;
        correctOption = correct;
    }

    void askQuestion(int &score) {
        int ans;

        cout << "\n" << question << endl;
        cout << "1. " << option1 << endl;
        cout << "2. " << option2 << endl;
        cout << "3. " << option3 << endl;
        cout << "4. " << option4 << endl;

        cout << "Enter your answer (1-4): ";
        cin >> ans;

        if (ans == correctOption) {
            cout << "Correct!\n";
            score++;
        } else {
            cout << "Wrong! Correct answer was option "
                 << correctOption << ".\n";
        }
    }

    void display() {
        cout << "\n" << question << endl;
        cout << "1. " << option1 << endl;
        cout << "2. " << option2 << endl;
        cout << "3. " << option3 << endl;
        cout << "4. " << option4 << endl;
    }

    void editQuestion() {
        cin.ignore();

        cout << "\nEnter new question: ";
        getline(cin, question);

        cout << "Option 1: ";
        getline(cin, option1);

        cout << "Option 2: ";
        getline(cin, option2);

        cout << "Option 3: ";
        getline(cin, option3);

        cout << "Option 4: ";
        getline(cin, option4);

        cout << "Enter correct option number (1-4): ";
        cin >> correctOption;

        cout << "Question updated successfully!\n";
    }
};


class Student {
private:
    string name;

    int mathsScore, scienceScore;
    int socialScore, englishScore;

    bool attemptedMaths, attemptedScience;
    bool attemptedSocial, attemptedEnglish;

public:
    Student(string n = "Unknown") {
        name = n;

        mathsScore = scienceScore =
        socialScore = englishScore = 0;

        attemptedMaths =
        attemptedScience =
        attemptedSocial =
        attemptedEnglish = false;
    }

    void attemptQuiz(Question q[], int total, string subject) {
        int score = 0;

        for (int i = 0; i < total; i++) {
            q[i].askQuestion(score);
        }

        cout << "\n" << name
             << ", your score in " << subject
             << ": " << score
             << " out of " << total << endl;

        if (subject == "Maths") {
            mathsScore = score;
            attemptedMaths = true;
        }
        else if (subject == "Science") {
            scienceScore = score;
            attemptedScience = true;
        }
        else if (subject == "Social") {
            socialScore = score;
            attemptedSocial = true;
        }
        else if (subject == "English") {
            englishScore = score;
            attemptedEnglish = true;
        }
    }

    void showAllScores() {
        cout << "\n===== " << name
             << "'s Subject Scores =====\n";

        cout << "Maths: "
             << (attemptedMaths ?
                 to_string(mathsScore) :
                 "Not Attempted") << endl;

        cout << "Science: "
             << (attemptedScience ?
                 to_string(scienceScore) :
                 "Not Attempted") << endl;

        cout << "Social: "
             << (attemptedSocial ?
                 to_string(socialScore) :
                 "Not Attempted") << endl;

        cout << "English: "
             << (attemptedEnglish ?
                 to_string(englishScore) :
                 "Not Attempted") << endl;
    }
};


int main() {

    Question maths[10];
    int mathsCount = 2;

    maths[0].setData(
        "What is 10 + 5?",
        "12", "15", "20", "25", 2
    );

    maths[1].setData(
        "What is 9 * 3?",
        "18", "21", "27", "30", 3
    );


    Question science[10];
    int scienceCount = 2;

    science[0].setData(
        "Which gas do humans breathe in?",
        "Oxygen", "Carbon Dioxide",
        "Nitrogen", "Hydrogen", 1
    );

    science[1].setData(
        "Water freezes at what temperature?",
        "0C", "10C", "50C", "100C", 1
    );


    Question social[10];
    int socialCount = 2;

    social[0].setData(
        "Who is the Father of the Nation (India)?",
        "Nehru", "Gandhi", "Patel", "Ambedkar", 2
    );

    social[1].setData(
        "Which is the capital of India?",
        "Mumbai", "Delhi", "Kolkata", "Chennai", 2
    );


    Question english[10];
    int englishCount = 2;

    english[0].setData(
        "Choose the correct spelling:",
        "Enviroment", "Environment",
        "Environmment", "Enviourment", 2
    );

    english[1].setData(
        "Opposite of 'Happy'?",
        "Joyful", "Excited", "Sad", "Calm", 3
    );


    cout << "===== ONLINE EXAMINATION SYSTEM =====\n";

    int roleChoice;
    bool exitSystem = false;

    do {

        cout << "\nSelect Role:\n";
        cout << "1. Teacher\n";
        cout << "2. Student\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> roleChoice;


        // TEACHER
        if (roleChoice == 1) {

            string pass;

            cout << "Enter Teacher Password: ";
            cin >> pass;

            if (pass != "teacher123") {
                cout << "Wrong password! Access denied.\n";
                continue;
            }

            int tChoice;

            do {

                cout << "\n===== TEACHER MENU =====\n";
                cout << "1. Add New Question\n";
                cout << "2. Edit Existing Question\n";
                cout << "3. Back to Main Menu\n";
                cout << "Enter your choice: ";
                cin >> tChoice;


                // ADD QUESTION
                if (tChoice == 1) {

                    int sub;

                    cout << "\nSelect Subject to Add Question:\n";
                    cout << "1. Maths\n";
                    cout << "2. Science\n";
                    cout << "3. Social\n";
                    cout << "4. English\n";
                    cout << "Enter: ";
                    cin >> sub;

                    cin.ignore();

                    string q, o1, o2, o3, o4;
                    int ans;

                    cout << "\nEnter Question: ";
                    getline(cin, q);

                    cout << "Option 1: ";
                    getline(cin, o1);

                    cout << "Option 2: ";
                    getline(cin, o2);

                    cout << "Option 3: ";
                    getline(cin, o3);

                    cout << "Option 4: ";
                    getline(cin, o4);

                    cout << "Enter correct option number (1-4): ";
                    cin >> ans;


                    switch (sub) {

                        case 1:
                            maths[mathsCount++]
                                .setData(q, o1, o2, o3, o4, ans);
                            break;

                        case 2:
                            science[scienceCount++]
                                .setData(q, o1, o2, o3, o4, ans);
                            break;

                        case 3:
                            social[socialCount++]
                                .setData(q, o1, o2, o3, o4, ans);
                            break;

                        case 4:
                            english[englishCount++]
                                .setData(q, o1, o2, o3, o4, ans);
                            break;

                        default:
                            cout << "Invalid subject!\n";
                    }

                    cout << "Question added successfully!\n";
                }


                // EDIT QUESTION
                else if (tChoice == 2) {

                    int sub;

                    cout << "\nSelect Subject to Edit:\n";
                    cout << "1. Maths\n";
                    cout << "2. Science\n";
                    cout << "3. Social\n";
                    cout << "4. English\n";
                    cout << "Enter: ";
                    cin >> sub;

                    Question *selected = nullptr;
                    int total = 0;


                    switch (sub) {

                        case 1:
                            selected = maths;
                            total = mathsCount;
                            break;

                        case 2:
                            selected = science;
                            total = scienceCount;
                            break;

                        case 3:
                            selected = social;
                            total = socialCount;
                            break;

                        case 4:
                            selected = english;
                            total = englishCount;
                            break;

                        default:
                            cout << "Invalid subject!\n";
                            continue;
                    }


                    for (int i = 0; i < total; i++) {

                        cout << "\n" << i + 1 << ". ";
                        selected[i].display();
                    }


                    int qNo;

                    cout << "\nEnter question number to edit: ";
                    cin >> qNo;


                    if (qNo >= 1 && qNo <= total) {

                        selected[qNo - 1].editQuestion();

                    } else {

                        cout << "Invalid question number!\n";
                    }
                }

            } while (tChoice != 3);
        }


        // STUDENT
        else if (roleChoice == 2) {

            string spass;

            cout << "Enter Student Password: ";
            cin >> spass;

            if (spass != "student123") {
                cout << "Wrong Password! Access denied.\n";
                continue;
            }

            cin.ignore();

            string studentName;

            cout << "Enter your name: ";
            getline(cin, studentName);

            Student s(studentName);

            int choice;


            do {

                cout << "\n===== STUDENT MENU =====\n";
                cout << "1. Take Quiz\n";
                cout << "2. Show All Scores\n";
                cout << "3. Back to Main Menu\n";
                cout << "Enter your choice: ";
                cin >> choice;


                // TAKE QUIZ
                if (choice == 1) {

                    int subjectChoice;

                    cout << "\nChoose Subject:\n";
                    cout << "1. Maths\n";
                    cout << "2. Science\n";
                    cout << "3. Social\n";
                    cout << "4. English\n";
                    cout << "Enter your choice: ";
                    cin >> subjectChoice;


                    switch (subjectChoice) {

                        case 1:
                            s.attemptQuiz(
                                maths,
                                mathsCount,
                                "Maths"
                            );
                            break;

                        case 2:
                            s.attemptQuiz(
                                science,
                                scienceCount,
                                "Science"
                            );
                            break;

                        case 3:
                            s.attemptQuiz(
                                social,
                                socialCount,
                                "Social"
                            );
                            break;

                        case 4:
                            s.attemptQuiz(
                                english,
                                englishCount,
                                "English"
                            );
                            break;

                        default:
                            cout << "Invalid choice!\n";
                    }
                }


                // SHOW SCORES
                else if (choice == 2) {

                    s.showAllScores();
                }

            } while (choice != 3);

            s.showAllScores();
        }


        // EXIT
        else if (roleChoice == 3) {

            cout << "\nExiting system...\n";
            exitSystem = true;
        }


        else {

            cout << "Invalid choice! Try again.\n";
        }

    } while (!exitSystem);


    cout << "\n===== THANK YOU =====\n";

    return 0;
}
