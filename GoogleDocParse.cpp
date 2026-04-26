#include <iostream>
#include <string>
#include <curl/curl.h>
#include <map>
#include <vector>
#include <windows.h>
using namespace std;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

string fetchHTML(const string& url) {
    CURL* curl;
    string response;

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }

    return response;
}

vector<string> get_td(string tr) {


    size_t pos = 0;
    vector<string> values;
    while ((pos = tr.find("<td", pos)) != string::npos)
    {
        size_t start = pos + 70; // length of <td>
        size_t end = tr.find("</span>", start);

        string value = tr.substr(start, end - start);

        values.push_back(value);
        pos = end + 7; // move past </span>
    }
    
    return values;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    string url = "https://docs.google.com/document/d/e/2PACX-1vSvM5gDlNvt7npYHhp_XfsJvuntUhq184By5xO_pA4b_gCWeXb6dM6ZxwN8rE6S4ghUsCj2VKR21oEP/pub";
    string html = fetchHTML(url);
    
    vector<string> values = get_td(html);
    values.erase(values.begin(), values.begin() + 3);

    map<pair<int, int>, string> positions;
    int max_x = 0;
    int max_y = 0;
    for (int i = 0; i < values.size(); i += 3)
    {
        int x = stoi(values[i]);
        string ch = values[i + 1];
        int y = stoi(values[i + 2]);

        positions[{x, y}] = ch;

        if (x > max_x)
            max_x = x;
        if (y > max_y)
            max_y = y;
    }
    
    vector<vector<string>> grid(max_y + 1,vector<string>(max_x + 1, " "));
    for (auto& entry : positions)
    {
        int x = entry.first.first;
        int y = entry.first.second;
        string ch = entry.second;

        grid[y][x] = ch;
    }
    for (const auto& row : grid)
    {
        for (const auto& cell : row)
        {
            cout << cell;
        }
        cout << endl;
    }
    system("pause > 0");

    return 0;
}