//#pragma once
//#include "Component.h"
//#include <chrono>
//#include <vector>
//#include <iostream>
//
//class GameObject;
//
//namespace dae
//{
//    class PerformanceGraphComponent : public Component
//    {
//	public:
//		PerformanceGraphComponent(GameObject* owner);
//		~PerformanceGraphComponent();
//
//		PerformanceGraphComponent(const PerformanceGraphComponent& other) = delete;
//		PerformanceGraphComponent(PerformanceGraphComponent&& other) noexcept = delete;
//		PerformanceGraphComponent& operator=(const PerformanceGraphComponent& other) = delete;
//		PerformanceGraphComponent& operator=(PerformanceGraphComponent&& other)	noexcept = delete;
//
//		void Exercise1();
//		void Exercise2();
//
//
//        template <typename T>
//        void DoPerformanceTest()
//        {
//            const int size = 1 << 26; // Size of the array
//            const int num_experiments = 10; // Number of experiments to run
//            std::vector<T> objects(size);
//            int stepsize;
//
//            for (int i = 0; i < size; i++)
//            {
//                if constexpr (std::is_pointer_v<T>)
//                {
//                    objects[i] = new GameObject3D();
//                    objects[i]->id = 0;
//                }
//                else if constexpr (std::is_same_v<T, int>)
//                {
//                    objects[i] = 0;
//                }
//                else
//                {
//                    objects[i].id = 0;
//                }
//            }
//
//            for (stepsize = 1; stepsize <= 1024; stepsize *= 2)
//            {
//                std::vector<double> durations;
//
//                for (int exp = 0; exp < num_experiments; exp++)
//                {
//                    auto start = std::chrono::high_resolution_clock::now();
//
//                    for (int i = 0; i < size; i += stepsize)
//                    {
//                        if constexpr (std::is_pointer_v<T>)
//                        {
//                            objects[i]->id *= 2; // Perform some operation
//                        }
//                        else if constexpr (std::is_same_v<T, int>)
//                        {
//                            objects[i] *= 2; // Perform some operation
//                        }
//                        else
//                        {
//                            objects[i].id *= 2; // Perform some operation
//                        }
//                    }
//
//                    auto end = std::chrono::high_resolution_clock::now();
//                    std::chrono::duration<double, std::micro> duration = end - start;
//                    durations.push_back(duration.count());
//                }
//
//                // Remove the top and bottom outliers
//                std::sort(durations.begin(), durations.end());
//                durations.erase(durations.begin());
//                durations.pop_back();
//
//                // Calculate the average duration
//                double average_duration = std::accumulate(durations.begin(), durations.end(), 0.0) / durations.size();
//
//                std::cout << average_duration << std::endl;
//            }
//
//            if constexpr (std::is_pointer_v<T>)
//            {
//                for (int i = 0; i < size; i++)
//                {
//                    delete objects[i];
//                }
//            }
//        }
//    };
//
//	struct transform
//	{
//		float matrix[16] = {
//			1,0,0,0,
//			0,1,0,0,
//			0,0,1,0,
//			0,0,0,1
//		};
//	};
//
//	class GameObject3D
//	{
//	public:
//		transform local{};
//		int id{ 1 };
//
//		GameObject3D& operator*=(int rhs)
//		{
//			id *= rhs;
//			return *this;
//		}
//	};
//}
