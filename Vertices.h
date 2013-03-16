#ifndef VERTICES_H
#define VERTICES_H

#include "public.h"

class Vertices {
	private:
		class Vertex {
			private:
				int vindex;
				int degree;
			public:
				Vertex() : vindex(0), degree(0) {}
				void set_index(const int i) { vindex = i; }
				int get_index() const { return vindex; }
				void set_degree(const int d) { degree = d; }
				void inc_degree() { ++degree; }
				void dec_degree() { --degree; }
				int get_degree() const { return degree; }
		/*		Vertex & operator = (Vertex &v) {
					vindex = v.vindex;
					degree = v.degree;
					return *this;
				}*/
		};
		typedef std::vector<Vertex> vvec_type;
		vvec_type vertices;
		static bool desc_degree(const Vertex vi, const Vertex vj) { return vi.get_degree() > vj.get_degree(); }
	public:
		Vertices(size_t size = 0) { vertices.resize(size); }
		//init the vertices index of vector
		void init(size_t size);
		//copy vector<Vertex> vertices from v, which element connect with vertex_index
		void cut_vertex_from( const bool * const *conn, Vertices &v, int vertex_index);
		//copy vertices' index to V
		void copy_to(std::vector<int> &V) const ;
		//set degree for all vertex in vector
		void set_degrees(const  bool * const * conn);
		//sort vertex in vector according degree 
		void degree_sort() {
			std::sort( vertices.begin(), vertices.end(), desc_degree ); 
		}
		//sort vertex in vector according to MCR
		void MCR_sort(const bool * const *conn);
		//sort vertex in vector according color method, min_k = max(Qmax.szie - Q.szie + 1, 1)
		void colo_sort(const bool * const * conn, int min_k);
		bool empty() const { return vertices.empty(); }
		size_t get_size() const { return vertices.size();}
		int get_color_num() const { return vertices.back().get_degree() + 1;}
		size_t pop() { size_t index = vertices.back().get_index(); vertices.pop_back(); return index; }
#ifndef NDEBUG
		void print();
		void print_colors();
#endif
};

#endif
