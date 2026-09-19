#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

// ============================================================
// QUESTION CLASS
// ============================================================

class Question {
private:
    string question;
    string option1;
    string option2;
    string option3;
    string option4;
    int correctOption;

public:

    // Constructor
    Question() {
        correctOption = 1;
    }

    // Set question data
    void setData(string q, string o1, string o2,
                 string o3, string o4, int correct) {

        question = q;
        option1 = o1;
        option2 = o2;
        option3 = o3;
        option4 = o4;
        correctOption = correct;
    }

    // Display question
    void display() const {

        cout << "\n" << question << endl;
        cout << "1. " << option1 << endl;
        cout << "2. " << option2 << endl;
        cout << "3. " << option3 << endl;
        cout << "4. " << option4 << endl;
    }

    // Ask question and return whether answer is correct
    bool askQuestion() const {

        int answer;

        display();

        cout << "Enter your answer (1-4): ";
        cin >> answer;

        if (answer == correctOption) {
            cout << "Correct!\n";
            return true;
        }
        else {
            cout << "Wrong!\n";
            cout << "Correct answer was option "
                 << correctOption << ".\n";

            return false;
        }
    }

    // Edit question
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

        do {
            cout << "Enter correct option number (1-4): ";
            cin >> correctOption;

            if (correctOption < 1 || correctOption > 4) {
                cout << "Invalid option. Try again.\n";
            }

        } while (correctOption < 1 || correctOption > 4);

        cout << "Question updated successfully!\n";
    }

    // Save question to file
    void saveToFile(ofstream &file) const {

        file << question << '\n';
        file << option1 << '\n';
        file << option2 << '\n';
        file << option3 << '\n';
        file << option4 << '\n';
        file << correctOption << '\n';
    }

    // Load question from file
    bool loadFromFile(ifstream &file) {

        string correct;

        if (!getline(file, question)) {
            return false;
        }

        if (!getline(file, option1)) return false;
        if (!getline(file, option2)) return false;
        if (!getline(file, option3)) return false;
        if (!getline(file, option4)) return false;
        if (!getline(file, correct)) return false;

        try {
            correctOption = stoi(correct);
        }
        catch (...) {
            return false;
        }

        return true;
    }
};


// ============================================================
// QUESTION BANK CLASS
// ============================================================

class QuestionBank {
private:

    vector<Question> questions;

public:

    // Add question
    void addQuestion(const Question &q) {
        questions.push_back(q);
    }

    // Number of questions
    int size() const {
        return questions.size();
    }

    // Access question
    Question &operator[](int index) {
        return questions[index];
    }

    // Display all questions
    void displayQuestions() const {

        if (questions.empty()) {
            cout << "\nNo questions available.\n";
            return;
        }

        for (int i = 0; i < questions.size(); i++) {

            cout << "\nQuestion " << i + 1 << ":";
            questions[i].display();
        }
    }

    // Save all questions
    void saveToFile(const string &filename) const {

        ofstream file(filename);

        if (!file) {
            cout << "Error opening file: "
                 << filename << endl;
            return;
        }

        for (const Question &q : questions) {
            q.saveToFile(file);
        }

        file.close();
    }

    // Load all questions
    void loadFromFile(const string &filename) {

        questions.clear();

        ifstream file(filename);

        // If file doesn't exist, simply start with empty bank
        if (!file) {
            return;
        }

        while (true) {

            Question q;

            if (!q.loadFromFile(file)) {
                break;
            }

            questions.push_back(q);
        }

        file.close();
    }

    // Get randomized questions
    vector<Question> getRandomQuestions(int count) const {

        vector<Question> selected = questions;

        // Random number generator
        random_device rd;
        mt19937 generator(rd());

        shuffle(
            selected.begin(),
            selected.end(),
            generator
        );

        if (count < selected.size()) {
            selected.resize(count);
        }

        return selected;
    }
};


// ============================================================
// STUDENT CLASS
// ============================================================

class Student {
private:

    string name;

    int mathsScore;
    int scienceScore;
    int socialScore;
    int englishScore;

    bool attemptedMaths;
    bool attemptedScience;
    bool attemptedSocial;
    bool attemptedEnglish;

public:

    Student(string n = "Unknown") {

        name = n;

        mathsScore = 0;
        scienceScore = 0;
        socialScore = 0;
        englishScore = 0;

        attemptedMaths = false;
        attemptedScience = false;
        attemptedSocial = false;
        attemptedEnglish = false;
    }

