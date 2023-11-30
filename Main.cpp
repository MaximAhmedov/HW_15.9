#include <iostream>
#include "Chat.h"

int main() {

	Chat A;
	char user1[] = "user1";
	char pass1[] = "userpass1";
	char user2[] = "user2";
	char pass2[] = "userpass2";

	A.reg(user1, pass1, sizeof(pass1));
	A.reg(user2, pass2, sizeof(pass2));

	std::cout << A.login(user1, pass1, sizeof(pass1)) << std::endl;
	std::cout << A.login(user2, pass2, sizeof(pass2)) << std::endl;

	A.logout(user1, pass1, sizeof(pass1));

	std::cout << A.login(user1, pass1, sizeof(pass1)) << std::endl;
	std::cout << A.login(user2, pass2, sizeof(pass2)) << std::endl;

	return 0;
}