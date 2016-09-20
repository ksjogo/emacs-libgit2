# CMake build script for emacs-libgit2

PROJECT(emacs-libgit2 C)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)

SET(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
SET(BUILD_CLAR FALSE)
SET(BUILD_SHARED_LIBS FALSE)

IF(APPLE)
  SET(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
ENDIF(APPLE)

ADD_SUBDIRECTORY(libgit2)
INCLUDE_DIRECTORIES(libgit2/include)

ADD_LIBRARY(git2-core SHARED libgit2-core.c)
TARGET_LINK_LIBRARIES(git2-core c -static git2)

ADD_CUSTOM_COMMAND(
  OUTPUT include/emacs-module.h
  COMMAND curl -SL https://github.com/emacs-mirror/emacs/raw/master/src/emacs-module.h --create-dirs -o include/emacs-module.h)
ADD_CUSTOM_TARGET(curl_emacs_module DEPENDS include/emacs-module.h)
ADD_DEPENDENCIES(git2-core curl_emacs_module)

