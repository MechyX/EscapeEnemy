#include "game.h"

Game :: Game(){
    window = new sf::RenderWindow(sf::VideoMode(32*16,32*16) , "Escape the enemy");
    window->setFramerateLimit(60);
    player = new Player();
    enemy = new Enemy();
    gameMap = new Map();

    showMenu();
}

Game :: ~Game(){
    std::cout << "DESTRUCTING OLD GAME" << std::endl;  
    window->close();
    delete window;
    window = NULL;
    delete player;
    player = NULL;
    delete enemy;
    enemy = NULL;
    delete gameMap;
    gameMap = NULL;
}

void Game :: showMenu(){

    //load texture bg
    sf::Texture textureBG;
    if(!textureBG.loadFromFile("bg.jpg")){
        std::cout << "could not load background texture" << std::endl;
        exit(1);
    }
    std::cout << "Loaded main menu Background Texture" << std::endl; 

    sf::Sprite bg(textureBG);

    //load font
    sf::Font font;
    if(!font.loadFromFile("font.ttf")){
        std::cout << "could not load font" << std::endl;
        exit(1);
    }
    
    std::cout << "Loaded the font" << std::endl;

    //create buttons and set colors
    Button playButton(std::string("PLAY"), sf::Vector2f(200.f,256.f), sf::Vector2f(100.f,50.f),font);
    Button closeButton(std::string("EXIT"), sf::Vector2f(200.f,320.f), sf::Vector2f(100.f,50.f),font);
    
    playButton.setTextColor(sf::Color::Green);
    closeButton.setTextColor(sf::Color::Cyan);

    playButton.setBackgroundColor(sf::Color::Transparent);
    closeButton.setBackgroundColor(sf::Color::Transparent);
    
    //title text
    sf::Text title;
    title.setFont(font);
    title.setString("ESCAPE THE ENEMY");
    title.setFillColor(sf::Color::Red);
    title.setStyle(sf::Text::Bold);
    title.setCharacterSize(70);
    title.setPosition(sf::Vector2f(100.f,90.f));

    bool startx = false;
    
    //game loop
    while(!startx){
        sf::Event event;
         while(window->pollEvent(event) && !startx){

            if(event.type == sf::Event::Closed){
                std::cout << "game window closed" << std::endl;     
                window->close();   
                exit(0);   
            }

            if(event.type == sf::Event::MouseButtonPressed){

                if(event.mouseButton.button == sf::Mouse::Left){
                    if(playButton.isClicked(sf::Vector2f(event.mouseButton.x , event.mouseButton.y)))
                        startx = true;
                        
                    else if(closeButton.isClicked(sf::Vector2f(event.mouseButton.x , event.mouseButton.y)))
                        exit(0);
                }
                
            }
    }
    window->clear();
    window->draw(bg);
    window->draw(title);
    playButton.drawButton(*window);
    closeButton.drawButton(*window);
    window->display();
}
}

void Game :: start(){
    std::cout << "Game started" << std::endl;
    //16x16 tile map

     int level[] = {
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
        3, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 3, 
        3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, // 2 , 4,9
        3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, // 3 , 4,9
        3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 3, // 4 , 4,9
        3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, // 5 , 1,12
        3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, // 6 , 1,12
        3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
        3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
        3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
        3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3, //10 , 4,9
        3, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 3, 
        3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
        3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, // 13
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    };

    //declare obstacles here itself
    std::vector< std::pair<uint,uint>> obstacles;

        for(uint i = 0 ; i < 16 ; i++)
            for(uint j = 0 ; j < 16; ++j)
                if(level[i*16 + j] != 0)
                    obstacles.push_back(std::make_pair(i - 1,j - 1));
        
        


    bool endGame = false;

      if(!gameMap->intialize(level , sf::Vector2u(32,32) , 16 , 16)){
        std::cout << "Error loading map" << std::endl;
        exit(1);
     }
    
    sf::Clock enemySpeed;           
    sf::Clock playerSpeed;
    sf::Clock newPath;
    sf::Clock gameClock;
    while(!endGame){
        sf::Event event;
       
        while(window->pollEvent(event)){
            if(event.type == sf::Event::Closed){
                std::cout << "game window closed" << std::endl;
                window->close();
                exit(0);
            }

       //player can move only one tile for a 0.1 second
       
       if(playerSpeed.getElapsedTime().asSeconds() > 0.1){
           if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                player->moveUp(obstacles);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
               player->moveDown(obstacles);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                player->moveRight(obstacles);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
               player->moveLeft(obstacles);
            }
        playerSpeed.restart();
       }    
        }
    
        if(enemySpeed.getElapsedTime().asSeconds() > 0.2){
            enemy->moveNext();
            enemySpeed.restart();
        }

        else if(newPath.getElapsedTime().asSeconds() > 2){
            enemy->findPath(player->getPos());
            newPath.restart();
        }

        //enemy moves even more slower than that
        

        if(player->getPos() == enemy->getPos()){
            endGame = true;
            gameTime = gameClock.getElapsedTime();
        }

        window->clear();
        window->draw(*gameMap);
        window->draw(*player);
        window->draw(*enemy);
        window->display();   
    }
}

bool Game :: gameOver(){
    std::cout << "Game Over" << std::endl;
    //display gameover create some buttons as well....

    sf::Font font;
    if(!font.loadFromFile("font.ttf")){
        std::cout << "could not load font" << std::endl;
        exit(1);
    }

    //create buttons and set colors
    Button playButton(std::string("PLAY AGAIN"), sf::Vector2f(200.f,256.f), sf::Vector2f(100.f,50.f),font);
    Button closeButton(std::string("EXIT"), sf::Vector2f(200.f,320.f), sf::Vector2f(100.f,50.f),font);
    
    playButton.setTextColor(sf::Color::Green);
    closeButton.setTextColor(sf::Color::Cyan);

    playButton.setBackgroundColor(sf::Color::Transparent);
    closeButton.setBackgroundColor(sf::Color::Transparent);
    
    //title text
    sf::Text title;
    title.setFont(font);
    title.setString(std::string("YOU SURVIVED FOR ") + std::to_string(gameTime.asSeconds() / 60) + std::string(" minutes"));
    title.setFillColor(sf::Color::Red);
    title.setStyle(sf::Text::Bold);
    title.setCharacterSize(40);
    title.setPosition(sf::Vector2f(40.f,90.f));

    bool truth = false;

    while(!truth){
        sf::Event event;
         while(window->pollEvent(event) && !truth){

            if(event.type == sf::Event::Closed){
                std::cout << "game window closed" << std::endl;     
                window->close();   
                exit(1);   
            }

            if(event.type == sf::Event::MouseButtonPressed){

                if(event.mouseButton.button == sf::Mouse::Left){
                    if(playButton.isClicked(sf::Vector2f(event.mouseButton.x , event.mouseButton.y)))
                        truth = true;
                        
                    else if(closeButton.isClicked(sf::Vector2f(event.mouseButton.x , event.mouseButton.y)))
                        exit(0);
                    
                    }

            }
   
        }
    window->clear();
    window->draw(title);
    playButton.drawButton(*window);
    closeButton.drawButton(*window);
    window->display();
}
    return truth;
}