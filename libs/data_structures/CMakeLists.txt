add_library(data_structures
        bitset/bitset.c
        ordered_set/ordered_set.c
        unordered_set/unordered_set.c
		vector/vector.c
	void_vector/void_vector.c
	matrix/matrix.c
        matrix/matrix.h
)

target_link_libraries(data_structures algorithms)