#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

enum enQuestionLevel { Easy = 1, Med, Hard, MixQL };

enum enOperationType { Add = 1, Sub, Mul, Div, MixOT };

struct stReadQuestion
{
    int firstNumber;
    int secondNumber;
    float userAnswer;
    float correctAnswer;
    enOperationType operationType;
    bool isCorrectAnswer = false;
};

struct stFinalResult
{
    short numberOfQuestion = 0;
    short numberOfRightQuestion = 0;
    short numberOfWrongQuestion = 0;
    enQuestionLevel questionLevel;
    enOperationType operationType;
    bool isPass = false;
};

int readPositiveNumber(int from, int to)
{
    int number;
    do
    {
        cin >> number;
    } while (number<from || number>to);
    return number;
}

float readAnswer()
{
    float number;
    cin >> number;
    return number;
}

int choiceRandomNumber(int from, int to)
{
    return rand() % (to - from + 1) + from;
}

int readManyOfQuestion()
{
    cout << "How many question do you want to answer ? ";
    return readPositiveNumber(1, 50);
}

enQuestionLevel readQuestionLevel()
{
    cout << "Enter Question Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
    return (enQuestionLevel)readPositiveNumber(1, 4);
}

enOperationType readOperationType()
{
    cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
    return (enOperationType)readPositiveNumber(1, 5);
}

char toChar(enOperationType operationType)
{
    char arr[4] = { '+','-','*','/' };
    return arr[operationType - 1];
}

string operationTypeToString(enOperationType operationType)
{
    string arr[5] = { "ADD","SUB","MUL","DIV","Mix" };
    return arr[operationType - 1];
}

string questionLevelToString(enQuestionLevel questionLevel)
{
    string arr[4] = { "Easy","Med","High","Mix" };
    return arr[questionLevel - 1];
}

int questionLevel(enQuestionLevel questionLevel)
{
    switch (questionLevel)
    {
    case enQuestionLevel::Easy: return choiceRandomNumber(1, 10);
    case enQuestionLevel::Med: return choiceRandomNumber(20, 50);
    case enQuestionLevel::Hard: return choiceRandomNumber(50, 100);
    case enQuestionLevel::MixQL: return choiceRandomNumber(1, 100);
    default: return 0;
    }
}

float correctAnswer(int firstNumber, enOperationType operationType, int secondNumber)
{
    switch (operationType)
    {
    case enOperationType::Add: return (float)firstNumber + secondNumber;
    case enOperationType::Sub: return (float)firstNumber - secondNumber;
    case enOperationType::Mul: return (float)firstNumber * secondNumber;
    case enOperationType::Div: return ((float)firstNumber / secondNumber);
    default: return 0;
    }
}

stFinalResult showFinalResult(stFinalResult& finalResult, stReadQuestion readQuestion)
{
    if (readQuestion.isCorrectAnswer)
    {
        cout << "Right Answer \n";
        finalResult.numberOfRightQuestion++;
    }
    else
    {
        cout << "Wrong Answer \n";
        cout << "The Right Answer is : " << readQuestion.correctAnswer << endl;
        finalResult.numberOfWrongQuestion++;
    }
    return finalResult;
}

stFinalResult firstQusetions(stFinalResult& finalResult)
{
    finalResult.numberOfQuestion = readManyOfQuestion();
    finalResult.questionLevel = readQuestionLevel();
    finalResult.operationType = readOperationType();

    return finalResult;
}

stReadQuestion getQuestion(stReadQuestion& readQuestion, stFinalResult& finalResult)
{
    readQuestion.firstNumber = questionLevel(finalResult.questionLevel);
    readQuestion.secondNumber = questionLevel(finalResult.questionLevel);

    readQuestion.operationType = finalResult.operationType;
    if (finalResult.operationType == enOperationType::MixOT)
        readQuestion.operationType = (enOperationType)choiceRandomNumber(1, 4);

    readQuestion.correctAnswer = correctAnswer(readQuestion.firstNumber, readQuestion.operationType, readQuestion.secondNumber);
    return readQuestion;
}

stFinalResult printQuestion(stReadQuestion& readQuestion, stFinalResult& finalResult, int i)
{
    getQuestion(readQuestion, finalResult);
    cout << "Question [" << i << "/" << finalResult.numberOfQuestion << "]\n\n";
    cout << readQuestion.firstNumber << "\n     " << toChar(readQuestion.operationType) << "\n";
    cout << readQuestion.secondNumber << "\n__________\n";

    readQuestion.userAnswer = readAnswer();
    readQuestion.isCorrectAnswer = readQuestion.correctAnswer == readQuestion.userAnswer;
    showFinalResult(finalResult, readQuestion);
    cout << "\n\n";

    return finalResult;
}

stFinalResult questions()
{
    stFinalResult finalResult;
    stReadQuestion readQuestion;
    firstQusetions(finalResult);
    for (int i = 1; i <= finalResult.numberOfQuestion; i++)
    {
        printQuestion(readQuestion, finalResult, i);
    }
    finalResult.isPass = finalResult.numberOfRightQuestion >= finalResult.numberOfWrongQuestion;

    return finalResult;
}

void printResult(stFinalResult finalResult)
{
    cout << "__________________________\n";
    if (finalResult.isPass)
    {
        system("color 2F");
        cout << "Final Result is PASS\n";
    }
    else
    {
        system("color 4F");
        cout << "Final Result is FAIL\n";
    }

    cout << "___________________________\n";

    cout << "Number of Questions    : " << finalResult.numberOfQuestion << endl;
    cout << "Questions Level        : " << questionLevelToString(finalResult.questionLevel) << endl;
    cout << "Operation Type         : " << operationTypeToString(finalResult.operationType) << endl;
    cout << "Number of Right Answer : " << finalResult.numberOfRightQuestion << endl;
    cout << "Number of Wrong Answer : " << finalResult.numberOfWrongQuestion << endl;
}

void clearScreen()
{
    system("cls");
    system("color 0F");
}

void startQuestions()
{
    stFinalResult finalResult;
    char ch;
    do {
        clearScreen();
        finalResult = questions();
        printResult(finalResult);
        cout << "\nDo you want to play again? (y)yes (n)no? ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
}

int main()
{
    srand((unsigned)time(NULL));
    startQuestions();
    return 0;
}