    // Take quiz
    int attemptQuiz(
        const QuestionBank &bank,
        string subject
    ) {

        if (bank.size() == 0) {

            cout << "\nNo questions available for "
                 << subject << ".\n";

            return 0;
        }

        // Number of questions
        int numberOfQuestions;

        cout << "\nAvailable questions: "
             << bank.size() << endl;

        cout << "How many questions do you want to attempt? ";

        cin >> numberOfQuestions;

        if (numberOfQuestions < 1) {
            cout << "Invalid number of questions.\n";
            return 0;
        }

        if (numberOfQuestions > bank.size()) {
            numberOfQuestions = bank.size();

            cout << "Only " << bank.size()
                 << " questions are available.\n";
        }

        // Random question selection
        vector<Question> quizQuestions =
            bank.getRandomQuestions(numberOfQuestions);

        int score = 0;

        cout << "\n====================================\n";
        cout << "          " << subject << " EXAM\n";
        cout << "====================================\n";

        for (int i = 0; i < quizQuestions.size(); i++) {

            cout << "\nQuestion "
                 << i + 1
                 << " of "
                 << quizQuestions.size()
                 << endl;

            if (quizQuestions[i].askQuestion()) {
                score++;
            }
        }

        cout << "\n====================================\n";
        cout << "              RESULT\n";
        cout << "====================================\n";

        cout << "Student : " << name << endl;
        cout << "Subject : " << subject << endl;
        cout << "Score   : " << score
             << " / "
             << quizQuestions.size()
             << endl;

        double percentage =
            (double)score /
            quizQuestions.size() * 100;

        cout << "Percentage : "
             << percentage
             << "%\n";

        // Store subject score
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

        // Save result to file
        saveResult(
            subject,
            score,
            quizQuestions.size(),
            percentage
        );

        return score;
    }

    // Show all scores
    void showAllScores() const {

        cout << "\n====================================\n";
        cout << "       " << name
             << "'s SUBJECT SCORES\n";
        cout << "====================================\n";

        cout << "Maths: ";

        if (attemptedMaths)
            cout << mathsScore;
        else
            cout << "Not Attempted";

        cout << endl;


        cout << "Science: ";

        if (attemptedScience)
            cout << scienceScore;
        else
            cout << "Not Attempted";

        cout << endl;


        cout << "Social: ";

        if (attemptedSocial)
            cout << socialScore;
        else
            cout << "Not Attempted";

        cout << endl;


        cout << "English: ";

        if (attemptedEnglish)
            cout << englishScore;
        else
            cout << "Not Attempted";

        cout << endl;
    }

    // Save result
    void saveResult(
        string subject,
        int score,
        int total,
        double percentage
    ) const {

        ofstream file("results.txt", ios::app);

        if (!file) {

            cout << "Unable to save result.\n";
            return;
        }

        time_t now = time(0);

        file << "====================================\n";
        file << "Student: " << name << '\n';
        file << "Subject: " << subject << '\n';
        file << "Score: "
             << score
             << "/"
             << total
             << '\n';

        file << "Percentage: "
             << percentage
             << "%\n";

        file << "Date: "
             << ctime(&now);

        file << "====================================\n\n";

        file.close();
    }
};


// ============================================================
// ADMIN / TEACHER CLASS
// ============================================================

class Admin {
private:

    string password;

public:

    Admin() {
        password = "teacher123";
    }

    // Login
    bool login() {

        string enteredPassword;

        cout << "\nEnter Teacher Password: ";
        cin >> enteredPassword;

        if (enteredPassword == password) {

            cout << "Teacher login successful!\n";
            return true;
        }

        cout << "Wrong password! Access denied.\n";

        return false;
    }

    // Add question
    void addQuestion(
        QuestionBank &maths,
        QuestionBank &science,
        QuestionBank &social,
        QuestionBank &english
    ) {

        int subject;

        cout << "\n====================================\n";
        cout << "       SELECT SUBJECT\n";
        cout << "====================================\n";

        cout << "1. Maths\n";
        cout << "2. Science\n";
        cout << "3. Social\n";
        cout << "4. English\n";

        cout << "Enter choice: ";
        cin >> subject;

        cin.ignore();

        string q;
        string o1, o2, o3, o4;

        int correct;

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

        do {

            cout << "Enter correct option (1-4): ";
            cin >> correct;

            if (correct < 1 || correct > 4) {
                cout << "Invalid option. Try again.\n";
            }

        } while (correct < 1 || correct > 4);


        Question newQuestion;

        newQuestion.setData(
            q,
            o1,
            o2,
            o3,
            o4,
            correct
        );


        switch (subject) {

            case 1:
                maths.addQuestion(newQuestion);
                maths.saveToFile("maths.txt");
                break;

            case 2:
                science.addQuestion(newQuestion);
                science.saveToFile("science.txt");
                break;

            case 3:
                social.addQuestion(newQuestion);
                social.saveToFile("social.txt");
                break;

            case 4:
                english.addQuestion(newQuestion);
                english.saveToFile("english.txt");
                break;

            default:
                cout << "Invalid subject!\n";
                return;
        }

        cout << "\nQuestion added successfully!\n";
        cout << "Question saved permanently.\n";
    }


