#include "pch.h"
#include "CppUnitTest.h"
#include "../ALGSD_lab_3/ALGSD_lab_3.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ALGSDlab3test
{
	TEST_CLASS(ALGSDlab3test)
	{
	public:
		
		TEST_METHOD(Test_iterator)
		{
			Heap heap(1);
			Iterator* dfs, * bfs;
			heap.insert(1);
			heap.insert(2);
			heap.insert(3);
			heap.insert(4);
			heap.insert(666);
			heap.insert(4);
			heap.insert(9);
			heap.insert(7);
			int arrayDfs[9], i = 0;
			dfs = heap.create_dfs();
			bfs = heap.create_bfs();
			if (dfs->has_next()) {
				while (dfs->has_next()) { arrayDfs[i++] = dfs->next(); }
			}
			int arrayBfs[9]; i = 0;
			if (bfs->has_next()) {
				while (bfs->has_next()) { arrayBfs[i++] = bfs->next(); }
			}
			Assert::AreEqual(666, arrayDfs[0]);
			Assert::AreEqual(9, arrayDfs[1]);
			Assert::AreEqual(7, arrayDfs[2]);
			Assert::AreEqual(1, arrayDfs[3]);
			Assert::AreEqual(3, arrayDfs[4]);
			Assert::AreEqual(2, arrayDfs[5]);
			Assert::AreEqual(4, arrayDfs[6]);
			Assert::AreEqual(1, arrayDfs[7]);
			Assert::AreEqual(4, arrayDfs[8]);

			Assert::AreEqual(666, arrayBfs[0]);
			Assert::AreEqual(9, arrayBfs[1]);
			Assert::AreEqual(4, arrayBfs[2]);
			Assert::AreEqual(7, arrayBfs[3]);
			Assert::AreEqual(2, arrayBfs[4]);
			Assert::AreEqual(1, arrayBfs[5]);
			Assert::AreEqual(4, arrayBfs[6]);
			Assert::AreEqual(1, arrayBfs[7]);
			Assert::AreEqual(3, arrayBfs[8]);
			delete dfs, bfs;
		}
		TEST_METHOD(Test_Heap_operations)
		{
			Heap heap(1), empyHeap;
			Iterator* dfs, * bfs;
			heap.insert(1);
			heap.insert(2);
			heap.insert(15);
			heap.insert(4);
			heap.insert(42);
			heap.insert(4);
			heap.insert(19);
			heap.insert(7);
			/*
			Heap status					
							42
						  /		\
						 19		15
					   /   \   /   \
					  7     2  1    4
					/  \
			      1    4
			after insert(3)
							42
						  /		\
						 19		15
					   /   \   /   \
					  7     2  1    4
					/  \             \
				  1    4              3
			after remove(7)
							42
						  /		\
						 19		15
					   /   \   /   \
					  4     2  1    4
					/                \
				  1                   3
			*/
			Assert::IsFalse(heap.contains(8));
			Assert::IsTrue(heap.contains(42));
			heap.insert(3);
			Assert::IsTrue(heap.contains(3));
			heap.remove(7);
			Assert::IsFalse(heap.contains(7));
			Assert::IsTrue(heap.contains(1)); Assert::IsTrue(heap.contains(4));
		}
		TEST_METHOD(Test_Stack)
		{
			Stack<int> stack;
			for (int i = 0; i < 10; i++)
			{
				stack.push(i);
			}
			Assert::IsFalse(stack.empty());
			for (int i = 9; i >= 0; i--) { Assert::AreEqual(stack.top(), i); stack.pop(); }
			Assert::IsTrue(stack.empty());
			bool check = 1;
			try
			{
				stack.top();
			}
			catch (std::out_of_range)
			{
				check = 0;
			}
			Assert::IsFalse(check);
		}
		TEST_METHOD(Test_Queue)
		{
			Queue<int> queue;
			for (int i = 0; i < 10; i++)
			{
				queue.push(i);
			}
			Assert::IsFalse(queue.empty());
			for (int i = 0; i < 10; i++)
			{
				Assert::AreEqual(queue.front(), i); queue.pop();
			}
			Assert::IsTrue(queue.empty());
			bool check = 1;
			try
			{
				queue.front();
			}
			catch (std::out_of_range)
			{
				check = 0;
			}
			Assert::IsFalse(check);
		}
	};
}
