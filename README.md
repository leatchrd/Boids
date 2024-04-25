### How to use the application?
To simplify the use of the application, you can use certain keys on the keyboard.

*For a QWERTY keyboard:*
- Press the Q key to quit the application.
- Press the Z and X keys to pause and play the application.

*For a AZERTY keyboard:*
- Press the A key to quit the application.
- Press the W and X keys to pause and play the application.


### How to use our wandering submarine?
Our submarine can move in all directions. To do this, you must use the keyboard keys. Note that the movement takes place from the submarine's point of view.

*For a QWERTY keyboard:*
- Press the W key to go forward.
- Press the S key to go backwards.
- Press the A key to go left.
- Press the D key to go right.
- Press the space key to go up.
- Press the left ctrl key on the keyboard to go down.

*For a AZERTY keyboard:*
- Press the Z key to go forward.
- Press the S key to go backwards.
- Press the Q key to go left.
- Press the D key to go right.
- Press the space key to go up.
- Press the left ctrl key on the keyboard to go down.


### How to look at the scene from all its angles?
It is also possible to change the point of view. To do this, move the camera with the keyboard keys or the mouse.

- Press the left key to rotate left.
- Press the right key to rotate right.
- Press the up key to rotate up.
- Press the down key to rotate down.
- If you would rather use the mouse, right-click and drag.
- Scroll up to to move toward in the aquarium.
- Scroll down to to move away from in the aquarium.



### How to use the ImGui menu?
The ImGui menu allows you to vary the simulation parameters.

- To move the slider for each setting, left-click and drag left or right. Changes are made live.


The first slider sets the *level of detail* of the scene textures. Defaulting to 1.5, the lower the slider value, the more pixelated the textures will be and vice versa.


*The three rules for the behavior of our boids.*
The second slider allows you to play on the ability of the fish to move away from each other. The default value is 1, the higher the value the more the fish will separate if they are close together.

The third slider allows you to play on the ability of fish to go in the same direction as their neighbors. The default value is 1, the higher the value, the more fish will line up in the same direction.

The fourth slider allows you to play on the cohesion of the fish between them. The default value is 1, the higher the value, the more nearby fish will group together.



### Lights?
⚠️ Since the applications lighting thanks to the fragment shader isn't complete, we chose not to have it present in the `main` branch. However, you can have a look at the code we put together regarding the lighting in the `lighting` branch.



### Simple-p6-Setup

This template contains all the things you need to get started with a clean and modern C++ project (formatter, linter, tests, continuous integration, etc.).
**It works on all platforms (Windows, Linux, MacOS).**

- [Setting up](#setting-up)
  - [Creating a repository](#creating-a-repository)
  - [Downloading your repository](#downloading-your-repository)
  - [Compiling](#compiling)
  - [Clangd](#clangd)
  - [Formatter](#formatter)
  - [Linter](#linter)
- [Coding](#coding)
  - [Renaming the project](#renaming-the-project)
  - [Folder structure](#folder-structure)
  - [p6](#p6)
- [Going further](#going-further)
  - [Writing tests](#writing-tests)
  - [Warnings as errors](#warnings-as-errors)



## Setting up
### Creating a repository

First, create your own repository based on this one. If you are using GitHub you can use this repository as a template:

![image](https://user-images.githubusercontent.com/45451201/217287736-20058d69-f0ed-40ff-b4e5-cfd852e2ba82.png)

Otherwise simply create a repository on your own and copy-paste all the files in this repo to your new repo.

**NB:** you might also want to change or remove the LICENSE file. Your project does not need to use the same license as the one we use for this template.

### Downloading your repository

Run this command inside the directory where you want to put this project:

```
git clone your_repo_url
```

### Compiling

If that is not already done, [install a compiler](https://julesfouchy.github.io/Learn--Clean-Code-With-Cpp/lessons/install-a-compiler/).

If that is not already done, [setup your IDE for C++ development](https://julesfouchy.github.io/Learn--Clean-Code-With-Cpp/lessons/ide/).

Once that is done, open the project folder in your IDE: it will detect the CMakeLists.txt file automatically and you can just run the project:
![image](https://user-images.githubusercontent.com/45451201/217290500-bd09bc81-861f-4da9-b3c6-fef5e28a83f6.png)

You should see this, with the circle following your mouse cursor:

![initial-window](https://user-images.githubusercontent.com/45451201/217267551-9134512a-6462-4637-963e-d1e5e9519f29.png)

🎉 Congrats you are **almost** done! But keep reading, we will now install amazing tools that will make your life so much easier!

### Clangd

First, you need to [install and setup _clangd_](https://julesfouchy.github.io/Learn--Clean-Code-With-Cpp/lessons/clangd/). It will provide even better C++ support than the default extensions, and is also required for the other tools to work.

### Formatter

[Setup clang-format](https://julesfouchy.github.io/Learn--Clean-Code-With-Cpp/lessons/formatting-tool/).

### Linter

[Setup clang-tidy](https://julesfouchy.github.io/Learn--Clean-Code-With-Cpp/lessons/static-analysers/).

## Coding

### Renaming the project

If you want to rename the project (called "Simple-p6-Setup" by default), you need to change it in 3 places:

- In the `CMakeLists.txt`, change the line `project(Simple-p6-Setup)`
- In the `.github/workflows/build_and_run_tests.yml`, change the line `TARGET: Simple-p6-Setup`
- In the `src/main.cpp`, change the line `auto ctx = p6::Context{{.title = "Simple-p6-Setup"}};`

### Folder structure

All your source files (.cpp) and header files (.hpp) need to go in the `src` folder. It is recommended to have the corresponding .cpp and .hpp next to each other:

```
src
   main.cpp
   some_folder
      some_file.cpp
      some_file.hpp
      another_file.cpp
      another_file.hpp
   another_folder
      a_third_file.cpp
      a_third_file.hpp
```

### p6

_p6_ is a 2D-drawing library that is designed to be extremely simple to use. In order to learn how to use it, [read their tutorials](https://julesfouchy.github.io/p6-docs/tutorials/the-context). (Note that you can skip the first chapter "Creating a project" as this template already does everything you need).

## Going further

### Writing tests

This template comes with the [Doctest](https://github.com/doctest/doctest) testing library all set up.
You can simply write something like

```cpp
TEST_CASE("Addition is commutative")
{
    CHECK(1 + 2 == 2 + 1);
    CHECK(4 + 7 == 7 + 4);
}
```

in _any_ source file and the tests will run whenever you run your project. You will see their output in the console:

![tests-output](https://user-images.githubusercontent.com/45451201/217270153-73d865d0-dc25-4176-b5eb-af2e9afb507e.png)

To learn more about Doctest, see https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md

### Warnings as errors

Warnings are usually only considered as errors during the CI process (so that any warning is considered a failure and gets reported to you).
If you want to have warnings as errors in your local project too (typically in order to fix a warning shown by the CI):

- <kbd>CTRL</kbd> + <kbd>SHIFT</kbd> + <kbd>P</kbd> (to open VSCode's command palette)
- Search for `CMake: Edit CMake Cache (UI)`
- Turn `WARNINGS_AS_ERRORS` ON and then save
  ![image](https://user-images.githubusercontent.com/45451201/217280969-48939e75-0bad-4a9f-bdf6-08e37649c4c6.png)
