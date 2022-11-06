#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	ifstream ifs("data.txt");
	vector<string> v1;
	string buf;

	if(ifs)
	{
		while(getline(ifs,buf))
		{
			v1.push_back(buf);
		}
	}


	for(const auto &s : v1)
		cout << s << endl;

	return 0;
}