    // Edit question
    void editQuestion(
        QuestionBank &maths,
        QuestionBank &science,
        QuestionBank &social,
        QuestionBank &english
    ) {

        int subject;

        cout << "\n====================================\n";
        cout << "       SELECT SUBJECT\n";
        cout << "====================================\n";

        cout << "1. Maths\n";
        cout << "2. Science\n";
        cout << "3. Social\n";
        cout << "4. English\n";

        cout << "Enter choice: ";
        cin >> subject;


        QuestionBank *selectedBank = nullptr;
        string filename;


        switch (subject) {

            case 1:
                selectedBank = &maths;
                filename = "maths.txt";
                break;

            case 2:
                selectedBank = &science;
                filename = "science.txt";
                break;

            case 3:
                selectedBank = &social;
                filename = "social.txt";
                break;

            case 4:
                selectedBank = &english;
                filename = "english.txt";
                break;

            default:
                cout << "Invalid subject!\n";
                return;
        }


        if (selectedBank->size() == 0) {

            cout << "No questions available.\n";
            return;
        }


        selectedBank->displayQuestions();


        int questionNumber;

        cout << "\nEnter question number to edit: ";
        cin >> questionNumber;


        if (
            questionNumber < 1 ||
            questionNumber > selectedBank->size()
        ) {

            cout << "Invalid question number!\n";
            return;
        }


        (*selectedBank)[questionNumber - 1]
            .editQuestion();


        selectedBank->saveToFile(filename);

        cout << "Changes saved successfully!\n";
    }


    // View questions
    void viewQuestions(
        const QuestionBank &maths,
        const QuestionBank &science,
        const QuestionBank &social,
        const QuestionBank &english
    ) {

        int subject;

        cout << "\nSelect Subject:\n";

        cout << "1. Maths\n";
        cout << "2. Science\n";
        cout << "3. Social\n";
        cout << "4. English\n";

        cout << "Enter choice: ";
        cin >> subject;


        switch (subject) {

            case 1:
                maths.displayQuestions();
                break;

            case 2:
                science.displayQuestions();
                break;

            case 3:
                social.displayQuestions();
                break;

            case 4:
                english.displayQuestions();
                break;

            default:
                cout << "Invalid subject!\n";
        }
    }
};


// ============================================================
// LOAD DEFAULT QUESTIONS
// ============================================================

void createDefaultQuestions(
    QuestionBank &maths,
    QuestionBank &science,
    QuestionBank &social,
    QuestionBank &english
) {

    // ---------------- MATHS ----------------

    if (maths.size() == 0) {

        Question q1;

        q1.setData(
            "What is 10 + 5?",
            "12",
            "15",
            "20",
            "25",
            2
        );

        maths.addQuestion(q1);


        Question q2;

        q2.setData(
            "What is 9 * 3?",
            "18",
            "21",
            "27",
            "30",
            3
        );

        maths.addQuestion(q2);


        maths.saveToFile("maths.txt");
    }


    // ---------------- SCIENCE ----------------

    if (science.size() == 0) {

        Question q1;

        q1.setData(
            "Which gas do humans breathe in?",
            "Oxygen",
            "Carbon Dioxide",
            "Nitrogen",
            "Hydrogen",
            1
        );

        science.addQuestion(q1);


        Question q2;

        q2.setData(
            "Water freezes at what temperature?",
            "0C",
            "10C",
            "50C",
            "100C",
            1
        );

        science.addQuestion(q2);


        science.saveToFile("science.txt");
    }


    // ---------------- SOCIAL ----------------

    if (social.size() == 0) {

        Question q1;

        q1.setData(
            "Who is the Father of the Nation (India)?",
            "Nehru",
            "Gandhi",
            "Patel",
            "Ambedkar",
            2
        );

        social.addQuestion(q1);


        Question q2;

        q2.setData(
            "Which is the capital of India?",
            "Mumbai",
            "Delhi",
            "Kolkata",
            "Chennai",
            2
        );

        social.addQuestion(q2);


        social.saveToFile("social.txt");
    }


    // ---------------- ENGLISH ----------------

    if (english.size() == 0) {

        Question q1;

        q1.setData(
            "Choose the correct spelling:",
            "Enviroment",
            "Environment",
            "Environmment",
            "Enviourment",
            2
        );

        english.addQuestion(q1);


        Question q2;

        q2.setData(
            "Opposite of 'Happy'?",
            "Joyful",
            "Excited",
            "Sad",
            "Calm",
            3
        );

        english.addQuestion(q2);


        english.saveToFile("english.txt");
    }
}


