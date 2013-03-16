#include "Vertices.h"

void Vertices::init(size_t size) {
	Vertex v;
	for(size_t i = 0; i != size; i++) {
		v.set_index(i);
		vertices.push_back(v);
	}
}

void Vertices::cut_vertex_from( const bool * const *conn, Vertices &v, int vertex_index ) {
	vertices.resize(0);
	for(vvec_type::const_iterator iter = v.vertices.begin(); iter != v.vertices.end(); ++iter) {
		if(conn[vertex_index][iter->get_index()])
			vertices.push_back(*iter);
	}
}

void Vertices::copy_to(std::vector<int> &V) const {
	for(vvec_type::const_iterator iter = vertices.begin(); iter != vertices.end(); ++iter) {
		V.push_back(iter->get_index());
	}
}

void Vertices::set_degrees(const bool *const *conn) {
	//set degrees to 0
	for(vvec_type::iterator iter = vertices.begin(); iter != vertices.end(); ++iter) {
		iter->set_degree(0);
	}

	for(vvec_type::iterator iter_i = vertices.begin(); iter_i != vertices.end(); ++iter_i) {
		for(vvec_type::iterator iter_j = iter_i + 1; iter_j != vertices.end(); ++iter_j) {
			if(conn[iter_i->get_index()][iter_j->get_index()]) {
				iter_i->inc_degree();
				iter_j->inc_degree();
			}
		}
	}
}

void Vertices::MCR_sort(const bool * const *conn) {
	int min_degree = vertices.size();
	vvec_type::iterator min_iter = vertices.end();

	vvec_type R;
	for(vvec_type::size_type i = 0; i != vertices.size(); ++i) {
		//find vertex with min degree
		R.resize(0);
		min_degree = vertices[0].get_degree();
		min_iter = vertices.begin();
		R.push_back(*min_iter);
		for(vvec_type::iterator iter = vertices.begin() + 1; iter != vertices.end() - i; ++iter) {
			if(iter->get_degree() == min_degree) {
				R.push_back(*iter);
			}
			else if(iter->get_degree() < min_degree) {
				min_degree = iter->get_degree();
				min_iter = iter;
			}
		}

		//regular subgraph
		if(R.size() == vertices.size() - i)
			break;
		std::swap(*min_iter, *(vertices.end() - i - 1));

		//update degrees of remain vertices
		for(vvec_type::iterator iter = vertices.begin(); iter != vertices.end() - i - 1; ++iter) {
			if(conn[iter->get_index()][(vertices.end() - i - 1) ->get_index()])
				iter->dec_degree();
		}
	}
}

//judge if a vertex is conflict with color
bool color_conflict(const bool *const * conn, int vindex, const std::vector<int> &color) {
	for(std::vector<int>::const_iterator iter = color.begin(); iter != color.end(); ++iter) {
		if(conn[*iter][vindex])
			return true;
	}
	return false;
}
void Vertices::colo_sort(const bool * const * conn, int min_k) {
	if(min_k <= 0)
		min_k = 1;
	typedef std::vector<int> color;
	typedef std::vector<color> colors;
	static color C;
	static colors Cs;
	size_t colors_num = 0;
	C.resize(0);

	for(colors::iterator iter = Cs.begin(); iter != Cs.end(); ++iter) {
		iter->resize(0);
	}

	vvec_type::iterator insert_ver_iter = vertices.begin();
	for(vvec_type::iterator ver_iter = vertices.begin(); ver_iter != vertices.end(); ++ver_iter) {

		//find the proper color to insert vertex
		colors::size_type i = 0;
		for(; i != colors_num; ++i) {
			if(!color_conflict(conn, ver_iter->get_index(), Cs[i])) {
				//proper color found
				Cs[i].push_back(ver_iter->get_index());
				break;
			}
		}

		//no proper color found, create empty one
		if(i == colors_num) {
			C.resize(0);
			C.push_back(ver_iter->get_index());
			if(Cs.size() > colors_num)
				C.swap(Cs[colors_num]);
			else
				Cs.push_back(C);
			++colors_num;
		}
		//contain small color vertices in order
		if(i + 1 < static_cast<unsigned int>(min_k)) {
			insert_ver_iter->set_index(ver_iter->get_index());
			insert_ver_iter->set_degree(0);
			++insert_ver_iter;
		}
		/*
		//find the proper color to insert vertex
		colors::iterator colors_iter = Cs.begin();
		for(; colors_iter != Cs.end(); ++colors_iter) {
			if(!color_conflict(conn, ver_iter->get_index(), *colors_iter)) {
				//proper color found
				(*colors_iter).push_back(ver_iter->get_index());
				break;
			}
		}

		//no proper color found, create empty one
		if(colors_iter == Cs.end()) {
			C.resize(0);
			C.push_back(ver_iter->get_index());
			Cs.push_back(C);
			colors_iter = Cs.end() - 1;
			++colors_num;
		}
		//contain small color vertices in order
		if(colors_iter - Cs.begin() + 1 < min_k) {
			insert_ver_iter->set_index(ver_iter->get_index());
			insert_ver_iter->set_degree(0);
			++insert_ver_iter;
		}
		*/
	}
	colors::size_type i = min_k - 1;
	for(; i < Cs.size(); ++i) {
		for(color::size_type j = 0; j != Cs[i].size(); ++insert_ver_iter, ++j) {
			insert_ver_iter->set_index(Cs[i][j]);
			insert_ver_iter->set_degree(i);
		}
	}
}

#ifndef NDEBUG
void Vertices::print()
{
	for(vvec_type::iterator iter = vertices.begin(); iter != vertices.end(); ++iter) {
		std::cout<<iter->get_index() + 1<<"  ";
	}
	std::cout<<std::endl;

	for(vvec_type::iterator iter = vertices.begin(); iter != vertices.end(); ++iter) {
		std::cout<<iter->get_degree()<<"  ";
	}
	std::cout<<std::endl;
}
void Vertices::print_colors(){
	int pre_color = vertices.begin()->get_degree();
	int count = 1;
	for(vvec_type::iterator iter = vertices.begin() + 1; iter != vertices.end(); ++iter) {
		if(pre_color != iter->get_degree()) {
			count = 1;
			std::cout<<count<<"  ";
			pre_color = iter->get_degree();
			continue;
		}
		++count;
	}
	std::cout<<count;
}
#endif
