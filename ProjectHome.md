# About #
Totem is a cross platform C++ header-only library for component and entity system development.

Essentially the library offers robust building blocks to achieve independent components that indirectly can share data and events without ever knowing about each other.

## Features ##
  * Very liberal zlib style [license](http://www.totem-edk.com/developer/license/).
  * No third-party dependencies.
  * Template-based component system with runtime rtti and custom constructor parameters.
  * Template-based property system with string hash indexing and value changed signal callback.
  * Shared properties.
  * Property-list system with string hash indexing and multiple state change signal callbacks.
  * CMake build files with advanced preprocessing capabilities to shoehorn Totem into your project code.
  * Event system addon.
  * Delegate system addon.
  * Multiple examples showing how Totem can be used.