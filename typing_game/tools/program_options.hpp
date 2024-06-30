
#include <vector>
#include <string_view>

class ProgramOptions {
public:
	static void parse(int argc, char* argv[]);

	static const std::vector<std::string_view> &inputArguments();

private:


};