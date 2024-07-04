# Algorithm Visualizer

This project will eventually be a general-purpose algorihm visualizer.

It mostly will serve as my practice for getting back into graphics programming, so I hope to get comfortable enough to eventually transition into OpenGL.

**If you have any suggestions on how I can improve this project, please feel free to reach out!**

## Setting up SFML

1. Download and extract [SFML v2.6.1](https://www.sfml-dev.org/download/sfml/2.6.1/) for your respective system.
2. Inside the extracted folder, among other directories, you should see `include` and `lib`.

   - Inside `include`, there should be a folder called `SFML`. Place this folder inside this project's `/include/` directory. Your `/include/` directory should look something like this:

     ```
     include/
         ...
         SFML/
         ...
     ```

   - Inside this project's directory, create a folder called `lib`. After doing so, the directory should look something like this:

     ```
     .vscode/
     assets/
     include/
     lib/
     src/
     .gitignore
     Makefile
     README.md
     ```

     Next, create a folder called `SFML` inside of the newly created `/lib/`. In this folder, copy the contents of the downloaded SFML `/lib/` directory. After doing so it should look something like this:

     ```
     lib/
         SFML/
             libsfml-audio.2.6.1.dylib
             ...
             libsfml-window.dylib
     ```

   _Note: Across different systems the file extensions inside your `/lib/` directory may be something different like `.dll`_

## Compiling

- `make`: Compiles the program into the `/bin/` directory.
- `make run`: Compiles & runs the program.
- `make clean`: Clean up function for clearing out old builds.
