#include <iostream>
#include <string>
#include <unistd.h>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>

using namespace std;
using namespace state;

int main(int argc,char* argv[])
{
    string testString = argv[1];
    if(testString=="state"){
        //execl ("/home/ensea/plt/build","make unittest", (char *)0);
        system("cd build ;make unittest;sleep 1;make code-coverage");
    }else{

        
        cout << testString << endl;

        cout << "It works !" << endl;
    }
	




    return 0;
}
