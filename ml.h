#pragma once

#include "typedefs.h"

namespace MachineLearning {

	class MachineLearningAlgorithms{
	private:

	public:

	};

	template <class T1 = int, typename T2 = int, T2(*GetDist)(T1 &a, T1 &b) = int(*GetDist)(int &a, int &b)>
	class MetricAlgorithms : public MachineLearningAlgorithms{
	private:
		vector <pair<T1, int>> m_TrainingSample;
		vector <T1> m_TestSample;
		vector <int> m_Result;
		int m_nAmountClasses;

	public:
		MetricAlgorithms(const vector<pair<T1, int>> &_TrainingSample, const vector <T1>_TestSample, int _nAmountClasses) 
			: m_TrainingSample(_TrainingSample), m_TestSample(_TestSample), m_nAmountClasses(_nAmountClasses) {}
		
		template <typename T>
		void GeneralMetricAlgorithm(vector<T> &_weight, int k = -1)
		{		
			//if (k == -1) k = m_TrainingSample.size();
			
			assert(m_TrainingSample.size() >= k && "=====Error #1.1! Size of Training sample is not equal to size of weights vector====");
			assert(_weight.size() >= k && "=====Error #1.2! Size of Training sample is not equal to size of weights vector====");
			
			m_Result.resize(m_TestSample.size());

			for (int i = 0; i < m_TestSample.size(); i++) 
			{

				vector <pair<T2, int>> sortedData(m_TestSample.size());
				map <int, T2> summaryDists;

				for (int j = 0; j < m_TrainingSample.size(); j++) 
				{
					T2 curDist = GetDist(m_TestSample[i], m_TrainingSample[j].X);
					sortedData[j] = mp(curDist, j);
				}

				sort(all(sortedData));

				for (int j = 0; j < k; j++)
				{
					summaryDists[m_TrainingSample[sortedData[j].Y].Y] += _weight[j];
				}

				auto it = summaryDists.end();
				it--;
				m_Result[i] = (*it).X;
			}
		}
	
		template <typename T>
		vector <pair<T1, int>> GeneralMetricAlgorithm(T (*WeightFunc)(int _numberFromCur)/*, int k = -1*/) 
		{
			m_Result.resize(m_TestSample.size());
			sort(all(m_TrainingSample));
			sort(all(m_TestSample));
			for (int i = 0; i < m_TestSample.size(); i++) 
			{
				vector <pair<T2, int>> sortedData;
				vector <T> summaryDists(m_nAmountClasses);

				for (int j = 0; j < m_TrainingSample.size(); j++) 
				{
					T2 curDist = GetDist(m_TestSample[i], m_TrainingSample[j].X);
					if (curDist != 0)
						sortedData.pb(mp(curDist, j));
				}

				sort(all(sortedData));

				for (int j = 0; j < m_TrainingSample.size(); j++) 
				{
					summaryDists[m_TrainingSample[sortedData[j].Y].Y - 1] += WeightFunc(j);
				}
				int res = -1;
				int curClass = -1;
				for (int j = 0; j < m_nAmountClasses; j++)
				{
					if (summaryDists[j] > res)
					{
						curClass = j + 1;
						res = summaryDists[j];
					}
				}
				m_Result[i] = curClass;

			}
			vector <pair<T1, int>> result(m_TestSample.size());
			for (int i = 0; i < result.size(); i++)
			{
				result[i] = mp(m_TestSample[i], m_Result[i]);
			}
			return result;
		}

		void LeaveOneOut()
		{
			for (int i = 1; i < m_TrainingSample.size(); i++)
			{
	//			vector <pair<T1, int>> curRes = General
			}
		}
	};
};
