#include <iostream>
#include <vector>
#include <string>
#include <map>

class User {
public:
    User(const std::string& login, const std::string& password, const std::string& name)
        : login(login), password(password), name(name) {}

    const std::string& getLogin() const {
        return login;
    }

    const std::string& getPassword() const {
        return password;
    }

    const std::string& getName() const {
        return name;
    }

private:
    std::string login;
    std::string password;
    std::string name;
};

class Chat {
public:
    void registerUser(const std::string& login, const std::string& password, const std::string& name) {
        users.push_back(User(login, password, name));
    }

    bool loginUser(const std::string& login, const std::string& password) {
        for (const User& user : users) {
            if (user.getLogin() == login && user.getPassword() == password) {
                return true;
            }
        }
        return false;
    }

    void sendMessage(const std::string& senderLogin, const std::string& receiverLogin, const std::string& message) {
        std::cout << senderLogin << " -> " << receiverLogin << ": " << message << std::endl;
    }

    void broadcastMessage(const std::string& senderLogin, const std::string& message) {
        for (const User& user : users) {
            if (user.getLogin() != senderLogin) {
                std::cout << senderLogin << " -> " << user.getLogin() << ": " << message << std::endl;
            }
        }
    }
    std::string findUserName(std::string login) {
        for (User user : users) {
            if (user.getLogin() == login) {
                return user.getName();
            }
            
        }
    }

private:
    std::vector<User> users;
};

Chat chat;
std::string Username;
bool loggedIn = false;
bool privateChat = false;
std::string privateUser;


void Login() 
{
    std::string login, password;
    std::cout << "Enter login: \r\n";
    std::cin >> login;
    std::cout << "Enter password: \r\n";
    std::cin >> password;
    loggedIn = chat.loginUser(login, password);
    Username = chat.findUserName(login);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
};
void Reg()
{
    std::string login, password, username;
    std::cout << "Enter login: \r\n";
    std::cin >> login;
    std::cout << "Enter password: \r\n";
    std::cin >> password;
    std::cout << "Enter username: \r\n";
    std::cin >> username;
    chat.registerUser(login, password, username);
    Login();
};
void init() {
    std::string c;
    std::cout << "enter oper: \r\n";
    std::cin >> c;
    std::map <std::string, int> commandmap;
    commandmap["login"] = 0;
    commandmap["register"] = 1;
    switch (commandmap[c])
    {
    case 0:
        Login();
        break;
    case 1:
        Reg();
        break;
    default:
        std::cout << "error\r\n";
        break;
    }
}
void tick() {
    while (loggedIn) {
        char input[250];
        std::cout << "Enter message: \r\n";
        std::cin.getline(input,sizeof(input));
        std::map <std::string, int> commandmap;
        commandmap["private"] = 3;
        commandmap["global"] = 1;
        commandmap["exit"] = 2;
        std::string message = input;
        std::string r[2];
        if (message.find("private") != std::string::npos) {
            r[0] = "private";
            r[1] = message.substr(8);
            message = r[0];
        }
        switch (commandmap[message])
        {
        case 3:
            privateChat = true;
            privateUser = r[1];
            break;
        case 1:
            privateChat = false;
            privateUser = "";
            break;
        case 2:
            loggedIn = false;
            break;
        default:
            
            if (privateChat) {
                std::cout << Username + "->" + privateUser + ":" + message + "\r\n";
            }
            else {
                std::cout << Username + ":" + message + "\r\n";
            }
            break;
        }
    }

}
int main() {
   
    chat.registerUser("user1", "password1", "User 1");
    chat.registerUser("user2", "password2", "User 2");
    chat.registerUser("user3", "password3", "User 3");

    while (true)
    {
        init();
        tick();
    }
    // Вход в чат

    //if (chat.Login() {
    //    std::cout << "Login successful!" << std::endl;

    //    // Отправка сообщений
    //    std::string receiverLogin, message;
    //    std::cout << "Enter receiver login: ";
    //    std::cin >> receiverLogin;
    //    std::cout << "Enter message: ";
    //    std::cin.ignore(); // Игнорируем символ новой строки после ввода логина
    //    std::getline(std::cin, message);

    //    chat.sendMessage(login, receiverLogin, message);

    //    // Обмен сообщениями между всеми пользователями
    //    std::cout << "Enter broadcast message: ";
    //    std::getline(std::cin, message);

    //    chat.broadcastMessage(login, message);
    //}
    //else {
    //    std::cout << "Invalid login or password!" << std::endl;
    //}

    return 0;
}