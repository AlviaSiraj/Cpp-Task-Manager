# C++ SFML Time Management App

This is a desktop-based time management application built using C++ and SFML (Simple and Fast Multimedia Library). The app features a playful UI with animated animal characters and a visually engaging task container. Users can view a live timer and manage simple tasks via an intuitive interface. A popup modal allows users to add new tasks easily.

🧪 This app is currently ongoing and continuously being improved.

## 💻Technology Used

<a href="https://isocpp.org/" title="C++"><img src="https://github.com/get-icon/geticon/raw/master/icons/c-plusplus.svg" alt="C++" width="21px" height="21px"></a>
<a href="https://www.sfml-dev.org/" title="SFML"><img src="https://upload.wikimedia.org/wikipedia/en/thumb/0/07/SFML_Logo.svg/1280px-SFML_Logo.svg.png" alt="SFML" width="21px" height="21px"></a>
<a href="https://code.visualstudio.com/" title="Visual Studio Code"><img src="https://github.com/get-icon/geticon/raw/master/icons/visual-studio-code.svg" alt="VS Code" width="21px" height="21px"></a>

### ✨Features

- 🐾 Cute Themed UI: Animals like bears, cats, dogs, and frogs create a cozy, fun environment.

- ⏱ Live Timer: (Currently static) Displays a running or fixed digital timer.

- ✅ Task Container: A visual panel where task-related information is shown.

- ➕ Add Task Popup: Opens a modal to simulate adding new tasks.

- 🖱 Interactive UI: Cursor changes and clickable buttons offer engaging interaction.

- 💡 Expandable Architecture: Designed for future additions like saving tasks or timer logic.

## 🚀Installation & Running

1. Clone the repository

```bash
git clone https://github.com/AlviaSiraj/Cpp-Task-Manager.git
```

2. Install SFML
   Install SFML from sfml-dev.org
   Or via package managers:

- Windows: Use vcpkg or download manually

- macOS: brew install sfml

- Linux: sudo apt install libsfml-dev

3. Compile the App
   Using g++:

```bash
g++ main.cpp -o TimeManager -lsfml-graphics -lsfml-window -lsfml-system

```

4. Run the App

```bash
./TimeManager
```

## 🛠 Roadmap

#### Version 0.1.0

- Basic animal-themed interface created

- Timer and static task panel implemented

- Add Task popup working

#### Coming Soon

- Timer start/pause functionality

- Dynamic task entry and display

- Save/load tasks with file I/O

- Keyboard input handling

## 🙌 Conclusion

This SFML-based time management app is designed to bring a playful experience to staying productive. While simple in functionality, it serves as a creative starting point for building C++ UI-based applications using SFML. More features and polish are on the way!
