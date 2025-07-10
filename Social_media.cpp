#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct Post {
    string author;
    string content;
    int likes;

    Post(string a, string c) : author(a), content(c), likes(0) {}
};

class User {
public:
    string username;
    string password;

    User(string u, string p) : username(u), password(p) {}
};

class SocialMedia {
private:
    vector<User> users;
    vector<Post> posts;
    map<string, bool> loggedInUsers;

public:
    void registerUser() {
        string username, password;
        cout << "Enter new username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        for (auto& user : users) {
            if (user.username == username) {
                cout << "Username already exists.\n";
                return;
            }
        }

        users.emplace_back(username, password);
        cout << "User registered successfully!\n";
    }

    bool loginUser() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        for (auto& user : users) {
            if (user.username == username && user.password == password) {
                loggedInUsers[username] = true;
                cout << "Login successful!\n";
                return true;
            }
        }
        cout << "Invalid credentials.\n";
        return false;
    }

    void postMessage(const string& username) {
        if (!loggedInUsers[username]) {
            cout << "You must be logged in to post.\n";
            return;
        }

        cin.ignore();
        string content;
        cout << "Enter your post: ";
        getline(cin, content);

        posts.emplace_back(username, content);
        cout << "Post created!\n";
    }

    void viewPosts() {
        cout << "\n--- All Posts ---\n";
        for (size_t i = 0; i < posts.size(); ++i) {
            cout << "[" << i << "] " << posts[i].author << ": " << posts[i].content
                 << " ❤️ " << posts[i].likes << " likes\n";
        }
    }

    void likePost() {
        int index;
        cout << "Enter post index to like: ";
        cin >> index;

        if (index >= 0 && index < posts.size()) {
            posts[index].likes++;
            cout << "You liked the post!\n";
        } else {
            cout << "Invalid post index.\n";
        }
    }
};
int main() {
    SocialMedia app;
    string currentUser;
    int choice;

    while (true) {
        cout << "\n--- Social Media Simulator ---\n";
        cout << "1. Register\n2. Login\n3. Post Message\n4. View Posts\n5. Like Post\n6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                app.registerUser();
                break;
            case 2:
                if (app.loginUser()) {
                    cout << "Enter your username again to continue: ";
                    cin >> currentUser;
                }
                break;
            case 3:
                app.postMessage(currentUser);
                break;
            case 4:
                app.viewPosts();
                break;
            case 5:
                app.viewPosts();
                app.likePost();
                break;
            case 6:
                cout << "Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}



