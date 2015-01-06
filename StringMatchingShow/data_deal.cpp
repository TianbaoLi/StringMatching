#include<fstream>
using namespace std;
int main()
{
	ifstream fin("article.txt");
	ofstream fout("text.txt");
	char c;
	while(fin>>c)
		if(c!='\n')
			fout<<c;
	return 0;
}
