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

	cout<<"   ";
	for(size_t i = 0; i != size; ++i) {
		cout<<i + 1<<"  ";
	}
	cout<<endl;

	for(size_t i = 0; i != size; ++i) {
		cout<<i + 1<<"  ";
		for(size_t j = 0; j != size; ++j) {
			cout<<conn[i][j]<<"  ";
		}
		cout<<endl;
	}
	Vertices V, V_MCR;
	V.init(size);
	V_MCR.init(size);
	
	cout<<"degrees"<<endl;
	V.set_degrees(conn);
	V_MCR.set_degrees(conn);
	V_MCR.print();

	cout<<"------------common sort-------------------"<<endl;
	V.degree_sort();
	V.print();
	cout<<endl;
	V.colo_sort(conn, 1);
	V.print();
	cout<<"------------------------------------------"<<endl;
 
	cout<<"------------MCR sort----------------------"<<endl;
	V_MCR.cut_vertex_copy(conn, V, 8);
	V_MCR.set_degrees(conn);
	V_MCR.print();
	V_MCR.MCR_sort(conn);
	V_MCR.print();
	cout<<endl;
	V_MCR.colo_sort(conn, 1);
	V_MCR.print();
	cout<<"------------------------------------------"<<endl;
	return 0;
 
}
