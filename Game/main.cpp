#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <time.h>
#include <Windows.h>
#include <string>

using namespace sf;
using namespace std;

int game()
{

    /*
    

    IpAddress ip = IpAddress::getLocalAddress();
    TcpSocket socket;
    string user;
    cin >> user;
    if (user == "host")
    {
        TcpListener listener;
        listener.listen(66666);
        cout << "..." << endl;
        if (listener.accept(socket) != Socket::Done)
            return -1;
    }
    if (user == "client")
    {
        cout << "..." << endl;
        if (socket.connect(ip, 66666, seconds(10)) != Socket::Done)
        {
            return -1;
        }
    }

    */


    //random number generator

    srand(time(0));
    RenderWindow window(VideoMode(400, 400), "MINESWEEPER");

    int w = 32;
    int grid[12][12];
    int sgrid[12][12]; //for showing

    //texture 

    Texture t;
    t.loadFromFile("D:/mine/icons.jpg");
    Sprite s(t);

    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++)
        {
            sgrid[i][j] = 10;
            if (rand() % 5 == 0)  grid[i][j] = 9;
            else grid[i][j] = 0;
        }
    }

    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++)
        {
            int n = 0;
            if (grid[i][j] == 9) continue;
            if (grid[i + 1][j] == 9) n++;
            if (grid[i][j + 1] == 9) n++;
            if (grid[i - 1][j] == 9) n++;
            if (grid[i][j - 1] == 9) n++;
            if (grid[i + 1][j + 1] == 9) n++;
            if (grid[i - 1][j - 1] == 9) n++;
            if (grid[i - 1][j + 1] == 9) n++;
            if (grid[i + 1][j - 1] == 9) n++;
            grid[i][j] = n;
        }
    }

    while (window.isOpen())
    {
        Vector2i pos = Mouse::getPosition(window);
        int x = pos.x / w;
        int y = pos.y / w;

        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

            if (e.type == Event::MouseButtonPressed)
                if (e.key.code == Mouse::Left) sgrid[x][y] = grid[x][y];
                else if (e.key.code == Mouse::Right) sgrid[x][y] = 11;
        }


        /*
        

        Packet packet;

        if (socket.receive(packet) == Socket::Done)
        {
            Vector2f pos;
            packet >> x >> y;
        }

         if (socket.send(packet) != Socket::Done)
         {
             return -1;
         }
     

        */

        window.clear(Color::White);

        for (int i = 1; i <= 10; i++)
            for (int j = 1; j <= 10; j++)
            {
                if (sgrid[x][y] == 9) sgrid[i][j] = grid[i][j];
                s.setTextureRect(IntRect(sgrid[i][j] * w, 0, w, w));
                s.setPosition(i * w, j * w);
                window.draw(s);
            }

        window.display();
    }

    return 0;
}


int main()
{

    game();

    return 0;
}