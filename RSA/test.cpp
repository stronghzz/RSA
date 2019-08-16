#include "RSA.h"

void testString()
{
	RSA rsa;
	Key key = rsa.getKey();
	std::string strin;
	std::cout << "���������Ϣ" << std::endl;
	std::cin >> strin;
	std::vector<long> strecrept = rsa.ecrept(strin, key.ekey,key.pkey);
	std::string strout = rsa.decrept(strecrept, key.dkey, key.pkey);
	std::cout << "������Ϣ" << std::endl;
	rsa.printInfo(strecrept);
	std::cout << "������Ϣ" << std::endl;
	std::cout << strout << std::endl;
}

int main()
{
	testString();

	return 0;
}