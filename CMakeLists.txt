cmake_minimum_required( VERSION 2.8 )
 
# Create Project
project( hackrfiotest C CXX)
add_executable( hackrfiotest HackrfIoTest.cpp )
set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT "hackrfiotest" )
 
# Find Packages
find_package( HACKRF REQUIRED )
 
if( HACKRF_FOUND )
  include_directories( ${HACKRF_INCLUDE_DIRS} )
  link_directories( ${HACKRF_LIBRARY_DIRS} )
  target_link_libraries( hackrfiotest ${HACKRF_LIBRARIES} )
endif()
