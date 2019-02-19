#include "utils.h"

int main(int argc, char *argv[]) {
	if (argc != 3) {
		std::cout << "Usage : receiver [bandwidth] [spreading factor]" << std::endl;
		return -1;
	}

	std::string src = makeJsonObject(argv[1], argv[2], 1,
									"123456", "987654", -90, -91,
									30, 35.236222, 129.072921);
	sendNodeREDServer(src);

	return 0;
}
