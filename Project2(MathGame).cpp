#include <iostream>
#include<cstdlib>
using namespace std;
enum enLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, Mixx = 5 };
struct stInfoOfQuestion 
{
	short Number1, Number2, CorrectAnswer, PlayerAnswer;
	enLevel Level;
	enOperationType Operation;
};
struct stInfoOfQuizz 
{
	short NumOfQuestion = 0;
	stInfoOfQuestion Question;
};
struct stPlayerInfo
{
	short PlayerCorrect = 0;
	short PlayerWrong = 0;
};
enLevel GetQuestionLevel()
{
	cout << "\nEnter Question Level [1] Easy, [2] Med, [3] Hard, [4] Mix ?";
	int Level;
	cin >> Level;
	return enLevel(Level);
}
enOperationType GetOpType()
{	
	cout << "\nEneter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ?";
	int Operation;
	cin >> Operation;
	return enOperationType(Operation);
}
void ClearScreen()
{
	system("cls");
	system("color 0f");
}
void CorrectAnswerScreen()
{
	system("color 2f");
}
void WrongAnswerScreen()
{
	system("color 4f");
}
short GetNumberOfQuestion()
{
	cout << "How Many Questions do you want to answer ?";
	short NumOfQuestion = 0;
	cin >> NumOfQuestion;
	return NumOfQuestion;
}
short GetPlayerAnswer()
{
	short Answer = 0;
	cin >> Answer;
	return Answer;
}
short RandomNumber(int From, int To)
{
	short randNum = rand() % (To - From + 1) + From;
	return randNum;
}
short GenerateNumberDepanedOnLevel(stInfoOfQuizz InfoOfQuizz)
{
	switch (InfoOfQuizz.Question.Level)
	{
	case enLevel::Easy:return RandomNumber(1, 10);
		break;
	case enLevel::Med:return RandomNumber(10, 50);
		break;
	case enLevel::Hard:return RandomNumber(50, 100);
		break;
	case enLevel::Mix:return RandomNumber(1, 100);
		break;
	}
}
enOperationType ChooseOperationIfMixIsChoosen()
{
	return enOperationType(RandomNumber(1, 4));
}
short FindCorrectAnswer(stInfoOfQuizz &InfoOfQuizz)
{
	if(InfoOfQuizz.Question.Operation!= enOperationType::Mixx)
	switch (InfoOfQuizz.Question.Operation)
	{
	case enOperationType::Add:return (InfoOfQuizz.Question.Number1 + InfoOfQuizz.Question.Number2);
		break;
	case enOperationType::Sub:return (InfoOfQuizz.Question.Number1 - InfoOfQuizz.Question.Number2);
		break;
	case enOperationType::Mul:return (InfoOfQuizz.Question.Number1 * InfoOfQuizz.Question.Number2);
		break;
	case enOperationType::Div:return (InfoOfQuizz.Question.Number1 / InfoOfQuizz.Question.Number2);
		break;
	}
	else
	{
		InfoOfQuizz.Question.Operation=ChooseOperationIfMixIsChoosen();
		FindCorrectAnswer(InfoOfQuizz);
	}
}
string PrintOperation(stInfoOfQuizz &InfoOfQuizz)
{
	switch (InfoOfQuizz.Question.Operation)
	{
	case enOperationType::Add:return "+\n";
		break;
	case enOperationType::Sub:return "-\n";
		break;
	case enOperationType::Mul:return "*\n";
		break;
	case enOperationType::Div:return "/\n";
		break;
	default:return "Mix\n";
		break;
	}
}
string PrintLevel(stInfoOfQuizz InfoOfQuizz)
{
	switch (InfoOfQuizz.Question.Level)
	{
	case enLevel::Easy:return "Easy\n";
		break;
	case enLevel::Med:return "Med\n";
		break;
	case enLevel::Hard:return "Hard\n";
		break;
	case enLevel::Mix:return "Mix\n";
		break;
	}
}
void PrintTheQuestion(stInfoOfQuizz InfoOfQuizz,short NumberOfQuestion)
{
	cout << "\nQuestion [" << NumberOfQuestion << "/" << InfoOfQuizz.NumOfQuestion << "]\n\n";
	cout << InfoOfQuizz.Question.Number1 << endl;
	cout << InfoOfQuizz.Question.Number2 << " ";
	cout<<PrintOperation(InfoOfQuizz);
	cout << "_______________\n";

}
bool CheckIfAnswerIsCorrect(stInfoOfQuizz InfoOfQuizz)
{
	return (InfoOfQuizz.Question.PlayerAnswer == InfoOfQuizz.Question.CorrectAnswer);
}
void PrintCorrectAnswer()
{
	CorrectAnswerScreen();
	cout << "Right Answer :-)\n\n";
}
void PrintWrongAnswer(stInfoOfQuizz InfoOfQuizz)
{
	WrongAnswerScreen();
	cout << "Wrong Answer :-(\n";
	cout << "The right answer is: " << InfoOfQuizz.Question.CorrectAnswer << "\n\n";

}
void DetermineTheFinalResult(stPlayerInfo PlayerInfo)
{
	if (PlayerInfo.PlayerCorrect > PlayerInfo.PlayerWrong)
		cout << "Pass :-)\n";
	else
		cout << "Fail :-(\n";
}
void PrintFinalResult(stPlayerInfo PlayerInfo, stInfoOfQuizz InfoOfQuizz)
{
	cout << "\n----------------------------------------\n";
	cout << " Final Resultes is ";
	DetermineTheFinalResult(PlayerInfo);
	cout << "\n----------------------------------------\n";

}
void GenerateOneQuestion(stPlayerInfo& PlayerInfo, stInfoOfQuizz InfoOfQuizz,short NumberOfQuestion)
{
	InfoOfQuizz.Question.Number1 = GenerateNumberDepanedOnLevel(InfoOfQuizz);
	InfoOfQuizz.Question.Number2 = GenerateNumberDepanedOnLevel(InfoOfQuizz);
	InfoOfQuizz.Question.CorrectAnswer = FindCorrectAnswer(InfoOfQuizz);
	PrintTheQuestion(InfoOfQuizz, NumberOfQuestion);
	InfoOfQuizz.Question.PlayerAnswer = GetPlayerAnswer();
	if (CheckIfAnswerIsCorrect(InfoOfQuizz))
	{
		PlayerInfo.PlayerCorrect++;
		PrintCorrectAnswer();
	}
	else
	{
		PlayerInfo.PlayerWrong++;
		PrintWrongAnswer(InfoOfQuizz);
	}
}
void PrintSummaryResult(stInfoOfQuizz &InfoOfQuizz, stPlayerInfo PlayerInfo)
{
	cout << "Number of Questions: " << InfoOfQuizz.NumOfQuestion << endl;
	cout << "Questions Level"<< ": " << PrintLevel(InfoOfQuizz) << endl;
	cout << "OpType"<< ": " << PrintOperation(InfoOfQuizz) << endl;
	cout << "Number Of Right Answers: " << PlayerInfo.PlayerCorrect << endl;
	cout << "Number Of Wrong Answers: " << PlayerInfo.PlayerWrong << endl;
	cout << "----------------------------------------\n";
}
void PlayAgain(char& Loop)
{
	char Again;
	cout << "Do you Want to Play Again? Y/N?";
	cin >> Again;
	Loop = Again;

}
void MathGame()
{
	char Loop = 'y';
	do
	{
		ClearScreen();
		stInfoOfQuizz InfoOfQuizz;
		stPlayerInfo PlayerInfo;
		InfoOfQuizz.NumOfQuestion = GetNumberOfQuestion();
		InfoOfQuizz.Question.Level = GetQuestionLevel();
		InfoOfQuizz.Question.Operation = GetOpType();
		for (int i = 0; i < InfoOfQuizz.NumOfQuestion; i++)
		{
			GenerateOneQuestion(PlayerInfo, InfoOfQuizz, i + 1);
		}
		PrintFinalResult(PlayerInfo, InfoOfQuizz);
		PrintSummaryResult(InfoOfQuizz, PlayerInfo);
		PlayAgain(Loop);
	} while (Loop == 'y' || Loop == 'Y');
	
}
int main()
{
	srand((unsigned)time(NULL));
	MathGame();
}
