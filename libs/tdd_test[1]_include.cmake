if(EXISTS "/home/pabut/IVS_Project1/libs/tdd_test[1]_tests.cmake")
  include("/home/pabut/IVS_Project1/libs/tdd_test[1]_tests.cmake")
else()
  add_test(tdd_test_NOT_BUILT tdd_test_NOT_BUILT)
endif()
