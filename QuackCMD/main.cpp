#include "pch.h"
#include "fileparser.h"

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

	return 0;
}