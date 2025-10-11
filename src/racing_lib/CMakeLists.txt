
add_library(racing_lib STATIC
    car.h car.cpp
    level.h
    levelutil.h levelutil.cpp
    renderer.h renderer.cpp
    IBackend.h
)

#target_link_libraries(racing_lib )
