add_test([=[Vehicle.TyreDragOnly]=]  K:/Study_Material_AC/Control_Projects/Cruise_Control/build/vehicle_test.exe [==[--gtest_filter=Vehicle.TyreDragOnly]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vehicle.TyreDragOnly]=]
  PROPERTIES
    
    _CMAKE_TEST_BUILD_DEPENDS [==[K:/Study_Material_AC/Control_Projects/Cruise_Control/build/vehicle_test.exe]==]
    DEF_SOURCE_LINE [==[K:\Study_Material_AC\Control_Projects\Cruise_Control\tests\vehicle_test.cpp:10]==]
    WORKING_DIRECTORY [==[K:/Study_Material_AC/Control_Projects/Cruise_Control/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vehicle.EngineLag]=]  K:/Study_Material_AC/Control_Projects/Cruise_Control/build/vehicle_test.exe [==[--gtest_filter=Vehicle.EngineLag]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vehicle.EngineLag]=]
  PROPERTIES
    
    _CMAKE_TEST_BUILD_DEPENDS [==[K:/Study_Material_AC/Control_Projects/Cruise_Control/build/vehicle_test.exe]==]
    DEF_SOURCE_LINE [==[K:\Study_Material_AC\Control_Projects\Cruise_Control\tests\vehicle_test.cpp:27]==]
    WORKING_DIRECTORY [==[K:/Study_Material_AC/Control_Projects/Cruise_Control/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vehicle.TopSpeed]=]  K:/Study_Material_AC/Control_Projects/Cruise_Control/build/vehicle_test.exe [==[--gtest_filter=Vehicle.TopSpeed]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vehicle.TopSpeed]=]
  PROPERTIES
    
    _CMAKE_TEST_BUILD_DEPENDS [==[K:/Study_Material_AC/Control_Projects/Cruise_Control/build/vehicle_test.exe]==]
    DEF_SOURCE_LINE [==[K:\Study_Material_AC\Control_Projects\Cruise_Control\tests\vehicle_test.cpp:41]==]
    WORKING_DIRECTORY [==[K:/Study_Material_AC/Control_Projects/Cruise_Control/build]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
set(vehicle_test_TESTS [==[Vehicle.TyreDragOnly]==] [==[Vehicle.EngineLag]==] [==[Vehicle.TopSpeed]==])
