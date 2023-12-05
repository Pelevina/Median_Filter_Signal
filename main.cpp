#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> medianFilter(vector<int>& signals, int window)
{
	vector<int> res(signals.size());
	for (size_t i{}; i < signals.size(); i++)
	{
		vector<int> v(window);
		v[v.size() / 2] = signals[i];
		int left_dif = i - window / 2;
		size_t right_dif = i + window / 2;
		for (size_t j{}; j < v.size() / 2; j++)
		{
			if (left_dif < 0)
			{
				v[j] = signals[0];
				left_dif++;
			}
			else
			{
				v[j] = signals[i + (j - v.size() / 2)];
			}
		}
		for (size_t j{v.size() - 1}; j > v.size() / 2; j--)
		{
			if (right_dif > signals.size() - 1)
			{
				v[j] = signals[signals.size() - 1];
				right_dif--;
			}
			else
			{
				v[j] = signals[i + (j - v.size() / 2)];
			}
		}
		sort(v.begin(), v.end());
		res[i] = v[v.size() / 2];
	}
	return res;
}

int main(int argc, char* argv[])
{
	vector<int> signals;
	size_t size;
	cout << "Enter count of signals: ";
	cin >> size;
	cout << "Enter signals for filtering: ";
	for (size_t i{}; i < size; i++)
	{
		int a;
		cin >> a;
		signals.push_back(a);
	}
	if (argc >= 2)
	{
		string w(argv[1]);
		try
		{
			int window = stoi(w);
			if (window >= 1 && window % 2 != 0)
			{
				vector<int> filtered = medianFilter(signals, window);
				cout << "Filtered signals: ";
				for (size_t i{}; i < filtered.size(); i++)
				{
					cout << filtered[i] << " ";
				}
				cout << endl;
			}
			else if (window < 1)
			{
				cerr << "Window size for median filter is less or equal 1";
			}
			else
			{
				cerr << "Window size for median filter is even";
			}
		}
		catch(const invalid_argument&)
		{
			cerr << "Window size for median filter is not integer";
		}
	}
	else
	{
		cerr << "Window size is not defined";
	}
}
