/*
Author: Phillip Sopt
Description:
This is the set of test cases I made for the Graph.h. It should cover all the cases for every function.
Note that these set of test cases were written using Visual Studios testing framework. So if you want to use them,
either convert them to regular old assert commands in C++ or import it into Visual Studio.

*/
#include "stdafx.h"
#include <vector>
#include <string>
#include "CppUnitTest.h"
#include "Graph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:

		////////////////////////////////// BFS NPATH //////////////////////////////////////////////////////////
		TEST_METHOD(t_BFS_npath)
		{
			graph g;
			vector<graph::vertex_label> bfs_rpt;

			//test1
			g.read_file("test1");
			g.bfs(0, bfs_rpt);
			//            a b c e d
			int arr[] = { 1,1,1,2,1 };
			for (int i = 0; i < bfs_rpt.size(); i++)
			{
				Assert::AreEqual(arr[i], bfs_rpt[i].npaths, L"arr to bst_rpt check", LINE_INFO());
			}
			g.reset();

			//test2
			g.read_file("test2");
			g.bfs(0, bfs_rpt);
			//             a b c f d h e g
			int arr2[] = { 1,1,1,2,1,1,3,1 };
			for (int i = 0; i < bfs_rpt.size(); i++)
			{
				Assert::AreEqual(arr2[i], bfs_rpt[i].npaths, L"arr to bst_rpt check", LINE_INFO());
			}
			g.reset();

			//test3
			g.read_file("test3");
			g.bfs(0, bfs_rpt);
			//             a b d f c g e h i k j l
			int arr3[] = { 1,1,1,1,2,2,1,2,2,2,3,2 };
			for (int i = 0; i < bfs_rpt.size(); i++)
			{
				Assert::AreEqual(arr3[i], bfs_rpt[i].npaths, L"arr to bst_rpt check", LINE_INFO());
			}
			g.reset();
		}

		///////////////////////////////////// BFS SHORT PATH ////////////////////////////////////////////
		TEST_METHOD(t_BFS_shortpath)
		{
			std::stringstream ss;
			graph g;
			vector<graph::vertex_label> bfs_rpt;

			//test1
			g.read_file("test1");
			g.bfs(0, bfs_rpt);
			//a b c e d
			double arr[] = { 0,1,1,2,2 };
			for (int i = 0; i < bfs_rpt.size(); i++)
			{
				Assert::AreEqual(arr[i], bfs_rpt[i].dist, L"arr to bst_rpt shortes check", LINE_INFO());
			}
			g.reset();

			//test2
			g.read_file("test2");
			g.bfs(0, bfs_rpt);
			g.display();
			//a b c f d h e g
			double arr2[] = { 0,1,1,2,2,2,3,3 };
			for (int i = 0; i < bfs_rpt.size(); i++)
			{	
				//ss << "i :" << i;
				//Logger::WriteMessage(ss.str().c_str() );
				Assert::AreEqual(arr2[i], bfs_rpt[i].dist, L"arr to bst_rpt shortest check", LINE_INFO());
				//ss.clear();
			}
			g.reset();

			//test3
			g.read_file("test3");
			g.bfs(0, bfs_rpt);
			//             a b d f c g e h i k j l
			double arr3[] = { 0,1,1,1,2,3,2,4,4,4,5,5 };
			for (int i = 0; i < bfs_rpt.size(); i++)
			{
				Assert::AreEqual(arr3[i], bfs_rpt[i].dist, L"arr to bst_rpt check", LINE_INFO());
			}
			g.reset();
		}

		///////////////////////////////////// EXTRACT PATH ////////////////////////////////////////////
		TEST_METHOD(t_extract_path)
		{
			graph g;
			g.read_file("ex1A");
			vector<graph::vertex_label> bfs_rpt;
			g.bfs(0, bfs_rpt);
			vector<int> path;
			Assert::IsFalse(g.extract_path(bfs_rpt, g.name2id("r"), path), L"impossible path", LINE_INFO());
			int i = path.size();
			Assert::AreEqual(0, i, L"test", LINE_INFO());
			path.clear();

			//a -> g
			Assert::IsTrue(g.extract_path(bfs_rpt, g.name2id("g"), path), L"normal path", LINE_INFO());
			Assert::IsTrue(g.t_confirm_path(path, g.name2id("g")), L" confirm path", LINE_INFO()); 
			path.clear();

			//a -> b
			Assert::IsTrue(g.extract_path(bfs_rpt, g.name2id("b"), path), L"normal path", LINE_INFO());
			Assert::IsTrue(g.t_confirm_path(path, g.name2id("b")), L" confirm path", LINE_INFO()); 
			path.clear();

			//a -> d
			Assert::IsTrue(g.extract_path(bfs_rpt, g.name2id("d"), path), L"normal path", LINE_INFO());
			Assert::IsTrue(g.t_confirm_path(path, g.name2id("d")), L" confirm path", LINE_INFO()); 
			path.clear();
			bfs_rpt.clear();

			g.reset();

			//test3
			g.read_file("test3");
			g.bfs(0, bfs_rpt);

			//a -> c
			Assert::IsTrue(g.extract_path(bfs_rpt, g.name2id("d"), path), L"normal path", LINE_INFO());
			Assert::IsTrue(g.t_confirm_path(path, g.name2id("d")), L" confirm path", LINE_INFO()); 
			path.clear();

			//a -> g
			Assert::IsTrue(g.extract_path(bfs_rpt, g.name2id("g"), path), L"normal path", LINE_INFO());
			Assert::IsTrue(g.t_confirm_path(path, g.name2id("g")), L" confirm path", LINE_INFO()); 
			path.clear();

			//a -> j
			Assert::IsTrue(g.extract_path(bfs_rpt, g.name2id("j"), path), L"normal path", LINE_INFO());
			Assert::IsTrue(g.t_confirm_path(path, g.name2id("j")), L" confirm path", LINE_INFO()); 
			path.clear();

			//a -> k
			Assert::IsTrue(g.extract_path(bfs_rpt, g.name2id("k"), path), L"normal path", LINE_INFO());
			Assert::IsTrue(g.t_confirm_path(path, g.name2id("k")), L" confirm path", LINE_INFO()); 
			path.clear();
		}


		TEST_METHOD(t_critical_paths)
		{
			graph g;
			vector<graph::vertex_label> rpt;
			vector<int> path;

			//empty graph
			Assert::IsTrue(g.dag_critical_paths(rpt), L"empty g", LINE_INFO());
			rpt.clear();

			g.read_file("t_cyclic");
			Assert::IsFalse(g.dag_critical_paths(rpt), L"cyclic graph", LINE_INFO());
			rpt.clear();
			g.reset();

			/* // apparently you can't make 1 node graphs
			//single graph
			g.read_file("t_1_node");
			Assert::IsTrue(g.dag_critical_paths(rpt), L"one node", LINE_INFO());
			Assert::IsTrue(g.extract_path(rpt, g.name2id("a"), path), L"extract path", LINE_INFO());
			Assert::IsTrue(g.t_confirm_path(path, g.name2id("a")), L"confirm path", LINE_INFO());
			Assert::IsTrue(g.t_confirm_path_num(path, g.name2id("a"), 0), L"confirm path length", LINE_INFO());
			path.clear();
			rpt.clear();
			g.reset();
			*/
			
			//2-node graph
			g.read_file("t_2_node");
			Assert::IsTrue(g.dag_critical_paths(rpt), L"two nodes", LINE_INFO());
			Assert::IsTrue(g.extract_path(rpt, g.name2id("b"), path), L"extract path", LINE_INFO());
			Assert::IsTrue(g.t_confirm_path(path, g.name2id("b")), L"confirm path", LINE_INFO());
			Assert::IsTrue(g.t_confirm_path_num(path, g.name2id("b"), 1), L"confirm path length", LINE_INFO());
			path.clear();
			rpt.clear();
			g.reset();

			//ex1A
			//a -> b -> d -> e -> g
			g.read_file("ex1A");
			g.dag_critical_paths(rpt);
			Assert::IsTrue(g.extract_path(rpt, g.name2id("g"), path), L"normal path", LINE_INFO());
			Assert::IsTrue(g.t_confirm_path(path, g.name2id("g")), L" confirm path", LINE_INFO());
			Assert::IsTrue(g.t_confirm_path_num(path, g.name2id("g"), 4), L" confirm path length", LINE_INFO());
			path.clear();
			rpt.clear();
			g.reset();

			//test3
			//a -> d -> e -> c -> g -> k -> l -> j
			g.read_file("test3");
			g.dag_critical_paths(rpt);
			Assert::IsTrue(g.extract_path(rpt, g.name2id("j"), path), L"normal path", LINE_INFO());
			Assert::IsTrue(g.t_confirm_path(path, g.name2id("j")), L" confirm path", LINE_INFO());
			Assert::IsTrue(g.t_confirm_path_num(path, g.name2id("j"), 7), L" confirm path length", LINE_INFO());
			path.clear();
			rpt.clear();
			g.reset();

			//aladder
			//a -> d -> e -> c -> g -> k -> l -> j
			g.read_file("aladder.g");
			g.dag_critical_paths(rpt);
			Assert::IsTrue(g.extract_path(rpt, g.name2id("b4"), path), L"normal path", LINE_INFO());
			Assert::IsTrue(g.t_confirm_path(path, g.name2id("b4")), L" confirm path", LINE_INFO());
			g.disp_report(rpt, true);
			Assert::IsTrue(g.t_confirm_path_num(path, g.name2id("b4"), 4), L" confirm path length", LINE_INFO());
			path.clear();
			rpt.clear();
			g.reset();

		}

		TEST_METHOD(t_dag_num_paths)
		{
			graph g;
			vector<graph::vertex_label> rpt;
			vector<int> arr;

			//empty graph
			Assert::IsTrue(g.dag_num_paths(rpt), L"empty g", LINE_INFO());
			rpt.clear();

			g.read_file("t_cyclic");
			Assert::IsFalse(g.dag_num_paths(rpt), L"cyclic graph", LINE_INFO());
			rpt.clear();
			g.reset();

			//2-node graph
			g.read_file("t_2_node");
			Assert::IsTrue(g.dag_num_paths(rpt), L"two nodes", LINE_INFO());
			Assert::AreEqual(1, rpt[0].npaths, L"checking rpt", LINE_INFO());
			Assert::AreEqual(1, rpt[1].npaths, L"checking rpt", LINE_INFO());
			rpt.clear();
			g.reset();

			//ex1A
			//a -> b -> d -> e -> g
			g.read_file("ex1A");
			arr = {};
			Assert::IsTrue(g.dag_num_paths(rpt), L"two nodes", LINE_INFO());
			arr.clear();
			rpt.clear();
			g.reset();

			//test3
			//a -> d -> e -> c -> g -> k -> l -> j
			g.read_file("test3");
			g.dag_num_paths(rpt);

			rpt.clear();
			g.reset();

			//aladder
			//a -> d -> e -> c -> g -> k -> l -> j
			g.read_file("aladder.g");
			g.dag_num_paths(rpt);
			int i = 2;
			i = i + 1;
			rpt.clear();
			g.reset();
		}
	};
}