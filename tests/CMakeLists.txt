find_package(Qt6 REQUIRED COMPONENTS Test)

# Тест 1: Виженер
add_executable(test_vigenere
    test_vigenere.cpp
    ../src/VigenereCipher.cpp
)
target_link_libraries(test_vigenere PRIVATE Qt6::Core Qt6::Test)
add_test(NAME test_vigenere COMMAND test_vigenere)

# Тест 2: MD5
add_executable(test_md5
    test_md5.cpp
    ../src/MD5.cpp
)
target_link_libraries(test_md5 PRIVATE Qt6::Core Qt6::Test)
add_test(NAME test_md5 COMMAND test_md5)

# Тест 3: Метод секущих
add_executable(test_secant
    test_secant.cpp
    ../src/SecantMethod.cpp
)
target_link_libraries(test_secant PRIVATE Qt6::Core Qt6::Test)
add_test(NAME test_secant COMMAND test_secant)

# Тест 4: Граф
add_executable(test_graph
    test_graph.cpp
    ../src/GraphCycle.cpp
)
target_link_libraries(test_graph PRIVATE Qt6::Core Qt6::Test)
add_test(NAME test_graph COMMAND test_graph)

# Тест 5: Сервер
add_executable(test_server
    test_server.cpp
    ../src/ServerStub.cpp
)
target_link_libraries(test_server PRIVATE Qt6::Core Qt6::Test)
add_test(NAME test_server COMMAND test_server)