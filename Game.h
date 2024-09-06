#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "AssetManager.cpp"
#include "Settings.h"
#include "Savings.h"

class Game {
private:
    sf::Font          font;
    Settings&         settings;
    Leaderboards&     leaderboards;
    Savings&          savings;
    sf::RenderWindow& window;
    bool end = false;
public:
    static inline std::string textEntered;
    static inline int score = 0;
    static inline float wordsSpeed = 0.01;
    static inline std::vector<std::vector<sf::Text>> words = std::vector<std::vector<sf::Text>>();
    static inline std::pair<int, int> wave;

    std::vector<std::string> sixLength = std::vector<std::string>{
            "apple", "monkey", "zebra", "quick", "happy", "grape",
            "chair", "table", "house", "beach", "jolly", "clock",
            "smile", "flame", "brave", "cloud", "ocean", "lemon",
            "bread", "fancy", "daisy", "eagle", "jumpy", "grill",
            "bunny", "crane", "drift", "elite", "flora", "globe",
            "honey", "inbox", "jazzy", "knack", "lucky", "melon",
            "noble", "olive", "pearl", "quack", "racer", "shade",
            "tiger", "ultra", "vivid", "whale", "xenon", "yacht",
            "zippy", "alarm", "blend", "charm", "dwarf", "eager",
            "frost", "giant", "hover", "icily", "joust", "kneel",
            "lodge", "mimic", "ninja", "orbit", "piano", "quake",
            "robot", "swarm", "trend", "under", "viper", "wrist",
            "xerox", "yield", "zonal", "amber", "broil", "claim",
            "donut", "eject", "flock", "glide", "haunt", "inlet",
            "ball", "cat", "dog", "egg", "fan", "gum", "hat", "ink",
            "jam", "kite", "log", "map", "net", "owl", "pen", "quiz"
    };

    std::vector<std::string> nineLength = std::vector<std::string>{
           "holiday", "journey", "morning", "evening", "mountain",
           "fantasy", "mystery", "gallery", "victory", "freedom",
           "whisper", "thunder", "explorer", "kingdom", "radiant",
           "serenity", "harmony", "tranquil", "sunshine", "voyager",
           "beautiful", "elephant", "giraffe", "dolphin", "universe",
           "kangaroo", "imagine", "miracle", "treasure", "courage",
           "discovery", "adventure", "laughter", "twilight", "rainbow",
           "whenever", "whatever", "somebody", "anything", "everything",
           "triumph", "crystals", "dynamics", "elegance", "embrace",
           "festival", "gorgeous", "horizons", "innocent", "landmark",
           "marathon", "memories", "milestone", "paradise", "patience",
           "peaceful", "progress", "profound", "romantic", "sanctuary",
           "sapphire", "sequence", "shelter", "shimmer", "spectral",
           "spectrum", "starlight", "stunning", "superior", "swimming",
           "synergy", "temporal", "tranquil", "treasure", "vacation",
           "velocity", "vertical", "vitality", "volcano", "wholesome",
           "wildlife", "wilderness", "wonderful", "workshop", "yourself",
           "yesterday", "abundant", "absolute", "abstract", "accurate",
           "activity", "addition", "adequate", "advanced", "affinity",
           "allegory", "alliance", "although", "ambition", "analysis"
   };

    std::vector<std::string> twelveLength = {
            "adventurous", "celebration", "perception", "consequence", "destination",
            "discovery", "entertain", "friendship", "generation", "happiness",
            "imagination", "inspiration", "leadership", "motivation", "opportunity",
            "perfection", "reflection", "resolution", "relationship", "significant",
            "transformation", "understand", "vulnerability", "appreciation", "confidence",
            "determined", "excitement", "fascination", "gratitude", "illumination",
            "improvement", "interaction", "invitation", "meaningful", "observation",
            "possibility", "remarkable", "sensitivity", "successful", "adventurous",
            "aspiration", "astonishing", "capability", "celebratory", "challenging",
            "commitment", "complicated", "considerate", "creativity", "dedication",
            "developing", "encouraging", "enthusiasm", "essentially", "expression",
            "extraordinary", "fascinating", "fulfillment", "generosity", "harmonizing",
            "impressive", "independent", "innovation", "involvement", "justifiable",
            "leadership", "meaningful", "motivational", "negotiation", "observation",
            "opportunity", "partnership", "persistence", "philosophical", "preparation",
            "productive", "proficiency", "recognition", "reliability", "remarkable",
            "significant", "spontaneity", "stimulating", "successful", "supervision",
            "sustainable", "transcendent", "unbelievable", "understanding", "unforgettable",
            "universal", "vulnerability", "willingness", "wonderfully", "admirable",
            "application", "appropriate", "authenticity", "beneficial", "celebration"
    };


    Game(sf::RenderWindow &window, std::string font, Settings &settings, Leaderboards& leaderboards, Savings& savings) :
            window(window), font(AssetManager::getFont(font)), settings(settings), leaderboards(leaderboards), savings(savings)
            {
        wave = std::pair<int, int>(0, 5);
    }

    auto showGame()     -> void;
    auto endGameMenu()  -> void;
    auto restart()      -> void;
    auto addNewWords(Shape& shape) -> void;
    auto getWordLength()    -> std::vector<std::string>&;
    auto shortcuts(sf::Event event) -> void;
    auto updateFrame(std::vector<std::vector<sf::Text>>& words, sf::RectangleShape const& yellow,
                           sf::RectangleShape const& red, sf::RectangleShape const& dead, sf::Text& userScore,
                           Shape& typeArea, sf::Text& scoreText, sf::Text& waveText, sf::Text& waveTextInt,
                           sf::Music& pop) -> void;
};
