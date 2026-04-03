cmake_minimum_required(VERSION 3.16)
project(scheduler C)

set(CMAKE_C_STANDARD 11)

find_package(Threads REQUIRED)

add_executable(scheduler
        main.c
        process/pcb.c
        scheduler/scheduler.c
        interrupt/interrupt.c
        process/threads.c
        process/threads.h
        process/process_threads.c
        process/process_threads.h
)

target_compile_options(scheduler PRIVATE -Wall -Wextra -g)
target_link_libraries(scheduler PRIVATE Threads::Threads)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(scheduler PRIVATE
            -fsanitize=address
            -fsanitize=undefined
            -fno-omit-frame-pointer
    )
    target_link_options(scheduler PRIVATE
            -fsanitize=address
            -fsanitize=undefined
    )
endif()

