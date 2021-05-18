// LabaIvana2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
using namespace std;


#include <D:\Project\VS2019\Labs\cryptopp850\osrng.h>
#include <D:\Project\VS2019\Labs\cryptopp850\cryptlib.h>
#include <D:\Project\VS2019\Labs\cryptopp850\files.h>
#include <D:\Project\VS2019\Labs\cryptopp850\hex.h>
#include <D:\Project\VS2019\Labs\cryptopp850\modes.h>
#include <D:\Project\VS2019\Labs\cryptopp850\rijndael.h>

//using namespace CryptoPP;



int main()
{
	using namespace CryptoPP;
	AutoSeededRandomPool rng;
	HexEncoder encoder(new FileSink(cout));
	string plainText = "Text what we want to encrypt";
	string encryptText, decyptText;
	SecByteBlock key(AES::DEFAULT_KEYLENGTH);
	SecByteBlock iv(AES::BLOCKSIZE);

	cout << "plain text: " << plainText << endl;
	rng.GenerateBlock(key, key.size());
	rng.GenerateBlock(iv, iv.size());

	try
	{
		CBC_Mode< AES >::Encryption e;
		e.SetKeyWithIV(key, key.size(), iv);
		StringSource s(plainText, true,
			new StreamTransformationFilter(e,
				new StringSink(encryptText)
			)
		);
	}
	catch (const Exception& e)
	{
		std::cerr << e.what() << std::endl;
		exit(1);
	}

	cout << "key: ";
	encoder.Put(key, key.size());
	encoder.MessageEnd();
	cout << endl;

	cout << "iv: ";
	encoder.Put(iv, iv.size());
	encoder.MessageEnd();
	cout << endl;

	cout << "cipher text: ";
	encoder.Put((const byte*)&encryptText[0], encryptText.size());
	encoder.MessageEnd();
	cout << endl;

	try
	{
		CBC_Mode< AES >::Decryption d;
		d.SetKeyWithIV(key, key.size(), iv);

		StringSource s(encryptText, true,
			new StreamTransformationFilter(d,
				new StringSink(decyptText)
			)
		);

		std::cout << "recovered text: " << decyptText << std::endl;
	}
	catch (const Exception& d)
	{
		std::cerr << d.what() << std::endl;
		exit(1);
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
