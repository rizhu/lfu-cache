clean:
	rm -rf build/

test: test_kv_linked_list_basic test_kv_linked_list_copy test_kv_linked_list_move test_lfu_cache_hashable test_lfu_cache_basic test_lfu_cache_copy

test_kv_linked_list_basic:
	mkdir -p build/
	mkdir -p build/kv_linked_list/
	g++ -std=c++20 -o build/kv_linked_list/test_basic tests/kv_linked_list/test_basic.cpp
	./build/kv_linked_list/test_basic

test_kv_linked_list_copy:
	mkdir -p build/
	mkdir -p build/kv_linked_list/
	g++ -std=c++20 -o build/kv_linked_list/test_copy tests/kv_linked_list/test_copy.cpp
	./build/kv_linked_list/test_copy

test_kv_linked_list_move:
	mkdir -p build/
	mkdir -p build/kv_linked_list/
	g++ -std=c++20 -o build/kv_linked_list/test_move tests/kv_linked_list/test_move.cpp
	./build/kv_linked_list/test_move

test_lfu_cache_hashable:
	mkdir -p build/
	mkdir -p build/lfu_cache/
	g++ -std=c++20 -o build/lfu_cache/test_hashable tests/lfu_cache/test_hashable.cpp
	./build/lfu_cache/test_hashable

test_lfu_cache_basic:
	mkdir -p build/
	mkdir -p build/lfu_cache/
	g++ -std=c++20 -o build/lfu_cache/test_basic tests/lfu_cache/test_basic.cpp
	./build/lfu_cache/test_basic

test_lfu_cache_copy:
	mkdir -p build/
	mkdir -p build/lfu_cache/
	g++ -std=c++20 -o build/lfu_cache/test_copy tests/lfu_cache/test_copy.cpp
	./build/lfu_cache/test_copy