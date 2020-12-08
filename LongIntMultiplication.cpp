//152120161008 FIRAT CAN YILDIRIM
//152120161028 KERÝM DAÞ
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string>
#include<vector>
#include<math.h>
using namespace std;
/*
*Cikan sonuc result.txt dosyasina yazilir.
*/
void writeFile(string fileName, vector<char>result)
{
	ofstream writer;
	int len = result.size() - 1;
	writer.open(fileName, ios::beg);
	if (writer.is_open())
	{
		while (len >= 0)
		{
			writer << result[len];
			len--;
		}
		writer.close();
	}
}
/*
*Verilen yoldaki dosya okunur ve vector<char>'a atilir.
*/
vector<char> readFile(string fileName, int N)
{
	ifstream reader;
	reader.open(fileName, ios::in);
	char okunan;
	vector<char> full;
	if (reader.is_open())
	{
		while (reader.get(okunan))
		{
			N--;
			if (N < 0)
				break;
			full.push_back(okunan);
		}
	}
	return full;
}
/*
*sayinin basinda varolan sifirlar yok edilir. ilk rakam 0dan farkli olur.
*/
void zeroControl(vector<char>& number)
{
	int N = number.size();
	for (int i = N - 1; i >= 0; i--)
	{
		if (number[i] - '0' == 0)
			number.pop_back();
		else
			return;
	}
	if (number.size() == 0)
		number.push_back('0');
	return;
}
/*
*uzunluklarý farkli olan sayilarin basina sifir atayarak sayilarin uzunlugunu esitler.
*/
int makeEqualLength(vector<char>& firstNumber, vector<char>& secondNumber)
{
	int len1 = firstNumber.size();
	int len2 = secondNumber.size();
	if (len1 < len2)
	{
		for (int i = 0; i < len2 - len1; i++)
		{
			firstNumber.push_back('0');
		}
		return len2;
	}
	else if (len1 > len2)
	{
		for (int i = 0; i < len1 - len2; i++)
		{
			secondNumber.push_back('0');
		}
	}
	return len1;
}
/*
*sayi*(10^n) => islemi yapilirken sayinin sonuna n=shiftStepLength kadar sifir atilir.
*bu islem icin bi temp vector<char> kullanip sifir/sifirlari sayinin sonuna ekleriz ve bu islemden sonra mevcut sayiyi da temp'e aktaririz.
*temp return edilir.
*/
vector<char> shifting(vector<char> number, int shiftStepLength)
{
	vector<char> temp;
	for (int i = 0; i < shiftStepLength; i++)
	{
		temp.push_back('0');
	}
	for (int i = 0; i < number.size(); i++)
	{
		temp.push_back(number[i]);
	}
	return temp;
}
/*
*parametre olarak verilen sayilarin toplama islemi yapilir.
*/
vector<char> add(vector<char> firstNumber, vector<char> secondNumber)
{
	vector<char> tempSum;
	int len = makeEqualLength(firstNumber, secondNumber);
	int carry = 0;
	for (int i = 0; i < len; i++)
	{
		int firstDigit = firstNumber.at(i) - '0';
		int secondDigit = secondNumber.at(i) - '0';

		int sum = (firstDigit + secondDigit + carry);
		carry = sum / 10;
		sum %= 10;
		sum = sum + '0';
		tempSum.push_back((char)sum);

	}
	if (carry > 0)
		tempSum.push_back(char(carry + '0'));;

	return tempSum;
}
/*
*parametre olarak verilen sayilarin cikarma islemi yapilir
*verilen sayilar basina sifir eklenerek ayni uzunluga getirilir.
*/
vector<char> subtract(vector<char> firstNumber, vector<char> secondNumber)
{
	int len = makeEqualLength(firstNumber, secondNumber);
	int difference;
	vector<char> tempSubt;
	if (len == 1)
	{
		difference = (firstNumber[0] - '0') - (secondNumber[0] - '0');
		if (difference < 0)
			tempSubt.push_back((char)((difference + 10) + '0'));
		else
			tempSubt.push_back((char)((difference)+'0'));
		return tempSubt;

	}
	for (int i = 0; i < len; i++)
	{
		difference = (firstNumber[i] - '0') - (secondNumber[i] - '0'); //ayni basamaklarin farki alinir.
		if (difference > 0)
			tempSubt.push_back((char)(difference + '0'));
		else if (difference < 0)
		{
			difference += 10; //fark sifirdan kücükse 10 ekleyerek pozitif hale getirilir.
			int otherDigitDiff = 0;
			if (i < len - 1)
				otherDigitDiff = (firstNumber[i + 1] - '0') - 1;//fark sifirdan kücük oldugu icin bir üst basamak 1 azaltilir.
			if (otherDigitDiff < 0)
			{
				if (i < len - 1)
					firstNumber[i + 1] = (otherDigitDiff + 10) + '0';//üst basamak da sifir kücükse +10 eklenerek pozitif hale getirilir ve güncellenir.
				tempSubt.push_back((char)(difference + '0'));//fark sonuc vectorune aktarilir.


				int tempOtherDigit = otherDigitDiff;
				int counter = i + 1;
				/*
				bir ust basamagin negatif degere düsmesinden sonra ustteki diger basamaklara bakilir ve 1 azaltilir tempOtherDigit degiskenine atilir
				tempOtherDigit  degiskeni sifirdan kücük iken bu islem sürer.
				(700129-356428 islemini ornek verecek olursak yuzler basamaklari farki negatif olacaktir(1-4). Bu farki pozitif yaptigimizda, bir ust basamaktan 1 cikarmak gerekir.
				(0-1) negatif oldugu icin +10 eklenip pozitif yapilir (bu basamak 9 olur)ve bunun da bir ust basamagindan 1 cikartilir. ..... bu islem ust basamagindan 1 cikartilinca
				pozitif olana kadar surer.)
				*/
				while (tempOtherDigit < 0)
				{
					tempOtherDigit = (firstNumber[counter + 1] - '0') - 1;
					if (tempOtherDigit < 0)
					{
						firstNumber[counter + 1] = (tempOtherDigit + 10) + '0';
					}
					else
						firstNumber[counter + 1] = (tempOtherDigit)+'0';
					counter++;
					if (counter == len - 1)
						break;
				}
			}
			else
			{
				if (i < len - 1)
					firstNumber[i + 1] = (otherDigitDiff)+'0';
				tempSubt.push_back((char)(difference + '0'));
			}
		}
		else
			tempSubt.push_back((char)(difference + '0'));
	}
	return tempSubt;
}
void Mult(vector<char> first, vector<char> second, vector<char>& result)
{
	int N = makeEqualLength(first, second);//sayilarin uzunluklari burdan bulunur ve recursion icin fonksiyonlara bu deger gonderilir.
	if (N == 1)//sayi uzunluklarý 1 ise
	{
		int n1 = (int(second[N - 1] - '0')) * (int(first[N - 1] - '0'));//sayilar carpilir.
		if (n1 >= 10)
		{
			char mod = n1 % 10 + '0';
			result.push_back(char(mod));
			n1 /= 10;
			if (n1 == 0)
				return;
		}
		result.push_back(char(n1 + '0'));
		return;
	}
	if (N % 2 == 1)//sayi uzunlugu tek ise sifir eklenerek cift yapilir.
	{
		first.push_back('0');
		second.push_back('0');
		N += 1;
	}
	int middle = N / 2;
	//first sayinin most significant bit bulunur.
	vector<char> w;
	for (int i = N - middle; i < N; i++)
	{
		w.push_back(first[i]);
	}
	//first sayinin least significant bit bulunur.
	vector<char> x;
	for (int i = 0; i < middle; i++)
	{
		x.push_back(first[i]);
	}
	//second sayinin most significant bit bulunur.
	vector<char> y;
	for (int i = N - middle; i < N; i++)
	{
		y.push_back(second[i]);
	}
	//second sayinin least significant bit bulunur.
	vector<char> z;
	for (int i = 0; i < middle; i++)
	{
		z.push_back(second[i]);
	}

	vector<char> C;//w*y
	vector<char> D;//x*z
	vector<char> E;//((w+x)*(y+z))
	Mult(w, y, C);
	Mult(x, z, D);
	Mult(add(w, x), add(y, z), E);
	E = subtract(E, C); //		 ((w+y)*(x+z))-(w*y)
	E = subtract(E, D); //		 ((w+y)*(x+z))-(w*y)-(x*z)
	C = shifting(C, N); //       (w*y)*(10^N)
	E = shifting(E, N / 2);//    (((w+y)*(x+z))-(w*y)-(x*z))*(10^(N/2))
	result = add(add(C, E), D);// (w*y)*(10^N)   +    (((w+y)*(x+z))-(w*y)-(x*z))*(10^(N/2))   +   (x*z)
}
void main()
{
	int N;
	string firstFileName = "";
	string secondFileName = "";
	string resultFileName = "result.txt";
	vector<char> numberRead1;
	vector<char> numberRead2;
	vector<char> resultNumber,
		resultNumberReverse;
	cout << "Enter N : ";
	cin >> N;
	if (N <= 0)
		return;
	cout << "Enter First File Name : ";
	cin >> firstFileName;
	cout << "Enter Second File Name : ";
	cin >> secondFileName;
	numberRead1 = readFile(firstFileName, N); //girilen ilk dosya yolundan ilk sayi okunur.
	numberRead2 = readFile(secondFileName, N);//girilen ikinci dosya yolundan ikinci sayi okunur.
	cout << "number1 : ";
	for (int i = numberRead1.size() - 1; i >= 0; i--)
	{
		cout << numberRead1[i]; //ilk sayi yazilir.
	}
	cout << endl <<"number2 : ";
	for (int i = numberRead2.size() - 1; i >= 0; i--)
	{
		cout << numberRead2[i]; //ikinci sayi yazilir.
	}
	cout << endl;
	Mult(numberRead1, numberRead2, resultNumber); //carpma islemi yapilir ve resultNumber degiskenine atanir.
	zeroControl(resultNumber); //sayinin basinda sifir var ise yok edilir.
	cout << "result  : ";//carpma islemi sonucu bulunan sayi yazilir.
	for (int i = resultNumber.size() - 1; i >= 0; i--)
	{
		cout << resultNumber[i];
		resultNumberReverse.push_back(resultNumber[i]);
	}
	cout << endl;
	writeFile(resultFileName, resultNumberReverse);//carpma sonucu bulunan sayi dosyaya yazilir.
	system("pause");
}