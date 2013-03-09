#include "read_file.h"
using namespace std;

void read_file(string name, bool ** &conn, size_t &size) {
	ifstream f(name.c_str());
	char buffer[80];
	assert(f.is_open());
	set<int> v;
	multimap<int, int> e;

	while(!f.eof()) {
		f.getline (buffer, 70);
		if(buffer[0] == 'e') {
			int vi, vj;
			sscanf(buffer, "%*c %d %d", &vi, &vj);
			v.insert(vi);
			v.insert(vj);
			e.insert(make_pair(vi, vj));
		}
	}
	size = v.size();

	conn = new bool *[size];
	for(size_t i = 0; i < size; i++) {
		conn[i] = new bool[size];
		memset(conn[i], 0, size * sizeof(bool));
	}
	for(multimap<int, int>::iterator it = e.begin(); it != e.end(); it++) {
		conn[it->first - 1][it->second -1] = true;
		conn[it->second - 1][it->first - 1] = true;
	}

	cout << "|E| = "<< e.size() << " |V| = " << v.size() << " p = " << (double) e.size() / (v.size() * (v.size() - 1) /2) <<endl;
	f.close();
}
