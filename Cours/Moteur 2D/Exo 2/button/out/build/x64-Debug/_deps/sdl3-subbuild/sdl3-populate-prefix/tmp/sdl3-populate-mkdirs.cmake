# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Users/icotvaquero/Documents/GitHub/G-TECH-1/Moteur 2D/Exo 2/button/out/build/x64-Debug/_deps/sdl3-src")
  file(MAKE_DIRECTORY "C:/Users/icotvaquero/Documents/GitHub/G-TECH-1/Moteur 2D/Exo 2/button/out/build/x64-Debug/_deps/sdl3-src")
endif()
file(MAKE_DIRECTORY
  "C:/Users/icotvaquero/Documents/GitHub/G-TECH-1/Moteur 2D/Exo 2/button/out/build/x64-Debug/_deps/sdl3-build"
  "C:/Users/icotvaquero/Documents/GitHub/G-TECH-1/Moteur 2D/Exo 2/button/out/build/x64-Debug/_deps/sdl3-subbuild/sdl3-populate-prefix"
  "C:/Users/icotvaquero/Documents/GitHub/G-TECH-1/Moteur 2D/Exo 2/button/out/build/x64-Debug/_deps/sdl3-subbuild/sdl3-populate-prefix/tmp"
  "C:/Users/icotvaquero/Documents/GitHub/G-TECH-1/Moteur 2D/Exo 2/button/out/build/x64-Debug/_deps/sdl3-subbuild/sdl3-populate-prefix/src/sdl3-populate-stamp"
  "C:/Users/icotvaquero/Documents/GitHub/G-TECH-1/Moteur 2D/Exo 2/button/out/build/x64-Debug/_deps/sdl3-subbuild/sdl3-populate-prefix/src"
  "C:/Users/icotvaquero/Documents/GitHub/G-TECH-1/Moteur 2D/Exo 2/button/out/build/x64-Debug/_deps/sdl3-subbuild/sdl3-populate-prefix/src/sdl3-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/icotvaquero/Documents/GitHub/G-TECH-1/Moteur 2D/Exo 2/button/out/build/x64-Debug/_deps/sdl3-subbuild/sdl3-populate-prefix/src/sdl3-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/icotvaquero/Documents/GitHub/G-TECH-1/Moteur 2D/Exo 2/button/out/build/x64-Debug/_deps/sdl3-subbuild/sdl3-populate-prefix/src/sdl3-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
