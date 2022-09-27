#include "RSA.h"
#include <math.h>
#include <fstream>
RSA::RSA()
{
	produce_keys();
}
void RSA::ecrept(const char* plain_file_in, const char* ecrept_file_out,
	long ekey, long pkey)
{
	std::ifstream fin(plain_file_in);
	std::ofstream fout(ecrept_file_out,std::ofstream::app);
	if (!fin.is_open())
	{
		std::cout << "open file failed!" << std::endl;
		return;
	}
	const int NUM = 256;
	char buffer[NUM];
	long buffer_out[NUM];
	int curNum;
	//打开文件，按块读取，逐段加密
	while (!fin.eof())
	{
		fin.read(buffer, NUM);
		curNum = fin.gcount();//最近读了多少字节
		for (int i = 0; i < curNum; ++i)
		{
			buffer_out[i] = ecrept((long)buffer[i], ekey, pkey);
		}
		fout.write((char*)buffer_out, curNum * sizeof(long));
	}
	fin.close();
	fout.close();
}
void RSA::decrept(const char* ecrept_file_in, const char* plain_file_out,
	long dkey, long pkey) 
{
	std::ifstream fin(ecrept_file_in);
	std::ofstream fout(plain_file_out,std::ofstream::app);
	if (!fin.is_open())
	{
		std::cout << "open file failed!" << std::endl;
		return;
	}
	const int NUM = 256;
	long buffer[NUM];
	char buffer_out[NUM];
	int curNum;
	//打开文件，按块读取，逐段加密
	while (!fin.eof())
	{
		fin.read((char*)buffer, NUM * sizeof(long));
		curNum = fin.gcount();//最近读了多少字节
		curNum /= sizeof(long);
		for (int i = 0; i < curNum; ++i)
		{
			buffer_out[i] = (char)ecrept(buffer[i], dkey, pkey);
		}
		fout.write(buffer_out, curNum);
	}
	fin.close();
	fout.close();
}

std::vector<long> RSA::ecrept(std::string& str_in, long ekey, long pkey)
{
	std::vector<long> vecout;
	for (const auto&e : str_in)
	{
		vecout.push_back(ecrept(e, ekey, pkey));
	}
	return vecout;
}
std::string RSA:: decrept(std::vector<long>& ecrept_str, long dkey, long pkey)
{
	std::string strout;
	for (const auto& e : ecrept_str)
	{
		strout.push_back((char)ecrept(e, dkey, pkey));
	}
	return strout;
}

void RSA::printInfo(std::vector<long>& ecrept_str)
{
	for (const auto& e : ecrept_str)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
}

//模幂运算
long RSA::ecrept(long msg, long key, long pkey)
{
	//溢出
	/*long ret = pow(msg,key);
	*/
	long msg_out = 1;
	long a = msg;
	long b = key;
	int c = pkey;
	while (b)
	{
		if (b & 1)
		{
			msg_out = (msg_out*a) % c;
		}
		b >>= 1;
		a = (a*a) % c;
	}
	return msg_out;
}
long RSA::produce_prime()
{
	srand(time(nullptr));
	long prime = 0;
	while (1)
	{
		prime = rand() % 50 + 2;
		if (is_prime(prime))
			break;
	}
	return prime;
}
bool RSA::is_prime(long prime)
{
	if (prime < 2)
	{
		return false;
	}
	for (int i = 2; i <= sqrt(prime); ++i)
	{
		if (prime % i == 0)
		{
			return false;
		}	
	}
	return true;
}
void RSA::produce_keys()
{
	//随机选择两个不相等的质数
	long prime1 = produce_prime();
	long prime2 = produce_prime();
	while (prime1 == prime2)
	{
		prime2 = produce_prime();
	}
	_key.pkey = produce_pkey(prime1, prime2);
	long orla = produce_orla(prime1, prime2);
	_key.ekey = produce_ekey(orla);
	_key.dkey = produce_dkey(_key.ekey, orla);
}
long RSA::produce_pkey(long prime1, long prime2)
{
	return prime1 * prime2;
}
long RSA::produce_orla(long prime1, long prime2)
{
	return (prime1 - 1) * (prime2 - 1);
}
long RSA::produce_ekey(long orla)
{
	long ekey;
	srand(time(nullptr));
	while (1)
	{
		ekey = rand() % orla;
		if (ekey > 1 && produce_gcd(ekey, orla) == 1)
			break;
	}
	return ekey;
}
long RSA::produce_gcd(long ekey, long orla)
{
	//gcd(a,b) = gcd(b,a%b)
	long residual;
	while (residual = ekey % orla)
	{
		ekey = orla;
		orla = residual;
	}
	return orla;
}
long RSA::produce_dkey(long ekey, long orla)
{
	//(dkey*ekey)% orla == 1;
	long dkey = orla / ekey;
	while (1)
	{
		if ((dkey * ekey) % orla == 1)
			break;
		++dkey;
	}
	return dkey;
}