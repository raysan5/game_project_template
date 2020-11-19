## C++ Coding Style Conventions

Here it is a list with some of the conventions used in this project template:

Code element | Convention | Example
--- | :---: | ---
Defines | ALL_CAPS | `#define PLATFORM_DESKTOP`
Macros | ALL_CAPS | `#define MIN(a,b) (((a)<(b))?(a):(b))`
Variables | lowerCase | `int screenWidth = 0;`
Local variables | lowerCase | `Vector2 playerPosition;`
Global variables | lowerCase | `bool fullscreen = false;`
Constants | lowerCase | `const int maxValue = 8`
Pointers | MyType* pointer | `Texture2D* array;`
float values | always x.xf | `float value = 10.0f`
Operators | value1 * value2 | `int product = value * 6;`
Operators | value1 / value2 | `int division = value / 4;`
Operators | value1 + value2 | `int sum = value + 10;`
Operators | value1 - value2 | `int res = value - 5;`
Enum | TitleCase | `enum TextureFormat`
Enum members | ALL_CAPS | `UNCOMPRESSED_R8G8B8`
Struct | TitleCase | `struct Texture2D`
Struct members |lowerCase | `texture.id`
Functions | TitleCase | `InitWindow()`
Class | TitleCase | `class Player`
Class Fields | lowerCase | `Vector2 position`
Class Methods | TitleCase | `GetPosition()`
Ternary Operator | (condition)? result1 : result2 | `printf("Value is 0: %s", (value == 0)? "yes" : "no");`

 - Project uses aligned braces or curly brackets:
```c
void SomeFunction()
{
   // TODO: Do something here!
}
```

 - Project uses **TABS** instead of 4 spaces.

 - Trailing spaces MUST be avoided!
 
 ## Files and Directories Naming Conventions
 
  - Directories will be named using `TitleCase` : `Assets/Audio/Music`
  
  - Files will be named using `snake_case`: `main_title.png`
  
  _NOTE: Avoid any space or special character in the files/dir naming!_
  
  ### Directories Organization:
  
Files should be organized by context and usage in the game, think about the loading requirements and put all the assets that need to be loaded at the same time together.

Here an example, note that some assets require to be loaded all at once while other assets require to be loaded only at initialization (gui, font).
  
```
Assets/Audio/Fx/long_jump.wav
Assets/Audio/Music/main_theme.ogg
Assets/Screens/Logo/logo.png
Assets/Screens/Title/title.png
Assets/Screens/Gameplay/background.png
Assets/Characters/player.png
Assets/Characters/enemy_slime.png
Assets/Common/font_arial.ttf
Assets/GUI/gui.png
```

Use descriptive names for the files, it would be perfect if just reading the name of the file, it was possible to know what is that file and where it fits in the game.
