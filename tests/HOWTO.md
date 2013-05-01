Writing test applications using CMake
=====================================

* Create a new directory in this directory (which will be referred
  to as the "new test directory").
* Use the EUSDAB::Application class, overriding its optional
  callbacks `event`, `update` and `render` methods.
* Keep all files in the "new test directory".
* Add a line `add_subdirectory("new test directory")` to the 
  "CMakeLists.txt" file in this directory.
* Add a CMakeLists.txt inspired by the ones in existing subdirectories.
