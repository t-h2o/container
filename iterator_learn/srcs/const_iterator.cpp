#include <map>
#include <set>
#include <vector>

#include <iostream>

static void
vector_iterator(void)
{
	std::vector<int> std_vector;

	std_vector.push_back(42);
	std_vector.push_back(1);
	std_vector.push_back(2);
	std_vector.push_back(3);

	/** iterator
	 * can change the value
	 * cannot set an iterator with rbegin()
	 */
	{
		std::cout << "vector: iterator" << std::endl;
		std::vector<int>::iterator it(std_vector.begin());
		std::cout << "value: " << *it << std::endl;
	}

	/** const_iterator
	 * cannot change the value
	 */
	{
		std::cout << "vector: const_iterator" << std::endl;
		std::vector<int>::const_iterator it(std_vector.begin());
		std::cout << "value: " << *it << std::endl;
	}

	/** reverse_iterator
	 * can change the value
	 */
	{
		std::cout << "vector: reverse_iterator" << std::endl;
		{
			std::vector<int>::reverse_iterator it(std_vector.begin());
			std::cout << "std::vector<int>::reverse_iterator it(std_vector.begin());" << std::endl;
			std::cout << "  value: " << *it << std::endl;
			std::cout << "--value: " << *--it << std::endl;
			std::cout << "--value: " << *--it << std::endl;
			std::cout << "--value: " << *--it << std::endl;
		}
		{
			std::vector<int>::reverse_iterator it(std_vector.rbegin());
			std::cout << "std::vector<int>::reverse_iterator it(std_vector.rbegin());" << std::endl;
			std::cout << "  value: " << *it << std::endl;
			std::cout << "++value: " << *++it << std::endl;
			std::cout << "++value: " << *++it << std::endl;
			std::cout << "++value: " << *++it << std::endl;
		}
	}

	/** const_reverse_iterator
	 * cannot change the value
	 */
	{
		std::cout << "vector: const_reverse_iterator" << std::endl;
		{
			std::vector<int>::const_reverse_iterator it(std_vector.begin());
			std::cout << "std::vector<int>::const_reverse_iterator it(std_vector.begin());" << std::endl;
			std::cout << "  value: " << *it << std::endl;
			std::cout << "--value: " << *--it << std::endl;
			std::cout << "--value: " << *--it << std::endl;
			std::cout << "--value: " << *--it << std::endl;
		}
		{
			std::vector<int>::const_reverse_iterator it(std_vector.rbegin());
			std::cout << "std::vector<int>::const_reverse_iterator it(std_vector.rbegin());" << std::endl;
			std::cout << "  value: " << *it << std::endl;
			std::cout << "++value: " << *++it << std::endl;
			std::cout << "++value: " << *++it << std::endl;
			std::cout << "++value: " << *++it << std::endl;
		}
	}
}

static void
map_iterator(void)
{
	std::pair<int, std::string> std_pair(42, "42 forty-two");
	std::map<int, std::string>	std_map;

	std_map.insert(std_pair);

	/** iterator
	 * cannot change pair.first
	 * can change pair.second
	 */
	{
		std::map<int, std::string>::iterator it(std_map.begin());
		std::cout << it->first << ": " << (*it).second << std::endl;
		it->second = "forty-two";
		std::cout << it->first << ": " << (*it).second << std::endl;
	}

	/** const_iterator
	 * cannot change pair.first
	 * cannot change pair.second
	 */
	{
		std::map<int, std::string>::const_iterator it(std_map.begin());
		std::cout << it->first << ": " << (*it).second << std::endl;
	}
}

void
const_iterator(void)
{
	map_iterator();
	vector_iterator();
}
