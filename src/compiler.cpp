#include "ast.hpp"
#include <string>
#include <fstream>

using namespace std;    
extern FILE* yyin;


int main(int argc, char *argv[])
{
ofstream fileOut;
        // Parse the AST
        if ((argc == 5) && (std::string(argv[1]) == "-S")) //INPUT FILE
        {
            yyin = fopen(argv[2], "r");
        }else{
            return 1;
        }
        if ((argc == 5) && (std::string(argv[3]) == "-o")) //OUTPUT FILE
        {
            fileOut.open(argv[4]);
        }else{
            return 1;
        }





    Expression *ast=parseAST();

    Context context = Context();
    ast->codeGen(fileOut,"$v0",context);

    //fileOut.close();

    return 0;
    
}