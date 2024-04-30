cmake_minimum_required(VERSION 3.26)
project(C23Exe C)

set(CMAKE_C_STANDARD 23)

add_executable(C23Exe main.c)

add_library(str string/string_.h string/string_.c
# string/tasks/digitToStartTransform.h
# string/tasks/reverseWords.h
# string/tasks/replaceDigitsBySpaces.h
# ...
# < файл с решением задачи >
# ...
# string/tasks/hasPairOfWordsWithEqualLetterSet.h
# string/tasks/printWordsNonEqualLastWord.h
)
# описываем, что для запуска project потребуется сборка tasks
target_link_libraries(C23Exe str)

add_library(19_laba 19_laba/file.h 19_laba/file.c)
target_link_libraries(C23Exe 19_laba)

add_subdirectory(libs)
target_link_libraries(C23Exe data_structures)
target_link_libraries(C23Exe algorithms)
