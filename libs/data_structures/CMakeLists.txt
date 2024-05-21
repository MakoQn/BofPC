add_library(data_structures
        bitset/bitset.c
        ordered_set/ordered_set.c
        unordered_set/unordered_set.c
		vector/vector.c
	void_vector/void_vector.c
	matrix/matrix.c
        matrix/matrix.h
	string/string_.c
	string/string_.h
	19_laba/file.c
	19_laba/file.h
	20_laba/TASK9.с
)

target_link_libraries(data_structures algorithms)