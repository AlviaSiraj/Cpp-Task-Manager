#include <SFML/Graphics.hpp>
#include <sstream> // declares classes, templates, and other types for reading from and writing to strings in the same manner as reading from and writing to files
#include <iostream>
using namespace std;

// Helper Function
// Resizing sprite function
map<string, sf::Texture> textures; // storing textures in a map
sf::Sprite createScaledSprite(const string &key, const string &filepath, float width, float height)
{
    sf::Texture texture;
    if (!texture.loadFromFile(filepath))
    {
        throw runtime_error("Failed to load texture: " + filepath);
    }
    textures[key] = texture; // stores a copy (safe & persists)
    sf::Sprite sprite(textures[key]);

    sf::Vector2u textureSize = textures[key].getSize();
    float scaleX = width / textureSize.x;
    float scaleY = height / textureSize.y;
    sprite.setScale(scaleX, scaleY);

    return sprite;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Time Management App"); // creates the window

    // Loading background
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("assets/background.png"))
        return -1;
    sf::Sprite background(bgTexture);

    // loading font
    sf::Font font;
    if (!font.loadFromFile("assets/pixel-font.ttf"))
        return -1;

    bool showPopup = false;

    // Timer text
    sf::Text timer("00:00:00", font, 37);
    timer.setFillColor(sf::Color::Black);
    timer.setPosition(113, 630); // Position in bear's sign

    /********** Adding the animals**************/
    // bear
    sf::Sprite bear = createScaledSprite("bear", "assets/bear.png", 400.0f, 410.0);
    bear.setPosition(0, 420); // Adjust as needed
    // hamster
    sf::Sprite hamster = createScaledSprite("hamster", "assets/hamster.png", 200.0f, 210.0);
    hamster.setPosition(0, 220); // Adjust as needed
    // cat
    sf::Sprite cat = createScaledSprite("cat", "assets/cat.png", 300.0f, 310.0);
    cat.setPosition(100, 20); // Adjust as needed

    // duck
    sf::Sprite chick = createScaledSprite("chick", "assets/chick.png", 400.0f, 410.0);
    chick.setPosition(600, 20); // Adjust as needed
    // dog
    sf::Sprite dog = createScaledSprite("dog", "assets/dog.png", 400.0f, 410.0);
    dog.setPosition(600, 450); // Adjust as needed
    // frog
    sf::Sprite frog = createScaledSprite("frog", "assets/frog.png", 400.0f, 410.0);
    frog.setPosition(350, 550); // Adjust as needed
    // bunny
    sf::Sprite bunny = createScaledSprite("bunny", "assets/bunny.png", 400.0f, 410.0);
    bunny.setPosition(700, 280); // Adjust as needed

    // // clock logic
    // sf::Clock clock;

    // Rectangle
    sf::RectangleShape taskContainer;
    taskContainer.setSize(sf::Vector2f(400, 500));
    // taskContainer.setOutlineColor(sf::Color::Black);
    taskContainer.setFillColor(sf::Color(217, 217, 217));
    // taskContainer.setOutlineThickness(1);
    taskContainer.setPosition(320, 160);

    // task title text
    sf::Text taskTitle("Tasks", font, 35);
    taskTitle.setFillColor(sf::Color::Black);
    taskTitle.setPosition(470, 160); // Position in bear's sign

    // Title
    sf::Texture titleContainer;
    sf::Sprite roundedRectSprite = createScaledSprite("rectangle", "assets/rectangle.png", 1720.0f, 1720.0);
    roundedRectSprite.setPosition(-360, -585); // wherever you want

    sf::Text title("Task Manager", font, 35);
    title.setFillColor(sf::Color::Black);
    title.setPosition(390, 30); // Position in bear's sign

    // AddButton
    sf::RectangleShape addTaskButton(sf::Vector2f(100, 40));
    addTaskButton.setFillColor(sf::Color(244, 185, 185)); // pastel pink
    addTaskButton.setPosition(600, 600);                  // Top-right corner

    sf::Text buttonText("Add Task", font, 20);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setPosition(610, 605); // Position in bear's sign

    // Define closeButton inside popup (for now, just a dummy)
    sf::RectangleShape closeButton(sf::Vector2f(80, 40));
    closeButton.setFillColor(sf::Color(200, 200, 255));
    closeButton.setPosition(400, 420);

    sf::Text closeText("Close", font, 20);
    closeText.setFillColor(sf::Color::Black);
    closeText.setPosition(410, 425);

    sf::RectangleShape okButton(sf::Vector2f(80, 40));
    okButton.setFillColor(sf::Color(200, 200, 255));
    okButton.setPosition(500, 420);

    sf::Text okText("Add", font, 20);
    okText.setFillColor(sf::Color::Black);
    okText.setPosition(520, 425);

    // cursor control
    sf::Cursor arrowCursor;
    sf::Cursor handCursor;

    // Load system cursors
    if (!arrowCursor.loadFromSystem(sf::Cursor::Arrow) ||
        !handCursor.loadFromSystem(sf::Cursor::Hand))
    {
        throw runtime_error("Error loading cursor");
    }

    // this is for the popup user input
    string userTaskInput = "";
    string desc = "";
    bool typingTask = false;
    bool typingDesc = false;

    // Adding the input boxes:
    sf::RectangleShape taskInputBox(sf::Vector2f(300, 40));
    taskInputBox.setFillColor(sf::Color(255, 255, 255));
    taskInputBox.setPosition(350, 250);
    // Adding the input boxes:
    sf::RectangleShape descInputBox(sf::Vector2f(300, 40));
    descInputBox.setFillColor(sf::Color(255, 255, 255));
    descInputBox.setPosition(350, 300);
    // dropdown
    //  Adding the input boxes:
    sf::RectangleShape timeInput(sf::Vector2f(100, 40));
    timeInput.setFillColor(sf::Color(255, 255, 255));
    timeInput.setPosition(450, 350);

    sf::Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(20);
    inputText.setFillColor(sf::Color::Black);
    inputText.setPosition(taskInputBox.getPosition().x + 10, taskInputBox.getPosition().y + 5);

    sf::Text descInputText;
    descInputText.setFont(font);
    descInputText.setCharacterSize(20);
    descInputText.setFillColor(sf::Color::Black);
    descInputText.setPosition(descInputBox.getPosition().x + 10, descInputBox.getPosition().y + 5);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();
            // if the addTaskButton is pressed, show the popup modal
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                // if the current mouse position is the addbutton position and is clicked
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                if (addTaskButton.getGlobalBounds().contains(mousePos))
                {
                    showPopup = true;
                }

                if (showPopup && closeButton.getGlobalBounds().contains(mousePos) || showPopup && okButton.getGlobalBounds().contains(mousePos))
                {
                    showPopup = false;
                }
                if (taskInputBox.getGlobalBounds().contains(mousePos))
                {
                    typingTask = true;
                    typingDesc = false;
                }
                else if (descInputBox.getGlobalBounds().contains(mousePos))
                {
                    typingTask = false;
                    typingDesc = true;
                }
                else
                {
                    typingTask = false;
                    typingDesc = false;
                }
            }
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b')
                { // Handle backspace
                    if (typingTask && !userTaskInput.empty())
                        userTaskInput.pop_back();
                    if (typingDesc && !desc.empty())
                        desc.pop_back();
                }
                else if (event.text.unicode == '\r' || event.text.unicode == '\n')
                {
                    typingTask = false;
                    typingDesc = false;
                    cout << "Entered: " << userTaskInput << endl; // value stored
                    cout << "Entered: " << desc << endl;          // value stored
                }
                else if (event.text.unicode < 128)
                { // Only ASCII
                    if (typingTask)
                        userTaskInput += static_cast<char>(event.text.unicode);
                    if (typingDesc)
                        desc += static_cast<char>(event.text.unicode);
                }
                inputText.setString(userTaskInput);
                descInputText.setString(desc);
            }
        }
        // update cursor
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        window.setMouseCursor(addTaskButton.getGlobalBounds().contains(mousePos) ||
                                      (showPopup && closeButton.getGlobalBounds().contains(mousePos)) || (showPopup && okButton.getGlobalBounds().contains(mousePos))
                                  ? handCursor
                                  : arrowCursor);
        // Update timer
        timer.setString("00:00:00");

        window.clear();
        window.draw(background);
        window.draw(bear);
        window.draw(hamster);
        window.draw(cat);
        window.draw(chick);
        window.draw(dog);
        window.draw(frog);
        window.draw(bunny);

        window.draw(timer);

        window.draw(taskContainer);
        window.draw(taskTitle);
        window.draw(roundedRectSprite);
        window.draw(title);

        window.draw(addTaskButton);
        window.draw(buttonText);

        if (showPopup)
        {
            sf::RectangleShape popup(sf::Vector2f(400, 300));
            popup.setFillColor(sf::Color(255, 228, 225));
            popup.setPosition(300, 200);

            sf::Text title("Add New Task", font, 20);
            title.setFillColor(sf::Color::Black);
            title.setPosition(440, 210);

            window.draw(popup);
            window.draw(title);
            window.draw(closeButton);
            window.draw(closeText);
            window.draw(okButton);
            window.draw(okText);
            window.draw(taskInputBox);
            window.draw(inputText);
            window.draw(descInputBox);
            window.draw(descInputText);
            window.draw(timeInput);
        }

        window.display();
    }
    return 0;
}
