#include "RSA.h"

void testString()
{
	RSA rsa;
	Key key = rsa.getKey();
	std::string strin;
	std::cout << "输入加密信息" << std::endl;
	std::cin >> strin;
	std::vector<long> strecrept = rsa.ecrept(strin, key.ekey,key.pkey);
	std::string strout = rsa.decrept(strecrept, key.dkey, key.pkey);
	std::cout << "加密信息" << std::endl;
	rsa.printInfo(strecrept);
	std::cout << "解密信息" << std::endl;
	std::cout << strout << std::endl;
}

int main()
{
	testString();

	return 0;
}