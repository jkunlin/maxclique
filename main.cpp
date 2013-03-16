#include "public.h"
#include "read_file.h"
#include "Vertices.h"

using namespace std;

static int num = 0;
static vector<int> maxclique;
static vector<int> tmpclique;
void expand(bool MCR, const bool * const * conn, Vertices &V);

int main(int argc, char *argv[]) {
	assert(argc == 2);
	cout << "args = " << argv[1] << endl;

	bool **conn;
	size_t size;
	read_file(argv[1], conn, size);

	clock_t start1 = time(NULL);
	clock_t start2 = clock();

	Vertices V, V_MCR;

	cout<<"--------------------------normal sort-----------------------------------"<<endl;
	V.init(size);
	V.set_degrees(conn);
	V.degree_sort();
	V.colo_sort(conn, 1);
	expand(false, conn, V);
	/*
	cout<<"maxclique: ";
	for(vector<int>::iterator iter = maxclique.begin(); iter != maxclique.end(); ++iter) {
		cout<<*iter + 1<<' ';
	}
	cout<<endl;
	*/
	cout<<"size: "<<maxclique.size()<<endl;
	cout<<"common expand num:"<<num<<endl;
	cout<<"Time = "<<difftime(time(NULL), start1) <<endl;
	cout<<"Time (precise) = "<<((double) (clock() - start2)) / CLOCKS_PER_SEC <<endl;
	
	num = 0;
	maxclique.resize(0);

	start1 = time(NULL);
	start2 = clock();

	cout<<"--------------------------MCR sort--------------------------------------"<<endl;
	V_MCR.init(size);
	V_MCR.set_degrees(conn);
	V_MCR.MCR_sort(conn);
	V_MCR.colo_sort(conn, 1);
	expand(true, conn, V_MCR);
	/*
	cout<<"maxclique: ";
	for(vector<int>::iterator iter = maxclique.begin(); iter != maxclique.end(); ++iter) {
		cout<<*iter + 1<<' ';
	}
	cout<<endl;
	*/
	cout<<"size: "<<maxclique.size()<<endl;
	cout<<"MCR expand num:"<<num<<endl;
	cout<<"Time = "<<difftime(time(NULL), start1) <<endl;
	cout<<"Time (precise) = "<<((double) (clock() - start2)) / CLOCKS_PER_SEC <<endl;

	return 0;
}

void expand(bool MCR, const bool * const * conn, Vertices &V) {
	int min_k;
	Vertices temp;
	size_t i;
	while(!V.empty()) {
		min_k = maxclique.size() > tmpclique.size() ? maxclique.size() - tmpclique.size() : -1;
		if(V.get_color_num() > min_k) {
			i = V.pop();
			tmpclique.push_back(i);
			temp.cut_vertex_from(conn, V, i);
			if(!temp.empty()) {
		//		temp.set_degrees(conn);
		//		MCR ? temp.MCR_sort(conn) : temp.degree_sort();
		//		temp.colo_sort(conn, min_k);
				num++;
				expand(MCR, conn, temp);
			}
			else if (tmpclique.size() > maxclique.size()) {
				std::cout<<"step = "<<num<<" current max size: "<<tmpclique.size()<<std::endl;
				maxclique = tmpclique;
			}
			tmpclique.pop_back();
		}
		else {
			return;
		}
	}
}
