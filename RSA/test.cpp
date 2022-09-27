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

void testfile()
{
	RSA rsa;
	Key key = rsa.getKey();
	rsa.ecrept("plain.txt", "ecrept.out.txt",key.ekey, key.pkey);
	rsa.decrept("ecrept.out.txt", "dcrept.out.txt", key.dkey, key.pkey);

}
int main()
{
	//testString();
	testfile();
	return 0;
}