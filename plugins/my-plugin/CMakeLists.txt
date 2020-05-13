project(my-plugin)

set(my-plugin_SOURCES
      my-plugin.c
      my-output.c
)

add_library(my-plugin SHARED ${my-plugin_SOURCES})
target_link_libraries(my-plugin libobs)

install_obs_plugin_with_data(my-plugin data)
