#include "pch.h"
#include "fileparser.h"
#include "compiler.h"

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
	Compiler compiler;
	Context context;

	Token token;
	int col = 0;

	if (parser.open(root + "/Assets/test.qck"))
	{
		while ((token = parser.getNextToken()) != Token::Type::None)
		{
			if (++col % 4 == 0)
				cout << endl;

			if (!token.isTerm())
				cout << std::left << setw(20) << "[" + token.toString() + "]";
			else
				cout << std::left << setw(20) << "\"" + parser.getStringValue() + "\"";
		}

		parser.reset();
		
		compiler.setContext(&context);
		compiler.compile(&parser);

		parser.close();
	}

	return 0;
}