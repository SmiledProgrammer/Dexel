#ifndef VARIABLE_ASSIGNMENT_COMPONENT_H
#define VARIABLE_ASSIGNMENT_COMPONENT_H

#include <map>
#include "SyntaxComponent.h"
#include "NumericValues.h"

namespace dexel {

	/*
		TODO:

		Przyklad:
		((width + 4) * 13) / 4 - 6 * height

		- sledz glebokosc nawiasow (zliczaj otwarcia/zamkniecia)
		- nawias moze byc w dowolnym miejscu, o ile nie jest nadmiernym zamknieciem (gdy juz brakuje nawiasow otwierajacych)
		- trzeba sprawdzac czy operatory i operandy (identyfikatory lub literaly) wystepuja na zmiane (ignorujac nawiasy pomiedzy)
		- ostroznie z przypadkiem, gdy w nawiasie jest tylko jeden operand (i w ogole gdy jest tylko jeden operand po znaku rownosci)
		- iterowac po kolejnych tokenach, a gdy natkniesz sie na operator, to tworzyc obiekt OperationValue
		- obiekty LiteralIntegerValue i IdentifierValue zawsze beda elementami OperationValue
		- jesli natkniemy sie na nawias, to rozpoczynamy rekurencyjne rozpatrywanie jedynie zawartosci tego nawiasu i jej konwersji na NumericValue
		- gdy natkniemy sie na operator powinnismy sprawdzic czy po jego prawej stronie nie ma operatora o wyzszej precedensji,
		  a jesli jest, to rekurencyjnie rozpatrzec najpierw tamta operacje i dopiero po jej konwersji na NumericValue przystapic do konwersji pierwotnej operacji
		- po lewej stronie operatora mozemy miec albo nawias (wtedy na pewno zostal on juz przetworzony na jakis NumericValue)
		  albo identyfikator/literal i wtedy, zakladajac powyzsza zasade, tez rowniez na pewno zostal on juz przetworzony na jakies NumericValue

		- IDEA polega na tym, zeby caly czas laczyc 2 operandy i operator w jedno OperationValue
		  i trzeba sie przesuwac w prawo do kolejnego operatora tak dlugo, jak znajdujemy tam operator o wyzszej precedensji od aktualnego
		- jesli natkniemy sie na nawias, to powinnismy go traktowac jako oddzielne, rekurencyjne wywolanie tej funkcji dla podzakresu indeksow

		+. nie uzywamy m_index tylko wlasnego indexu
		0. Iterujemy po tokenach, dopoki nie napotkamy nawiasu konczacego lub srednika (przy czym trzeba sprawdzac czy nawias koncowy ma otwierajacego kolege)
		1. Zawsze na poczatek sprawdzamy czy token jest otworzeniem/zamknieciem nawiasu (jesli tak, to wywolanie rekurencyjne)
			- pamietaj tylko, zeby przyjmujac wynik rekurencyjnego wywolania przesunac sie indeksem na koniec nawiasu, bo inaczej wpadniesz w nieskonczona petle rekurencji
		2. Na poczatek sprawdzamy raz czy token jest identyfikatorem/literalem (jesli nie, to blad)
		3. 


		1. Iteruj po tokenach, dopoki nie napotkasz ")" lub ";"

	*/

	class VariableAssignmentComponent : public SyntaxComponent {

		static const vector<Token::Type> m_startingPattern;
		static const map<NumericOperator, int> m_operatorsPrecedence;

		string m_variableName;
		NumericValue m_numericValue;
		Token::Type m_lastOperationRead;

	public:
		VariableAssignmentComponent(vector<Token>& tokens, int index);

		void readComponent() override;
		string convertToMCFunctionCode(const string& destinationFilepath) override;

	private:
		bool isAssignmentExpressionValid();
		NumericValue parseNumericValue(int& startingTokenIndex);
		NumericValue readOperandNumericValue(int& index);
		NumericOperator readNumericValueOperator(int index);
		bool hasOperatorHigherPrecedence(NumericOperator thisOperator, NumericOperator otherOperator);
		NumericValue tryToSimplifyNumericValue(NumericValue numericValue);
		NumericValue tryToSimplifyOperationValue(OperationValue operationValue);

	};
}

#endif
