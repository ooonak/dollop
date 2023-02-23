include(FetchContent)

if(MANAGE_DEPENDENCIES_WITH_FETCH_CONTENT)
    message(STATUS "Dependencies are handled by FetchContent.")

    FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.11.0
    )

    FetchContent_Declare(
        toml
        GIT_REPOSITORY https://github.com/ToruNiina/toml11.git
        GIT_TAG v3.7.1
    )

    FetchContent_Declare(
        msgpack
        GIT_REPOSITORY https://github.com/msgpack/msgpack-c.git
        GIT_TAG cpp-5.0.0
    )

    FetchContent_Declare(
        sodium
        GIT_REPOSITORY https://github.com/jedisct1/libsodium.git
        GIT_TAG 1.0.18
    )

    # https://www.boost.org/users/history/version_1_81_0.html
    FetchContent_Declare(
        boost
        URL https://boostorg.jfrog.io/artifactory/main/release/1.81.0/source/boost_1_81_0.tar.gz
        URL_HASH SHA256=205666dea9f6a7cfed87c7a6dfbeb52a2c1b9de55712c9c1a87735d7181452b6
    )

    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.13.0
    )

    FetchContent_MakeAvailable(googletest boost spdlog toml msgpack sodium)
endif()