// ============================================================
// MAIN FUNCTION
// ============================================================

int main() {

    // Create question banks
    QuestionBank maths;
    QuestionBank science;
    QuestionBank social;
    QuestionBank english;


    // Load questions from files
    maths.loadFromFile("maths.txt");
    science.loadFromFile("science.txt");
    social.loadFromFile("social.txt");
    english.loadFromFile("english.txt");


    // If files are empty, create default questions
    createDefaultQuestions(
        maths,
        science,
        social,
        english
    );


    // Create admin
    Admin admin;


    cout << "\n============================================\n";
    cout << "       ONLINE EXAMINATION SYSTEM\n";
    cout << "============================================\n";


    int roleChoice;

    bool exitSystem = false;


    do {

        cout << "\n====================================\n";
        cout << "             MAIN MENU\n";
        cout << "====================================\n";

        cout << "1. Teacher\n";
        cout << "2. Student\n";
        cout << "3. Exit\n";

        cout << "Enter your choice: ";
        cin >> roleChoice;


        // ====================================================
        // TEACHER
        // ====================================================

        if (roleChoice == 1) {

            if (!admin.login()) {
                continue;
            }


            int teacherChoice;


            do {

                cout << "\n====================================\n";
                cout << "          TEACHER MENU\n";
                cout << "====================================\n";

                cout << "1. Add New Question\n";
                cout << "2. Edit Existing Question\n";
                cout << "3. View Questions\n";
                cout << "4. Back to Main Menu\n";

                cout << "Enter choice: ";
                cin >> teacherChoice;


                if (teacherChoice == 1) {

                    admin.addQuestion(
                        maths,
                        science,
                        social,
                        english
                    );
                }


                else if (teacherChoice == 2) {

                    admin.editQuestion(
                        maths,
                        science,
                        social,
                        english
                    );
                }


                else if (teacherChoice == 3) {

                    admin.viewQuestions(
                        maths,
                        science,
                        social,
                        english
                    );
                }


                else if (teacherChoice == 4) {

                    cout << "Returning to main menu...\n";
                }


                else {

                    cout << "Invalid choice!\n";
                }


            } while (teacherChoice != 4);
        }


        // ====================================================
        // STUDENT
        // ====================================================

        else if (roleChoice == 2) {

            string studentPassword;

            cout << "\nEnter Student Password: ";
            cin >> studentPassword;


            if (studentPassword != "student123") {

                cout << "Wrong password! Access denied.\n";
                continue;
            }


            cin.ignore();


            string studentName;

            cout << "Enter your name: ";
            getline(cin, studentName);


            Student student(studentName);


            int studentChoice;


            do {

                cout << "\n====================================\n";
                cout << "          STUDENT MENU\n";
                cout << "====================================\n";

                cout << "1. Take Quiz\n";
                cout << "2. Show All Scores\n";
                cout << "3. Back to Main Menu\n";

                cout << "Enter choice: ";
                cin >> studentChoice;


                if (studentChoice == 1) {

                    int subjectChoice;


                    cout << "\n====================================\n";
                    cout << "          SELECT SUBJECT\n";
                    cout << "====================================\n";

                    cout << "1. Maths\n";
                    cout << "2. Science\n";
                    cout << "3. Social\n";
                    cout << "4. English\n";

                    cout << "Enter choice: ";
                    cin >> subjectChoice;


                    switch (subjectChoice) {

                        case 1:
                            student.attemptQuiz(
                                maths,
                                "Maths"
                            );
                            break;

                        case 2:
                            student.attemptQuiz(
                                science,
                                "Science"
                            );
                            break;

                        case 3:
                            student.attemptQuiz(
                                social,
                                "Social"
                            );
                            break;

                        case 4:
                            student.attemptQuiz(
                                english,
                                "English"
                            );
                            break;

                        default:
                            cout << "Invalid subject!\n";
                    }
                }


                else if (studentChoice == 2) {

                    student.showAllScores();
                }


                else if (studentChoice == 3) {

                    cout << "Returning to main menu...\n";
                }


                else {

                    cout << "Invalid choice!\n";
                }


            } while (studentChoice != 3);


            student.showAllScores();
        }


        // ====================================================
        // EXIT
        // ====================================================

        else if (roleChoice == 3) {

            cout << "\nExiting system...\n";

            exitSystem = true;
        }


        else {

            cout << "Invalid choice! Try again.\n";
        }


    } while (!exitSystem);


    cout << "\n====================================\n";
    cout << "          THANK YOU!\n";
    cout << "====================================\n";


    return 0;
}
