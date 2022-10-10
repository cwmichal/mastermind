#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

static int CODE_SIZE = 4;

void Welcome()
{
	cout<< "Welcome to the Mastermind. "<<endl;
	cout<< "You have 12 chances to guess a combination of "<<endl;
	cout<< "4 non-repeating digits from 0 to 9."<<endl;
	cout<< "Enter your digits as xxxx. " <<endl;
}

template<typename T>
void Logging(string s, T var)
{
	cout << "LOG: " << s << " " << var << endl; 
}

vector<int> IntToIntVector(int number)
{
	vector<int> vec(CODE_SIZE);
	for (int i=0; i < CODE_SIZE; ++i)
	{
		vec[CODE_SIZE-i-1] = number%10;
		number/=10;
	}
	return vec;
}

int MasterCodeCreator()
{
	vector<int> v {0,1,2,3,4,5,6,7,8,9};
	random_shuffle(v.begin(), v.end());
	v.erase(v.begin(),v.begin()+6);
	
	reverse(v.begin(), v.end());
    int dec = 1;
    int res = 0;
    for (auto& item : v)
    {
        res += item * dec;
        dec *= 10;
    }
	return res;
}

int main(){
		
	Welcome();
	int mastercode = MasterCodeCreator();
	//Logging("The computer chose: ", mastercode);
	char command {};
	int guess {};	
	
	for(int i = 1; true; ++i)  
	{
		cout<< "Enter your guess: ";
		cin >> guess;
		if(guess > 9999)
		{
			cout << "Please enter 4-digit code" << endl;
			continue;
		}
		if(guess == mastercode)
		{
			cout << "Congrats, you broke the mastercode: *" << mastercode << "* in " << i << " tries." << endl; 
			break;
		}
		else
		{
			auto array_guess = IntToIntVector(guess);		
			auto array_mastercode = IntToIntVector(mastercode);

			int correctDigits {};
			int correctDigitsInSpot {};

			for (int k=0; k < CODE_SIZE; ++k)
			{
				if(array_guess[k] == array_mastercode[k])
					++correctDigitsInSpot;
				
			}
			
			for (int k=0; k < CODE_SIZE; ++k)
			{
				for(int j=0; j < CODE_SIZE ; ++j)
				{
					if(array_guess[j] == array_mastercode[k])
					{
						++correctDigits;
						Logging("correctDigits", correctDigits);
						break;
					}
				}
			}
			cout<<"Correct Digits: " << correctDigits << endl;
			cout<<"Correct Digits in Spot: "<< correctDigitsInSpot << endl;
		} 
		
		cout << "Do you want to keep guessing? (y/n)" << endl;
		cin >> command;
		if(command == 'n')
		{
			break;
		}
	}
	
	cout << "Goodbye" <<endl;
    return 0;
}
