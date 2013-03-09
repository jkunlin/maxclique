#include "public.h"
#include "read_file.h"
#include "Vertices.h"

using namespace std;

int main(int argc, char *argv[]) {
	assert(argc == 2);
	cout << "args = " << argv[1] << endl;

	bool **conn;
	size_t size;
	read_file(argv[1], conn, size);

	Vertices V(size);
	return 0;
}
