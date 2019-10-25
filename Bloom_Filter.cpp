#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>

class Bits_Array
{
	std::vector<bool> bits_array;
public:
	Bits_Array() {}

	void set_size(size_t& m)
	{
		bits_array.resize(m);
	}

	bool value_of(size_t index)
	{
		return bits_array[index];
	}

	bool find(size_t& index)
	{
		return bits_array[index];
	}

	void add(size_t index)
	{
		bits_array[index] = true;
	}

	std::string print()
	{
		std::string result = "";
		for (size_t i = 0; i < bits_array.size(); i++)
		{
			result += std::to_string(bits_array[i]);
		}
		return result;
	}
};

class Bloom_Filter 
{
	
	size_t n, hashs, m;
	double P;
	unsigned long long M = 2147483647;
	Bits_Array bits_arr;
	std::vector<size_t> primes = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263};

public:
	Bloom_Filter()
	{
		n = 0;
		hashs = 0;
		m = 0;
		P = 0;
	}

	void set (long long set_n, long double set_P)
	{
		if (set_n <= 0 || (set_P >= 1 || set_P <= 0) || (-1.0 * std::log2(set_P) < 1)) throw std::logic_error("error");
		else 
		{
			n = static_cast<size_t>(set_n);
			P = set_P;
			double logs = - static_cast<double>(std::log2(P) / std::log(2.0));
			m = static_cast<size_t>(std::round(static_cast<double>(n) * logs));
			bits_arr.set_size(m);
			hashs = static_cast<size_t>(std::round(-std::log2(P)));
		}	
	}

	std::pair<size_t, size_t> &get_m_hashs() 
	{
		std::pair<size_t, size_t> params = { m,hashs };
		return params;
	}

	size_t make_hash_index(size_t i, unsigned long long K) 
	{
		unsigned long long value = static_cast<unsigned long long>(i + 1.0) * static_cast<unsigned long long> (K % M) + static_cast<unsigned long long>(primes[i]);
		value = (value % M) % static_cast<unsigned long long> (m);
		size_t index = static_cast<size_t>(value);
		return index;
	}

	void Add(unsigned long long K)
	{
		for (size_t i = 0; i < hashs; i++)
		{
			bits_arr.add(make_hash_index(i, K));
		}
	}

	std::string Print() 
	{
		return bits_arr.print();
	}

	bool search(unsigned long long K) 
	{
		if (K < 0) throw std::logic_error("error");
		for (size_t i = 0; i < hashs; i++)
		{
			if (bits_arr.value_of(make_hash_index(i, K)) == false) return false;
		}
		return true;
	}
};


int main()
{
	std::string temp_1, temp_2, temp_3, output = "";
	Bloom_Filter Filter;
	std::getline(std::cin, temp_1, '\0');
	std::istringstream line_stream(temp_1);
	while (line_stream >> temp_1)
	{
		try
		{
			if (temp_1 == "set" && line_stream.peek() != '\n' && line_stream >> temp_2 && line_stream.peek() != '\n' &&
				line_stream >> temp_3 && line_stream.peek() == '\n')
			{
				int n = std::stoi(temp_2);
				double P = std::stod(temp_3);
				Filter.set(n, P);
				std::pair<size_t, size_t> params = Filter.get_m_hashs();
				output += std::to_string(params.first) + ' ' + std::to_string(params.second) + '\n';
				break;
			}
			else throw std::logic_error("error");
		}
		catch (...)
		{
			output+= "error\n"; line_stream.ignore(256, '\n');
		}
	}

	while (line_stream >> temp_1) 
	{
		try 
		{
			if (temp_1 == "print" && line_stream.peek() == '\n') 
			{
				output += Filter.Print() + '\n';
			}
			else if (temp_1 == "add" && line_stream.peek() != '\n' && line_stream >> temp_2 && line_stream.peek() == '\n') 
			{
			Filter.Add(std::stoull(temp_2));
			}
			else if (temp_1 == "search" && line_stream.peek() != '\n' && line_stream >> temp_2 && line_stream.peek() == '\n') 
			{
				output += std::to_string(Filter.search(std::stoull(temp_2))) + '\n';
			}
			else 
			{
				line_stream.ignore(256, '\n');
				output += "error\n";
			}
		}
		catch (...)
		{
			output += "error\n";
			line_stream.ignore(256, '\n');
		}
	}

	if (output != "") output.pop_back();
	std::cout << output;
	return 0;
}
