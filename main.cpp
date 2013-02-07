#include "public.h"
#include "read_file.h"

using namespace std;

int main(int argc, char *argv[]) {
	assert(argc == 2);
	cout << "args = " << argv[1] << endl;

	bool **conn;
	int size;
	read_file(argv[1], conn, size);

	return 0;
}
