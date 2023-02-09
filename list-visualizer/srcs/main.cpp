#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <stdio.h>
#include <stdlib.h>

static void
print_address(void *ptr, std::fstream &readme)
{
	static std::map<void *, std::string> address;

	std::map<void *, std::string>::iterator it = address.find(ptr);

	if (it == address.end())
	{

		std::pair<void *, std::string> p;
		p.first = ptr;

		if (address.size() == 0)
			p.second = "end";
		else
			p.second = std::to_string(address.size());

		address.insert(p);

		readme << p.second;
	}
	else
	{

		readme << it->second;
	}
}

static void
print_nodes(std::list<int> &a, std::fstream &readme)
{
	std::list<int>::iterator it(a.begin());
	std::list<int>::iterator it_end(a.end());

	readme << "\n== " << a.size()
		   << "\n\n"

			  "[graphviz, target=out_"
		   << a.size()
		   << ", format=svg]\n....\n"
			  "digraph "
			  " {\n"
			  "graph [\n"
			  "  fontname=\"JetBrains Mono,Helvetica,Arial,sans-serif\"\n"
			  "]\n"

			  "edge [\n"
			  "  arrowsize=0.5\n"
			  "  fontname=\"JetBrains Mono,Helvetica,Arial,sans-serif\"\n"
			  "  labeldistance=3\n"
			  "  labelfontcolor=\"#00000080\"\n"
			  "  penwidth=2\n"
			  "]\n";

	do
	{
		readme << "  ";
		print_address(it._M_node, readme);
		readme << " -> ";
		print_address(it._M_node->_M_prev, readme);
		readme << " [label=\"prev\"];" << std::endl;
		readme << "  ";
		print_address(it._M_node, readme);
		readme << " -> ";
		print_address(it._M_node->_M_next, readme);
		readme << " [label=\"next\"];" << std::endl;
	} while (it++ != it_end);

	readme << "}" << std::endl;
	readme << "....\n";
}

int
main(void)
{

	std::fstream   readme;
	std::list<int> a;

	readme.open("README.adoc", std::fstream::out | std::fstream::trunc);

	readme << "= Graph\n";

	for (int i = 1; i < 5; ++i)
	{
		print_nodes(a, readme);
		a.push_back(i);
	}

	readme.close();
}
