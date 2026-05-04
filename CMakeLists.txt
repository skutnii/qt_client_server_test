cmake_minimum_required(VERSION 3.10...3.27)

project(wirex_test)

set(CMAKE_CXX_STANDARD 23)

find_package(Qt6 REQUIRED COMPONENTS 
		Core
	  Gui
	  Widgets
	  Network
)

qt6_wrap_cpp(server_moc_sources server_app.h) 

add_executable(test_server 
								server.cpp 
								server_app.cpp 
								user_record.cpp
								${server_moc_sources})
target_link_libraries(test_server PRIVATE Qt6::Network)
target_include_directories(test_server AFTER PRIVATE 
														${Qt6Network_INCLUDE_DIRS})

qt6_wrap_cpp(client_moc_sources client_window.h client_view_model.h) 

add_executable(test_client client.cpp 
								client_window.cpp 
								client_view_model.cpp 
								user_record.cpp
								${client_moc_sources})
target_link_libraries(test_client PRIVATE Qt6::Network Qt6::Widgets)
target_include_directories(test_client AFTER PRIVATE 
														${Qt6Network_INCLUDE_DIRS}
														${Qt6Widgets_INCLUDE_DIRS})

if (PROJECT_IS_TOP_LEVEL AND UNIX)
    # Create symlink to compile_commands.json for IDEs to pick it up
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_BINARY_DIR}/compile_commands.json
            ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
    )
endif()
