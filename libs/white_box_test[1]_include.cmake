if(EXISTS "/home/pabut/IVS_Project1/libs/white_box_test[1]_tests.cmake")
  include("/home/pabut/IVS_Project1/libs/white_box_test[1]_tests.cmake")
else()
  add_test(white_box_test_NOT_BUILT white_box_test_NOT_BUILT)
endif()
