#ifndef MAP_UTILS_H
#define MAP_UTILS_H

#include <map>

template<typename K, typename V>
static std::map<V, K> reverseMap(const std::map<K, V>& m) {
	map<V, K> r;
	for (const auto& kv : m)
		r[kv.second] = kv.first;
	return r;
}


#endif
