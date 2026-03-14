#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

enum enQuestionLevel { Easy = 1, Med, Hard, MixQL };

enum enOperationType { Add = 1, Sub, Mul, Div, MixOT };

struct stReadQuestions
{
    int firstNumber;
    int secondNumber;
    float playerAnswer;
    float correctAnswer;
    enQuestionLevel questionLevel;
    enOperationType operationType;

};


struct stFinalResult
{
    stReadQuestions readQuestion;
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
    stFinalResult finalResult;
    if (questionLevel == enQuestionLevel::MixQL)
        questionLevel == choiceRandomNumber(1, 3);
    finalResult.readQuestion.questionLevel = questionLevel;
    switch (finalResult.readQuestion.questionLevel)
    {
    case enQuestionLevel::Easy:
        return choiceRandomNumber(1, 10);
        break;
    case enQuestionLevel::Med:
        return choiceRandomNumber(20, 50);
        break;
    case enQuestionLevel::Hard:
        return choiceRandomNumber(50, 100);
        break;
    case enQuestionLevel::MixQL:
        return choiceRandomNumber(1, 100);
        break;

    default:
        break;
    }
}

float correctAnswer(int firstNumber, enOperationType operationType, int secondNumber)
{
    stFinalResult finalResult;
    if (operationType == enOperationType::MixOT)
    {
        operationType == (enOperationType)choiceRandomNumber(1, 4);
    }
    finalResult.readQuestion.operationType = operationType;
    switch (finalResult.readQuestion.operationType)
    {
    case enOperationType::Add:
        return (float)firstNumber + secondNumber;
        break;
    case enOperationType::Sub:
        return (float)firstNumber - secondNumber;
        break;
    case enOperationType::Mul:
        return (float)firstNumber * secondNumber;
        break;
    case enOperationType::Div:
        return ((float)firstNumber / secondNumber);
        break;

    default:
        break;
    }
}

stFinalResult showFinalResult(stFinalResult& finalResult, float correctAnswer, float userAnswer)
{
    if (correctAnswer == userAnswer)
    {
        cout << "Right Answer \n";
        finalResult.numberOfRightQuestion++;
    }
    else
    {
        cout << "Wrong Answer \n";
        cout << "The Right Answer is : " << correctAnswer << endl;
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

stFinalResult getQuestion(stFinalResult finalResult)
{
    finalResult.readQuestion.firstNumber = questionLevel(finalResult.questionLevel);
    finalResult.readQuestion.secondNumber = questionLevel(finalResult.questionLevel);
    finalResult.readQuestion.correctAnswer = correctAnswer(finalResult.readQuestion.firstNumber, finalResult.readQuestion.operationType, finalResult.readQuestion.secondNumber);
    return finalResult;
}

stFinalResult questions()
{
    stFinalResult finalResult;
    firstQusetions(finalResult);
    for (int i = 1; i <= finalResult.numberOfQuestion; i++)
    {
        getQuestion(finalResult);
        cout << "Question [" << i << "/" << finalResult.numberOfQuestion << "]\n\n";
        cout << finalResult.readQuestion.firstNumber << "\n     " << toChar(finalResult.readQuestion.operationType) << "\n"
            << finalResult.readQuestion.secondNumber << "\n__________\n";

        finalResult.readQuestion.playerAnswer = readAnswer();
        showFinalResult(finalResult, finalResult.readQuestion.correctAnswer, finalResult.readQuestion.playerAnswer);
        cout << "\n\n";
    }
    if (finalResult.numberOfRightQuestion >= finalResult.numberOfWrongQuestion)
        finalResult.isPass = true;
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

void startQuestions()
{
    stFinalResult finalResult;
    char ch;
    do {
        system("cls");
        system("color 0F");
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