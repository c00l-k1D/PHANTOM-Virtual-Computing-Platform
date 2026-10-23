# CMake generated Testfile for 
# Source directory: C:/Users/User/Desktop/Проекты/GitHub/Релиз/PHANTOM — Virtual Computing Platform
# Build directory: C:/Users/User/Desktop/Проекты/GitHub/Релиз/PHANTOM — Virtual Computing Platform/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(cpu_tests "C:/Users/User/Desktop/Проекты/GitHub/Релиз/PHANTOM — Virtual Computing Platform/build/Debug/cpu_tests.exe")
  set_tests_properties(cpu_tests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/User/Desktop/Проекты/GitHub/Релиз/PHANTOM — Virtual Computing Platform/CMakeLists.txt;23;add_test;C:/Users/User/Desktop/Проекты/GitHub/Релиз/PHANTOM — Virtual Computing Platform/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(cpu_tests "C:/Users/User/Desktop/Проекты/GitHub/Релиз/PHANTOM — Virtual Computing Platform/build/Release/cpu_tests.exe")
  set_tests_properties(cpu_tests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/User/Desktop/Проекты/GitHub/Релиз/PHANTOM — Virtual Computing Platform/CMakeLists.txt;23;add_test;C:/Users/User/Desktop/Проекты/GitHub/Релиз/PHANTOM — Virtual Computing Platform/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(cpu_tests "C:/Users/User/Desktop/Проекты/GitHub/Релиз/PHANTOM — Virtual Computing Platform/build/MinSizeRel/cpu_tests.exe")
  set_tests_properties(cpu_tests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/User/Desktop/Проекты/GitHub/Релиз/PHANTOM — Virtual Computing Platform/CMakeLists.txt;23;add_test;C:/Users/User/Desktop/Проекты/GitHub/Релиз/PHANTOM — Virtual Computing Platform/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(cpu_tests "C:/Users/User/Desktop/Проекты/GitHub/Релиз/PHANTOM — Virtual Computing Platform/build/RelWithDebInfo/cpu_tests.exe")
  set_tests_properties(cpu_tests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/User/Desktop/Проекты/GitHub/Релиз/PHANTOM — Virtual Computing Platform/CMakeLists.txt;23;add_test;C:/Users/User/Desktop/Проекты/GitHub/Релиз/PHANTOM — Virtual Computing Platform/CMakeLists.txt;0;")
else()
  add_test(cpu_tests NOT_AVAILABLE)
endif()
