#include "pch.h"
#include "CppUnitTest.h"
#include <ctime>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestMahjong
{
	TEST_CLASS(UnitTestMahjong)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			clock_t start = clock();
			clock_t end = clock();
		}
	};
}
