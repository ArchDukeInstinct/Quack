#include "pch.h"
#include "fileparser.h"
#include "list.h"

using std::cout;
using std::endl;
using std::setw;
using std::string;
namespace fs = std::filesystem;
using namespace qck;

int main(int argc, char** argv)
{
	auto root = fs::current_path().parent_path().string();
	FileParser parser;
	Token token;
	int col = 0;

	List<int> list;

	if (parser.open(root + "/Assets/test.qck"))
	{
		while ((token = parser.getNextToken()) != Token::Type::None)
		{
			if (++col % 4 == 0)
				cout << endl;

			if (!token.isTerm())
				cout << setw(20) << "[" + token.toString() + "]";
			else
				cout << setw(20) << "\"" + parser.getStringValue() + "\"";
		}

		parser.close();
	}

	cout << endl;


	try
	{
		for (auto i = 1; i < 10; i += 2)
			list.insert(i);

		for (auto i : list)
			cout << i << " ";
		cout << endl;

		list.remove(1);
		list.remove(2);

		for (auto i : list)
			cout << i << " ";
		cout << endl;

		list.insert(11);
		list.insert(15);

		for (auto i : list)
			cout << i << " ";
		cout << endl;

		list.remove(list.search(5));

		for (auto i : list)
			cout << i << " ";
		cout << endl;
	}
	catch (string exception)
	{

		cout << "\n\nError: " << exception << endl;
	}

	return 0;
}