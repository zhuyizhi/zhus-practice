#include "fstream"
#include "string"
#include "iostream"
#include "sstream"
#include "bitset"
using namespace std;

typedef unsigned char BYTE;

const int size = sizeof(char);
class TransferFile{
public:
		int transfer(std::string in_file_path, std::string out_file_path){
			std::ifstream ifs(in_file_path.c_str());
			std::ofstream ofs(out_file_path.c_str());

			if(!ifs){
				cout<<"error opening the input file"<<endl;
				return -1;
			}

			string line;
			char c;

			//char buffer[1024];
			//ifs.read(buffer, 1024);
			ifs.seekg(0, ios::end);
			unsigned long len = ifs.tellg();
			char* buffer = new char[len];
			ifs.seekg(0, ios::beg);
			ifs.read(buffer, len);
			ifs.close();
			for(int i = 0; i < len; i++){
				int c = buffer[i];
				int cr = ~c;
				buffer[i] = (char)cr;
			}

			ofs.write(buffer, len);
			ofs.close();
			delete []buffer;
		}

private:
	
	bitset<size> reverse_byte(char c){
		bitset<size> bitvec(c);
		bitvec.flip();
		return bitvec;
	}

};