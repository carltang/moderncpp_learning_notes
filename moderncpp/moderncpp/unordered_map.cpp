//
//  unordered_map.cpp
//  moderncpp
//
//  Created by carltang on 2024/4/21.
//

#include "unordered_map.hpp"
#include <unordered_map>
#include <vector>
using namespace std;

/*
 std::map底层数据结构是红黑树，

 std::unordered_map底层是hash，

 而unordered_map没有专门的hash提供给std::pair,
 
 所以一定要用std::pair的话，把unordered_map换成map，

 或者自己定义一个hash结构并传递给std::pair
 */
struct pair_hash {
	 template <class T1, class T2>
	 std::size_t operator () (std::pair<T1, T2> const &v) const {
		 return std::hash<T1>()(v.first) ^ std::hash<T2>()(v.second);
	 }
 };

 int maxPoints(vector<vector<int>>& points) {
	 std::unordered_map<std::pair<float, float>, int, pair_hash> line_count;
	 int num = static_cast<int>(points.size());
	 for (int i = 0; i < num - 1; ++ i) {
		 for (int j = i + 1; j < num; ++ j) {
			 float tmp = points[i][1] * points[j][0] - points[j][1] * points[i][0];
			 float yy = points[i][0] == points[j][0] ? INT_MAX : tmp / (points[j][0] - points[i][0]);
			 float xx = points[i][1] == points[j][1] ? INT_MAX : tmp / (points[i][1] - points[j][1]);
			 std::pair<float, float> line(xx, yy);
			 line_count[line] = line_count[line] + 1;
			 /*
			 if (line_count.contains(line)) {
				 line_count[line] = line_count[line] + 1;
			 } else {
				 line_count[line] = 1;
			 }
			 */
		 }
	 }
	 int max_count = 0;
	 for (const auto& k : line_count) {
		 if (k.second > max_count) {
			 max_count = k.second;
		 }
	 }
	 return int((sqrt(8 * max_count + 1) + 1) / 2);
 }
