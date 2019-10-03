
#include "parser.cpp"
int main() {
    std::string str;
    while (true) {
        Response result;
        std::getline(std::cin, str);
        result = parse_request(str.c_str());
        if(result.code)
            std::cerr << result.errorMsg << std::endl;
        printf("ENTER NEW COMMAND\n");
    }
}