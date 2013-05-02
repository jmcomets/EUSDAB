Writing test applications using CMake
=====================================

* Create a new directory in this directory (which will be referred
  to as the new test directory).
* Use the EUSDAB::Application class, overriding its optional
  callbacks `event`, `update` and `render` methods.
* Keep all files in the new test directory.
* Add a line with the test name to the `EUSDAB_TESTS` variable
