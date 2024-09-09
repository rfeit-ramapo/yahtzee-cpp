#include <string>
#include <vector>

using namespace std;

class Category
{
    public:

        // Constructors
        Category() {}; // Default

        Category(string a_name, string a_description, string a_score):
        m_name(a_name), m_description(a_description), m_score(a_score)
        {};

        Category(string a_name, string a_description, string a_score, string a_winner, int a_points, int a_round):
        m_name(a_name), m_description(a_description), m_score(a_score), m_winner(a_winner), m_points(a_points), m_round(a_round)
        {};

        // Setters
        inline void const SetWinner(string a_winner) { m_winner = a_winner; }
        inline void const SetPoints(int a_points) { m_points = a_points; }
        inline void const SetRound(int a_round) { m_round = a_round; }

    private:
        string m_name;
        string m_description;
        string m_score;
        string m_winner;
        int m_points;
        int m_round;
};